/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024.h
 *
 * Code generated for Simulink model 'Torque_Vectoring_2024'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Mar 21 01:15:47 2025
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
  real_T Delay_DSTATE;                 /* '<Root>/Delay' */
  real_T u;                            /* '<S120>/Integrator' */
  real_T u_m;                          /* '<S220>/Integrator' */
  real_T u_a;                          /* '<S70>/Integrator' */
  real_T u_g;                          /* '<S170>/Integrator' */
  real_T Memory1_PreviousInput[2];     /* '<S3>/Memory1' */
  real_T Memory_PreviousInput[4];      /* '<S21>/Memory' */
  real_T Memory_PreviousInput_d[4];    /* '<S14>/Memory' */
  real_T Divide_DWORK4;                /* '<S14>/Divide' */
  real_T Memory_PreviousInput_b;       /* '<S24>/Memory' */
  real_T Memory2_PreviousInput[2];     /* '<S3>/Memory2' */
  real32_T Memory4_PreviousInput;      /* '<S3>/Memory4' */
  boolean_T Delay1_DSTATE[100];        /* '<S24>/Delay1' */
} DW_Torque_Vectoring_2024_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ax;                           /* '<Root>/ax' */
  real_T ay;                           /* '<Root>/ay' */
  real32_T yaw_r;                      /* '<Root>/yaw_r' */
  real32_T throttle;                   /* '<Root>/throttle' */
  real_T regenpaddle;                  /* '<Root>/regen paddle' */
  real32_T brakepressurefront;         /* '<Root>/brake pressure front' */
  real32_T brakepressurerear;          /* '<Root>/brake pressure rear' */
  real32_T steering;                   /* '<Root>/steering' */
  real32_T rpm[4];                     /* '<Root>/rpm' */
  real_T voltage;                      /* '<Root>/voltage' */
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
  real_T CLA1;                           /* Variable: CLA
                                        * Referenced by: '<S11>/Fl'
                                        */
  real_T FZ0;                          /* Variable: FZ0
                                        * Referenced by:
                                        *   '<S1>/Constant1'
                                        *   '<S1>/Gain'
                                        *   '<S1>/Gain1'
                                        */
  real_T Ilim;                         /* Variable: Ilim
                                        * Referenced by: '<S25>/MATLAB Function'
                                        */
  real_T Ld;    /* Variable: Ld
                                        * Referenced by:
                                        *   '<S25>/MATLAB Function'
                                        *   '<S28>/Gain6'
                                        */
  real_T Lq;                           /* Variable: Lq
                                        * Referenced by:
                                        *   '<S25>/MATLAB Function'
                                        *   '<S28>/Gain6'
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
                                        * Referenced by: '<S22>/Total Power Limit'
                                        */
  real_T Q[4];                         /* Variable: Q
                                        * Referenced by: '<S14>/Constant7'
                                        */
  real_T R1;                            /* Variable: R
                                        * Referenced by: '<S14>/Constant5'
                                        */
  real_T R01;                           /* Variable: R0
                                        * Referenced by:
                                        *   '<S5>/Constant'
                                        *   '<S5>/Saturation'
                                        */
  real_T R_batt;                       /* Variable: R_batt
                                        * Referenced by:
                                        *   '<S6>/Gain'
                                        *   '<S6>/Gain1'
                                        */
  real_T R_phase;                      /* Variable: R_phase
                                        * Referenced by:
                                        *   '<S25>/Gain'
                                        *   '<S28>/Constant'
                                        */
  real_T TC_CL_I_R;                    /* Variable: TC_CL_I_R
                                        * Referenced by:
                                        *   '<S67>/Integral Gain'
                                        *   '<S117>/Integral Gain'
                                        *   '<S167>/Integral Gain'
                                        *   '<S217>/Integral Gain'
                                        */
  real_T TC_CL_P_R;                    /* Variable: TC_CL_P_R
                                        * Referenced by:
                                        *   '<S75>/Proportional Gain'
                                        *   '<S125>/Proportional Gain'
                                        *   '<S175>/Proportional Gain'
                                        *   '<S225>/Proportional Gain'
                                        */
  real_T TC_CL_TARGET_SLIP_F;          /* Variable: TC_CL_TARGET_SLIP_F
                                        * Referenced by: '<S31>/Desired slip front1'
                                        */
  real_T TC_CL_TARGET_SLIP_R;          /* Variable: TC_CL_TARGET_SLIP_R
                                        * Referenced by: '<S31>/Desired slip rear1'
                                        */
  real_T TC_MAX_CUT;                   /* Variable: TC_MAX_CUT
                                        * Referenced by: '<S31>/Constant'
                                        */
  real_T TC_VX_ON_F;                   /* Variable: TC_VX_ON_F
                                        * Referenced by: '<S32>/Constant3'
                                        */
  real_T TC_VX_ON_R;                   /* Variable: TC_VX_ON_R
                                        * Referenced by: '<S32>/Constant2'
                                        */
  real_T T_max;                        /* Variable: T_max
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T T_regen_max;                  /* Variable: T_regen_max
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Voltage;                      /* Variable: Voltage
                                        * Referenced by: '<S6>/Max battery voltage'
                                        */
  real_T a;                             /* Variable: a
                                        * Referenced by:
                                        *   '<S11>/Constant1'
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real_T a_a;                          /* Variable: a_a
                                        * Referenced by: '<S11>/Gain'
                                        */
  real_T ax0;                          /* Variable: ax0
                                        * Referenced by:
                                        *   '<S18>/Constant'
                                        *   '<S19>/Constant'
                                        *   '<S20>/Constant'
                                        */
  real_T b;                            /* Variable: b
                                        * Referenced by:
                                        *   '<S11>/Constant'
                                        *   '<S11>/Gain3'
                                        */
  real_T b_a;                          /* Variable: b_a
                                        * Referenced by: '<S11>/Gain1'
                                        */
  real_T directCurrent;                /* Variable: directCurrent
                                        * Referenced by: '<S24>/Saturation'
                                        */
  real_T eta_inv;                      /* Variable: eta_inv
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T flux_mg;                      /* Variable: flux_mg
                                        * Referenced by:
                                        *   '<S25>/MATLAB Function'
                                        *   '<S28>/Gain3'
                                        */
  real_T g;                            /* Variable: g
                                        * Referenced by:
                                        *   '<Root>/Saturation'
                                        *   '<Root>/Saturation1'
                                        *   '<S11>/Constant'
                                        *   '<S11>/Constant1'
                                        */
  real_T k_Re1;                         /* Variable: k_Re
                                        * Referenced by: '<S5>/Gain2'
                                        */
  real_T kr_f1;                         /* Variable: kr_f
                                        * Referenced by:
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real_T kr_r1;                         /* Variable: kr_r
                                        * Referenced by:
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real_T m;                            /* Variable: m
                                        * Referenced by:
                                        *   '<S11>/Constant'
                                        *   '<S11>/Constant1'
                                        *   '<S11>/Gain2'
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real_T maxCurrent;                   /* Variable: maxCurrent
                                        * Referenced by:
                                        *   '<S6>/Constant'
                                        *   '<S24>/Constant1'
                                        *   '<S24>/Saturation'
                                        */
  real_T mu_00;                        /* Variable: mu_00
                                        * Referenced by: '<S10>/Constant7'
                                        */
  real_T mu_01;                        /* Variable: mu_01
                                        * Referenced by: '<S10>/Gain'
                                        */
  real_T mu_02;                        /* Variable: mu_02
                                        * Referenced by: '<S10>/Gain1'
                                        */
  real_T mu_03;                        /* Variable: mu_03
                                        * Referenced by: '<S10>/Gain2'
                                        */
  real_T mu_04;                        /* Variable: mu_04
                                        * Referenced by: '<S10>/Gain3'
                                        */
  real_T mu_05;                        /* Variable: mu_05
                                        * Referenced by: '<S10>/Gain4'
                                        */
  real_T mu_06;                        /* Variable: mu_06
                                        * Referenced by: '<S10>/Gain5'
                                        */
  real_T mu_10;                        /* Variable: mu_10
                                        * Referenced by: '<S10>/Gain13'
                                        */
  real_T mu_11;                        /* Variable: mu_11
                                        * Referenced by: '<S10>/Gain17'
                                        */
  real_T mu_12;                        /* Variable: mu_12
                                        * Referenced by: '<S10>/Gain22'
                                        */
  real_T mu_13;                        /* Variable: mu_13
                                        * Referenced by: '<S10>/Gain23'
                                        */
  real_T mu_14;                        /* Variable: mu_14
                                        * Referenced by: '<S10>/Gain24'
                                        */
  real_T mu_15;                        /* Variable: mu_15
                                        * Referenced by: '<S10>/Gain25'
                                        */
  real_T mu_20;                        /* Variable: mu_20
                                        * Referenced by: '<S10>/Gain10'
                                        */
  real_T mu_21;                        /* Variable: mu_21
                                        * Referenced by: '<S10>/Gain26'
                                        */
  real_T mu_22;                        /* Variable: mu_22
                                        * Referenced by: '<S10>/Gain27'
                                        */
  real_T mu_23;                        /* Variable: mu_23
                                        * Referenced by: '<S10>/Gain21'
                                        */
  real_T mu_24;                        /* Variable: mu_24
                                        * Referenced by: '<S10>/Gain20'
                                        */
  real_T mu_30;                        /* Variable: mu_30
                                        * Referenced by: '<S10>/Gain9'
                                        */
  real_T mu_31;                        /* Variable: mu_31
                                        * Referenced by: '<S10>/Gain19'
                                        */
  real_T mu_32;                        /* Variable: mu_32
                                        * Referenced by: '<S10>/Gain18'
                                        */
  real_T mu_33;                        /* Variable: mu_33
                                        * Referenced by: '<S10>/Gain12'
                                        */
  real_T mu_40;                        /* Variable: mu_40
                                        * Referenced by: '<S10>/Gain8'
                                        */
  real_T mu_41;                        /* Variable: mu_41
                                        * Referenced by: '<S10>/Gain16'
                                        */
  real_T mu_42;                        /* Variable: mu_42
                                        * Referenced by: '<S10>/Gain15'
                                        */
  real_T mu_50;                        /* Variable: mu_50
                                        * Referenced by: '<S10>/Gain7'
                                        */
  real_T mu_51;                        /* Variable: mu_51
                                        * Referenced by: '<S10>/Gain14'
                                        */
  real_T mu_60;                        /* Variable: mu_60
                                        * Referenced by: '<S10>/Gain6'
                                        */
  real_T n_phase;                      /* Variable: n_phase
                                        * Referenced by: '<S25>/Gain5'
                                        */
  real_T offset_brake_csi;             /* Variable: offset_brake_csi
                                        * Referenced by:
                                        *   '<Root>/Constant2'
                                        *   '<Root>/Gain12'
                                        */
  real_T offset_cornering;             /* Variable: offset_cornering
                                        * Referenced by:
                                        *   '<S237>/Constant1'
                                        *   '<S237>/Multiply'
                                        */
  real_T offset_throttle_csi;          /* Variable: offset_throttle_csi
                                        * Referenced by:
                                        *   '<S9>/Constant2'
                                        *   '<S9>/Gain4'
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
                                        * Referenced by: '<S11>/Fl'
                                        */
  real_T sigma_w1;                     /* Variable: sigma_w1
                                        * Referenced by: '<S21>/Constant3'
                                        */
  real_T sigma_w2;                     /* Variable: sigma_w2
                                        * Referenced by: '<S21>/Constant1'
                                        */
  real_T t_alpha;                      /* Variable: t_alpha
                                        * Referenced by:
                                        *   '<S28>/Gain1'
                                        *   '<S28>/Gain6'
                                        */
  real_T t_f;                          /* Variable: t_f
                                        * Referenced by: '<S11>/Gain3'
                                        */
  real_T t_r;                          /* Variable: t_r
                                        * Referenced by: '<S11>/Gain4'
                                        */
  real_T tau;                          /* Variable: tau
                                        * Referenced by: '<S10>/Gain11'
                                        */
  real_T toe_f;                        /* Variable: toe_f
                                        * Referenced by: '<S12>/Constant2'
                                        */
  real_T toe_r;                        /* Variable: toe_r
                                        * Referenced by: '<S12>/Constant4'
                                        */
  real_T w;                            /* Variable: w
                                        * Referenced by:
                                        *   '<S11>/Constant'
                                        *   '<S11>/Constant1'
                                        *   '<S11>/Gain'
                                        *   '<S11>/Gain1'
                                        *   '<S11>/Gain2'
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real_T zCoG;                         /* Variable: zCoG
                                        * Referenced by:
                                        *   '<S11>/Gain2'
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real_T zRC_f1;                        /* Variable: zRC_f
                                        * Referenced by:
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real_T zRC_r1;                        /* Variable: zRC_r
                                        * Referenced by:
                                        *   '<S11>/Gain3'
                                        *   '<S11>/Gain4'
                                        */
  real32_T r0;                         /* Variable: r0
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T PIDController3_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController3_InitialConditionForIntegrator
                  * Referenced by: '<S120>/Integrator'
                  */
  real_T PIDController8_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController8_InitialConditionForIntegrator
                  * Referenced by: '<S220>/Integrator'
                  */
  real_T PIDController1_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController1_InitialConditionForIntegrator
                  * Referenced by: '<S70>/Integrator'
                  */
  real_T PIDController7_InitialConditionForIntegrator;
                 /* Mask Parameter: PIDController7_InitialConditionForIntegrator
                  * Referenced by: '<S170>/Integrator'
                  */
  real_T PIDController3_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController3_LowerIntegratorSaturationLimit
                 * Referenced by: '<S120>/Integrator'
                 */
  real_T PIDController8_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController8_LowerIntegratorSaturationLimit
                 * Referenced by: '<S220>/Integrator'
                 */
  real_T PIDController1_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController1_LowerIntegratorSaturationLimit
                 * Referenced by: '<S70>/Integrator'
                 */
  real_T PIDController7_LowerIntegratorSaturationLimit;
                /* Mask Parameter: PIDController7_LowerIntegratorSaturationLimit
                 * Referenced by: '<S170>/Integrator'
                 */
  real_T PIDController3_LowerSaturationLimit;
                          /* Mask Parameter: PIDController3_LowerSaturationLimit
                           * Referenced by:
                           *   '<S127>/Saturation'
                           *   '<S113>/DeadZone'
                           */
  real_T PIDController8_LowerSaturationLimit;
                          /* Mask Parameter: PIDController8_LowerSaturationLimit
                           * Referenced by:
                           *   '<S227>/Saturation'
                           *   '<S213>/DeadZone'
                           */
  real_T PIDController1_LowerSaturationLimit;
                          /* Mask Parameter: PIDController1_LowerSaturationLimit
                           * Referenced by:
                           *   '<S77>/Saturation'
                           *   '<S63>/DeadZone'
                           */
  real_T PIDController7_LowerSaturationLimit;
                          /* Mask Parameter: PIDController7_LowerSaturationLimit
                           * Referenced by:
                           *   '<S177>/Saturation'
                           *   '<S163>/DeadZone'
                           */
  real_T PIDController3_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController3_UpperIntegratorSaturationLimit
                 * Referenced by: '<S120>/Integrator'
                 */
  real_T PIDController8_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController8_UpperIntegratorSaturationLimit
                 * Referenced by: '<S220>/Integrator'
                 */
  real_T PIDController1_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController1_UpperIntegratorSaturationLimit
                 * Referenced by: '<S70>/Integrator'
                 */
  real_T PIDController7_UpperIntegratorSaturationLimit;
                /* Mask Parameter: PIDController7_UpperIntegratorSaturationLimit
                 * Referenced by: '<S170>/Integrator'
                 */
  real_T PIDController3_UpperSaturationLimit;
                          /* Mask Parameter: PIDController3_UpperSaturationLimit
                           * Referenced by:
                           *   '<S127>/Saturation'
                           *   '<S113>/DeadZone'
                           */
  real_T PIDController8_UpperSaturationLimit;
                          /* Mask Parameter: PIDController8_UpperSaturationLimit
                           * Referenced by:
                           *   '<S227>/Saturation'
                           *   '<S213>/DeadZone'
                           */
  real_T PIDController1_UpperSaturationLimit;
                          /* Mask Parameter: PIDController1_UpperSaturationLimit
                           * Referenced by:
                           *   '<S77>/Saturation'
                           *   '<S63>/DeadZone'
                           */
  real_T PIDController7_UpperSaturationLimit;
                          /* Mask Parameter: PIDController7_UpperSaturationLimit
                           * Referenced by:
                           *   '<S177>/Saturation'
                           *   '<S163>/DeadZone'
                           */
  real_T Constant1_Value;              /* Expression: Ilim^2
                                        * Referenced by: '<S28>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S23>/Constant'
                                        */
  real_T Constant1_Value_i;            /* Expression: 0
                                        * Referenced by: '<S61>/Constant1'
                                        */
  real_T Constant1_Value_g;            /* Expression: 0
                                        * Referenced by: '<S111>/Constant1'
                                        */
  real_T Constant1_Value_l;            /* Expression: 0
                                        * Referenced by: '<S161>/Constant1'
                                        */
  real_T Constant1_Value_j;            /* Expression: 0
                                        * Referenced by: '<S211>/Constant1'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0
                                        * Referenced by: '<Root>/Delay'
                                        */
  real_T Constant6_Value;              /* Expression: 1e-5
                                        * Referenced by: '<S8>/Constant6'
                                        */
  real_T Constant16_Value;             /* Expression: 1
                                        * Referenced by: '<S32>/Constant16'
                                        */
  real_T Constant6_Value_j;            /* Expression: 1
                                        * Referenced by: '<S32>/Constant6'
                                        */
  real_T Constant15_Value;             /* Expression: 0
                                        * Referenced by: '<S32>/Constant15'
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
  real_T Constant4_Value;              /* Expression: 3
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
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T Memory1_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S3>/Memory1'
                                        */
  real_T Memory_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<S21>/Memory'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/T
                                        * Referenced by: '<S21>/Gain1'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 1/2
                                        * Referenced by: '<S21>/Gain'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 0.4
                                        * Referenced by: '<S10>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -0.4
                                        * Referenced by: '<S10>/Saturation'
                                        */
  real_T Constant_Value_b;             /* Expression: 3
                                        * Referenced by: '<S10>/Constant'
                                        */
  real_T Constant1_Value_c;            /* Expression: 4
                                        * Referenced by: '<S10>/Constant1'
                                        */
  real_T Constant2_Value_d;            /* Expression: 5
                                        * Referenced by: '<S10>/Constant2'
                                        */
  real_T Constant3_Value_o;            /* Expression: 6
                                        * Referenced by: '<S10>/Constant3'
                                        */
  real_T Constant4_Value_p;            /* Expression: 3
                                        * Referenced by: '<S10>/Constant4'
                                        */
  real_T Constant5_Value_a;            /* Expression: 4
                                        * Referenced by: '<S10>/Constant5'
                                        */
  real_T Constant6_Value_p;            /* Expression: 5
                                        * Referenced by: '<S10>/Constant6'
                                        */
  real_T Constant8_Value;              /* Expression: 6
                                        * Referenced by: '<S10>/Constant8'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 2500
                                        * Referenced by: '<S10>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: 50
                                        * Referenced by: '<S10>/Saturation1'
                                        */
  real_T Constant_Value_n;             /* Expression: 1
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Constant_Value_h;             /* Expression: 1
                                        * Referenced by: '<S237>/Constant'
                                        */
  real_T Constant_Value_a;             /* Expression: 1
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Constant5_Value_h;            /* Expression: 0
                                        * Referenced by: '<S31>/Constant5'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S120>/Integrator'
                                        */
  real_T Integrator_gainval_b;       /* Computed Parameter: Integrator_gainval_b
                                      * Referenced by: '<S220>/Integrator'
                                      */
  real_T Integrator_gainval_h;       /* Computed Parameter: Integrator_gainval_h
                                      * Referenced by: '<S70>/Integrator'
                                      */
  real_T Integrator_gainval_l;       /* Computed Parameter: Integrator_gainval_l
                                      * Referenced by: '<S170>/Integrator'
                                      */
  real_T Constant_Value_an;            /* Expression: 0.1
                                        * Referenced by: '<S22>/Constant'
                                        */
  real_T Constant_Value_k;             /* Expression: 0.1
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Constant1_Value_m;            /* Expression: 20000*pi/30
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real_T Saturation1_UpperSat_m;       /* Expression: 20000*pi/30
                                        * Referenced by: '<S7>/Saturation1'
                                        */
  real_T Saturation1_LowerSat_p;       /* Expression: 0
                                        * Referenced by: '<S7>/Saturation1'
                                        */
  real_T Memory_InitialCondition_i[4]; /* Expression: [0 0; 0 0]
                                        * Referenced by: '<S14>/Memory'
                                        */
  real_T Constant_Value_nt;            /* Expression: 1
                                        * Referenced by: '<S14>/Constant'
                                        */
  real_T Constant6_Value_h[4];         /* Expression: eye(2)
                                        * Referenced by: '<S14>/Constant6'
                                        */
  real_T Constant4_Value_g[2];         /* Expression: [1 0]
                                        * Referenced by: '<S14>/Constant4'
                                        */
  real_T Constant1_Value_ir[4];        /* Expression: [1 0; 0 1]
                                        * Referenced by: '<S14>/Constant1'
                                        */
  real_T Gain3_Gain;                   /* Expression: T
                                        * Referenced by: '<S14>/Gain3'
                                        */
  real_T Saturation8_UpperSat;         /* Expression: 600
                                        * Referenced by: '<Root>/Saturation8'
                                        */
  real_T Saturation8_LowerSat;         /* Expression: 0
                                        * Referenced by: '<Root>/Saturation8'
                                        */
  real_T Saturation4_UpperSat;         /* Expression: 1
                                        * Referenced by: '<Root>/Saturation4'
                                        */
  real_T Saturation4_LowerSat;         /* Expression: 0
                                        * Referenced by: '<Root>/Saturation4'
                                        */
  real_T Memory_InitialCondition_ir;   /* Expression: 0
                                        * Referenced by: '<S24>/Memory'
                                        */
  real_T Constant_Value_nb;            /* Expression: kRamp*T
                                        * Referenced by: '<S24>/Constant'
                                        */
  real_T Constant_Value_e;             /* Expression: 0
                                        * Referenced by: '<S25>/Constant'
                                        */
  real_T Gain4_Gain;                   /* Expression: 3/2
                                        * Referenced by: '<S28>/Gain4'
                                        */
  real_T Gain2_Gain;                   /* Expression: -1
                                        * Referenced by: '<S28>/Gain2'
                                        */
  real_T Gain7_Gain;                   /* Expression: 1/21
                                        * Referenced by: '<S25>/Gain7'
                                        */
  real_T Constant1_Value_ca;           /* Expression: 21
                                        * Referenced by: '<S26>/Constant1'
                                        */
  real_T Gain1_Gain_i;                 /* Expression: 1/4
                                        * Referenced by: '<S7>/Gain1'
                                        */
  real_T Gain_Gain_k;                  /* Expression: 30/pi
                                        * Referenced by: '<S26>/Gain'
                                        */
  real_T Constant_Value_f;             /* Expression: 13000
                                        * Referenced by: '<S26>/Constant'
                                        */
  real_T Saturation_UpperSat_a;        /* Expression: 7000
                                        * Referenced by: '<S26>/Saturation'
                                        */
  real_T Saturation_LowerSat_i;        /* Expression: 0
                                        * Referenced by: '<S26>/Saturation'
                                        */
  real_T Gain1_Gain_f;                 /* Expression: 0.000857
                                        * Referenced by: '<S26>/Gain1'
                                        */
  real_T Constant4_Value_o;            /* Expression: 0
                                        * Referenced by: '<S7>/Constant4'
                                        */
  real_T Constant3_Value_k;            /* Expression: 1
                                        * Referenced by: '<S27>/Constant3'
                                        */
  real_T Constant5_Value_c;            /* Expression: 1
                                        * Referenced by: '<S27>/Constant5'
                                        */
  real_T Gain3_Gain_o;                 /* Expression: -1
                                        * Referenced by: '<S7>/Gain3'
                                        */
  real_T Memory2_InitialCondition[2];  /* Expression: [1.3;0]
                                        * Referenced by: '<S3>/Memory2'
                                        */
  real_T Constant_Value_er;            /* Expression: 1
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Clamping_zero_Value;          /* Expression: 0
                                        * Referenced by: '<S161>/Clamping_zero'
                                        */
  real_T Clamping_zero_Value_e;        /* Expression: 0
                                        * Referenced by: '<S61>/Clamping_zero'
                                        */
  real_T Clamping_zero_Value_j;        /* Expression: 0
                                        * Referenced by: '<S211>/Clamping_zero'
                                        */
  real_T Clamping_zero_Value_m;        /* Expression: 0
                                        * Referenced by: '<S111>/Clamping_zero'
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
  real32_T Saturation2_UpperSat;     /* Computed Parameter: Saturation2_UpperSat
                                      * Referenced by: '<Root>/Saturation2'
                                      */
  real32_T Saturation2_LowerSat;     /* Computed Parameter: Saturation2_LowerSat
                                      * Referenced by: '<Root>/Saturation2'
                                      */
  real32_T Multiply_Gain;              /* Computed Parameter: Multiply_Gain
                                        * Referenced by: '<S15>/Multiply'
                                        */
  real32_T Multiply1_Gain;             /* Computed Parameter: Multiply1_Gain
                                        * Referenced by: '<S15>/Multiply1'
                                        */
  real32_T Multiply2_Gain;             /* Computed Parameter: Multiply2_Gain
                                        * Referenced by: '<S15>/Multiply2'
                                        */
  real32_T Multiply3_Gain;             /* Computed Parameter: Multiply3_Gain
                                        * Referenced by: '<S15>/Multiply3'
                                        */
  real32_T Saturation3_UpperSat;     /* Computed Parameter: Saturation3_UpperSat
                                      * Referenced by: '<Root>/Saturation3'
                                      */
  real32_T Saturation3_LowerSat;     /* Computed Parameter: Saturation3_LowerSat
                                      * Referenced by: '<Root>/Saturation3'
                                      */
  real32_T Gain_Gain_b;                /* Computed Parameter: Gain_Gain_b
                                        * Referenced by: '<S9>/Gain'
                                        */
  real32_T Gain1_Gain_l;               /* Computed Parameter: Gain1_Gain_l
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T Memory4_InitialCondition;
                                 /* Computed Parameter: Memory4_InitialCondition
                                  * Referenced by: '<S3>/Memory4'
                                  */
  real32_T Gain_Gain_i;                /* Computed Parameter: Gain_Gain_i
                                        * Referenced by: '<S14>/Gain'
                                        */
  real32_T Gain1_Gain_d;               /* Expression: T
                                        * Referenced by: '<S14>/Gain1'
                                        */
  real32_T Saturation7_UpperSat;     /* Computed Parameter: Saturation7_UpperSat
                                      * Referenced by: '<Root>/Saturation7'
                                      */
  real32_T Saturation7_LowerSat;     /* Computed Parameter: Saturation7_LowerSat
                                      * Referenced by: '<Root>/Saturation7'
                                      */
  real32_T Gain_Gain_o;                /* Computed Parameter: Gain_Gain_o
                                        * Referenced by: '<S27>/Gain'
                                        */
  real32_T Saturation9_UpperSat;     /* Computed Parameter: Saturation9_UpperSat
                                      * Referenced by: '<Root>/Saturation9'
                                      */
  real32_T Saturation9_LowerSat;     /* Computed Parameter: Saturation9_LowerSat
                                      * Referenced by: '<Root>/Saturation9'
                                      */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S27>/Gain1'
                                        */
  boolean_T Delay1_InitialCondition;
                                  /* Computed Parameter: Delay1_InitialCondition
                                   * Referenced by: '<S24>/Delay1'
                                   */
  int16_T Constant_Value_hq;           /* Computed Parameter: Constant_Value_hq
                                        * Referenced by: '<S61>/Constant'
                                        */
  int16_T Constant2_Value_j;           /* Computed Parameter: Constant2_Value_j
                                        * Referenced by: '<S61>/Constant2'
                                        */
  int16_T Constant3_Value_op;          /* Computed Parameter: Constant3_Value_op
                                        * Referenced by: '<S61>/Constant3'
                                        */
  int16_T Constant4_Value_e;           /* Computed Parameter: Constant4_Value_e
                                        * Referenced by: '<S61>/Constant4'
                                        */
  int16_T Constant_Value_d;            /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S111>/Constant'
                                        */
  int16_T Constant2_Value_dk;          /* Computed Parameter: Constant2_Value_dk
                                        * Referenced by: '<S111>/Constant2'
                                        */
  int16_T Constant3_Value_d;           /* Computed Parameter: Constant3_Value_d
                                        * Referenced by: '<S111>/Constant3'
                                        */
  int16_T Constant4_Value_j;           /* Computed Parameter: Constant4_Value_j
                                        * Referenced by: '<S111>/Constant4'
                                        */
  int16_T Constant_Value_am;           /* Computed Parameter: Constant_Value_am
                                        * Referenced by: '<S161>/Constant'
                                        */
  int16_T Constant2_Value_p;           /* Computed Parameter: Constant2_Value_p
                                        * Referenced by: '<S161>/Constant2'
                                        */
  int16_T Constant3_Value_ob;          /* Computed Parameter: Constant3_Value_ob
                                        * Referenced by: '<S161>/Constant3'
                                        */
  int16_T Constant4_Value_c;           /* Computed Parameter: Constant4_Value_c
                                        * Referenced by: '<S161>/Constant4'
                                        */
  int16_T Constant_Value_ej;           /* Computed Parameter: Constant_Value_ej
                                        * Referenced by: '<S211>/Constant'
                                        */
  int16_T Constant2_Value_g;           /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S211>/Constant2'
                                        */
  int16_T Constant3_Value_j;           /* Computed Parameter: Constant3_Value_j
                                        * Referenced by: '<S211>/Constant3'
                                        */
  int16_T Constant4_Value_oj;          /* Computed Parameter: Constant4_Value_oj
                                        * Referenced by: '<S211>/Constant4'
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
 * Block '<S22>/Scope' : Unused code path elimination
 * Block '<S25>/Scope1' : Unused code path elimination
 * Block '<S31>/Scope1' : Unused code path elimination
 * Block '<S31>/Scope2' : Unused code path elimination
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
 * '<S6>'   : 'Torque_Vectoring_2024/Regenerative Power'
 * '<S7>'   : 'Torque_Vectoring_2024/Regenerative braking'
 * '<S8>'   : 'Torque_Vectoring_2024/TC'
 * '<S9>'   : 'Torque_Vectoring_2024/TV '
 * '<S10>'  : 'Torque_Vectoring_2024/Torque limit'
 * '<S11>'  : 'Torque_Vectoring_2024/Vertical loads calculator'
 * '<S12>'  : 'Torque_Vectoring_2024/Wheels Angle '
 * '<S13>'  : 'Torque_Vectoring_2024/KF/Compare To Constant'
 * '<S14>'  : 'Torque_Vectoring_2024/KF/Matrices'
 * '<S15>'  : 'Torque_Vectoring_2024/KF/Measurement'
 * '<S16>'  : 'Torque_Vectoring_2024/KF/Measurement Update'
 * '<S17>'  : 'Torque_Vectoring_2024/KF/Time Update'
 * '<S18>'  : 'Torque_Vectoring_2024/KF/Measurement/Compare To Constant2'
 * '<S19>'  : 'Torque_Vectoring_2024/KF/Measurement/Compare To Constant3'
 * '<S20>'  : 'Torque_Vectoring_2024/KF/Measurement/Compare To Constant4'
 * '<S21>'  : 'Torque_Vectoring_2024/KF/Measurement/Weights'
 * '<S22>'  : 'Torque_Vectoring_2024/Power Limitation/Subsystem'
 * '<S23>'  : 'Torque_Vectoring_2024/Regenerative Power/Compare To Zero'
 * '<S24>'  : 'Torque_Vectoring_2024/Regenerative Power/ramp'
 * '<S25>'  : 'Torque_Vectoring_2024/Regenerative braking/Engine'
 * '<S26>'  : 'Torque_Vectoring_2024/Regenerative braking/Torque limit'
 * '<S27>'  : 'Torque_Vectoring_2024/Regenerative braking/csi_regen'
 * '<S28>'  : 'Torque_Vectoring_2024/Regenerative braking/Engine/Id Iq'
 * '<S29>'  : 'Torque_Vectoring_2024/Regenerative braking/Engine/MATLAB Function'
 * '<S30>'  : 'Torque_Vectoring_2024/Regenerative braking/Engine/Id Iq/MATLAB Function'
 * '<S31>'  : 'Torque_Vectoring_2024/TC/CLTC '
 * '<S32>'  : 'Torque_Vectoring_2024/TC/Slip Calculation'
 * '<S33>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1'
 * '<S34>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3'
 * '<S35>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7'
 * '<S36>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8'
 * '<S37>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup'
 * '<S38>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/D Gain'
 * '<S39>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter'
 * '<S40>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter ICs'
 * '<S41>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/I Gain'
 * '<S42>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain'
 * '<S43>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain Fdbk'
 * '<S44>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator'
 * '<S45>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator ICs'
 * '<S46>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Copy'
 * '<S47>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Gain'
 * '<S48>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/P Copy'
 * '<S49>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Parallel P Gain'
 * '<S50>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Reset Signal'
 * '<S51>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation'
 * '<S52>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation Fdbk'
 * '<S53>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum'
 * '<S54>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum Fdbk'
 * '<S55>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode'
 * '<S56>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode Sum'
 * '<S57>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Integral'
 * '<S58>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Ngain'
 * '<S59>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/postSat Signal'
 * '<S60>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/preSat Signal'
 * '<S61>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S62>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S63>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S64>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/D Gain/Disabled'
 * '<S65>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter/Disabled'
 * '<S66>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Filter ICs/Disabled'
 * '<S67>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/I Gain/Internal Parameters'
 * '<S68>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain/Passthrough'
 * '<S69>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S70>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator/Discrete'
 * '<S71>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Integrator ICs/Internal IC'
 * '<S72>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S73>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/N Gain/Disabled'
 * '<S74>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/P Copy/Disabled'
 * '<S75>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S76>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Reset Signal/Disabled'
 * '<S77>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation/Enabled'
 * '<S78>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Saturation Fdbk/Disabled'
 * '<S79>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum/Sum_PI'
 * '<S80>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Sum Fdbk/Disabled'
 * '<S81>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode/Disabled'
 * '<S82>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S83>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Integral/Passthrough'
 * '<S84>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S85>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/postSat Signal/Forward_Path'
 * '<S86>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller1/preSat Signal/Forward_Path'
 * '<S87>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup'
 * '<S88>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/D Gain'
 * '<S89>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter'
 * '<S90>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter ICs'
 * '<S91>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/I Gain'
 * '<S92>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain'
 * '<S93>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain Fdbk'
 * '<S94>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator'
 * '<S95>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator ICs'
 * '<S96>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Copy'
 * '<S97>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Gain'
 * '<S98>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/P Copy'
 * '<S99>'  : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Parallel P Gain'
 * '<S100>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Reset Signal'
 * '<S101>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation'
 * '<S102>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation Fdbk'
 * '<S103>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum'
 * '<S104>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum Fdbk'
 * '<S105>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode'
 * '<S106>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode Sum'
 * '<S107>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Integral'
 * '<S108>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Ngain'
 * '<S109>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/postSat Signal'
 * '<S110>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/preSat Signal'
 * '<S111>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S112>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S113>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S114>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/D Gain/Disabled'
 * '<S115>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter/Disabled'
 * '<S116>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Filter ICs/Disabled'
 * '<S117>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/I Gain/Internal Parameters'
 * '<S118>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain/Passthrough'
 * '<S119>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S120>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator/Discrete'
 * '<S121>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Integrator ICs/Internal IC'
 * '<S122>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S123>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/N Gain/Disabled'
 * '<S124>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/P Copy/Disabled'
 * '<S125>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S126>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Reset Signal/Disabled'
 * '<S127>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation/Enabled'
 * '<S128>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Saturation Fdbk/Disabled'
 * '<S129>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum/Sum_PI'
 * '<S130>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Sum Fdbk/Disabled'
 * '<S131>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode/Disabled'
 * '<S132>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S133>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Integral/Passthrough'
 * '<S134>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S135>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/postSat Signal/Forward_Path'
 * '<S136>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller3/preSat Signal/Forward_Path'
 * '<S137>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup'
 * '<S138>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/D Gain'
 * '<S139>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter'
 * '<S140>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter ICs'
 * '<S141>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/I Gain'
 * '<S142>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain'
 * '<S143>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain Fdbk'
 * '<S144>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator'
 * '<S145>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator ICs'
 * '<S146>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Copy'
 * '<S147>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Gain'
 * '<S148>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/P Copy'
 * '<S149>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Parallel P Gain'
 * '<S150>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Reset Signal'
 * '<S151>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation'
 * '<S152>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation Fdbk'
 * '<S153>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum'
 * '<S154>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum Fdbk'
 * '<S155>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode'
 * '<S156>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode Sum'
 * '<S157>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Integral'
 * '<S158>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Ngain'
 * '<S159>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/postSat Signal'
 * '<S160>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/preSat Signal'
 * '<S161>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel'
 * '<S162>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S163>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S164>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/D Gain/Disabled'
 * '<S165>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter/Disabled'
 * '<S166>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Filter ICs/Disabled'
 * '<S167>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/I Gain/Internal Parameters'
 * '<S168>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain/Passthrough'
 * '<S169>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Ideal P Gain Fdbk/Disabled'
 * '<S170>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator/Discrete'
 * '<S171>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Integrator ICs/Internal IC'
 * '<S172>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Copy/Disabled wSignal Specification'
 * '<S173>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/N Gain/Disabled'
 * '<S174>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/P Copy/Disabled'
 * '<S175>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Parallel P Gain/Internal Parameters'
 * '<S176>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Reset Signal/Disabled'
 * '<S177>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation/Enabled'
 * '<S178>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Saturation Fdbk/Disabled'
 * '<S179>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum/Sum_PI'
 * '<S180>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Sum Fdbk/Disabled'
 * '<S181>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode/Disabled'
 * '<S182>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tracking Mode Sum/Passthrough'
 * '<S183>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Integral/Passthrough'
 * '<S184>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/Tsamp - Ngain/Passthrough'
 * '<S185>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/postSat Signal/Forward_Path'
 * '<S186>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller7/preSat Signal/Forward_Path'
 * '<S187>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup'
 * '<S188>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/D Gain'
 * '<S189>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter'
 * '<S190>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter ICs'
 * '<S191>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/I Gain'
 * '<S192>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain'
 * '<S193>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain Fdbk'
 * '<S194>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator'
 * '<S195>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator ICs'
 * '<S196>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Copy'
 * '<S197>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Gain'
 * '<S198>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/P Copy'
 * '<S199>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Parallel P Gain'
 * '<S200>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Reset Signal'
 * '<S201>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation'
 * '<S202>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation Fdbk'
 * '<S203>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum'
 * '<S204>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum Fdbk'
 * '<S205>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode'
 * '<S206>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode Sum'
 * '<S207>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Integral'
 * '<S208>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Ngain'
 * '<S209>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/postSat Signal'
 * '<S210>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/preSat Signal'
 * '<S211>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel'
 * '<S212>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S213>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S214>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/D Gain/Disabled'
 * '<S215>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter/Disabled'
 * '<S216>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Filter ICs/Disabled'
 * '<S217>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/I Gain/Internal Parameters'
 * '<S218>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain/Passthrough'
 * '<S219>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Ideal P Gain Fdbk/Disabled'
 * '<S220>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator/Discrete'
 * '<S221>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Integrator ICs/Internal IC'
 * '<S222>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Copy/Disabled wSignal Specification'
 * '<S223>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/N Gain/Disabled'
 * '<S224>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/P Copy/Disabled'
 * '<S225>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Parallel P Gain/Internal Parameters'
 * '<S226>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Reset Signal/Disabled'
 * '<S227>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation/Enabled'
 * '<S228>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Saturation Fdbk/Disabled'
 * '<S229>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum/Sum_PI'
 * '<S230>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Sum Fdbk/Disabled'
 * '<S231>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode/Disabled'
 * '<S232>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tracking Mode Sum/Passthrough'
 * '<S233>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Integral/Passthrough'
 * '<S234>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/Tsamp - Ngain/Passthrough'
 * '<S235>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/postSat Signal/Forward_Path'
 * '<S236>' : 'Torque_Vectoring_2024/TC/CLTC /PID Controller8/preSat Signal/Forward_Path'
 * '<S237>' : 'Torque_Vectoring_2024/TV /Ripartizione'
 */
#endif                                 /* RTW_HEADER_Torque_Vectoring_2024_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
