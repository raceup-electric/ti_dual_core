#include "power_controller.h"
#include "car_management.h"

void powerControl()
{
    int i;
    float sTorque = 0;

    for (i = 0; i < NUM_OF_MOTORS; i++)
        sTorque+=posTorquesNM[i];

    power_error = total_power - car_settings.power_limit; //limited by BMS temp

    reduction_factor = saturateFloat((PIController(power_error)/STANDARD_SPEED), sTorque*(0.99f), 0)/sTorque;

    if (reduction_factor > 0)
    {
        int i;
        for (i = 0; i < NUM_OF_MOTORS; i++)
            posTorquesNM[i] = posTorquesNM[i] - (reduction_factor*posTorquesNM[i]);
        return;
    }
    else
        return;

}

float PIController(float pi_error)
{
    float pGain = pi_error * KP_PI;
    float iGain = pi_error * KI_PI * T_SAMPLING_ECU;

    iGain+= anti_wind_up;

    iGain = saturateFloat(iGain, PI_UPPER_BOUND, 0);

    anti_wind_up = iGain;

    float pe_red = saturateFloat(iGain + pGain, PI_UPPER_BOUND, 0);

    return pe_red;
}


