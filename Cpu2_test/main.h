
#include "driverlib.h"
#include "device.h"
#include "F2837xD_Ipc_drivers.h"

//statusStruct
struct StatStruct {
        uint8_t throttle;
        uint8_t steering;
        uint8_t steeringShift;
        uint8_t brake;
        uint8_t brkPress;
        uint8_t status;
        uint8_t actualVelocityKMH;
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

//MegaStruct
struct AllData {
    //IMU
    float acc[3];
    float omegas[3];


    //StatStruct
    struct StatStruct s;

    //Temps
    uint8_t temps[8];

    //SetPoints
    struct motorSetPoints motorSetPoints[4];

    //Sendyne
    uint8_t sendyneValues[8];

    //Motors
    struct motorValues1 motorValues1[4];
    struct motorValues2 motorValues2[4];
};


