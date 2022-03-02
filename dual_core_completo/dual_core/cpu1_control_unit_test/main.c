#include "main.h"

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

#ifdef _STANDALONE
#ifdef _FLASH
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

//
// Step 2. Initialize GPIO:
//
    InitGpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();


//
// Give Memory Access to GS0/ GS14 SARAM to CPU02
//


//
//  Copy ISR routine to a specified RAM location to determine the size
//
    //memcpy(&isrfuncRunStart, &isrfuncLoadStart, (uint32_t)&isrfuncLoadSize);

    cpu1_timer_setup();

    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;
//
// Enable global Interrupts and higher priority real-time debug events:
//
    GPIOSetup();
    setupSD();

    while( !(MemCfgRegs.GSxMSEL.bit.MSEL_GS2 &
             MemCfgRegs.GSxMSEL.bit.MSEL_GS1))
    {
        EALLOW;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS2 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS1 = 1;
        EDIS;
    }

    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM



    InitEPwm4Gpio();
    InitEPwm5Gpio();
    InitEPwm6Gpio();

//
// Transfer ownership of EPWMs and ADCs
//
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

    CpuTimer1Regs.TCR.bit.TSS = 0;          //start timer1
    //CpuTimer2Regs.TCR.bit.TSS = 0;        //do not start timer2



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
    EALLOW;  // This is needed to write to EALLOW protected registers
    //PieVectTable.TIMER0_INT = &cpu_timer0_isr;
    PieVectTable.TIMER1_INT = &cpu_timer1_isr;
    PieVectTable.TIMER2_INT = &cpu_timer2_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripheral. This function can be
//         found in F2837xD_CpuTimers.c
//
    InitCpuTimers();   // For this example, only initialize the Cpu Timers

//
// Configure CPU-Timer0 to interrupt every second:
// c2_FREQ in MHz, 10 millisecond Period (in uSeconds)
//
    //ConfigCpuTimer(&CpuTimer0, 200, 100000);
    ConfigCpuTimer(&CpuTimer1, 200, 10000);
    ConfigCpuTimer(&CpuTimer2, 200, 20000);

//
// To ensure precise timing, use write-only instructions to write to the
// entire register.
//
    CpuTimer1Regs.TCR.all = 0x4000;
    CpuTimer2Regs.TCR.all = 0x4000;

//
// Enable CPU int1 which is connected to CPU-Timer 0
//
//    IER |= M_INT1;
    IER |= M_INT13;   //timer1
    IER |= M_INT14;   //timer2
//
////
//// Enable TINT0 in the PIE: Group 1 interrupt 7
////
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

    //memcpy(local_buf, c1_r_w_array, sizeof(local_buf));
    local_sh = sh;
    local_time_elapsed = time_elapsed;
    //memcpy(&local_sh, &sh, 256);
}

__interrupt void cpu_timer1_isr(void)
{
        //setupSD();
        EALLOW;
        CpuTimer1.InterruptCount++;
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
        EDIS;

        Shared_Ram_dataRead_c1();

        //char cmd[250] = "\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        //    CmdLineProcess(cmd);

        char cmd[200];
        int index;

        sprintf(cmd, "timestamp %d stop", (int)local_time_elapsed);
        writeSD(cmd);

        for(index = 0; index < 4; index++)
        {
           //TO USE
           sprintf(cmd , "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
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

        //cmd = "ls";
        //deb = CmdLineProcess(cmd);



        /*for(index = 0; index < 4; index++)
        {
           //AMKVAL1 TO DECIDE
            EALLOW;
//            CpuTimer1.InterruptCount++;
//            GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
            GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
            EDIS;
           sprintf(cmd , "%d %d %d %d %d %d %d %d %d %d %d %d",
                           local_sh.motorVal1[index].AMK_ActualVelocity, local_sh.motorVal1[index].AMK_Current,
                           local_sh.motorVal1[index].AMK_MagnetizingCurrent, local_sh.motorVal1[index].AMK_TorqueCurrent,
                           local_sh.motorVal1[index].AMK_bDcOn, local_sh.motorVal1[index].AMK_bDerating,
                           local_sh.motorVal1[index].AMK_bError, local_sh.motorVal1[index].AMK_bInverterOn,
                           local_sh.motorVal1[index].AMK_bQuitDcOn, local_sh.motorVal1[index].AMK_bQuitInverterOn,
                           local_sh.motorVal1[index].AMK_bSystemReady, local_sh.motorVal1[index].AMK_bWarn);
           writeSD(cmd);


           //AMKVAL2 TO DECIDE
           sprintf(cmd , "%d %d %d %d",
                           local_sh.motorVal2[index].AMK_ErrorInfo, local_sh.motorVal2[index].AMK_TempIGBT,
                           local_sh.motorVal2[index].AMK_TempInverter, local_sh.motorVal2[index].AMK_TempMotor);
           writeSD(cmd);

           //SETPOINTS TO DECIDE
           sprintf(cmd , "%d %d %d %d %d %d %d",
                           local_sh.motorSetP[index].AMK_bInverterOn, local_sh.motorSetP[index].AMK_bDcOn,
                           local_sh.motorSetP[index].AMK_bEnable, local_sh.motorSetP[index].AMK_bErrorReset,
                           local_sh.motorSetP[index].AMK_TargetVelocity, local_sh.motorSetP[index].AMK_TorqueLimitPositive,
                           local_sh.motorSetP[index].AMK_TorqueLimitNegative);
           writeSD(cmd);
        }*/

//        sprintf(cmd , "%d %d %d %d %d %d %d %d %d %d %d %d %d %d",
//                        local_sh.Temps[0], local_sh.Temps[1], local_sh.Temps[2], local_sh.Temps[3],
//                        local_sh.Temps[4], local_sh.Temps[5], local_sh.Temps[6], local_sh.Temps[7],
//                        local_sh.status.throttle_shared, local_sh.status.steering_shared,
//                        local_sh.status.brake_shared, local_sh.status.brakePress_shared,
//                        local_sh.status.status_shared, local_sh.status.actualVelocityKMH_shared);
//        writeSD(cmd);


//        //TEMPS
//        sprintf(cmd , "%d %d %d %d %d %d %d %d",
//                        local_sh.Temps[0], local_sh.Temps[1], local_sh.Temps[2], local_sh.Temps[3],
//                        local_sh.Temps[4], local_sh.Temps[5], local_sh.Temps[6], local_sh.Temps[7]);
//        writeSD(cmd);
//
//        //STATUS
//        sprintf(cmd , "Status %d %d %d %d %d %d stop ",
//                        local_sh.status.throttle_shared, local_sh.status.steering_shared,
//                        local_sh.status.brake_shared, local_sh.status.brakePress_shared,
//                        local_sh.status.status_shared, local_sh.status.actualVelocityKMH_shared);
//        writeSD(cmd);


        //TO USE
        sprintf(cmd , "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %d %d %.2f %.2f %.2f %.2f %.2f %.2f "
                " %d %d %d %d %d %d %d %d\n",
                        local_sh.Temps[0], local_sh.Temps[1], local_sh.Temps[2], local_sh.Temps[3],
                        local_sh.Temps[4], local_sh.Temps[5], local_sh.Temps[6], local_sh.Temps[7],
                        local_sh.status.throttle_shared, local_sh.status.steering_shared,
                        local_sh.status.brake_shared, local_sh.status.brakePress_shared,
                        local_sh.status.status_shared, local_sh.status.actualVelocityKMH_shared,
                        local_sh.bms.max_bms_temp_shared, local_sh.bms.min_bms_voltage_shared,
                        local_sh.bms.mean_bms_voltage_shared, local_sh.bms.max_bms_temp_shared,
                        local_sh.bms.min_bms_temp_shared, local_sh.bms.mean_bms_temp_shared,
                        local_sh.sendyne.sendyne_voltage_shared, local_sh.sendyne.sendyne_current_shared,
                        local_sh.sendyne.curr_sens_shared, local_sh.sendyne.total_power_shared,
                        local_sh.fanSpeed.leftFanSpeed_shared, local_sh.fanSpeed.rightFanSpeed_shared,
                        local_sh.imu.accelerations_shared[0], local_sh.imu.accelerations_shared[1],
                        local_sh.imu.accelerations_shared[2], local_sh.imu.omegas_shared[0],
                        local_sh.imu.omegas_shared[1], local_sh.imu.omegas_shared[2],
                        local_sh.gpio.Bms_shared, local_sh.gpio.Imd_shared,
                        local_sh.gpio.Sdc1_shared, local_sh.gpio.Sdc2_shared,
                        local_sh.gpio.Sdc3_shared, local_sh.gpio.Sdc4_shared,
                        local_sh.gpio.Sdc5_shared, local_sh.gpio.Sdc6_shared);
        writeSD(cmd);

//        //STATUS
//        sprintf(cmd , "new %d %d %d %d %d %d %d %d",
//                        local_sh.gpio.Bms_shared, local_sh.gpio.Imd_shared,
//                        local_sh.gpio.Sdc1_shared, local_sh.gpio.Sdc2_shared,
//                        local_sh.gpio.Sdc3_shared, local_sh.gpio.Sdc4_shared,
//                        local_sh.gpio.Sdc5_shared, local_sh.gpio.Sdc6_shared);
//        writeSD(cmd);


//        //SENDYNE AND CURRENT
//        sprintf(cmd , "",
//
//        writeSD(cmd);
//
//        //FANSPEED
//        sprintf(cmd , "FanSpeed %d %d stop ",
//
//        writeSD(cmd);
//
//        //IMU
//        sprintf(cmd , "Imu %.2f %.2f %.2f %.2f %.2f %.2f stop \n",
//
//        writeSD(cmd);
//
//        //BMS
//        sprintf(cmd , "%.2f %.2f %.2f %.2f %.2f %.2f",
//
//        writeSD(cmd);


//        //SENDYNE AND CURRENT
//        sprintf(cmd , "%.2f %.2f %.2f %.2f",
//                        local_sh.sendyne.sendyne_voltage_shared, local_sh.sendyne.sendyne_current_shared,
//                        local_sh.sendyne.curr_sens_shared, local_sh.sendyne.total_power_shared);
//        writeSD(cmd);
//
//        //FANSPEED
//        sprintf(cmd , "FanSpeed %d %d stop ",
//                        local_sh.fanSpeed.leftFanSpeed_shared, local_sh.fanSpeed.rightFanSpeed_shared);
//        writeSD(cmd);
//
//        //IMU
//        sprintf(cmd , "Imu %.2f %.2f %.2f %.2f %.2f %.2f stop \n",
//                        local_sh.imu.accelerations_shared[0], local_sh.imu.accelerations_shared[1],
//                        local_sh.imu.accelerations_shared[2], local_sh.imu.omegas_shared[0],
//                        local_sh.imu.omegas_shared[1], local_sh.imu.omegas_shared[2]);
//        writeSD(cmd);


        //char gmd[100] = "testiamo insieme amici del bosco AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";

        //PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
        //EALLOW;
//        CpuTimer1.InterruptCount++;
//        //GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        //GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
        //EDIS;

}

//not necessary at the moment
__interrupt void cpu_timer2_isr(void)
{
//
//    EALLOW;
//    CpuTimer2.InterruptCount++;
//    //GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
//    //GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
//    EDIS;
//
//    Shared_Ram_dataRead_c1();
//
////        char cmd[250] = "\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
////                   //    CmdLineProcess(cmd);
//////        char cmd[100] = "testiamo insieme amici del bosco\n";
////         writeSD(cmd);
//
//    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
////    EALLOW;
////    //GpioDataRegs.GPATOGGLE.bit.GPIO16 = 1;
////    EDIS;
}



