#ifndef MAIN_H_
#define MAIN_H_


#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "GPIO_management.h"
#include <stdint.h>
#include <stdbool.h>
//#include "math.h"
#include <stdio.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "sd_card.h"


//
// Globals
//
Uint16 c1_r_w_array[256];
Uint16 increment;
Uint16 deb;

Uint16 local_buf[256];
Uint16 local_val;

struct motorValues1 {
    bool AMK_bSystemReady;      //System ready(SBM)
    bool AMK_bError;            //Error
    bool AMK_bWarn;             //Warning
    bool AMK_bQuitDcOn;         //HVactivation acknowledgment
    bool AMK_bDcOn;             //HVactivation level
    bool AMK_bQuitInverterOn;   // RF Controller enable acknowledgment
    bool AMK_bInverterOn;       //Controller enable level
    bool AMK_bDerating;         //Derating (torque limitation active)

    float AMK_ActualVelocity;       //Signed - Unit: rpm - Actual speed value
    float AMK_TorqueCurrent;        //Signed - Raw data for calculating 'actual torque current'Iq See 'Units'on page 61
    float AMK_MagnetizingCurrent;   //Signed - Raw data for calculating 'actual magnetizing current'Id See 'Units'on page 1
    float AMK_Current;  // see PDK
};

struct motorValues2 {
    float AMK_TempMotor;                //Signed - Unit: 0.1 °C - Motor temperature
    float AMK_TempInverter;             //Signed - Unit: 0.1 °C - Cold plate temperature
    float AMK_TempIGBT;                 //Signed - Unit: 0.1 °C - IGBTtemperature
    unsigned int AMK_ErrorInfo;         //Unsigned - Diagnostic number
};

struct motorSetPoints {
    bool AMK_bInverterOn;               // Controller enable
    bool AMK_bDcOn;                     // HVactivation
    bool AMK_bEnable;                   // Driverenable
    bool AMK_bErrorReset;               // Remove error*

    int AMK_TargetVelocity;             //Signed - Unit: rpm - Speed setpoint
    int AMK_TorqueLimitPositive;        //Signed - Unit:  0.1% M_N  - Positive torque limit (subject to nominal torque)
    int AMK_TorqueLimitNegative;        //Signed - Unit:  0.1% M_N  - Negative torque limit (subject to nominal torque)
};

struct Status_Log {
    int throttle_shared;
    int steering_shared;
    int brake_shared;
    int brakePress_shared;
    int status_shared;
    int actualVelocityKMH_shared;
};

struct BMS_Log {
    float max_bms_voltage_shared;
    float min_bms_voltage_shared;
    float mean_bms_voltage_shared;
    float max_bms_temp_shared;
    float min_bms_temp_shared;
    float mean_bms_temp_shared;
};

struct Sendyne_Log {
    float sendyne_current_shared;
    float sendyne_voltage_shared;
    float curr_sens_shared;
    float total_power_shared;
};

struct FanSpeed_Log{
    Uint16 leftFanSpeed_shared;
    Uint16 rightFanSpeed_shared;
};

struct Imu_Log{
    float accelerations_shared[3];
    float omegas_shared[3];
};


struct Share_struct {
    Uint16 Temps[8];
    struct motorValues1 motorVal1[4];
    struct motorValues2 motorVal2[4];
    struct motorSetPoints motorSetP[4];
    struct Imu_Log imu;
    struct FanSpeed_Log fanSpeed;
    struct Sendyne_Log sendyne;
    struct BMS_Log bms;
    struct Status_Log status;
};

struct Share_struct sh;
struct Share_struct local_sh;

Uint16 Temps_shared[8];

struct Status_Log status_log;

struct motorValues1 motorVal1_shared[4];
struct motorValues2 motorVal2_shared[4];  //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR
struct motorSetPoints motorSetP_shared[4];

struct BMS_Log bms_log;

struct Sendyne_Log sendyne_log;

struct FanSpeed_Log fanspeed_log;

struct Imu_Log imu_log;



//#pragma DATA_SECTION(c1_r_w_array,"SHARERAMGS1");
#pragma DATA_SECTION(sh,"SHARERAMGS1");

uint16_t error;
uint16_t multiplier;

//
// Function Prototypes
//
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);
void Shared_Ram_dataRead_c1(void);
void send_can_to_cpu2(void);
void cpu1_timer_setup(void);

#endif
