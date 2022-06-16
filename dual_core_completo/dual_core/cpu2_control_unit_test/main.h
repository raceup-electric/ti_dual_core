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
Uint32 time_elapsed;

// sendyne
float sendyne_current;
float sendyne_voltage;
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



//configuration
int driving_configuration;

//R2D
bool R2D_first_state = 0;
bool R2D_state = 0;
bool brk_disconnected = false;
bool implausibility_occurred = false;

// driver input
// filtro max-nuotatori: media mobile, senza contare i top N valori
const int filterValCount = 20;
const int filterDiscardCount = 10;
int throttles[20];  //20 = filterValCount
int brakes[20];
int steerings[20];
uint16_t value=0;

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
float repFz[4];
float posTorqueCandidate[4][4];      //[MotorIndex][CandidateIndex]
float negTorqueCandidate[4];      //[MotorIndex][CandidateIndex]
float Torque_max[4];
float AMK_TorqueLimitPositive[4];
float AMK_TorqueLimitNegative[4];
float torque_reg_IPM[4];            //massima coppia rigenerativa per motore


//power control
float total_power;
float power_error;
float anti_wind_up = 0;
float reduction_factor;

Uint16 regensetup[8];
float max_regen_current=-20.0f;

float power_limit; //quello che gli arriva dal volante
bool powerOK = false;
Uint16 powersetup[8];

int amkVal1ForwardCounter[4] = {0,0,0,0};
int amkVal2ForwardCounter[4] = {0,0,0,0};
Uint16 RX_A_temp[8];
//volatile Uint32 id;

//AMK
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
float temperatures[5];
Uint32 suspensions[4];

float bms_lv_cell[8]; //gli ultimi due valori sono temperature

//Calibration parameter
float versx[3];
float versy[3];
float versz[3];
float V[3][3];

//timer
volatile uint16_t cpuTimer0IntCount;
volatile uint16_t cpuTimer1IntCount;
volatile uint16_t cpuTimer2IntCount;
volatile Uint32 pinValue;

//schermo
int presets_power[8] = {3, 30, 40, 50, 60, 65, 70, 75};

float presets_regen[6]={-1.5f,-3.0f,-5.0f,-10.0f,-15.0f,-20.0f};

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
tCANMsgObject RXCANA_BmsLV_Message;
tCANMsgObject RXCANA_PwCtrl_Message;
tCANMsgObject RXCANA_Wheel_Message;
tCANMsgObject RXCANA_Lem_Message; //aggiunto lem
unsigned char RXA_Imu_Data[8];
unsigned char RXA_Smu_Data[8];
unsigned char RXA_Sendyne_Data[8];
unsigned char RXA_BmsVol_Data[6];
unsigned char RXA_BmsTemp_Data[6];
unsigned char RXA_BmsLV_Data[8];
unsigned char RXA_PwCtrl_Data[1];
unsigned char RXA_Wheel_Data[1];
float TXA_Smu_Calibration[5][2];
unsigned char RXA_Lem_Data[8]; //aggiunto lem

tCANMsgObject RXCANB_AmkVal1_Message[4];
tCANMsgObject RXCANB_AmkVal2_Message[4];
unsigned char RXB_AmkVal_Data[8];

tCANMsgObject TXCANB_Setpoints_Message[4];
unsigned char TXB_Setpoints_Data[4][8];

//Hardware debug variables
bool Imd_State;
bool Bms_State;
bool Sdc1_State;
bool Sdc2_State;
bool Sdc3_State;
bool Sdc4_State;
bool Sdc5_State;
bool Sdc6_State;

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

Uint16 Temps_shared[8];
float bms_lv_shared[8];

struct Status_Log status_log;

struct motorValues1 motorVal1_shared[4];
struct motorValues2 motorVal2_shared[4];  //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR
struct motorSetPoints motorSetP_shared[4];

struct BMS_Log bms_log;

struct Sendyne_Log sendyne_log;

struct FanSpeed_Log fanspeed_log;

struct Imu_Log imu_log;

struct Gpio_Log gpio_log;

struct Display_command display;


//shard ram
Uint16 c2_r_w_array[256];
Uint16 increment;

//#pragma DATA_SECTION(c2_r_w_array,"SHARERAMGS1");
#pragma DATA_SECTION(sh,"SHARERAMGS1");
#pragma DATA_SECTION(time_elapsed,"SHARERAMGS2");
#pragma DATA_SECTION(display,"SHARERAMGS14");


//
// prototypes
//
void setup(void);

void loop();

#endif



