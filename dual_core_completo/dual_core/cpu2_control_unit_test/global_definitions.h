#ifndef GLOBAL_DEFINITIONS_H_
#define GLOBAL_DEFINITIONS_H_

/*
 * Here you can find every global variable used in the code,
 * except for pedal variables which are in dirver_input.h.
 * Some variables must be modified accordingly with Powertrain
 * members (so ask them if you are not sure); variables are:
 *      SPEED_LIMIT
 *      REAR_MOTOR_SCALE
 *      FRONT_MOTOR_SCALE
 *      MAX_POS_TORQUE
 *      MAX_NEG_TORQUE
 *      MAX_REGEN_CURRENT
 *
 */

/*
 * SUPER IMPORTANT MACROS
 */
#define ONE_PEDAL   0
#define REG_BRAKE   0
#define TORQUE_VECTORING    0
#define TRACTION_CTRL   0
#define THERMAL_POWER_CTRL    0

/*
 * END OF SUPER IMPORTANT MACROS
 */


#define R_P   0.00949
#define Atraction     0.84425
#define Btraction     0.69075
#define S_MAX         0.1
#define S_MIN         -0.12

#define R2D_BRAKE_TRESHOLD  10

#define FIFTEEN_SEC   15 * 1000 * 1000

//
// torque
//
#define NUM_OF_MOTORS       4
#define KMH2MS              (1 / 3.6)

/*
 * REAR_MOTOR_SCALE and FRONT_MOTOR_SCALE are the values used when TV is disabled
 * Be careful when you set them, always ask powertrain department
 */
#define REAR_MOTOR_SCALE    1.8f
#define FRONT_MOTOR_SCALE   0.65f

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
#define SPEED_LIMIT                 18000   // Typical value: 15000
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
#define FZR                         78.0f
#define FZF                         63.0f
#define W                           1.535f
#define MASS                        282.0f
#define Z_G                         0.3f
#define T_F                         1.23f
#define T_R                         1.2f
#define K_F                         0.4775f
#define K_R                         (1-K_F)
#define C_Z_A                       3.94f
#define RHO                         1.25f
#define A_A                         1.087f
#define AX0                         0.5f
#define TOE_F                       0.f
#define TOE_R                       0.f

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

#define MAX_POS_TORQUE              17.0f
#define MAX_NEG_TORQUE              -7.0f

#define MAX_REGEN_CURRENT           30.0f           //E' GIUSTO IL SEGNO POSITIVO!!!!


/*
 * POWER CONTROL
 */
#define POWER_LIMIT         45000.0f       //Watt
#define STANDARD_SPEED      1000.0f
#define KP_PI               0.05f
#define KI_PI               10.0f
#define T_SAMPLING_ECU      0.010f       //seconds
#define PI_UPPER_BOUND      175929.2f

#define K1_THERMAL          0.3
#define K2_THERMAL          0.00002
#define K3_THERMAL          600
#define T_MAX               35
#define T_MIN               29

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

/*
 * CAN MANAGEMENT
 * Recall: mailboxes are just memory location where certain can messages depending on the id are sent.
 * So, mailbox number is independent from message ID. It's up to the programmer to choose which messages are sent
 * in a specific mailbox.
 * Note: mailboxes after 28 are usually problematic, try to avoid them.
 */
#define RX_OBJ_ID               1       //ID della "mailbox"
#define TX_OBJ_ID               2

#define MSG_DATA_LENGTH         8

//Used Mailboxes
#define OBJ_ID_FROM_SMU         7
#define TX_OBJ_TO_HOST          8
#define OBJ_ID_STEERING_WHEEL   9
#define OBJ_ID_BMS_VOLTAGE      10
#define OBJ_ID_BMS_TEMP         11
#define TX_OBJ_AMK_SETPOINTS    14
/*
 * 15, 16, 17 are occupied by AMK, DO NOT USE THEM!!!
 */
#define OBJ_ID_FROM_BMS_LV      18
#define OBJ_ID_FROM_LEM         21
#define OBJ_ID_FROM_IMU         22
#define OBJ_ID_TO_ATMEGA        23
#define OBJ_ID_POWER_CONTROL    25
#define OBJ_ID_FROM_AMK         26


//Message IDs
#define MSG_ID_CALIBRATION_TO_SMU 0x30
#define MSG_ID_AMK1_DATA_BASE   0x40
#define MSG_ID_AMK2_DATA_BASE   0x44
#define MSG_ID_TEMPS            0x49
#define MSG_ID_CAR_STATUS       0x52
#define MSG_ID_BMS_BASE         0x55
#define MSG_ID_BMS_LV_1         0x55
#define MSG_ID_BMS_LV_2         0x56
#define MSG_ID_IMU_BASE         0x60
#define MSG_ID_IMU_1            0x60
#define MSG_ID_IMU_2            0x61
#define MSG_ID_IMU_3            0x62
#define MSG_ID_POWER_CONTROL    0X81
#define MSG_ID_AMK_SETPOINTS    0x82
#define MSG_ID_STEERING_WHEEL_BASE 0x90
#define MSG_ID_STEERING_WHEEL_DISPLAY_PAGE   0x90   //buttons ID
#define MSG_ID_STEERING_WHEEL_CHANGE_SETUP   0x91
#define MSG_ID_STEERING_WHEEL_CHANGE_SETUP_2         0x92
#define MSG_ID_SMU_BASE                      0x100
#define MSG_ID_SMU_TEMPERATURES              0x100
#define MSG_ID_SMU_SUSPENSIONS               0x102
#define MSG_ID_BMS_VOLTAGE                   0x110
#define MSG_ID_BMS_TEMP                      0x111
#define MSG_ID_HOST_SEND                     0x120
#define MSG_ID_TO_ATMEGA                     0x130
#define MSG_ID_LEM                           0x3C2


//SCHERMO
#define MAX_PAGE_NUMBER     14
#define MAX_DRIVING_PAGE    2

#define CONFIRMATION        0x1
#define NEXT_PAGE           0x2
#define CALIBRATION         0x3//TO REVIEW
#define PREVIOUS_PAGE       0x4
#define START_LAUNCH        0x8

#define SETUP_PAGE          0x08
#define PEDAL_SETUP_PAGE    0x09
#define MACROS_PAGE         0x0A
#define FANSPEED_PAGE       0x0D


/*
 * In SCREEN_DEBUG mode we use every page
 * In SCREEN_DRIVING mode we use only the last pages.
 * MAX_DRIVING_PAGE defines the number of pages used in SCREEN_DRIVING mode
 */
#define SCREEN_DEBUG        0x00
#define SCREEN_DRIVING      0x01
#define CHANGE_SCREEN_MODE  0x09

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


/*
 * KALMAN
 */

#define SMALL_R0        0.0349f
#define SIGMA_W2        1.5f
#define SIGMA_W1        7.f

#endif
