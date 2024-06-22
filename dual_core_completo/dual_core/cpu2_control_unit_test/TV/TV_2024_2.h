/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TV_2024_2.h
 *
 * Code generated for Simulink model 'TV_2024_2'.
 *
 * Model version                  : 2.0
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu May  9 13:00:30 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef TV_2024_2_h_
#define TV_2024_2_h_
#ifndef TV_2024_2_COMMON_INCLUDES_
#define TV_2024_2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* TV_2024_2_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Memory_PreviousInput[4];      /* '<S13>/Memory' */
  real_T Memory_PreviousInput_i[4];    /* '<S4>/Memory' */
  real_T Memory1_PreviousInput[2];     /* '<S3>/Memory1' */
  real_T Memory2_PreviousInput[2];     /* '<S3>/Memory2' */
  real_T Memory_PreviousInput_j[4];    /* '<S20>/Memory' */
  real_T Memory1_PreviousInput_n[4];   /* '<S10>/Memory1' */
  real_T Memory_PreviousInput_o[4];    /* '<S10>/Memory' */
  real_T Memory4_PreviousInput;        /* '<S3>/Memory4' */
  real_T Divide_DWORK4;                /* '<S13>/Divide' */
  real_T Memory_PreviousInput_g;       /* '<S22>/Memory' */
  boolean_T Delay1_DSTATE[10];         /* '<S22>/Delay1' */
} DW;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain;                   /* '<S11>/Gain' */
} ConstB;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [1 0]
   * Referenced by: '<S13>/Constant4'
   */
  real_T Constant4_Value[2];

  /* Expression: Q
   * Referenced by: '<S13>/Constant7'
   */
  real_T Constant7_Value[4];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ax;                           /* '<Root>/ax' */
  real_T ay;                           /* '<Root>/ay' */
  real_T yaw_r;                        /* '<Root>/yaw_r' */
  real_T throttle;                     /* '<Root>/throttle' */
  real_T regen;                        /* '<Root>/regen' */
  real_T brake;                        /* '<Root>/brake' */
  real_T steer;                        /* '<Root>/steer' */
  real_T rpm[4];                       /* '<Root>/rpm' */
  real_T voltage;                      /* '<Root>/voltage' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T T_pos1[4];                    /* '<Root>/T_pos1' */
  real_T T_neg1[4];                    /* '<Root>/T_neg1' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;
extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void TV_2024_2_initialize(void);
extern void TV_2024_2_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Propagation' : Unused code path elimination
 * Block '<S10>/Add10' : Unused code path elimination
 * Block '<S10>/Add9' : Unused code path elimination
 * Block '<S27>/Compare' : Unused code path elimination
 * Block '<S27>/Constant' : Unused code path elimination
 * Block '<S10>/Constant1' : Unused code path elimination
 * Block '<S10>/Constant10' : Unused code path elimination
 * Block '<S10>/Constant15' : Unused code path elimination
 * Block '<S10>/Constant5' : Unused code path elimination
 * Block '<S10>/Gain1' : Unused code path elimination
 * Block '<S10>/Gain5' : Unused code path elimination
 * Block '<S10>/Gain6' : Unused code path elimination
 * Block '<S10>/Gain7' : Unused code path elimination
 * Block '<S10>/Memory2' : Unused code path elimination
 * Block '<S10>/Memory3' : Unused code path elimination
 * Block '<S10>/Min3' : Unused code path elimination
 * Block '<S10>/Minus1' : Unused code path elimination
 * Block '<S10>/Minus2' : Unused code path elimination
 * Block '<S10>/Product1' : Unused code path elimination
 * Block '<S10>/Product3' : Unused code path elimination
 * Block '<S10>/Saturation1' : Unused code path elimination
 * Block '<S10>/err'-' : Unused code path elimination
 * Block '<S10>/err-' : Unused code path elimination
 * Block '<S10>/ktc+1' : Unused code path elimination
 * Block '<S10>/r-' : Unused code path elimination
 * Block '<Root>/Gain12' : Eliminated nontunable gain of 1
 * Block '<S8>/Gain4' : Eliminated nontunable gain of 1
 * Block '<S25>/Gain' : Eliminated nontunable gain of 1
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
 * '<Root>' : 'TV_2024_2'
 * '<S1>'   : 'TV_2024_2/Csi'
 * '<S2>'   : 'TV_2024_2/Fz1'
 * '<S3>'   : 'TV_2024_2/KF'
 * '<S4>'   : 'TV_2024_2/Re'
 * '<S5>'   : 'TV_2024_2/Regenerative'
 * '<S6>'   : 'TV_2024_2/Subsystem'
 * '<S7>'   : 'TV_2024_2/Subsystem1'
 * '<S8>'   : 'TV_2024_2/TV '
 * '<S9>'   : 'TV_2024_2/Torque limit'
 * '<S10>'  : 'TV_2024_2/Traction control'
 * '<S11>'  : 'TV_2024_2/Wheels Angle '
 * '<S12>'  : 'TV_2024_2/KF/Compare To Constant'
 * '<S13>'  : 'TV_2024_2/KF/Matrices'
 * '<S14>'  : 'TV_2024_2/KF/Measurement'
 * '<S15>'  : 'TV_2024_2/KF/Measurement Update'
 * '<S16>'  : 'TV_2024_2/KF/Time Update'
 * '<S17>'  : 'TV_2024_2/KF/Measurement/Compare To Constant2'
 * '<S18>'  : 'TV_2024_2/KF/Measurement/Compare To Constant3'
 * '<S19>'  : 'TV_2024_2/KF/Measurement/Compare To Constant4'
 * '<S20>'  : 'TV_2024_2/KF/Measurement/Weights'
 * '<S21>'  : 'TV_2024_2/Regenerative/Compare To Zero'
 * '<S22>'  : 'TV_2024_2/Regenerative/ramp'
 * '<S23>'  : 'TV_2024_2/Subsystem/Torque limit'
 * '<S24>'  : 'TV_2024_2/Subsystem/motor'
 * '<S25>'  : 'TV_2024_2/TV /Ripartizione'
 * '<S26>'  : 'TV_2024_2/Torque limit/Saturation Dynamic'
 * '<S27>'  : 'TV_2024_2/Traction control/Compare To Zero'
 * '<S28>'  : 'TV_2024_2/Traction control/Compare To Zero1'
 */
#endif                                 /* TV_2024_2_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
