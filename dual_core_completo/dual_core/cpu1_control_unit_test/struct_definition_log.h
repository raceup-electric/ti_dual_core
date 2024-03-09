
#ifndef STRUCT_DEFINITION_LOG_H_
#define STRUCT_DEFINITION_LOG_H_
#include "F28x_Project.h"
#include "uart.h"
#include "stdio.h"
#include "global_definitions.h"

extern struct Share_struct local_sh;
extern struct Car_settings car_settings;
extern struct Macros_settings macros_settings;

// Logging
struct motorValues1
{
    bool AMK_bSystemReady;    // System ready(SBM)
    bool AMK_bError;          // Error
    bool AMK_bWarn;           // Warning
    bool AMK_bQuitDcOn;       // HVactivation acknowledgment
    bool AMK_bDcOn;           // HVactivation level
    bool AMK_bQuitInverterOn; // RF Controller enable acknowledgment
    bool AMK_bInverterOn;     // Controller enable level
    bool AMK_bDerating;       // Derating (torque limitation active)

    float AMK_ActualVelocity; // Signed - Unit: rpm - Actual speed value
    float AMK_TorqueCurrent;  // Signed - Raw data for calculating 'actual torque current'Iq See 'Units'on page 61
    Uint16 AMK_Voltage;       // Signed - Raw data for calculating 'actual magnetizing current'Id See 'Units'on page 1
    float AMK_Current;        // see PDK
};

struct motorValues2
{
    float AMK_TempMotor;        // Signed - Unit: 0.1 �C - Motor temperature
    float AMK_TempInverter;     // Signed - Unit: 0.1 �C - Cold plate temperature
    float AMK_TempIGBT;         // Signed - Unit: 0.1 �C - IGBTtemperature
    unsigned int AMK_ErrorInfo; // Unsigned - Diagnostic number
};

struct motorSetPoints
{
    bool AMK_bInverterOn; // Controller enable
    bool AMK_bDcOn;       // HVactivation
    bool AMK_bEnable;     // Driverenable
    bool AMK_bErrorReset; // Remove error*

    int AMK_TargetVelocity;      // Signed - Unit: rpm - Speed setpoint
    int AMK_TorqueLimitPositive; // Signed - Unit:  0.1% M_N  - Positive torque limit (subject to nominal torque)
    int AMK_TorqueLimitNegative; // Signed - Unit:  0.1% M_N  - Negative torque limit (subject to nominal torque)
};

struct Status_Log
{
    int throttle_shared;
    int steering_shared;
    int brake_shared;
    int brakePress_shared;
    int actualVelocityKMH_shared;
    char status_shared;
};

struct BMS_Log
{
    float max_bms_voltage_shared;
    float min_bms_voltage_shared;
    float mean_bms_voltage_shared;
    float max_bms_temp_shared;
    float min_bms_temp_shared;
    float mean_bms_temp_shared;
    Uint16 max_bms_temp_nslave_shared;
    Uint16 bms_bitmap_shared;
};

struct Power_Log
{
    float lem_current_shared;
    float batteryPack_voltage_shared;
    float curr_sens_shared;
    float total_power_shared;
};

struct FanSpeed_Log
{
    Uint16 fanSpeed_shared;
};

struct Imu_Log
{
    float accelerations_shared[3];
    float omegas_shared[3];
    float temperatures_shared[10];
    float suspensions_shared[4];
};
struct Pedals_Log
{
    float acc_shared;
    float brk_shared;
    int brk_req_shared;
    int throttle_req_shared;
};

struct Gpio_Log
{
    Uint16 Imd_shared;
    Uint16 Bms_shared;
    Uint16 Sdc1_shared;
    Uint16 Sdc2_shared;
    Uint16 Sdc3_shared;
    Uint16 Sdc4_shared;
    Uint16 Sdc5_shared;
    Uint16 Sdc6_shared;
};

struct Power_Setup_Log
{
    int max_speed_shared;
    float rear_motor_scale_shared;
    float front_motor_scale_shared;
    float power_limit_shared;
};

struct Car_settings
{
    // status
    bool lauch_ready;

    // screen
    float presets_power[8];
    float presets_regen[6];

    // setup variables
    float max_regen_current;
    float max_speed;
    float rear_motor_scale;
    float front_motor_scale;
    float max_pos_torque;
    float max_neg_torque;
    float power_limit;
};

struct Macros_settings
{
    bool torque_vectoring;
    bool traction_ctrl;
    bool one_pedal;
    bool thermal_power_ctrl;
    bool reg_brake;
};

struct Share_struct
{
    float bms_lv[8];
    struct motorValues1 motorVal1[4];
    struct motorValues2 motorVal2[4];
    struct motorSetPoints motorSetP[4];
    struct Imu_Log imu;
    struct FanSpeed_Log fanSpeed;
    struct Power_Log power;
    struct BMS_Log bms;
    struct Status_Log status;
    struct Gpio_Log gpio;
    struct Pedals_Log pedals;
    struct Power_Setup_Log power_setup;
};

#endif /* STRUCT_DEFINITION_LOG_H_ */
