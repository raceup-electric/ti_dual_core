#ifndef GLOBAL_DEFINITIONS_H_
#define GLOBAL_DEFINITIONS_H_


#define R2D_BRAKE_TRESHOLD  10

#define FIFTEEN_SEC   15 * 1000 * 1000

//
// torque
//
#define NUM_OF_MOTORS       4
#define KMH2MS              (1 / 3.6)
#ifdef NO_TORQUE_VECTORING
#define REAR_MOTOR_SCALE    1.8f
#define FRONT_MOTOR_SCALE   0.65f
#else
#define REAR_MOTOR_SCALE    1.0f
#define FRONT_MOTOR_SCALE   1.0f
#endif
#define STZ_RANGE           90

#define G_ACC               9.81f
#define PI_FLOAT            3.14159265f
#define HALF_PI             1.5707963267948966192313216916398
#define PI                  3.1415926535897932384626433832795
#define TWO_PI              6.283185307179586476925286766559
#define DEG_TO_RAD          0.017453292519943295769236907684886
#define KMH2MS              (1 / 3.6)
#define RAD_TO_DEG          57.295779513082320876798154814105
#define RPM_TO_KMH          (TWO_PI*0.00095)
#define RPM_TO_RADS         (PI/30)

#define THROTTLE_POWER_SCALE        10
#define REG_POWER_SCALE             0

#define REGENERATIVE_BRAKE_LIMIT    75     //Regenerative brake position limit
#define NEGATIVE_TORQUE_LIMIT       -21       //% of M_N
#define SPEED_LIMIT                 14000 //15000               //Speed limit
#define M_N                         9.8f

//
// PERFORMANCE PACK
//
#define ACC_X_UPPER_BOUND           1.8f*G_ACC
#define ACC_X_LOWER_BOUND           -2.1f*G_ACC
#define ACC_Y_UPPER_BOUND           2.6f*G_ACC
#define ACC_Y_LOWER_BOUND           -2.6f*G_ACC
#define YAW_R_UPPER_BOUND           2.0*PI_FLOAT
#define YAW_R_LOWER_BOUND           -2.0*PI_FLOAT
#define STR_UPPER_BOUND             90
#define STR_LOWER_BOUND             -90
#define MOTOR_SPEED_UPPER_BOUND     18000
#define MOTOR_SPEED_LOWER_BOUND     0
#define FZ_UPPER_BOUND              2000.0f
#define FZ_LOWER_BOUND              50.0f

#define TAU                         (1.0f/14.4f)
#define K_DELTA                     0.2776853f
#define R0                          0.228f
#define FZR                         75.0f
#define FZF                         60.0f
#define W                           1.535f
#define MASS                        270.0f
#define Z_G                         0.3f
#define T_F                         1.23f
#define T_R                         1.2f
#define K_F                         0.53f
#define K_R                         (1-K_F)
#define C_Z_A                       3.94f
#define RHO                         1.1352f
#define A_A                         1.087f

//Constants of TorqueLimit1
#define NU1                         1.7977585706847f;
#define NU2                         0.000387300865455914f;
#define NU3                         -3.14517395274217E-06;
#define NU4                          4.6481093251002E-09;
#define NU5                         -3.5206874715397E-12;
#define NU6                         1.31537731918249E-15;
#define ALPHA0                      1.0f;
#define ALPHA1                      0.000387300865455914f;
#define ALPHA2                      -3.14517395274217E-06;
#define ALPHA3                      4.64810932510023E-09;
#define ALPHA4                      -3.5206874715397E-12;
#define ALPHA5                      1.31537731918249E-15;

#define MAX_POS_TORQUE              12.0f
#define MAX_NEG_TORQUE              -7.0f

#define MAX_REGEN_CURRENT           30.0f           //E' GIUSTO IL SEGNO POSITIVO!!!!!!!! xd RIcjy
//

// POWER CONTROL
//
#define POWER_LIMIT         30000.0f       //Watt
#define STANDARD_SPEED      1000.0f
#define KP_PI               0.05f
#define KI_PI               10.0f
#define T_SAMPLING_ECU      0.010f       //seconds
#define PI_UPPER_BOUND      175929.2f

//
// IMU
//
#define X                   0
#define Y                   1
#define Z                   2


//
// motor management
//
#define MOTOR_FL 0
#define MOTOR_FR 1
#define MOTOR_RL 2
#define MOTOR_RR 3

#define AMK_CURR_SCALE (107.2f / 16384.0f)

#define FORWARD_ACC 0
#define COASTING    1
#define BRAKES_POS  2
#define BRAKES_NEG  3
#define REVERSE_ACC 4

#define RF_TRAP                 50      //*10 ms
#define HV_TRAP                 50

//
// adc management
//
#define RESULTS_BUFFER_SIZE     256
#define EX_ADC_RESOLUTION       12
#define ACQPS_                   240
#define VREFLO                  0
#define VREFHI                  3.3

//
// can management
//
#define RX_OBJ_ID               1       //ID della "mailbox"
#define TX_OBJ_ID               2

#define MSG_DATA_LENGTH         8

//Used Mailboxes
#define TX_OBJ_TO_HOST          8
#define OBJ_ID_STEERING_WHEEL   9
#define OBJ_ID_BMS_VOLTAGE      10
#define OBJ_ID_BMS_TEMP         11
#define TX_OBJ_AMK_SETPOINTS    14      //Occupa da 14 a 14 + motorIndex = 17
#define OBJ_ID_FROM_BMS_LV      18
#define OBJ_ID_FROM_LEM         21
#define OBJ_ID_FROM_IMU         22
#define OBJ_ID_POWER_CONTROL    25
#define OBJ_ID_FROM_AMK         26
#define OBJ_ID_FROM_SENDYNE     27
#define OBJ_ID_FROM_SMU         28






//Message IDs
#define MSG_ID_CALIBRATION_TO_SMU 0x30
#define MSG_ID_AMK1_DATA_BASE   0x40
#define MSG_ID_AMK2_DATA_BASE   0x44
#define MSG_ID_TEMPS            0x49
#define MSG_ID_SENDYNE          0x50
#define MSG_ID_CAR_STATUS       0x52
#define MSG_ID_BMS_BASE         0x55
#define MSG_ID_BMS_LV_1         0x55
#define MSG_ID_BMS_LV_2         0x56
#define MSG_ID_IMU_BASE         0x60
#define MSG_ID_IMU_1            0x60
#define MSG_ID_IMU_2            0x61
#define MSG_ID_IMU_3            0x62
#define MSG_ID_SENDYNE_FORWARD  0x70
#define MSG_ID_POWER_CONTROL    0X81
#define MSG_ID_AMK_SETPOINTS    0x82
#define MSG_ID_STEERING_WHEEL_BASE 0x90         //id dei buttons
#define MSG_ID_STEERING_WHEEL_DISPLAY_PAGE   0x90
#define MSG_ID_STEERING_WHEEL_CHANGE_SETUP   0x91   //id del selector
#define MSG_ID_SMU_BASE                      0x100
#define MSG_ID_SMU_TEMPERATURES              0x100
#define MSG_ID_SMU_SUSPENSIONS               0x101
#define MSG_ID_BMS_VOLTAGE                   0x110
#define MSG_ID_BMS_TEMP                      0x111
#define MSG_ID_HOST_SEND                     0x120
#define MSG_ID_LEM                           0x3C2


//SCHERMO
#define MAX_PAGE_NUMBER     17

#define CONFIRMATION        0x1
#define NEXT_PAGE           0x2
#define CALIBRATION         0x3//TO REVIEW
#define PREVIOUS_PAGE       0x4
#define START_LAUNCH        0x8

#define POWER_CONTROL_PAGE   0x08
#define REGEN_PAGE          0x09
#define SPEED_LIMIT_PAGE     0x0E
#define COPPIE_PAGE_FRONT    0x0F
#define COPPIE_PAGE_REAR     0x10
#define BRAKE_PAGE          0x11

//
// ePWM
//
#define EPWM_CMP_UP             1U
#define EPWM_CMP_DOWN           0U
#define EPWM_TIMER_TBPRD        2000U       //più basso il numero, più alta la frequenza
                                            //vedi la guida per calcolare la frequenza
#define VENTOLA_DX              1
#define VENTOLA_SX              2
#define POMPA_DX                3
#define POMPA_SX                4

//Temp ventole accensione
#define FAN_MAX_TEMP 60
#define FAN_MIN_TEMP 50
#define FAN_THRESHOLD 5

#define IMD_STATE           14      //PIN74     //INPUT
#define BMS_STATE           15      //PIN73     //INPUT

#define ENABLE_PUMPS        94      //PIN45
#define VENTOLA_Abil         97      //PIN46
#define AIR_1_STATE         40      //PIN50     //INPUT
#define AIR_2_STATE         41      //PIN49     //INPUT
#define RTDS                27      //PIN52
#define SCS_FAULT           11      //PIN75
#define R2D                 6       //PIN80
#define BRAKE_LIGHT_Abil    25      //PIN51
#define SDC1_STATE          26      //PIN53     //INPUT
#define SDC2_STATE          130     //PIN57     //INPUT
#define SDC3_STATE          64      //PIN54     //INPUT
#define SDC4_STATE          131     //PIN58     //INPUT
#define SDC5_STATE          63      //PIN55     //INPUT
#define SDC6_STATE          66      //PIN59     //INPUT
#define DEBUG_LED1          105     //PIN9
#define DEBUG_LED2          104     //PIN10

#define R2D_LED_OFF          0
#define R2D_LED_ON           1U      //GPIO ALTA -> LED ACCESO       GPIO BASSA -> LED SPENSO

#define RTDS_DURATION       15      //*100ms

#define BRAKE_LIGHT_ON      1U
#define BRAKE_LIGHT_OFF     0

#define RED_BLINK           34
#define BLUE_BLINK          31
//
// misc
//
#define BRAKE_LIGHT_MIN                 5   //valore minimo di brake per attivare la brake light


#endif
