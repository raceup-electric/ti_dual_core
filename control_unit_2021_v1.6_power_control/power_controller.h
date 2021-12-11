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

//DEPRECATED
//float proportionalTerm(float power_diff);   //azione proporzionale
//
//float integralTerm(float power_diff);       //azione integrale
//
//float calculateUpperBound();         //calcolo del limite superiore
//
//void calculateTorque(int pedal_pressure);//calcolo del setpoint di coppia
//
//void simulateInverter(float torque_setpoint);//simula il consumo di corrente
//                                             //degli inverter in funzione
//                                             //della coppia
//
//int simulatePedal();        //simula la pressione del pedale
//                            //dell'acceleratore

#endif
