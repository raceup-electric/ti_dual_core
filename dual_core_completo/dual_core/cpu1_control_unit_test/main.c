#include "main.h"


int LoRa_Packet_Counter = 0;

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

#ifndef NO_LORA

    GPIO_LoRa_Setup();
    LoRa_begin(LORA_DEFAULT_SPI_FREQUENCY);
#endif


    while( !(
            MemCfgRegs.GSxMSEL.bit.MSEL_GS3 &
            MemCfgRegs.GSxMSEL.bit.MSEL_GS2 &
             MemCfgRegs.GSxMSEL.bit.MSEL_GS1))
    {
        EALLOW;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS3 = 1;
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
    char str_init[200];
    sprintf(str_init , "timestamp;AmkStatusFL;AmkStatusFR;AmkStatusRL;AmkStatusRR;TempMotor;ErrorInfo;TempIGBT;TempInverter;TempMotor;");
    writeSD(str_init);
    sprintf(str_init , "ErrorInfo;TempIGBT;TempInverter;TempMotor;ErrorInfo;TempIGBT;TempInverter;TempMotor;ErrorInfo;TempIGBT;TempInverter;");
    writeSD(str_init);
    sprintf(str_init , "ActualVelocityFL;ActualVelocityFR;ActualVelocityRL;ActualVelocityRR;TorqueLimitPositiveFL;TorqueLimitPositiveFR;");
    writeSD(str_init);
    sprintf(str_init , "TorqueLimitPositiveRL;TorqueLimitPositiveRR;TorqueLimitNegativeFL;TorqueLimitNegativeFR;TorqueLimitNegativeRL;");
    writeSD(str_init);
    sprintf(str_init , "TorqueLimitNegativeRR;throttle;steering angle;brake;brake_press;status;actualVelocityKMH;max voltage;min voltage;");
    writeSD(str_init);
    sprintf(str_init , "avg voltage;max temp;min temp;avg temp;bms_lv[0];bms_lv[1];bms_lv[2];bms_lv[3];bms_lv[4];bms_lv[5];bms_lv[6];bms_lv[7];");
    writeSD(str_init);
    sprintf(str_init , "Car voltage;Lem current;current sensor;total power;acceleration x;acceleration y;acceleration z;omega x;omega y;omega z;");
    writeSD(str_init);
    sprintf(str_init , "SuspensionsFL;SuspensionsFR;SuspensionsRL;SuspensionsRR;temp pre rad;temp pre cold;temp post cold;temp pre mot;temp post mot;");
    writeSD(str_init);
    sprintf(str_init , "Gpio bms;Gpio imd;Gpio sdc 1;Gpio sdc 2;Gpio sdc 3;Gpio sdc 4;Gpio sdc 5;Gpio sdc 6\n");
    writeSD(str_init);

#ifdef LORA_DEBUG
    debugSet();
    CpuTimer1Regs.TCR.bit.TSS = 1;      //Do not start timer 1 (SD) in LORA_DEBUG
#else
    CpuTimer1Regs.TCR.bit.TSS = 0;      //Start SD timer
#endif

          //start timer1
    CpuTimer2Regs.TCR.bit.TSS = 1;        //Start timer 2



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
    ConfigCpuTimer(&CpuTimer2, 200, 150000);

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
        CpuTimer1.InterruptCount++;


        Shared_Ram_dataRead_c1();
#ifdef LOGGING
        char cmd[200];

        sprintf(cmd, "%d;", (int)local_time_elapsed);
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

        sprintf(cmd ,
                        "%d;%d;%d;%d;%d;%d;"                //status
                        "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;"    //bms
                        "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;"    //bms_lv
                        "%.1f;%.3f;%.2f;%.2f;",              //sendyne
                        //status
                        local_sh.status.throttle_shared, local_sh.status.steering_shared,
                        local_sh.status.brake_shared, local_sh.status.brakePress_shared,
                        local_sh.status.status_shared, local_sh.status.actualVelocityKMH_shared,
                        //bms
                        local_sh.bms.max_bms_voltage_shared, local_sh.bms.min_bms_voltage_shared,
                        local_sh.bms.mean_bms_voltage_shared, local_sh.bms.max_bms_temp_shared,
                        local_sh.bms.min_bms_temp_shared, local_sh.bms.mean_bms_temp_shared,
                        //bms_lv
                        local_sh.bms_lv[0], local_sh.bms_lv[1], local_sh.bms_lv[2],
                        local_sh.bms_lv[3], local_sh.bms_lv[4], local_sh.bms_lv[5],
                        local_sh.bms_lv[6], local_sh.bms_lv[7],
                        //power
                        local_sh.power.batteryPack_voltage_shared, local_sh.power.lem_current_shared,
                        local_sh.power.curr_sens_shared, local_sh.power.total_power_shared);
        writeSD(cmd);

        sprintf(cmd ,
//                "%d;%d;"                           //fanSpeed
                "%.4f;%.4f;%.4f;%.4f;%.4f;%.4f;"   //imu
                "%.1f;%.1f;%.1f;%.1f;"                   //suspensions
                "%.1f;%.1f;%.1f;%.1f;%.1f;"        //temperatures per cooling
                "%d;%d;%d;%d;%d;%d;%d;%d\n",

//                        //fanSpeed
//                        local_sh.fanSpeed.leftFanSpeed_shared, local_sh.fanSpeed.rightFanSpeed_shared,
                        //imu
                        local_sh.imu.accelerations_shared[0], local_sh.imu.accelerations_shared[1],
                        local_sh.imu.accelerations_shared[2], local_sh.imu.omegas_shared[0],
                        local_sh.imu.omegas_shared[1], local_sh.imu.omegas_shared[2],
                        //potenziometri sospensioni FL-FR-RL-RR
                        local_sh.imu.suspensions_shared[0], local_sh.imu.suspensions_shared[1],
                        local_sh.imu.suspensions_shared[2], local_sh.imu.suspensions_shared[3],
                        //temperature per cooling
                        local_sh.imu.temperatures_shared[0], local_sh.imu.temperatures_shared[1],
                        local_sh.imu.temperatures_shared[2], local_sh.imu.temperatures_shared[3],
                        local_sh.imu.temperatures_shared[4],
                        //gpio
                        local_sh.gpio.Bms_shared, local_sh.gpio.Imd_shared,
                        local_sh.gpio.Sdc1_shared, local_sh.gpio.Sdc2_shared,
                        local_sh.gpio.Sdc3_shared, local_sh.gpio.Sdc4_shared,
                        local_sh.gpio.Sdc5_shared, local_sh.gpio.Sdc6_shared);
        writeSD(cmd);


#endif
        if(CpuTimer1.InterruptCount % 5 == 0)
        {
            EALLOW;
            GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
            updatePage(display.page);
            updateValues();
            //GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
            EDIS;
        }
}

//not necessary at the moment
__interrupt void cpu_timer2_isr(void)
{
#ifdef DISPLAY
    updatePage(display.page);
    updateValues();
    //updatePage(display.page);
    //updateValues();
//    var_v++;
//    var_v = var_v % 9;
//    setAck();
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
#endif
#ifndef NO_LORA
    if(LoRa_Packet_Counter == 0){
        send_Motors();
        LoRa_Packet_Counter++;
    }else{
        send_Status_Imu_BMS_Sendyne();
        LoRa_Packet_Counter--;
    }

#endif

}

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




