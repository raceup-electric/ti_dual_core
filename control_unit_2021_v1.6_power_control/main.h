#ifndef MAIN_H_
#define MAIN_H_


//
// includes
//
#include "global_definitions.h"
#include "driverlib.h"
#include "device.h"
#include "can_management.h"
#include "timer_management.h"
#include "epwm_management.h"
#include "adc_management.h"
#include "motor_management.h"
#include "torque_management.h"
#include "GPIO_management.h"
#include "car_management.h"
#include "power_controller.h"
#include "dac_management.h"


//...
#if (defined(DEBUG_HV) && defined(DEBUG_NO_HV))
#error "Error! Both DEBUG_HV and DEBUG_NO_HV are defined! Define only one of the two debug configurations at the same time"
#endif
//
// const
//


//
// variables
//

// sendyne
float sendyne_current;
float sendyne_voltage;
unsigned long int reassembled_data;
unsigned char CAN_SENDYNE_ACT_VALUES[8];

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

uint8_t leftFanSpeed = 0;
uint8_t rightFanSpeed = 0;

bool temp_warning = false;
uint8_t Temps[8];
uint8_t status = 0b00000000;

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


//power control
float total_power;
float power_error;
float anti_wind_up = 0;
float reduction_factor;

float power_limit; //quello che gli arriva dal volante
bool powerOK = false;
uint8_t powersetup[8];

//CAN
volatile uint32_t errorFlag = 0;
volatile uint32_t rxBMsgCount = 0;
volatile uint32_t rxAMsgCount = 0;
int errorFrameCounterB = 0;
int errorFrameCounterA = 0;

int amkVal1ForwardCounter[4] = {0,0,0,0};
int amkVal2ForwardCounter[4] = {0,0,0,0};
uint8_t RX_A_temp[8];
//volatile uint32_t id;

//AMK
uint16_t rxMsg[8];
uint16_t txMsg[8];

const int AMK_VAL_1_IDS[4] = {0x283, 0x284, 0x287, 0x288};
const int AMK_VAL_2_IDS[4] = {0x285, 0x286, 0x289, 0x28A};
const int AMK_SETPOINTS_IDS[4] = {0x184, 0x185, 0x188, 0x189};

uint8_t CAN_AMK_SET_POINT[4][8];

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

//timer
volatile uint16_t cpuTimer0IntCount;
volatile uint16_t cpuTimer1IntCount;
volatile uint16_t cpuTimer2IntCount;
volatile uint32_t pinValue;

uint8_t var = 0;



struct StatStruct stat;
struct AllData dts;

void updateValues(){
    //dts.acc = accelerations;
    //dts.omegas = omegas;

    dts.s = stat;
    //dts.temps = Temps;

//    dts.motorSetPoints = motorSet;
//    dts.motorValues1 = motorVal1;
//    dts.motorValues2 = motorVal2;

    //dts.sendyneValues =
}


//#pragma DATA_SECTION(Temps,"ramgs1");
#pragma DATA_SECTION(dts,"ramgs2");



//
// prototypes
//
void setup();

void loop();

#endif
