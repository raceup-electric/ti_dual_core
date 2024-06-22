
#ifndef MAIN_H_
#define MAIN_H_


#include "F28x_Project.h"
#include "global_definitions.h"
#include "motor_management.h"
#include "epwm_management.h"
#include "GPIO_management.h"
#include "utils.h"
#include "can_management.h"
#include "GPS.h"

#if (defined(DEBUG_HV) && defined(DEBUG_NO_HV))
#error "Error! Both DEBUG_HV and DEBUG_NO_HV are defined! Define only one of the two debug configurations at the same time"
#endif


//timestamp
Uint32 time_elapsed = 0;
Uint32 last_imu_message_time = 0;
Uint32 time_elapsed_ATC = 0;


Uint16 batteryPackTension;
float lem_current;


//bms
float max_bms_voltage;
float min_bms_voltage;
float mean_bms_voltage;
float max_bms_temp;
float min_bms_temp;
float mean_bms_temp;
Uint16 max_temp_nslave;
Uint16 bms_bitmap;


//R2D
bool R2D_first_state = 0;
bool R2D_state = 0;


/*
 * PRESETS
 */
const float presets_power[10] = {75000.f, 60000.f, 45000.f, 30000.f, 15000.f, 15000.f, 15000.f, 15000.f, 15000.f, 15000.f};
const float presets_regen[10] = {0.0f, 0.3f, 0.5f, 0.8f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};   // max curr regen A
const float presets_repartition[20] = {1.f, 1.f, 2.f, 0.5f, 1.8f, 0.6f, 1.8f, 0.6f, 1.8f, 0.6f, 1.8f, 0.6f, 1.8f, 0.6f, 1.8f, 0.6f, 1.8f, 0.6f, 1.8f, 0.6f};

Uint16 fanSpeed = 0;
char status = 0;

//torque
int actualVelocityRPM = 0;
float actualVelocityKMH = 0;
int brake = 0; 
int brakePress = 0; // Pa
int paddle = 0;  // 0-100
int steering = 0; 
int throttle = 0; 
unsigned char imp;
bool checkPower = false;

float posTorquesNM[4];
float negTorquesNM[4];

float repFz[4];
float torque_reg_IPM[4];            //massima coppia rigenerativa per motore



const int AMK_VAL_1_IDS[4] = {0x283, 0x284, 0x287, 0x288};
const int AMK_VAL_2_IDS[4] = {0x285, 0x286, 0x289, 0x28A};
const int AMK_SETPOINTS_IDS[4] = {0x184, 0x185, 0x188, 0x189};

Uint16 CAN_AMK_SET_POINT[4][8];

struct motorValues1 motorVal1[4];
struct motorValues2 motorVal2[4];  //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR
struct motorSetPoints motorSetP[4];

int hvCounter[4] = {0,0,0,0};
int rfCounter[4] = {0,0,0,0};

bool inverterHV[4] = {0,0,0,0};
bool inverterRF[4] = {0,0,0,0};

bool motorInitialized[4] = {false, false, false, false};
bool enableMotor = false;
int velocityRef = 0;
int throttleReq = 0;
int brakeReq = 0;
int drivingMode = 0;

//IMU
float accelerations[3]; //g
float omegas[3];        //rad/s
float temperatures[10];
float suspensions[4]; 

// TODO: Use a better structure
float bms_lv_cell[8]; //gli ultimi due valori sono temperature

//Calibration parameter

float V[3][3] = {{0.9989f,-0.0464f,0.0076f},{0.0463f,0.9988f,-0.0128f},{0.0082f,0.0125f,0.9999f}};


//power control
float total_power;
float power_error;
float anti_wind_up = 0;
float reduction_factor;

float thermal_power_lim = POWER_LIMIT;
float thermal_power_min = 15000;



//CAN
volatile Uint32 errorFlag = 0;
volatile Uint32 rxBMsgCount = 0;
volatile Uint32 rxAMsgCount = 0;
int errorFrameCounterB = 0;
int errorFrameCounterA = 0;
tCANMsgObject RXCANA_Imu_Message;
tCANMsgObject RXCANA_Smu_Message;
tCANMsgObject RXCANA_Sendyne_Message;
tCANMsgObject RXCANA_BmsVol_Message;
tCANMsgObject RXCANA_BmsTemp_Message;
tCANMsgObject TXCANA_BmsHost_Message;
tCANMsgObject RXCANA_BmsLV_Message;
tCANMsgObject RXCANA_Map_SW_Message;
tCANMsgObject RXCANA_Lem_Message;
tCANMsgObject RXCANA_SW_Message;


tCANMsgObject TXCANA_PCU_Message;
tCANMsgObject TXCANA_CarSettings_Message;
tCANMsgObject TXCANA_CarStatus_Message;

tCANMsgObject RXCANA_ATC_Message_TBS;
tCANMsgObject RXCANA_ATC_Message_SUSPS;
tCANMsgObject RXCANA_ATC_Message_TEMPS;
tCANMsgObject RXCANA_SetStart_Message;


unsigned char RXA_Imu_Data[8];
unsigned char RXA_Smu_Data[8];
unsigned char RXA_Sendyne_Data[8];
unsigned char RXA_BmsVol_Data[8];
unsigned char RXA_BmsTemp_Data[7];
unsigned char RXA_BmsLV_Data[8];
unsigned char RXA_Map_SW_Data[1];
unsigned char TXA_Host_Data[2];
unsigned char RXA_Lem_Data[8];
unsigned char TXCANA_PCU_Data[2];
unsigned char TXCANA_CarStatus_Data[2];
unsigned char TXCANA_CarSettings_Data[8];
unsigned char RXA_ATC_DATA_TBS[4];
unsigned char RXA_ATC_DATA_SUSPS[3];
unsigned char RXA_ATC_DATA_TEMPS[3];
unsigned char RXA_SetStart;

unsigned char RXA_SW_Data[1];


unsigned char fan_enable;
unsigned char pump_enable;

/*
 * AMK CAN
 */
tCANMsgObject RXCANB_AmkVal1_Message[4];
tCANMsgObject RXCANB_AmkVal2_Message[4];
unsigned char RXB_AmkVal_Data[8];

tCANMsgObject TXCANB_Setpoints_Message[4];
unsigned char TXB_Setpoints_Data[4][8];

//Hardware debug variables
Uint16 Air1_State;
Uint16 Air2_State;
// TODO: Read but unused
Uint16 Imd_State;
// TODO: Read but unused
Uint16 Bms_State;
// TODO: Remove if unused (check schematic 2024)
Uint16 Sdc1_State;
Uint16 Sdc2_State;
Uint16 Sdc3_State;
Uint16 Sdc4_State;
Uint16 Sdc5_State;
Uint16 Sdc6_State;


/*
 * Shared structs
 */
unsigned char setStart = false;
struct Share_struct sh;

float bms_lv_shared[8];

struct Status_Log status_log;

struct motorValues1 motorVal1_shared[4];
struct motorValues2 motorVal2_shared[4];  //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR
struct motorSetPoints motorSetP_shared[4];

struct BMS_Log bms_log;

struct Power_Log power_log;

struct FanSpeed_Log fanspeed_log;

struct Imu_Log imu_log;

struct Gpio_Log gpio_log;

struct Pedals_Log pedals_log;

struct Power_Setup_Log power_setup_log;

struct Car_settings car_settings;

GPS gps;


#pragma DATA_SECTION(sh,"SHARERAMGS11");
#pragma DATA_SECTION(time_elapsed,"SHARERAMGS12");
#pragma DATA_SECTION(car_settings,"SHARERAMGS14");
#pragma DATA_SECTION(setStart, "SHARERAMGS15");


//
// prototypes
//
void setup(void);

void loop();

#endif


