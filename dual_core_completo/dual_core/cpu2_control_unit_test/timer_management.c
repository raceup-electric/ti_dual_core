#include "timer_management.h"


void timerSetup()
{
    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
       EALLOW;  // This is needed to write to EALLOW protected registers
       PieVectTable.TIMER0_INT = &cpu_timer0_isr;
       PieVectTable.TIMER1_INT = &cpu_timer1_isr;
       PieVectTable.TIMER2_INT = &cpu_timer2_isr;
       EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize the Device Peripheral. This function can be
    //         found in F2837xD_CpuTimers.c
    //
       InitCpuTimers();   // For this example, only initialize the Cpu Timers

    //
    // Configure CPU-Timer 0 to __interrupt every m milliseconds:
    // 200MHz CPU Freq, millisecond Period (in uSeconds)
    //
       ConfigCpuTimer(&CpuTimer0, 200, 10000);
       ConfigCpuTimer(&CpuTimer1, 200, 10000);
       ConfigCpuTimer(&CpuTimer2, 200, 100000);

    //
    // To ensure precise timing, use write-only instructions to write to the entire
    // register. Therefore, if any of the configuration bits are changed in
    // ConfigCpuTimer and InitCpuTimers (in F2837xD_cputimervars.h), the below
    // settings must also be updated.
    //
       CpuTimer0Regs.TCR.all = 0x4000;
       CpuTimer1Regs.TCR.all = 0x4000;
       CpuTimer2Regs.TCR.all = 0x4000;

       //
       // Enable CPU INT
       //
          IER |= M_INT1;  //timer0
          IER |= M_INT13;   //timer1
          IER |= M_INT14;   //timer2

       //
       // Enable TINT0 in the PIE: Group 1 __interrupt 7
       //
          PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

       CpuTimer2Regs.TCR.bit.TSS = 1;   //Stop timer R2D
       CpuTimer1Regs.TCR.bit.TSS = 1;
}

// timer 0 - blink
__interrupt void cpu_timer0_isr(void){
    if(CpuTimer0.InterruptCount % 50 == 0){
        EALLOW;
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
        EDIS;
    }
    CpuTimer0.InterruptCount++;

    time_elapsed++;
    //time_elapsed_ATC++;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

// timer 1 - main timer (ex timer0)
__interrupt void cpu_timer1_isr(void)
{
    CpuTimer1.InterruptCount++;

    readAllADC();
    brakeLight();
    readVelocity();

    if(time_elapsed%(40 MS) == 0){
        sendHostData();
    }

    if(time_elapsed%(500 MS) == 0){
        pumpFanControl();  // start only in R2D

        checkStatus();
        send_car_status();

        carSettingsMessage();
        send_car_settings();
    }

    updateGPIOState();

    updateTVstruct();
    Torque_Vectoring_2024_forsecontiu_step();


#ifndef DEBUG_NO_HV
    /*
     * Every cycle is verified if we can trigger R2D
     */
    checkHV();
    checkRF();
    R2D_init();
#endif

    if (time_elapsed - time_elapsed_map > 20000 MS) {
        setup_car_settings();
    }

    if (time_elapsed - time_elapsed_paddle > 500 MS) {
        paddle = 0;
    }

    paddleControl(time_elapsed);

    bool canSendAMK = R2D_state && readRF() && isHVOn();
    
    if (!imp && canSendAMK && ((time_elapsed - time_elapsed_ATC) < 500 MS)) {
        if(paddle > 0) {
            brakeAMK(paddle);
        }
        else if(throttle > 0) {
            throttleAMK(throttle);
        }
        else {
            stopAMK();
        }
    }
    else {
        stopAMK();
    }


    if(time_elapsed - time_elapsed_ATC >= 500 MS) {
        GPIO_WritePin(SCS, SCS_OFF);
    }


    sendAMKData();

    computeBatteryPackTension();
    sendDataToLogger();
}

// timer 2 - for R2D sound
__interrupt void cpu_timer2_isr(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    CpuTimer2.InterruptCount++;


    if (CpuTimer2.InterruptCount == RTDS_DURATION)
    {
        GPIO_WritePin(RTDS, 0);
        CpuTimer2Regs.TCR.bit.TSS = 1;  //stop timer
    }
}
