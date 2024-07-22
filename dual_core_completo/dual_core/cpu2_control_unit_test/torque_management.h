#ifndef TORQUE_MANAGEMENT_H_
#define TORQUE_MANAGEMENT_H_

//
// include
//
#include "matrix.h"
#include "motor_management.h"
#include "global_definitions.h"
#include "utils.h"



#define R 0.0675
#define POLES 5
#define FLUX_MG 0.0296
#define LD 0.12E-3
#define LQ 0.24E-3
#define ETA_INV 0.98
#define ETA_MECH 0.9
#define RBATT 0.3
#define TALPHA -5.919761121102884
#define BATTERY_FULL_VOLTAGE 554 // 4.2 * 132


//
// variables
//
extern int actualVelocityRPM;
extern float actualVelocityKMH;
extern int throttleReq;
extern int brakeReq;
extern int brake;
extern int steering;
extern int throttle;

extern float posTorquesNM[4];
extern float negTorquesNM[4];

extern float repFz[4];
extern float torque_reg_IPM[4];


extern float power_limit;

//
// prototypes
//


float readRPMVelocity();

void readVelocity();

void regBrake();

#endif
