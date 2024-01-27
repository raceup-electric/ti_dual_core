#ifndef MOTOR_MANAGEMENT_H_
#define MOTOR_MANAGEMENT_H_

//
// includes
//
#include "F28x_Project.h"
#include "global_definitions.h"
#include <stdbool.h>
#include <string.h>
//#include "device.h"
#include "can_management.h"
#include "utils.h"


//add
#include "power_controller.h"
#include "torque_management.h"

//
// struct
//


extern struct motorValues1 motorVal1[4];
extern struct motorValues2 motorVal2[4];  //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR
extern struct motorSetPoints motorSetP[4];

extern const int AMK_VAL_1_IDS[4];
extern const int AMK_VAL_2_IDS[4];
extern const int AMK_SETPOINTS_IDS[4];

//extern tCANMsgObject TX_CAN_AMK_SET_POINT[4];
extern Uint16 CAN_AMK_SET_POINT[4][8];

extern int amkVal1ForwardCounter[4];
extern int amkVal2ForwardCounter[4];
extern int drivingMode;
extern bool motorInitialized[4];
extern bool enableMotor;

extern int velocityRef;

//added new

extern float posTorquesNM[4];
extern float negTorquesNM[4];
extern int throttleReq;
extern int brakeReq;
extern float anti_wind_up;

//extern int max_speed;
//extern float rear_motor_scale;
//extern float front_motor_scale;
//extern float max_pos_torque;
//extern float max_neg_torque;

extern struct Car_settings car_settings;


//
// prototypes
//
void read_AMK_Values1(Uint16 canMsg[], int);
void read_AMK_Values2(Uint16 canMsg[], int);
void send_AMK_SetPoints(int indexMotor, int velocity, int posTorque, int negTorque);
void set_AMK_Drive_Mode(int);
void sendAMKDataMotor(int motor, int posTorque, int negTorque);
void sendAMKData();


void initializeMotor(int);
void deactiveMotor(int);
void removeError(int);

char getByte(int);
bool getBit(char, int);
void int2Bytes(unsigned char* bytes_temp, int int_variable);
void float2Bytes(unsigned char* bytes_temp, float float_variable);
void set_SetPoint(int, int, int, int);

int getMotorIndex(int id);      //restitusice il numero (0-4) dell'inverter a seconda dell'ID
int getAMKValNumber(int id);    //restituisce il numero (1-2) dell'ActualValue a seconda dell'ID

void setAMK(int, int, int);
void stopAMK();
void brakeAMK(int);
void throttleAMK(int);

void sendHostData();

#endif
