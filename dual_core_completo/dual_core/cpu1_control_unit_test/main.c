#include "main.h"

void main(void)
{

    InitSysCtrl();

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

    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;

    GPIOSetup();
    setupSD();
    uart_setup();

    while( !(
            MemCfgRegs.GSxMSEL.bit.MSEL_GS14 &
            MemCfgRegs.GSxMSEL.bit.MSEL_GS2 &
             MemCfgRegs.GSxMSEL.bit.MSEL_GS1))
    {
        EALLOW;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS14 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS2 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS1 = 1;
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

    send_can_to_cpu2();


    local_sh = sh;
    //DELAY_US(10000);
    char str_init[100];
    sprintf(str_init , "throttle | steering | brake | brakePress | status | actualVelocityKMH \n");
    writeSD(str_init);

    CpuTimer1Regs.TCR.bit.TSS = 0;        //start timer1
    CpuTimer2Regs.TCR.bit.TSS = 0;        //do not start timer2



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
    ConfigCpuTimer(&CpuTimer2, 200, 100000);

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

void Shared_Ram_dataRead_c1(void)
{

    local_sh = sh;
    local_time_elapsed = time_elapsed;
}

__interrupt void cpu_timer1_isr(void)
{
        //setupSD();
        EALLOW;
        CpuTimer1.InterruptCount++;
        //GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        //GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
        EDIS;

        Shared_Ram_dataRead_c1();

        char cmd[200];
        int index;

        sprintf(cmd, "timestamp %d stop", (int)local_time_elapsed);
        writeSD(cmd);

        for(index = 0; index < 4; index++)
        {
           //TO USE
           sprintf(cmd , "%d %d %d %d %d %d %d %d %d %d %d %d"  //MotorVal1
                   " %d %d %d %d"                               //MotorVal2
                   " %d %d %d %d %d %d %d",                     //MotorSetP
                           local_sh.motorVal1[index].AMK_ActualVelocity, local_sh.motorVal1[index].AMK_Current,
                           local_sh.motorVal1[index].AMK_MagnetizingCurrent, local_sh.motorVal1[index].AMK_TorqueCurrent,
                           local_sh.motorVal1[index].AMK_bDcOn, local_sh.motorVal1[index].AMK_bDerating,
                           local_sh.motorVal1[index].AMK_bError, local_sh.motorVal1[index].AMK_bInverterOn,
                           local_sh.motorVal1[index].AMK_bQuitDcOn, local_sh.motorVal1[index].AMK_bQuitInverterOn,
                           local_sh.motorVal1[index].AMK_bSystemReady, local_sh.motorVal1[index].AMK_bWarn,


                           local_sh.motorVal2[index].AMK_ErrorInfo, local_sh.motorVal2[index].AMK_TempIGBT,
                           local_sh.motorVal2[index].AMK_TempInverter, local_sh.motorVal2[index].AMK_TempMotor,


                           local_sh.motorSetP[index].AMK_bInverterOn, local_sh.motorSetP[index].AMK_bDcOn,
                           local_sh.motorSetP[index].AMK_bEnable, local_sh.motorSetP[index].AMK_bErrorReset,
                           local_sh.motorSetP[index].AMK_TargetVelocity, local_sh.motorSetP[index].AMK_TorqueLimitPositive,
                           local_sh.motorSetP[index].AMK_TorqueLimitNegative);
           writeSD(cmd);
        }


        //TO USE
        sprintf(cmd , "%d %d %d %d %d %d %d %d"     //Temps
                " %d %d %d %d %d %d"                //status
                " %.2f %.2f %.2f %.2f %.2f %.2f"    //bms
                " %.2f %.2f %.2f %.2f"              //sendyne
                " %d %d "                           //fanSpeed
                " %.2f %.2f %.2f %.2f %.2f %.2f "   //imu
                " %d %d %d %d %d %d %d %d\n",       //gpio
                        //Temps
                        local_sh.Temps[0], local_sh.Temps[1], local_sh.Temps[2], local_sh.Temps[3],
                        local_sh.Temps[4], local_sh.Temps[5], local_sh.Temps[6], local_sh.Temps[7],

                        //status
                        local_sh.status.throttle_shared, local_sh.status.steering_shared,
                        local_sh.status.brake_shared, local_sh.status.brakePress_shared,
                        local_sh.status.status_shared, local_sh.status.actualVelocityKMH_shared,

                        //bms
                        local_sh.bms.max_bms_temp_shared, local_sh.bms.min_bms_voltage_shared,
                        local_sh.bms.mean_bms_voltage_shared, local_sh.bms.max_bms_temp_shared,
                        local_sh.bms.min_bms_temp_shared, local_sh.bms.mean_bms_temp_shared,

                        //sendyne
                        local_sh.sendyne.sendyne_voltage_shared, local_sh.sendyne.sendyne_current_shared,
                        local_sh.sendyne.curr_sens_shared, local_sh.sendyne.total_power_shared,

                        //fanSpeed
                        local_sh.fanSpeed.leftFanSpeed_shared, local_sh.fanSpeed.rightFanSpeed_shared,

                        //imu
                        local_sh.imu.accelerations_shared[0], local_sh.imu.accelerations_shared[1],
                        local_sh.imu.accelerations_shared[2], local_sh.imu.omegas_shared[0],
                        local_sh.imu.omegas_shared[1], local_sh.imu.omegas_shared[2],

                        //gpio
                        local_sh.gpio.Bms_shared, local_sh.gpio.Imd_shared,
                        local_sh.gpio.Sdc1_shared, local_sh.gpio.Sdc2_shared,
                        local_sh.gpio.Sdc3_shared, local_sh.gpio.Sdc4_shared,
                        local_sh.gpio.Sdc5_shared, local_sh.gpio.Sdc6_shared);
        writeSD(cmd);

        //EALLOW;
//        CpuTimer1.InterruptCount++;
//        //GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        //GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
        //EDIS;

}

//not necessary at the moment
__interrupt void cpu_timer2_isr(void)
{
    updatePage(display.page);
//    setAck();
//    setSelector();
//    display.page++;
//    display.selector++;
//    display.page = display.page % 9;
//    display.selector = display.selector % 8;
//    if(display.selector == sel){
//        display.ack = display.selector;
//        display.ack = display.ack % 8;
//        sel = sel + 2;
//        sel = sel % 8;
//    }

}



