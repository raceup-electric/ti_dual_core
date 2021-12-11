#include "GPIO_management.h"

//
// include
//
#include "device.h"
#include "gpio.h"
#include "global_definitions.h"

int gpioOutput[] = {POMPA_DX_Abil,
                    POMPA_SX_Abil,
                    RTDS,
                    SCS_FAULT,
                    R2D,
                    BRAKE_LIGHT_Abil,
                    VENTOLA_Abil};

int gpioInput[] = { AIR_1_STATE,
                    AIR_2_STATE,
                    AUX_SDC,
                    LV_ALARM};

void GPIOSetup()
{

    int i;
    for (i=0; i<(sizeof(gpioOutput)/sizeof(int)); i++)
    {
        GPIO_setPadConfig(gpioOutput[i], GPIO_PIN_TYPE_STD);
        GPIO_setDirectionMode(gpioOutput[i], GPIO_DIR_MODE_OUT);
    }

    for (i=0; i<(sizeof(gpioInput)/sizeof(int)); i++)
    {
        GPIO_setPadConfig(gpioInput[i], GPIO_PIN_TYPE_STD);
        GPIO_setDirectionMode(gpioInput[i], GPIO_DIR_MODE_IN);
    }

    //setup LED 1
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    //setup LED 2
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0);
    GPIO_writePin(R2D, R2D_LED_OFF);
    GPIO_writePin(RTDS, 0);
    GPIO_writePin(POMPA_SX_Abil, 0);
    GPIO_writePin(POMPA_DX_Abil, 0);
    GPIO_writePin(VENTOLA_Abil, 0);
    GPIO_writePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF);
    GPIO_writePin(SCS_FAULT, 1U);

#ifdef TSAL_CTRL
    //------------------------------------------
    //Tramacci TSAL
    GPIO_setPadConfig(11, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(11, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(14, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(14, GPIO_DIR_MODE_OUT);
    GPIO_writePin(11, 0);
    GPIO_writePin(14, 0);
    //------------------------------------------
#endif

}
