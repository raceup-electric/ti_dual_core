#include <math.h>
#include "utils.h"

void setup_car_settings(){

    memcpy(car_settings.presets_power, presets_power, sizeof(presets_power));
    memcpy(car_settings.presets_torque_pos, presets_torque_pos, sizeof(presets_torque_pos));
    memcpy(car_settings.presets_repartition, presets_repartition, sizeof(presets_repartition));
    memcpy(car_settings.presets_regen, presets_regen, sizeof(presets_regen));
    memcpy(car_settings.presets_torque_neg, presets_torque_neg, sizeof(presets_torque_neg));

    car_settings.regen_current_scale = 0.0f;
    car_settings.max_regen_current = PEAK_REGEN_CURRENT;
    car_settings.max_speed = SPEED_LIMIT;
    car_settings.max_pos_torque = MAX_POS_TORQUE;
    car_settings.max_neg_torque = MAX_NEG_TORQUE;
    car_settings.power_limit = POWER_LIMIT;
    rtP.Pmax = POWER_LIMIT;
    rtP.TC_map[0] = KP_TC;
    rtP.TC_map[1] = KI_TC;
    rtP.TC_map[2] = KD_TC;
    rtP.T_max = MAX_POS_TORQUE;
    rtP.kRamp = K_RAMP;
    rtP.offset_brake_csi = OFFSET_BRAKE;
    rtP.offset_cornering = OFFSET_CORNER;
    rtP.offset_throttle_csi = OFFSET_THROTTLE;
    car_settings.torque_vectoring = TORQUE_VECTORING;

    /*
     * Torques are computed by TV when active, so we don't have to set them
     */
    if(car_settings.torque_vectoring){
        car_settings.rear_motor_repartition = 0.5f;
        car_settings.front_motor_repartition = 0.5f;
    } else {
        car_settings.rear_motor_repartition = REAR_MOTOR_REPARTITION;
        car_settings.front_motor_repartition = FRONT_MOTOR_REPARTITION;
    }

    repFz[0] = 0.6;
    repFz[1] = 0.6;
    repFz[2] = 0.4;
    repFz[3] = 0.4;
}


float convertBMSvoltage(Uint16 voltage){
  return (float)(voltage / 10000.f);
}


float saturateFloat(float signal, float upperBound, float lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}

float saturateInt(int signal, int upperBound, int lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}


float uint32_to_float(Uint32 u)
{
    union
    {
        Uint32 u;
        float f;
    } temp;
    temp.u=u;

    return temp.f;
}

int16_t unsigned_to_signed(Uint16 value){
    union{
        Uint16 u;
        int16_t s;
    }temp;
    temp.u = value;
    return temp.s;
}

float convert_temp_lv(float cell_volt)
{
  float x = ((log((5 - cell_volt)/cell_volt))/3435);
  x = 1/((1/298.15) - x);
  return x - 273.15;
}


float torqueSetpointToNM(int setpoint)
{
    return (setpoint/1000.0)*M_N;
}

int NMtoTorqueSetpoint(float torqueNM)
{
    return (torqueNM/M_N)*1000;
}


void apply_calibration(){
    accelerations[X] = accelerations[X] * V[0][0] + accelerations[Y] * V[0][1] + accelerations[Z] * V[0][2];
    accelerations[Y] = accelerations[X] * V[1][0] + accelerations[Y] * V[1][1] + accelerations[Z] * V[1][2];
    accelerations[Z] = accelerations[X] * V[2][0] + accelerations[Y] * V[2][1] + accelerations[Z] * V[2][2];
}
