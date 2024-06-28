/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TV_2024_2.c
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

#include "TV_2024_2.h"
#include <math.h>
#include "rtwtypes.h"
#include "math.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real_T rt_powd_snf(real_T u0, real_T u1);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
real_T rtNaN = -(real_T)NAN;
real_T rtInf = (real_T)INFINITY;
real_T rtMinusInf = -(real_T)INFINITY;
real32_T rtNaNF = -(real32_T)NAN;
real32_T rtInfF = (real32_T)INFINITY;
real32_T rtMinusInfF = -(real32_T)INFINITY;

/* Return rtInf needed by the generated code. */
static real_T rtGetInf(void)
{
  return rtInf;
}

/* Get rtInfF needed by the generated code. */
static real32_T rtGetInfF(void)
{
  return rtInfF;
}

/* Return rtMinusInf needed by the generated code. */
static real_T rtGetMinusInf(void)
{
  return rtMinusInf;
}

/* Return rtMinusInfF needed by the generated code. */
static real32_T rtGetMinusInfF(void)
{
  return rtMinusInfF;
}

/* Return rtNaN needed by the generated code. */
static real_T rtGetNaN(void)
{
  return rtNaN;
}

/* Return rtNaNF needed by the generated code. */
static real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void TV_2024_2_step(void)
{
  real_T rtb_A_k[4];
  real_T rtb_Product1_m[4];
  real_T rtb_K_k[2];
  real_T Memory_PreviousInput;
  real_T Memory_PreviousInput_0;
  real_T rtb_Add1_c;
  real_T rtb_Gain11_a_idx_0_tmp;
  real_T rtb_Gain11_a_idx_1_tmp;
  real_T rtb_Gain11_a_idx_2;
  real_T rtb_Gain2_nj;
  real_T rtb_Gain3_c_idx_0;
  real_T rtb_Gain3_c_idx_1;
  real_T rtb_Gain3_c_idx_2;
  real_T rtb_Product1_l_idx_0;
  real_T rtb_Product1_l_idx_1;
  real_T rtb_Product1_l_idx_2;
  real_T rtb_Product1_l_idx_3;
  real_T rtb_Product3;
  real_T rtb_Product4_idx_0;
  real_T rtb_Product4_idx_1;
  real_T rtb_Product4_idx_3;
  real_T rtb_Product_idx_0;
  real_T rtb_Product_idx_1;
  real_T rtb_Product_idx_2;
  real_T rtb_SignedSqrt;
  real_T rtb_ua;
  real_T rtb_vims_idx_0;
  real_T rtb_vims_idx_1;
  real_T rtb_vims_idx_2;
  real_T rtb_vims_idx_3;
  real_T rtb_x_k_idx_0;
  real_T rtb_x_k_idx_1;
  real_T u;
  real_T u0;
  real_T u0_0;
  real_T u_0;
  int16_T k;
  int16_T rtb_Product1_l_tmp;
  boolean_T rtb_Compare_c;

  /* SignalConversion generated from: '<S13>/Vector Concatenate' incorporates:
   *  Constant: '<S13>/Constant'
   */
  rtb_A_k[0] = 1.0;

  /* Gain: '<S13>/Gain' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[1] = -0.05 * rtDW.Memory4_PreviousInput;

  /* Gain: '<S13>/Gain1' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[2] = 0.05 * rtDW.Memory4_PreviousInput;

  /* SignalConversion generated from: '<S13>/Vector Concatenate1' incorporates:
   *  Constant: '<S13>/Constant'
   */
  rtb_A_k[3] = 1.0;

  /* Product: '<S13>/Product2' incorporates:
   *  Concatenate: '<S13>/Vector Concatenate2'
   *  Math: '<S13>/Transpose'
   *  Memory: '<S13>/Memory'
   */
  rtb_Add1_c = rtb_A_k[2];
  rtb_Gain2_nj = rtb_A_k[1];
  for (k = 0; k < 2; k++) {
    Memory_PreviousInput = rtDW.Memory_PreviousInput[k + 2];
    Memory_PreviousInput_0 = rtDW.Memory_PreviousInput[k];
    rtb_Product1_m[k] = Memory_PreviousInput * rtb_Add1_c +
      Memory_PreviousInput_0;
    rtb_Product1_m[k + 2] = Memory_PreviousInput_0 * rtb_Gain2_nj +
      Memory_PreviousInput;
  }

  /* Product: '<S13>/Product4' */
  Memory_PreviousInput_0 = 0.0;

  /* Product: '<S13>/Product2' */
  rtb_vims_idx_0 = rtb_Product1_m[1];
  rtb_vims_idx_1 = rtb_Product1_m[0];
  rtb_vims_idx_2 = rtb_Product1_m[3];
  rtb_vims_idx_3 = rtb_Product1_m[2];
  for (k = 0; k < 2; k++) {
    /* Sum: '<S13>/Add' incorporates:
     *  Concatenate: '<S13>/Vector Concatenate2'
     *  Constant: '<S13>/Constant7'
     *  Product: '<Root>/Product1'
     *  Product: '<S13>/Product2'
     */
    rtb_Add1_c = rtb_A_k[k + 2];
    rtb_Gain2_nj = rtb_A_k[k];
    Memory_PreviousInput = (rtb_Add1_c * rtb_vims_idx_0 + rtb_Gain2_nj *
      rtb_vims_idx_1) + rtConstP.Constant7_Value[k];
    rtb_Product1_m[k] = Memory_PreviousInput;

    /* Product: '<S13>/Product4' incorporates:
     *  Product: '<S13>/Product3'
     */
    rtb_Product_idx_0 = Memory_PreviousInput;

    /* Sum: '<S13>/Add' incorporates:
     *  Constant: '<S13>/Constant7'
     *  Product: '<Root>/Product1'
     *  Product: '<S13>/Product2'
     */
    Memory_PreviousInput = (rtb_Add1_c * rtb_vims_idx_2 + rtb_Gain2_nj *
      rtb_vims_idx_3) + rtConstP.Constant7_Value[k + 2];
    rtb_Product1_m[k + 2] = Memory_PreviousInput;

    /* Product: '<S13>/Product4' incorporates:
     *  Constant: '<S13>/Constant4'
     *  Math: '<S13>/Transpose2'
     *  Product: '<S13>/Product3'
     */
    rtb_Product_idx_0 += Memory_PreviousInput * 0.0;
    rtb_K_k[k] = rtb_Product_idx_0;
    Memory_PreviousInput_0 += rtConstP.Constant4_Value[k] * rtb_Product_idx_0;
  }

  /* Product: '<S13>/Divide' incorporates:
   *  Constant: '<S13>/Constant5'
   *  Product: '<S13>/Product3'
   *  Product: '<S13>/Product4'
   *  Sum: '<S13>/Add2'
   */
  rtb_K_k[0] /= Memory_PreviousInput_0 + 0.05;
  rtb_K_k[1] /= Memory_PreviousInput_0 + 0.05;

  /* Sum: '<S13>/Add1' incorporates:
   *  Constant: '<S13>/Constant4'
   *  Constant: '<S13>/Constant6'
   *  Product: '<S13>/Divide'
   *  Product: '<S13>/Product5'
   */
  rtb_Add1_c = 1.0 - rtb_K_k[0];
  rtb_Gain2_nj = 0.0 - rtb_K_k[1];
  rtb_vims_idx_0 = 0.0 - rtb_K_k[0] * 0.0;
  Memory_PreviousInput_0 = rtb_K_k[1] * 0.0;
  for (k = 0; k < 2; k++) {
    /* Product: '<S13>/Product6' incorporates:
     *  Constant: '<S13>/Constant6'
     *  Memory: '<S13>/Memory'
     *  Product: '<Root>/Product1'
     *  Sum: '<S13>/Add1'
     */
    rtb_Product1_l_tmp = k << 1U;
    Memory_PreviousInput = rtb_Product1_m[rtb_Product1_l_tmp + 1];
    rtb_vims_idx_1 = rtb_Product1_m[rtb_Product1_l_tmp];
    rtDW.Memory_PreviousInput[rtb_Product1_l_tmp] = Memory_PreviousInput *
      rtb_vims_idx_0 + rtb_vims_idx_1 * rtb_Add1_c;
    rtDW.Memory_PreviousInput[rtb_Product1_l_tmp + 1] = (1.0 -
      Memory_PreviousInput_0) * Memory_PreviousInput + rtb_vims_idx_1 *
      rtb_Gain2_nj;
  }

  /* Sum: '<S4>/Add' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Gain2'
   *  Memory: '<S4>/Memory'
   */
  Memory_PreviousInput_0 = -3.533E-6 * rtDW.Memory_PreviousInput_i[0] + 0.2032;

  /* Saturate: '<S4>/Saturation' */
  if (Memory_PreviousInput_0 > 0.2032) {
    Memory_PreviousInput_0 = 0.2032;
  } else if (Memory_PreviousInput_0 < 0.19304) {
    Memory_PreviousInput_0 = 0.19304;
  }

  /* Sum: '<S4>/Add' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Gain2'
   *  Memory: '<S4>/Memory'
   */
  u0 = -3.533E-6 * rtDW.Memory_PreviousInput_i[1] + 0.2032;

  /* Saturate: '<S4>/Saturation' */
  if (u0 > 0.2032) {
    u0 = 0.2032;
  } else if (u0 < 0.19304) {
    u0 = 0.19304;
  }

  /* Sum: '<S4>/Add' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Gain2'
   *  Memory: '<S4>/Memory'
   */
  u0_0 = -3.533E-6 * rtDW.Memory_PreviousInput_i[2] + 0.2032;

  /* Saturate: '<S4>/Saturation' */
  if (u0_0 > 0.2032) {
    u0_0 = 0.2032;
  } else if (u0_0 < 0.19304) {
    u0_0 = 0.19304;
  }

  /* Sum: '<S4>/Add' incorporates:
   *  Constant: '<S4>/Constant'
   *  Gain: '<S4>/Gain2'
   *  Memory: '<S4>/Memory'
   */
  Memory_PreviousInput = -3.533E-6 * rtDW.Memory_PreviousInput_i[3] + 0.2032;

  /* Saturate: '<S4>/Saturation' */
  if (Memory_PreviousInput > 0.2032) {
    Memory_PreviousInput = 0.2032;
  } else if (Memory_PreviousInput < 0.19304) {
    Memory_PreviousInput = 0.19304;
  }

  /* Gain: '<S2>/Gain3' incorporates:
   *  Inport: '<Root>/ay'
   */
  rtb_Add1_c = 24.884829140045444 * rtU.ay;

  /* Gain: '<S2>/Gain2' incorporates:
   *  Inport: '<Root>/ax'
   */
  rtb_Gain2_nj = 24.625407166123782 * rtU.ax;

  /* Sum: '<S16>/Sum' incorporates:
   *  Concatenate: '<S13>/Vector Concatenate2'
   *  Gain: '<S13>/Gain3'
   *  Memory: '<S3>/Memory1'
   *  Memory: '<S3>/Memory2'
   *  Product: '<S16>/Product'
   *  Product: '<S16>/Product1'
   */
  rtb_x_k_idx_0 = (rtDW.Memory1_PreviousInput[1] * rtb_A_k[2] +
                   rtDW.Memory1_PreviousInput[0]) + (0.05 *
    rtDW.Memory2_PreviousInput[0] + 0.0 * rtDW.Memory2_PreviousInput[1]);
  rtb_x_k_idx_1 = (rtDW.Memory1_PreviousInput[0] * rtb_A_k[1] +
                   rtDW.Memory1_PreviousInput[1]) + (0.0 *
    rtDW.Memory2_PreviousInput[0] + 0.05 * rtDW.Memory2_PreviousInput[1]);

  /* Gain: '<S7>/Gain3' incorporates:
   *  Inport: '<Root>/steer'
   */
  rtb_Product3 = 0.00030229102644541785 * rtU.steer;

  /* Math: '<S7>/Math Function1' incorporates:
   *  Constant: '<S7>/Constant1'
   *  Math: '<S7>/Math Function5'
   */
  rtb_SignedSqrt = rt_powd_snf(rtb_Product3, 4.0);

  /* Math: '<S7>/Square2' incorporates:
   *  Math: '<S7>/Square1'
   */
  rtb_vims_idx_0 = rtb_Product3 * rtb_Product3;

  /* Gain: '<S7>/Gain2' incorporates:
   *  Constant: '<S7>/Constant2'
   *  Gain: '<S7>/Gain9'
   *  Math: '<S7>/Math Function2'
   */
  rtb_vims_idx_1 = 63090.0 * rt_powd_snf(rtb_Product3, 3.0);

  /* Gain: '<S7>/Gain1' incorporates:
   *  Constant: '<S7>/Constant3'
   *  Gain: '<S7>/Gain10'
   *  Math: '<S7>/Math Function3'
   */
  rtb_vims_idx_2 = 2.497E+7 * rt_powd_snf(rtb_Product3, 5.0);

  /* Gain: '<S7>/Gain' incorporates:
   *  Constant: '<S7>/Constant7'
   *  Gain: '<S7>/Gain1'
   *  Gain: '<S7>/Gain11'
   *  Gain: '<S7>/Gain2'
   *  Gain: '<S7>/Gain4'
   *  Gain: '<S7>/Gain5'
   *  Gain: '<S7>/Gain6'
   *  Gain: '<S7>/Gain7'
   *  Gain: '<S7>/Gain8'
   *  Math: '<S7>/Math Function1'
   *  Math: '<S7>/Square2'
   *  Sum: '<S7>/Sum1'
   *  Sum: '<S7>/Sum2'
   */
  rtb_Product4_idx_0 = (((((-1.217E+6 * rtb_SignedSqrt + rtb_vims_idx_2) +
    rtb_vims_idx_1) + rtb_vims_idx_0 * -3034.0) + 988.7 * rtb_Product3) -
                        0.0009525) * 0.017453292519943295;
  rtb_Product4_idx_1 = (((((988.7 * rtb_Product3 + 0.0009525) + rtb_vims_idx_0 *
    3034.0) + rtb_vims_idx_1) + 1.217E+6 * rtb_SignedSqrt) + rtb_vims_idx_2) *
    0.017453292519943295;

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain4'
   *  Inport: '<Root>/rpm'
   *  Saturate: '<S4>/Saturation'
   */
  rtb_ua = 0.078947160665366667 * rtU.rpm[0] * Memory_PreviousInput_0;
  rtb_Gain3_c_idx_0 = rtb_ua;

  /* Trigonometry: '<S14>/Cos' incorporates:
   *  Gain: '<S7>/Gain'
   *  Trigonometry: '<S10>/Cos'
   */
  rtb_Gain11_a_idx_0_tmp = cos(rtb_Product4_idx_0);

  /* Product: '<S14>/Product1' incorporates:
   *  Trigonometry: '<S14>/Cos'
   */
  rtb_Product3 = rtb_Gain11_a_idx_0_tmp * rtb_ua;

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain4'
   *  Inport: '<Root>/rpm'
   *  Saturate: '<S4>/Saturation'
   */
  rtb_ua = 0.078947160665366667 * rtU.rpm[1] * u0;
  rtb_Gain3_c_idx_1 = rtb_ua;

  /* Trigonometry: '<S14>/Cos' incorporates:
   *  Gain: '<S7>/Gain'
   *  Trigonometry: '<S10>/Cos'
   */
  rtb_Gain11_a_idx_1_tmp = cos(rtb_Product4_idx_1);

  /* Product: '<S14>/Product1' incorporates:
   *  Trigonometry: '<S14>/Cos'
   */
  rtb_SignedSqrt = rtb_Gain11_a_idx_1_tmp * rtb_ua;

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain4'
   *  Inport: '<Root>/rpm'
   *  Saturate: '<S4>/Saturation'
   */
  rtb_ua = 0.078947160665366667 * rtU.rpm[2] * u0_0;
  rtb_Gain3_c_idx_2 = rtb_ua;

  /* Trigonometry: '<S14>/Cos' incorporates:
   *  SignalConversion generated from: '<S14>/Cos'
   *  Trigonometry: '<S10>/Cos'
   */
  rtb_Product4_idx_3 = cos(rtConstB.Gain);

  /* Product: '<S14>/Product1' incorporates:
   *  Trigonometry: '<S14>/Cos'
   */
  rtb_Gain11_a_idx_2 = rtb_Product4_idx_3 * rtb_ua;

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain4'
   *  Inport: '<Root>/rpm'
   *  Saturate: '<S4>/Saturation'
   */
  rtb_ua = 0.078947160665366667 * rtU.rpm[3] * Memory_PreviousInput;

  /* Sum: '<S14>/Add' incorporates:
   *  Gain: '<S14>/Multiply'
   *  Gain: '<S14>/Multiply1'
   *  Gain: '<S14>/Multiply2'
   *  Gain: '<S14>/Multiply3'
   *  Inport: '<Root>/yaw_r'
   *  Product: '<S14>/Product1'
   */
  rtb_vims_idx_0 = 0.615 * rtU.yaw_r + rtb_Product3;
  rtb_vims_idx_1 = -0.615 * rtU.yaw_r + rtb_SignedSqrt;
  rtb_vims_idx_2 = 0.6 * rtU.yaw_r + rtb_Gain11_a_idx_2;
  rtb_vims_idx_3 = -0.6 * rtU.yaw_r + rtb_ua;

  /* Sum: '<S20>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  u = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_0;

  /* Sum: '<S20>/Add2' incorporates:
   *  Gain: '<S20>/Gain1'
   *  Inport: '<Root>/ax'
   *  Memory: '<S20>/Memory'
   *  Sum: '<S20>/Add'
   *  Sum: '<S20>/Add1'
   */
  u_0 = rtU.ax - (rtb_vims_idx_0 - rtDW.Memory_PreviousInput_j[0]) * 20.0;

  /* Math: '<S20>/Exp4' incorporates:
   *  Gain: '<S20>/Gain'
   *  Math: '<S20>/Exp'
   *  Math: '<S20>/Exp1'
   *  Product: '<S20>/Divide'
   *  Product: '<S20>/Divide1'
   *  Sum: '<S20>/Add3'
   *
   * About '<S20>/Exp4':
   *  Operator: exp
   *
   * About '<S20>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S20>/Exp1':
   *  Operator: magnitude^2
   */
  u = exp(((0.0 - u * u * 0.44444444444444442) - u_0 * u_0 / 49.0) * 0.5);
  rtb_Product3 = u;

  /* Product: '<S14>/Product' incorporates:
   *  Sum: '<S20>/Add1'
   */
  rtb_Product_idx_0 = rtb_vims_idx_0 * u;

  /* Sum: '<S20>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  u = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_1;

  /* Sum: '<S20>/Add2' incorporates:
   *  Gain: '<S20>/Gain1'
   *  Inport: '<Root>/ax'
   *  Memory: '<S20>/Memory'
   *  Sum: '<S20>/Add'
   *  Sum: '<S20>/Add1'
   */
  u_0 = rtU.ax - (rtb_vims_idx_1 - rtDW.Memory_PreviousInput_j[1]) * 20.0;

  /* Math: '<S20>/Exp4' incorporates:
   *  Gain: '<S20>/Gain'
   *  Math: '<S20>/Exp'
   *  Math: '<S20>/Exp1'
   *  Product: '<S20>/Divide'
   *  Product: '<S20>/Divide1'
   *  Sum: '<S20>/Add3'
   *
   * About '<S20>/Exp4':
   *  Operator: exp
   *
   * About '<S20>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S20>/Exp1':
   *  Operator: magnitude^2
   */
  u = exp(((0.0 - u * u * 0.44444444444444442) - u_0 * u_0 / 49.0) * 0.5);
  rtb_SignedSqrt = u;

  /* Product: '<S14>/Product' incorporates:
   *  Sum: '<S20>/Add1'
   */
  rtb_Product_idx_1 = rtb_vims_idx_1 * u;

  /* Sum: '<S20>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  u = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_2;

  /* Sum: '<S20>/Add2' incorporates:
   *  Gain: '<S20>/Gain1'
   *  Inport: '<Root>/ax'
   *  Memory: '<S20>/Memory'
   *  Sum: '<S20>/Add'
   *  Sum: '<S20>/Add1'
   */
  u_0 = rtU.ax - (rtb_vims_idx_2 - rtDW.Memory_PreviousInput_j[2]) * 20.0;

  /* Math: '<S20>/Exp4' incorporates:
   *  Gain: '<S20>/Gain'
   *  Math: '<S20>/Exp'
   *  Math: '<S20>/Exp1'
   *  Product: '<S20>/Divide'
   *  Product: '<S20>/Divide1'
   *  Sum: '<S20>/Add3'
   *
   * About '<S20>/Exp4':
   *  Operator: exp
   *
   * About '<S20>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S20>/Exp1':
   *  Operator: magnitude^2
   */
  u = exp(((0.0 - u * u * 0.44444444444444442) - u_0 * u_0 / 49.0) * 0.5);
  rtb_Gain11_a_idx_2 = u;

  /* Product: '<S14>/Product' incorporates:
   *  Sum: '<S20>/Add1'
   */
  rtb_Product_idx_2 = rtb_vims_idx_2 * u;

  /* Sum: '<S20>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  u = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_3;

  /* Sum: '<S20>/Add2' incorporates:
   *  Gain: '<S20>/Gain1'
   *  Inport: '<Root>/ax'
   *  Memory: '<S20>/Memory'
   *  Sum: '<S20>/Add'
   *  Sum: '<S20>/Add1'
   */
  u_0 = rtU.ax - (rtb_vims_idx_3 - rtDW.Memory_PreviousInput_j[3]) * 20.0;

  /* Math: '<S20>/Exp4' incorporates:
   *  Gain: '<S20>/Gain'
   *  Math: '<S20>/Exp'
   *  Math: '<S20>/Exp1'
   *  Product: '<S20>/Divide'
   *  Product: '<S20>/Divide1'
   *  Sum: '<S20>/Add3'
   *
   * About '<S20>/Exp4':
   *  Operator: exp
   *
   * About '<S20>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S20>/Exp1':
   *  Operator: magnitude^2
   */
  u = exp(((0.0 - u * u * 0.44444444444444442) - u_0 * u_0 / 49.0) * 0.5);

  /* Sum: '<S15>/Add' incorporates:
   *  Abs: '<S14>/Abs'
   *  Constant: '<S13>/Constant4'
   *  Constant: '<S17>/Constant'
   *  Constant: '<S18>/Constant'
   *  Constant: '<S19>/Constant'
   *  Inport: '<Root>/ax'
   *  Math: '<S20>/Exp4'
   *  MinMax: '<S14>/Max'
   *  MinMax: '<S14>/Min'
   *  Product: '<S14>/Divide'
   *  Product: '<S14>/Product'
   *  Product: '<S14>/Product of Elements'
   *  Product: '<S15>/Product'
   *  RelationalOperator: '<S17>/Compare'
   *  RelationalOperator: '<S18>/Compare'
   *  RelationalOperator: '<S19>/Compare'
   *  Sum: '<S14>/Add'
   *  Sum: '<S14>/Sum of Elements'
   *  Sum: '<S14>/Sum of Elements1'
   *  Sum: '<S14>/Sum of Elements2'
   *  Sum: '<S20>/Add1'
   *
   * About '<S20>/Exp4':
   *  Operator: exp
   */
  rtb_Gain11_a_idx_2 = (((((rtb_Product_idx_0 + rtb_Product_idx_1) +
    rtb_Product_idx_2) + rtb_vims_idx_3 * u) / (((rtb_Product3 + rtb_SignedSqrt)
    + rtb_Gain11_a_idx_2) + u) * (real_T)(fabs(rtU.ax) <= 1.5) + (real_T)(rtU.ax
    >= 1.5) * fmin(fmin(fmin(rtb_vims_idx_0, rtb_vims_idx_1), rtb_vims_idx_2),
                   rtb_vims_idx_3)) + (real_T)(rtU.ax < -1.5) * fmax(fmax(fmax
    (rtb_vims_idx_0, rtb_vims_idx_1), rtb_vims_idx_2), rtb_vims_idx_3)) - (0.0 *
    rtb_x_k_idx_1 + rtb_x_k_idx_0);

  /* Sum: '<S15>/Add1' incorporates:
   *  Product: '<S13>/Divide'
   *  Product: '<S15>/Product1'
   */
  rtb_K_k[0] = rtb_K_k[0] * rtb_Gain11_a_idx_2 + rtb_x_k_idx_0;
  rtb_K_k[1] = rtb_K_k[1] * rtb_Gain11_a_idx_2 + rtb_x_k_idx_1;

  /* Gain: '<S2>/Fl' incorporates:
   *  Math: '<S2>/Square'
   */
  rtb_Gain11_a_idx_2 = rtb_K_k[0] * rtb_K_k[0] * 2.737875;

  /* Gain: '<S2>/Gain1' */
  rtb_x_k_idx_1 = 0.19449351084683267 * rtb_Gain11_a_idx_2;

  /* Sum: '<S2>/Add' incorporates:
   *  Constant: '<S2>/Constant'
   */
  rtb_Product3 = ((582.71400000000017 - rtb_Add1_c) - rtb_Gain2_nj) +
    rtb_x_k_idx_1;

  /* Sum: '<S2>/Add1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  rtb_Add1_c = ((rtb_Add1_c + 582.71400000000017) - rtb_Gain2_nj) +
    rtb_x_k_idx_1;

  /* Gain: '<S2>/Gain4' incorporates:
   *  Inport: '<Root>/ay'
   */
  rtb_x_k_idx_1 = 37.493050131453444 * rtU.ay;

  /* Gain: '<S2>/Gain' */
  rtb_Gain11_a_idx_2 *= 0.3055064891531673;

  /* Saturate: '<S2>/Saturation' */
  if (rtb_Product3 > 2000.0) {
    rtb_Product_idx_0 = 2000.0;
  } else if (rtb_Product3 < 0.0) {
    rtb_Product_idx_0 = 0.0;
  } else {
    rtb_Product_idx_0 = rtb_Product3;
  }

  if (rtb_Add1_c > 2000.0) {
    rtb_Product_idx_1 = 2000.0;
  } else if (rtb_Add1_c < 0.0) {
    rtb_Product_idx_1 = 0.0;
  } else {
    rtb_Product_idx_1 = rtb_Add1_c;
  }

  /* Sum: '<S2>/Add2' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  rtb_Product_idx_2 = ((741.63600000000008 - rtb_x_k_idx_1) + rtb_Gain2_nj) +
    rtb_Gain11_a_idx_2;

  /* Saturate: '<S2>/Saturation' */
  if (rtb_Product_idx_2 > 2000.0) {
    rtb_Product_idx_2 = 2000.0;
  } else if (rtb_Product_idx_2 < 0.0) {
    rtb_Product_idx_2 = 0.0;
  }

  /* Sum: '<S2>/Add3' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  rtb_x_k_idx_0 = ((rtb_x_k_idx_1 + 741.63600000000008) + rtb_Gain2_nj) +
    rtb_Gain11_a_idx_2;

  /* Saturate: '<S2>/Saturation' */
  if (rtb_x_k_idx_0 > 2000.0) {
    rtb_x_k_idx_0 = 2000.0;
  } else if (rtb_x_k_idx_0 < 0.0) {
    rtb_x_k_idx_0 = 0.0;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  Inport: '<Root>/throttle'
   */
  rtb_Gain11_a_idx_2 = 42.0 * rtU.throttle;

  /* Sum: '<S1>/Add' incorporates:
   *  Sum: '<S25>/Sum'
   *  Sum: '<S25>/Sum1'
   */
  rtb_Add1_c = rtb_Product_idx_0 + rtb_Product_idx_1;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Add'
   *  Sum: '<S1>/Add2'
   *  Sum: '<S1>/Subtract'
   */
  rtb_x_k_idx_1 = ((rtb_Add1_c - 667.461609) * -0.00034582756054813037 +
                   1.8189395) * rtb_Add1_c;

  /* Sum: '<S1>/Add1' */
  rtb_Product3 = rtb_Product_idx_2 + rtb_x_k_idx_0;

  /* Product: '<S1>/Divide' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain1'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Add3'
   *  Sum: '<S1>/Add4'
   *  Sum: '<S1>/Subtract1'
   */
  rtb_x_k_idx_1 /= ((rtb_Product3 - 667.461609) * -0.00034582756054813037 +
                    1.8189395) * rtb_Product3 + rtb_x_k_idx_1;

  /* Product: '<S8>/Divide' incorporates:
   *  Constant: '<S8>/Constant'
   *  Product: '<S8>/Divide1'
   *  Sum: '<S8>/Add'
   *  Sum: '<S8>/Add5'
   */
  rtb_Product3 = 1.0 / (1.0 - rtb_x_k_idx_1) * (rtb_x_k_idx_1 *
    rtb_Gain11_a_idx_2);

  /* Product: '<S25>/Divide' */
  rtb_SignedSqrt = rtb_Product_idx_0 / rtb_Add1_c;

  /* Product: '<S25>/Divide1' incorporates:
   *  Sum: '<S25>/Add2'
   *  Sum: '<S25>/Sum'
   */
  rtb_Add1_c = 1.0 / (((rtb_Add1_c + rtb_Product_idx_2) + rtb_x_k_idx_0) -
                      rtb_Add1_c) * rtb_x_k_idx_0;

  /* Product: '<S3>/Product' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S12>/Constant'
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/yaw_r'
   *  RelationalOperator: '<S12>/Compare'
   *  Sum: '<S3>/Add'
   */
  rtb_Gain2_nj = (1.0 - (real_T)(fabs(rtU.yaw_r) <= 0.034906585039886591)) *
    rtb_K_k[1];

  /* Gain: '<S9>/Gain12' */
  u = 2.0 * rtb_Product_idx_0;

  /* Sum: '<S9>/Sum' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  Gain: '<S9>/Gain'
   *  Gain: '<S9>/Gain1'
   *  Gain: '<S9>/Gain12'
   *  Gain: '<S9>/Gain2'
   *  Gain: '<S9>/Gain3'
   *  Gain: '<S9>/Gain4'
   *  Gain: '<S9>/Gain5'
   *  Math: '<S9>/Math Function'
   *  Math: '<S9>/Math Function1'
   *  Math: '<S9>/Math Function2'
   *  Math: '<S9>/Math Function3'
   *  Math: '<S9>/Square'
   */
  rtb_Product1_l_idx_0 = ((((rtb_Product_idx_0 * rtb_Product_idx_0 *
    0.000387300865455914 + 1.7977585706847 * rtb_Product_idx_0) +
    -3.1451739527421698E-6 * rt_powd_snf(rtb_Product_idx_0, 3.0)) +
    4.6481093251002305E-9 * rt_powd_snf(rtb_Product_idx_0, 4.0)) +
    -3.5206874715396997E-12 * rt_powd_snf(rtb_Product_idx_0, 5.0)) +
    1.3153773191824902E-15 * rt_powd_snf(rtb_Product_idx_0, 6.0);

  /* Switch: '<S26>/Switch2' incorporates:
   *  RelationalOperator: '<S26>/LowerRelop1'
   */
  if (!(rtb_Product1_l_idx_0 > u)) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S9>/Constant8'
     *  RelationalOperator: '<S26>/UpperRelop'
     */
    if (rtb_Product1_l_idx_0 < 1.0) {
      u = 1.0;
    } else {
      u = rtb_Product1_l_idx_0;
    }
  }

  /* Trigonometry: '<S9>/Tan' */
  rtb_Product1_l_idx_0 = tan(rtb_Product4_idx_0);

  /* Saturate: '<S9>/Saturation' */
  if (rtb_Product1_l_idx_0 > 0.2) {
    rtb_Product1_l_idx_0 = 0.2;
  } else if (rtb_Product1_l_idx_0 < -0.2) {
    rtb_Product1_l_idx_0 = -0.2;
  }

  /* Gain: '<S9>/Gain11' incorporates:
   *  Constant: '<S9>/Constant4'
   *  Constant: '<S9>/Constant5'
   *  Constant: '<S9>/Constant6'
   *  Constant: '<S9>/Constant7'
   *  Gain: '<S9>/Gain10'
   *  Gain: '<S9>/Gain6'
   *  Gain: '<S9>/Gain7'
   *  Gain: '<S9>/Gain8'
   *  Gain: '<S9>/Gain9'
   *  Math: '<S9>/Math Function4'
   *  Math: '<S9>/Math Function5'
   *  Math: '<S9>/Math Function7'
   *  Math: '<S9>/Square1'
   *  Product: '<S9>/Product1'
   *  Saturate: '<S4>/Saturation'
   *  Sum: '<S9>/Sum1'
   */
  u_0 = (((((rtb_Product1_l_idx_0 * rtb_Product1_l_idx_0 * -21.4167 + 0.0 *
             rtb_Product1_l_idx_0) + 0.0 * rt_powd_snf(rtb_Product1_l_idx_0, 3.0))
           + 291.6667 * rt_powd_snf(rtb_Product1_l_idx_0, 4.0)) + 0.0 *
          rt_powd_snf(rtb_Product1_l_idx_0, 5.0)) + 1.0) * (u *
    Memory_PreviousInput_0) * 0.078947160665366667;

  /* Gain: '<S9>/Gain12' */
  u = 2.0 * rtb_Product_idx_1;

  /* Sum: '<S9>/Sum' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  Gain: '<S9>/Gain'
   *  Gain: '<S9>/Gain1'
   *  Gain: '<S9>/Gain12'
   *  Gain: '<S9>/Gain2'
   *  Gain: '<S9>/Gain3'
   *  Gain: '<S9>/Gain4'
   *  Gain: '<S9>/Gain5'
   *  Math: '<S9>/Math Function'
   *  Math: '<S9>/Math Function1'
   *  Math: '<S9>/Math Function2'
   *  Math: '<S9>/Math Function3'
   *  Math: '<S9>/Square'
   */
  rtb_Product1_l_idx_0 = ((((rtb_Product_idx_1 * rtb_Product_idx_1 *
    0.000387300865455914 + 1.7977585706847 * rtb_Product_idx_1) +
    -3.1451739527421698E-6 * rt_powd_snf(rtb_Product_idx_1, 3.0)) +
    4.6481093251002305E-9 * rt_powd_snf(rtb_Product_idx_1, 4.0)) +
    -3.5206874715396997E-12 * rt_powd_snf(rtb_Product_idx_1, 5.0)) +
    1.3153773191824902E-15 * rt_powd_snf(rtb_Product_idx_1, 6.0);

  /* Switch: '<S26>/Switch2' incorporates:
   *  RelationalOperator: '<S26>/LowerRelop1'
   */
  if (!(rtb_Product1_l_idx_0 > u)) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S9>/Constant8'
     *  RelationalOperator: '<S26>/UpperRelop'
     */
    if (rtb_Product1_l_idx_0 < 1.0) {
      u = 1.0;
    } else {
      u = rtb_Product1_l_idx_0;
    }
  }

  /* Trigonometry: '<S9>/Tan' */
  rtb_Product1_l_idx_0 = tan(rtb_Product4_idx_1);

  /* Saturate: '<S9>/Saturation' */
  if (rtb_Product1_l_idx_0 > 0.2) {
    rtb_Product1_l_idx_0 = 0.2;
  } else if (rtb_Product1_l_idx_0 < -0.2) {
    rtb_Product1_l_idx_0 = -0.2;
  }

  /* Gain: '<S9>/Gain11' incorporates:
   *  Constant: '<S9>/Constant4'
   *  Constant: '<S9>/Constant5'
   *  Constant: '<S9>/Constant6'
   *  Constant: '<S9>/Constant7'
   *  Gain: '<S9>/Gain10'
   *  Gain: '<S9>/Gain6'
   *  Gain: '<S9>/Gain7'
   *  Gain: '<S9>/Gain8'
   *  Gain: '<S9>/Gain9'
   *  Math: '<S9>/Math Function4'
   *  Math: '<S9>/Math Function5'
   *  Math: '<S9>/Math Function7'
   *  Math: '<S9>/Square1'
   *  Product: '<S9>/Product1'
   *  Saturate: '<S4>/Saturation'
   *  Sum: '<S9>/Sum1'
   */
  u0 = (((((rtb_Product1_l_idx_0 * rtb_Product1_l_idx_0 * -21.4167 + 0.0 *
            rtb_Product1_l_idx_0) + 0.0 * rt_powd_snf(rtb_Product1_l_idx_0, 3.0))
          + 291.6667 * rt_powd_snf(rtb_Product1_l_idx_0, 4.0)) + 0.0 *
         rt_powd_snf(rtb_Product1_l_idx_0, 5.0)) + 1.0) * (u * u0) *
    0.078947160665366667;

  /* Gain: '<S9>/Gain12' */
  u = 2.0 * rtb_Product_idx_2;

  /* Sum: '<S9>/Sum' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  Gain: '<S9>/Gain'
   *  Gain: '<S9>/Gain1'
   *  Gain: '<S9>/Gain12'
   *  Gain: '<S9>/Gain2'
   *  Gain: '<S9>/Gain3'
   *  Gain: '<S9>/Gain4'
   *  Gain: '<S9>/Gain5'
   *  Math: '<S9>/Math Function'
   *  Math: '<S9>/Math Function1'
   *  Math: '<S9>/Math Function2'
   *  Math: '<S9>/Math Function3'
   *  Math: '<S9>/Square'
   */
  rtb_Product1_l_idx_0 = ((((rtb_Product_idx_2 * rtb_Product_idx_2 *
    0.000387300865455914 + 1.7977585706847 * rtb_Product_idx_2) +
    -3.1451739527421698E-6 * rt_powd_snf(rtb_Product_idx_2, 3.0)) +
    4.6481093251002305E-9 * rt_powd_snf(rtb_Product_idx_2, 4.0)) +
    -3.5206874715396997E-12 * rt_powd_snf(rtb_Product_idx_2, 5.0)) +
    1.3153773191824902E-15 * rt_powd_snf(rtb_Product_idx_2, 6.0);

  /* Switch: '<S26>/Switch2' incorporates:
   *  RelationalOperator: '<S26>/LowerRelop1'
   */
  if (!(rtb_Product1_l_idx_0 > u)) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S9>/Constant8'
     *  RelationalOperator: '<S26>/UpperRelop'
     */
    if (rtb_Product1_l_idx_0 < 1.0) {
      u = 1.0;
    } else {
      u = rtb_Product1_l_idx_0;
    }
  }

  /* Trigonometry: '<S9>/Tan' incorporates:
   *  SignalConversion generated from: '<S14>/Cos'
   */
  rtb_Product1_l_idx_0 = tan(rtConstB.Gain);

  /* Saturate: '<S9>/Saturation' */
  if (rtb_Product1_l_idx_0 > 0.2) {
    rtb_Product1_l_idx_0 = 0.2;
  } else if (rtb_Product1_l_idx_0 < -0.2) {
    rtb_Product1_l_idx_0 = -0.2;
  }

  /* Gain: '<S9>/Gain11' incorporates:
   *  Constant: '<S9>/Constant4'
   *  Constant: '<S9>/Constant5'
   *  Constant: '<S9>/Constant6'
   *  Constant: '<S9>/Constant7'
   *  Gain: '<S9>/Gain10'
   *  Gain: '<S9>/Gain6'
   *  Gain: '<S9>/Gain7'
   *  Gain: '<S9>/Gain8'
   *  Gain: '<S9>/Gain9'
   *  Math: '<S9>/Math Function4'
   *  Math: '<S9>/Math Function5'
   *  Math: '<S9>/Math Function7'
   *  Math: '<S9>/Square1'
   *  Product: '<S9>/Product1'
   *  Saturate: '<S4>/Saturation'
   *  Sum: '<S9>/Sum1'
   */
  u0_0 = (((((rtb_Product1_l_idx_0 * rtb_Product1_l_idx_0 * -21.4167 + 0.0 *
              rtb_Product1_l_idx_0) + 0.0 * rt_powd_snf(rtb_Product1_l_idx_0,
              3.0)) + 291.6667 * rt_powd_snf(rtb_Product1_l_idx_0, 4.0)) + 0.0 *
           rt_powd_snf(rtb_Product1_l_idx_0, 5.0)) + 1.0) * (u * u0_0) *
    0.078947160665366667;

  /* Gain: '<S9>/Gain12' */
  u = 2.0 * rtb_x_k_idx_0;

  /* Sum: '<S9>/Sum' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Constant: '<S9>/Constant2'
   *  Constant: '<S9>/Constant3'
   *  Gain: '<S9>/Gain'
   *  Gain: '<S9>/Gain1'
   *  Gain: '<S9>/Gain12'
   *  Gain: '<S9>/Gain2'
   *  Gain: '<S9>/Gain3'
   *  Gain: '<S9>/Gain4'
   *  Gain: '<S9>/Gain5'
   *  Math: '<S9>/Math Function'
   *  Math: '<S9>/Math Function1'
   *  Math: '<S9>/Math Function2'
   *  Math: '<S9>/Math Function3'
   *  Math: '<S9>/Square'
   */
  rtb_Product1_l_idx_0 = ((((rtb_x_k_idx_0 * rtb_x_k_idx_0 *
    0.000387300865455914 + 1.7977585706847 * rtb_x_k_idx_0) +
    -3.1451739527421698E-6 * rt_powd_snf(rtb_x_k_idx_0, 3.0)) +
    4.6481093251002305E-9 * rt_powd_snf(rtb_x_k_idx_0, 4.0)) +
    -3.5206874715396997E-12 * rt_powd_snf(rtb_x_k_idx_0, 5.0)) +
    1.3153773191824902E-15 * rt_powd_snf(rtb_x_k_idx_0, 6.0);

  /* Switch: '<S26>/Switch2' incorporates:
   *  RelationalOperator: '<S26>/LowerRelop1'
   */
  if (!(rtb_Product1_l_idx_0 > u)) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S9>/Constant8'
     *  RelationalOperator: '<S26>/UpperRelop'
     */
    if (rtb_Product1_l_idx_0 < 1.0) {
      u = 1.0;
    } else {
      u = rtb_Product1_l_idx_0;
    }
  }

  /* Product: '<S8>/Product' incorporates:
   *  Constant: '<S25>/Constant'
   *  Sum: '<S25>/Add'
   *  Sum: '<S25>/Add1'
   *  Sum: '<S25>/Add3'
   */
  rtb_Product1_l_idx_0 = rtb_Product3 * rtb_SignedSqrt;
  rtb_Product1_l_idx_1 = (1.0 - rtb_SignedSqrt) * rtb_Product3;
  rtb_Product1_l_idx_2 = (1.0 - rtb_Add1_c) * rtb_Gain11_a_idx_2;
  rtb_Product1_l_idx_3 = rtb_Gain11_a_idx_2 * rtb_Add1_c;

  /* Gain: '<S10>/Multiply1' incorporates:
   *  Inport: '<Root>/yaw_r'
   */
  rtb_Gain11_a_idx_2 = 0.615 * rtU.yaw_r;

  /* Gain: '<S10>/Multiply3' incorporates:
   *  Inport: '<Root>/yaw_r'
   */
  rtb_Add1_c = 0.6 * rtU.yaw_r;

  /* Product: '<S10>/Product4' incorporates:
   *  Sum: '<S10>/Add3'
   *  Sum: '<S10>/Add6'
   */
  rtb_Product1_m[0] = (rtb_K_k[0] - rtb_Gain11_a_idx_2) * rtb_Gain11_a_idx_0_tmp;
  rtb_Product1_m[1] = (rtb_Gain11_a_idx_2 + rtb_K_k[0]) * rtb_Gain11_a_idx_1_tmp;

  /* Sum: '<S10>/Add' incorporates:
   *  Gain: '<S10>/Multiply4'
   *  Inport: '<Root>/yaw_r'
   */
  rtb_Gain11_a_idx_2 = 0.8596 * rtU.yaw_r + rtb_Gain2_nj;

  /* Sum: '<S10>/Add1' incorporates:
   *  Gain: '<S10>/Multiply7'
   *  Inport: '<Root>/yaw_r'
   */
  rtb_Product3 = -0.6754 * rtU.yaw_r - rtb_Gain2_nj;

  /* Sum: '<S10>/Minus' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Product: '<Root>/Product'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product4'
   *  Product: '<S10>/Product5'
   *  SignalConversion generated from: '<S14>/Cos'
   *  Sum: '<S10>/Add2'
   *  Sum: '<S10>/Add4'
   *  Sum: '<S10>/Add5'
   *  Trigonometry: '<S10>/Sin'
   */
  rtb_Product4_idx_0 = rtb_Gain3_c_idx_0 - (sin(rtb_Product4_idx_0) *
    rtb_Gain11_a_idx_2 + rtb_Product1_m[0]) * 1.12;
  rtb_Product4_idx_1 = rtb_Gain3_c_idx_1 - (sin(rtb_Product4_idx_1) *
    rtb_Gain11_a_idx_2 + rtb_Product1_m[1]) * 1.12;
  rtb_Gain3_c_idx_2 -= ((rtb_K_k[0] - rtb_Add1_c) * rtb_Product4_idx_3 + sin
                        (rtConstB.Gain) * rtb_Product3) * 1.12;
  rtb_Product4_idx_3 = rtb_ua - ((rtb_Add1_c + rtb_K_k[0]) + 0.0 * rtb_Product3)
    * 1.12;

  /* Gain: '<S6>/Gain' incorporates:
   *  Inport: '<Root>/rpm'
   *  Sum: '<S6>/Add1'
   */
  rtb_Gain11_a_idx_2 = (((rtU.rpm[0] + rtU.rpm[1]) + rtU.rpm[2]) + rtU.rpm[3]) *
    4.0;

  /* Sum: '<S22>/Add1' incorporates:
   *  Constant: '<S22>/Constant'
   *  Delay: '<S22>/Delay1'
   *  Memory: '<S22>/Memory'
   *  Product: '<S22>/Product2'
   */
  rtb_Gain3_c_idx_1 = 0.875 * (real_T)rtDW.Delay1_DSTATE[0] +
    rtDW.Memory_PreviousInput_g;

  /* RelationalOperator: '<S21>/Compare' incorporates:
   *  Constant: '<S21>/Constant'
   *  Inport: '<Root>/regen'
   */
  rtb_Compare_c = (rtU.regen > 0.0);

  /* Saturate: '<S22>/Saturation' incorporates:
   *  Constant: '<S22>/Constant1'
   *  Sum: '<S22>/Add'
   */
  if (100.0 - rtb_Gain3_c_idx_1 > 100.0) {
    Memory_PreviousInput_0 = 100.0;
  } else if (100.0 - rtb_Gain3_c_idx_1 < 65.0) {
    Memory_PreviousInput_0 = 65.0;
  } else {
    Memory_PreviousInput_0 = 100.0 - rtb_Gain3_c_idx_1;
  }

  /* MinMax: '<S5>/Imax' incorporates:
   *  Constant: '<S5>/Constant'
   *  Constant: '<S5>/Max battery voltage'
   *  Gain: '<S5>/Gain'
   *  Inport: '<Root>/regen'
   *  Inport: '<Root>/voltage'
   *  Product: '<S22>/Product'
   *  Product: '<S5>/Product'
   *  Saturate: '<S22>/Saturation'
   *  Sum: '<S5>/Subtract'
   */
  rtb_Product3 = fmin(fmin((564.96 - rtU.voltage) * 2.5, 100.0 * rtU.regen),
                      Memory_PreviousInput_0 * (real_T)rtb_Compare_c);

  /* Product: '<S5>/Product1' incorporates:
   *  Gain: '<S5>/Gain1'
   *  Inport: '<Root>/voltage'
   *  Sum: '<S5>/Tot voltage'
   */
  rtb_Product3 *= 0.3 * rtb_Product3 + rtU.voltage;

  /* Gain: '<S24>/FRmotor Erad//s' */
  rtb_Add1_c = 5.0 * rtb_Gain11_a_idx_2;

  /* Gain: '<S24>/a' incorporates:
   *  Constant: '<S24>/R*(1+1//t_alpha)'
   *  Gain: '<S24>/(Ld-Lq)//t_alpha'
   *  Sum: '<S24>/Add'
   */
  rtb_SignedSqrt = (2.0270999999999996E-5 * rtb_Add1_c + 0.0694261735) * 1.5;

  /* Gain: '<S24>/2a' */
  rtb_ua = 2.0 * rtb_SignedSqrt;

  /* Gain: '<S24>/b' */
  rtb_Add1_c *= 0.0444;

  /* Sum: '<S24>/Add1' incorporates:
   *  Gain: '<S24>/4a'
   *  Math: '<S24>/b^2'
   *  Product: '<S24>/4ac'
   */
  rtb_SignedSqrt = 4.0 * rtb_SignedSqrt * rtb_Product3 + rtb_Add1_c * rtb_Add1_c;

  /* Sqrt: '<S24>/Signed Sqrt'
   *
   * About '<S24>/Signed Sqrt':
   *  Operator: signedSqrt
   */
  if (rtb_SignedSqrt < 0.0) {
    Memory_PreviousInput_0 = -sqrt(fabs(rtb_SignedSqrt));
  } else {
    Memory_PreviousInput_0 = sqrt(rtb_SignedSqrt);
  }

  /* Product: '<S24>/Iq' incorporates:
   *  Sqrt: '<S24>/Signed Sqrt'
   *  Sum: '<S24>/Subtract'
   *
   * About '<S24>/Signed Sqrt':
   *  Operator: signedSqrt
   */
  rtb_Add1_c = 1.0 / rtb_ua * (Memory_PreviousInput_0 - rtb_Add1_c);

  /* Math: '<S24>/Math Function' */
  rtb_SignedSqrt = rtb_Add1_c * rtb_Add1_c;

  /* Gain: '<S24>/Gain1' */
  rtb_Add1_c *= -0.1689;

  /* MinMax: '<S6>/Min' incorporates:
   *  Constant: '<S23>/Constant'
   *  Constant: '<S23>/Constant1'
   *  Gain: '<S23>/Gain1'
   *  Gain: '<S24>/Gain'
   *  Math: '<S24>/Math Function1'
   *  Product: '<S6>/Tmax'
   *  Sum: '<S23>/Subtract'
   *  Sum: '<S23>/Subtract1'
   *  Sum: '<S24>/Iq^2+Id^2'
   *  Sum: '<S6>/Ptot'
   */
  rtb_Product3 = fmin(((rtb_Add1_c * rtb_Add1_c + rtb_SignedSqrt) * 0.1013 +
                       rtb_Product3) / rtb_Gain11_a_idx_2, 21.0 -
                      (rtb_Gain11_a_idx_2 - 13000.0) * 0.000857);

  /* Product: '<S6>/Product' incorporates:
   *  Constant: '<S6>/Constant'
   *  Constant: '<S6>/Constant1'
   *  Constant: '<S6>/Constant3'
   *  Gain: '<S6>/Gain1'
   *  Gain: '<S6>/Gain2'
   *  Inport: '<Root>/brake'
   *  Math: '<S6>/Power1'
   *  Product: '<S6>/Divide'
   *  Product: '<S6>/Product1'
   *  Sum: '<S6>/Add'
   *  Sum: '<S6>/Add2'
   *  Sum: '<S6>/Add4'
   */
  rtb_x_k_idx_1 *= ((1.0 - 0.7 * rt_powd_snf(rtb_x_k_idx_1, -1.0)) * (0.2088384 *
    rtU.brake) + rtb_Product3) / (rtb_Product3 + 1.0E-8);

  /* Saturate: '<S6>/Saturation' */
  if (rtb_x_k_idx_1 > 1.0) {
    rtb_x_k_idx_1 = 1.0;
  } else if (rtb_x_k_idx_1 < 0.0) {
    rtb_x_k_idx_1 = 0.0;
  }

  /* End of Saturate: '<S6>/Saturation' */

  /* Product: '<S6>/Product2' */
  rtb_Gain11_a_idx_2 = rtb_Product3 * rtb_x_k_idx_1;

  /* Product: '<S6>/Product3' incorporates:
   *  Constant: '<S6>/Constant2'
   *  Sum: '<S6>/Add3'
   */
  rtb_Product3 *= 1.0 - rtb_x_k_idx_1;

  /* Outport: '<Root>/T_neg1' incorporates:
   *  Gain: '<S6>/Gain3'
   */
  rtY.T_neg1[0] = -rtb_Gain11_a_idx_2;
  rtY.T_neg1[1] = -rtb_Gain11_a_idx_2;
  rtY.T_neg1[2] = -rtb_Product3;
  rtY.T_neg1[3] = -rtb_Product3;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Inport: '<Root>/ax'
   *  Memory: '<S3>/Memory2'
   */
  rtDW.Memory2_PreviousInput[0] = rtU.ax;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Inport: '<Root>/ay'
   *  Memory: '<S3>/Memory2'
   */
  rtDW.Memory2_PreviousInput[1] = rtU.ay;

  /* Update for Memory: '<S3>/Memory4' incorporates:
   *  Inport: '<Root>/yaw_r'
   */
  rtDW.Memory4_PreviousInput = rtU.yaw_r;

  /* Update for Memory: '<S3>/Memory1' */
  rtDW.Memory1_PreviousInput[0] = rtb_K_k[0];
  rtDW.Memory1_PreviousInput[1] = rtb_Gain2_nj;

  /* MinMax: '<S10>/err+' incorporates:
   *  Constant: '<S10>/Constant'
   */
  rtb_Add1_c = fmax(0.0, rtb_Product4_idx_0);

  /* Sum: '<S10>/Add7' incorporates:
   *  Memory: '<S10>/Memory1'
   */
  rtb_ua = rtb_Add1_c + rtDW.Memory1_PreviousInput_n[0];

  /* Sum: '<S10>/Add8' incorporates:
   *  Constant: '<S10>/Constant11'
   *  Constant: '<S10>/Constant12'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S28>/Constant'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain2'
   *  Gain: '<S10>/Gain3'
   *  Gain: '<S10>/Gain4'
   *  Memory: '<S10>/Memory'
   *  MinMax: '<S10>/Min'
   *  MinMax: '<S10>/err+'
   *  MinMax: '<S10>/err'+'
   *  Product: '<S10>/Product2'
   *  RelationalOperator: '<S28>/Compare'
   *  Sum: '<S10>/Minus6'
   *  Sum: '<S10>/r+'
   */
  Memory_PreviousInput_0 = (fmin(0.75, (1.0 - (real_T)(rtb_Add1_c == 0.0)) *
    rtb_ua * 0.0005) + 0.1 * rtb_Add1_c) + fmax((rtb_Product4_idx_0 -
    rtDW.Memory_PreviousInput_o[0]) * 20.0, 0.0) * 0.03;

  /* Saturate: '<S10>/Saturation' */
  if (Memory_PreviousInput_0 > 1.0) {
    Memory_PreviousInput_0 = 1.0;
  } else if (Memory_PreviousInput_0 < 0.0) {
    Memory_PreviousInput_0 = 0.0;
  }

  /* Outport: '<Root>/T_pos1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S10>/Constant17'
   *  Gain: '<S9>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Saturate: '<S10>/Saturation'
   *  Sum: '<S10>/ktc+'
   */
  rtY.T_pos1[0] = fmin(fmin(21.0, u_0), (1.0 - Memory_PreviousInput_0) *
                       rtb_Product1_l_idx_0);

  /* Update for Memory: '<S4>/Memory' */
  rtDW.Memory_PreviousInput_i[0] = rtb_Product_idx_0;

  /* Update for Memory: '<S20>/Memory' */
  rtDW.Memory_PreviousInput_j[0] = rtb_vims_idx_0;

  /* Update for Memory: '<S10>/Memory1' */
  rtDW.Memory1_PreviousInput_n[0] = rtb_ua;

  /* Update for Memory: '<S10>/Memory' incorporates:
   *  MinMax: '<S10>/err+'
   */
  rtDW.Memory_PreviousInput_o[0] = rtb_Product4_idx_0;

  /* MinMax: '<S10>/err+' incorporates:
   *  Constant: '<S10>/Constant'
   */
  rtb_Add1_c = fmax(0.0, rtb_Product4_idx_1);

  /* Sum: '<S10>/Add7' incorporates:
   *  Memory: '<S10>/Memory1'
   */
  rtb_ua = rtb_Add1_c + rtDW.Memory1_PreviousInput_n[1];

  /* Sum: '<S10>/Add8' incorporates:
   *  Constant: '<S10>/Constant11'
   *  Constant: '<S10>/Constant12'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S28>/Constant'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain2'
   *  Gain: '<S10>/Gain3'
   *  Gain: '<S10>/Gain4'
   *  Memory: '<S10>/Memory'
   *  MinMax: '<S10>/Min'
   *  MinMax: '<S10>/err+'
   *  MinMax: '<S10>/err'+'
   *  Product: '<S10>/Product2'
   *  RelationalOperator: '<S28>/Compare'
   *  Sum: '<S10>/Minus6'
   *  Sum: '<S10>/r+'
   */
  Memory_PreviousInput_0 = (fmin(0.75, (1.0 - (real_T)(rtb_Add1_c == 0.0)) *
    rtb_ua * 0.0005) + 0.1 * rtb_Add1_c) + fmax((rtb_Product4_idx_1 -
    rtDW.Memory_PreviousInput_o[1]) * 20.0, 0.0) * 0.03;

  /* Saturate: '<S10>/Saturation' */
  if (Memory_PreviousInput_0 > 1.0) {
    Memory_PreviousInput_0 = 1.0;
  } else if (Memory_PreviousInput_0 < 0.0) {
    Memory_PreviousInput_0 = 0.0;
  }

  /* Outport: '<Root>/T_pos1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S10>/Constant17'
   *  Gain: '<S9>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Saturate: '<S10>/Saturation'
   *  Sum: '<S10>/ktc+'
   */
  rtY.T_pos1[1] = fmin(fmin(21.0, u0), (1.0 - Memory_PreviousInput_0) *
                       rtb_Product1_l_idx_1);

  /* Update for Memory: '<S4>/Memory' */
  rtDW.Memory_PreviousInput_i[1] = rtb_Product_idx_1;

  /* Update for Memory: '<S20>/Memory' */
  rtDW.Memory_PreviousInput_j[1] = rtb_vims_idx_1;

  /* Update for Memory: '<S10>/Memory1' */
  rtDW.Memory1_PreviousInput_n[1] = rtb_ua;

  /* Update for Memory: '<S10>/Memory' incorporates:
   *  MinMax: '<S10>/err+'
   */
  rtDW.Memory_PreviousInput_o[1] = rtb_Product4_idx_1;

  /* MinMax: '<S10>/err+' incorporates:
   *  Constant: '<S10>/Constant'
   */
  rtb_Add1_c = fmax(0.0, rtb_Gain3_c_idx_2);

  /* Sum: '<S10>/Add7' incorporates:
   *  Memory: '<S10>/Memory1'
   */
  rtb_ua = rtb_Add1_c + rtDW.Memory1_PreviousInput_n[2];

  /* Sum: '<S10>/Add8' incorporates:
   *  Constant: '<S10>/Constant11'
   *  Constant: '<S10>/Constant12'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S28>/Constant'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain2'
   *  Gain: '<S10>/Gain3'
   *  Gain: '<S10>/Gain4'
   *  Memory: '<S10>/Memory'
   *  MinMax: '<S10>/Min'
   *  MinMax: '<S10>/err+'
   *  MinMax: '<S10>/err'+'
   *  Product: '<S10>/Product2'
   *  RelationalOperator: '<S28>/Compare'
   *  Sum: '<S10>/Minus6'
   *  Sum: '<S10>/r+'
   */
  Memory_PreviousInput_0 = (fmin(0.75, (1.0 - (real_T)(rtb_Add1_c == 0.0)) *
    rtb_ua * 0.0005) + 0.1 * rtb_Add1_c) + fmax((rtb_Gain3_c_idx_2 -
    rtDW.Memory_PreviousInput_o[2]) * 20.0, 0.0) * 0.03;

  /* Saturate: '<S10>/Saturation' */
  if (Memory_PreviousInput_0 > 1.0) {
    Memory_PreviousInput_0 = 1.0;
  } else if (Memory_PreviousInput_0 < 0.0) {
    Memory_PreviousInput_0 = 0.0;
  }

  /* Outport: '<Root>/T_pos1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S10>/Constant17'
   *  Gain: '<S9>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Saturate: '<S10>/Saturation'
   *  Sum: '<S10>/ktc+'
   */
  rtY.T_pos1[2] = fmin(fmin(21.0, u0_0), (1.0 - Memory_PreviousInput_0) *
                       rtb_Product1_l_idx_2);

  /* Update for Memory: '<S4>/Memory' */
  rtDW.Memory_PreviousInput_i[2] = rtb_Product_idx_2;

  /* Update for Memory: '<S20>/Memory' */
  rtDW.Memory_PreviousInput_j[2] = rtb_vims_idx_2;

  /* Update for Memory: '<S10>/Memory1' */
  rtDW.Memory1_PreviousInput_n[2] = rtb_ua;

  /* Update for Memory: '<S10>/Memory' incorporates:
   *  MinMax: '<S10>/err+'
   */
  rtDW.Memory_PreviousInput_o[2] = rtb_Gain3_c_idx_2;

  /* MinMax: '<S10>/err+' incorporates:
   *  Constant: '<S10>/Constant'
   */
  rtb_Add1_c = fmax(0.0, rtb_Product4_idx_3);

  /* Sum: '<S10>/Add7' incorporates:
   *  Memory: '<S10>/Memory1'
   */
  rtb_ua = rtb_Add1_c + rtDW.Memory1_PreviousInput_n[3];

  /* Sum: '<S10>/Add8' incorporates:
   *  Constant: '<S10>/Constant11'
   *  Constant: '<S10>/Constant12'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S28>/Constant'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain2'
   *  Gain: '<S10>/Gain3'
   *  Gain: '<S10>/Gain4'
   *  Memory: '<S10>/Memory'
   *  MinMax: '<S10>/Min'
   *  MinMax: '<S10>/err+'
   *  MinMax: '<S10>/err'+'
   *  Product: '<S10>/Product2'
   *  RelationalOperator: '<S28>/Compare'
   *  Sum: '<S10>/Minus6'
   *  Sum: '<S10>/r+'
   */
  Memory_PreviousInput_0 = (fmin(0.75, (1.0 - (real_T)(rtb_Add1_c == 0.0)) *
    rtb_ua * 0.0005) + 0.1 * rtb_Add1_c) + fmax((rtb_Product4_idx_3 -
    rtDW.Memory_PreviousInput_o[3]) * 20.0, 0.0) * 0.03;

  /* Saturate: '<S10>/Saturation' */
  if (Memory_PreviousInput_0 > 1.0) {
    Memory_PreviousInput_0 = 1.0;
  } else if (Memory_PreviousInput_0 < 0.0) {
    Memory_PreviousInput_0 = 0.0;
  }

  /* Outport: '<Root>/T_pos1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S10>/Constant17'
   *  Gain: '<S9>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Product: '<S9>/Product1'
   *  Saturate: '<S10>/Saturation'
   *  Saturate: '<S4>/Saturation'
   *  Sum: '<S10>/ktc+'
   */
  rtY.T_pos1[3] = fmin(fmin(21.0, u * Memory_PreviousInput *
    0.078947160665366667), (1.0 - Memory_PreviousInput_0) * rtb_Product1_l_idx_3);

  /* Update for Memory: '<S4>/Memory' */
  rtDW.Memory_PreviousInput_i[3] = rtb_x_k_idx_0;

  /* Update for Memory: '<S20>/Memory' */
  rtDW.Memory_PreviousInput_j[3] = rtb_vims_idx_3;

  /* Update for Memory: '<S10>/Memory1' */
  rtDW.Memory1_PreviousInput_n[3] = rtb_ua;

  /* Update for Memory: '<S10>/Memory' incorporates:
   *  MinMax: '<S10>/err+'
   */
  rtDW.Memory_PreviousInput_o[3] = rtb_Product4_idx_3;

  /* Update for Memory: '<S22>/Memory' */
  rtDW.Memory_PreviousInput_g = rtb_Gain3_c_idx_1;

  /* Update for Delay: '<S22>/Delay1' */
  for (k = 0; k < 9; k++) {
    rtDW.Delay1_DSTATE[k] = rtDW.Delay1_DSTATE[k + 1];
  }

  rtDW.Delay1_DSTATE[9] = rtb_Compare_c;

  /* End of Update for Delay: '<S22>/Delay1' */
}

/* Model initialize function */
void TV_2024_2_initialize(void)
{
  /* InitializeConditions for Memory: '<S3>/Memory2' */
  rtDW.Memory2_PreviousInput[0] = 1.3;
  rtDW.Memory2_PreviousInput[1] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
