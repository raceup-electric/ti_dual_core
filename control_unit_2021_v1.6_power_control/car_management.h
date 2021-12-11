#ifndef _CAR_MANAGEMENT_H_
#define _CAR_MANAGEMENT_H_

//
// includes
//
#include "global_definitions.h"
#include "driver_input.h"
#include "adc_management.h"

//
// variables
//
extern bool R2D_first_state;
extern bool R2D_state;
extern bool brk_disconnected;
extern bool implBrakeAndThrottle ;

extern float sendyne_current;
extern float sendyne_voltage;
extern unsigned long int reassembled_data;
extern unsigned char CAN_SENDYNE_ACT_VALUES[8];

//bms
extern float max_bms_voltage;
extern float min_bms_voltage;
extern float mean_bms_voltage;
extern float max_bms_temp;
extern float min_bms_temp;
extern float mean_bms_temp;

extern float accelerations[3];
extern float omegas[3];

extern char RTDS_STATE;  // RTDS
extern char OIL_PUMP_STATE;
extern char WAT_PUMP_STATE;
extern char FAN_STATE;
extern int pump;
extern int stopPumpLimit;
extern int enablePumpLimit;

extern uint8_t Temps[8];
extern uint8_t status;

extern uint8_t leftFanSpeed;
extern uint8_t rightFanSpeed;

//AMK
extern int hvCounter[4];
extern int rfCounter[4];

extern bool inverterHV[4];
extern bool inverterRF[4];

//power control
extern float power_limit;


//
// prototypes
//
void read_SENDYNE_message(unsigned char sendyne_values[]);

void read_IMU_message(uint8_t imu_values[], int id);

void read_power_control_message(uint8_t val[]);

void read_BMS_TEMP_message(uint8_t bms_values[]);

void read_BMS_VOLTAGE_message(uint8_t bms_values[]);

void brakeLight();

void playRTDS();

void R2D_On();

void R2D_Off();

void R2D_init();

void checkHV();

void checkRF();

bool isHVOn();

bool readRF();

void checkImplausibility();

//void checkPumps();  //deprecated

void checkTemps();

void checkStatus();

void sendDataToLogger();

void sendStatusToLogger();

void sendTempsToLogger();

void sendSetpointsToLogger();

uint8_t fanSpeedFunction(int temp);

void fanControl();

#endif
