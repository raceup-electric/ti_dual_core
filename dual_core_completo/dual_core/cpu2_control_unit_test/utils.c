#include <math.h>
#include "utils.h"

void setup_car_settings(){

    /*
     * Must be called before changing car_settings struct
     */
    setup_macros();

    memcpy(car_settings.presets_power, presets_power, sizeof(presets_power));
    memcpy(car_settings.presets_regen, presets_regen, sizeof(presets_regen));

    car_settings.max_regen_current=MAX_REGEN_CURRENT;
    car_settings.max_speed = SPEED_LIMIT;
    car_settings.max_pos_torque = MAX_POS_TORQUE;
    car_settings.max_neg_torque = MAX_NEG_TORQUE;
    car_settings.power_limit = POWER_LIMIT;

    /*
     * Torques are computed by TV when active, so we don't have to set them
     */
    if(macros_settings.torque_vectoring){
        car_settings.rear_motor_scale = 1.0f;
        car_settings.front_motor_scale = 1.0f;
        repFz[0] = 0.6;
        repFz[1] = 0.6;
        repFz[2] = 0.4;
        repFz[3] = 0.4;
    } else {
        car_settings.rear_motor_scale = REAR_MOTOR_SCALE;
        car_settings.front_motor_scale = FRONT_MOTOR_SCALE;
        repFz[0] = 0.6;
        repFz[1] = 0.6;
        repFz[2] = 0.4;
        repFz[3] = 0.4;
    }
}

void setup_macros() {
    macros_settings.one_pedal = ONE_PEDAL;
    macros_settings.reg_brake = REG_BRAKE;
    macros_settings.thermal_power_ctrl = THERMAL_POWER_CTRL;
    macros_settings.torque_vectoring = TORQUE_VECTORING;
    macros_settings.traction_ctrl = TRACTION_CTRL;
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