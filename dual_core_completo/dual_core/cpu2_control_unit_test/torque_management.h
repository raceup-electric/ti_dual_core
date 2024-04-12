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
#define P 5
#define FLUX_MG 0.0296
#define LD 0.12E-3
#define LQ 0.24E-3
#define ETA_INV 0.98
#define SATURAZIONE 0.9
#define RBATT 0.3
#define TALPHA -5.919761121102884


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

void performancePack();

void saturationsAndConversions();

void TractionControl(double T);

//Debug version for initial implementation
void SimplifiedTractionControl(double T);

void FzCalculatorTV();

void FzCalculatorTC();

void RECalculatorTC();

void speedCalculatorTV();

void torqueVectoring();

void torqueRepartition();

void regBrake();

void torqueLimit1();

void ExtendedKalmanFilter(double T);

double ZK_compute(double T);

void velocity_estimation(double T);

#endif
