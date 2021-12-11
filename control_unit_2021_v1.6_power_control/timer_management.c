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
    // ISRs for each CPU Timer interrupt
    //
    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);
    Interrupt_register(INT_TIMER1, &cpuTimer1ISR);
    Interrupt_register(INT_TIMER2, &cpuTimer2ISR);

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    initCPUTimers();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 1 second Period (in uSeconds)
    //
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 10000);
    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 100000);
    configCPUTimer(CPUTIMER2_BASE, DEVICE_SYSCLK_FREQ, 5000000);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);
    CPUTimer_enableInterrupt(CPUTIMER2_BASE);

    //
    // Enables CPU int1, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    Interrupt_enable(INT_TIMER0);
    Interrupt_enable(INT_TIMER1);
    Interrupt_enable(INT_TIMER2);

    //
    // Starts CPU-Timer 0, CPU-Timer 1, and CPU-Timer 2.
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);
    CPUTimer_startTimer(CPUTIMER1_BASE);
    CPUTimer_startTimer(CPUTIMER2_BASE);

    CPUTimer_stopTimer(CPUTIMER1_BASE); //lo fermo, per il momento non ci serve
    CPUTimer_stopTimer(CPUTIMER2_BASE); //lo fermo, per il momento non ci serve

}

void initCPUTimers(void)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_stopTimer(CPUTIMER2_BASE);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);

    //
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;
}

void configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (cpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER1_BASE)
    {
        cpuTimer1IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER2_BASE)
    {
        cpuTimer2IntCount = 0;
    }
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
__interrupt void
cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;
    readThrottleBrakeSteering();
    brakeLight();
    readVelocity();
    fanControl();
    checkTemps();


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
//    GPIO_writePin(POMPA_SX_Abil, pompa_sx_on_off);
    GPIO_writePin(VENTOLA_Abil, ventola_on_off);

//    GPIO_writePin(POMPA_DX_Abil, pompa_dx_on_off);
//    GPIO_writePin(SCS_FAULT, scs_on_off);


#endif

#ifdef TSAL_CTRL
    //----------------------------------------------------------------------------------
    //Tramacci TSAL
    if (!GPIO_readPin(AIR_1_STATE) || !GPIO_readPin(AIR_2_STATE) || sendyne_voltage > 60)
    {
        GPIO_writePin(11, 1U);
        CPUTimer_startTimer(CPUTIMER2_BASE);

    }
    else
    {
        GPIO_writePin(11, 0);
        CPUTimer_stopTimer(CPUTIMER2_BASE);
        GPIO_writePin(14, 0);
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

    uint8_t i = 0;
    for (i = 0; i <8; i++){
        Temps[i] = var;
    }

    stat.throttle = var;
    motorVal1[0].AMK_ActualVelocity = var%10;
    var++;



    dts.s = stat;
    i = 0;
    for (i = 0; i < 4; i++)
    {
        dts.motorValues1[i] = motorVal1[i];
        dts.motorValues2[i] = motorVal2[i];
        dts.motorSetPoints[i] = motorSetP[i];
    }
    memcpy(dts.temps, Temps, 8);


    sendAMKData();
    checkStatus();
    sendDataToLogger();
    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
//TIMER FOR R2DS
__interrupt void
cpuTimer1ISR(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer1IntCount++;

    if (cpuTimer1IntCount == RTDS_DURATION)
    {
        GPIO_writePin(RTDS, 0U);
        CPUTimer_stopTimer(CPUTIMER1_BASE);
    }

}

//
// cpuTimer2ISR - Counter for CpuTimer2
//
__interrupt void
cpuTimer2ISR(void)
{

    //
    // The CPU acknowledges the interrupt.
    //
#ifdef TSAL_CTRL
    GPIO_togglePin(14);
#endif
    cpuTimer2IntCount++;
}
