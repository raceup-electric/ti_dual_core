#include "main.h"

volatile int setupOk = 0;
int loopCounter = 0;


void main(void)
{

    #ifdef _FLASH
        memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
    #endif

    setup();
    loop();
}

void setup()
{

    Device_init();
    Device_initGPIO();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();
    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    MemCfg_setGSRAMMasterSel((MEMCFG_SECT_GS0 | MEMCFG_SECT_GS14),
                                 MEMCFG_GSRAMMASTER_CPU2);


    timerSetup();
    canSetup();
    epwmSetup();
    adcSetup();
    GPIOSetup();
    //setupDAC();
    GPIO_writePin(DEVICE_GPIO_PIN_LED2,0U);
    setupOk = 1;    //debug


}


void loop()
{
#ifdef DEBUG_NO_HV
    enableMotor = true; //debug
#endif
    while(true) {
        if(isHVOn()) {
            if(!enableMotor) {
                DEVICE_DELAY_US(10000000);  // wait for precharge
                enableMotor = true;
            }
        } else {
            enableMotor = false;
        }
    loopCounter++; //debug
    }
}
