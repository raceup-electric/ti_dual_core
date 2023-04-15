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
extern Uint16 n_setup;
extern Uint16 ack;

extern Uint16 old_setup_power;
extern Uint16 old_setup_regen;
extern Uint16 old_ack_power;
extern Uint16 old_ack_regen;

extern Uint16 old_setup_speed;
extern Uint16 old_setup_coppia_front;
extern Uint16 old_setup_coppia_rear;

extern Uint16 old_ack_speed;
extern Uint16 old_ack_coppia_front;
extern Uint16 old_ack_coppia_rear;

struct Display_command{
    Uint16 page;
    Uint16 selector_p;
    Uint16 ack_p; //non � un bool, ma il valore della selezione 0-7
    Uint16 selector_r;
    Uint16 ack_r; //non � un bool, ma il valore della selezione 0-7
    Uint16 selector_speed;
    Uint16 ack_speed; //non � un bool, ma il valore della selezione 0-7
    Uint16 selector_coppie_rear;
    Uint16 ack_coppie_rear; //non � un bool, ma il valore della selezione 0-7
    Uint16 selector_coppie_front;
    Uint16 ack_coppie_front; //non � un bool, ma il valore della selezione 0-7
    //Handle of emergency brake screen
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
    float AMK_TempMotor;                //Signed - Unit: 0.1 �C - Motor temperature
    float AMK_TempInverter;             //Signed - Unit: 0.1 �C - Cold plate temperature
    float AMK_TempIGBT;                 //Signed - Unit: 0.1 �C - IGBTtemperature
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
    bool lauch_ready;
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
    struct Car_settings settings;
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
void updatePage13();
void updatePage14();
void updatePage15();
void updatePage16();
void updatePage17();



void changePreset(Uint16 preset, Uint16 page, Uint16 ack);

void setBMS_voltage();

void setRRstatus();

void setSelectorPowerControl();

void setAckPowerControl();

void setSelectorRegen();

void setAckRegen();

void setSelectorSpeed();

void setAckSpeed();

void setSelectorCoppiaFront();

void setAckCoppiaFront();

void setSelectorCoppiaRear();

void setAckCoppiaRear();

float getLowestLvVoltage();

int getMaxTempSmu();

int getMaxTempInv();

int getMaxTempMot();

int getMaxTempIGBT();

#endif /* DISPLAY_H_ */
