#include "power_controller.h"

void powerControl()
{
    int i;
    float sTorque = 0;

    for (i = 0; i < NUM_OF_MOTORS; i++)
        sTorque+=posTorquesNM[i];

    float computed_power_limit = Thermal_Power_Control();

    power_error = total_power - computed_power_limit;



    reduction_factor = PIController(power_error);
    reduction_factor = reduction_factor/STANDARD_SPEED;

    reduction_factor = saturateFloat(reduction_factor, sTorque*(0.99f), 0)/sTorque;

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

float Thermal_Power_Control()
{
    if(macros_settings.thermal_power_ctrl)
    {
        if (mean_bms_temp > T_MAX)
            thermal_power_lim = car_settings.power_limit *(1 - K1_THERMAL);
        else if (mean_bms_temp < T_MIN)
            thermal_power_lim = car_settings.power_limit;
        else
        {
            if (time_elapsed%30 == 0)
                thermal_power_lim = car_settings.power_limit * (1- K1_THERMAL * (mean_bms_temp - T_MIN) / (T_MAX - T_MIN));
            else
                if (thermal_power_lim > thermal_power_min)
                    thermal_power_lim = thermal_power_lim * (1 - K2_THERMAL);

        }
    }
    else
        if (thermal_power_lim < car_settings.power_limit - 100)
        {
            thermal_power_lim += K3_THERMAL;
        }
        else
        {
            thermal_power_lim = car_settings.power_limit;
        }

    return thermal_power_lim;
}
