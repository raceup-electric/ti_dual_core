/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024_discreto.h
 *
 * Code generated for Simulink model 'Torque_Vectoring_2024_discreto'.
 *
 * Model version                  : 2.24
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Wed Aug  7 11:14:38 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Torque_Vectoring_2024_discreto_h_
#define RTW_HEADER_Torque_Vectoring_2024_discreto_h_
#ifndef Torque_Vectoring_2024_discreto_COMMON_INCLUDES_
#define Torque_Vectoring_2024_discreto_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                     /* Torque_Vectoring_2024_discreto_COMMON_INCLUDES_ */

#include <stddef.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define Torque_Vectoring_2024_discreto_M (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE[4];         /* '<S63>/Integrator' */
  real_T Memory1_PreviousInput[2];     /* '<S3>/Memory1' */
  real_T Memory_PreviousInput_g[4];    /* '<S21>/Memory' */
  real_T Memory2_PreviousInput[2];     /* '<S3>/Memory2' */
  real_T Memory_PreviousInput_o[4];    /* '<S14>/Memory' */
  real_T Memory_PreviousInput;         /* '<Root>/Memory' */
  real_T Memory4_PreviousInput;        /* '<S3>/Memory4' */
  real_T Divide_DWORK4;                /* '<S14>/Divide' */
  real_T Memory_PreviousInput_b;       /* '<S24>/Memory' */
  boolean_T Delay1_DSTATE[150];        /* '<S24>/Delay1' */
} DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [1 0]
   * Referenced by: '<S14>/Constant4'
   */
  real_T Constant4_Value[2];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ax;                           /* '<Root>/ax' */
  real_T ay;                           /* '<Root>/ay' */
  real_T yaw_r;                        /* '<Root>/yaw_r' */
  real_T throttle;                     /* '<Root>/throttle' */
  real_T regenpaddle;                  /* '<Root>/regen paddle' */
  real_T brakepressurefront;           /* '<Root>/brake pressure front' */
  real_T brakepressurerear;            /* '<Root>/brake pressure rear' */
  real_T steering;                     /* '<Root>/steering' */
  real_T rpm[4];                       /* '<Root>/rpm' */
  real_T voltage;                      /* '<Root>/voltage' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T T_pos[4];                     /* '<Root>/T_pos' */
  real_T T_neg[4];                     /* '<Root>/T_neg' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T Pmax;                         /* Variable: Pmax
                                        * Referenced by: '<S22>/Total Power Limit'
                                        */
  real_T TC_map[3];                    /* Variable: TC_map
                                        * Referenced by:
                                        *   '<S60>/Integral Gain'
                                        *   '<S68>/Proportional Gain'
                                        */
  real_T T_max;                        /* Variable: T_max
                                        * Referenced by:
                                        *   '<Root>/Constant1'
                                        *   '<S9>/Gain'
                                        */
  real_T offset_brake_csi;             /* Variable: offset_brake_csi
                                        * Referenced by:
                                        *   '<Root>/Constant2'
                                        *   '<Root>/Gain12'
                                        */
  real_T offset_cornering;             /* Variable: offset_cornering
                                        * Referenced by:
                                        *   '<S80>/Constant1'
                                        *   '<S80>/Multiply'
                                        */
  real_T offset_throttle_csi;          /* Variable: offset_throttle_csi
                                        * Referenced by:
                                        *   '<S9>/Constant2'
                                        *   '<S9>/Gain4'
                                        */
  real_T regen_on;                     /* Variable: regen_on
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T toe_f;                        /* Variable: toe_f
                                        * Referenced by: '<S12>/Constant2'
                                        */
  real_T toe_r;                        /* Variable: toe_r
                                        * Referenced by: '<S12>/Constant4'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void Torque_Vectoring_2024_forsecontiu_initialize(void);
extern void Torque_Vectoring_2024_forsecontiu_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S22>/Scope' : Unused code path elimination
 * Block '<S25>/Scope1' : Unused code path elimination
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
 * '<Root>' : 'Torque_Vectoring_2024_discreto'
 * '<S1>'   : 'Torque_Vectoring_2024_discreto/Csi'
 * '<S2>'   : 'Torque_Vectoring_2024_discreto/Delta estimators'
 * '<S3>'   : 'Torque_Vectoring_2024_discreto/KF'
 * '<S4>'   : 'Torque_Vectoring_2024_discreto/Power Limitation'
 * '<S5>'   : 'Torque_Vectoring_2024_discreto/Re'
 * '<S6>'   : 'Torque_Vectoring_2024_discreto/Regenerative Power'
 * '<S7>'   : 'Torque_Vectoring_2024_discreto/Regenerative braking'
 * '<S8>'   : 'Torque_Vectoring_2024_discreto/TC'
 * '<S9>'   : 'Torque_Vectoring_2024_discreto/TV '
 * '<S10>'  : 'Torque_Vectoring_2024_discreto/Torque limit'
 * '<S11>'  : 'Torque_Vectoring_2024_discreto/Vertical loads calculator'
 * '<S12>'  : 'Torque_Vectoring_2024_discreto/Wheels Angle '
 * '<S13>'  : 'Torque_Vectoring_2024_discreto/KF/Compare To Constant'
 * '<S14>'  : 'Torque_Vectoring_2024_discreto/KF/Matrices'
 * '<S15>'  : 'Torque_Vectoring_2024_discreto/KF/Measurement'
 * '<S16>'  : 'Torque_Vectoring_2024_discreto/KF/Measurement Update'
 * '<S17>'  : 'Torque_Vectoring_2024_discreto/KF/Time Update'
 * '<S18>'  : 'Torque_Vectoring_2024_discreto/KF/Measurement/Compare To Constant2'
 * '<S19>'  : 'Torque_Vectoring_2024_discreto/KF/Measurement/Compare To Constant3'
 * '<S20>'  : 'Torque_Vectoring_2024_discreto/KF/Measurement/Compare To Constant4'
 * '<S21>'  : 'Torque_Vectoring_2024_discreto/KF/Measurement/Weights'
 * '<S22>'  : 'Torque_Vectoring_2024_discreto/Power Limitation/Subsystem'
 * '<S23>'  : 'Torque_Vectoring_2024_discreto/Regenerative Power/Compare To Zero'
 * '<S24>'  : 'Torque_Vectoring_2024_discreto/Regenerative Power/ramp'
 * '<S25>'  : 'Torque_Vectoring_2024_discreto/Regenerative braking/Engine'
 * '<S26>'  : 'Torque_Vectoring_2024_discreto/Regenerative braking/Torque limit'
 * '<S27>'  : 'Torque_Vectoring_2024_discreto/Regenerative braking/csi_regen'
 * '<S28>'  : 'Torque_Vectoring_2024_discreto/Regenerative braking/Engine/Id Iq'
 * '<S29>'  : 'Torque_Vectoring_2024_discreto/Regenerative braking/Engine/MATLAB Function'
 * '<S30>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller'
 * '<S31>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller'
 * '<S32>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Anti-windup'
 * '<S33>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/D Gain'
 * '<S34>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Filter'
 * '<S35>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Filter ICs'
 * '<S36>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/I Gain'
 * '<S37>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Ideal P Gain'
 * '<S38>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Ideal P Gain Fdbk'
 * '<S39>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Integrator'
 * '<S40>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Integrator ICs'
 * '<S41>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/N Copy'
 * '<S42>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/N Gain'
 * '<S43>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/P Copy'
 * '<S44>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Parallel P Gain'
 * '<S45>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Reset Signal'
 * '<S46>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Saturation'
 * '<S47>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Saturation Fdbk'
 * '<S48>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Sum'
 * '<S49>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Sum Fdbk'
 * '<S50>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tracking Mode'
 * '<S51>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tracking Mode Sum'
 * '<S52>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tsamp - Integral'
 * '<S53>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tsamp - Ngain'
 * '<S54>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/postSat Signal'
 * '<S55>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/preSat Signal'
 * '<S56>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Anti-windup/Passthrough'
 * '<S57>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/D Gain/Disabled'
 * '<S58>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Filter/Disabled'
 * '<S59>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Filter ICs/Disabled'
 * '<S60>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/I Gain/Internal Parameters'
 * '<S61>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Ideal P Gain/Passthrough'
 * '<S62>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S63>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Integrator/Discrete'
 * '<S64>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Integrator ICs/Internal IC'
 * '<S65>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S66>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/N Gain/Disabled'
 * '<S67>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/P Copy/Disabled'
 * '<S68>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S69>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Reset Signal/Disabled'
 * '<S70>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Saturation/Enabled'
 * '<S71>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Saturation Fdbk/Disabled'
 * '<S72>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Sum/Sum_PI'
 * '<S73>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Sum Fdbk/Disabled'
 * '<S74>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tracking Mode/Disabled'
 * '<S75>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S76>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S77>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S78>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/postSat Signal/Forward_Path'
 * '<S79>'  : 'Torque_Vectoring_2024_discreto/TC/PI controller/PID Controller/preSat Signal/Forward_Path'
 * '<S80>'  : 'Torque_Vectoring_2024_discreto/TV /Ripartizione'
 */
#endif                        /* RTW_HEADER_Torque_Vectoring_2024_discreto_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
