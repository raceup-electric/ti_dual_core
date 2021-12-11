#ifndef MOTOR_MANAGEMENT_H_
#define MOTOR_MANAGEMENT_H_

//
// includes
//
#include "global_definitions.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "device.h"
#include "can_management.h"

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
extern uint8_t CAN_AMK_SET_POINT[4][8];

extern int amkVal1ForwardCounter[4];
extern int amkVal2ForwardCounter[4];
extern int drivingMode;
extern bool motorInitialized[4];
extern bool enableMotor;

extern int velocityRef;

//
// prototypes
//
void read_AMK_Values1(uint8_t canMsg[], int);
void read_AMK_Values2(uint8_t canMsg[], int);
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
void set_SetPoint(int, int, int, int);

int getMotorIndex(int id);      //restitusice il numero (0-4) dell'inverter a seconda dell'ID
int getAMKValNumber(int id);    //restituisce il numero (1-2) dell'ActualValue a seconda dell'ID

void setAMK(int, int, int);
void stopAMK();
void brakeAMK(int);
void throttleAMK(int);


#endif
