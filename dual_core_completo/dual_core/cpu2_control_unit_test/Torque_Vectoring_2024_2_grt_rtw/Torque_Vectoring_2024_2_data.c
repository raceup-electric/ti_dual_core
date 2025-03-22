/*
 * Torque_Vectoring_2024_2_data.c
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

#include "Torque_Vectoring_2024_2.h"

/* Invariant block signals (default storage) */
const ConstB_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_ConstB = {
  { 1.0, 0.0 },                        /* '<S12>/Transpose2' */

  { 0.01, 0.0, 0.0, 0.01 },            /* '<S12>/Gain3' */
  2.25,                                /* '<S19>/Exp2' */
  49.0,                                /* '<S19>/Exp3' */
  -0.0                                 /* '<S10>/Gain' */
};

/* Block parameters (default storage) */
P_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_P = {
  /* Variable: Pmax
   * Referenced by: '<S20>/Total Power Limit'
   */
  80000.0,

  /* Variable: TC_CL_I_R
   * Referenced by:
   *   '<S60>/Integral Gain'
   *   '<S114>/Integral Gain'
   *   '<S168>/Integral Gain'
   *   '<S222>/Integral Gain'
   */
  0.75,

  /* Variable: TC_CL_P_R
   * Referenced by:
   *   '<S68>/Proportional Gain'
   *   '<S122>/Proportional Gain'
   *   '<S176>/Proportional Gain'
   *   '<S230>/Proportional Gain'
   */
  1.25,

  /* Variable: TC_CL_TARGET_SLIP_F
   * Referenced by: '<S21>/Desired slip front1'
   */
  0.12,

  /* Variable: TC_CL_TARGET_SLIP_R
   * Referenced by: '<S21>/Desired slip rear1'
   */
  0.12,

  /* Variable: TC_MAX_CUT
   * Referenced by: '<S21>/Constant'
   */
  1.0,

  /* Variable: TC_VX_ON_F
   * Referenced by: '<S22>/Constant3'
   */
  0.25,

  /* Variable: TC_VX_ON_R
   * Referenced by: '<S22>/Constant2'
   */
  1.0,

  /* Variable: T_max
   * Referenced by:
   *   '<Root>/Constant1'
   *   '<S7>/Gain'
   */
  21.0,

  /* Variable: offset_cornering
   * Referenced by:
   *   '<S243>/Constant1'
   *   '<S243>/Multiply'
   */
  0.5,

  /* Variable: offset_throttle_csi
   * Referenced by:
   *   '<S7>/Constant2'
   *   '<S7>/Gain4'
   */
  0.0
};

/* Constant parameters (default storage) */
const ConstP_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_ConstP = {
  /* Expression: [1 0]
   * Referenced by: '<S12>/Constant4'
   */
  { 1.0, 0.0 },

  /* Expression: Q
   * Referenced by: '<S12>/Constant7'
   */
  { 0.1, 0.0, 0.0, 0.1 }
};
