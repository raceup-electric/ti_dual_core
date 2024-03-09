
#ifndef _CAR_MANAGEMENT_H_
#define _CAR_MANAGEMENT_H_

//
// includes
//
#include "driver_input.h"
#include "adc_management.h"
#include "atc_management.h"
#include "utils.h"
#include "global_definitions.h"
#include "epwm_management.h"
#include "can_management.h"
#include "atc_management.h"

//
// variables
//
extern bool R2D_first_state;
extern bool R2D_state;
extern char status;

extern Uint32 last_imu_message_time;

// sendyne DEPRECATED. IL SENDYNE NON VIENE PIU USATO
// extern float sendyne_current;
// extern float sendyne_voltage;

extern Uint16 batteryPackTension;
extern float lem_current;
extern unsigned long int reassembled_data;
extern unsigned char CAN_SENDYNE_ACT_VALUES[8];

extern unsigned char fan_enable;
extern unsigned char pump_enable;

// bms
extern float max_bms_voltage;
extern float min_bms_voltage;
extern float mean_bms_voltage;
extern float max_bms_temp;
extern float min_bms_temp;
extern float mean_bms_temp;
extern Uint16 max_temp_nslave;
extern Uint16 bms_bitmap;

extern int brakeReq;
extern int throttleReq;

extern float accelerations[3];
extern float omegas[3];
extern float suspensions[4];
extern float temperatures[10];

extern float bms_lv_cell[8];

extern Uint16 fanSpeed;

// AMK
extern int hvCounter[4];
extern int rfCounter[4];

extern bool inverterHV[4];
extern bool inverterRF[4];

extern float repFz[4];

// Launch setting
extern bool is_launch_inserted;
// logging
extern struct Share_struct sh;
extern struct Status_Log status_log;
extern struct BMS_Log bms_log;
extern struct Power_Log power_log;
extern struct FanSpeed_Log fanspeed_log;
extern struct Imu_Log imu_log;
extern struct Gpio_Log gpio_log;
extern Uint16 Temps_shared[8];
extern struct motorSetPoints motorSetP_shared[4];
extern struct motorValues1 motorVal1_shared[4];
extern struct motorValues2 motorVal2_shared[4];
extern float bms_lv_shared[8];
extern struct Pedals_Log pedals_log;
extern struct Power_Setup_Log power_setup_log;

extern struct Car_settings car_settings;

extern struct motorValues1 motorVal1[4]; //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR

//
// prototypes
//
void read_SENDYNE_message(unsigned char sendyne_values[]);

void read_LEM_message(unsigned char lem_values[]);

void read_IMU_message(Uint16 imu_values[], int id);

void read_SMU_Message(Uint16 smu_values[], int id);

void read_BMSLV_message(Uint16 bmslv_values[], int id);

void read_map_sw_message(Uint16 val);

void read_BMS_TEMP_message(Uint16 bms_values[]);

void read_BMS_VOLTAGE_message(Uint16 bms_values[]);

void read_steering_wheel_message(Uint16 val[], int id);

void read_ATC_TBS(Uint16 data[]);

void read_ATC_SENSORS(Uint16 data[]);

void brakeLight();

void R2D_On();

void R2D_Off();

void R2D_init();

void checkHV();

void checkRF();

bool isHVOn();

bool readRF();

void checkTemps();

void checkStatus();

void carSettingsMessage();

void update_shared_mem();

void update_log_values();

Uint16 fanSpeedFunction(int temp);

void fanControl();

void sendDataToLogger();

void computeBatteryPackTension();

#endif
