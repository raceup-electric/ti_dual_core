#ifndef GLOBAL_DEFINITIONS_H_
#define GLOBAL_DEFINITIONS_H_

/*
 * Here you can find every global variable used in the code,
 * except for pedal variables which are in dirver_input.h.
 * Some variables must be modified accordingly with Powertrain
 * members (so ask them if you are not sure); variables are:
 *      POWER_LIMIT SPEED_LIMIT
 *      REAR_MOTOR_SCALE
 *      FRONT_MOTOR_SCALE
 *      MAX_POS_TORQUE
 *      MAX_NEG_TORQUE
 *      PEAK_REGEN_CURRENT
 *
 */

// TODO chech if it is needed
#define THERMAL_POWER_CTRL    0

/*
 * END OF SUPER IMPORTANT MACROS
 */


#define R_P   0.01898f                          // %pinion radius [m]

#define R2D_BRAKE_TRESHOLD  10


//
// torque
//
#define NUM_OF_MOTORS       4


#define REAR_MOTOR_PERCENTAGE    0.5f  // rear scale fixed to MAX_TORQUE_SCALE
#define FRONT_MOTOR_PERCENTAGE   0.5f  // front scale -> x/(MAX_TORQUE_SCALE + x) = FRONT_MOTOR_SCALE
#define MAX_TORQUE_SCALE 2.14


#define G_ACC               9.81f                   // gravity acceleration [m/s^2]
#define PI_FLOAT            3.14159265f
#define PI                  3.1415926535897932384626433832795
#define TWO_PI              6.283185307179586476925286766559
#define RPM_TO_KMH          RPM_TO_RADS*3.6f*R0*TAU
#define RPM_TO_RADS         (PI/30)

#define THROTTLE_POWER_SCALE        10
#define REG_POWER_SCALE             10

#define SPEED_LIMIT                 18000   // Typical value: 15000
#define M_N                         9.8f

/*
 * AERO
 */
#define CLA                         3.814f                  // lift coefficient*surface, positive downwards (->downforce) [m^2]
#define CDA                         1.098f                  // drag coefficient*surface, positive rearwards [m^2]
// center of pressure coordinates [m^2]; reference system: t/2, w/2; x positive rearwards, z positive upwards
#define CoP_0                       -0.112f
#define CoP_2                       0.115f

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
#define MOTOR_SPEED_UPPER_BOUND     SPEED_LIMIT
#define MOTOR_SPEED_LOWER_BOUND     0
#define FZ_UPPER_BOUND              2000.0f
#define FZ_LOWER_BOUND              0.0f
#define SPEED_UPPER_BOUND           35.0f       //in [m/s]
#define SPEED_LOWER_BOUND           -0.5f

#define TAU                         (1.0f/14.44f)
#define TAU_TC                      14.44f                  // gear unit reduction rate []
#define R0                          0.2032f                 // unloaded radius [m]
#define W                           1.535f                  // wheelbase  [m]
#define MASS                        270.0f                  // total mass (vehicle + driver) [kg]
#define Z_COG                       0.3f                    // center of gravity height [m]
#define zRC_f                       0.01542f                // front roll center height [m]
#define zRC_r                       0.03824f                // rear roll center height [m]
#define T_F                         1.23f                   // track front [m]
#define T_R                         1.2f                    // track rear [m]
#define K_F                         0.5279f
#define K_R                         (1-K_F)
#define C_Z_A                       CLA
#define RHO                         1.225f                  // air density [kg/m^3]
#define A                           W*M_DR                  // front wheels-CoG (longitudinal distance) [m]
#define B                           W*M_DF                  // rear wheels-CoG (longitudinal distance) [m]
#define A_A                         W/2+CoP_0+CoP_2*CDA/CLA   // front wheels-CoP (longitudinal distance) [m]
#define B_A                         W - A_A                 // rear wheels-CoP (longitudinal distance) [m]
#define AX0                         0.5f                    // vehicle longitudinal acceleration threshold [m/s^2]
#define TOE_F                       0.f                     // toe front: positive if toe IN [rad]
#define TOE_R                       0.f                     // toe rear: positive if toe IN [rad]
#define T_MAX_HC                    26.0f

#define M_DF                        0.436f                   // mass distribution (front mass/total mass) []
#define M_DR                        1 - M_DF                // mass distribution (rear mass/total mass) []

#define k_sf                        61294.f                 // spring stiffness [N/m]
#define k_sr                        61294.f                 // spring stiffness [N/m]
#define k_ARBf                      192940.f                // front ARB stiffness [N/m]
#define k_ARBr                      253740.f                // rear ARB stiffness [N/m]
#define MR_sf                       1.14f                   // front spring motion ratio (dz_wheel/dl_sf) []
#define MR_sr                       1.18f                  // rear spring motion ratio (dz_wheel/dl_sr) []
#define MR_ARBf                     1.7f                   // front ARB motion ratio (dz_wheel/dl_ARBf) []
#define MR_ARBr                     1.6f                  // rear ARB motion ratio (dz_wheel/dl_ARBr) []

#define k_t                         122414.f                // tire stiffness at 150lbs on 8in rim [N/m]

#define kr_wf                       k_sf/(MR_sf*MR_sf) + k_ARBf/(MR_ARBf*MR_ARBf)    // front wheel stiffness in roll [N/m]
#define kr_wr                       k_sr/(MR_sr*MR_sr) + k_ARBr/(MR_ARBr*MR_ARBr)    // rear wheel stiffness in roll [N/m]

#define kr_rf                       kr_wf*k_t/(kr_wf+k_t)   // front ride rate in roll [N/m]
#define kr_rr                       kr_wr*k_t/(kr_wr+k_t)   // rear ride rate in roll [N/m]

#define kr_f                        (kr_rf*T_F*T_F/2.f)     // front roll stiffness (hp: left=right) [Nm]
#define kr_r                        (kr_rr*T_R*T_R/2.f)     // rear roll stiffness (hp: left=right) [Nm]

#define max_I_pos                   0.75f                   // max positive integral term in PID controller []
#define max_I_neg                   max_I_pos               // max negative integral term in PID controller []

#define S_MAX         0.12f
#define S_MIN         -0.12f
#define I_POS          0.0005f
#define P_POS          0.1f
#define D_POS          0.03f
#define I_NEG          I_POS
#define P_NEG          P_POS
#define D_NEG          D_POS

//Constants of TorqueLimit1
#define NU1                         1.7977585706847f;
#define NU2                         0.000387300865455914f;
#define NU3                         -3.14517395274217E-06;
#define NU4                          4.6481093251002E-09;
#define NU5                         -3.5206874715397E-12;
#define NU6                         1.31537731918249E-15;

#define ALPHA0                     1.f;
#define ALPHA1                     0.f;
#define ALPHA2                     -21.4167f;
#define ALPHA3                     0.f;
#define ALPHA4                     291.6667f;
#define ALPHA5                     0.f;

#define MAX_POS_TORQUE              15.f
#define MAX_NEG_TORQUE              -12.f

#define PEAK_REGEN_CURRENT           150.0f           //E' GIUSTO IL SEGNO POSITIVO!!!!
#define TORQUE_VECTORING            0
/*
 * POWER CONTROL
 */
#define POWER_LIMIT         35000.0f       //Watt
#define STANDARD_SPEED      1000.0f
#define KP_PI               0.05f
#define KI_PI               10.0f
#define T_SAMPLING_ECU      0.010f                          // sample period [s]
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
#define ACQPS_                   240

/*
 * CAN MANAGEMENT
 * Recall: mailboxes are just memory location where certain can messages depending on the id are sent.
 * So, mailbox number is independent from message ID. It's up to the programmer to choose which messages are sent
 * in a specific mailbox.
 * Note: mailboxes after 28 are usually problematic, try to avoid them.
 */


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
#define OBJ_ID_CAR_INFOS        19
#define OBJ_ID_PADDLE_SW           25
#define OBJ_ID_FROM_LEM         21
#define OBJ_ID_FROM_IMU         22
#define OBJ_ID_TO_PCU        23
#define OBJ_ID_MAP_SW    20
#define OBJ_ID_FROM_AMK         26
//alberto patch
#define OBJ_ID_FROM_ATC_TBS             27 
#define OBJ_ID_FROM_ATC_SUSPS           28
#define OBJ_ID_FROM_ATC_TEMPS           29
#define OBJ_ID_SETSTART                 30


// -- Message IDs --
// -- CAN2 --
#define MSG_ID_ATC_TBS                  0x053

#define MSG_ID_PADDLE_SW    0X52

#define MSG_ID_BMS_LV_1         0x54
#define MSG_ID_BMS_LV_2         0x55

#define MSG_ID_BMS_VOLTAGE                   0x57
#define MSG_ID_BMS_TEMP                      0x58

#define MSG_ID_IMU_1            0x60
#define MSG_ID_IMU_2            0x61
#define MSG_ID_IMU_3            0x62
// 0x63 must be free for IMU mask


#define MSG_ID_MAP_SW    0X64

#define MSG_ID_CAR_STATUS                    0x65
#define MSG_ID_CAR_SETTINGS                  0x66

#define MSG_ID_SET_START              0x70 //receive "set start position"

#define MSG_ID_SMU_BASE                      0x100
#define MSG_ID_SMU_TEMPERATURES              0x100
#define MSG_ID_SMU_SUSPENSIONS               0x102  // rear
// 0x103 must be free for SMU mask


#define MSG_ID_ATC_SUSPS                0x104   // front
#define MSG_ID_ATC_TEMPS                0x105

#define MSG_ID_HOST_SEND                     0x120
#define MSG_ID_TO_PCU                        0x130

#define MSG_ID_LEM                           0x3C2

// --- CAN1 ----
#define MSG_ID_AMK_SETPOINTS    0x82
#define MSG_ID_STEERING_WHEEL_BASE 0x90
#define MSG_ID_STEERING_WHEEL_DISPLAY_PAGE   0x90   //buttons ID
#define MSG_ID_STEERING_WHEEL_CHANGE_SETUP   0x91
#define MSG_ID_STEERING_WHEEL_CHANGE_SETUP_2         0x92








#define IMD_STATE           3      //PIN37     //INPUT
#define BMS_STATE           2      //PIN38    //INPUT
#define AIR_1_STATE         1      //PIN39     //INPUT
#define AIR_2_STATE         0      //PIN40     //INPUT
#define RTDS                6      //PIN80

#define R2D                 25       //PIN51
#define BRAKE_LIGHT_Abil    27      //PIN52

#define DEBUG_LED1          105     //PIN9
#define DEBUG_LED2          104     //PIN10

#define R2D_LED_OFF          0
#define R2D_LED_ON           1U      //GPIO ALTA -> LED ACCESO       GPIO BASSA -> LED SPENTO

#define RTDS_DURATION       15      //*100ms
#define BRAKE_LIGHT_ON      1U
#define BRAKE_LIGHT_OFF     0
#define BLUE_BLINK          31

#define SCS 19               // PIN61
#define SCS_ON 1U            // CONST ON
#define SCS_OFF 0            // CONST ON

//
// misc
//
#define BRAKE_LIGHT_MIN                 5   //valore minimo di brake per attivare la brake light


/*
 * KALMAN
 */

// linear gain [m/N] in Re = R0 - k_Re*Fz 
// defined from FSAE TTC Round 8 data (Free Rolling)
// of RE, by using the function polyfix,
// that is polyfit but forcing Re(Fz=0) == R0
#define k_Re            9.33e-06f
#define SMALL_R0        0.0349f             // yaw rate threshold [rad/s]
#define SIGMA_W2        1.5f
#define SIGMA_W1        7.f

#endif

