#ifndef MAIN_H_
#define MAIN_H_


#include "F28x_Project.h"
#include "global_definitions.h"
//#include "can_management.h"
//#include "timer_management.h"
#include "motor_management.h"
#include "epwm_management.h"
//#include "car_management.h"
//#include "adc_management.h"

#include "GPIO_management.h"
//#include "torque_management.h"
//#include "power_controller.h"
#include "utils.h"





#if (defined(DEBUG_HV) && defined(DEBUG_NO_HV))
#error "Error! Both DEBUG_HV and DEBUG_NO_HV are defined! Define only one of the two debug configurations at the same time"
#endif

int counter;    //for debug

//timestamp
Uint32 time_elapsed = 0;
Uint32 T_s = 0;

Uint16 batteryPackTension;
unsigned long int reassembled_data;
unsigned char CAN_SENDYNE_ACT_VALUES[8];

float lem_current;

//bms
float max_bms_voltage;
float min_bms_voltage;
float mean_bms_voltage;
float max_bms_temp;
float min_bms_temp;
float mean_bms_temp;
uint16_t max_temp_nslave;


//configuration
int driving_configuration;

//R2D
bool R2D_first_state = 0;
bool R2D_state = 0;
bool brk_disconnected = false;
bool implausibility_occurred = false;

bool is_launch_inserted = false;


/*
 * PRESETS
 */
const float presets_power[8] = {5000.f, 15000.f, 30000.f, 45000.f, 60000.f, 65000.f, 70000.f, 75000.f};
const float presets_max_pos[5] = {10.f, 13.f, 15.f, 17.f, 20.f};
const float presets_max_neg[5] = {-3.f, -5.f, -7.f, -9.f, -11.f};
const float presets_regen[5] = {0.0f, 10.0f, 20.0f, 25.0f, 30.0f};
const float presets_speed[6] = {5000, 10000, 14000, 15000, 18000, 20000};
const float presets_coppie_front[6] = {0.3f, 0.4f, 0.5f, 0.63f, 0.7f, 0.8f};
const float presets_coppie_rear[6] = {0.5f, 1.f, 1.3f, 1.5f, 1.7f, 1.8f};

// driver input
// filtro max-nuotatori: media mobile, senza contare i top N valori
const int filterValCount = 20;
const int filterDiscardCount = 10;
int throttles[20];  //20 = filterValCount
int brakes[20];
int steerings[20];
uint16_t value = 0;
char screen_mode = 0;

//pumps and fans
char RTDS_STATE = 0;  // RTDS
char OIL_PUMP_STATE = 0;
char WAT_PUMP_STATE = 0;
char FAN_STATE = 0;
int pump;
int stopPumpLimit;
int enablePumpLimit;

Uint16 leftFanSpeed = 0;
Uint16 rightFanSpeed = 0;

bool temp_warning = false;
Uint16 Temps[8];

//Temps[0]=getTempAvPT1000(TempRadOutLC_temp);
//Temps[1]=getTempAvPT1000(TempRadOutRC_temp);
//Temps[2]=getTempAvPT1000(TempRadInLC_temp);
//Temps[3]=getTempAvPT1000(TempRadInRC_temp);
//Temps[4]=0;
//Temps[5]=0;
//Temps[6]=leftFanSpeed;
//Temps[7]=rightFanSpeed;

Uint16 status = 0b00000000;

//torque
int actualVelocityRPM = 0;
float actualVelocityKMH = 0;
int brake = 0;
int steering = 0;
int throttle = 0;
const int STEERING_DEADBAND = 5;
bool implBrakeAndThrottle = false;
bool checkPower = false;
int posTorques[4];
int negTorques[4];

float AccPot1;
float AccPot2;
float BrkPot;

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

double TC_pos = 0;
double TC_neg = 0;

float posTorqueCandidate[4][4];      //[MotorIndex][CandidateIndex]
float negTorqueCandidate[4];      //[MotorIndex][CandidateIndex]
float Torque_max[4];
float AMK_TorqueLimitPositive[4];
float AMK_TorqueLimitNegative[4];
float torque_reg_IPM[4];            //massima coppia rigenerativa per motore


//AMK
int amkVal1ForwardCounter[4] = {0,0,0,0};
int amkVal2ForwardCounter[4] = {0,0,0,0};
Uint16 RX_A_temp[8];
//volatile Uint32 id;

uint16_t rxMsg[8];
uint16_t txMsg[8];

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

bool brakeWhenSlow = 0;
bool brakeReg = 0;
bool brakeMec = 0;
bool noBrake = 0;

//IMU
float accelerations[3]; //g
float omegas[3];        //rad/s
float temperatures[8];
Uint32 suspensions[4];

float bms_lv_cell[8]; //gli ultimi due valori sono temperature

//Calibration parameter
float versx[3];
float versy[3];
float versz[3];
float V[3][3] = {{0.9989f,-0.0464f,0.0076f},{0.0463f,0.9988f,-0.0128f},{0.0082f,0.0125f,0.9999f}};
float corrected_accelerations[3];

//timer
volatile uint16_t cpuTimer0IntCount;
volatile uint16_t cpuTimer1IntCount;
volatile uint16_t cpuTimer2IntCount;
volatile Uint32 pinValue;



//power control
float total_power;
float power_error;
float anti_wind_up = 0;
float reduction_factor;

float thermal_power_lim = POWER_LIMIT;
float thermal_power_min = 15000;
bool powerOK = false;



//CAN
volatile Uint32 errorFlag = 0;
volatile Uint32 rxBMsgCount = 0;
volatile Uint32 rxAMsgCount = 0;
int errorFrameCounterB = 0;
int errorFrameCounterA = 0;
tCANMsgObject RXCANA_Imu_Message;
tCANMsgObject RXCANA_Smu_Message;
tCANMsgObject TXCANA_Smu_Message[5];
tCANMsgObject RXCANA_Sendyne_Message;
tCANMsgObject RXCANA_BmsVol_Message;
tCANMsgObject RXCANA_BmsTemp_Message;
tCANMsgObject TXCANA_BmsHost_Message;
tCANMsgObject RXCANA_BmsLV_Message;
tCANMsgObject RXCANA_PwCtrl_Message;
tCANMsgObject RXCANA_Wheel_Message;
tCANMsgObject RXCANA_Lem_Message; //aggiunto lem
tCANMsgObject TXCANA_ATMega_Message;

unsigned char RXA_Imu_Data[8];
unsigned char RXA_Smu_Data[8];
unsigned char RXA_Sendyne_Data[8];
unsigned char RXA_BmsVol_Data[6];
unsigned char RXA_BmsTemp_Data[7];
unsigned char RXA_BmsLV_Data[8];
unsigned char RXA_PwCtrl_Data[1];
unsigned char RXA_Wheel_Data[1];
unsigned char TXA_Host_Data[4];
float TXA_Smu_Calibration[5][2];
unsigned char RXA_Lem_Data[8]; //aggiunto lem
unsigned char TXCANA_ATMega_Data[2];


unsigned char fan_enable;
unsigned char pump_enable;
unsigned char epwm4B;
unsigned char epwm5A;
unsigned char epwm5B;
unsigned char epwm6A;

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
Uint16 Imd_State;
Uint16 Bms_State;
Uint16 Sdc1_State;
Uint16 Sdc2_State;
Uint16 Sdc3_State;
Uint16 Sdc4_State;
Uint16 Sdc5_State;
Uint16 Sdc6_State;

//ADC
Uint16 Acc2_temp;
Uint16 CurrSens_temp;
Uint16 Acc1_temp;
Uint16 BrakeClean_temp;
Uint16 BrakePress_temp;
Uint16 Steering_temp;
Uint16 TempRadOutLC_temp;
Uint16 TempRadOutRC_temp;
Uint16 TempRadInLC_temp;
Uint16 TempRadInRC_temp;


//Shared structs

struct Share_struct sh;

float bms_lv_shared[8];

struct Status_Log status_log;

struct motorValues1 motorVal1_shared[4];
struct motorValues2 motorVal2_shared[4];  //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR
struct motorSetPoints motorSetP_shared[4];

struct BMS_Log bms_log;

//struct Sendyne_Log sendyne_log;
struct Power_Log power_log;

struct FanSpeed_Log fanspeed_log;

struct Imu_Log imu_log;

struct Gpio_Log gpio_log;

struct Display_command display;

struct Pedals_Log pedals_log;

struct Power_Setup_Log power_setup_log;

struct Car_settings car_settings;

struct Macros_settings macros_settings;

#pragma DATA_SECTION(macros_settings,"SHARERAMGS15");
#pragma DATA_SECTION(car_settings,"SHARERAMGS14");
#pragma DATA_SECTION(sh,"SHARERAMGS11");
#pragma DATA_SECTION(time_elapsed,"SHARERAMGS12");
#pragma DATA_SECTION(display,"SHARERAMGS13");


//
// prototypes
//
void setup(void);

void loop();

#endif



