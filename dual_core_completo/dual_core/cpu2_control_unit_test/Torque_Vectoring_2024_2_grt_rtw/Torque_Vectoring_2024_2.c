/*
 * Torque_Vectoring_2024_2.c
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
#include "rtwtypes.h"
#include <emmintrin.h>
#include <math.h>
#include "Torque_Vectoring_2024_2_private.h"
#include <string.h>
#include "rt_nonfinite.h"

/* Block states (default storage) */
DW_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_Y;

/* Real-time model */
static RT_MODEL_Torque_Vectoring_2024_2_T Torque_Vectoring_2024_2_M_;
RT_MODEL_Torque_Vectoring_2024_2_T *const Torque_Vectoring_2024_2_M =
  &Torque_Vectoring_2024_2_M_;
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
void Torque_Vectoring_2024_2_step(void)
{
  __m128d tmp_2;
  __m128d tmp_3;
  real_T rtb_A_k[4];
  real_T rtb_Exp4[4];
  real_T rtb_PowerFactor[4];
  real_T rtb_K_k[2];
  real_T rtb_Sliperror[2];
  real_T rtb_delta_fldelta_frrad[2];
  real_T tmp_4[2];
  real_T rtb_DeadZone_c;
  real_T rtb_DeadZone_i;
  real_T rtb_Gain9;
  real_T rtb_Integrator_h;
  real_T rtb_Integrator_m;
  real_T rtb_Integrator_o;
  real_T rtb_MathFunction5_0;
  real_T rtb_PowerFactor_0;
  real_T rtb_Product4_0;
  real_T rtb_Product7_0;
  real_T rtb_Product8_0;
  real_T rtb_Product_idx_0;
  real_T rtb_Product_idx_1;
  real_T rtb_Product_idx_2;
  real_T rtb_Saturation;
  real_T rtb_Saturation1;
  real_T rtb_Saturation_e_idx_0;
  real_T rtb_Saturation_e_idx_1;
  real_T rtb_Saturation_e_idx_2;
  real_T rtb_Saturation_g;
  real_T rtb_Saturation_g5_tmp;
  real_T rtb_Saturation_k2;
  real_T rtb_Saturation_nm;
  real_T rtb_Switch_h;
  real_T rtb_TmpSignalConversionAtMathFunctionInport1_idx_0;
  real_T rtb_TmpSignalConversionAtMathFunctionInport1_idx_1;
  real_T rtb_TmpSignalConversionAtMathFunctionInport1_idx_2;
  real_T rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  real_T rtb_vims_idx_0;
  real_T rtb_vims_idx_1;
  real_T rtb_vims_idx_3;
  real_T rtb_vxms;
  real_T u0;
  real_T u0_0;
  real_T u0_1;
  int32_T i;
  int32_T tmp_5;
  int32_T tmp_6;
  real32_T rtb_Saturation5_0;
  real32_T rtb_Saturation5_idx_0;
  real32_T rtb_Saturation5_idx_1;
  real32_T rtb_Saturation5_idx_2;
  real32_T tmp;
  int8_T tmp_0;
  int8_T tmp_1;

  /* SignalConversion generated from: '<S12>/Vector Concatenate' incorporates:
   *  Constant: '<S12>/Constant'
   */
  rtb_A_k[0] = 1.0;

  /* Gain: '<S12>/Gain' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[1] = -0.0099999997764825821 *
    Torque_Vectoring_2024_2_DW.Memory4_PreviousInput;

  /* Gain: '<S12>/Gain1' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[2] = 0.0099999997764825821 *
    Torque_Vectoring_2024_2_DW.Memory4_PreviousInput;

  /* SignalConversion generated from: '<S12>/Vector Concatenate1' incorporates:
   *  Constant: '<S12>/Constant'
   */
  rtb_A_k[3] = 1.0;

  /* Product: '<S12>/Product2' incorporates:
   *  Concatenate: '<S12>/Vector Concatenate2'
   *  Math: '<S12>/Transpose'
   *  Memory: '<S12>/Memory'
   */
  rtb_Saturation1 = rtb_A_k[2];
  rtb_Saturation = rtb_A_k[1];
  for (i = 0; i <= 0; i += 2) {
    tmp_2 = _mm_loadu_pd(&Torque_Vectoring_2024_2_DW.Memory_PreviousInput[i + 2]);
    tmp_3 = _mm_loadu_pd(&Torque_Vectoring_2024_2_DW.Memory_PreviousInput[i]);
    _mm_storeu_pd(&rtb_Exp4[i], _mm_add_pd(_mm_mul_pd(tmp_2, _mm_set1_pd
      (rtb_Saturation1)), tmp_3));
    _mm_storeu_pd(&rtb_Exp4[i + 2], _mm_add_pd(_mm_mul_pd(tmp_3, _mm_set1_pd
      (rtb_Saturation)), tmp_2));
  }

  /* Product: '<S12>/Product4' */
  rtb_Saturation1 = 0.0;

  /* Product: '<S12>/Product2' */
  rtb_Saturation = rtb_Exp4[1];
  rtb_vxms = rtb_Exp4[0];
  rtb_DeadZone_i = rtb_Exp4[3];
  rtb_Saturation_g = rtb_Exp4[2];

  /* Product: '<S12>/Product4' incorporates:
   *  Math: '<S12>/Transpose2'
   */
  rtb_Saturation_nm = Torque_Vectoring_2024_2_ConstB.Transpose2[0];
  rtb_vims_idx_0 = Torque_Vectoring_2024_2_ConstB.Transpose2[1];
  for (i = 0; i < 2; i++) {
    /* Sum: '<S12>/Add' incorporates:
     *  Concatenate: '<S12>/Vector Concatenate2'
     *  Constant: '<S12>/Constant7'
     *  Math: '<S19>/Exp4'
     *  Product: '<S12>/Product2'
     *
     * About '<S19>/Exp4':
     *  Operator: exp
     */
    rtb_vims_idx_1 = rtb_A_k[i + 2];
    rtb_Switch_h = (rtb_vims_idx_1 * rtb_Saturation + rtb_A_k[i] * rtb_vxms) +
      Torque_Vectoring_2024_2_ConstP.Constant7_Value_d[i];
    rtb_Exp4[i] = rtb_Switch_h;

    /* Product: '<S12>/Product4' incorporates:
     *  Math: '<S12>/Transpose2'
     *  Product: '<S12>/Product3'
     */
    rtb_Gain9 = rtb_Switch_h * rtb_Saturation_nm;

    /* Sum: '<S12>/Add' incorporates:
     *  Concatenate: '<S12>/Vector Concatenate2'
     *  Constant: '<S12>/Constant7'
     *  Math: '<S19>/Exp4'
     *  Product: '<S12>/Product2'
     *
     * About '<S19>/Exp4':
     *  Operator: exp
     */
    rtb_Switch_h = (rtb_vims_idx_1 * rtb_DeadZone_i + rtb_A_k[i] *
                    rtb_Saturation_g) +
      Torque_Vectoring_2024_2_ConstP.Constant7_Value_d[i + 2];
    rtb_Exp4[i + 2] = rtb_Switch_h;

    /* Product: '<S12>/Product4' incorporates:
     *  Constant: '<S12>/Constant4'
     *  Math: '<S12>/Transpose2'
     *  Product: '<S12>/Product3'
     */
    rtb_Gain9 += rtb_Switch_h * rtb_vims_idx_0;
    rtb_K_k[i] = rtb_Gain9;
    rtb_Saturation1 += Torque_Vectoring_2024_2_ConstP.Constant4_Value[i] *
      rtb_Gain9;
  }

  /* Product: '<S12>/Product3' incorporates:
   *  Constant: '<S12>/Constant5'
   *  Product: '<S12>/Product4'
   *  Sum: '<S12>/Add2'
   */
  tmp_2 = _mm_div_pd(_mm_loadu_pd(&rtb_K_k[0]), _mm_add_pd(_mm_set1_pd
    (rtb_Saturation1), _mm_set1_pd(0.01)));

  /* Product: '<S12>/Divide' incorporates:
   *  Product: '<S12>/Product3'
   */
  _mm_storeu_pd(&rtb_K_k[0], tmp_2);

  /* Sum: '<S12>/Add1' incorporates:
   *  Constant: '<S12>/Constant6'
   *  Product: '<S12>/Divide'
   *  Product: '<S12>/Product5'
   */
  tmp_2 = _mm_sub_pd(_mm_set_pd(0.0, 1.0), _mm_loadu_pd(&rtb_K_k[0]));
  _mm_storeu_pd(&tmp_4[0], tmp_2);

  /* Sum: '<S12>/Add1' incorporates:
   *  Constant: '<S12>/Constant4'
   *  Constant: '<S12>/Constant6'
   *  Product: '<S12>/Divide'
   *  Product: '<S12>/Product5'
   */
  rtb_vims_idx_1 = tmp_4[0];
  rtb_Saturation = tmp_4[1];
  rtb_vims_idx_0 = 0.0 - rtb_K_k[0] * 0.0;
  rtb_Saturation1 = rtb_K_k[1] * 0.0;
  for (i = 0; i <= 0; i += 2) {
    /* Product: '<S12>/Product6' incorporates:
     *  Math: '<S19>/Exp4'
     *  Memory: '<S12>/Memory'
     *
     * About '<S19>/Exp4':
     *  Operator: exp
     */
    tmp_5 = (i + 1) << 1;
    tmp_6 = i << 1;
    tmp_2 = _mm_set_pd(rtb_Exp4[tmp_5 + 1], rtb_Exp4[tmp_6 + 1]);
    tmp_3 = _mm_set_pd(rtb_Exp4[tmp_5], rtb_Exp4[tmp_6]);
    _mm_storeu_pd(&tmp_4[0], _mm_add_pd(_mm_mul_pd(tmp_2, _mm_set1_pd
      (rtb_vims_idx_0)), _mm_mul_pd(tmp_3, _mm_set1_pd(rtb_vims_idx_1))));
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput[tmp_6] = tmp_4[0];
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput[tmp_5] = tmp_4[1];

    /* Sum: '<S12>/Add1' incorporates:
     *  Constant: '<S12>/Constant6'
     *  Product: '<S12>/Product6'
     */
    _mm_storeu_pd(&tmp_4[0], _mm_add_pd(_mm_mul_pd(tmp_2, _mm_sub_pd(_mm_set1_pd
      (1.0), _mm_set1_pd(rtb_Saturation1))), _mm_mul_pd(tmp_3, _mm_set1_pd
      (rtb_Saturation))));

    /* Product: '<S12>/Product6' incorporates:
     *  Memory: '<S12>/Memory'
     */
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput[tmp_6 + 1] = tmp_4[0];
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput[tmp_5 + 1] = tmp_4[1];
  }

  /* Saturate: '<Root>/Saturation1' incorporates:
   *  Inport: '<Root>/ay'
   */
  if (Torque_Vectoring_2024_2_U.ay > 25.506000000000004) {
    rtb_Saturation1 = 25.506000000000004;
  } else if (Torque_Vectoring_2024_2_U.ay < -25.506000000000004) {
    rtb_Saturation1 = -25.506000000000004;
  } else {
    rtb_Saturation1 = Torque_Vectoring_2024_2_U.ay;
  }

  /* End of Saturate: '<Root>/Saturation1' */

  /* Gain: '<S9>/Gain3' */
  rtb_Saturation_g = 28.224717611553253 * rtb_Saturation1;

  /* Saturate: '<Root>/Saturation' incorporates:
   *  Inport: '<Root>/ax'
   */
  if (Torque_Vectoring_2024_2_U.ax > 17.658) {
    rtb_Saturation = 17.658;
  } else if (Torque_Vectoring_2024_2_U.ax < -20.601000000000003) {
    rtb_Saturation = -20.601000000000003;
  } else {
    rtb_Saturation = Torque_Vectoring_2024_2_U.ax;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Gain: '<S9>/Gain2' */
  rtb_Integrator_h = 27.788921824104236 * rtb_Saturation;

  /* Memory: '<Root>/Memory' */
  rtb_vxms = Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k;

  /* Gain: '<S9>/Fl' incorporates:
   *  Math: '<S9>/Square'
   *  Memory: '<Root>/Memory'
   */
  rtb_DeadZone_c = Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k *
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k * 2.75625;

  /* Gain: '<S9>/Gain1' */
  rtb_Saturation_nm = 0.26535596091205216 * rtb_DeadZone_c;

  /* Sum: '<S9>/Add' incorporates:
   *  Constant: '<S9>/Constant'
   */
  rtb_Integrator_m = ((627.682966425 - rtb_Saturation_g) - rtb_Integrator_h) +
    rtb_Saturation_nm;

  /* Sum: '<S9>/Add1' incorporates:
   *  Constant: '<S9>/Constant'
   */
  rtb_Saturation_g = ((rtb_Saturation_g + 627.682966425) - rtb_Integrator_h) +
    rtb_Saturation_nm;

  /* Gain: '<S9>/Gain4' */
  rtb_Saturation_nm = 42.162989448157909 * rtb_Saturation1;

  /* Gain: '<S9>/Gain' */
  rtb_DeadZone_c *= 0.23464403908794787;

  /* Sum: '<S9>/Add2' incorporates:
   *  Constant: '<S9>/Constant1'
   */
  rtb_DeadZone_i = ((767.16807007500006 - rtb_Saturation_nm) + rtb_Integrator_h)
    + rtb_DeadZone_c;

  /* Sum: '<S9>/Add3' incorporates:
   *  Constant: '<S9>/Constant1'
   */
  rtb_Saturation_nm = ((rtb_Saturation_nm + 767.16807007500006) +
                       rtb_Integrator_h) + rtb_DeadZone_c;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_2_U.rpm[0] > 20000.0F) {
    rtb_Saturation5_0 = 20000.0F;
  } else if (Torque_Vectoring_2024_2_U.rpm[0] < 0.0F) {
    rtb_Saturation5_0 = 0.0F;
  } else {
    rtb_Saturation5_0 = Torque_Vectoring_2024_2_U.rpm[0];
  }

  rtb_Saturation5_idx_0 = rtb_Saturation5_0;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = -3.533E-6 * rtb_Integrator_m + 0.2032;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > 0.2032) {
    u0 = 0.2032;
  } else if (u0 < 0.19304) {
    u0 = 0.19304;
  }

  rtb_Saturation_e_idx_0 = u0;

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Switch_h = 0.104719758F * rtb_Saturation5_0 * 0.078947164118289948 * u0;
  rtb_Exp4[0] = rtb_Switch_h;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  Torque_Vectoring_2024_2_Y.lambda[0] = fmax(rtb_Switch_h, 1.0E-5);

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_2_U.rpm[1] > 20000.0F) {
    rtb_Saturation5_0 = 20000.0F;
  } else if (Torque_Vectoring_2024_2_U.rpm[1] < 0.0F) {
    rtb_Saturation5_0 = 0.0F;
  } else {
    rtb_Saturation5_0 = Torque_Vectoring_2024_2_U.rpm[1];
  }

  rtb_Saturation5_idx_1 = rtb_Saturation5_0;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = -3.533E-6 * rtb_Saturation_g + 0.2032;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > 0.2032) {
    u0 = 0.2032;
  } else if (u0 < 0.19304) {
    u0 = 0.19304;
  }

  rtb_Saturation_e_idx_1 = u0;

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Switch_h = 0.104719758F * rtb_Saturation5_0 * 0.078947164118289948 * u0;
  rtb_Exp4[1] = rtb_Switch_h;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  Torque_Vectoring_2024_2_Y.lambda[1] = fmax(rtb_Switch_h, 1.0E-5);

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_2_U.rpm[2] > 20000.0F) {
    rtb_Saturation5_0 = 20000.0F;
  } else if (Torque_Vectoring_2024_2_U.rpm[2] < 0.0F) {
    rtb_Saturation5_0 = 0.0F;
  } else {
    rtb_Saturation5_0 = Torque_Vectoring_2024_2_U.rpm[2];
  }

  rtb_Saturation5_idx_2 = rtb_Saturation5_0;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = -3.533E-6 * rtb_DeadZone_i + 0.2032;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > 0.2032) {
    u0 = 0.2032;
  } else if (u0 < 0.19304) {
    u0 = 0.19304;
  }

  rtb_Saturation_e_idx_2 = u0;

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Switch_h = 0.104719758F * rtb_Saturation5_0 * 0.078947164118289948 * u0;
  rtb_Exp4[2] = rtb_Switch_h;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  Torque_Vectoring_2024_2_Y.lambda[2] = fmax(rtb_Switch_h, 1.0E-5);

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_2_U.rpm[3] > 20000.0F) {
    rtb_Saturation5_0 = 20000.0F;
  } else if (Torque_Vectoring_2024_2_U.rpm[3] < 0.0F) {
    rtb_Saturation5_0 = 0.0F;
  } else {
    rtb_Saturation5_0 = Torque_Vectoring_2024_2_U.rpm[3];
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = -3.533E-6 * rtb_Saturation_nm + 0.2032;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > 0.2032) {
    u0 = 0.2032;
  } else if (u0 < 0.19304) {
    u0 = 0.19304;
  }

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Switch_h = 0.104719758F * rtb_Saturation5_0 * 0.078947164118289948 * u0;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  Torque_Vectoring_2024_2_Y.lambda[3] = fmax(rtb_Switch_h, 1.0E-5);

  /* MinMax: '<S22>/Max2' incorporates:
   *  Constant: '<S22>/Constant2'
   *  Constant: '<S22>/Constant3'
   *  Memory: '<Root>/Memory'
   *  MinMax: '<S22>/Max1'
   */
  tmp_2 = _mm_set_pd(fmax(Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k,
    Torque_Vectoring_2024_2_P.TC_VX_ON_R), fmax
                     (Torque_Vectoring_2024_2_P.TC_VX_ON_F,
                      Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k));

  /* Sum: '<S22>/Sum3' incorporates:
   *  Constant: '<S22>/Constant16'
   *  Product: '<S22>/Divide1'
   */
  tmp_3 = _mm_set1_pd(1.0);
  _mm_storeu_pd(&tmp_4[0], _mm_sub_pd(_mm_div_pd(_mm_set_pd
    (Torque_Vectoring_2024_2_Y.lambda[2], Torque_Vectoring_2024_2_Y.lambda[0]),
    tmp_2), tmp_3));

  /* Product: '<S22>/Divide1' */
  rtb_vims_idx_1 = tmp_4[0];
  rtb_vims_idx_0 = tmp_4[1];

  /* Sum: '<S22>/Sum3' incorporates:
   *  Product: '<S22>/Divide1'
   */
  _mm_storeu_pd(&tmp_4[0], _mm_sub_pd(_mm_div_pd(_mm_set_pd
    (Torque_Vectoring_2024_2_Y.lambda[3], Torque_Vectoring_2024_2_Y.lambda[1]),
    tmp_2), tmp_3));

  /* Saturate: '<Root>/Saturation6' incorporates:
   *  Inport: '<Root>/steering'
   */
  if (Torque_Vectoring_2024_2_U.steering > 100.0F) {
    tmp = 100.0F;
  } else if (Torque_Vectoring_2024_2_U.steering < -100.0F) {
    tmp = -100.0F;
  } else {
    tmp = Torque_Vectoring_2024_2_U.steering;
  }

  /* Gain: '<S2>/Gain3' incorporates:
   *  Saturate: '<Root>/Saturation6'
   */
  rtb_DeadZone_c = 0.000302291038678959 * tmp;

  /* Math: '<S2>/Math Function4' incorporates:
   *  Constant: '<S2>/Constant4'
   *  Math: '<S2>/Math Function2'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_DeadZone_c, 3.0);
  rtb_Saturation_k2 = rtb_Saturation_g5_tmp;

  /* Gain: '<S2>/Gain9' */
  rtb_Gain9 = 63090.0 * rtb_Saturation_k2;

  /* Math: '<S2>/Math Function5' incorporates:
   *  Constant: '<S2>/Constant5'
   *  Math: '<S2>/Math Function1'
   */
  rtb_Saturation_k2 = rt_powd_snf(rtb_DeadZone_c, 4.0);

  /* Math: '<S2>/Math Function3' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Math: '<S2>/Math Function7'
   */
  rtb_vims_idx_3 = rt_powd_snf(rtb_DeadZone_c, 5.0);

  /* Math: '<S2>/Square2' incorporates:
   *  Math: '<S2>/Square1'
   */
  rtb_Product_idx_0 = rtb_DeadZone_c * rtb_DeadZone_c;

  /* Gain: '<S2>/Gain' incorporates:
   *  Constant: '<S2>/Constant7'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S2>/Gain10'
   *  Gain: '<S2>/Gain11'
   *  Gain: '<S2>/Gain2'
   *  Gain: '<S2>/Gain4'
   *  Gain: '<S2>/Gain5'
   *  Gain: '<S2>/Gain6'
   *  Gain: '<S2>/Gain7'
   *  Gain: '<S2>/Gain8'
   *  Math: '<S2>/Math Function3'
   *  Math: '<S2>/Square2'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S2>/Sum2'
   */
  rtb_delta_fldelta_frrad[0] = (((((2.497E+7 * rtb_vims_idx_3 + -1.217E+6 *
    rtb_Saturation_k2) + 63090.0 * rtb_Saturation_g5_tmp) + rtb_Product_idx_0 *
    -3034.0) + 988.7 * rtb_DeadZone_c) - 0.0009525) * 0.017453292519943295;
  rtb_delta_fldelta_frrad[1] = (((((988.7 * rtb_DeadZone_c + 0.0009525) +
    rtb_Product_idx_0 * 3034.0) + rtb_Gain9) + 1.217E+6 * rtb_Saturation_k2) +
    2.497E+7 * rtb_vims_idx_3) * 0.017453292519943295;

  /* Sum: '<S10>/Add' incorporates:
   *  Constant: '<S10>/Constant2'
   */
  rtb_Saturation_k2 = rtb_delta_fldelta_frrad[0] - -0.017453292519943295;

  /* SignalConversion generated from: '<S13>/Cos' */
  rtb_DeadZone_c = rtb_Saturation_k2;

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  Constant: '<S22>/Constant6'
   *  MinMax: '<S22>/Min3'
   */
  Torque_Vectoring_2024_2_Y.lambda[0] = fmax(fmin(rtb_vims_idx_1, 1.0), 0.0);

  /* Outport: '<Root>/wR' */
  Torque_Vectoring_2024_2_Y.wR[0] = rtb_Exp4[0];

  /* Product: '<S13>/Product1' incorporates:
   *  Outport: '<Root>/wR'
   *  SignalConversion generated from: '<S13>/Cos'
   *  Trigonometry: '<S13>/Cos'
   */
  rtb_vims_idx_1 = cos(rtb_Saturation_k2) * rtb_Exp4[0];

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  Constant: '<S22>/Constant6'
   *  MinMax: '<S22>/Min3'
   */
  Torque_Vectoring_2024_2_Y.lambda[1] = fmax(fmin(tmp_4[0], 1.0), 0.0);

  /* Outport: '<Root>/wR' */
  Torque_Vectoring_2024_2_Y.wR[1] = rtb_Exp4[1];

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  Constant: '<S22>/Constant6'
   *  MinMax: '<S22>/Min3'
   */
  Torque_Vectoring_2024_2_Y.lambda[2] = fmax(fmin(rtb_vims_idx_0, 1.0), 0.0);

  /* Outport: '<Root>/wR' */
  Torque_Vectoring_2024_2_Y.wR[2] = rtb_Exp4[2];

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  Constant: '<S22>/Constant6'
   *  MinMax: '<S22>/Min3'
   */
  Torque_Vectoring_2024_2_Y.lambda[3] = fmax(fmin(tmp_4[1], 1.0), 0.0);

  /* Outport: '<Root>/wR' incorporates:
   *  Product: '<Root>/Product'
   */
  Torque_Vectoring_2024_2_Y.wR[3] = rtb_Switch_h;

  /* Saturate: '<Root>/Saturation2' incorporates:
   *  Inport: '<Root>/yaw_r'
   */
  if (Torque_Vectoring_2024_2_U.yaw_r > 6.28318548F) {
    /* Saturate: '<Root>/Saturation2' */
    Torque_Vectoring_2024_2_DW.Memory4_PreviousInput = 6.28318548F;
  } else if (Torque_Vectoring_2024_2_U.yaw_r < -6.28318548F) {
    /* Saturate: '<Root>/Saturation2' */
    Torque_Vectoring_2024_2_DW.Memory4_PreviousInput = -6.28318548F;
  } else {
    /* Saturate: '<Root>/Saturation2' */
    Torque_Vectoring_2024_2_DW.Memory4_PreviousInput =
      Torque_Vectoring_2024_2_U.yaw_r;
  }

  /* End of Saturate: '<Root>/Saturation2' */

  /* Gain: '<S13>/Multiply' */
  rtb_Saturation_k2 = 0.61500000953674316 *
    Torque_Vectoring_2024_2_DW.Memory4_PreviousInput;

  /* Sum: '<S13>/Add' incorporates:
   *  Product: '<S13>/Product1'
   */
  rtb_vims_idx_0 = rtb_Saturation_k2 + rtb_vims_idx_1;

  /* Gain: '<S13>/Multiply2' incorporates:
   *  Gain: '<S13>/Multiply1'
   *  Outport: '<Root>/wR'
   *  SignalConversion generated from: '<S13>/Cos'
   *  Sum: '<S10>/Add1'
   *  Trigonometry: '<S13>/Cos'
   */
  _mm_storeu_pd(&tmp_4[0], _mm_add_pd(_mm_mul_pd(_mm_set_pd(0.60000002384185791,
    cos(rtb_delta_fldelta_frrad[1] - 0.017453292519943295)), _mm_set_pd
    (Torque_Vectoring_2024_2_DW.Memory4_PreviousInput, rtb_Exp4[1])), _mm_mul_pd
    (_mm_set_pd(cos(Torque_Vectoring_2024_2_ConstB.Gain), -0.61500000953674316),
     _mm_set_pd(rtb_Exp4[2], Torque_Vectoring_2024_2_DW.Memory4_PreviousInput))));

  /* Sum: '<S13>/Add' incorporates:
   *  Gain: '<S13>/Multiply3'
   *  Product: '<Root>/Product'
   */
  rtb_vims_idx_1 = tmp_4[0];
  rtb_Gain9 = tmp_4[1];
  rtb_vims_idx_3 = -0.60000002384185791 *
    Torque_Vectoring_2024_2_DW.Memory4_PreviousInput + rtb_Switch_h;

  /* Sum: '<S19>/Add1' */
  rtb_Switch_h = Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_0;

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_Saturation_k2 = rtb_Saturation - (rtb_vims_idx_0 -
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[0]) * 100.0;

  /* Math: '<S19>/Exp4' incorporates:
   *  Gain: '<S19>/Gain'
   *  Math: '<S19>/Exp'
   *  Math: '<S19>/Exp1'
   *  Product: '<S19>/Divide'
   *  Product: '<S19>/Divide1'
   *  Sum: '<S19>/Add3'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   *
   * About '<S19>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S19>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Switch_h = exp(((0.0 - 1.0 / Torque_Vectoring_2024_2_ConstB.Exp2 *
                       (rtb_Switch_h * rtb_Switch_h)) - rtb_Saturation_k2 *
                      rtb_Saturation_k2 / Torque_Vectoring_2024_2_ConstB.Exp3) *
                     0.5);
  rtb_Exp4[0] = rtb_Switch_h;

  /* Product: '<S13>/Product' incorporates:
   *  Sum: '<S19>/Add1'
   */
  rtb_Product_idx_0 = rtb_vims_idx_0 * rtb_Switch_h;

  /* Saturate: '<S8>/Saturation' */
  if (rtb_DeadZone_c > 0.4) {
    rtb_DeadZone_c = 0.4;
  } else if (rtb_DeadZone_c < -0.4) {
    rtb_DeadZone_c = -0.4;
  }

  /* Math: '<S8>/Square' incorporates:
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_k2 = rtb_Integrator_m * rtb_Integrator_m;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Integrator_o = rt_powd_snf(rtb_Integrator_m, 3.0);

  /* Gain: '<S8>/Gain2' */
  rtb_Switch_h = -1.8682E-5 * rtb_Integrator_o;

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_Integrator_m, 4.0);

  /* Gain: '<S8>/Gain3' */
  rtb_Integrator_h = 1.8267E-8 * rtb_MathFunction5_0;

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_Integrator_m, 5.0);

  /* Gain: '<S8>/Gain4' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_0 = -8.8652E-12 *
    rtb_Saturation_g5_tmp;

  /* Product: '<S8>/Product13' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_1 = rtb_DeadZone_c *
    rtb_Integrator_o;

  /* Product: '<S8>/Product12' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_2 = rtb_DeadZone_c *
    rtb_MathFunction5_0;

  /* Product: '<S8>/Product11' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_DeadZone_c *
    rtb_Saturation_g5_tmp;

  /* Math: '<S8>/Square1' */
  rtb_PowerFactor_0 = rtb_DeadZone_c * rtb_DeadZone_c;

  /* Product: '<S8>/Product8' */
  rtb_Product8_0 = rtb_PowerFactor_0 * rtb_Integrator_o;

  /* Product: '<S8>/Product7' */
  rtb_Product7_0 = rtb_PowerFactor_0 * rtb_MathFunction5_0;

  /* Math: '<S8>/Math Function4' incorporates:
   *  Constant: '<S8>/Constant4'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_DeadZone_c, 3.0);

  /* Product: '<S8>/Product4' */
  rtb_Product4_0 = rtb_Saturation_g5_tmp * rtb_Integrator_o;

  /* Math: '<S8>/Math Function5' incorporates:
   *  Constant: '<S8>/Constant5'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_DeadZone_c, 4.0);

  /* Math: '<S8>/Math Function7' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_Integrator_o = rt_powd_snf(rtb_DeadZone_c, 5.0);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Constant: '<S8>/Constant8'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain12'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain20'
   *  Gain: '<S8>/Gain21'
   *  Gain: '<S8>/Gain22'
   *  Gain: '<S8>/Gain23'
   *  Gain: '<S8>/Gain24'
   *  Gain: '<S8>/Gain25'
   *  Gain: '<S8>/Gain26'
   *  Gain: '<S8>/Gain27'
   *  Gain: '<S8>/Gain5'
   *  Gain: '<S8>/Gain6'
   *  Gain: '<S8>/Gain7'
   *  Gain: '<S8>/Gain8'
   *  Gain: '<S8>/Gain9'
   *  Math: '<S8>/Math Function2'
   *  Math: '<S8>/Math Function6'
   *  Product: '<S8>/Product'
   *  Product: '<S8>/Product10'
   *  Product: '<S8>/Product14'
   *  Product: '<S8>/Product15'
   *  Product: '<S8>/Product2'
   *  Product: '<S8>/Product3'
   *  Product: '<S8>/Product5'
   *  Product: '<S8>/Product6'
   *  Product: '<S8>/Product9'
   *  SignalConversion generated from: '<S8>/Math Function'
   *  Sum: '<S8>/Add'
   */
  u0_0 = ((((((((((((((((((((((((((0.2483 * rtb_Integrator_m + 0.0088 *
    rtb_Saturation_k2) + rtb_Switch_h) + rtb_Integrator_h) +
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_0) + 1.7349E-15 *
    rt_powd_snf(rtb_Integrator_m, 6.0)) + rtb_DeadZone_c * rtb_Integrator_m *
    -0.00098788) + rtb_DeadZone_c * rtb_Saturation_k2 * 5.2321E-5) + -3.0722E-8 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_1) + -2.1326E-11 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_2) + 1.417E-14 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3) + rtb_PowerFactor_0 *
    rtb_Integrator_m * -34.6685) + rtb_PowerFactor_0 * rtb_Saturation_k2 *
                        2.9871E-5) + 1.7183E-5 * rtb_Product8_0) + -6.5431E-9 *
                      rtb_Product7_0) + rtb_Saturation_g5_tmp * rtb_Integrator_m
                     * -0.202) + rtb_Saturation_g5_tmp * rtb_Saturation_k2 *
                    0.00013761) + 1.2868E-9 * rtb_Product4_0) +
                  rtb_MathFunction5_0 * rtb_Integrator_m * 202.6574) +
                 rtb_MathFunction5_0 * rtb_Saturation_k2 * -0.0863) +
                rtb_Integrator_o * rtb_Integrator_m * -0.1108) + 1.146 *
               rtb_DeadZone_c) + -12185.0 * rtb_PowerFactor_0) + -10.876 *
             rtb_Saturation_g5_tmp) + 260290.0 * rtb_MathFunction5_0) + 346.9631
           * rtb_Integrator_o) + -1.4028E+6 * rt_powd_snf(rtb_DeadZone_c, 6.0))
    + 300.2078;

  /* Sum: '<S19>/Add1' */
  rtb_Switch_h = Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0] - tmp_4[0];

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   */
  rtb_Saturation_k2 = rtb_Saturation - (tmp_4[0] -
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[1]) * 100.0;

  /* Math: '<S19>/Exp4' incorporates:
   *  Gain: '<S19>/Gain'
   *  Math: '<S19>/Exp'
   *  Math: '<S19>/Exp1'
   *  Product: '<S19>/Divide'
   *  Product: '<S19>/Divide1'
   *  Sum: '<S19>/Add3'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   *
   * About '<S19>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S19>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Switch_h = exp(((0.0 - 1.0 / Torque_Vectoring_2024_2_ConstB.Exp2 *
                       (rtb_Switch_h * rtb_Switch_h)) - rtb_Saturation_k2 *
                      rtb_Saturation_k2 / Torque_Vectoring_2024_2_ConstB.Exp3) *
                     0.5);
  rtb_Exp4[1] = rtb_Switch_h;

  /* Product: '<S13>/Product' */
  rtb_Product_idx_1 = tmp_4[0] * rtb_Switch_h;

  /* Saturate: '<S8>/Saturation' incorporates:
   *  Sum: '<S10>/Add1'
   */
  if (rtb_delta_fldelta_frrad[1] - 0.017453292519943295 > 0.4) {
    rtb_DeadZone_c = 0.4;
  } else if (rtb_delta_fldelta_frrad[1] - 0.017453292519943295 < -0.4) {
    rtb_DeadZone_c = -0.4;
  } else {
    rtb_DeadZone_c = rtb_delta_fldelta_frrad[1] - 0.017453292519943295;
  }

  /* Math: '<S8>/Square' incorporates:
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_k2 = rtb_Saturation_g * rtb_Saturation_g;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Integrator_o = rt_powd_snf(rtb_Saturation_g, 3.0);

  /* Gain: '<S8>/Gain2' */
  rtb_Switch_h = -1.8682E-5 * rtb_Integrator_o;

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_Saturation_g, 4.0);

  /* Gain: '<S8>/Gain3' */
  rtb_Integrator_h = 1.8267E-8 * rtb_MathFunction5_0;

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_Saturation_g, 5.0);

  /* Gain: '<S8>/Gain4' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_0 = -8.8652E-12 *
    rtb_Saturation_g5_tmp;

  /* Product: '<S8>/Product13' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_1 = rtb_DeadZone_c *
    rtb_Integrator_o;

  /* Product: '<S8>/Product12' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_2 = rtb_DeadZone_c *
    rtb_MathFunction5_0;

  /* Product: '<S8>/Product11' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_DeadZone_c *
    rtb_Saturation_g5_tmp;

  /* Math: '<S8>/Square1' */
  rtb_PowerFactor_0 = rtb_DeadZone_c * rtb_DeadZone_c;

  /* Product: '<S8>/Product8' */
  rtb_Product8_0 = rtb_PowerFactor_0 * rtb_Integrator_o;

  /* Product: '<S8>/Product7' */
  rtb_Product7_0 = rtb_PowerFactor_0 * rtb_MathFunction5_0;

  /* Math: '<S8>/Math Function4' incorporates:
   *  Constant: '<S8>/Constant4'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_DeadZone_c, 3.0);

  /* Product: '<S8>/Product4' */
  rtb_Product4_0 = rtb_Saturation_g5_tmp * rtb_Integrator_o;

  /* Math: '<S8>/Math Function5' incorporates:
   *  Constant: '<S8>/Constant5'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_DeadZone_c, 4.0);

  /* Math: '<S8>/Math Function7' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_Integrator_o = rt_powd_snf(rtb_DeadZone_c, 5.0);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Constant: '<S8>/Constant8'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain12'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain20'
   *  Gain: '<S8>/Gain21'
   *  Gain: '<S8>/Gain22'
   *  Gain: '<S8>/Gain23'
   *  Gain: '<S8>/Gain24'
   *  Gain: '<S8>/Gain25'
   *  Gain: '<S8>/Gain26'
   *  Gain: '<S8>/Gain27'
   *  Gain: '<S8>/Gain5'
   *  Gain: '<S8>/Gain6'
   *  Gain: '<S8>/Gain7'
   *  Gain: '<S8>/Gain8'
   *  Gain: '<S8>/Gain9'
   *  Math: '<S8>/Math Function2'
   *  Math: '<S8>/Math Function6'
   *  Product: '<S8>/Product'
   *  Product: '<S8>/Product10'
   *  Product: '<S8>/Product14'
   *  Product: '<S8>/Product15'
   *  Product: '<S8>/Product2'
   *  Product: '<S8>/Product3'
   *  Product: '<S8>/Product5'
   *  Product: '<S8>/Product6'
   *  Product: '<S8>/Product9'
   *  SignalConversion generated from: '<S8>/Math Function'
   *  Sum: '<S8>/Add'
   */
  u0_1 = ((((((((((((((((((((((((((0.2483 * rtb_Saturation_g + 0.0088 *
    rtb_Saturation_k2) + rtb_Switch_h) + rtb_Integrator_h) +
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_0) + 1.7349E-15 *
    rt_powd_snf(rtb_Saturation_g, 6.0)) + rtb_DeadZone_c * rtb_Saturation_g *
    -0.00098788) + rtb_DeadZone_c * rtb_Saturation_k2 * 5.2321E-5) + -3.0722E-8 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_1) + -2.1326E-11 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_2) + 1.417E-14 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3) + rtb_PowerFactor_0 *
    rtb_Saturation_g * -34.6685) + rtb_PowerFactor_0 * rtb_Saturation_k2 *
                        2.9871E-5) + 1.7183E-5 * rtb_Product8_0) + -6.5431E-9 *
                      rtb_Product7_0) + rtb_Saturation_g5_tmp * rtb_Saturation_g
                     * -0.202) + rtb_Saturation_g5_tmp * rtb_Saturation_k2 *
                    0.00013761) + 1.2868E-9 * rtb_Product4_0) +
                  rtb_MathFunction5_0 * rtb_Saturation_g * 202.6574) +
                 rtb_MathFunction5_0 * rtb_Saturation_k2 * -0.0863) +
                rtb_Integrator_o * rtb_Saturation_g * -0.1108) + 1.146 *
               rtb_DeadZone_c) + -12185.0 * rtb_PowerFactor_0) + -10.876 *
             rtb_Saturation_g5_tmp) + 260290.0 * rtb_MathFunction5_0) + 346.9631
           * rtb_Integrator_o) + -1.4028E+6 * rt_powd_snf(rtb_DeadZone_c, 6.0))
    + 300.2078;

  /* Sum: '<S19>/Add1' */
  rtb_Switch_h = Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0] - tmp_4[1];

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   */
  rtb_Saturation_k2 = rtb_Saturation - (tmp_4[1] -
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[2]) * 100.0;

  /* Math: '<S19>/Exp4' incorporates:
   *  Gain: '<S19>/Gain'
   *  Math: '<S19>/Exp'
   *  Math: '<S19>/Exp1'
   *  Product: '<S19>/Divide'
   *  Product: '<S19>/Divide1'
   *  Sum: '<S19>/Add3'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   *
   * About '<S19>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S19>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Switch_h = exp(((0.0 - 1.0 / Torque_Vectoring_2024_2_ConstB.Exp2 *
                       (rtb_Switch_h * rtb_Switch_h)) - rtb_Saturation_k2 *
                      rtb_Saturation_k2 / Torque_Vectoring_2024_2_ConstB.Exp3) *
                     0.5);
  rtb_Exp4[2] = rtb_Switch_h;

  /* Product: '<S13>/Product' */
  rtb_Product_idx_2 = tmp_4[1] * rtb_Switch_h;

  /* Saturate: '<S8>/Saturation' incorporates:
   *  SignalConversion generated from: '<S13>/Cos'
   */
  if (Torque_Vectoring_2024_2_ConstB.Gain > 0.4) {
    rtb_DeadZone_c = 0.4;
  } else if (Torque_Vectoring_2024_2_ConstB.Gain < -0.4) {
    rtb_DeadZone_c = -0.4;
  } else {
    rtb_DeadZone_c = Torque_Vectoring_2024_2_ConstB.Gain;
  }

  /* Math: '<S8>/Square' incorporates:
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_k2 = rtb_DeadZone_i * rtb_DeadZone_i;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Integrator_o = rt_powd_snf(rtb_DeadZone_i, 3.0);

  /* Gain: '<S8>/Gain2' */
  rtb_Switch_h = -1.8682E-5 * rtb_Integrator_o;

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_DeadZone_i, 4.0);

  /* Gain: '<S8>/Gain3' */
  rtb_Integrator_h = 1.8267E-8 * rtb_MathFunction5_0;

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_DeadZone_i, 5.0);

  /* Gain: '<S8>/Gain4' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_0 = -8.8652E-12 *
    rtb_Saturation_g5_tmp;

  /* Product: '<S8>/Product13' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_1 = rtb_DeadZone_c *
    rtb_Integrator_o;

  /* Product: '<S8>/Product12' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_2 = rtb_DeadZone_c *
    rtb_MathFunction5_0;

  /* Product: '<S8>/Product11' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_DeadZone_c *
    rtb_Saturation_g5_tmp;

  /* Math: '<S8>/Square1' */
  rtb_PowerFactor_0 = rtb_DeadZone_c * rtb_DeadZone_c;

  /* Product: '<S8>/Product8' */
  rtb_Product8_0 = rtb_PowerFactor_0 * rtb_Integrator_o;

  /* Product: '<S8>/Product7' */
  rtb_Product7_0 = rtb_PowerFactor_0 * rtb_MathFunction5_0;

  /* Math: '<S8>/Math Function4' incorporates:
   *  Constant: '<S8>/Constant4'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_DeadZone_c, 3.0);

  /* Product: '<S8>/Product4' */
  rtb_Product4_0 = rtb_Saturation_g5_tmp * rtb_Integrator_o;

  /* Math: '<S8>/Math Function5' incorporates:
   *  Constant: '<S8>/Constant5'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_DeadZone_c, 4.0);

  /* Math: '<S8>/Math Function7' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_Integrator_o = rt_powd_snf(rtb_DeadZone_c, 5.0);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Constant: '<S8>/Constant8'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain12'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain20'
   *  Gain: '<S8>/Gain21'
   *  Gain: '<S8>/Gain22'
   *  Gain: '<S8>/Gain23'
   *  Gain: '<S8>/Gain24'
   *  Gain: '<S8>/Gain25'
   *  Gain: '<S8>/Gain26'
   *  Gain: '<S8>/Gain27'
   *  Gain: '<S8>/Gain5'
   *  Gain: '<S8>/Gain6'
   *  Gain: '<S8>/Gain7'
   *  Gain: '<S8>/Gain8'
   *  Gain: '<S8>/Gain9'
   *  Math: '<S8>/Math Function2'
   *  Math: '<S8>/Math Function6'
   *  Product: '<S8>/Product'
   *  Product: '<S8>/Product10'
   *  Product: '<S8>/Product14'
   *  Product: '<S8>/Product15'
   *  Product: '<S8>/Product2'
   *  Product: '<S8>/Product3'
   *  Product: '<S8>/Product5'
   *  Product: '<S8>/Product6'
   *  Product: '<S8>/Product9'
   *  SignalConversion generated from: '<S8>/Math Function'
   *  Sum: '<S8>/Add'
   */
  rtb_PowerFactor_0 = ((((((((((((((((((((((((((0.2483 * rtb_DeadZone_i + 0.0088
    * rtb_Saturation_k2) + rtb_Switch_h) + rtb_Integrator_h) +
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_0) + 1.7349E-15 *
    rt_powd_snf(rtb_DeadZone_i, 6.0)) + rtb_DeadZone_c * rtb_DeadZone_i *
    -0.00098788) + rtb_DeadZone_c * rtb_Saturation_k2 * 5.2321E-5) + -3.0722E-8 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_1) + -2.1326E-11 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_2) + 1.417E-14 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3) + rtb_PowerFactor_0 *
    rtb_DeadZone_i * -34.6685) + rtb_PowerFactor_0 * rtb_Saturation_k2 *
    2.9871E-5) + 1.7183E-5 * rtb_Product8_0) + -6.5431E-9 * rtb_Product7_0) +
    rtb_Saturation_g5_tmp * rtb_DeadZone_i * -0.202) + rtb_Saturation_g5_tmp *
    rtb_Saturation_k2 * 0.00013761) + 1.2868E-9 * rtb_Product4_0) +
    rtb_MathFunction5_0 * rtb_DeadZone_i * 202.6574) + rtb_MathFunction5_0 *
    rtb_Saturation_k2 * -0.0863) + rtb_Integrator_o * rtb_DeadZone_i * -0.1108)
    + 1.146 * rtb_DeadZone_c) + -12185.0 * rtb_PowerFactor_0) + -10.876 *
    rtb_Saturation_g5_tmp) + 260290.0 * rtb_MathFunction5_0) + 346.9631 *
                        rtb_Integrator_o) + -1.4028E+6 * rt_powd_snf
                       (rtb_DeadZone_c, 6.0)) + 300.2078;

  /* Sum: '<S19>/Add1' */
  rtb_Switch_h = Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_3;

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_Saturation_k2 = rtb_Saturation - (rtb_vims_idx_3 -
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[3]) * 100.0;

  /* Math: '<S19>/Exp4' incorporates:
   *  Gain: '<S19>/Gain'
   *  Math: '<S19>/Exp'
   *  Math: '<S19>/Exp1'
   *  Product: '<S19>/Divide'
   *  Product: '<S19>/Divide1'
   *  Sum: '<S19>/Add3'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   *
   * About '<S19>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S19>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Switch_h = exp(((0.0 - 1.0 / Torque_Vectoring_2024_2_ConstB.Exp2 *
                       (rtb_Switch_h * rtb_Switch_h)) - rtb_Saturation_k2 *
                      rtb_Saturation_k2 / Torque_Vectoring_2024_2_ConstB.Exp3) *
                     0.5);

  /* Math: '<S8>/Square' incorporates:
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_k2 = rtb_Saturation_nm * rtb_Saturation_nm;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Integrator_o = rt_powd_snf(rtb_Saturation_nm, 3.0);

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_Saturation_nm, 4.0);

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Saturation_g5_tmp = rt_powd_snf(rtb_Saturation_nm, 5.0);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain12'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain2'
   *  Gain: '<S8>/Gain20'
   *  Gain: '<S8>/Gain21'
   *  Gain: '<S8>/Gain22'
   *  Gain: '<S8>/Gain23'
   *  Gain: '<S8>/Gain24'
   *  Gain: '<S8>/Gain25'
   *  Gain: '<S8>/Gain26'
   *  Gain: '<S8>/Gain27'
   *  Gain: '<S8>/Gain3'
   *  Gain: '<S8>/Gain4'
   *  Gain: '<S8>/Gain5'
   *  Math: '<S8>/Math Function2'
   *  Product: '<S8>/Product'
   *  Product: '<S8>/Product10'
   *  Product: '<S8>/Product11'
   *  Product: '<S8>/Product12'
   *  Product: '<S8>/Product13'
   *  Product: '<S8>/Product14'
   *  Product: '<S8>/Product15'
   *  Product: '<S8>/Product2'
   *  Product: '<S8>/Product3'
   *  Product: '<S8>/Product4'
   *  Product: '<S8>/Product5'
   *  Product: '<S8>/Product6'
   *  Product: '<S8>/Product7'
   *  Product: '<S8>/Product8'
   *  Product: '<S8>/Product9'
   *  SignalConversion generated from: '<S8>/Math Function'
   *  Sum: '<S8>/Add'
   */
  rtb_MathFunction5_0 = ((((((((((((((((((((0.2483 * rtb_Saturation_nm + 0.0088 *
    rtb_Saturation_k2) + -1.8682E-5 * rtb_Integrator_o) + 1.8267E-8 *
    rtb_MathFunction5_0) + -8.8652E-12 * rtb_Saturation_g5_tmp) + 1.7349E-15 *
    rt_powd_snf(rtb_Saturation_nm, 6.0)) + 0.0 * rtb_Saturation_nm * -0.00098788)
    + 0.0 * rtb_Saturation_k2 * 5.2321E-5) + 0.0 * rtb_Integrator_o * -3.0722E-8)
    + 0.0 * rtb_MathFunction5_0 * -2.1326E-11) + 0.0 * rtb_Saturation_g5_tmp *
    1.417E-14) + 0.0 * rtb_Saturation_nm * -34.6685) + 0.0 * rtb_Saturation_k2 *
    2.9871E-5) + 0.0 * rtb_Integrator_o * 1.7183E-5) + 0.0 * rtb_MathFunction5_0
    * -6.5431E-9) + 0.0 * rtb_Saturation_nm * -0.202) + 0.0 * rtb_Saturation_k2 *
    0.00013761) + 0.0 * rtb_Integrator_o * 1.2868E-9) + 0.0 * rtb_Saturation_nm *
    202.6574) + 0.0 * rtb_Saturation_k2 * -0.0863) + 0.0 * rtb_Saturation_nm *
    -0.1108) + 300.2078;

  /* Saturate: '<Root>/Saturation3' incorporates:
   *  Inport: '<Root>/throttle'
   */
  if (Torque_Vectoring_2024_2_U.throttle > 1.0F) {
    tmp = 1.0F;
  } else if (Torque_Vectoring_2024_2_U.throttle < 0.0F) {
    tmp = 0.0F;
  } else {
    tmp = Torque_Vectoring_2024_2_U.throttle;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  Gain: '<S7>/Gain1'
   *  Saturate: '<Root>/Saturation3'
   */
  rtb_Integrator_o = 2.0F * tmp * Torque_Vectoring_2024_2_P.T_max;

  /* Sum: '<S1>/Add' incorporates:
   *  Sum: '<S243>/Sum'
   *  Sum: '<S243>/Sum1'
   */
  rtb_Saturation_g5_tmp = rtb_Integrator_m + rtb_Saturation_g;
  rtb_Saturation_k2 = rtb_Saturation_g5_tmp;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Add2'
   *  Sum: '<S1>/Subtract'
   */
  rtb_Saturation_k2 *= (rtb_Saturation_k2 - 667.461609) *
    -0.00049402457842335622 + 2.106129056;

  /* Sum: '<S1>/Add1' */
  rtb_DeadZone_c = rtb_DeadZone_i + rtb_Saturation_nm;

  /* Sum: '<S7>/Add5' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S7>/Constant2'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S7>/Gain4'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Add3'
   *  Sum: '<S1>/Add4'
   *  Sum: '<S1>/Subtract1'
   */
  rtb_Saturation_k2 = rtb_Saturation_k2 / (((rtb_DeadZone_c - 667.461609) *
    -0.00049402457842335622 + 2.106129056) * rtb_DeadZone_c + rtb_Saturation_k2)
    * (1.0 - Torque_Vectoring_2024_2_P.offset_throttle_csi) +
    Torque_Vectoring_2024_2_P.offset_throttle_csi;

  /* Product: '<S243>/Divide' */
  rtb_Integrator_h = rtb_Integrator_m / rtb_Saturation_g5_tmp;

  /* Product: '<S243>/Divide1' incorporates:
   *  Sum: '<S243>/Add2'
   *  Sum: '<S243>/Sum'
   */
  rtb_Saturation_nm *= 1.0 / (((rtb_Saturation_g5_tmp + rtb_DeadZone_i) +
    rtb_Saturation_nm) - rtb_Saturation_g5_tmp);

  /* Sum: '<S243>/Add3' incorporates:
   *  Constant: '<S243>/Constant'
   *  Constant: '<S243>/Constant1'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<S243>/Multiply'
   *  Sum: '<S243>/Add'
   *  Sum: '<S243>/Add1'
   */
  Torque_Vectoring_2024_2_Y.T_pos[0] = (1.0 -
    Torque_Vectoring_2024_2_P.offset_cornering) * rtb_Integrator_h +
    Torque_Vectoring_2024_2_P.offset_cornering;
  Torque_Vectoring_2024_2_Y.T_pos[1] = (1.0 -
    Torque_Vectoring_2024_2_P.offset_cornering) * (1.0 - rtb_Integrator_h) +
    Torque_Vectoring_2024_2_P.offset_cornering;
  Torque_Vectoring_2024_2_Y.T_pos[2] = (1.0 -
    Torque_Vectoring_2024_2_P.offset_cornering) * (1.0 - rtb_Saturation_nm) +
    Torque_Vectoring_2024_2_P.offset_cornering;
  Torque_Vectoring_2024_2_Y.T_pos[3] = (1.0 -
    Torque_Vectoring_2024_2_P.offset_cornering) * rtb_Saturation_nm +
    Torque_Vectoring_2024_2_P.offset_cornering;

  /* Product: '<S7>/Divide' incorporates:
   *  Constant: '<S7>/Constant'
   *  Product: '<S7>/Divide1'
   *  Product: '<S7>/Product'
   *  Sum: '<S7>/Add'
   */
  tmp_2 = _mm_mul_pd(_mm_set1_pd(1.0 / (1.0 - rtb_Saturation_k2) *
    (rtb_Saturation_k2 * rtb_Integrator_o)), _mm_loadu_pd
                     (&Torque_Vectoring_2024_2_Y.T_pos[0]));
  _mm_storeu_pd(&tmp_4[0], tmp_2);

  /* Product: '<S7>/Product' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_0 = tmp_4[0];
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_1 = tmp_4[1];
  tmp_2 = _mm_mul_pd(_mm_set1_pd(rtb_Integrator_o), _mm_loadu_pd
                     (&Torque_Vectoring_2024_2_Y.T_pos[2]));
  _mm_storeu_pd(&tmp_4[0], tmp_2);

  /* Product: '<S7>/Product' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_2 = tmp_4[0];
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = tmp_4[1];

  /* Sum: '<S21>/Sum1' incorporates:
   *  Constant: '<S21>/Desired slip front1'
   *  Constant: '<S21>/Desired slip rear1'
   *  Sum: '<S21>/Sum2'
   */
  tmp_2 = _mm_set_pd(Torque_Vectoring_2024_2_P.TC_CL_TARGET_SLIP_R,
                     Torque_Vectoring_2024_2_P.TC_CL_TARGET_SLIP_F);
  _mm_storeu_pd(&tmp_4[0], _mm_sub_pd(_mm_set_pd
    (Torque_Vectoring_2024_2_Y.lambda[2], Torque_Vectoring_2024_2_Y.lambda[0]),
    tmp_2));

  /* Sum: '<S21>/Sum2' */
  rtb_delta_fldelta_frrad[0] = tmp_4[0];

  /* Sum: '<S21>/Sum1' incorporates:
   *  Sum: '<S21>/Sum2'
   */
  rtb_Sliperror[0] = tmp_4[1];
  _mm_storeu_pd(&tmp_4[0], _mm_sub_pd(_mm_set_pd
    (Torque_Vectoring_2024_2_Y.lambda[3], Torque_Vectoring_2024_2_Y.lambda[1]),
    tmp_2));

  /* Sum: '<S21>/Sum2' */
  rtb_delta_fldelta_frrad[1] = tmp_4[0];

  /* Sum: '<S21>/Sum1' */
  rtb_Sliperror[1] = tmp_4[1];

  /* Sum: '<S126>/Sum' incorporates:
   *  DiscreteIntegrator: '<S117>/Integrator'
   *  Gain: '<S122>/Proportional Gain'
   */
  rtb_Integrator_m = Torque_Vectoring_2024_2_P.TC_CL_P_R *
    rtb_delta_fldelta_frrad[0] + Torque_Vectoring_2024_2_DW.u;

  /* Saturate: '<S124>/Saturation' */
  if (rtb_Integrator_m > 1.0) {
    rtb_Saturation_k2 = 1.0;
  } else if (rtb_Integrator_m < 0.0) {
    rtb_Saturation_k2 = 0.0;
  } else {
    rtb_Saturation_k2 = rtb_Integrator_m;
  }

  /* End of Saturate: '<S124>/Saturation' */

  /* Sum: '<S234>/Sum' incorporates:
   *  DiscreteIntegrator: '<S225>/Integrator'
   *  Gain: '<S230>/Proportional Gain'
   */
  rtb_DeadZone_i = Torque_Vectoring_2024_2_P.TC_CL_P_R *
    rtb_delta_fldelta_frrad[1] + Torque_Vectoring_2024_2_DW.u_m;

  /* Saturate: '<S232>/Saturation' */
  if (rtb_DeadZone_i > 1.0) {
    rtb_Saturation_nm = 1.0;
  } else if (rtb_DeadZone_i < 0.0) {
    rtb_Saturation_nm = 0.0;
  } else {
    rtb_Saturation_nm = rtb_DeadZone_i;
  }

  /* End of Saturate: '<S232>/Saturation' */

  /* Sum: '<S72>/Sum' incorporates:
   *  DiscreteIntegrator: '<S63>/Integrator'
   *  Gain: '<S68>/Proportional Gain'
   */
  rtb_DeadZone_c = Torque_Vectoring_2024_2_P.TC_CL_P_R * rtb_Sliperror[0] +
    Torque_Vectoring_2024_2_DW.u_a;

  /* Saturate: '<S70>/Saturation' */
  if (rtb_DeadZone_c > 1.0) {
    rtb_Saturation_g = 1.0;
  } else if (rtb_DeadZone_c < 0.0) {
    rtb_Saturation_g = 0.0;
  } else {
    rtb_Saturation_g = rtb_DeadZone_c;
  }

  /* End of Saturate: '<S70>/Saturation' */

  /* Sum: '<S180>/Sum' incorporates:
   *  DiscreteIntegrator: '<S171>/Integrator'
   *  Gain: '<S176>/Proportional Gain'
   */
  rtb_Integrator_o = Torque_Vectoring_2024_2_P.TC_CL_P_R * rtb_Sliperror[1] +
    Torque_Vectoring_2024_2_DW.u_g;

  /* Saturate: '<S178>/Saturation' */
  if (rtb_Integrator_o > 1.0) {
    rtb_Integrator_h = 1.0;
  } else if (rtb_Integrator_o < 0.0) {
    rtb_Integrator_h = 0.0;
  } else {
    rtb_Integrator_h = rtb_Integrator_o;
  }

  /* End of Saturate: '<S178>/Saturation' */

  /* MinMax: '<S21>/Min1' incorporates:
   *  Constant: '<S21>/Constant'
   *  Constant: '<S21>/Constant5'
   *  MinMax: '<S21>/Min'
   */
  Torque_Vectoring_2024_2_Y.TC_CUT[0] = fmax(fmin(rtb_Saturation_k2,
    Torque_Vectoring_2024_2_P.TC_MAX_CUT), 0.0);
  Torque_Vectoring_2024_2_Y.TC_CUT[1] = fmax(fmin(rtb_Saturation_nm,
    Torque_Vectoring_2024_2_P.TC_MAX_CUT), 0.0);
  Torque_Vectoring_2024_2_Y.TC_CUT[2] = fmax(fmin(rtb_Saturation_g,
    Torque_Vectoring_2024_2_P.TC_MAX_CUT), 0.0);
  Torque_Vectoring_2024_2_Y.TC_CUT[3] = fmax(fmin(rtb_Integrator_h,
    Torque_Vectoring_2024_2_P.TC_MAX_CUT), 0.0);

  /* Gain: '<Root>/Gain1' */
  rtb_Saturation_g5_tmp = 0.10471975803375244 * rtb_Saturation5_idx_0;
  Torque_Vectoring_2024_2_Y.T_pos[0] = rtb_Saturation_g5_tmp;

  /* Saturate: '<S8>/Saturation1' */
  if (u0_0 > 2500.0) {
    u0_0 = 2500.0;
  } else if (u0_0 < 50.0) {
    u0_0 = 50.0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S8>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Product: '<S8>/Product1'
   *  Saturate: '<S8>/Saturation1'
   *  Sum: '<S6>/Sum'
   */
  rtb_PowerFactor[0] = fmin(fmin(Torque_Vectoring_2024_2_P.T_max, u0_0 *
    rtb_Saturation_e_idx_0 * 0.078947160665366667), (1.0 -
    Torque_Vectoring_2024_2_Y.TC_CUT[0]) *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_0) * rtb_Saturation_g5_tmp;

  /* Gain: '<Root>/Gain1' */
  rtb_Saturation_g5_tmp = 0.10471975803375244 * rtb_Saturation5_idx_1;
  Torque_Vectoring_2024_2_Y.T_pos[1] = rtb_Saturation_g5_tmp;

  /* Saturate: '<S8>/Saturation1' */
  if (u0_1 > 2500.0) {
    u0_1 = 2500.0;
  } else if (u0_1 < 50.0) {
    u0_1 = 50.0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S8>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Product: '<S8>/Product1'
   *  Saturate: '<S8>/Saturation1'
   *  Sum: '<S6>/Sum'
   */
  rtb_PowerFactor[1] = fmin(fmin(Torque_Vectoring_2024_2_P.T_max, u0_1 *
    rtb_Saturation_e_idx_1 * 0.078947160665366667), (1.0 -
    Torque_Vectoring_2024_2_Y.TC_CUT[1]) *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_1) * rtb_Saturation_g5_tmp;

  /* Gain: '<Root>/Gain1' */
  rtb_Saturation_g5_tmp = 0.10471975803375244 * rtb_Saturation5_idx_2;
  Torque_Vectoring_2024_2_Y.T_pos[2] = rtb_Saturation_g5_tmp;

  /* Saturate: '<S8>/Saturation1' */
  if (rtb_PowerFactor_0 > 2500.0) {
    rtb_PowerFactor_0 = 2500.0;
  } else if (rtb_PowerFactor_0 < 50.0) {
    rtb_PowerFactor_0 = 50.0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S8>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Product: '<S8>/Product1'
   *  Saturate: '<S8>/Saturation1'
   *  Sum: '<S6>/Sum'
   */
  rtb_PowerFactor[2] = fmin(fmin(Torque_Vectoring_2024_2_P.T_max,
    rtb_PowerFactor_0 * rtb_Saturation_e_idx_2 * 0.078947160665366667), (1.0 -
    Torque_Vectoring_2024_2_Y.TC_CUT[2]) *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_2) * rtb_Saturation_g5_tmp;

  /* Gain: '<Root>/Gain1' incorporates:
   *  Saturate: '<Root>/Saturation5'
   */
  rtb_Saturation_g5_tmp = 0.10471975803375244 * rtb_Saturation5_0;
  Torque_Vectoring_2024_2_Y.T_pos[3] = rtb_Saturation_g5_tmp;

  /* Saturate: '<S8>/Saturation1' */
  if (rtb_MathFunction5_0 > 2500.0) {
    rtb_MathFunction5_0 = 2500.0;
  } else if (rtb_MathFunction5_0 < 50.0) {
    rtb_MathFunction5_0 = 50.0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S8>/Gain11'
   *  MinMax: '<Root>/Min'
   *  Product: '<Root>/Product1'
   *  Product: '<S8>/Product1'
   *  Saturate: '<S5>/Saturation'
   *  Saturate: '<S8>/Saturation1'
   *  Sum: '<S6>/Sum'
   */
  rtb_PowerFactor[3] = fmin(fmin(Torque_Vectoring_2024_2_P.T_max,
    rtb_MathFunction5_0 * u0 * 0.078947160665366667), (1.0 -
    Torque_Vectoring_2024_2_Y.TC_CUT[3]) *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3) * rtb_Saturation_g5_tmp;

  /* Sum: '<S20>/Add' */
  rtb_Saturation_e_idx_1 = ((rtb_PowerFactor[0] + rtb_PowerFactor[1]) +
    rtb_PowerFactor[2]) + rtb_PowerFactor[3];

  /* MinMax: '<S20>/Max' incorporates:
   *  Constant: '<S20>/Constant'
   */
  rtb_Saturation_e_idx_0 = fmax(rtb_Saturation_e_idx_1, 0.1);

  /* MinMax: '<S20>/Min' incorporates:
   *  Constant: '<S20>/Total Power Limit'
   */
  rtb_Saturation_e_idx_1 = fmin(rtb_Saturation_e_idx_1,
    Torque_Vectoring_2024_2_P.Pmax);

  /* Product: '<S20>/Divide' */
  rtb_PowerFactor_0 = rtb_PowerFactor[0] / rtb_Saturation_e_idx_0;
  rtb_PowerFactor[0] = rtb_PowerFactor_0;

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Gain: '<Root>/Gain1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S20>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_2_Y.T_pos[0] = rtb_Saturation_e_idx_1 *
    rtb_PowerFactor_0 / fmax(Torque_Vectoring_2024_2_Y.T_pos[0], 0.1) * (real_T)
    (Torque_Vectoring_2024_2_Y.T_pos[0] <= 2094.3951023931954);

  /* Product: '<S20>/Divide' */
  rtb_PowerFactor_0 = rtb_PowerFactor[1] / rtb_Saturation_e_idx_0;
  rtb_PowerFactor[1] = rtb_PowerFactor_0;

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Gain: '<Root>/Gain1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S20>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_2_Y.T_pos[1] = rtb_Saturation_e_idx_1 *
    rtb_PowerFactor_0 / fmax(Torque_Vectoring_2024_2_Y.T_pos[1], 0.1) * (real_T)
    (Torque_Vectoring_2024_2_Y.T_pos[1] <= 2094.3951023931954);

  /* Product: '<S20>/Divide' */
  rtb_PowerFactor_0 = rtb_PowerFactor[2] / rtb_Saturation_e_idx_0;
  rtb_PowerFactor[2] = rtb_PowerFactor_0;

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Gain: '<Root>/Gain1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S20>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_2_Y.T_pos[2] = rtb_Saturation_e_idx_1 *
    rtb_PowerFactor_0 / fmax(Torque_Vectoring_2024_2_Y.T_pos[2], 0.1) * (real_T)
    (Torque_Vectoring_2024_2_Y.T_pos[2] <= 2094.3951023931954);

  /* Product: '<S20>/Divide' */
  rtb_PowerFactor_0 = rtb_PowerFactor[3] / rtb_Saturation_e_idx_0;
  rtb_PowerFactor[3] = rtb_PowerFactor_0;

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Gain: '<Root>/Gain1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S20>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_2_Y.T_pos[3] = rtb_Saturation_e_idx_1 *
    rtb_PowerFactor_0 / fmax(Torque_Vectoring_2024_2_Y.T_pos[3], 0.1) * (real_T)
    (Torque_Vectoring_2024_2_Y.T_pos[3] <= 2094.3951023931954);

  /* Product: '<S15>/Product' incorporates:
   *  Concatenate: '<S12>/Vector Concatenate2'
   *  Gain: '<S12>/Gain3'
   *  Memory: '<S3>/Memory2'
   *  Product: '<S15>/Product1'
   */
  tmp_2 = _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set_pd
    (Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0],
     Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[1]), _mm_set_pd(rtb_A_k[1],
    rtb_A_k[2])), _mm_loadu_pd
    (&Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0])), _mm_add_pd
                     (_mm_mul_pd(_mm_set_pd
    (Torque_Vectoring_2024_2_DW.Memory2_PreviousInput[0],
     Torque_Vectoring_2024_2_ConstB.B[0]), _mm_set_pd
    (Torque_Vectoring_2024_2_ConstB.B[1],
     Torque_Vectoring_2024_2_DW.Memory2_PreviousInput[0])), _mm_mul_pd
                      (_mm_set1_pd
                       (Torque_Vectoring_2024_2_DW.Memory2_PreviousInput[1]),
                       _mm_loadu_pd(&Torque_Vectoring_2024_2_ConstB.B[2]))));
  _mm_storeu_pd(&tmp_4[0], tmp_2);

  /* Product: '<S14>/Product1' incorporates:
   *  Abs: '<S13>/Abs'
   *  Constant: '<S12>/Constant4'
   *  Constant: '<S16>/Constant'
   *  Constant: '<S17>/Constant'
   *  Constant: '<S18>/Constant'
   *  Math: '<S19>/Exp4'
   *  MinMax: '<S13>/Max'
   *  MinMax: '<S13>/Min'
   *  Product: '<S12>/Divide'
   *  Product: '<S13>/Divide'
   *  Product: '<S13>/Product'
   *  Product: '<S13>/Product of Elements'
   *  Product: '<S14>/Product'
   *  RelationalOperator: '<S16>/Compare'
   *  RelationalOperator: '<S17>/Compare'
   *  RelationalOperator: '<S18>/Compare'
   *  Sum: '<S13>/Add'
   *  Sum: '<S13>/Sum of Elements'
   *  Sum: '<S13>/Sum of Elements1'
   *  Sum: '<S13>/Sum of Elements2'
   *  Sum: '<S14>/Add'
   *  Sum: '<S19>/Add1'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   */
  tmp_2 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&rtb_K_k[0]), _mm_set1_pd
    ((((((rtb_Product_idx_0 + rtb_Product_idx_1) + rtb_Product_idx_2) +
        rtb_vims_idx_3 * rtb_Switch_h) / (((rtb_Exp4[0] + rtb_Exp4[1]) +
    rtb_Exp4[2]) + rtb_Switch_h) * (real_T)(fabs(rtb_Saturation) <= 1.8) +
       (real_T)(rtb_Saturation >= 1.8) * fmin(fmin(fmin(rtb_vims_idx_0,
    rtb_vims_idx_1), rtb_Gain9), rtb_vims_idx_3)) + (real_T)(rtb_Saturation <
    -1.8) * fmax(fmax(fmax(rtb_vims_idx_0, rtb_vims_idx_1), rtb_Gain9),
                 rtb_vims_idx_3)) - (0.0 * tmp_4[1] + tmp_4[0]))), _mm_set_pd
                     (tmp_4[1], tmp_4[0]));

  /* Sum: '<S14>/Add1' incorporates:
   *  Product: '<S12>/Divide'
   *  Product: '<S14>/Product1'
   */
  _mm_storeu_pd(&rtb_K_k[0], tmp_2);

  /* DeadZone: '<S163>/DeadZone' */
  if (rtb_Integrator_o > 1.0) {
    rtb_Integrator_o--;
  } else if (rtb_Integrator_o >= 0.0) {
    rtb_Integrator_o = 0.0;
  }

  /* End of DeadZone: '<S163>/DeadZone' */

  /* Gain: '<S168>/Integral Gain' */
  rtb_Saturation_g = Torque_Vectoring_2024_2_P.TC_CL_I_R * rtb_Sliperror[1];

  /* Switch: '<S161>/Switch1' incorporates:
   *  Constant: '<S161>/Clamping_zero'
   *  Constant: '<S161>/Constant'
   *  Constant: '<S161>/Constant2'
   *  RelationalOperator: '<S161>/fix for DT propagation issue'
   */
  if (rtb_Integrator_o > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S161>/Switch2' incorporates:
   *  Constant: '<S161>/Clamping_zero'
   *  Constant: '<S161>/Constant3'
   *  Constant: '<S161>/Constant4'
   *  RelationalOperator: '<S161>/fix for DT propagation issue1'
   */
  if (rtb_Saturation_g > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  /* Switch: '<S161>/Switch' incorporates:
   *  Constant: '<S161>/Clamping_zero'
   *  Constant: '<S161>/Constant1'
   *  Logic: '<S161>/AND3'
   *  RelationalOperator: '<S161>/Equal1'
   *  RelationalOperator: '<S161>/Relational Operator'
   *  Switch: '<S161>/Switch1'
   *  Switch: '<S161>/Switch2'
   */
  if ((rtb_Integrator_o != 0.0) && (tmp_0 == tmp_1)) {
    rtb_Saturation_nm = 0.0;
  } else {
    rtb_Saturation_nm = rtb_Saturation_g;
  }

  /* End of Switch: '<S161>/Switch' */

  /* DeadZone: '<S55>/DeadZone' */
  if (rtb_DeadZone_c > 1.0) {
    rtb_DeadZone_c--;
  } else if (rtb_DeadZone_c >= 0.0) {
    rtb_DeadZone_c = 0.0;
  }

  /* End of DeadZone: '<S55>/DeadZone' */

  /* Gain: '<S60>/Integral Gain' */
  rtb_Saturation_g = Torque_Vectoring_2024_2_P.TC_CL_I_R * rtb_Sliperror[0];

  /* Switch: '<S53>/Switch1' incorporates:
   *  Constant: '<S53>/Clamping_zero'
   *  Constant: '<S53>/Constant'
   *  Constant: '<S53>/Constant2'
   *  RelationalOperator: '<S53>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_c > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S53>/Switch2' incorporates:
   *  Constant: '<S53>/Clamping_zero'
   *  Constant: '<S53>/Constant3'
   *  Constant: '<S53>/Constant4'
   *  RelationalOperator: '<S53>/fix for DT propagation issue1'
   */
  if (rtb_Saturation_g > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  /* Switch: '<S53>/Switch' incorporates:
   *  Constant: '<S53>/Clamping_zero'
   *  Constant: '<S53>/Constant1'
   *  Logic: '<S53>/AND3'
   *  RelationalOperator: '<S53>/Equal1'
   *  RelationalOperator: '<S53>/Relational Operator'
   *  Switch: '<S53>/Switch1'
   *  Switch: '<S53>/Switch2'
   */
  if ((rtb_DeadZone_c != 0.0) && (tmp_0 == tmp_1)) {
    rtb_Switch_h = 0.0;
  } else {
    rtb_Switch_h = rtb_Saturation_g;
  }

  /* End of Switch: '<S53>/Switch' */

  /* DeadZone: '<S217>/DeadZone' */
  if (rtb_DeadZone_i > 1.0) {
    rtb_DeadZone_i--;
  } else if (rtb_DeadZone_i >= 0.0) {
    rtb_DeadZone_i = 0.0;
  }

  /* End of DeadZone: '<S217>/DeadZone' */

  /* Gain: '<S222>/Integral Gain' */
  rtb_Saturation_g = Torque_Vectoring_2024_2_P.TC_CL_I_R *
    rtb_delta_fldelta_frrad[1];

  /* Switch: '<S215>/Switch1' incorporates:
   *  Constant: '<S215>/Clamping_zero'
   *  Constant: '<S215>/Constant'
   *  Constant: '<S215>/Constant2'
   *  RelationalOperator: '<S215>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_i > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S215>/Switch2' incorporates:
   *  Constant: '<S215>/Clamping_zero'
   *  Constant: '<S215>/Constant3'
   *  Constant: '<S215>/Constant4'
   *  RelationalOperator: '<S215>/fix for DT propagation issue1'
   */
  if (rtb_Saturation_g > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  /* Switch: '<S215>/Switch' incorporates:
   *  Constant: '<S215>/Clamping_zero'
   *  Constant: '<S215>/Constant1'
   *  Logic: '<S215>/AND3'
   *  RelationalOperator: '<S215>/Equal1'
   *  RelationalOperator: '<S215>/Relational Operator'
   *  Switch: '<S215>/Switch1'
   *  Switch: '<S215>/Switch2'
   */
  if ((rtb_DeadZone_i != 0.0) && (tmp_0 == tmp_1)) {
    rtb_DeadZone_i = 0.0;
  } else {
    rtb_DeadZone_i = rtb_Saturation_g;
  }

  /* End of Switch: '<S215>/Switch' */

  /* DeadZone: '<S109>/DeadZone' */
  if (rtb_Integrator_m > 1.0) {
    rtb_Integrator_m--;
  } else if (rtb_Integrator_m >= 0.0) {
    rtb_Integrator_m = 0.0;
  }

  /* End of DeadZone: '<S109>/DeadZone' */

  /* Gain: '<S114>/Integral Gain' */
  rtb_Saturation_g = Torque_Vectoring_2024_2_P.TC_CL_I_R *
    rtb_delta_fldelta_frrad[0];

  /* Outport: '<Root>/vx_est' incorporates:
   *  Memory: '<Root>/Memory'
   */
  Torque_Vectoring_2024_2_Y.vx_est =
    Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  Torque_Vectoring_2024_2_DW.Memory2_PreviousInput[0] = rtb_Saturation;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  Torque_Vectoring_2024_2_DW.Memory2_PreviousInput[1] = rtb_Saturation1;

  /* Update for Memory: '<Root>/Memory' */
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k = rtb_K_k[0];

  /* Update for Memory: '<S3>/Memory1' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S11>/Constant'
   *  Constant: '<S3>/Constant'
   *  Product: '<S3>/Product'
   *  RelationalOperator: '<S11>/Compare'
   *  Sum: '<S3>/Add'
   */
  Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0] = rtb_vxms;
  Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[1] = (1.0 - (real_T)(fabsf
    (Torque_Vectoring_2024_2_DW.Memory4_PreviousInput) <= 0.0349065848F)) *
    rtb_K_k[1];

  /* Update for Memory: '<S19>/Memory' */
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[0] = rtb_vims_idx_0;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[1] = rtb_vims_idx_1;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[2] = rtb_Gain9;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[3] = rtb_vims_idx_3;

  /* Switch: '<S107>/Switch1' incorporates:
   *  Constant: '<S107>/Clamping_zero'
   *  Constant: '<S107>/Constant'
   *  Constant: '<S107>/Constant2'
   *  RelationalOperator: '<S107>/fix for DT propagation issue'
   */
  if (rtb_Integrator_m > 0.0) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S107>/Switch2' incorporates:
   *  Constant: '<S107>/Clamping_zero'
   *  Constant: '<S107>/Constant3'
   *  Constant: '<S107>/Constant4'
   *  RelationalOperator: '<S107>/fix for DT propagation issue1'
   */
  if (rtb_Saturation_g > 0.0) {
    tmp_1 = 1;
  } else {
    tmp_1 = -1;
  }

  /* Switch: '<S107>/Switch' incorporates:
   *  Constant: '<S107>/Clamping_zero'
   *  Constant: '<S107>/Constant1'
   *  Logic: '<S107>/AND3'
   *  RelationalOperator: '<S107>/Equal1'
   *  RelationalOperator: '<S107>/Relational Operator'
   *  Switch: '<S107>/Switch1'
   *  Switch: '<S107>/Switch2'
   */
  if ((rtb_Integrator_m != 0.0) && (tmp_0 == tmp_1)) {
    rtb_Saturation_g = 0.0;
  }

  /* Update for DiscreteIntegrator: '<S117>/Integrator' incorporates:
   *  Switch: '<S107>/Switch'
   */
  Torque_Vectoring_2024_2_DW.u += 0.005 * rtb_Saturation_g;
  if (Torque_Vectoring_2024_2_DW.u > 1.0) {
    Torque_Vectoring_2024_2_DW.u = 1.0;
  } else if (Torque_Vectoring_2024_2_DW.u < 0.0) {
    Torque_Vectoring_2024_2_DW.u = 0.0;
  }

  /* End of Update for DiscreteIntegrator: '<S117>/Integrator' */

  /* Update for DiscreteIntegrator: '<S225>/Integrator' */
  Torque_Vectoring_2024_2_DW.u_m += 0.005 * rtb_DeadZone_i;
  if (Torque_Vectoring_2024_2_DW.u_m > 1.0) {
    Torque_Vectoring_2024_2_DW.u_m = 1.0;
  } else if (Torque_Vectoring_2024_2_DW.u_m < 0.0) {
    Torque_Vectoring_2024_2_DW.u_m = 0.0;
  }

  /* End of Update for DiscreteIntegrator: '<S225>/Integrator' */

  /* Update for DiscreteIntegrator: '<S63>/Integrator' */
  Torque_Vectoring_2024_2_DW.u_a += 0.005 * rtb_Switch_h;
  if (Torque_Vectoring_2024_2_DW.u_a > 1.0) {
    Torque_Vectoring_2024_2_DW.u_a = 1.0;
  } else if (Torque_Vectoring_2024_2_DW.u_a < 0.0) {
    Torque_Vectoring_2024_2_DW.u_a = 0.0;
  }

  /* End of Update for DiscreteIntegrator: '<S63>/Integrator' */

  /* Update for DiscreteIntegrator: '<S171>/Integrator' */
  Torque_Vectoring_2024_2_DW.u_g += 0.005 * rtb_Saturation_nm;
  if (Torque_Vectoring_2024_2_DW.u_g > 1.0) {
    Torque_Vectoring_2024_2_DW.u_g = 1.0;
  } else if (Torque_Vectoring_2024_2_DW.u_g < 0.0) {
    Torque_Vectoring_2024_2_DW.u_g = 0.0;
  }

  /* End of Update for DiscreteIntegrator: '<S171>/Integrator' */

  /* Matfile logging */
  rt_UpdateTXYLogVars(Torque_Vectoring_2024_2_M->rtwLogInfo,
                      (&Torque_Vectoring_2024_2_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.005s, 0.0s] */
    if ((rtmGetTFinal(Torque_Vectoring_2024_2_M)!=-1) &&
        !((rtmGetTFinal(Torque_Vectoring_2024_2_M)-
           Torque_Vectoring_2024_2_M->Timing.taskTime0) >
          Torque_Vectoring_2024_2_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(Torque_Vectoring_2024_2_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Torque_Vectoring_2024_2_M->Timing.clockTick0)) {
    ++Torque_Vectoring_2024_2_M->Timing.clockTickH0;
  }

  Torque_Vectoring_2024_2_M->Timing.taskTime0 =
    Torque_Vectoring_2024_2_M->Timing.clockTick0 *
    Torque_Vectoring_2024_2_M->Timing.stepSize0 +
    Torque_Vectoring_2024_2_M->Timing.clockTickH0 *
    Torque_Vectoring_2024_2_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Torque_Vectoring_2024_2_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Torque_Vectoring_2024_2_M, 0,
                sizeof(RT_MODEL_Torque_Vectoring_2024_2_T));
  rtmSetTFinal(Torque_Vectoring_2024_2_M, -1);
  Torque_Vectoring_2024_2_M->Timing.stepSize0 = 0.005;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    Torque_Vectoring_2024_2_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Torque_Vectoring_2024_2_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Torque_Vectoring_2024_2_M->rtwLogInfo, (NULL));
    rtliSetLogT(Torque_Vectoring_2024_2_M->rtwLogInfo, "tout");
    rtliSetLogX(Torque_Vectoring_2024_2_M->rtwLogInfo, "");
    rtliSetLogXFinal(Torque_Vectoring_2024_2_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Torque_Vectoring_2024_2_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Torque_Vectoring_2024_2_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Torque_Vectoring_2024_2_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Torque_Vectoring_2024_2_M->rtwLogInfo, 1);
    rtliSetLogY(Torque_Vectoring_2024_2_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Torque_Vectoring_2024_2_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Torque_Vectoring_2024_2_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&Torque_Vectoring_2024_2_DW, 0,
                sizeof(DW_Torque_Vectoring_2024_2_T));

  /* external inputs */
  (void)memset(&Torque_Vectoring_2024_2_U, 0, sizeof
               (ExtU_Torque_Vectoring_2024_2_T));

  /* external outputs */
  (void)memset(&Torque_Vectoring_2024_2_Y, 0, sizeof
               (ExtY_Torque_Vectoring_2024_2_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Torque_Vectoring_2024_2_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Torque_Vectoring_2024_2_M),
    Torque_Vectoring_2024_2_M->Timing.stepSize0, (&rtmGetErrorStatus
    (Torque_Vectoring_2024_2_M)));

  /* InitializeConditions for Saturate: '<Root>/Saturation2' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  Torque_Vectoring_2024_2_DW.Memory4_PreviousInput = 0.0F;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput[0] = 0.0;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput[1] = 0.0;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput[2] = 0.0;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput[3] = 0.0;

  /* InitializeConditions for Memory: '<Root>/Memory' */
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_k = 0.0;

  /* InitializeConditions for Memory: '<S3>/Memory1' */
  Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[0] = 0.0;
  Torque_Vectoring_2024_2_DW.Memory1_PreviousInput[1] = 0.0;

  /* InitializeConditions for Memory: '<S19>/Memory' */
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[0] = 0.0;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[1] = 0.0;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[2] = 0.0;
  Torque_Vectoring_2024_2_DW.Memory_PreviousInput_h[3] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S117>/Integrator' */
  Torque_Vectoring_2024_2_DW.u = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S225>/Integrator' */
  Torque_Vectoring_2024_2_DW.u_m = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S63>/Integrator' */
  Torque_Vectoring_2024_2_DW.u_a = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S171>/Integrator' */
  Torque_Vectoring_2024_2_DW.u_g = 0.0;

  /* InitializeConditions for Memory: '<S3>/Memory2' */
  Torque_Vectoring_2024_2_DW.Memory2_PreviousInput[0] = 1.3;
  Torque_Vectoring_2024_2_DW.Memory2_PreviousInput[1] = 0.0;

  /* ConstCode for Outport: '<Root>/T_neg' incorporates:
   *  Constant: '<Root>/Constant'
   */
  Torque_Vectoring_2024_2_Y.T_neg[0] = 0.0;
  Torque_Vectoring_2024_2_Y.T_neg[1] = 0.0;
  Torque_Vectoring_2024_2_Y.T_neg[2] = 0.0;
  Torque_Vectoring_2024_2_Y.T_neg[3] = 0.0;
}

/* Model terminate function */
void Torque_Vectoring_2024_2_terminate(void)
{
  /* (no terminate code required) */
}
