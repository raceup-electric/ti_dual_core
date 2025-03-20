/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: powercontrol_RGe08_2022.h
 *
 * Code generated for Simulink model 'powercontrol_RGe08_2022'.
 *
 * Model version                  : 2.0
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Thu Mar 20 10:30:58 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_powercontrol_RGe08_2022_h_
#define RTW_HEADER_powercontrol_RGe08_2022_h_
#ifndef powercontrol_RGe08_2022_COMMON_INCLUDES_
#define powercontrol_RGe08_2022_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "../rigen_fun_simulink22_ert_rtw/rigen_fun_simulink22.h"
#endif                            /* powercontrol_RGe08_2022_COMMON_INCLUDES_ */

#include "powercontrol_RGe08_2022_types.h"
#include <stddef.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  dsp_simulink_LowpassFilter_po_T obj; /* '<Root>/Lowpass Filter' */
  real_T UnitDelay1_DSTATE;            /* '<S1>/Unit Delay1' */
  real32_T UD_DSTATE;                  /* '<S2>/UD' */
  boolean_T isInitialized;             /* '<Root>/Lowpass Filter' */
} DW_powercontrol_RGe08_2022_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Vbatt;                      /* '<Root>/Vbatt' */
  real_T TorqueFL1;                    /* '<Root>/TorqueFL1' */
  real_T TorqueFR1;                    /* '<Root>/TorqueFR1' */
  real_T TorqueRL1;                    /* '<Root>/TorqueRL1' */
  real_T TorqueRR1;                    /* '<Root>/TorqueRR1' */
  real32_T DC_current;                 /* '<Root>/DC_current' */
} ExtU_powercontrol_RGe08_2022_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T TorqueFL;                     /* '<Root>/TorqueFL' */
  real_T TorqueFR;                     /* '<Root>/TorqueFR' */
  real_T TorqueRL;                     /* '<Root>/TorqueRL' */
  real_T TorqueRR;                     /* '<Root>/TorqueRR' */
} ExtY_powercontrol_RGe08_2022_T;

/* Parameters (default storage) */
struct P_powercontrol_RGe08_2022_T_ {
  real_T Mmax;                         /* Variable: Mmax
                                        * Referenced by:
                                        *   '<S1>/  limite massimo'
                                        *   '<S1>/limite massimo  '
                                        */
  real_T Pe_lim;                       /* Variable: Pe_lim
                                        * Referenced by: '<Root>/Constant5'
                                        */
  real_T kp_pl;                        /* Variable: kp_pl
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real32_T DiscreteDerivative_ICPrevScaled;
                              /* Mask Parameter: DiscreteDerivative_ICPrevScaled
                               * Referenced by: '<S2>/UD'
                               */
  real_T fattorediriduzionenullo_Value;/* Expression: 0
                                        * Referenced by: '<Root>/fattore di riduzione nullo '
                                        */
  real_T err_Value;                    /* Expression: -1
                                        * Referenced by: '<Root>/err'
                                        */
  real_T minimo_Value;                 /* Expression: 0
                                        * Referenced by: '<Root>/minimo'
                                        */
  real_T switchlogico_Threshold;       /* Expression: 0
                                        * Referenced by: '<Root>/switch logico  '
                                        */
  real_T Gain_Gain;                    /* Expression: 0.99
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 78500
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Switch3_Threshold;            /* Expression: 0
                                        * Referenced by: '<Root>/Switch3'
                                        */
  real_T Gain2_Gain;                   /* Expression: ki_pl*Tsc
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T UnitDelay1_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<S1>/Unit Delay1'
                                        */
  real_T limitemassimo_LowerSat;       /* Expression: 0
                                        * Referenced by: '<S1>/  limite massimo'
                                        */
  real_T limitemassimo_LowerSat_o;     /* Expression: 0
                                        * Referenced by: '<S1>/limite massimo  '
                                        */
  real_T constant_Value;               /* Expression: 1000
                                        * Referenced by: '<Root>/ constant'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<Root>/Switch'
                                        */
  real32_T Gain4_Gain;                 /* Computed Parameter: Gain4_Gain
                                        * Referenced by: '<Root>/Gain4'
                                        */
  real32_T Gain1_Gain;                 /* Expression: Tsc
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T TSamp_WtEt;                 /* Computed Parameter: TSamp_WtEt
                                        * Referenced by: '<S2>/TSamp'
                                        */
};
//
//typedef struct {
//  struct {
//    uint32_T wordH;
//    uint32_T wordL;
//  } words;
//} BigEndianIEEEDouble;
//
//
//typedef struct {
//  struct {
//    uint32_T wordL;
//    uint32_T wordH;
//  } words;
//} LittleEndianIEEEDouble;
//
//
//
//typedef struct {
//  union {
//    real32_T wordLreal;
//    uint32_T wordLuint;
//  } wordL;
//} IEEESingle;

/* Real-time Model Data Structure */
struct tag_RTM_powercontrol_RGe08_20_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_P;

/* Block states (default storage) */
extern DW_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_Y;

/* Model entry point functions */
extern void powercontrol_RGe08_2022_initialize(void);
extern void powercontrol_RGe08_2022_step(void);
extern void powercontrol_RGe08_2022_terminate(void);

/* Real-time Model object */
extern RT_MODEL_powercontrol_RGe08_2_T *const powercontrol_RGe08_2022_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<Root>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<Root>/Zero-Order Hold1' : Eliminated since input and output rates are identical
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
 * '<Root>' : 'powercontrol_RGe08_2022'
 * '<S1>'   : 'powercontrol_RGe08_2022/ '
 * '<S2>'   : 'powercontrol_RGe08_2022/Discrete Derivative'
 * '<S3>'   : 'powercontrol_RGe08_2022/MATLAB Function'
 * '<S4>'   : 'powercontrol_RGe08_2022/i'
 */
#endif                               /* RTW_HEADER_powercontrol_RGe08_2022_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
