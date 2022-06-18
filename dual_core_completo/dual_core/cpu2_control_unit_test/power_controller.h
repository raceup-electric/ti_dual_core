#ifndef POWER_CONTROLLER_H
#define POWER_CONTROLLER_H


//include
#include "motor_management.h"
#include "torque_management.h"
#include "global_definitions.h"


//variabili
extern float sendyne_current;
extern float sendyne_voltage;
extern float total_power;
extern int posTorques[4];
extern float posTorquesNM[4];
extern float power_error;
extern float anti_wind_up;
extern float reduction_factor;

//prototipi

void powerControl();

float PIController(float pi_error);

#endif
