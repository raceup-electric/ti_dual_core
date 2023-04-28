/*
 * display.h
 *
 *  Created on: 18 feb 2022
 *      Author: ludon
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "F28x_Project.h"
#include "uart.h"
#include "stdio.h"
#include "global_definitions.h"

#define TMP_SIZE 50

extern Uint16 currentPage;
extern char tmp[50];
extern struct Share_struct local_sh;
extern struct Display_command display;
extern struct Car_settings car_settings;
extern Uint16 n_setup;
extern Uint16 ack;

extern Uint16 old_setup;
extern Uint16 old_setup_pedal_setup;

extern Uint16 old_ack_setup;
extern Uint16 old_ack_pedal_setup;

struct Display_command{
    Uint16 page;
    Uint16 selector_setup;
    Uint16 ack_setup;

    Uint16 selector_regen;
    Uint16 selector_maxpos;
    Uint16 selector_maxneg;
    Uint16 selector_power;
    Uint16 selector_speed;
    Uint16 selector_trqf;
    Uint16 selector_trqr;

    Uint16 selector_pedal_setup;
    Uint16 ack_pedal_setup;

    int emergencyBrk_active;
    int emergencyBrk_isNotSet;
};

//Logging
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
    Uint16 AMK_Voltage;   //Signed - Raw data for calculating 'actual magnetizing current'Id See 'Units'on page 1
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
    uint16_t max_bms_temp_nslave_shared;
};

struct Power_Log {
    float lem_current_shared;
    float batteryPack_voltage_shared;
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
    float temperatures_shared[8];
    float suspensions_shared[4];
};
struct Pedals_Log{
   float  acc_pot1_shared;
   float  acc_pot2_shared;
   float  brk_pot_shared;
   int brk_req_shared;
   int throttle_req_shared;

   Uint16 acc1_low_calibration;
   Uint16 acc2_low_calibration;
   Uint16 acc1_high_calibration;
   Uint16 acc2_high_calibration;
   Uint16 brk_low_calibration;
   Uint16 brk_high_calibration;
};


struct Gpio_Log{
    Uint16 Imd_shared;
    Uint16 Bms_shared;
    Uint16 Sdc1_shared;
    Uint16 Sdc2_shared;
    Uint16 Sdc3_shared;
    Uint16 Sdc4_shared;
    Uint16 Sdc5_shared;
    Uint16 Sdc6_shared;
};

struct Power_Setup_Log{
    int max_speed_shared;
    float rear_motor_scale_shared;
    float front_motor_scale_shared;
    float power_limit_shared;
};

struct Car_settings{
    //status
    bool lauch_ready;

    //screen
    float presets_power[8];
    float presets_max_pos[5];
    float presets_max_neg[5];
    float presets_regen[6];
    float presets_speed[6];
    float presets_coppie_front[6];
    float presets_coppie_rear[6];

    //setup variables
    float max_regen_current;
    float max_speed;
    float rear_motor_scale;
    float front_motor_scale;
    float max_pos_torque;
    float max_neg_torque;
    float power_limit;
};

struct Share_struct {
    Uint16 Temps[8];
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



void updateValues();
void updatePage(Uint16 page);

void updatePage1();
void updatePage2();
void updatePage3();
void updatePage4();
void updatePage5();
void updatePage6();
void updatePage7();
void updatePage8();
void updatePage9();
void updatePage10();
void updatePage11();
void updatePage12();


void changePreset(Uint16 preset, Uint16 page, Uint16 ack);

void setBMS_voltage();

void setRRstatus();

void setSelectorPowerControl();

void setAckPowerControl();

void setSelectorPedalConfig();

void setAckPedalConfig();

void setSelector1_update();

void setSelector2_update();

void setAckSetup();

float getLowestLvVoltage();

int getMaxTempSmu();

int getMaxTempInv();

int getMaxTempMot();

int getMaxTempIGBT();

#endif /* DISPLAY_H_ */
