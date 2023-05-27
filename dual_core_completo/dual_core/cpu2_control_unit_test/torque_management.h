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
extern const int STEERING_DEADBAND;
extern int actualVelocityRPM;
extern float actualVelocityKMH;
extern int throttleReq;
extern int brakeReq;
extern int brake;
extern int steering;
extern int throttle;
extern float sendyne_current;
extern float sendyne_voltage;

extern int posTorques[4];
extern int negTorques[4];

extern float posTorquesNM[4];
extern float negTorquesNM[4];

//performance pack
extern float th, brk;
extern int str;
extern float ax, ay, yaw_r;
extern float motorSpeeds[4];
extern float steers[4];
extern float speedTv;
extern float fz[4];
extern float re[4];
extern double fzTC[4];
extern double reTC[4];
extern float speedTv;
extern float repFz[4];
extern float posTorqueCandidate[4][4];      //[MotorIndex][CandidateIndex]
extern float negTorqueCandidate[4];      //[MotorIndex]
extern float AMK_TorqueLimitPositive[4];
extern float AMK_TorqueLimitNegative[4];
extern float torque_reg_IPM[4];


extern float power_limit;

/*
 * KALMAN
 */

extern double speed_state[2];
extern double w_angles[4];
extern double v_wheels[4];
extern double delta_steer[2];

//
// prototypes
//


float readRPMVelocity();

void readVelocity();

void performancePack();

void saturationsAndConversions();

void FzCalculatorTV();

void FzCalculatorTC();

void RECalculatorTC();

void speedCalculatorTV();

void torqueVectoring();

void torqueRepartition();

void regBrake();

void onePedalDriving();

void torqueLimit1();

void ExtendedKalmanFilter(double T);

double ZK_compute(double T);

#endif
