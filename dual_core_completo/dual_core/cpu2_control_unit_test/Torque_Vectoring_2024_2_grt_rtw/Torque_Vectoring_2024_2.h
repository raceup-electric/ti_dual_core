/*
 * Torque_Vectoring_2024_2.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Torque_Vectoring_2024_2".
 *
 * Model version              : 5.3
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Sat Mar 22 11:17:47 2025
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Torque_Vectoring_2024_2_h_
#define Torque_Vectoring_2024_2_h_
#ifndef Torque_Vectoring_2024_2_COMMON_INCLUDES_
#define Torque_Vectoring_2024_2_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                            /* Torque_Vectoring_2024_2_COMMON_INCLUDES_ */

#include "Torque_Vectoring_2024_2_types.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <float.h>
#include <string.h>
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T u;                            /* '<S117>/Integrator' */
  real_T u_m;                          /* '<S225>/Integrator' */
  real_T u_a;                          /* '<S63>/Integrator' */
  real_T u_g;                          /* '<S171>/Integrator' */
  real_T Memory_PreviousInput[4];      /* '<S12>/Memory' */
  real_T Divide_DWORK4;                /* '<S12>/Divide' */
  real_T Memory_PreviousInput_k;       /* '<Root>/Memory' */
  real_T Memory1_PreviousInput[2];     /* '<S3>/Memory1' */
  real_T Memory_PreviousInput_h[4];    /* '<S19>/Memory' */
  real_T Memory2_PreviousInput[2];     /* '<S3>/Memory2' */
  real32_T Memory4_PreviousInput;      /* '<S3>/Memory4' */
} DW_Torque_Vectoring_2024_2_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Transpose2[2];          /* '<S12>/Transpose2' */
  const real_T B[4];                   /* '<S12>/Gain3' */
  const real_T Exp2;                   /* '<S19>/Exp2' */
  const real_T Exp3;                   /* '<S19>/Exp3' */
  const real_T Gain;                   /* '<S10>/Gain' */
} ConstB_Torque_Vectoring_2024_2_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [1 0]
   * Referenced by: '<S12>/Constant4'
   */
  real_T Constant4_Value[2];

  /* Expression: Q
   * Referenced by: '<S12>/Constant7'
   */
  real_T Constant7_Value_d[4];
} ConstP_Torque_Vectoring_2024_2_T;

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
  real32_T rpm[4];                     /* '<Root>/rpm' */
  real32_T voltage;                    /* '<Root>/voltage' */
} ExtU_Torque_Vectoring_2024_2_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T T_pos[4];                     /* '<Root>/T_pos' */
  real_T T_neg[4];                     /* '<Root>/T_neg' */
  real_T TC_CUT[4];                    /* '<Root>/TC_CUT' */
  real_T lambda[4];                    /* '<Root>/lambda' */
  real_T vx_est;                       /* '<Root>/vx_est' */
  real_T wR[4];                        /* '<Root>/wR' */
} ExtY_Torque_Vectoring_2024_2_T;

/* Parameters (default storage) */
struct P_Torque_Vectoring_2024_2_T_ {
  real_T Pmax;                         /* Variable: Pmax
                                        * Referenced by: '<S20>/Total Power Limit'
                                        */
  real_T TC_CL_I_R;                    /* Variable: TC_CL_I_R
                                        * Referenced by:
                                        *   '<S60>/Integral Gain'
                                        *   '<S114>/Integral Gain'
                                        *   '<S168>/Integral Gain'
                                        *   '<S222>/Integral Gain'
                                        */
  real_T TC_CL_P_R;                    /* Variable: TC_CL_P_R
                                        * Referenced by:
                                        *   '<S68>/Proportional Gain'
                                        *   '<S122>/Proportional Gain'
                                        *   '<S176>/Proportional Gain'
                                        *   '<S230>/Proportional Gain'
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
                                        * Referenced by:
                                        *   '<Root>/Constant1'
                                        *   '<S7>/Gain'
                                        */
  real_T offset_cornering;             /* Variable: offset_cornering
                                        * Referenced by:
                                        *   '<S243>/Constant1'
                                        *   '<S243>/Multiply'
                                        */
  real_T offset_throttle_csi;          /* Variable: offset_throttle_csi
                                        * Referenced by:
                                        *   '<S7>/Constant2'
                                        *   '<S7>/Gain4'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Torque_Vectoring_2024_2_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_P;

/* Block states (default storage) */
extern DW_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_Y;
extern const ConstB_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_ConstP;

/* Model entry point functions */
extern void Torque_Vectoring_2024_2_initialize(void);
extern void Torque_Vectoring_2024_2_step(void);
extern void Torque_Vectoring_2024_2_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Torque_Vectoring_2024_2_T *const Torque_Vectoring_2024_2_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Saturation4' : Unused code path elimination
 * Block '<Root>/Saturation7' : Unused code path elimination
 * Block '<Root>/Saturation8' : Unused code path elimination
 * Block '<Root>/Saturation9' : Unused code path elimination
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
 * '<Root>' : 'Torque_Vectoring_2024_2'
 * '<S1>'   : 'Torque_Vectoring_2024_2/Csi'
 * '<S2>'   : 'Torque_Vectoring_2024_2/Delta estimators'
 * '<S3>'   : 'Torque_Vectoring_2024_2/KF'
 * '<S4>'   : 'Torque_Vectoring_2024_2/Power Limitation'
 * '<S5>'   : 'Torque_Vectoring_2024_2/Re'
 * '<S6>'   : 'Torque_Vectoring_2024_2/TC'
 * '<S7>'   : 'Torque_Vectoring_2024_2/TV '
 * '<S8>'   : 'Torque_Vectoring_2024_2/Torque limit'
 * '<S9>'   : 'Torque_Vectoring_2024_2/Vertical loads calculator'
 * '<S10>'  : 'Torque_Vectoring_2024_2/Wheels Angle '
 * '<S11>'  : 'Torque_Vectoring_2024_2/KF/Compare To Constant'
 * '<S12>'  : 'Torque_Vectoring_2024_2/KF/Matrices'
 * '<S13>'  : 'Torque_Vectoring_2024_2/KF/Measurement'
 * '<S14>'  : 'Torque_Vectoring_2024_2/KF/Measurement Update'
 * '<S15>'  : 'Torque_Vectoring_2024_2/KF/Time Update'
 * '<S16>'  : 'Torque_Vectoring_2024_2/KF/Measurement/Compare To Constant2'
 * '<S17>'  : 'Torque_Vectoring_2024_2/KF/Measurement/Compare To Constant3'
 * '<S18>'  : 'Torque_Vectoring_2024_2/KF/Measurement/Compare To Constant4'
 * '<S19>'  : 'Torque_Vectoring_2024_2/KF/Measurement/Weights'
 * '<S20>'  : 'Torque_Vectoring_2024_2/Power Limitation/Subsystem'
 * '<S21>'  : 'Torque_Vectoring_2024_2/TC/CLTC '
 * '<S22>'  : 'Torque_Vectoring_2024_2/TC/Slip Calculation'
 * '<S23>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1'
 * '<S24>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3'
 * '<S25>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7'
 * '<S26>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8'
 * '<S27>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Anti-windup'
 * '<S28>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/D Gain'
 * '<S29>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/External Derivative'
 * '<S30>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Filter'
 * '<S31>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Filter ICs'
 * '<S32>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/I Gain'
 * '<S33>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Ideal P Gain'
 * '<S34>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Ideal P Gain Fdbk'
 * '<S35>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Integrator'
 * '<S36>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Integrator ICs'
 * '<S37>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/N Copy'
 * '<S38>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/N Gain'
 * '<S39>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/P Copy'
 * '<S40>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Parallel P Gain'
 * '<S41>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Reset Signal'
 * '<S42>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Saturation'
 * '<S43>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Saturation Fdbk'
 * '<S44>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Sum'
 * '<S45>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Sum Fdbk'
 * '<S46>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tracking Mode'
 * '<S47>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tracking Mode Sum'
 * '<S48>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tsamp - Integral'
 * '<S49>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tsamp - Ngain'
 * '<S50>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/postSat Signal'
 * '<S51>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/preInt Signal'
 * '<S52>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/preSat Signal'
 * '<S53>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S54>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S55>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S56>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/D Gain/Disabled'
 * '<S57>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/External Derivative/Disabled'
 * '<S58>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Filter/Disabled'
 * '<S59>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Filter ICs/Disabled'
 * '<S60>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/I Gain/Internal Parameters'
 * '<S61>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Ideal P Gain/Passthrough'
 * '<S62>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S63>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Integrator/Discrete'
 * '<S64>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Integrator ICs/Internal IC'
 * '<S65>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S66>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/N Gain/Disabled'
 * '<S67>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/P Copy/Disabled'
 * '<S68>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S69>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Reset Signal/Disabled'
 * '<S70>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Saturation/Enabled'
 * '<S71>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Saturation Fdbk/Disabled'
 * '<S72>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Sum/Sum_PI'
 * '<S73>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Sum Fdbk/Disabled'
 * '<S74>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tracking Mode/Disabled'
 * '<S75>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S76>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S77>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S78>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/postSat Signal/Forward_Path'
 * '<S79>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/preInt Signal/Internal PreInt'
 * '<S80>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller1/preSat Signal/Forward_Path'
 * '<S81>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Anti-windup'
 * '<S82>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/D Gain'
 * '<S83>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/External Derivative'
 * '<S84>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Filter'
 * '<S85>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Filter ICs'
 * '<S86>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/I Gain'
 * '<S87>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Ideal P Gain'
 * '<S88>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Ideal P Gain Fdbk'
 * '<S89>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Integrator'
 * '<S90>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Integrator ICs'
 * '<S91>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/N Copy'
 * '<S92>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/N Gain'
 * '<S93>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/P Copy'
 * '<S94>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Parallel P Gain'
 * '<S95>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Reset Signal'
 * '<S96>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Saturation'
 * '<S97>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Saturation Fdbk'
 * '<S98>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Sum'
 * '<S99>'  : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Sum Fdbk'
 * '<S100>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tracking Mode'
 * '<S101>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tracking Mode Sum'
 * '<S102>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tsamp - Integral'
 * '<S103>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tsamp - Ngain'
 * '<S104>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/postSat Signal'
 * '<S105>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/preInt Signal'
 * '<S106>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/preSat Signal'
 * '<S107>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S108>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S109>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S110>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/D Gain/Disabled'
 * '<S111>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/External Derivative/Disabled'
 * '<S112>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Filter/Disabled'
 * '<S113>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Filter ICs/Disabled'
 * '<S114>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/I Gain/Internal Parameters'
 * '<S115>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Ideal P Gain/Passthrough'
 * '<S116>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S117>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Integrator/Discrete'
 * '<S118>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Integrator ICs/Internal IC'
 * '<S119>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S120>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/N Gain/Disabled'
 * '<S121>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/P Copy/Disabled'
 * '<S122>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S123>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Reset Signal/Disabled'
 * '<S124>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Saturation/Enabled'
 * '<S125>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Saturation Fdbk/Disabled'
 * '<S126>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Sum/Sum_PI'
 * '<S127>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Sum Fdbk/Disabled'
 * '<S128>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tracking Mode/Disabled'
 * '<S129>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S130>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tsamp - Integral/TsSignalSpecification'
 * '<S131>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S132>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/postSat Signal/Forward_Path'
 * '<S133>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/preInt Signal/Internal PreInt'
 * '<S134>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller3/preSat Signal/Forward_Path'
 * '<S135>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Anti-windup'
 * '<S136>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/D Gain'
 * '<S137>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/External Derivative'
 * '<S138>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Filter'
 * '<S139>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Filter ICs'
 * '<S140>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/I Gain'
 * '<S141>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Ideal P Gain'
 * '<S142>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Ideal P Gain Fdbk'
 * '<S143>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Integrator'
 * '<S144>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Integrator ICs'
 * '<S145>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/N Copy'
 * '<S146>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/N Gain'
 * '<S147>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/P Copy'
 * '<S148>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Parallel P Gain'
 * '<S149>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Reset Signal'
 * '<S150>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Saturation'
 * '<S151>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Saturation Fdbk'
 * '<S152>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Sum'
 * '<S153>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Sum Fdbk'
 * '<S154>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tracking Mode'
 * '<S155>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tracking Mode Sum'
 * '<S156>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tsamp - Integral'
 * '<S157>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tsamp - Ngain'
 * '<S158>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/postSat Signal'
 * '<S159>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/preInt Signal'
 * '<S160>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/preSat Signal'
 * '<S161>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel'
 * '<S162>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S163>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S164>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/D Gain/Disabled'
 * '<S165>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/External Derivative/Disabled'
 * '<S166>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Filter/Disabled'
 * '<S167>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Filter ICs/Disabled'
 * '<S168>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/I Gain/Internal Parameters'
 * '<S169>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Ideal P Gain/Passthrough'
 * '<S170>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Ideal P Gain Fdbk/Disabled'
 * '<S171>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Integrator/Discrete'
 * '<S172>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Integrator ICs/Internal IC'
 * '<S173>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/N Copy/Disabled wSignal Specification'
 * '<S174>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/N Gain/Disabled'
 * '<S175>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/P Copy/Disabled'
 * '<S176>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Parallel P Gain/Internal Parameters'
 * '<S177>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Reset Signal/Disabled'
 * '<S178>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Saturation/Enabled'
 * '<S179>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Saturation Fdbk/Disabled'
 * '<S180>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Sum/Sum_PI'
 * '<S181>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Sum Fdbk/Disabled'
 * '<S182>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tracking Mode/Disabled'
 * '<S183>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tracking Mode Sum/Passthrough'
 * '<S184>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tsamp - Integral/TsSignalSpecification'
 * '<S185>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/Tsamp - Ngain/Passthrough'
 * '<S186>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/postSat Signal/Forward_Path'
 * '<S187>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/preInt Signal/Internal PreInt'
 * '<S188>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller7/preSat Signal/Forward_Path'
 * '<S189>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Anti-windup'
 * '<S190>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/D Gain'
 * '<S191>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/External Derivative'
 * '<S192>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Filter'
 * '<S193>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Filter ICs'
 * '<S194>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/I Gain'
 * '<S195>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Ideal P Gain'
 * '<S196>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Ideal P Gain Fdbk'
 * '<S197>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Integrator'
 * '<S198>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Integrator ICs'
 * '<S199>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/N Copy'
 * '<S200>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/N Gain'
 * '<S201>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/P Copy'
 * '<S202>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Parallel P Gain'
 * '<S203>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Reset Signal'
 * '<S204>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Saturation'
 * '<S205>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Saturation Fdbk'
 * '<S206>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Sum'
 * '<S207>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Sum Fdbk'
 * '<S208>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tracking Mode'
 * '<S209>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tracking Mode Sum'
 * '<S210>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tsamp - Integral'
 * '<S211>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tsamp - Ngain'
 * '<S212>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/postSat Signal'
 * '<S213>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/preInt Signal'
 * '<S214>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/preSat Signal'
 * '<S215>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel'
 * '<S216>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S217>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S218>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/D Gain/Disabled'
 * '<S219>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/External Derivative/Disabled'
 * '<S220>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Filter/Disabled'
 * '<S221>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Filter ICs/Disabled'
 * '<S222>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/I Gain/Internal Parameters'
 * '<S223>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Ideal P Gain/Passthrough'
 * '<S224>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Ideal P Gain Fdbk/Disabled'
 * '<S225>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Integrator/Discrete'
 * '<S226>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Integrator ICs/Internal IC'
 * '<S227>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/N Copy/Disabled wSignal Specification'
 * '<S228>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/N Gain/Disabled'
 * '<S229>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/P Copy/Disabled'
 * '<S230>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Parallel P Gain/Internal Parameters'
 * '<S231>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Reset Signal/Disabled'
 * '<S232>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Saturation/Enabled'
 * '<S233>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Saturation Fdbk/Disabled'
 * '<S234>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Sum/Sum_PI'
 * '<S235>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Sum Fdbk/Disabled'
 * '<S236>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tracking Mode/Disabled'
 * '<S237>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tracking Mode Sum/Passthrough'
 * '<S238>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tsamp - Integral/TsSignalSpecification'
 * '<S239>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/Tsamp - Ngain/Passthrough'
 * '<S240>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/postSat Signal/Forward_Path'
 * '<S241>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/preInt Signal/Internal PreInt'
 * '<S242>' : 'Torque_Vectoring_2024_2/TC/CLTC /PID Controller8/preSat Signal/Forward_Path'
 * '<S243>' : 'Torque_Vectoring_2024_2/TV /Ripartizione'
 */
#endif                                 /* Torque_Vectoring_2024_2_h_ */
