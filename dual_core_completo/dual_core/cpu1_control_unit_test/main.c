#include "main.h"

const int struct_size = sizeof(local_sh);

void main(void)
{

    InitSysCtrl();

    //if standalone is active cpu1 will try to start cpu2
#ifdef _STANDALONE
#ifdef _FLASH

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

    InitGpio();

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    cpu1_timer_setup();

    //stop both timers
    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;

    GPIOSetup();

    uart_setup();

    // Write auth of some banks of Global Shared (GS) RAM is
    // given to CPU2
    while( !(
            MemCfgRegs.GSxMSEL.bit.MSEL_GS15 &
            MemCfgRegs.GSxMSEL.bit.MSEL_GS14 &
            MemCfgRegs.GSxMSEL.bit.MSEL_GS13 &
            MemCfgRegs.GSxMSEL.bit.MSEL_GS12 &
             MemCfgRegs.GSxMSEL.bit.MSEL_GS11))
    {
        EALLOW;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS15 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS14 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS13 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS12 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS11 = 1;
        EDIS;
    }

    EINT;
    ERTM;

    InitEPwm4Gpio();
    InitEPwm5Gpio();
    InitEPwm6Gpio();

    //Muxing epwm e adc to CPU2
    EALLOW;
    DevCfgRegs.CPUSEL0.bit.EPWM4 = 1;
    DevCfgRegs.CPUSEL0.bit.EPWM5 = 1;
    DevCfgRegs.CPUSEL0.bit.EPWM6 = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_A = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_B = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_C = 1;
    EDIS;

    //CAN muxed to CPU2
    send_can_to_cpu2();

    //shared struct copied in local variable
    local_sh = sh;

    CpuTimer1Regs.TCR.bit.TSS = 0;      //Start telemetry timer

    //stop timer2 - it's not used for the moment
    CpuTimer2Regs.TCR.bit.TSS = 1;

    Uint16 i;
    while(1)
    {
        if(i > 1000)
            i = 0;
        i++;
    }
}

void cpu1_timer_setup(void)
{
    EALLOW;

    PieVectTable.TIMER1_INT = &cpu_timer1_isr;
    PieVectTable.TIMER2_INT = &cpu_timer2_isr;
    EDIS;

    InitCpuTimers();

    ConfigCpuTimer(&CpuTimer1, 200, 20000);
    ConfigCpuTimer(&CpuTimer2, 200, 8000);

    CpuTimer1Regs.TCR.all = 0x4000;
    CpuTimer2Regs.TCR.all = 0x4000;

    IER |= M_INT13;   //timer1
    IER |= M_INT14;   //timer2

    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
}

void send_can_to_cpu2(void)
{
    EALLOW;
    CpuSysRegs.PCLKCR10.bit.CAN_A = 0;
    CpuSysRegs.PCLKCR10.bit.CAN_B = 0;
    EDIS;

    EALLOW;
    DevCfgRegs.CPUSEL8.bit.CAN_A = 1;
    DevCfgRegs.CPUSEL8.bit.CAN_B = 1;
    EDIS;

    CANInit(CANA_BASE);
    CANInit(CANB_BASE);
}

/*
 * every cycle of timer1 shared data are copied into
 * local variables to avoid concurrent access of cpu2 while
 * cpu1 is logging
 */
void Shared_Ram_dataRead_c1(void)
{

    local_sh = sh;
    local_time_elapsed = time_elapsed;
}

__interrupt void cpu_timer1_isr(void)
{
        CpuTimer1.InterruptCount++;

        Shared_Ram_dataRead_c1();

    #ifdef LOGGING
        compute_AMKStatus();

        if(CpuTimer1.InterruptCount % 500 == 0){
            GPIO_WritePin(RED_BLINK, 1);
        }
        // ESP32 message
        char data[sizeof(local_sh)];
        memcpy(data, &local_sh, sizeof(local_sh));
        char ptr[sizeof(local_sh)*2];

        int i;
        for(i=0; i<sizeof(local_sh); i++){
            ptr[i*2] = data[i] & 0x00FF;
            ptr[i*2+1] = data[i] >> 8;
        }

        char encoded[sizeof(ptr) + 2];
        cobs_encode(encoded, sizeof(encoded)-1, &ptr, sizeof(ptr));
        encoded[sizeof(ptr) + 1] = '\0';
        // ESP32 message

        scic_msg(encoded);
    #endif

        if(CpuTimer1.InterruptCount % 100 == 0){
            GPIO_WritePin(RED_BLINK, 0);
        }
}

//not necessary at the moment
__interrupt void cpu_timer2_isr(void)
{
}

/*
 * Function to compress amk status in one Byte
 */
void compute_AMKStatus(){
    int index = 0;
    for(index = 0; index < 4; index++)
    {
        AmkStatus[index] = 0;
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bSystemReady);
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bError << 1);
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bWarn << 2);
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bQuitDcOn << 3);
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bDcOn << 4);
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bQuitInverterOn << 5);
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bInverterOn << 6);
        AmkStatus[index] |= (local_sh.motorVal1[index].AMK_bInverterOn << 7);
    }
}




