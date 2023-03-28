#include "GPIO_management.h"


int gpioOutput[] = {
                    RTDS,
                    SCS_FAULT,
                    R2D,
                    DEBUG_LED1,
                    DEBUG_LED2,
                    BRAKE_LIGHT_Abil,
                    };

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


    GPIO_WritePin(SDC1_STATE, 0);
    GPIO_WritePin(SDC2_STATE, 0);
    GPIO_WritePin(SDC3_STATE, 0);
    GPIO_WritePin(SDC4_STATE, 0);
    GPIO_WritePin(SDC5_STATE, 0);
    GPIO_WritePin(SDC6_STATE, 0);

    GPIO_WritePin(BLUE_BLINK, 0);
    GPIO_WritePin(R2D, R2D_LED_OFF);
    GPIO_WritePin(RTDS, 0);
    //GPIO_WritePin(ENABLE_PUMPS, 0);
    //GPIO_WritePin(VENTOLA_Abil, 0);

    //TXCANA_ATMega_Data = TXCANA_ATMega_Data & 0xFFFC;  // set the least two bits at zero
    //TXCANA_ATMega_Data = TXCANA_ATMega_Data & 0x0;  // set every bit to zero

    fan_enable = 0;
    pump_enable = 0;

    TXCANA_ATMega_Data[0] = fan_enable;
    TXCANA_ATMega_Data[1] = pump_enable;
    send_pwm_to_pcu();

    GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF);
    GPIO_WritePin(SCS_FAULT, 1U);

}

void updateGPIOState()
{
    Air1_State = GPIO_ReadPin(AIR_1_STATE);
    Air2_State = GPIO_ReadPin(AIR_2_STATE);
    Imd_State = GPIO_ReadPin(IMD_STATE);
    Bms_State = GPIO_ReadPin(BMS_STATE);
    Sdc1_State = GPIO_ReadPin(SDC1_STATE);
    Sdc2_State = GPIO_ReadPin(SDC2_STATE);
    Sdc3_State = GPIO_ReadPin(SDC3_STATE);
    Sdc4_State = GPIO_ReadPin(SDC4_STATE);
    Sdc5_State = GPIO_ReadPin(SDC5_STATE);
    Sdc6_State = GPIO_ReadPin(SDC6_STATE);
}
