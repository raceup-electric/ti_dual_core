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


    setupSD();
    //creates first file for logging
    createFirstFile();
    //writes the first line of log
    writeHeader();


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

    CpuTimer1Regs.TCR.bit.TSS = 0;      //Start SD timer

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

/*
 * Timer1 integrates all features: logging, display and LoRa
 *      - Logging is active every cycle.
 *      - Display updates every 5 cycles.
 *      - LoRa is active every cycle, but LoRa code is alternated to
 *        logging code, to give receiving buffer time to flush
 * if MORE_FILES function is active, a new log file will be
 * created periodically. This is a safer configuration if log files are
 * corrupted because of critical situations.
 */
__interrupt void cpu_timer1_isr(void)
{
        CpuTimer1.InterruptCount++;


        Shared_Ram_dataRead_c1();
#ifdef LOGGING
        char cmd[200];

        sprintf(cmd, "%lu;", local_time_elapsed);
        writeSD(cmd);

        compute_AMKStatus();

        sprintf(cmd, "%d;%d;%d;%d;"  //AMKStatus
                "%.2f;%u;%.2f;%.2f;"   //MotorVal2
                "%.2f;%u;%.2f;%.2f;"
                "%.2f;%u;%.2f;%.2f;"
                "%.2f;%u;%.2f;%.2f;",
                (int)AmkStatus[0], (int)AmkStatus[1], (int)AmkStatus[2], (int)AmkStatus[3],

                local_sh.motorVal2[0].AMK_TempMotor, local_sh.motorVal2[0].AMK_ErrorInfo,
                local_sh.motorVal2[0].AMK_TempIGBT, local_sh.motorVal2[0].AMK_TempInverter,
                local_sh.motorVal2[1].AMK_TempMotor, local_sh.motorVal2[1].AMK_ErrorInfo,
                local_sh.motorVal2[1].AMK_TempIGBT, local_sh.motorVal2[1].AMK_TempInverter,
                local_sh.motorVal2[2].AMK_TempMotor, local_sh.motorVal2[2].AMK_ErrorInfo,
                local_sh.motorVal2[2].AMK_TempIGBT, local_sh.motorVal2[2].AMK_TempInverter,
                local_sh.motorVal2[3].AMK_TempMotor, local_sh.motorVal2[3].AMK_ErrorInfo,
                local_sh.motorVal2[3].AMK_TempIGBT, local_sh.motorVal2[3].AMK_TempInverter
        );

        writeSD(cmd);

        //TO USE
        sprintf(cmd , "%.1f;%.1f;%.1f;%.1f;"  //Actual velocity
                      "%d;%d;%d;%d;" //MotorSetPoints positive
                      "%d;%d;%d;%d;", //MotorSetPoints negative
                        local_sh.motorVal1[0].AMK_ActualVelocity,local_sh.motorVal1[1].AMK_ActualVelocity,
                        local_sh.motorVal1[2].AMK_ActualVelocity,local_sh.motorVal1[3].AMK_ActualVelocity,

                        local_sh.motorSetP[0].AMK_TorqueLimitPositive,local_sh.motorSetP[1].AMK_TorqueLimitPositive,
                        local_sh.motorSetP[2].AMK_TorqueLimitPositive,local_sh.motorSetP[3].AMK_TorqueLimitPositive,

                        local_sh.motorSetP[0].AMK_TorqueLimitNegative,local_sh.motorSetP[1].AMK_TorqueLimitNegative,
                        local_sh.motorSetP[2].AMK_TorqueLimitNegative,local_sh.motorSetP[3].AMK_TorqueLimitNegative
                        );
        writeSD(cmd);

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

        scic_msg(encoded);

        sprintf(cmd ,
                        "%d;%d;%d;%d;%lu;%d;%d;%d;"                //status
                        "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%u;"    //bms
                        "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;"    //bms_lv
                        "%.1f;%.3f;%.2f;%.2f;",              //sendyne
                        //status
                        local_sh.status.throttle_shared, local_sh.status.steering_shared,
                        local_sh.status.brake_shared, local_sh.status.brakePress_shared,
                        local_sh.status.status_shared, local_sh.status.actualVelocityKMH_shared,
                        local_sh.pedals.brk_req_shared, local_sh.pedals.throttle_req_shared,
                        //bms
                        local_sh.bms.max_bms_voltage_shared, local_sh.bms.min_bms_voltage_shared,
                        local_sh.bms.mean_bms_voltage_shared, local_sh.bms.max_bms_temp_shared,
                        local_sh.bms.min_bms_temp_shared, local_sh.bms.mean_bms_temp_shared,
                        local_sh.bms.bms_bitmap_shared,
                        //bms_lv
                        local_sh.bms_lv[0], local_sh.bms_lv[1], local_sh.bms_lv[2],
                        local_sh.bms_lv[3], local_sh.bms_lv[4], local_sh.bms_lv[5],
                        local_sh.bms_lv[6], local_sh.bms_lv[7],
                        //power
                        local_sh.power.batteryPack_voltage_shared, local_sh.power.lem_current_shared,
                        local_sh.power.curr_sens_shared, local_sh.power.total_power_shared);
        writeSD(cmd);

        sprintf(cmd ,
                "%u;%u;"                           //fanSpeed
                "%.4f;%.4f;%.4f;%.4f;%.4f;%.4f;"   //imu
                "%.1f;%.1f;%.1f;%.1f;",            //suspensions

                        //fanSpeed
                        local_sh.fanSpeed.leftFanSpeed_shared, local_sh.fanSpeed.rightFanSpeed_shared,
                        //imu
                        local_sh.imu.accelerations_shared[0], local_sh.imu.accelerations_shared[1],
                        local_sh.imu.accelerations_shared[2], local_sh.imu.omegas_shared[0],
                        local_sh.imu.omegas_shared[1], local_sh.imu.omegas_shared[2],
                        //potenziometri sospensioni FL-FR-RL-RR
                        local_sh.imu.suspensions_shared[0], local_sh.imu.suspensions_shared[1],
                        local_sh.imu.suspensions_shared[2], local_sh.imu.suspensions_shared[3]);
        writeSD(cmd);

        sprintf(cmd ,
                "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;"        //temperatures per cooling
                "%d;%d;%d;%d;%d;%d\n",

                        //temperature per cooling
                        local_sh.imu.temperatures_shared[0], local_sh.imu.temperatures_shared[1],
                        local_sh.imu.temperatures_shared[2], local_sh.imu.temperatures_shared[3],
                        local_sh.imu.temperatures_shared[4], local_sh.imu.temperatures_shared[5],
                        local_sh.imu.temperatures_shared[6], local_sh.imu.temperatures_shared[7],
                        //gpio
                        local_sh.gpio.Bms_shared, local_sh.gpio.Imd_shared,
                        local_sh.bms.max_bms_temp_nslave_shared,
                        (int)local_sh.pedals.acc_pot1_shared,(int)local_sh.pedals.acc_pot2_shared,(int)local_sh.pedals.brk_pot_shared);
        writeSD(cmd);


#ifdef MORE_FILES
        if(CpuTimer1.InterruptCount % 2000 == 0 && CpuTimer1.InterruptCount != 0)
        {
            //DA TESTARE SE USARE O MENO
            newSetupSD();
            createFile();
            writeHeader();

        }
#endif
#endif
        if(CpuTimer1.InterruptCount % 5 == 0)
        {
            /*if(display.emergencyBrk_active){
                if(display.emergencyBrk_isNotSet){
                    scic_msg("page 18ÿÿÿ\0");
                    display.emergencyBrk_isNotSet = 0;
                }
            }else{*/
                EALLOW;
                GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
                updatePage(display.page);
                updateValues();
                display.emergencyBrk_isNotSet = 1;
                EDIS;
          // }
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




