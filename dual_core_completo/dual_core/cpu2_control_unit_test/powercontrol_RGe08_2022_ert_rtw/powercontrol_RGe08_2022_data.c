/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: powercontrol_RGe08_2022_data.c
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

#include "powercontrol_RGe08_2022.h"

/* Block parameters (default storage) */
P_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_P = {
  /* Variable: Mmax
   * Referenced by:
   *   '<S1>/  limite massimo'
   *   '<S1>/limite massimo  '
   */
  21.0,

  /* Variable: Pe_lim
   * Referenced by: '<Root>/Constant5'
   */
  80000.0,

  /* Variable: kp_pl
   * Referenced by: '<S1>/Gain1'
   */
  0.0015,

  /* Mask Parameter: DiscreteDerivative_ICPrevScaled
   * Referenced by: '<S2>/UD'
   */
  0.0F,

  /* Expression: 0
   * Referenced by: '<Root>/fattore di riduzione nullo '
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<Root>/err'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<Root>/minimo'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/switch logico  '
   */
  0.0,

  /* Expression: 0.99
   * Referenced by: '<Root>/Gain'
   */
  0.99,

  /* Expression: 78500
   * Referenced by: '<Root>/Constant'
   */
  78500.0,

  /* Expression: 0
   * Referenced by: '<Root>/Switch3'
   */
  0.0,

  /* Expression: ki_pl*Tsc
   * Referenced by: '<S1>/Gain2'
   */
  0.16,

  /* Expression: 0
   * Referenced by: '<S1>/Unit Delay1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/  limite massimo'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/limite massimo  '
   */
  0.0,

  /* Expression: 1000
   * Referenced by: '<Root>/ constant'
   */
  1000.0,

  /* Expression: 0
   * Referenced by: '<Root>/Switch'
   */
  0.0,

  /* Computed Parameter: Gain4_Gain
   * Referenced by: '<Root>/Gain4'
   */
  0.9999F,

  /* Expression: Tsc
   * Referenced by: '<Root>/Gain1'
   */
  0.01F,

  /* Computed Parameter: TSamp_WtEt
   * Referenced by: '<S2>/TSamp'
   */
  100.0F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
