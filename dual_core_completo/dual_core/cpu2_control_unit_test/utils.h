#ifndef UTILS_H
#define UTILS_H

//
// include
//
#include "motor_management.h"

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
    Uint16 AMK_Voltage;   //unSigned - Raw data for calculating 'actual dc_bus voltage
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

struct Pedals_Log{
   float  acc_pot1_shared;
   float  acc_pot2_shared;
   float  brk_pot_shared;
   int brk_req_shared;
   int throttle_req_shared;
};
struct BMS_Log {
    float max_bms_voltage_shared;
    float min_bms_voltage_shared;
    float mean_bms_voltage_shared;
    float max_bms_temp_shared;
    float min_bms_temp_shared;
    float mean_bms_temp_shared;
};
//Sendyne Deprecated
/*struct Sendyne_Log {
    float sendyne_current_shared;
    float sendyne_voltage_shared;
    float curr_sens_shared;
    float total_power_shared;
};*/
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

struct Display_command{
    Uint16 page;
    Uint16 selector_p;
    Uint16 ack_p; //non è un bool, ma il valore della selezione 0-7
    Uint16 selector_r;
    Uint16 ack_r; //non è un bool, ma il valore della selezione 0-7
    Uint16 selector_speed;
    Uint16 ack_speed; //non è un bool, ma il valore della selezione 0-7
    Uint16 selector_coppie_rear;
    Uint16 ack_coppie_rear; //non è un bool, ma il valore della selezione 0-7
    Uint16 selector_coppie_front;
    Uint16 ack_coppie_front; //non è un bool, ma il valore della selezione 0-7

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

};

extern float versx[3];
extern float versy[3];
extern float versz[3];
extern float V[3][3];


//
// prototypes
//

float convertBMSvoltage(Uint16 voltage);

float convertBMStemp(Uint16 temp);

float changeRange(float val, float minX, float maxX, float newMinX, float newMaxX);

Uint16 saturateUnsigned(Uint16 signal, Uint16 upperBound, Uint16 lowerBound);

float saturateFloat(float signal, float upperBound, float lowerBound);

float saturateInt(int signal, int upperBound, int lowerBound);

float torqueSetpointToNM(int setpoint);

int NMtoTorqueSetpoint(float torqueNM);

float convert_temp_lv(float cell_volt);

float ConvertTempToKelvin(int adc_read);

//void debugLight(int period);

float uint32_to_float(Uint32 u);

void send_calibration(float V[3][3]);
void imu_calibration_1(float accelerations[3]);
void imu_calibration_2(float accelerations[3]);

#endif
