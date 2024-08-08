/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024_discreto_data.c
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

#include "Torque_Vectoring_2024_forsecontiu.h"

/* Block parameters (default storage) */
P rtP = {
  /* Variable: Pmax
   * Referenced by: '<S22>/Total Power Limit'
   */
  50000.0,

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
  15.0,

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

  /* Variable: regen_on
   * Referenced by: '<Root>/Gain2'
   */
  0.0,

  /* Variable: toe_f
   * Referenced by: '<S12>/Constant2'
   */
  0.0,

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
