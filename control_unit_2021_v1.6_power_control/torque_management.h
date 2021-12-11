#ifndef TORQUE_MANAGEMENT_H_
#define TORQUE_MANAGEMENT_H_

//
// include
//
#include "global_definitions.h"
#include "motor_management.h"
#include "utils.h"
#include "math.h"

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
extern float speedTv;
extern float repFz[4];
extern float posTorqueCandidate[4][4];      //[MotorIndex][CandidateIndex]
extern float negTorqueCandidate[4];      //[MotorIndex]
extern float AMK_TorqueLimitPositive[4];
extern float AMK_TorqueLimitNegative[4];


//DEPRECATED
//extern float i_max;
//extern float tau_max;
//extern float tau_unbias;
//extern float percentage_tau;

//
// prototypes
//


float readRPMVelocity();

void readVelocity();

void performancePack();

void saturationsAndConversions();

void FzCalculatorTV();

void speedCalculatorTV();

void torqueVectoring();

void torqueRepartition();
//DEPRECATED
//float getMotorScale(int motor);
//
//bool isInnerMotor(int motor);
//
//bool isOuterMotor(int motor);
//
//bool isLeftTurn();
//
//bool isRightTurn();
//
//float getInnerTorque(float requestedTorque, float speed, float delta, float k);
//
//float getOuterTorque(float requestedTorque, float speed, float delta, float k);

#endif
