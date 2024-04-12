
#ifndef MAIN_H_
#define MAIN_H_


#include "F28x_Project.h"
#include "global_definitions.h"
#include "motor_management.h"
#include "epwm_management.h"
#include "GPIO_management.h"
#include "utils.h"



#if (defined(DEBUG_HV) && defined(DEBUG_NO_HV))
#error "Error! Both DEBUG_HV and DEBUG_NO_HV are defined! Define only one of the two debug configurations at the same time"
#endif


//timestamp
Uint32 time_elapsed = 0;
Uint32 last_imu_message_time = 0;
// TODO: remove useless (check TV)
double T_s = 0;


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


// TODO: remove useless (remove launch)
bool is_launch_inserted = false;


/*
 * PRESETS
 */
const float presets_power[8] = {5000.f, 15000.f, 30000.f, 45000.f, 60000.f, 65000.f, 70000.f, 75000.f};
const float presets_regen[5] = {0.0f, 10.0f, 20.0f, 25.0f, 30.0f};


Uint16 fanSpeed = 0;

char status = 0x00;

//torque
int actualVelocityRPM = 0;
float actualVelocityKMH = 0;
int brake = 0; 
int paddle = 0;  // 0-100
int steering = 0; 
int throttle = 0; 
unsigned char imp;
const int STEERING_DEADBAND = 5;
bool checkPower = false;
int posTorques[4];
int negTorques[4];

float posTorquesNM[4];
float negTorquesNM[4];

//PERFORMANCE PACK
float th, brk;
int str;
float ax, ay, yaw_r;
float motorSpeeds[4];
float steers[4];
float speedTv = 0;
float fz[4] = {0,0,0,0};
float re[4];

double fzTC[4] = {0,0,0,0};
double reTC[4];
float repFz[4];

double TC_pos[4] = {0, 0, 0, 0};
double TC_neg[4] = {0, 0, 0, 0};

float posTorqueCandidate[4][4];      //[MotorIndex][CandidateIndex]
float negTorqueCandidate[4];      //[MotorIndex][CandidateIndex]
float Torque_max[4];
float AMK_TorqueLimitPositive[4];
float AMK_TorqueLimitNegative[4];
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

//alberto patch
tCANMsgObject TXCANA_ATC_Message_TBS;
tCANMsgObject TXCANA_ATC_Message_SUSPS;
tCANMsgObject TXCANA_ATC_Message_TEMPS;


unsigned char RXA_Imu_Data[8];
unsigned char RXA_Smu_Data[8];
unsigned char RXA_Sendyne_Data[8];
unsigned char RXA_BmsVol_Data[8];
unsigned char RXA_BmsTemp_Data[7];
unsigned char RXA_BmsLV_Data[8];
unsigned char RXA_Map_SW_Data[1];
unsigned char TXA_Host_Data[4];
unsigned char RXA_Lem_Data[8];
unsigned char TXCANA_PCU_Data[2];
unsigned char TXCANA_CarStatus_Data[2];
unsigned char TXCANA_CarSettings_Data[8];
unsigned char RXA_ATC_DATA_TBS[4];
unsigned char RXA_ATC_DATA_SUSPS[3];
unsigned char RXA_ATC_DATA_TEMPS[3];

unsigned char RXA_SW_Data[1];



unsigned char fan_enable;
unsigned char pump_enable;


/*
 * KALMAN FILTER
 */


const double p_lf[] = {45640000,-1951000,60000,-3000,1000,0};
const double p_fr[] = {45640000,1951000,60000,3000,1000,0};

double speed_state[2] = {0,0};
double w_angles[4] = {0,0,0,0};
double v_wheels[4] = {0,0,0,0};
double delta_steer[2] = {0,0};


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
// TODO: Remove not connected
Uint16 Sdc1_State;
Uint16 Sdc2_State;
Uint16 Sdc3_State;
Uint16 Sdc4_State;
Uint16 Sdc5_State;
Uint16 Sdc6_State;

//ADC
// TODO: Remove unused
Uint16 CurrSens_temp;
Uint16 Steering_temp;
Uint16 TempRadOutLC_temp;
Uint16 TempRadOutRC_temp;
Uint16 TempRadInLC_temp;
Uint16 TempRadInRC_temp;


/*
 * Shared structs
 */

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

struct Macros_settings macros_settings;

#pragma DATA_SECTION(sh,"SHARERAMGS11");
#pragma DATA_SECTION(time_elapsed,"SHARERAMGS12");
#pragma DATA_SECTION(macros_settings,"SHARERAMGS15");
#pragma DATA_SECTION(car_settings,"SHARERAMGS14");


//
// prototypes
//
void setup(void);

void loop();

#endif


