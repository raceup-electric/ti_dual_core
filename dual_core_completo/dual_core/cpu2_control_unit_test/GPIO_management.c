#include "GPIO_management.h"


int gpioOutput[] = {
                    RTDS,
                    R2D,
                    DEBUG_LED1,
                    DEBUG_LED2,
                    BRAKE_LIGHT_Abil,
                    };

int gpioInput[] = { AIR_1_STATE,
                    AIR_2_STATE,
                    IMD_STATE,
                    BMS_STATE};


void GPIOSetup()
{


    GPIO_WritePin(BLUE_BLINK, 0);
    GPIO_WritePin(R2D, R2D_LED_OFF);
    GPIO_WritePin(RTDS, 0);

    GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF);

}

void updateGPIOState()
{
    Air1_State = GPIO_ReadPin(AIR_1_STATE);
    Air2_State = GPIO_ReadPin(AIR_2_STATE);
    Imd_State = GPIO_ReadPin(IMD_STATE);
    Bms_State = GPIO_ReadPin(BMS_STATE);
}
