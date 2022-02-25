
#include "timer_management.h"

#if defined(DEBUG_NO_HV) || defined(DEBUG_HV)

// variabili per debug
int ventola_sx_epwm = 0;
int ventola_dx_epwm = 0;
int pompa_dx_epwm = 0;
int pompa_sx_epwm = 0;
int debug_acc_brake = 0;

uint32_t pompa_sx_on_off = 0;
uint32_t pompa_dx_on_off = 0;
uint32_t ventola_on_off = 0;

uint32_t scs_on_off = 0;


float adc_values_debug[15];
uint16_t acc_brake_debug[3];
uint16_t dac_debug = 0;

int simulate_throttle = 0;

#endif


void timerSetup()
{
    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
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
    // Configure CPU-Timer 0 to __interrupt every 500 milliseconds:
    // 60MHz CPU Freq, 50 millisecond Period (in uSeconds)
    //
       //ConfigCpuTimer(&CpuTimer0, 200, 500000);
       ConfigCpuTimer(&CpuTimer1, 200, 10000);
       ConfigCpuTimer(&CpuTimer2, 200, 200000);

    //
    // To ensure precise timing, use write-only instructions to write to the entire
    // register. Therefore, if any of the configuration bits are changed in
    // ConfigCpuTimer and InitCpuTimers (in F2837xD_cputimervars.h), the below
    // settings must also be updated.
    //
       //CpuTimer0Regs.TCR.all = 0x4000;
       CpuTimer1Regs.TCR.all = 0x4000;
       CpuTimer2Regs.TCR.all = 0x4000;

       //
       // Enable CPU INT
       //
          //IER |= M_INT1;  //timer0
          IER |= M_INT13;   //timer1
          IER |= M_INT14;   //timer2

       //
       // Enable TINT0 in the PIE: Group 1 __interrupt 7
       //
          PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

       CpuTimer2Regs.TCR.bit.TSS = 1;   //Stop timer R2D
       CpuTimer1Regs.TCR.bit.TSS = 1;
}

//
// cpu_timer1_isr - main timer (ex timer0)
//
__interrupt void cpu_timer1_isr(void)
{
    CpuTimer1.InterruptCount++;

    readAllADC();

    readThrottleBrakeSteering();    //rewrite
    brakeLight();
    readVelocity();
    fanControl();
    checkTemps();                   //rewrite


#ifndef DEBUG_NO_HV
    checkHV();
    checkRF();
    R2D_init();
#endif

    debugLight(20);

#if defined(DEBUG_NO_HV) || defined(DEBUG_HV)

    //debug adc
    int i;
    for(i=0; i<15; i++){
        adc_values_debug[i]=getVoltage(readADC(i));
    }


    //debug acc1 acc2 brake
//    acc_brake_debug[0]=readADC(ACC_1);
//    acc_brake_debug[1]=readADC(ACC_2);
//    acc_brake_debug[2]=readADC(BRAKE_CLEAN);


    //debug DAC
    //setDACValue(dac_debug);

    //debug epwm
//    setFanSpeed(VENTOLA_SX, ventola_sx_epwm);
//    setFanSpeed(VENTOLA_DX, ventola_dx_epwm);
//
//    //debug epwm
//    setPumpSpeed(POMPA_SX, pompa_sx_epwm);
//    setPumpSpeed(POMPA_DX, pompa_dx_epwm);
//
//
//    //debug gpio
//    GPIO_WritePin(POMPA_SX_Abil, pompa_sx_on_off);
    GPIO_WritePin(VENTOLA_Abil, ventola_on_off);

//    GPIO_WritePin(POMPA_DX_Abil, pompa_dx_on_off);
//    GPIO_WritePin(SCS_FAULT, scs_on_off);


#endif

#ifdef TSAL_CTRL
    //----------------------------------------------------------------------------------
    //Tramacci TSAL
    if (!GPIO_readPin(AIR_1_STATE) || !GPIO_readPin(AIR_2_STATE) || sendyne_voltage > 60)
    {
        GPIO_WritePin(11, 1U);
        CPUTimer_startTimer(CPUTIMER2_BASE);

    }
    else
    {
        GPIO_WritePin(11, 0);
        CPUTimer_stopTimer(CPUTIMER2_BASE);
        GPIO_WritePin(14, 0);
    }
    //----------------------------------------------------------------------------------
#endif

    bool canSendAMK = R2D_state && readRF() && isHVOn();


#ifdef DEBUG_NO_HV  //for debug purposes with no inverter and no HV > HV ON is simulated by ECU
    canSendAMK = true; //debug
#endif

    if(canSendAMK)
    {

        bool brakeWhenSlow = brake > 10 && actualVelocityKMH <= 5;
        bool brakeReg = brake > 10 && brake < REGENERATIVE_BRAKE_LIMIT && actualVelocityKMH > 5;
        bool brakeMec = brake >= REGENERATIVE_BRAKE_LIMIT && actualVelocityKMH > 5;
        bool noBrake = brake <= 10;
        checkImplausibility();

        if (implBrakeAndThrottle || brk_disconnected)
        {
            stopAMK();
        }
        else if(brakeWhenSlow)
        {
            stopAMK();
        }
        else if(brakeReg)
        {
#ifdef NO_REG_BRAKE
            stopAMK();
#else
            //brakeAMK(brake * (NEGATIVE_TORQUE_LIMIT /10));
            if(sendyne_current > MAX_REGEN_CURRENT){
                brakeAMK(brake);
            }
            else {
                stopAMK();
            }
#endif
        }
        else if(brakeMec)
        {
#ifdef NO_REG_BRAKE
            stopAMK();
#else
            //brakeAMK((REGENERATIVE_BRAKE_LIMIT - (brake - REGENERATIVE_BRAKE_LIMIT) * (REGENERATIVE_BRAKE_LIMIT)/(100-REGENERATIVE_BRAKE_LIMIT)) * (NEGATIVE_TORQUE_LIMIT /10));
            if(sendyne_current > MAX_REGEN_CURRENT){
                brakeAMK(brake);
            }
            else {
                stopAMK();
            }
#endif
        }
        else if(noBrake)
        {
            //throttleAMK(throttle * THROTTLE_POWER_SCALE);
            throttleAMK(throttle);
        }
        else
        {
            stopAMK();
        }
    }
    else
    {
        stopAMK();
    }

    sendAMKData();
    checkStatus();
    sendDataToLogger();


//    char cmd[250] = "\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
//           //    CmdLineProcess(cmd);
//    writeSD(cmd);

//    char gmd[200] = "\n banan banan banan banan banan banan banan banan banan \n kapok kapok kapok kapok kapok kapok kapok kapok kapok\n";
//
//    writeSD(gmd);
//    int j = 0;
//    while (j < 8)
//    {
//        TXB_Setpoints_Data[1][j] = 0x60;
//        j++;
//    }
//
//    CANMessageSet(CANB_BASE, (14 + 1), &TXCANB_Setpoints_Message[1], MSG_OBJ_TYPE_TX);

    //GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

}



//
// cpu_timer2_isr - for R2D sound
//
__interrupt void cpu_timer2_isr(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    CpuTimer2.InterruptCount++;

    if (CpuTimer2.InterruptCount == RTDS_DURATION)
    {
        GPIO_WritePin(31, 1);
        GPIO_WritePin(RTDS, 0);
        CpuTimer2Regs.TCR.bit.TSS = 1;  //stop timer
    }
}
