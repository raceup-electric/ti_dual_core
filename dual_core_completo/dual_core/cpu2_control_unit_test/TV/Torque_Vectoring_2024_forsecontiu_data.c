/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024_forsecontiu_data.c
 *
 * Code generated for Simulink model 'Torque_Vectoring_2024_forsecontiu'.
 *
 * Model version                  : 2.19
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Tue Aug  6 17:37:49 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Torque_Vectoring_2024_forsecontiu.h"

/* Invariant block signals (default storage) */
const ConstB rtConstB = {
  2.25,                                /* '<S21>/Exp2' */
  49.0,                                /* '<S21>/Exp3' */

  { 0.01, 0.0, 0.0, 0.01 },            /* '<S14>/Gain3' */

  { 1.0, 0.0 }                         /* '<S14>/Transpose2' */
};

/* Block parameters (default storage) */
P rtP = {
  /* Variable: Pmax
   * Referenced by: '<S22>/Total Power Limit'
   */
  40000.0,

  /* Variable: TC_map
   * Referenced by:
   *   '<S60>/Integral Gain'
   *   '<S68>/Proportional Gain'
   */
  { 0.0, 0.0, 0.0 },

  /* Variable: T_max
   * Referenced by:
   *   '<Root>/Constant1'
   *   '<S9>/Gain'
   */
  12.0,

  /* Variable: offset_brake_csi
   * Referenced by:
   *   '<Root>/Constant2'
   *   '<Root>/Gain12'
   */
  0.0,

  /* Variable: offset_cornering
   * Referenced by:
   *   '<S80>/Constant1'
   *   '<S80>/Multiply'
   */
  0.5,

  /* Variable: offset_throttle_csi
   * Referenced by:
   *   '<S9>/Constant2'
   *   '<S9>/Gain4'
   */
  0.3,

  /* Variable: toe_f
   * Referenced by: '<S12>/Constant2'
   */
  -0.017453292519943295,

  /* Variable: toe_r
   * Referenced by: '<S12>/Constant4'
   */
  0.0
};

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Expression: [1 0]
   * Referenced by: '<S14>/Constant4'
   */
  { 1.0, 0.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */