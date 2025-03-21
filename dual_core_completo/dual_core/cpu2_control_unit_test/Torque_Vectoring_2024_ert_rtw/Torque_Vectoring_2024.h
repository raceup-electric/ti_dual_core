/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024.h
 *
 * Code generated for Simulink model 'Torque_Vectoring_2024'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Mar 21 11:48:46 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Torque_Vectoring_2024_h_
#define RTW_HEADER_Torque_Vectoring_2024_h_
#ifndef Torque_Vectoring_2024_COMMON_INCLUDES_
#define Torque_Vectoring_2024_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                              /* Torque_Vectoring_2024_COMMON_INCLUDES_ */

#include "Torque_Vectoring_2024_types.h"
#include <stddef.h>
#include <string.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T u;                            /* '<S110>/Integrator' */
  real_T u_m;                          /* '<S210>/Integrator' */
  real_T u_a;                          /* '<S60>/Integrator' */
  real_T u_g;                          /* '<S160>/Integrator' */
  real_T Memory_PreviousInput[4];      /* '<S12>/Memory' */
  real_T Divide_DWORK4;                /* '<S12>/Divide' */
  real_T Memory_PreviousInput_h[4];    /* '<S19>/Memory' */
  real_T Memory_PreviousInput_k;       /* '<Root>/Memory' */
  real_T Memory1_PreviousInput[2];     /* '<S3>/Memory1' */
  real_T Memory2_PreviousInput[2];     /* '<S3>/Memory2' */
  real32_T Memory4_PreviousInput;      /* '<S3>/Memory4' */
} DW_Torque_Vectoring_2024_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ax;                           /* '<Root>/ax' */
  real_T ay;                           /* '<Root>/ay' */
  real32_T yaw_r;                      /* '<Root>/yaw_r' */
  real32_T throttle;                   /* '<Root>/throttle' */
  real32_T regenpaddle;                /* '<Root>/regen paddle' */
  real32_T brakepressurefront;         /* '<Root>/brake pressure front' */
  real32_T brakepressurerear;          /* '<Root>/brake pressure rear' */
  real32_T steering;                   /* '<Root>/steering' */
  real32_T rpm;                        /* '<Root>/rpm' */
  real32_T voltage;                    /* '<Root>/voltage' */
} ExtU_Torque_Vectoring_2024_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T T_pos[4];                     /* '<Root>/T_pos' */
  real_T T_neg[4];                     /* '<Root>/T_neg' */
  real_T TC_CUT[4];                    /* '<Root>/TC_CUT' */
  real_T lambda[4];                    /* '<Root>/lambda' */
  real_T vx_est;                       /* '<Root>/vx_est' */
  real_T wR[4];                        /* '<Root>/wR' */
} ExtY_Torque_Vectoring_2024_T;

/* Parameters (default storage) */
struct P_Torque_Vectoring_2024_T_ {
  real_T CLA1;                          /* Variable: CLA
                                        * Referenced by: '<S9>/Fl'
                                        */
  real_T FZ0;                          /* Variable: FZ0
                                        * Referenced by:
                                        *   '<S1>/Constant1'
                                        *   '<S1>/Gain'
                                        *   '<S1>/Gain1'
                                        */
  real_T PDX1;                         /* Variable: PDX1
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T PDX2;                         /* Variable: PDX2
                                        * Referenced by:
                                        *   '<S1>/Gain'
                                        *   '<S1>/Gain1'
                                        */
  real_T Pmax;                         /* Variable: Pmax
                                        * Referenced by: '<S20>/Total Power Limit'
                                        */
  real_T Q[4];                         /* Variable: Q
                                        * Referenced by: '<S12>/Constant7'
                                        */
  real_T R1;                            /* Variable: R
                                        * Referenced by: '<S12>/Constant5'
                                        */
  real_T R01;                           /* Variable: R0
                                        * Referenced by:
                                        *   '<S5>/Constant'
                                        *   '<S5>/Saturation'
                                        */
  real_T TC_CL_I_R;                    /* Variable: TC_CL_I_R
                                        * Referenced by:
                                        *   '<S57>/Integral Gain'
                                        *   '<S107>/Integral Gain'
                                        *   '<S157>/Integral Gain'
                                        *   '<S207>/Integral Gain'
                                        */
  real_T TC_CL_P_R;                    /* Variable: TC_CL_P_R
                                        * Referenced by:
                                        *   '<S65>/Proportional Gain'
                                        *   '<S115>/Proportional Gain'
                                        *   '<S165>/Proportional Gain'
                                        *   '<S215>/Proportional Gain'
                                        */
  real_T TC_CL_TARGET_SLIP_F;          /* Variable: TC_CL_TARGET_SLIP_F
                                        * Referenced by: '<S21>/Desired slip front1'
                                        */
  real_T TC_CL_TARGET_SLIP_R;          /* Variable: TC_CL_TARGET_SLIP_R
                                        * Referenced by: '<S21>/Desired slip rear1'
                                        */
  real_T TC_MAX_CUT;                   /* Variable: TC_MAX_CUT
                                        * Referenced by: '<S21>/Constant'
                                        */
  real_T TC_VX_ON_F;                   /* Variable: TC_VX_ON_F
                                        * Referenced by: '<S22>/Constant3'
                                        */
  real_T TC_VX_ON_R;                   /* Variable: TC_VX_ON_R
                                        * Referenced by: '<S22>/Constant2'
                                        */
  real_T T_max;                        /* Variable: T_max
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T a;                            /* Variable: a
                                        * Referenced by:
                                        *   '<S9>/Constant1'
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real_T a_a;                          /* Variable: a_a
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T ax0;                          /* Variable: ax0
                                        * Referenced by:
                                        *   '<S16>/Constant'
                                        *   '<S17>/Constant'
                                        *   '<S18>/Constant'
                                        */
  real_T b;                            /* Variable: b
                                        * Referenced by:
                                        *   '<S9>/Constant'
                                        *   '<S9>/Gain3'
                                        */
  real_T b_a;                          /* Variable: b_a
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real_T g;                            /* Variable: g
                                        * Referenced by:
                                        *   '<Root>/Saturation'
                                        *   '<Root>/Saturation1'
                                        *   '<S9>/Constant'
                                        *   '<S9>/Constant1'
                                        */
  real_T k_Re1;                         /* Variable: k_Re
                                        * Referenced by: '<S5>/Gain2'
                                        */
  real_T kr_f1;                         /* Variable: kr_f
                                        * Referenced by:
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real_T kr_r1;                         /* Variable: kr_r
                                        * Referenced by:
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real_T m;                            /* Variable: m
                                        * Referenced by:
                                        *   '<S9>/Constant'
                                        *   '<S9>/Constant1'
                                        *   '<S9>/Gain2'
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real_T mu_00;                        /* Variable: mu_00
                                        * Referenced by: '<S8>/Constant7'
                                        */
  real_T mu_01;                        /* Variable: mu_01
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T mu_02;                        /* Variable: mu_02
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real_T mu_03;                        /* Variable: mu_03
                                        * Referenced by: '<S8>/Gain2'
                                        */
  real_T mu_04;                        /* Variable: mu_04
                                        * Referenced by: '<S8>/Gain3'
                                        */
  real_T mu_05;                        /* Variable: mu_05
                                        * Referenced by: '<S8>/Gain4'
                                        */
  real_T mu_06;                        /* Variable: mu_06
                                        * Referenced by: '<S8>/Gain5'
                                        */
  real_T mu_10;                        /* Variable: mu_10
                                        * Referenced by: '<S8>/Gain13'
                                        */
  real_T mu_11;                        /* Variable: mu_11
                                        * Referenced by: '<S8>/Gain17'
                                        */
  real_T mu_12;                        /* Variable: mu_12
                                        * Referenced by: '<S8>/Gain22'
                                        */
  real_T mu_13;                        /* Variable: mu_13
                                        * Referenced by: '<S8>/Gain23'
                                        */
  real_T mu_14;                        /* Variable: mu_14
                                        * Referenced by: '<S8>/Gain24'
                                        */
  real_T mu_15;                        /* Variable: mu_15
                                        * Referenced by: '<S8>/Gain25'
                                        */
  real_T mu_20;                        /* Variable: mu_20
                                        * Referenced by: '<S8>/Gain10'
                                        */
  real_T mu_21;                        /* Variable: mu_21
                                        * Referenced by: '<S8>/Gain26'
                                        */
  real_T mu_22;                        /* Variable: mu_22
                                        * Referenced by: '<S8>/Gain27'
                                        */
  real_T mu_23;                        /* Variable: mu_23
                                        * Referenced by: '<S8>/Gain21'
                                        */
  real_T mu_24;                        /* Variable: mu_24
                                        * Referenced by: '<S8>/Gain20'
                                        */
  real_T mu_30;                        /* Variable: mu_30
                                        * Referenced by: '<S8>/Gain9'
                                        */
  real_T mu_31;                        /* Variable: mu_31
                                        * Referenced by: '<S8>/Gain19'
                                        */
  real_T mu_32;                        /* Variable: mu_32
                                        * Referenced by: '<S8>/Gain18'
                                        */
  real_T mu_33;                        /* Variable: mu_33
                                        * Referenced by: '<S8>/Gain12'
                                        */
  real_T mu_40;                        /* Variable: mu_40
                                        * Referenced by: '<S8>/Gain8'
                                        */
  real_T mu_41;                        /* Variable: mu_41
                                        * Referenced by: '<S8>/Gain16'
                                        */
  real_T mu_42;                        /* Variable: mu_42
                                        * Referenced by: '<S8>/Gain15'
                                        */
  real_T mu_50;                        /* Variable: mu_50
                                        * Referenced by: '<S8>/Gain7'
                                        */
  real_T mu_51;                        /* Variable: mu_51
                                        * Referenced by: '<S8>/Gain14'
                                        */
  real_T mu_60;                        /* Variable: mu_60
                                        * Referenced by: '<S8>/Gain6'
                                        */
  real_T offset_cornering;             /* Variable: offset_cornering
                                        * Referenced by:
                                        *   '<S227>/Constant1'
                                        *   '<S227>/Multiply'
                                        */
  real_T offset_throttle_csi;          /* Variable: offset_throttle_csi
                                        * Referenced by:
                                        *   '<S7>/Constant2'
                                        *   '<S7>/Gain4'
                                        */
  real_T p_fl[6];                      /* Variable: p_fl
                                        * Referenced by:
                                        *   '<S2>/Constant8'
                                        *   '<S2>/Gain1'
                                        *   '<S2>/Gain2'
                                        *   '<S2>/Gain4'
                                        *   '<S2>/Gain5'
                                        *   '<S2>/Gain6'
                                        */
  real_T p_fr[6];                      /* Variable: p_fr
                                        * Referenced by:
                                        *   '<S2>/Constant7'
                                        *   '<S2>/Gain10'
                                        *   '<S2>/Gain11'
                                        *   '<S2>/Gain7'
                                        *   '<S2>/Gain8'
                                        *   '<S2>/Gain9'
                                        */
  real_T rho_air;                      /* Variable: rho_air
                                        * Referenced by: '<S9>/Fl'
                                        */
  real_T sigma_w1;                     /* Variable: sigma_w1
                                        * Referenced by: '<S19>/Constant3'
                                        */
  real_T sigma_w2;                     /* Variable: sigma_w2
                                        * Referenced by: '<S19>/Constant1'
                                        */
  real_T t_f;                          /* Variable: t_f
                                        * Referenced by: '<S9>/Gain3'
                                        */
  real_T t_r;                          /* Variable: t_r
                                        * Referenced by: '<S9>/Gain4'
                                        */
  real_T tau;                          /* Variable: tau
                                        * Referenced by: '<S8>/Gain11'
                                        */
  real_T toe_f;                        /* Variable: toe_f
                                        * Referenced by: '<S10>/Constant2'
                                        */
  real_T toe_r;                        /* Variable: toe_r
                                        * Referenced by: '<S10>/Constant4'
                                        */
  real_T w;                            /* Variable: w
                                        * Referenced by:
                                        *   '<S9>/Constant'
                                        *   '<S9>/Constant1'
                                        *   '<S9>/Gain'
                                        *   '<S9>/Gain1'
                                        *   '<S9>/Gain2'
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real_T zCoG;                         /* Variable: zCoG
                                        * Referenced by:
                                        *   '<S9>/Gain2'
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real_T zRC_f1;                        /* Variable: zRC_f
                                        * Referenced by:
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real_T zRC_r1;                        /* Variable: zRC_r
                                        * Referenced by:
                                        *   '<S9>/Gain3'
                                        *   '<S9>/Gain4'
                                        */
  real32_T r0;                         /* Variable: r0
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T PIDController3_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController3_InitialConditionForIntegrator
                  * Referenced by: '<S110>/Integrator'
                  */
  real_T PIDController8_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController8_InitialConditionForIntegrator
                  * Referenced by: '<S210>/Integrator'
                  */
  real_T PIDController1_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController1_InitialConditionForIntegrator
                  * Referenced by: '<S60>/Integrator'
                  */
  real_T PIDController7_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController7_InitialConditionForIntegrator
                  * Referenced by: '<S160>/Integrator'
                  */
  real_T PIDController3_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController3_LowerIntegratorSaturationLimit
                 * Referenced by: '<S110>/Integrator'
                 */
  real_T PIDController8_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController8_LowerIntegratorSaturationLimit
                 * Referenced by: '<S210>/Integrator'
                 */
  real_T PIDController1_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController1_LowerIntegratorSaturationLimit
                 * Referenced by: '<S60>/Integrator'
                 */
  real_T PIDController7_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController7_LowerIntegratorSaturationLimit
                 * Referenced by: '<S160>/Integrator'
                 */
  real_T PIDController3_LowerSaturationLimit;
                          /* Mask Parameter: PIDController3_LowerSaturationLimit
                           * Referenced by:
                           *   '<S117>/Saturation'
                           *   '<S103>/DeadZone'
                           */
  real_T PIDController8_LowerSaturationLimit;
                          /* Mask Parameter: PIDController8_LowerSaturationLimit
                           * Referenced by:
                           *   '<S217>/Saturation'
                           *   '<S203>/DeadZone'
                           */
  real_T PIDController1_LowerSaturationLimit;
                          /* Mask Parameter: PIDController1_LowerSaturationLimit
                           * Referenced by:
                           *   '<S67>/Saturation'
                           *   '<S53>/DeadZone'
                           */
  real_T PIDController7_LowerSaturationLimit;
                          /* Mask Parameter: PIDController7_LowerSaturationLimit
                           * Referenced by:
                           *   '<S167>/Saturation'
                           *   '<S153>/DeadZone'
                           */
  real_T PIDController3_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController3_UpperIntegratorSaturationLimit
                 * Referenced by: '<S110>/Integrator'
                 */
  real_T PIDController8_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController8_UpperIntegratorSaturationLimit
                 * Referenced by: '<S210>/Integrator'
                 */
  real_T PIDController1_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController1_UpperIntegratorSaturationLimit
                 * Referenced by: '<S60>/Integrator'
                 */
  real_T PIDController7_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController7_UpperIntegratorSaturationLimit
                 * Referenced by: '<S160>/Integrator'
                 */
  real_T PIDController3_UpperSaturationLimit;
                          /* Mask Parameter: PIDController3_UpperSaturationLimit
                           * Referenced by:
                           *   '<S117>/Saturation'
                           *   '<S103>/DeadZone'
                           */
  real_T PIDController8_UpperSaturationLimit;
                          /* Mask Parameter: PIDController8_UpperSaturationLimit
                           * Referenced by:
                           *   '<S217>/Saturation'
                           *   '<S203>/DeadZone'
                           */
  real_T PIDController1_UpperSaturationLimit;
                          /* Mask Parameter: PIDController1_UpperSaturationLimit
                           * Referenced by:
                           *   '<S67>/Saturation'
                           *   '<S53>/DeadZone'
                           */
  real_T PIDController7_UpperSaturationLimit;
                          /* Mask Parameter: PIDController7_UpperSaturationLimit
                           * Referenced by:
                           *   '<S167>/Saturation'
                           *   '<S153>/DeadZone'
                           */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S51>/Constant1'
                                        */
  real_T Constant1_Value_g;            /* Expression: 0
                                        * Referenced by: '<S101>/Constant1'
                                        */
  real_T Constant1_Value_l;            /* Expression: 0
                                        * Referenced by: '<S151>/Constant1'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * Referenced by: '<S201>/Constant1'
                                        */
  real_T Memory_InitialCondition[4];   /* Expression: [0 0; 0 0]
                                        * Referenced by: '<S12>/Memory'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant6_Value[4];           /* Expression: eye(2)
                                        * Referenced by: '<S12>/Constant6'
                                        */
  real_T Constant4_Value[2];           /* Expression: [1 0]
                                        * Referenced by: '<S12>/Constant4'
                                        */
  real_T Constant1_Value_i[4];         /* Expression: [1 0; 0 1]
                                        * Referenced by: '<S12>/Constant1'
                                        */
  real_T Gain3_Gain;                   /* Expression: T
                                        * Referenced by: '<S12>/Gain3'
                                        */
  real_T Memory_InitialCondition_l;    /* Expression: 0
                                        * Referenced by: '<S19>/Memory'
                                        */
  real_T Memory_InitialCondition_n;    /* Expression: 0
                                        * Referenced by: '<Root>/Memory'
                                        */
  real_T Constant3_Value;              /* Expression: 5
                                        * Referenced by: '<S2>/Constant3'
                                        */
  real_T Constant1_Value_k;            /* Expression: 4
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real_T Constant2_Value;              /* Expression: 3
                                        * Referenced by: '<S2>/Constant2'
                                        */
  real_T Constant4_Value_l;            /* Expression: 3
                                        * Referenced by: '<S2>/Constant4'
                                        */
  real_T Constant5_Value;              /* Expression: 4
                                        * Referenced by: '<S2>/Constant5'
                                        */
  real_T Constant6_Value_f;            /* Expression: 5
                                        * Referenced by: '<S2>/Constant6'
                                        */
  real_T Gain_Gain;                    /* Expression: pi/180
                                        * Referenced by: '<S2>/Gain'
                                        */
  real_T Gain_Gain_j;                  /* Expression: -1
                                        * Referenced by: '<S10>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/T
                                        * Referenced by: '<S19>/Gain1'
                                        */
  real_T Memory1_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S3>/Memory1'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 1/2
                                        * Referenced by: '<S19>/Gain'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 0.4
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -0.4
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real_T Constant_Value_b;             /* Expression: 3
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Constant1_Value_c;            /* Expression: 4
                                        * Referenced by: '<S8>/Constant1'
                                        */
  real_T Constant2_Value_d;            /* Expression: 5
                                        * Referenced by: '<S8>/Constant2'
                                        */
  real_T Constant3_Value_o;            /* Expression: 6
                                        * Referenced by: '<S8>/Constant3'
                                        */
  real_T Constant4_Value_p;            /* Expression: 3
                                        * Referenced by: '<S8>/Constant4'
                                        */
  real_T Constant5_Value_a;            /* Expression: 4
                                        * Referenced by: '<S8>/Constant5'
                                        */
  real_T Constant6_Value_p;            /* Expression: 5
                                        * Referenced by: '<S8>/Constant6'
                                        */
  real_T Constant8_Value;              /* Expression: 6
                                        * Referenced by: '<S8>/Constant8'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 2500
                                        * Referenced by: '<S8>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: 50
                                        * Referenced by: '<S8>/Saturation1'
                                        */
  real_T Constant_Value_n;             /* Expression: 1
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Constant_Value_h;             /* Expression: 1
                                        * Referenced by: '<S227>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: 1
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Constant5_Value_h;            /* Expression: 0
                                        * Referenced by: '<S21>/Constant5'
                                        */
  real_T Constant15_Value;             /* Expression: 0
                                        * Referenced by: '<S22>/Constant15'
                                        */
  real_T Constant6_Value_j;            /* Expression: 1
                                        * Referenced by: '<S22>/Constant6'
                                        */
  real_T Constant16_Value;             /* Expression: 1
                                        * Referenced by: '<S22>/Constant16'
                                        */
  real_T Constant6_Value_g;            /* Expression: 1e-5
                                        * Referenced by: '<S6>/Constant6'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S110>/Integrator'
                                        */
  real_T Integrator_gainval_b;       /* Computed Parameter: Integrator_gainval_b
                                      * Referenced by: '<S210>/Integrator'
                                      */
  real_T Integrator_gainval_h;       /* Computed Parameter: Integrator_gainval_h
                                      * Referenced by: '<S60>/Integrator'
                                      */
  real_T Integrator_gainval_l;       /* Computed Parameter: Integrator_gainval_l
                                      * Referenced by: '<S160>/Integrator'
                                      */
  real_T Constant_Value_an;            /* Expression: 0.1
                                        * Referenced by: '<S20>/Constant'
                                        */
  real_T Constant_Value_k;             /* Expression: 0.1
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Constant1_Value_m;            /* Expression: 20000*pi/30
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real_T Memory2_InitialCondition[2];  /* Expression: [1.3;0]
                                        * Referenced by: '<S3>/Memory2'
                                        */
  real_T Constant_Value_e;             /* Expression: 1
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Clamping_zero_Value;          /* Expression: 0
                                        * Referenced by: '<S151>/Clamping_zero'
                                        */
  real_T Clamping_zero_Value_e;        /* Expression: 0
                                        * Referenced by: '<S51>/Clamping_zero'
                                        */
  real_T Clamping_zero_Value_j;        /* Expression: 0
                                        * Referenced by: '<S201>/Clamping_zero'
                                        */
  real_T Clamping_zero_Value_m;        /* Expression: 0
                                        * Referenced by: '<S101>/Clamping_zero'
                                        */
  real_T Constant_Value_eh[4];         /* Expression: [0 0 0 0]
                                        * Referenced by: '<Root>/Constant'
                                        */
  real32_T Memory4_InitialCondition;
                                 /* Computed Parameter: Memory4_InitialCondition
                                  * Referenced by: '<S3>/Memory4'
                                  */
  real32_T Gain_Gain_i;                /* Computed Parameter: Gain_Gain_i
                                        * Referenced by: '<S12>/Gain'
                                        */
  real32_T Gain1_Gain_d;               /* Expression: T
                                        * Referenced by: '<S12>/Gain1'
                                        */
  real32_T Saturation2_UpperSat;     /* Computed Parameter: Saturation2_UpperSat
                                      * Referenced by: '<Root>/Saturation2'
                                      */
  real32_T Saturation2_LowerSat;     /* Computed Parameter: Saturation2_LowerSat
                                      * Referenced by: '<Root>/Saturation2'
                                      */
  real32_T Multiply_Gain;              /* Computed Parameter: Multiply_Gain
                                        * Referenced by: '<S13>/Multiply'
                                        */
  real32_T Multiply1_Gain;             /* Computed Parameter: Multiply1_Gain
                                        * Referenced by: '<S13>/Multiply1'
                                        */
  real32_T Multiply2_Gain;             /* Computed Parameter: Multiply2_Gain
                                        * Referenced by: '<S13>/Multiply2'
                                        */
  real32_T Multiply3_Gain;             /* Computed Parameter: Multiply3_Gain
                                        * Referenced by: '<S13>/Multiply3'
                                        */
  real32_T Saturation5_UpperSat;     /* Computed Parameter: Saturation5_UpperSat
                                      * Referenced by: '<Root>/Saturation5'
                                      */
  real32_T Saturation5_LowerSat;     /* Computed Parameter: Saturation5_LowerSat
                                      * Referenced by: '<Root>/Saturation5'
                                      */
  real32_T Gain_Gain_e;                /* Computed Parameter: Gain_Gain_e
                                        * Referenced by: '<Root>/Gain'
                                        */
  real32_T reduction_Gain;             /* Computed Parameter: reduction_Gain
                                        * Referenced by: '<Root>/reduction'
                                        */
  real32_T Saturation6_UpperSat;     /* Computed Parameter: Saturation6_UpperSat
                                      * Referenced by: '<Root>/Saturation6'
                                      */
  real32_T Saturation6_LowerSat;     /* Computed Parameter: Saturation6_LowerSat
                                      * Referenced by: '<Root>/Saturation6'
                                      */
  real32_T Gain3_Gain_a;               /* Computed Parameter: Gain3_Gain_a
                                        * Referenced by: '<S2>/Gain3'
                                        */
  real32_T Saturation3_UpperSat;     /* Computed Parameter: Saturation3_UpperSat
                                      * Referenced by: '<Root>/Saturation3'
                                      */
  real32_T Saturation3_LowerSat;     /* Computed Parameter: Saturation3_LowerSat
                                      * Referenced by: '<Root>/Saturation3'
                                      */
  real32_T Gain_Gain_b;                /* Computed Parameter: Gain_Gain_b
                                        * Referenced by: '<S7>/Gain'
                                        */
  real32_T Gain1_Gain_l;               /* Computed Parameter: Gain1_Gain_l
                                        * Referenced by: '<Root>/Gain1'
                                        */
  int16_T Constant_Value_hq;           /* Computed Parameter: Constant_Value_hq
                                        * Referenced by: '<S51>/Constant'
                                        */
  int16_T Constant2_Value_j;           /* Computed Parameter: Constant2_Value_j
                                        * Referenced by: '<S51>/Constant2'
                                        */
  int16_T Constant3_Value_op;          /* Computed Parameter: Constant3_Value_op
                                        * Referenced by: '<S51>/Constant3'
                                        */
  int16_T Constant4_Value_e;           /* Computed Parameter: Constant4_Value_e
                                        * Referenced by: '<S51>/Constant4'
                                        */
  int16_T Constant_Value_d;            /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S101>/Constant'
                                        */
  int16_T Constant2_Value_dk;          /* Computed Parameter: Constant2_Value_dk
                                        * Referenced by: '<S101>/Constant2'
                                        */
  int16_T Constant3_Value_d;           /* Computed Parameter: Constant3_Value_d
                                        * Referenced by: '<S101>/Constant3'
                                        */
  int16_T Constant4_Value_j;           /* Computed Parameter: Constant4_Value_j
                                        * Referenced by: '<S101>/Constant4'
                                        */
  int16_T Constant_Value_am;           /* Computed Parameter: Constant_Value_am
                                        * Referenced by: '<S151>/Constant'
                                        */
  int16_T Constant2_Value_p;           /* Computed Parameter: Constant2_Value_p
                                        * Referenced by: '<S151>/Constant2'
                                        */
  int16_T Constant3_Value_ob;          /* Computed Parameter: Constant3_Value_ob
                                        * Referenced by: '<S151>/Constant3'
                                        */
  int16_T Constant4_Value_c;           /* Computed Parameter: Constant4_Value_c
                                        * Referenced by: '<S151>/Constant4'
                                        */
  int16_T Constant_Value_ej;           /* Computed Parameter: Constant_Value_ej
                                        * Referenced by: '<S201>/Constant'
                                        */
  int16_T Constant2_Value_g;           /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S201>/Constant2'
                                        */
  int16_T Constant3_Value_j;           /* Computed Parameter: Constant3_Value_j
                                        * Referenced by: '<S201>/Constant3'
                                        */
  int16_T Constant4_Value_o;           /* Computed Parameter: Constant4_Value_o
                                        * Referenced by: '<S201>/Constant4'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Torque_Vectoring_2024_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_Torque_Vectoring_2024_T Torque_Vectoring_2024_P;

/* Block states (default storage) */
extern DW_Torque_Vectoring_2024_T Torque_Vectoring_2024_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Torque_Vectoring_2024_T Torque_Vectoring_2024_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Torque_Vectoring_2024_T Torque_Vectoring_2024_Y;

/* Model entry point functions */
extern void Torque_Vectoring_2024_initialize(void);
extern void Torque_Vectoring_2024_step(void);

/* Real-time Model object */
extern RT_MODEL_Torque_Vectoring_2024_T *const Torque_Vectoring_2024_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S20>/Scope' : Unused code path elimination
 * Block '<Root>/Saturation4' : Unused code path elimination
 * Block '<Root>/Saturation7' : Unused code path elimination
 * Block '<Root>/Saturation8' : Unused code path elimination
 * Block '<Root>/Saturation9' : Unused code path elimination
 * Block '<S21>/Scope1' : Unused code path elimination
 * Block '<S21>/Scope2' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Torque_Vectoring_2024'
 * '<S1>'   : 'Torque_Vectoring_2024/Csi'
 * '<S2>'   : 'Torque_Vectoring_2024/Delta estimators'
 * '<S3>'   : 'Torque_Vectoring_2024/KF'
 * '<S4>'   : 'Torque_Vectoring_2024/Power Limitation'
 * '<S5>'   : 'Torque_Vectoring_2024/Re'
 * '<S6>'   : 'Torque_Vectoring_2024/TC'
 * '<S7>'   : 'Torque_Vectoring_2024/TV '
 * '<S8>'   : 'Torque_Vectoring_2024/Torque limit'
 * '<S9>'   : 'Torque_Vectoring_2024/Vertical loads calculator'
 * '<S10>'  : 'Torque_Vectoring_2024/Wheels Angle '
 * '<S11>'  : 'Torque_Vectoring_2024/KF/Compare To Constant'
 * '<S12>'  : 'Torque_Vectoring_2024/KF/Matrices'
 * '<S13>'  : 'Torque_Vectoring_2024/KF/Measurement'
 * '<S14>'  : 'Torque_Vectoring_2024/KF/Measurement Update'
 * '<S15>'  : 'Torque_Vectoring_2024/KF/Time Update'
 * '<S16>'  : 'Torque_Vectoring_2024/KF/Measurement/Compare To Constant2'
 * '<S17>'  : 'Torque_Vectoring_2024/KF/Measurement/Compare To Constant3'
 * '<S18>'  : 'Torque_Vectoring_2024/KF/Measurement/Compare To Constant4'
 * '<S19>'  : 'Torque_Vectoring_2024/KF/Measurement/Weights'
 * '<S20>'  : 'Torque_Vectoring_2024/Power Limitation/Subsystem'
 * '<S21>'  : 'Torque_Vectoring_2024/TC/CLTC '
 * '<S22>'  : 'Torque_Vectoring_2024/TC/Slip Calculation'
 * '<S23>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1'
 * '<S24>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3'
 * '<S25>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7'
 * '<S26>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8'
 * '<S27>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup'
 * '<S28>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/D Gain'
 * '<S29>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter'
 * '<S30>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter ICs'
 * '<S31>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/I Gain'
 * '<S32>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain'
 * '<S33>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain Fdbk'
 * '<S34>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator'
 * '<S35>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator ICs'
 * '<S36>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Copy'
 * '<S37>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Gain'
 * '<S38>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/P Copy'
 * '<S39>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Parallel P Gain'
 * '<S40>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Reset Signal'
 * '<S41>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation'
 * '<S42>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation Fdbk'
 * '<S43>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum'
 * '<S44>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum Fdbk'
 * '<S45>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode'
 * '<S46>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode Sum'
 * '<S47>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Integral'
 * '<S48>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Ngain'
 * '<S49>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/postSat Signal'
 * '<S50>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/preSat Signal'
 * '<S51>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S52>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S53>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S54>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/D Gain/Disabled'
 * '<S55>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter/Disabled'
 * '<S56>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter ICs/Disabled'
 * '<S57>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/I Gain/Internal Parameters'
 * '<S58>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain/Passthrough'
 * '<S59>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S60>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator/Discrete'
 * '<S61>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator ICs/Internal IC'
 * '<S62>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S63>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Gain/Disabled'
 * '<S64>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/P Copy/Disabled'
 * '<S65>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S66>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Reset Signal/Disabled'
 * '<S67>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation/Enabled'
 * '<S68>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation Fdbk/Disabled'
 * '<S69>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum/Sum_PI'
 * '<S70>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum Fdbk/Disabled'
 * '<S71>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode/Disabled'
 * '<S72>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S73>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Integral/Passthrough'
 * '<S74>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S75>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/postSat Signal/Forward_Path'
 * '<S76>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/preSat Signal/Forward_Path'
 * '<S77>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup'
 * '<S78>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/D Gain'
 * '<S79>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter'
 * '<S80>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter ICs'
 * '<S81>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/I Gain'
 * '<S82>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain'
 * '<S83>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain Fdbk'
 * '<S84>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator'
 * '<S85>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator ICs'
 * '<S86>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Copy'
 * '<S87>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Gain'
 * '<S88>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/P Copy'
 * '<S89>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Parallel P Gain'
 * '<S90>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Reset Signal'
 * '<S91>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation'
 * '<S92>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation Fdbk'
 * '<S93>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum'
 * '<S94>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum Fdbk'
 * '<S95>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode'
 * '<S96>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode Sum'
 * '<S97>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Integral'
 * '<S98>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Ngain'
 * '<S99>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/postSat Signal'
 * '<S100>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/preSat Signal'
 * '<S101>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S102>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S103>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S104>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/D Gain/Disabled'
 * '<S105>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter/Disabled'
 * '<S106>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter ICs/Disabled'
 * '<S107>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/I Gain/Internal Parameters'
 * '<S108>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain/Passthrough'
 * '<S109>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S110>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator/Discrete'
 * '<S111>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator ICs/Internal IC'
 * '<S112>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S113>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Gain/Disabled'
 * '<S114>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/P Copy/Disabled'
 * '<S115>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S116>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Reset Signal/Disabled'
 * '<S117>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation/Enabled'
 * '<S118>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation Fdbk/Disabled'
 * '<S119>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum/Sum_PI'
 * '<S120>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum Fdbk/Disabled'
 * '<S121>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode/Disabled'
 * '<S122>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S123>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Integral/Passthrough'
 * '<S124>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S125>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/postSat Signal/Forward_Path'
 * '<S126>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/preSat Signal/Forward_Path'
 * '<S127>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup'
 * '<S128>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/D Gain'
 * '<S129>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter'
 * '<S130>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter ICs'
 * '<S131>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/I Gain'
 * '<S132>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain'
 * '<S133>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain Fdbk'
 * '<S134>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator'
 * '<S135>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator ICs'
 * '<S136>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Copy'
 * '<S137>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Gain'
 * '<S138>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/P Copy'
 * '<S139>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Parallel P Gain'
 * '<S140>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Reset Signal'
 * '<S141>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation'
 * '<S142>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation Fdbk'
 * '<S143>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum'
 * '<S144>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum Fdbk'
 * '<S145>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode'
 * '<S146>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode Sum'
 * '<S147>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Integral'
 * '<S148>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Ngain'
 * '<S149>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/postSat Signal'
 * '<S150>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/preSat Signal'
 * '<S151>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel'
 * '<S152>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S153>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S154>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/D Gain/Disabled'
 * '<S155>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter/Disabled'
 * '<S156>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter ICs/Disabled'
 * '<S157>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/I Gain/Internal Parameters'
 * '<S158>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain/Passthrough'
 * '<S159>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain Fdbk/Disabled'
 * '<S160>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator/Discrete'
 * '<S161>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator ICs/Internal IC'
 * '<S162>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Copy/Disabled wSignal Specification'
 * '<S163>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Gain/Disabled'
 * '<S164>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/P Copy/Disabled'
 * '<S165>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Parallel P Gain/Internal Parameters'
 * '<S166>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Reset Signal/Disabled'
 * '<S167>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation/Enabled'
 * '<S168>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation Fdbk/Disabled'
 * '<S169>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum/Sum_PI'
 * '<S170>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum Fdbk/Disabled'
 * '<S171>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode/Disabled'
 * '<S172>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode Sum/Passthrough'
 * '<S173>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Integral/Passthrough'
 * '<S174>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Ngain/Passthrough'
 * '<S175>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/postSat Signal/Forward_Path'
 * '<S176>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/preSat Signal/Forward_Path'
 * '<S177>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup'
 * '<S178>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/D Gain'
 * '<S179>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter'
 * '<S180>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter ICs'
 * '<S181>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/I Gain'
 * '<S182>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain'
 * '<S183>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain Fdbk'
 * '<S184>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator'
 * '<S185>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator ICs'
 * '<S186>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Copy'
 * '<S187>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Gain'
 * '<S188>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/P Copy'
 * '<S189>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Parallel P Gain'
 * '<S190>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Reset Signal'
 * '<S191>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation'
 * '<S192>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation Fdbk'
 * '<S193>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum'
 * '<S194>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum Fdbk'
 * '<S195>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode'
 * '<S196>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode Sum'
 * '<S197>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Integral'
 * '<S198>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Ngain'
 * '<S199>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/postSat Signal'
 * '<S200>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/preSat Signal'
 * '<S201>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel'
 * '<S202>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S203>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S204>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/D Gain/Disabled'
 * '<S205>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter/Disabled'
 * '<S206>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter ICs/Disabled'
 * '<S207>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/I Gain/Internal Parameters'
 * '<S208>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain/Passthrough'
 * '<S209>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain Fdbk/Disabled'
 * '<S210>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator/Discrete'
 * '<S211>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator ICs/Internal IC'
 * '<S212>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Copy/Disabled wSignal Specification'
 * '<S213>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Gain/Disabled'
 * '<S214>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/P Copy/Disabled'
 * '<S215>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Parallel P Gain/Internal Parameters'
 * '<S216>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Reset Signal/Disabled'
 * '<S217>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation/Enabled'
 * '<S218>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation Fdbk/Disabled'
 * '<S219>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum/Sum_PI'
 * '<S220>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum Fdbk/Disabled'
 * '<S221>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode/Disabled'
 * '<S222>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode Sum/Passthrough'
 * '<S223>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Integral/Passthrough'
 * '<S224>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Ngain/Passthrough'
 * '<S225>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/postSat Signal/Forward_Path'
 * '<S226>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/preSat Signal/Forward_Path'
 * '<S227>' : 'Torque_Vectoring_2024/TV /Ripartizione'
 */
#endif                                 /* RTW_HEADER_Torque_Vectoring_2024_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
