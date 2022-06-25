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

struct Display_command{
    Uint16 page;
    Uint16 selector_p;
    Uint16 ack_p; //non è un bool, ma il valore della selezione 0-7
    Uint16 selector_r;
    Uint16 ack_r; //non è un bool, ma il valore della selezione 0-7
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
    float temperatures_shared[5];
    float suspensions_shared[4];
};

struct Gpio_Log{
    bool Imd_shared;
    bool Bms_shared;
    bool Sdc1_shared;
    bool Sdc2_shared;
    bool Sdc3_shared;
    bool Sdc4_shared;
    bool Sdc5_shared;
    bool Sdc6_shared;
};

struct Share_struct {
    Uint16 Temps[8];
    float bms_lv_cell[8];
    struct motorValues1 motorVal1[4];
    struct motorValues2 motorVal2[4];
    struct motorSetPoints motorSetP[4];
    struct Imu_Log imu;
    struct FanSpeed_Log fanSpeed;
    struct Sendyne_Log sendyne;
    struct BMS_Log bms;
    struct Status_Log status;
    struct Gpio_Log gpio;
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



void changePreset(Uint16 preset, Uint16 page, Uint16 ack);


void setAMK_fl();

void setAMK_fr();

void setAMK_rl();

void setAMK_rr();

void setTemps();

void setBMS_voltage();

void setFLstatus();

void setFRstatus();

void setRLstatus();

void setRRstatus();

void setSelectorPowerControl();

void setAckPowerControl();

void setSelectorRegen();

void setAckRegen();

#endif /* DISPLAY_H_ */
