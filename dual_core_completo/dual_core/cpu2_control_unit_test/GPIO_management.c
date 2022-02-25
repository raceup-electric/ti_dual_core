#include "GPIO_management.h"
#include "global_definitions.h"

int gpioOutput[] = {ENABLE_PUMPS,
                    RTDS,
                    SCS_FAULT,
                    R2D,
                    DEBUG_LED1,
                    DEBUG_LED2,
                    BRAKE_LIGHT_Abil,
                    VENTOLA_Abil};

int gpioInput[] = { AIR_1_STATE,
                    AIR_2_STATE,
                    SDC1_STATE,
                    SDC2_STATE,
                    SDC3_STATE,
                    SDC4_STATE,
                    SDC5_STATE,
                    SDC6_STATE,
                    IMD_STATE,
                    BMS_STATE};


void GPIOSetup()
{
//    int i;
//    for (i=0; i<(sizeof(gpioOutput)/sizeof(int)); i++)
//    {
//        GPIO_SetupPinMux(gpioOutput[i], GPIO_MUX_CPU1, 0);
//        GPIO_SetupPinOptions(gpioOutput[i], GPIO_OUTPUT, GPIO_PUSHPULL);
//    }
//
//    for (i=0; i<(sizeof(gpioInput)/sizeof(int)); i++)
//    {
//        GPIO_SetupPinMux(gpioOutput[i], GPIO_MUX_CPU1, 0);
//        GPIO_SetupPinOptions(gpioOutput[i], GPIO_OUTPUT, GPIO_PUSHPULL);
//    }
//
//    //setup LED 1
//    GPIO_SetupPinMux(RED_BLINK, GPIO_MUX_CPU1, 0);
//    GPIO_SetupPinOptions(RED_BLINK, GPIO_OUTPUT, GPIO_PUSHPULL);
//
//    //setup LED 2
//    GPIO_SetupPinMux(BLUE_BLINK, GPIO_MUX_CPU1, 0);
//    GPIO_SetupPinOptions(BLUE_BLINK, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_WritePin(BLUE_BLINK, 0);
    GPIO_WritePin(R2D, R2D_LED_OFF);
    GPIO_WritePin(RTDS, 0);
    GPIO_WritePin(ENABLE_PUMPS, 0);
    GPIO_WritePin(VENTOLA_Abil, 0);
    GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF);
    GPIO_WritePin(SCS_FAULT, 1U);

#ifdef TSAL_CTRL
    //------------------------------------------
    //Tramacci TSAL
    GPIO_SetupPinMux(11, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinMux(14, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(11, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinOptions(14, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_WritePin(11, 0);
    GPIO_WritePin(14, 0);
    //------------------------------------------
#endif
}
