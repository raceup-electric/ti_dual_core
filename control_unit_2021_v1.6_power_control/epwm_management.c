#include "epwm_management.h"


void epwmSetup()
{

    //
    // Configure GPIO0/1 and GPIO2/3 as ePWM1A/1B and ePWM2A/2B
    // pins respectively
    //
    GPIO_setPadConfig(6, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_6_EPWM4A);

    GPIO_setPadConfig(7, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_7_EPWM4B);

    GPIO_setPadConfig(8, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_8_EPWM5A);

    GPIO_setPadConfig(9, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_9_EPWM5B);

    GPIO_setPadConfig(10, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_10_EPWM6A);

    GPIO_setPadConfig(11, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_11_EPWM6B);
    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initEPWM(EPWM4_BASE);
    initEPWM(EPWM5_BASE);
    initEPWM(EPWM6_BASE);


    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

}


//
// initEPWM4 - Configure ePWM4
//
void initEPWM(uint32_t base)
{

    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(base, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(base, 0U);
    EPWM_setTimeBaseCounter(base, 0U);
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP_DOWN); // ->center-aligned pwm o pwm simmetrica
    EPWM_disablePhaseShiftLoad(base);
    EPWM_setClockPrescaler(base, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    //
    // Set up shadowing
    // I duty-cycles vengono aggiornati solo quando il timer del pwm passa per lo zero
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set-up compare
    //

    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_A, convertPercent(0));
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B, convertPercent(0));

    //
    // Set actions
    //
    /*EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);*/
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    /*EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_NO_CHANGE,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);*/
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);


    /*EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);*/
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    /*EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_NO_CHANGE,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);*/
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

}

void setDutyCycle(uint32_t base, uint16_t module, int perc)
{
    if (module == A)
        EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_A, convertPercent(perc));
    else
        EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B, convertPercent(perc));
}

uint16_t convertPercent(int perc)
{
    perc = 100 - perc;  //LOGICA INVERTITA --- Commentare la linea se la logica non è invertita
    perc *= (EPWM_TIMER_TBPRD/100);
    if (perc == EPWM_TIMER_TBPRD)
        return 1;

    return EPWM_TIMER_TBPRD - perc;
}

void setFanSpeed(int fan, int speed){
    switch(fan){
    case VENTOLA_SX:
        setDutyCycle(EPWM5_BASE,B,speed);
    break;
    case VENTOLA_DX:
        setDutyCycle(EPWM6_BASE,A,speed);
    break;
    }
}

void setPumpSpeed(int pump, int speed){
    switch(pump){
    case POMPA_SX:
        setDutyCycle(EPWM5_BASE,A,speed);
    break;
    case POMPA_DX:
        setDutyCycle(EPWM4_BASE,B,speed);
    break;
    }
}
