/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024.c
 *
 * Code generated for Simulink model 'Torque_Vectoring_2024'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Mar 21 11:48:46 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Torque_Vectoring_2024.h"
#include "rtwtypes.h"
#include "Torque_Vectoring_2024_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include <string.h>

/* Block states (default storage) */
DW_Torque_Vectoring_2024_T Torque_Vectoring_2024_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Torque_Vectoring_2024_T Torque_Vectoring_2024_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Torque_Vectoring_2024_T Torque_Vectoring_2024_Y;

/* Real-time model */
static RT_MODEL_Torque_Vectoring_2024_T Torque_Vectoring_2024_M_;
RT_MODEL_Torque_Vectoring_2024_T *const Torque_Vectoring_2024_M =
  &Torque_Vectoring_2024_M_;
real_T Brt_powd_snf(real_T u0, real_T u1)
{
  real_T tmp;
  real_T tmp_0;
  real_T y;
  if (BrtIsNaN(u0) || BrtIsNaN(u1)) {
    y = (BrtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (BrtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (BrtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (BrtInf);
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
      y = (BrtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void Torque_Vectoring_2024_step(void)
{
  real_T rtb_A_k[4];
  real_T rtb_B[4];
  real_T tmp[4];
  real_T rtb_K_k[2];
  real_T rtb_Add2_c_idx_2;
  real_T rtb_B_tmp;
  real_T rtb_DeadZone;
  real_T rtb_DeadZone_c;
  real_T rtb_DeadZone_i;
  real_T rtb_DeadZone_l;
  real_T rtb_Exp2;
  real_T rtb_Exp3;
  real_T rtb_Gain12_o;
  real_T rtb_Gain20_p;
  real_T rtb_Gain21_n;
  real_T rtb_Gain23_b;
  real_T rtb_Gain24_i;
  real_T rtb_Gain25_m;
  real_T rtb_Integrator;
  real_T rtb_Integrator_g;
  real_T rtb_Integrator_h;
  real_T rtb_Integrator_m;
  real_T rtb_MathFunction7_idx_2;
  real_T rtb_Max_a;
  real_T rtb_Product1_kf;
  real_T rtb_Product_idx_0;
  real_T rtb_Product_idx_1;
  real_T rtb_Product_idx_2;
  real_T rtb_Saturation;
  real_T rtb_Saturation1;
  real_T rtb_Saturation_e_idx_0;
  real_T rtb_Saturation_e_idx_1;
  real_T rtb_Saturation_e_idx_2;
  real_T rtb_Sliperror_idx_0;
  real_T rtb_Sliperror_idx_1;
  real_T rtb_Switch_i;
  real_T rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  real_T rtb_vims_idx_0;
  real_T rtb_vims_idx_1;
  real_T rtb_vims_idx_2;
  real_T rtb_vims_idx_3;
  real_T rtb_vxms;
  real_T rtb_z_max_k;
  real_T rtb_z_min_k;
  real_T u0;
  real_T u0_0;
  real_T u0_1;
  real_T u0_2;
  real32_T rtb_Saturation5;
  real32_T tmp_0;
  int16_T Memory_PreviousInput_tmp;
  int16_T i;
  boolean_T rtb_Compare_m;
  boolean_T tmp_1;

  /* SignalConversion generated from: '<S12>/Vector Concatenate' incorporates:
   *  Constant: '<S12>/Constant'
   */
  rtb_A_k[0] = Torque_Vectoring_2024_P.Constant_Value;

  /* Gain: '<S12>/Gain' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[1] = (real_T)Torque_Vectoring_2024_P.Gain_Gain_i *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput;

  /* Gain: '<S12>/Gain1' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[2] = (real_T)Torque_Vectoring_2024_P.Gain1_Gain_d *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput;

  /* SignalConversion generated from: '<S12>/Vector Concatenate1' incorporates:
   *  Constant: '<S12>/Constant'
   */
  rtb_A_k[3] = Torque_Vectoring_2024_P.Constant_Value;

  /* Product: '<S12>/Product2' incorporates:
   *  Concatenate: '<S12>/Vector Concatenate2'
   *  Constant: '<S12>/Constant'
   *  Math: '<S12>/Transpose'
   *  Memory: '<S12>/Memory'
   */
  for (i = 0; i < 2; i++) {
    tmp[i] = 0.0;
    tmp[i] += Torque_Vectoring_2024_DW.Memory_PreviousInput[i] *
      Torque_Vectoring_2024_P.Constant_Value;
    rtb_Max_a = Torque_Vectoring_2024_DW.Memory_PreviousInput[i + 2];
    tmp[i] += rtb_Max_a * rtb_A_k[2];
    tmp[i + 2] = 0.0;
    tmp[i + 2] += Torque_Vectoring_2024_DW.Memory_PreviousInput[i] * rtb_A_k[1];
    tmp[i + 2] += rtb_Max_a * Torque_Vectoring_2024_P.Constant_Value;
  }

  /* Product: '<S12>/Product4' */
  rtb_Max_a = 0.0;
  for (i = 0; i < 2; i++) {
    /* Sum: '<S12>/Add' incorporates:
     *  Concatenate: '<S12>/Vector Concatenate2'
     *  Constant: '<S12>/Constant7'
     *  Gain: '<S12>/Gain3'
     *  Product: '<S12>/Product2'
     */
    rtb_B_tmp = rtb_A_k[i + 2];
    rtb_Integrator_g = (rtb_B_tmp * tmp[1] + rtb_A_k[i] * tmp[0]) +
      Torque_Vectoring_2024_P.Q[i];
    rtb_B[i] = rtb_Integrator_g;

    /* Product: '<S12>/Product4' incorporates:
     *  Constant: '<S12>/Constant4'
     *  Math: '<S12>/Transpose2'
     */
    rtb_Saturation1 = rtb_Integrator_g *
      Torque_Vectoring_2024_P.Constant4_Value[0];

    /* Sum: '<S12>/Add' incorporates:
     *  Concatenate: '<S12>/Vector Concatenate2'
     *  Constant: '<S12>/Constant7'
     *  Gain: '<S12>/Gain3'
     *  Product: '<S12>/Product2'
     */
    rtb_Integrator_g = (rtb_B_tmp * tmp[3] + rtb_A_k[i] * tmp[2]) +
      Torque_Vectoring_2024_P.Q[i + 2];
    rtb_B[i + 2] = rtb_Integrator_g;

    /* Product: '<S12>/Product4' incorporates:
     *  Constant: '<S12>/Constant4'
     *  Math: '<S12>/Transpose2'
     *  Product: '<S12>/Product3'
     */
    rtb_Saturation1 += rtb_Integrator_g *
      Torque_Vectoring_2024_P.Constant4_Value[1];
    rtb_Max_a += Torque_Vectoring_2024_P.Constant4_Value[i] * rtb_Saturation1;
    rtb_K_k[i] = rtb_Saturation1;
  }

  /* Sum: '<S12>/Add2' incorporates:
   *  Constant: '<S12>/Constant5'
   *  Product: '<S12>/Product4'
   */
  rtb_Integrator_g = rtb_Max_a + Torque_Vectoring_2024_P.R1;

  /* Product: '<S12>/Divide' incorporates:
   *  Product: '<S12>/Product3'
   */
  rtb_B_tmp = rtb_K_k[0] / rtb_Integrator_g;
  rtb_Integrator_g = rtb_K_k[1] / rtb_Integrator_g;

  /* Saturate: '<Root>/Saturation2' incorporates:
   *  Inport: '<Root>/yaw_r'
   */
  if (Torque_Vectoring_2024_U.yaw_r >
      Torque_Vectoring_2024_P.Saturation2_UpperSat) {
    /* Saturate: '<Root>/Saturation2' */
    Torque_Vectoring_2024_DW.Memory4_PreviousInput =
      Torque_Vectoring_2024_P.Saturation2_UpperSat;
  } else if (Torque_Vectoring_2024_U.yaw_r <
             Torque_Vectoring_2024_P.Saturation2_LowerSat) {
    /* Saturate: '<Root>/Saturation2' */
    Torque_Vectoring_2024_DW.Memory4_PreviousInput =
      Torque_Vectoring_2024_P.Saturation2_LowerSat;
  } else {
    /* Saturate: '<Root>/Saturation2' */
    Torque_Vectoring_2024_DW.Memory4_PreviousInput =
      Torque_Vectoring_2024_U.yaw_r;
  }

  /* End of Saturate: '<Root>/Saturation2' */

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_U.rpm > Torque_Vectoring_2024_P.Saturation5_UpperSat)
  {
    rtb_Saturation5 = Torque_Vectoring_2024_P.Saturation5_UpperSat;
  } else if (Torque_Vectoring_2024_U.rpm <
             Torque_Vectoring_2024_P.Saturation5_LowerSat) {
    rtb_Saturation5 = Torque_Vectoring_2024_P.Saturation5_LowerSat;
  } else {
    rtb_Saturation5 = Torque_Vectoring_2024_U.rpm;
  }

  /* End of Saturate: '<Root>/Saturation5' */

  /* Gain: '<Root>/reduction' incorporates:
   *  Gain: '<Root>/Gain'
   */
  rtb_DeadZone_c = (real_T)(Torque_Vectoring_2024_P.Gain_Gain_e *
    rtb_Saturation5) * Torque_Vectoring_2024_P.reduction_Gain;

  /* Saturate: '<Root>/Saturation1' incorporates:
   *  Inport: '<Root>/ay'
   */
  rtb_Saturation1 = -2.6 * Torque_Vectoring_2024_P.g;
  rtb_vxms = 2.6 * Torque_Vectoring_2024_P.g;
  if (Torque_Vectoring_2024_U.ay > rtb_vxms) {
    rtb_Saturation1 = rtb_vxms;
  } else if (!(Torque_Vectoring_2024_U.ay < rtb_Saturation1)) {
    rtb_Saturation1 = Torque_Vectoring_2024_U.ay;
  }

  /* End of Saturate: '<Root>/Saturation1' */

  /* Gain: '<S9>/Gain3' incorporates:
   *  Gain: '<S9>/Gain4'
   */
  rtb_DeadZone_l = Torque_Vectoring_2024_P.kr_f1 + Torque_Vectoring_2024_P.kr_r1;
  rtb_vims_idx_0 = Torque_Vectoring_2024_P.zCoG -
    ((Torque_Vectoring_2024_P.zRC_r1 - Torque_Vectoring_2024_P.zRC_f1) *
     Torque_Vectoring_2024_P.a / Torque_Vectoring_2024_P.w +
     Torque_Vectoring_2024_P.zRC_f1);
  rtb_z_min_k = (Torque_Vectoring_2024_P.kr_f1 / rtb_DeadZone_l * rtb_vims_idx_0
                 + Torque_Vectoring_2024_P.b * Torque_Vectoring_2024_P.zRC_f1 /
                 Torque_Vectoring_2024_P.w) * Torque_Vectoring_2024_P.m /
    Torque_Vectoring_2024_P.t_f * rtb_Saturation1;

  /* Saturate: '<Root>/Saturation' incorporates:
   *  Inport: '<Root>/ax'
   */
  rtb_Saturation = -2.1 * Torque_Vectoring_2024_P.g;
  rtb_vxms = 1.8 * Torque_Vectoring_2024_P.g;
  if (Torque_Vectoring_2024_U.ax > rtb_vxms) {
    rtb_Saturation = rtb_vxms;
  } else if (!(Torque_Vectoring_2024_U.ax < rtb_Saturation)) {
    rtb_Saturation = Torque_Vectoring_2024_U.ax;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Gain: '<S9>/Gain2' */
  rtb_Integrator_m = Torque_Vectoring_2024_P.m * Torque_Vectoring_2024_P.zCoG /
    (2.0 * Torque_Vectoring_2024_P.w) * rtb_Saturation;

  /* Memory: '<Root>/Memory' */
  rtb_vxms = Torque_Vectoring_2024_DW.Memory_PreviousInput_k;

  /* Gain: '<S9>/Fl' incorporates:
   *  Math: '<S9>/Square'
   *  Memory: '<Root>/Memory'
   */
  rtb_DeadZone_i = Torque_Vectoring_2024_P.rho_air * Torque_Vectoring_2024_P.CLA1
    / 2.0 * (Torque_Vectoring_2024_DW.Memory_PreviousInput_k *
             Torque_Vectoring_2024_DW.Memory_PreviousInput_k);

  /* Gain: '<S9>/Gain1' */
  rtb_z_max_k = 0.5 * Torque_Vectoring_2024_P.b_a / Torque_Vectoring_2024_P.w *
    rtb_DeadZone_i;

  /* Sum: '<S9>/Add' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  Sum: '<S9>/Add1'
   *  Sum: '<S9>/Add2'
   */
  rtb_vims_idx_1 = Torque_Vectoring_2024_P.m * Torque_Vectoring_2024_P.g;
  rtb_vims_idx_2 = rtb_vims_idx_1 * Torque_Vectoring_2024_P.b / (2.0 *
    Torque_Vectoring_2024_P.w);
  rtb_Integrator = ((rtb_vims_idx_2 - rtb_z_min_k) - rtb_Integrator_m) +
    rtb_z_max_k;

  /* Sum: '<S9>/Add1' */
  rtb_z_min_k = ((rtb_vims_idx_2 + rtb_z_min_k) - rtb_Integrator_m) +
    rtb_z_max_k;

  /* Gain: '<S9>/Gain4' */
  rtb_z_max_k = (Torque_Vectoring_2024_P.kr_r1 / rtb_DeadZone_l * rtb_vims_idx_0
                 + Torque_Vectoring_2024_P.a * Torque_Vectoring_2024_P.zRC_r1 /
                 Torque_Vectoring_2024_P.w) * Torque_Vectoring_2024_P.m /
    Torque_Vectoring_2024_P.t_r * rtb_Saturation1;

  /* Gain: '<S9>/Gain' */
  rtb_DeadZone_i *= 0.5 * Torque_Vectoring_2024_P.a_a /
    Torque_Vectoring_2024_P.w;

  /* Sum: '<S9>/Add2' incorporates:
   *  Constant: '<S9>/Constant1'
   *  Sum: '<S9>/Add3'
   */
  rtb_vims_idx_0 = rtb_vims_idx_1 * Torque_Vectoring_2024_P.a / (2.0 *
    Torque_Vectoring_2024_P.w);
  rtb_DeadZone_l = ((rtb_vims_idx_0 - rtb_z_max_k) + rtb_Integrator_m) +
    rtb_DeadZone_i;

  /* Sum: '<S9>/Add3' */
  rtb_z_max_k = ((rtb_vims_idx_0 + rtb_z_max_k) + rtb_Integrator_m) +
    rtb_DeadZone_i;

  /* SignalConversion generated from: '<S8>/Math Function' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_z_max_k;

  /* Saturate: '<S5>/Saturation' */
  rtb_Max_a = 0.95 * Torque_Vectoring_2024_P.R01;

  /* Saturate: '<Root>/Saturation6' incorporates:
   *  Inport: '<Root>/steering'
   */
  if (Torque_Vectoring_2024_U.steering >
      Torque_Vectoring_2024_P.Saturation6_UpperSat) {
    tmp_0 = Torque_Vectoring_2024_P.Saturation6_UpperSat;
  } else if (Torque_Vectoring_2024_U.steering <
             Torque_Vectoring_2024_P.Saturation6_LowerSat) {
    tmp_0 = Torque_Vectoring_2024_P.Saturation6_LowerSat;
  } else {
    tmp_0 = Torque_Vectoring_2024_U.steering;
  }

  /* Gain: '<S2>/Gain3' incorporates:
   *  Saturate: '<Root>/Saturation6'
   */
  rtb_DeadZone_i = (real_T)Torque_Vectoring_2024_P.Gain3_Gain_a * tmp_0;

  /* Math: '<S2>/Square2' incorporates:
   *  Math: '<S2>/Square1'
   */
  rtb_vims_idx_0 = rtb_DeadZone_i * rtb_DeadZone_i;

  /* SignalConversion generated from: '<S13>/Cos' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Constant: '<S10>/Constant4'
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant4'
   *  Constant: '<S2>/Constant5'
   *  Constant: '<S2>/Constant6'
   *  Constant: '<S2>/Constant7'
   *  Constant: '<S2>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S2>/Gain'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S2>/Gain10'
   *  Gain: '<S2>/Gain11'
   *  Gain: '<S2>/Gain2'
   *  Gain: '<S2>/Gain4'
   *  Gain: '<S2>/Gain5'
   *  Gain: '<S2>/Gain6'
   *  Gain: '<S2>/Gain7'
   *  Gain: '<S2>/Gain8'
   *  Gain: '<S2>/Gain9'
   *  Math: '<S2>/Math Function1'
   *  Math: '<S2>/Math Function2'
   *  Math: '<S2>/Math Function3'
   *  Math: '<S2>/Math Function4'
   *  Math: '<S2>/Math Function5'
   *  Math: '<S2>/Math Function7'
   *  Math: '<S2>/Square2'
   *  Sum: '<S10>/Add'
   *  Sum: '<S10>/Add1'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S2>/Sum2'
   */
  Torque_Vectoring_2024_Y.TC_CUT[0] = (((((Torque_Vectoring_2024_P.p_fl[0] *
    rt_powd_snf(rtb_DeadZone_i, Torque_Vectoring_2024_P.Constant3_Value) +
    Torque_Vectoring_2024_P.p_fl[1] * rt_powd_snf(rtb_DeadZone_i,
    Torque_Vectoring_2024_P.Constant1_Value_k)) + Torque_Vectoring_2024_P.p_fl[2]
    * rt_powd_snf(rtb_DeadZone_i, Torque_Vectoring_2024_P.Constant2_Value)) +
    rtb_vims_idx_0 * Torque_Vectoring_2024_P.p_fl[3]) +
    Torque_Vectoring_2024_P.p_fl[4] * rtb_DeadZone_i) +
    Torque_Vectoring_2024_P.p_fl[5]) * Torque_Vectoring_2024_P.Gain_Gain -
    Torque_Vectoring_2024_P.toe_f;
  Torque_Vectoring_2024_Y.TC_CUT[1] = (((((Torque_Vectoring_2024_P.p_fr[4] *
    rtb_DeadZone_i + Torque_Vectoring_2024_P.p_fr[5]) + rtb_vims_idx_0 *
    Torque_Vectoring_2024_P.p_fr[3]) + Torque_Vectoring_2024_P.p_fr[2] *
    rt_powd_snf(rtb_DeadZone_i, Torque_Vectoring_2024_P.Constant4_Value_l)) +
    Torque_Vectoring_2024_P.p_fr[1] * rt_powd_snf(rtb_DeadZone_i,
    Torque_Vectoring_2024_P.Constant5_Value)) + Torque_Vectoring_2024_P.p_fr[0] *
    rt_powd_snf(rtb_DeadZone_i, Torque_Vectoring_2024_P.Constant6_Value_f)) *
    Torque_Vectoring_2024_P.Gain_Gain + Torque_Vectoring_2024_P.toe_f;
  Torque_Vectoring_2024_Y.TC_CUT[2] = Torque_Vectoring_2024_P.Gain_Gain_j *
    Torque_Vectoring_2024_P.toe_r;
  Torque_Vectoring_2024_Y.TC_CUT[3] = Torque_Vectoring_2024_P.toe_r;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = Torque_Vectoring_2024_P.k_Re1 * rtb_Integrator +
    Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > Torque_Vectoring_2024_P.R01) {
    u0 = Torque_Vectoring_2024_P.R01;
  } else if (u0 < rtb_Max_a) {
    u0 = rtb_Max_a;
  }

  /* Product: '<Root>/Product' */
  Torque_Vectoring_2024_Y.wR[0] = u0 * rtb_DeadZone_c;

  /* Saturate: '<S5>/Saturation' */
  rtb_Saturation_e_idx_0 = u0;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = Torque_Vectoring_2024_P.k_Re1 * rtb_z_min_k + Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > Torque_Vectoring_2024_P.R01) {
    u0 = Torque_Vectoring_2024_P.R01;
  } else if (u0 < rtb_Max_a) {
    u0 = rtb_Max_a;
  }

  /* Product: '<Root>/Product' */
  Torque_Vectoring_2024_Y.wR[1] = u0 * rtb_DeadZone_c;

  /* Saturate: '<S5>/Saturation' */
  rtb_Saturation_e_idx_1 = u0;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = Torque_Vectoring_2024_P.k_Re1 * rtb_DeadZone_l +
    Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > Torque_Vectoring_2024_P.R01) {
    u0 = Torque_Vectoring_2024_P.R01;
  } else if (u0 < rtb_Max_a) {
    u0 = rtb_Max_a;
  }

  /* Product: '<Root>/Product' */
  Torque_Vectoring_2024_Y.wR[2] = u0 * rtb_DeadZone_c;

  /* Saturate: '<S5>/Saturation' */
  rtb_Saturation_e_idx_2 = u0;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  u0 = Torque_Vectoring_2024_P.k_Re1 * rtb_z_max_k + Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (u0 > Torque_Vectoring_2024_P.R01) {
    u0 = Torque_Vectoring_2024_P.R01;
  } else if (u0 < rtb_Max_a) {
    u0 = rtb_Max_a;
  }

  /* Product: '<Root>/Product' */
  Torque_Vectoring_2024_Y.wR[3] = u0 * rtb_DeadZone_c;

  /* Sum: '<S13>/Add' incorporates:
   *  Gain: '<S13>/Multiply'
   *  Gain: '<S13>/Multiply1'
   *  Gain: '<S13>/Multiply2'
   *  Gain: '<S13>/Multiply3'
   *  Product: '<S13>/Product1'
   *  Trigonometry: '<S13>/Cos'
   */
  rtb_vims_idx_0 = (real_T)Torque_Vectoring_2024_P.Multiply_Gain *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput + cos
    (Torque_Vectoring_2024_Y.TC_CUT[0]) * Torque_Vectoring_2024_Y.wR[0];
  rtb_vims_idx_1 = (real_T)Torque_Vectoring_2024_P.Multiply1_Gain *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput + cos
    (Torque_Vectoring_2024_Y.TC_CUT[1]) * Torque_Vectoring_2024_Y.wR[1];
  rtb_vims_idx_2 = (real_T)Torque_Vectoring_2024_P.Multiply2_Gain *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput + cos
    (Torque_Vectoring_2024_Y.TC_CUT[2]) * Torque_Vectoring_2024_Y.wR[2];
  rtb_vims_idx_3 = (real_T)Torque_Vectoring_2024_P.Multiply3_Gain *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput + cos
    (Torque_Vectoring_2024_Y.TC_CUT[3]) * Torque_Vectoring_2024_Y.wR[3];

  /* Math: '<S19>/Exp3' incorporates:
   *  Constant: '<S19>/Constant3'
   *
   * About '<S19>/Exp3':
   *  Operator: magnitude^2
   */
  rtb_Exp3 = Torque_Vectoring_2024_P.sigma_w1 * Torque_Vectoring_2024_P.sigma_w1;

  /* Math: '<S19>/Exp2' incorporates:
   *  Constant: '<S19>/Constant1'
   *
   * About '<S19>/Exp2':
   *  Operator: magnitude^2
   */
  rtb_Exp2 = Torque_Vectoring_2024_P.sigma_w2 * Torque_Vectoring_2024_P.sigma_w2;

  /* Gain: '<S8>/Gain11' */
  rtb_Max_a = 1.0 / Torque_Vectoring_2024_P.tau;

  /* Saturate: '<Root>/Saturation3' incorporates:
   *  Inport: '<Root>/throttle'
   */
  if (Torque_Vectoring_2024_U.throttle >
      Torque_Vectoring_2024_P.Saturation3_UpperSat) {
    tmp_0 = Torque_Vectoring_2024_P.Saturation3_UpperSat;
  } else if (Torque_Vectoring_2024_U.throttle <
             Torque_Vectoring_2024_P.Saturation3_LowerSat) {
    tmp_0 = Torque_Vectoring_2024_P.Saturation3_LowerSat;
  } else {
    tmp_0 = Torque_Vectoring_2024_U.throttle;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  Saturate: '<Root>/Saturation3'
   */
  rtb_DeadZone_i = (real_T)Torque_Vectoring_2024_P.Gain_Gain_b * tmp_0;

  /* Sum: '<S1>/Add' incorporates:
   *  Sum: '<S227>/Sum'
   *  Sum: '<S227>/Sum1'
   */
  rtb_Product_idx_0 = rtb_Integrator + rtb_z_min_k;

  /* Gain: '<S1>/Gain' incorporates:
   *  Gain: '<S1>/Gain1'
   */
  rtb_Product_idx_1 = Torque_Vectoring_2024_P.PDX2 / Torque_Vectoring_2024_P.FZ0;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Add'
   *  Sum: '<S1>/Add2'
   *  Sum: '<S1>/Subtract'
   */
  rtb_Integrator_m = ((rtb_Product_idx_0 - Torque_Vectoring_2024_P.FZ0) *
                      rtb_Product_idx_1 + Torque_Vectoring_2024_P.PDX1) *
    rtb_Product_idx_0;

  /* Sum: '<S1>/Add1' */
  rtb_DeadZone_c = rtb_DeadZone_l + rtb_z_max_k;

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
  rtb_Integrator_m = rtb_Integrator_m / (((rtb_DeadZone_c -
    Torque_Vectoring_2024_P.FZ0) * rtb_Product_idx_1 +
    Torque_Vectoring_2024_P.PDX1) * rtb_DeadZone_c + rtb_Integrator_m) * (1.0 -
    Torque_Vectoring_2024_P.offset_throttle_csi) +
    Torque_Vectoring_2024_P.offset_throttle_csi;

  /* Product: '<S7>/Divide' incorporates:
   *  Constant: '<S7>/Constant'
   *  Product: '<S7>/Divide1'
   *  Sum: '<S7>/Add'
   */
  rtb_Integrator_m = 1.0 / (Torque_Vectoring_2024_P.Constant_Value_n -
    rtb_Integrator_m) * (rtb_Integrator_m * rtb_DeadZone_i);

  /* Product: '<S227>/Divide' */
  rtb_Integrator_h = rtb_Integrator / rtb_Product_idx_0;

  /* Product: '<S227>/Divide1' incorporates:
   *  Sum: '<S227>/Add2'
   *  Sum: '<S227>/Sum'
   */
  rtb_z_max_k *= 1.0 / (((rtb_Product_idx_0 + rtb_DeadZone_l) + rtb_z_max_k) -
                        rtb_Product_idx_0);

  /* Sum: '<S19>/Add1' */
  rtb_Switch_i = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_0;

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_DeadZone_c = rtb_Saturation - (rtb_vims_idx_0 -
    Torque_Vectoring_2024_DW.Memory_PreviousInput_h[0]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

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
  rtb_Switch_i = exp(((0.0 - 1.0 / rtb_Exp2 * (rtb_Switch_i * rtb_Switch_i)) -
                      rtb_DeadZone_c * rtb_DeadZone_c / rtb_Exp3) *
                     Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Product: '<S13>/Product' incorporates:
   *  Sum: '<S19>/Add1'
   */
  rtb_Product_idx_0 = rtb_vims_idx_0 * rtb_Switch_i;

  /* Saturate: '<S8>/Saturation' */
  if (Torque_Vectoring_2024_Y.TC_CUT[0] >
      Torque_Vectoring_2024_P.Saturation_UpperSat) {
    Torque_Vectoring_2024_Y.TC_CUT[0] =
      Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (Torque_Vectoring_2024_Y.TC_CUT[0] <
             Torque_Vectoring_2024_P.Saturation_LowerSat) {
    Torque_Vectoring_2024_Y.TC_CUT[0] =
      Torque_Vectoring_2024_P.Saturation_LowerSat;
  }

  /* Math: '<S8>/Square' incorporates:
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  Torque_Vectoring_2024_Y.lambda[0] = rtb_Integrator * rtb_Integrator;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_DeadZone_c = rt_powd_snf(rtb_Integrator,
    Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S8>/Gain2' */
  rtb_Sliperror_idx_0 = Torque_Vectoring_2024_P.mu_03 * rtb_DeadZone_c;

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf(rtb_Integrator,
    Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S8>/Gain3' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_04 * rtb_Sliperror_idx_1;

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Product1_kf = rt_powd_snf(rtb_Integrator,
    Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S8>/Gain4' */
  rtb_MathFunction7_idx_2 = Torque_Vectoring_2024_P.mu_05 * rtb_Product1_kf;

  /* Gain: '<S8>/Gain23' incorporates:
   *  Product: '<S8>/Product13'
   */
  rtb_Gain23_b = Torque_Vectoring_2024_Y.TC_CUT[0] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_13;

  /* Gain: '<S8>/Gain24' incorporates:
   *  Product: '<S8>/Product12'
   */
  rtb_Gain24_i = Torque_Vectoring_2024_Y.TC_CUT[0] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_14;

  /* Gain: '<S8>/Gain25' incorporates:
   *  Product: '<S8>/Product11'
   */
  rtb_Gain25_m = Torque_Vectoring_2024_Y.TC_CUT[0] * rtb_Product1_kf *
    Torque_Vectoring_2024_P.mu_15;

  /* Math: '<S8>/Square1' incorporates:
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = Torque_Vectoring_2024_Y.TC_CUT[0] *
    Torque_Vectoring_2024_Y.TC_CUT[0];

  /* Gain: '<S8>/Gain21' incorporates:
   *  Product: '<S8>/Product8'
   */
  rtb_Gain21_n = Torque_Vectoring_2024_Y.T_pos[0] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_23;

  /* Gain: '<S8>/Gain20' incorporates:
   *  Product: '<S8>/Product7'
   */
  rtb_Gain20_p = Torque_Vectoring_2024_Y.T_pos[0] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_24;

  /* Math: '<S8>/Math Function4' incorporates:
   *  Constant: '<S8>/Constant4'
   */
  rtb_Product1_kf = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[0],
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Gain: '<S8>/Gain12' incorporates:
   *  Product: '<S8>/Product4'
   */
  rtb_Gain12_o = rtb_Product1_kf * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_33;

  /* Math: '<S8>/Math Function5' incorporates:
   *  Constant: '<S8>/Constant5'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[0],
    Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S8>/Math Function7' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_DeadZone_c = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[0],
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Constant: '<S8>/Constant8'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain22'
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
  u0_0 = ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 *
    rtb_Integrator + Torque_Vectoring_2024_P.mu_02 *
    Torque_Vectoring_2024_Y.lambda[0]) + rtb_Sliperror_idx_0) + rtb_DeadZone) +
    rtb_MathFunction7_idx_2) + Torque_Vectoring_2024_P.mu_06 * rt_powd_snf
    (rtb_Integrator, Torque_Vectoring_2024_P.Constant3_Value_o)) +
    Torque_Vectoring_2024_Y.TC_CUT[0] * rtb_Integrator *
    Torque_Vectoring_2024_P.mu_11) + Torque_Vectoring_2024_Y.TC_CUT[0] *
    Torque_Vectoring_2024_Y.lambda[0] * Torque_Vectoring_2024_P.mu_12) +
    rtb_Gain23_b) + rtb_Gain24_i) + rtb_Gain25_m) +
    Torque_Vectoring_2024_Y.T_pos[0] * rtb_Integrator *
    Torque_Vectoring_2024_P.mu_21) + Torque_Vectoring_2024_Y.T_pos[0] *
                        Torque_Vectoring_2024_Y.lambda[0] *
                        Torque_Vectoring_2024_P.mu_22) + rtb_Gain21_n) +
                      rtb_Gain20_p) + rtb_Product1_kf * rtb_Integrator *
                     Torque_Vectoring_2024_P.mu_31) + rtb_Product1_kf *
                    Torque_Vectoring_2024_Y.lambda[0] *
                    Torque_Vectoring_2024_P.mu_32) + rtb_Gain12_o) +
                  rtb_Sliperror_idx_1 * rtb_Integrator *
                  Torque_Vectoring_2024_P.mu_41) + rtb_Sliperror_idx_1 *
                 Torque_Vectoring_2024_Y.lambda[0] *
                 Torque_Vectoring_2024_P.mu_42) + rtb_DeadZone_c *
                rtb_Integrator * Torque_Vectoring_2024_P.mu_51) +
               Torque_Vectoring_2024_P.mu_10 * Torque_Vectoring_2024_Y.TC_CUT[0])
              + Torque_Vectoring_2024_P.mu_20 * Torque_Vectoring_2024_Y.T_pos[0])
             + Torque_Vectoring_2024_P.mu_30 * rtb_Product1_kf) +
            Torque_Vectoring_2024_P.mu_40 * rtb_Sliperror_idx_1) +
           Torque_Vectoring_2024_P.mu_50 * rtb_DeadZone_c) +
          Torque_Vectoring_2024_P.mu_60 * rt_powd_snf
          (Torque_Vectoring_2024_Y.TC_CUT[0],
           Torque_Vectoring_2024_P.Constant8_Value)) +
    Torque_Vectoring_2024_P.mu_00;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  rtb_Compare_m = rtIsNaN(Torque_Vectoring_2024_P.Constant6_Value_g);
  if ((Torque_Vectoring_2024_Y.wR[0] >=
       Torque_Vectoring_2024_P.Constant6_Value_g) || rtb_Compare_m) {
    Torque_Vectoring_2024_Y.lambda[0] = Torque_Vectoring_2024_Y.wR[0];
  } else {
    Torque_Vectoring_2024_Y.lambda[0] =
      Torque_Vectoring_2024_P.Constant6_Value_g;
  }

  /* Math: '<S19>/Exp4'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   */
  rtb_Integrator = rtb_Switch_i;

  /* Sum: '<S19>/Add1' */
  rtb_Switch_i = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_1;

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_DeadZone_c = rtb_Saturation - (rtb_vims_idx_1 -
    Torque_Vectoring_2024_DW.Memory_PreviousInput_h[1]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

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
  rtb_Switch_i = exp(((0.0 - 1.0 / rtb_Exp2 * (rtb_Switch_i * rtb_Switch_i)) -
                      rtb_DeadZone_c * rtb_DeadZone_c / rtb_Exp3) *
                     Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Product: '<S13>/Product' incorporates:
   *  Sum: '<S19>/Add1'
   */
  rtb_Product_idx_1 = rtb_vims_idx_1 * rtb_Switch_i;

  /* Saturate: '<S8>/Saturation' */
  if (Torque_Vectoring_2024_Y.TC_CUT[1] >
      Torque_Vectoring_2024_P.Saturation_UpperSat) {
    Torque_Vectoring_2024_Y.TC_CUT[1] =
      Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (Torque_Vectoring_2024_Y.TC_CUT[1] <
             Torque_Vectoring_2024_P.Saturation_LowerSat) {
    Torque_Vectoring_2024_Y.TC_CUT[1] =
      Torque_Vectoring_2024_P.Saturation_LowerSat;
  }

  /* Math: '<S8>/Square' incorporates:
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  Torque_Vectoring_2024_Y.lambda[1] = rtb_z_min_k * rtb_z_min_k;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_DeadZone_c = rt_powd_snf(rtb_z_min_k,
    Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S8>/Gain2' */
  rtb_Sliperror_idx_0 = Torque_Vectoring_2024_P.mu_03 * rtb_DeadZone_c;

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf(rtb_z_min_k,
    Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S8>/Gain3' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_04 * rtb_Sliperror_idx_1;

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Product1_kf = rt_powd_snf(rtb_z_min_k,
    Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S8>/Gain4' */
  rtb_MathFunction7_idx_2 = Torque_Vectoring_2024_P.mu_05 * rtb_Product1_kf;

  /* Gain: '<S8>/Gain23' incorporates:
   *  Product: '<S8>/Product13'
   */
  rtb_Gain23_b = Torque_Vectoring_2024_Y.TC_CUT[1] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_13;

  /* Gain: '<S8>/Gain24' incorporates:
   *  Product: '<S8>/Product12'
   */
  rtb_Gain24_i = Torque_Vectoring_2024_Y.TC_CUT[1] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_14;

  /* Gain: '<S8>/Gain25' incorporates:
   *  Product: '<S8>/Product11'
   */
  rtb_Gain25_m = Torque_Vectoring_2024_Y.TC_CUT[1] * rtb_Product1_kf *
    Torque_Vectoring_2024_P.mu_15;

  /* Math: '<S8>/Square1' incorporates:
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[1] = Torque_Vectoring_2024_Y.TC_CUT[1] *
    Torque_Vectoring_2024_Y.TC_CUT[1];

  /* Gain: '<S8>/Gain21' incorporates:
   *  Product: '<S8>/Product8'
   */
  rtb_Gain21_n = Torque_Vectoring_2024_Y.T_pos[1] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_23;

  /* Gain: '<S8>/Gain20' incorporates:
   *  Product: '<S8>/Product7'
   */
  rtb_Gain20_p = Torque_Vectoring_2024_Y.T_pos[1] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_24;

  /* Math: '<S8>/Math Function4' incorporates:
   *  Constant: '<S8>/Constant4'
   */
  rtb_Product1_kf = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[1],
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Gain: '<S8>/Gain12' incorporates:
   *  Product: '<S8>/Product4'
   */
  rtb_Gain12_o = rtb_Product1_kf * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_33;

  /* Math: '<S8>/Math Function5' incorporates:
   *  Constant: '<S8>/Constant5'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[1],
    Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S8>/Math Function7' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_DeadZone_c = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[1],
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Constant: '<S8>/Constant8'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain22'
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
  u0_1 = ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 * rtb_z_min_k +
    Torque_Vectoring_2024_P.mu_02 * Torque_Vectoring_2024_Y.lambda[1]) +
    rtb_Sliperror_idx_0) + rtb_DeadZone) + rtb_MathFunction7_idx_2) +
    Torque_Vectoring_2024_P.mu_06 * rt_powd_snf(rtb_z_min_k,
    Torque_Vectoring_2024_P.Constant3_Value_o)) +
    Torque_Vectoring_2024_Y.TC_CUT[1] * rtb_z_min_k *
    Torque_Vectoring_2024_P.mu_11) + Torque_Vectoring_2024_Y.TC_CUT[1] *
    Torque_Vectoring_2024_Y.lambda[1] * Torque_Vectoring_2024_P.mu_12) +
    rtb_Gain23_b) + rtb_Gain24_i) + rtb_Gain25_m) +
    Torque_Vectoring_2024_Y.T_pos[1] * rtb_z_min_k *
    Torque_Vectoring_2024_P.mu_21) + Torque_Vectoring_2024_Y.T_pos[1] *
                        Torque_Vectoring_2024_Y.lambda[1] *
                        Torque_Vectoring_2024_P.mu_22) + rtb_Gain21_n) +
                      rtb_Gain20_p) + rtb_Product1_kf * rtb_z_min_k *
                     Torque_Vectoring_2024_P.mu_31) + rtb_Product1_kf *
                    Torque_Vectoring_2024_Y.lambda[1] *
                    Torque_Vectoring_2024_P.mu_32) + rtb_Gain12_o) +
                  rtb_Sliperror_idx_1 * rtb_z_min_k *
                  Torque_Vectoring_2024_P.mu_41) + rtb_Sliperror_idx_1 *
                 Torque_Vectoring_2024_Y.lambda[1] *
                 Torque_Vectoring_2024_P.mu_42) + rtb_DeadZone_c * rtb_z_min_k *
                Torque_Vectoring_2024_P.mu_51) + Torque_Vectoring_2024_P.mu_10 *
               Torque_Vectoring_2024_Y.TC_CUT[1]) +
              Torque_Vectoring_2024_P.mu_20 * Torque_Vectoring_2024_Y.T_pos[1])
             + Torque_Vectoring_2024_P.mu_30 * rtb_Product1_kf) +
            Torque_Vectoring_2024_P.mu_40 * rtb_Sliperror_idx_1) +
           Torque_Vectoring_2024_P.mu_50 * rtb_DeadZone_c) +
          Torque_Vectoring_2024_P.mu_60 * rt_powd_snf
          (Torque_Vectoring_2024_Y.TC_CUT[1],
           Torque_Vectoring_2024_P.Constant8_Value)) +
    Torque_Vectoring_2024_P.mu_00;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  if ((Torque_Vectoring_2024_Y.wR[1] >=
       Torque_Vectoring_2024_P.Constant6_Value_g) || rtb_Compare_m) {
    Torque_Vectoring_2024_Y.lambda[1] = Torque_Vectoring_2024_Y.wR[1];
  } else {
    Torque_Vectoring_2024_Y.lambda[1] =
      Torque_Vectoring_2024_P.Constant6_Value_g;
  }

  /* Math: '<S19>/Exp4'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   */
  rtb_z_min_k = rtb_Switch_i;

  /* Sum: '<S19>/Add1' */
  rtb_Switch_i = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_2;

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_DeadZone_c = rtb_Saturation - (rtb_vims_idx_2 -
    Torque_Vectoring_2024_DW.Memory_PreviousInput_h[2]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

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
  rtb_Switch_i = exp(((0.0 - 1.0 / rtb_Exp2 * (rtb_Switch_i * rtb_Switch_i)) -
                      rtb_DeadZone_c * rtb_DeadZone_c / rtb_Exp3) *
                     Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Product: '<S13>/Product' incorporates:
   *  Sum: '<S19>/Add1'
   */
  rtb_Product_idx_2 = rtb_vims_idx_2 * rtb_Switch_i;

  /* Saturate: '<S8>/Saturation' */
  if (Torque_Vectoring_2024_Y.TC_CUT[2] >
      Torque_Vectoring_2024_P.Saturation_UpperSat) {
    Torque_Vectoring_2024_Y.TC_CUT[2] =
      Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (Torque_Vectoring_2024_Y.TC_CUT[2] <
             Torque_Vectoring_2024_P.Saturation_LowerSat) {
    Torque_Vectoring_2024_Y.TC_CUT[2] =
      Torque_Vectoring_2024_P.Saturation_LowerSat;
  }

  /* Math: '<S8>/Square' incorporates:
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  Torque_Vectoring_2024_Y.lambda[2] = rtb_DeadZone_l * rtb_DeadZone_l;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_DeadZone_c = rt_powd_snf(rtb_DeadZone_l,
    Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S8>/Gain2' */
  rtb_Sliperror_idx_0 = Torque_Vectoring_2024_P.mu_03 * rtb_DeadZone_c;

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf(rtb_DeadZone_l,
    Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S8>/Gain3' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_04 * rtb_Sliperror_idx_1;

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  SignalConversion generated from: '<S8>/Math Function'
   */
  rtb_Product1_kf = rt_powd_snf(rtb_DeadZone_l,
    Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S8>/Gain4' */
  rtb_MathFunction7_idx_2 = Torque_Vectoring_2024_P.mu_05 * rtb_Product1_kf;

  /* Gain: '<S8>/Gain23' incorporates:
   *  Product: '<S8>/Product13'
   */
  rtb_Gain23_b = Torque_Vectoring_2024_Y.TC_CUT[2] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_13;

  /* Gain: '<S8>/Gain24' incorporates:
   *  Product: '<S8>/Product12'
   */
  rtb_Gain24_i = Torque_Vectoring_2024_Y.TC_CUT[2] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_14;

  /* Gain: '<S8>/Gain25' incorporates:
   *  Product: '<S8>/Product11'
   */
  rtb_Gain25_m = Torque_Vectoring_2024_Y.TC_CUT[2] * rtb_Product1_kf *
    Torque_Vectoring_2024_P.mu_15;

  /* Math: '<S8>/Square1' incorporates:
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[2] = Torque_Vectoring_2024_Y.TC_CUT[2] *
    Torque_Vectoring_2024_Y.TC_CUT[2];

  /* Gain: '<S8>/Gain21' incorporates:
   *  Product: '<S8>/Product8'
   */
  rtb_Gain21_n = Torque_Vectoring_2024_Y.T_pos[2] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_23;

  /* Gain: '<S8>/Gain20' incorporates:
   *  Product: '<S8>/Product7'
   */
  rtb_Gain20_p = Torque_Vectoring_2024_Y.T_pos[2] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_24;

  /* Math: '<S8>/Math Function4' incorporates:
   *  Constant: '<S8>/Constant4'
   */
  rtb_Product1_kf = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[2],
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Gain: '<S8>/Gain12' incorporates:
   *  Product: '<S8>/Product4'
   */
  rtb_Gain12_o = rtb_Product1_kf * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_33;

  /* Math: '<S8>/Math Function5' incorporates:
   *  Constant: '<S8>/Constant5'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[2],
    Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S8>/Math Function7' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_DeadZone_c = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[2],
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Constant: '<S8>/Constant8'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain22'
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
  u0_2 = ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 *
    rtb_DeadZone_l + Torque_Vectoring_2024_P.mu_02 *
    Torque_Vectoring_2024_Y.lambda[2]) + rtb_Sliperror_idx_0) + rtb_DeadZone) +
    rtb_MathFunction7_idx_2) + Torque_Vectoring_2024_P.mu_06 * rt_powd_snf
    (rtb_DeadZone_l, Torque_Vectoring_2024_P.Constant3_Value_o)) +
    Torque_Vectoring_2024_Y.TC_CUT[2] * rtb_DeadZone_l *
    Torque_Vectoring_2024_P.mu_11) + Torque_Vectoring_2024_Y.TC_CUT[2] *
    Torque_Vectoring_2024_Y.lambda[2] * Torque_Vectoring_2024_P.mu_12) +
    rtb_Gain23_b) + rtb_Gain24_i) + rtb_Gain25_m) +
    Torque_Vectoring_2024_Y.T_pos[2] * rtb_DeadZone_l *
    Torque_Vectoring_2024_P.mu_21) + Torque_Vectoring_2024_Y.T_pos[2] *
                        Torque_Vectoring_2024_Y.lambda[2] *
                        Torque_Vectoring_2024_P.mu_22) + rtb_Gain21_n) +
                      rtb_Gain20_p) + rtb_Product1_kf * rtb_DeadZone_l *
                     Torque_Vectoring_2024_P.mu_31) + rtb_Product1_kf *
                    Torque_Vectoring_2024_Y.lambda[2] *
                    Torque_Vectoring_2024_P.mu_32) + rtb_Gain12_o) +
                  rtb_Sliperror_idx_1 * rtb_DeadZone_l *
                  Torque_Vectoring_2024_P.mu_41) + rtb_Sliperror_idx_1 *
                 Torque_Vectoring_2024_Y.lambda[2] *
                 Torque_Vectoring_2024_P.mu_42) + rtb_DeadZone_c *
                rtb_DeadZone_l * Torque_Vectoring_2024_P.mu_51) +
               Torque_Vectoring_2024_P.mu_10 * Torque_Vectoring_2024_Y.TC_CUT[2])
              + Torque_Vectoring_2024_P.mu_20 * Torque_Vectoring_2024_Y.T_pos[2])
             + Torque_Vectoring_2024_P.mu_30 * rtb_Product1_kf) +
            Torque_Vectoring_2024_P.mu_40 * rtb_Sliperror_idx_1) +
           Torque_Vectoring_2024_P.mu_50 * rtb_DeadZone_c) +
          Torque_Vectoring_2024_P.mu_60 * rt_powd_snf
          (Torque_Vectoring_2024_Y.TC_CUT[2],
           Torque_Vectoring_2024_P.Constant8_Value)) +
    Torque_Vectoring_2024_P.mu_00;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  if ((Torque_Vectoring_2024_Y.wR[2] >=
       Torque_Vectoring_2024_P.Constant6_Value_g) || rtb_Compare_m) {
    Torque_Vectoring_2024_Y.lambda[2] = Torque_Vectoring_2024_Y.wR[2];
  } else {
    Torque_Vectoring_2024_Y.lambda[2] =
      Torque_Vectoring_2024_P.Constant6_Value_g;
  }

  /* Math: '<S19>/Exp4'
   *
   * About '<S19>/Exp4':
   *  Operator: exp
   */
  rtb_Add2_c_idx_2 = rtb_Switch_i;

  /* Sum: '<S19>/Add1' */
  rtb_Switch_i = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_3;

  /* Sum: '<S19>/Add2' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Memory: '<S19>/Memory'
   *  Sum: '<S19>/Add'
   *  Sum: '<S19>/Add1'
   */
  rtb_DeadZone_c = rtb_Saturation - (rtb_vims_idx_3 -
    Torque_Vectoring_2024_DW.Memory_PreviousInput_h[3]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

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
  rtb_Switch_i = exp(((0.0 - 1.0 / rtb_Exp2 * (rtb_Switch_i * rtb_Switch_i)) -
                      rtb_DeadZone_c * rtb_DeadZone_c / rtb_Exp3) *
                     Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Saturate: '<S8>/Saturation' */
  if (Torque_Vectoring_2024_Y.TC_CUT[3] >
      Torque_Vectoring_2024_P.Saturation_UpperSat) {
    Torque_Vectoring_2024_Y.TC_CUT[3] =
      Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (Torque_Vectoring_2024_Y.TC_CUT[3] <
             Torque_Vectoring_2024_P.Saturation_LowerSat) {
    Torque_Vectoring_2024_Y.TC_CUT[3] =
      Torque_Vectoring_2024_P.Saturation_LowerSat;
  }

  /* Math: '<S8>/Square' */
  Torque_Vectoring_2024_Y.lambda[3] =
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;

  /* Math: '<S8>/Math Function' incorporates:
   *  Constant: '<S8>/Constant'
   *  Math: '<S8>/Square'
   */
  rtb_DeadZone_c = rt_powd_snf
    (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3,
     Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S8>/Gain2' */
  rtb_Sliperror_idx_0 = Torque_Vectoring_2024_P.mu_03 * rtb_DeadZone_c;

  /* Math: '<S8>/Math Function1' incorporates:
   *  Constant: '<S8>/Constant1'
   *  Math: '<S8>/Square'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf
    (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3,
     Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S8>/Gain3' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_04 * rtb_Sliperror_idx_1;

  /* Math: '<S8>/Math Function3' incorporates:
   *  Constant: '<S8>/Constant2'
   *  Math: '<S8>/Square'
   */
  rtb_Product1_kf = rt_powd_snf
    (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3,
     Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S8>/Gain4' */
  rtb_MathFunction7_idx_2 = Torque_Vectoring_2024_P.mu_05 * rtb_Product1_kf;

  /* Gain: '<S8>/Gain23' incorporates:
   *  Product: '<S8>/Product13'
   */
  rtb_Gain23_b = Torque_Vectoring_2024_Y.TC_CUT[3] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_13;

  /* Gain: '<S8>/Gain24' incorporates:
   *  Product: '<S8>/Product12'
   */
  rtb_Gain24_i = Torque_Vectoring_2024_Y.TC_CUT[3] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_14;

  /* Gain: '<S8>/Gain25' incorporates:
   *  Product: '<S8>/Product11'
   */
  rtb_Gain25_m = Torque_Vectoring_2024_Y.TC_CUT[3] * rtb_Product1_kf *
    Torque_Vectoring_2024_P.mu_15;

  /* Math: '<S8>/Square1' incorporates:
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[3] = Torque_Vectoring_2024_Y.TC_CUT[3] *
    Torque_Vectoring_2024_Y.TC_CUT[3];

  /* Gain: '<S8>/Gain21' incorporates:
   *  Product: '<S8>/Product8'
   */
  rtb_Gain21_n = Torque_Vectoring_2024_Y.T_pos[3] * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_23;

  /* Gain: '<S8>/Gain20' incorporates:
   *  Product: '<S8>/Product7'
   */
  rtb_Gain20_p = Torque_Vectoring_2024_Y.T_pos[3] * rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_P.mu_24;

  /* Math: '<S8>/Math Function4' incorporates:
   *  Constant: '<S8>/Constant4'
   */
  rtb_Product1_kf = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[3],
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Gain: '<S8>/Gain12' incorporates:
   *  Product: '<S8>/Product4'
   */
  rtb_Gain12_o = rtb_Product1_kf * rtb_DeadZone_c *
    Torque_Vectoring_2024_P.mu_33;

  /* Math: '<S8>/Math Function5' incorporates:
   *  Constant: '<S8>/Constant5'
   */
  rtb_Sliperror_idx_1 = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[3],
    Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S8>/Math Function7' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_DeadZone_c = rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[3],
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Saturate: '<S8>/Saturation1' incorporates:
   *  Constant: '<S8>/Constant3'
   *  Constant: '<S8>/Constant7'
   *  Constant: '<S8>/Constant8'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain14'
   *  Gain: '<S8>/Gain15'
   *  Gain: '<S8>/Gain16'
   *  Gain: '<S8>/Gain17'
   *  Gain: '<S8>/Gain18'
   *  Gain: '<S8>/Gain19'
   *  Gain: '<S8>/Gain22'
   *  Gain: '<S8>/Gain26'
   *  Gain: '<S8>/Gain27'
   *  Gain: '<S8>/Gain5'
   *  Gain: '<S8>/Gain6'
   *  Gain: '<S8>/Gain7'
   *  Gain: '<S8>/Gain8'
   *  Gain: '<S8>/Gain9'
   *  Math: '<S8>/Math Function2'
   *  Math: '<S8>/Math Function6'
   *  Math: '<S8>/Square'
   *  Product: '<S8>/Product'
   *  Product: '<S8>/Product10'
   *  Product: '<S8>/Product14'
   *  Product: '<S8>/Product15'
   *  Product: '<S8>/Product2'
   *  Product: '<S8>/Product3'
   *  Product: '<S8>/Product5'
   *  Product: '<S8>/Product6'
   *  Product: '<S8>/Product9'
   *  Sum: '<S8>/Add'
   */
  rtb_Product1_kf = ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 +
    Torque_Vectoring_2024_P.mu_02 * Torque_Vectoring_2024_Y.lambda[3]) +
    rtb_Sliperror_idx_0) + rtb_DeadZone) + rtb_MathFunction7_idx_2) +
    Torque_Vectoring_2024_P.mu_06 * rt_powd_snf
    (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3,
    Torque_Vectoring_2024_P.Constant3_Value_o)) +
    Torque_Vectoring_2024_Y.TC_CUT[3] *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 *
    Torque_Vectoring_2024_P.mu_11) + Torque_Vectoring_2024_Y.TC_CUT[3] *
    Torque_Vectoring_2024_Y.lambda[3] * Torque_Vectoring_2024_P.mu_12) +
    rtb_Gain23_b) + rtb_Gain24_i) + rtb_Gain25_m) +
    Torque_Vectoring_2024_Y.T_pos[3] *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 *
    Torque_Vectoring_2024_P.mu_21) + Torque_Vectoring_2024_Y.T_pos[3] *
    Torque_Vectoring_2024_Y.lambda[3] * Torque_Vectoring_2024_P.mu_22) +
    rtb_Gain21_n) + rtb_Gain20_p) + rtb_Product1_kf *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 *
    Torque_Vectoring_2024_P.mu_31) + rtb_Product1_kf *
    Torque_Vectoring_2024_Y.lambda[3] * Torque_Vectoring_2024_P.mu_32) +
    rtb_Gain12_o) + rtb_Sliperror_idx_1 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 *
    Torque_Vectoring_2024_P.mu_41) + rtb_Sliperror_idx_1 *
    Torque_Vectoring_2024_Y.lambda[3] * Torque_Vectoring_2024_P.mu_42) +
    rtb_DeadZone_c * rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 *
    Torque_Vectoring_2024_P.mu_51) + Torque_Vectoring_2024_P.mu_10 *
    Torque_Vectoring_2024_Y.TC_CUT[3]) + Torque_Vectoring_2024_P.mu_20 *
    Torque_Vectoring_2024_Y.T_pos[3]) + Torque_Vectoring_2024_P.mu_30 *
                        rtb_Product1_kf) + Torque_Vectoring_2024_P.mu_40 *
                       rtb_Sliperror_idx_1) + Torque_Vectoring_2024_P.mu_50 *
                      rtb_DeadZone_c) + Torque_Vectoring_2024_P.mu_60 *
                     rt_powd_snf(Torque_Vectoring_2024_Y.TC_CUT[3],
    Torque_Vectoring_2024_P.Constant8_Value)) + Torque_Vectoring_2024_P.mu_00;

  /* MinMax: '<S6>/Max' incorporates:
   *  Constant: '<S6>/Constant6'
   */
  if ((Torque_Vectoring_2024_Y.wR[3] >=
       Torque_Vectoring_2024_P.Constant6_Value_g) || rtb_Compare_m) {
    Torque_Vectoring_2024_Y.lambda[3] = Torque_Vectoring_2024_Y.wR[3];
  } else {
    Torque_Vectoring_2024_Y.lambda[3] =
      Torque_Vectoring_2024_P.Constant6_Value_g;
  }

  /* Product: '<S7>/Product' incorporates:
   *  Constant: '<S227>/Constant'
   *  Constant: '<S227>/Constant1'
   *  Gain: '<S227>/Multiply'
   *  Sum: '<S227>/Add1'
   *  Sum: '<S227>/Add3'
   */
  rtb_MathFunction7_idx_2 = ((1.0 - Torque_Vectoring_2024_P.offset_cornering) *
    (Torque_Vectoring_2024_P.Constant_Value_h - rtb_z_max_k) +
    Torque_Vectoring_2024_P.offset_cornering) * rtb_DeadZone_i;
  rtb_z_max_k = ((1.0 - Torque_Vectoring_2024_P.offset_cornering) * rtb_z_max_k
                 + Torque_Vectoring_2024_P.offset_cornering) * rtb_DeadZone_i;

  /* MinMax: '<S22>/Max1' incorporates:
   *  Memory: '<Root>/Memory'
   */
  rtb_Compare_m = rtIsNaN(Torque_Vectoring_2024_DW.Memory_PreviousInput_k);
  if ((Torque_Vectoring_2024_P.TC_VX_ON_F >=
       Torque_Vectoring_2024_DW.Memory_PreviousInput_k) || rtb_Compare_m) {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.TC_VX_ON_F;
  } else {
    rtb_DeadZone_l = Torque_Vectoring_2024_DW.Memory_PreviousInput_k;
  }

  /* Product: '<S22>/Divide1' incorporates:
   *  Constant: '<S22>/Constant16'
   *  MinMax: '<S22>/Max1'
   *  Sum: '<S22>/Sum3'
   */
  rtb_DeadZone_i = Torque_Vectoring_2024_Y.lambda[0] / rtb_DeadZone_l -
    Torque_Vectoring_2024_P.Constant16_Value;

  /* MinMax: '<S22>/Max2' incorporates:
   *  Memory: '<Root>/Memory'
   */
  tmp_1 = rtIsNaN(Torque_Vectoring_2024_P.TC_VX_ON_R);
  if ((Torque_Vectoring_2024_DW.Memory_PreviousInput_k >=
       Torque_Vectoring_2024_P.TC_VX_ON_R) || tmp_1) {
    rtb_DeadZone_l = Torque_Vectoring_2024_DW.Memory_PreviousInput_k;
  } else {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.TC_VX_ON_R;
  }

  /* Product: '<S22>/Divide1' incorporates:
   *  Constant: '<S22>/Constant16'
   *  MinMax: '<S22>/Max2'
   *  Sum: '<S22>/Sum3'
   */
  rtb_DeadZone_c = Torque_Vectoring_2024_Y.lambda[2] / rtb_DeadZone_l -
    Torque_Vectoring_2024_P.Constant16_Value;

  /* MinMax: '<S22>/Max1' incorporates:
   *  Memory: '<Root>/Memory'
   */
  if ((Torque_Vectoring_2024_P.TC_VX_ON_F >=
       Torque_Vectoring_2024_DW.Memory_PreviousInput_k) || rtb_Compare_m) {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.TC_VX_ON_F;
  } else {
    rtb_DeadZone_l = Torque_Vectoring_2024_DW.Memory_PreviousInput_k;
  }

  /* Product: '<S22>/Divide1' incorporates:
   *  Constant: '<S22>/Constant16'
   *  MinMax: '<S22>/Max1'
   *  Sum: '<S22>/Sum3'
   */
  rtb_Exp3 = Torque_Vectoring_2024_Y.lambda[1] / rtb_DeadZone_l -
    Torque_Vectoring_2024_P.Constant16_Value;

  /* MinMax: '<S22>/Max2' incorporates:
   *  Memory: '<Root>/Memory'
   */
  if ((Torque_Vectoring_2024_DW.Memory_PreviousInput_k >=
       Torque_Vectoring_2024_P.TC_VX_ON_R) || tmp_1) {
    rtb_DeadZone_l = Torque_Vectoring_2024_DW.Memory_PreviousInput_k;
  } else {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.TC_VX_ON_R;
  }

  /* Product: '<S22>/Divide1' incorporates:
   *  Constant: '<S22>/Constant16'
   *  MinMax: '<S22>/Max2'
   *  Sum: '<S22>/Sum3'
   */
  rtb_Exp2 = Torque_Vectoring_2024_Y.lambda[3] / rtb_DeadZone_l -
    Torque_Vectoring_2024_P.Constant16_Value;

  /* MinMax: '<S22>/Min3' incorporates:
   *  Constant: '<S22>/Constant6'
   */
  rtb_Compare_m = !rtIsNaN(Torque_Vectoring_2024_P.Constant6_Value_j);
  if ((!(rtb_DeadZone_i <= Torque_Vectoring_2024_P.Constant6_Value_j)) &&
      rtb_Compare_m) {
    rtb_DeadZone_i = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  MinMax: '<S22>/Min3'
   */
  tmp_1 = rtIsNaN(Torque_Vectoring_2024_P.Constant15_Value);
  if ((rtb_DeadZone_i >= Torque_Vectoring_2024_P.Constant15_Value) || tmp_1) {
    Torque_Vectoring_2024_Y.lambda[0] = rtb_DeadZone_i;
  } else {
    Torque_Vectoring_2024_Y.lambda[0] = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* MinMax: '<S22>/Min3' incorporates:
   *  Constant: '<S22>/Constant6'
   */
  if ((!(rtb_Exp3 <= Torque_Vectoring_2024_P.Constant6_Value_j)) &&
      rtb_Compare_m) {
    rtb_Exp3 = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  MinMax: '<S22>/Min3'
   */
  if ((rtb_Exp3 >= Torque_Vectoring_2024_P.Constant15_Value) || tmp_1) {
    Torque_Vectoring_2024_Y.lambda[1] = rtb_Exp3;
  } else {
    Torque_Vectoring_2024_Y.lambda[1] = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* MinMax: '<S22>/Min3' incorporates:
   *  Constant: '<S22>/Constant6'
   */
  if ((!(rtb_DeadZone_c <= Torque_Vectoring_2024_P.Constant6_Value_j)) &&
      rtb_Compare_m) {
    rtb_DeadZone_c = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  MinMax: '<S22>/Min3'
   */
  if ((rtb_DeadZone_c >= Torque_Vectoring_2024_P.Constant15_Value) || tmp_1) {
    Torque_Vectoring_2024_Y.lambda[2] = rtb_DeadZone_c;
  } else {
    Torque_Vectoring_2024_Y.lambda[2] = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* MinMax: '<S22>/Min3' incorporates:
   *  Constant: '<S22>/Constant6'
   */
  if ((!(rtb_Exp2 <= Torque_Vectoring_2024_P.Constant6_Value_j)) &&
      rtb_Compare_m) {
    rtb_Exp2 = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S22>/Max9' incorporates:
   *  Constant: '<S22>/Constant15'
   *  MinMax: '<S22>/Min3'
   */
  if ((rtb_Exp2 >= Torque_Vectoring_2024_P.Constant15_Value) || tmp_1) {
    Torque_Vectoring_2024_Y.lambda[3] = rtb_Exp2;
  } else {
    Torque_Vectoring_2024_Y.lambda[3] = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* Sum: '<S21>/Sum2' incorporates:
   *  Constant: '<S21>/Desired slip front1'
   */
  rtb_Exp3 = Torque_Vectoring_2024_Y.lambda[0] -
    Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_F;

  /* Sum: '<S21>/Sum1' incorporates:
   *  Constant: '<S21>/Desired slip rear1'
   */
  rtb_Sliperror_idx_0 = Torque_Vectoring_2024_Y.lambda[2] -
    Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_R;

  /* Sum: '<S21>/Sum2' incorporates:
   *  Constant: '<S21>/Desired slip front1'
   */
  rtb_Exp2 = Torque_Vectoring_2024_Y.lambda[1] -
    Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_F;

  /* Sum: '<S21>/Sum1' incorporates:
   *  Constant: '<S21>/Desired slip rear1'
   */
  rtb_Sliperror_idx_1 = Torque_Vectoring_2024_Y.lambda[3] -
    Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_R;

  /* Sum: '<S119>/Sum' incorporates:
   *  DiscreteIntegrator: '<S110>/Integrator'
   *  Gain: '<S115>/Proportional Gain'
   */
  rtb_DeadZone_l = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Exp3 +
    Torque_Vectoring_2024_DW.u;

  /* Sum: '<S219>/Sum' incorporates:
   *  DiscreteIntegrator: '<S210>/Integrator'
   *  Gain: '<S215>/Proportional Gain'
   */
  rtb_DeadZone_i = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Exp2 +
    Torque_Vectoring_2024_DW.u_m;

  /* Sum: '<S69>/Sum' incorporates:
   *  DiscreteIntegrator: '<S60>/Integrator'
   *  Gain: '<S65>/Proportional Gain'
   */
  rtb_DeadZone_c = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Sliperror_idx_0 +
    Torque_Vectoring_2024_DW.u_a;

  /* Sum: '<S169>/Sum' incorporates:
   *  DiscreteIntegrator: '<S160>/Integrator'
   *  Gain: '<S165>/Proportional Gain'
   */
  rtb_DeadZone = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Sliperror_idx_1 +
    Torque_Vectoring_2024_DW.u_g;

  /* Saturate: '<S117>/Saturation' */
  if (rtb_DeadZone_l >
      Torque_Vectoring_2024_P.PIDController3_UpperSaturationLimit) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController3_UpperSaturationLimit;
  } else if (rtb_DeadZone_l <
             Torque_Vectoring_2024_P.PIDController3_LowerSaturationLimit) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController3_LowerSaturationLimit;
  } else {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_DeadZone_l;
  }

  /* End of Saturate: '<S117>/Saturation' */

  /* MinMax: '<S21>/Min' */
  rtb_Compare_m = !rtIsNaN(Torque_Vectoring_2024_P.TC_MAX_CUT);
  if ((!(rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 <=
         Torque_Vectoring_2024_P.TC_MAX_CUT)) && rtb_Compare_m) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S21>/Min1' incorporates:
   *  Constant: '<S21>/Constant5'
   */
  tmp_1 = rtIsNaN(Torque_Vectoring_2024_P.Constant5_Value_h);
  if ((rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >=
       Torque_Vectoring_2024_P.Constant5_Value_h) || tmp_1) {
    Torque_Vectoring_2024_Y.TC_CUT[0] =
      rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  } else {
    Torque_Vectoring_2024_Y.TC_CUT[0] =
      Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Saturate: '<S217>/Saturation' */
  if (rtb_DeadZone_i >
      Torque_Vectoring_2024_P.PIDController8_UpperSaturationLimit) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController8_UpperSaturationLimit;
  } else if (rtb_DeadZone_i <
             Torque_Vectoring_2024_P.PIDController8_LowerSaturationLimit) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController8_LowerSaturationLimit;
  } else {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_DeadZone_i;
  }

  /* End of Saturate: '<S217>/Saturation' */

  /* MinMax: '<S21>/Min' */
  if ((!(rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 <=
         Torque_Vectoring_2024_P.TC_MAX_CUT)) && rtb_Compare_m) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S21>/Min1' incorporates:
   *  Constant: '<S21>/Constant5'
   */
  if ((rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >=
       Torque_Vectoring_2024_P.Constant5_Value_h) || tmp_1) {
    Torque_Vectoring_2024_Y.TC_CUT[1] =
      rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  } else {
    Torque_Vectoring_2024_Y.TC_CUT[1] =
      Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Saturate: '<S67>/Saturation' */
  if (rtb_DeadZone_c >
      Torque_Vectoring_2024_P.PIDController1_UpperSaturationLimit) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController1_UpperSaturationLimit;
  } else if (rtb_DeadZone_c <
             Torque_Vectoring_2024_P.PIDController1_LowerSaturationLimit) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController1_LowerSaturationLimit;
  } else {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_DeadZone_c;
  }

  /* End of Saturate: '<S67>/Saturation' */

  /* MinMax: '<S21>/Min' */
  if ((!(rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 <=
         Torque_Vectoring_2024_P.TC_MAX_CUT)) && rtb_Compare_m) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S21>/Min1' incorporates:
   *  Constant: '<S21>/Constant5'
   */
  if ((rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >=
       Torque_Vectoring_2024_P.Constant5_Value_h) || tmp_1) {
    Torque_Vectoring_2024_Y.TC_CUT[2] =
      rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  } else {
    Torque_Vectoring_2024_Y.TC_CUT[2] =
      Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Saturate: '<S167>/Saturation' */
  if (rtb_DeadZone > Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit)
  {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit;
  } else if (rtb_DeadZone <
             Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit;
  } else {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = rtb_DeadZone;
  }

  /* End of Saturate: '<S167>/Saturation' */

  /* MinMax: '<S21>/Min' */
  if ((!(rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 <=
         Torque_Vectoring_2024_P.TC_MAX_CUT)) && rtb_Compare_m) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S21>/Min1' incorporates:
   *  Constant: '<S21>/Constant5'
   */
  if ((rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >=
       Torque_Vectoring_2024_P.Constant5_Value_h) || tmp_1) {
    Torque_Vectoring_2024_Y.TC_CUT[3] =
      rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  } else {
    Torque_Vectoring_2024_Y.TC_CUT[3] =
      Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Gain: '<Root>/Gain1' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 = (real_T)
    Torque_Vectoring_2024_P.Gain1_Gain_l * rtb_Saturation5;

  /* Saturate: '<S8>/Saturation1' */
  if (u0_0 > Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    u0_0 = Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (u0_0 < Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    u0_0 = Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S8>/Gain11' incorporates:
   *  Product: '<S8>/Product1'
   *  Saturate: '<S8>/Saturation1'
   */
  rtb_Saturation_e_idx_0 = u0_0 * rtb_Saturation_e_idx_0 * rtb_Max_a;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S227>/Constant1'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S227>/Multiply'
   *  Product: '<S7>/Product'
   *  Sum: '<S227>/Add3'
   *  Sum: '<S6>/Sum'
   */
  u0_0 = ((1.0 - Torque_Vectoring_2024_P.offset_cornering) * rtb_Integrator_h +
          Torque_Vectoring_2024_P.offset_cornering) * rtb_Integrator_m *
    (Torque_Vectoring_2024_P.Constant_Value_a - Torque_Vectoring_2024_Y.TC_CUT[0]);

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation_e_idx_0 <= u0_0) || rtIsNaN(u0_0)) {
    u0_0 = rtb_Saturation_e_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = u0_0 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;

  /* Saturate: '<S8>/Saturation1' */
  if (u0_1 > Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    u0_1 = Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (u0_1 < Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    u0_1 = Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S8>/Gain11' incorporates:
   *  Product: '<S8>/Product1'
   *  Saturate: '<S8>/Saturation1'
   */
  rtb_Saturation_e_idx_0 = u0_1 * rtb_Saturation_e_idx_1 * rtb_Max_a;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S227>/Constant'
   *  Constant: '<S227>/Constant1'
   *  Constant: '<S6>/Constant'
   *  Gain: '<S227>/Multiply'
   *  Product: '<S7>/Product'
   *  Sum: '<S227>/Add'
   *  Sum: '<S227>/Add3'
   *  Sum: '<S6>/Sum'
   */
  u0_0 = ((1.0 - Torque_Vectoring_2024_P.offset_cornering) *
          (Torque_Vectoring_2024_P.Constant_Value_h - rtb_Integrator_h) +
          Torque_Vectoring_2024_P.offset_cornering) * rtb_Integrator_m *
    (Torque_Vectoring_2024_P.Constant_Value_a - Torque_Vectoring_2024_Y.TC_CUT[1]);

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation_e_idx_0 <= u0_0) || rtIsNaN(u0_0)) {
    u0_0 = rtb_Saturation_e_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[1] = u0_0 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;

  /* Saturate: '<S8>/Saturation1' */
  if (u0_2 > Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    u0_2 = Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (u0_2 < Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    u0_2 = Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S8>/Gain11' incorporates:
   *  Product: '<S8>/Product1'
   *  Saturate: '<S8>/Saturation1'
   */
  rtb_Saturation_e_idx_0 = u0_2 * rtb_Saturation_e_idx_2 * rtb_Max_a;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S6>/Constant'
   *  Sum: '<S6>/Sum'
   */
  u0_0 = (Torque_Vectoring_2024_P.Constant_Value_a -
          Torque_Vectoring_2024_Y.TC_CUT[2]) * rtb_MathFunction7_idx_2;

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation_e_idx_0 <= u0_0) || rtIsNaN(u0_0)) {
    u0_0 = rtb_Saturation_e_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[2] = u0_0 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;

  /* Saturate: '<S8>/Saturation1' */
  if (rtb_Product1_kf > Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    rtb_Product1_kf = Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (rtb_Product1_kf < Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    rtb_Product1_kf = Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S8>/Gain11' incorporates:
   *  Product: '<S8>/Product1'
   *  Saturate: '<S8>/Saturation1'
   */
  rtb_Saturation_e_idx_0 = rtb_Product1_kf * u0 * rtb_Max_a;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S6>/Constant'
   *  Sum: '<S6>/Sum'
   */
  u0_0 = (Torque_Vectoring_2024_P.Constant_Value_a -
          Torque_Vectoring_2024_Y.TC_CUT[3]) * rtb_z_max_k;

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation_e_idx_0 <= u0_0) || rtIsNaN(u0_0)) {
    u0_0 = rtb_Saturation_e_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[3] = u0_0 *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;

  /* Sum: '<S20>/Add' */
  rtb_z_max_k = ((Torque_Vectoring_2024_Y.T_pos[0] +
                  Torque_Vectoring_2024_Y.T_pos[1]) +
                 Torque_Vectoring_2024_Y.T_pos[2]) +
    Torque_Vectoring_2024_Y.T_pos[3];

  /* MinMax: '<S20>/Max' incorporates:
   *  Constant: '<S20>/Constant'
   */
  if ((rtb_z_max_k >= Torque_Vectoring_2024_P.Constant_Value_an) || rtIsNaN
      (Torque_Vectoring_2024_P.Constant_Value_an)) {
    rtb_Integrator_m = rtb_z_max_k;
  } else {
    rtb_Integrator_m = Torque_Vectoring_2024_P.Constant_Value_an;
  }

  /* End of MinMax: '<S20>/Max' */

  /* MinMax: '<S20>/Min' */
  if ((!(rtb_z_max_k <= Torque_Vectoring_2024_P.Pmax)) && (!rtIsNaN
       (Torque_Vectoring_2024_P.Pmax))) {
    rtb_z_max_k = Torque_Vectoring_2024_P.Pmax;
  }

  /* End of MinMax: '<S20>/Min' */

  /* MinMax: '<S4>/Max' incorporates:
   *  Constant: '<S4>/Constant'
   */
  if ((rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >=
       Torque_Vectoring_2024_P.Constant_Value_k) || rtIsNaN
      (Torque_Vectoring_2024_P.Constant_Value_k)) {
    rtb_Max_a = rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  } else {
    rtb_Max_a = Torque_Vectoring_2024_P.Constant_Value_k;
  }

  /* End of MinMax: '<S4>/Max' */

  /* RelationalOperator: '<S4>/Equal' incorporates:
   *  Constant: '<S4>/Constant1'
   */
  rtb_Compare_m = (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 <=
                   Torque_Vectoring_2024_P.Constant1_Value_m);

  /* Outport: '<Root>/T_pos' incorporates:
   *  Product: '<S20>/Divide'
   *  Product: '<S20>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = Torque_Vectoring_2024_Y.T_pos[0] /
    rtb_Integrator_m * rtb_z_max_k / rtb_Max_a * (real_T)rtb_Compare_m;
  Torque_Vectoring_2024_Y.T_pos[1] = Torque_Vectoring_2024_Y.T_pos[1] /
    rtb_Integrator_m * rtb_z_max_k / rtb_Max_a * (real_T)rtb_Compare_m;
  Torque_Vectoring_2024_Y.T_pos[2] = Torque_Vectoring_2024_Y.T_pos[2] /
    rtb_Integrator_m * rtb_z_max_k / rtb_Max_a * (real_T)rtb_Compare_m;
  Torque_Vectoring_2024_Y.T_pos[3] = Torque_Vectoring_2024_Y.T_pos[3] /
    rtb_Integrator_m * rtb_z_max_k / rtb_Max_a * (real_T)rtb_Compare_m;

  /* MinMax: '<S13>/Max' incorporates:
   *  MinMax: '<S13>/Min'
   */
  rtb_Compare_m = rtIsNaN(rtb_vims_idx_1);
  if ((rtb_vims_idx_0 >= rtb_vims_idx_1) || rtb_Compare_m) {
    rtb_Saturation_e_idx_1 = rtb_vims_idx_0;
  } else {
    rtb_Saturation_e_idx_1 = rtb_vims_idx_1;
  }

  /* MinMax: '<S13>/Min' */
  if ((rtb_vims_idx_0 <= rtb_vims_idx_1) || rtb_Compare_m) {
    rtb_Saturation_e_idx_2 = rtb_vims_idx_0;
  } else {
    rtb_Saturation_e_idx_2 = rtb_vims_idx_1;
  }

  /* MinMax: '<S13>/Max' incorporates:
   *  MinMax: '<S13>/Min'
   */
  tmp_1 = !rtIsNaN(rtb_vims_idx_2);
  if ((!(rtb_Saturation_e_idx_1 >= rtb_vims_idx_2)) && tmp_1) {
    rtb_Saturation_e_idx_1 = rtb_vims_idx_2;
  }

  /* MinMax: '<S13>/Min' */
  if ((!(rtb_Saturation_e_idx_2 <= rtb_vims_idx_2)) && tmp_1) {
    rtb_Saturation_e_idx_2 = rtb_vims_idx_2;
  }

  /* Sum: '<S15>/Sum' incorporates:
   *  Concatenate: '<S12>/Vector Concatenate2'
   *  Constant: '<S12>/Constant'
   *  Constant: '<S12>/Constant1'
   *  Gain: '<S12>/Gain3'
   *  Memory: '<S3>/Memory2'
   *  Product: '<S15>/Product'
   *  Product: '<S15>/Product1'
   */
  rtb_Integrator_m = (Torque_Vectoring_2024_P.Gain3_Gain *
                      Torque_Vectoring_2024_P.Constant1_Value_i[0] *
                      Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] +
                      Torque_Vectoring_2024_P.Gain3_Gain *
                      Torque_Vectoring_2024_P.Constant1_Value_i[2] *
                      Torque_Vectoring_2024_DW.Memory2_PreviousInput[1]) +
    (Torque_Vectoring_2024_P.Constant_Value *
     Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] +
     Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] * rtb_A_k[2]);
  rtb_Max_a = (Torque_Vectoring_2024_P.Gain3_Gain *
               Torque_Vectoring_2024_P.Constant1_Value_i[1] *
               Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] +
               Torque_Vectoring_2024_P.Gain3_Gain *
               Torque_Vectoring_2024_P.Constant1_Value_i[3] *
               Torque_Vectoring_2024_DW.Memory2_PreviousInput[1]) +
    (Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] * rtb_A_k[1] +
     Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] *
     Torque_Vectoring_2024_P.Constant_Value);

  /* MinMax: '<S13>/Min' incorporates:
   *  MinMax: '<S13>/Max'
   */
  tmp_1 = !rtIsNaN(rtb_vims_idx_3);
  if ((!(rtb_Saturation_e_idx_2 <= rtb_vims_idx_3)) && tmp_1) {
    rtb_Saturation_e_idx_2 = rtb_vims_idx_3;
  }

  /* MinMax: '<S13>/Max' */
  if ((!(rtb_Saturation_e_idx_1 >= rtb_vims_idx_3)) && tmp_1) {
    rtb_Saturation_e_idx_1 = rtb_vims_idx_3;
  }

  /* Sum: '<S14>/Add' incorporates:
   *  Abs: '<S13>/Abs'
   *  Constant: '<S12>/Constant4'
   *  Constant: '<S16>/Constant'
   *  Constant: '<S17>/Constant'
   *  Constant: '<S18>/Constant'
   *  MinMax: '<S13>/Max'
   *  MinMax: '<S13>/Min'
   *  Product: '<S13>/Divide'
   *  Product: '<S13>/Product'
   *  Product: '<S13>/Product of Elements'
   *  Product: '<S14>/Product'
   *  RelationalOperator: '<S16>/Compare'
   *  RelationalOperator: '<S17>/Compare'
   *  RelationalOperator: '<S18>/Compare'
   *  Sum: '<S13>/Sum of Elements'
   *  Sum: '<S13>/Sum of Elements1'
   *  Sum: '<S13>/Sum of Elements2'
   *  Sum: '<S19>/Add1'
   */
  rtb_Product_idx_0 = (((((rtb_Product_idx_0 + rtb_Product_idx_1) +
    rtb_Product_idx_2) + rtb_vims_idx_3 * rtb_Switch_i) / (((rtb_Integrator +
    rtb_z_min_k) + rtb_Add2_c_idx_2) + rtb_Switch_i) * (real_T)(fabs
    (rtb_Saturation) <= Torque_Vectoring_2024_P.ax0) + (real_T)(rtb_Saturation >=
    Torque_Vectoring_2024_P.ax0) * rtb_Saturation_e_idx_2) + (real_T)
                       (rtb_Saturation < -Torque_Vectoring_2024_P.ax0) *
                       rtb_Saturation_e_idx_1) -
    (Torque_Vectoring_2024_P.Constant4_Value[0] * rtb_Integrator_m +
     Torque_Vectoring_2024_P.Constant4_Value[1] * rtb_Max_a);

  /* DeadZone: '<S153>/DeadZone' */
  if (rtb_DeadZone > Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit)
  {
    rtb_DeadZone -= Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit;
  } else if (rtb_DeadZone >=
             Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit) {
    rtb_DeadZone = 0.0;
  } else {
    rtb_DeadZone -= Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S153>/DeadZone' */

  /* Gain: '<S157>/Integral Gain' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
    Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Sliperror_idx_1;

  /* Switch: '<S151>/Switch1' incorporates:
   *  Constant: '<S151>/Clamping_zero'
   *  Constant: '<S151>/Constant'
   *  Constant: '<S151>/Constant2'
   *  RelationalOperator: '<S151>/fix for DT propagation issue'
   */
  if (rtb_DeadZone > Torque_Vectoring_2024_P.Clamping_zero_Value) {
    i = Torque_Vectoring_2024_P.Constant_Value_am;
  } else {
    i = Torque_Vectoring_2024_P.Constant2_Value_p;
  }

  /* Switch: '<S151>/Switch2' incorporates:
   *  Constant: '<S151>/Clamping_zero'
   *  Constant: '<S151>/Constant3'
   *  Constant: '<S151>/Constant4'
   *  RelationalOperator: '<S151>/fix for DT propagation issue1'
   */
  if (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >
      Torque_Vectoring_2024_P.Clamping_zero_Value) {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant3_Value_ob;
  } else {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant4_Value_c;
  }

  /* Switch: '<S151>/Switch' incorporates:
   *  Constant: '<S151>/Clamping_zero'
   *  Constant: '<S151>/Constant1'
   *  Logic: '<S151>/AND3'
   *  RelationalOperator: '<S151>/Equal1'
   *  RelationalOperator: '<S151>/Relational Operator'
   *  Switch: '<S151>/Switch1'
   *  Switch: '<S151>/Switch2'
   */
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value != rtb_DeadZone) && (i ==
       Memory_PreviousInput_tmp)) {
    rtb_Integrator = Torque_Vectoring_2024_P.Constant1_Value_l;
  } else {
    rtb_Integrator = rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  }

  /* End of Switch: '<S151>/Switch' */

  /* DeadZone: '<S53>/DeadZone' */
  if (rtb_DeadZone_c >
      Torque_Vectoring_2024_P.PIDController1_UpperSaturationLimit) {
    rtb_DeadZone_c -=
      Torque_Vectoring_2024_P.PIDController1_UpperSaturationLimit;
  } else if (rtb_DeadZone_c >=
             Torque_Vectoring_2024_P.PIDController1_LowerSaturationLimit) {
    rtb_DeadZone_c = 0.0;
  } else {
    rtb_DeadZone_c -=
      Torque_Vectoring_2024_P.PIDController1_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S53>/DeadZone' */

  /* Gain: '<S57>/Integral Gain' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
    Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Sliperror_idx_0;

  /* Switch: '<S51>/Switch1' incorporates:
   *  Constant: '<S51>/Clamping_zero'
   *  Constant: '<S51>/Constant'
   *  Constant: '<S51>/Constant2'
   *  RelationalOperator: '<S51>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_c > Torque_Vectoring_2024_P.Clamping_zero_Value_e) {
    i = Torque_Vectoring_2024_P.Constant_Value_hq;
  } else {
    i = Torque_Vectoring_2024_P.Constant2_Value_j;
  }

  /* Switch: '<S51>/Switch2' incorporates:
   *  Constant: '<S51>/Clamping_zero'
   *  Constant: '<S51>/Constant3'
   *  Constant: '<S51>/Constant4'
   *  RelationalOperator: '<S51>/fix for DT propagation issue1'
   */
  if (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >
      Torque_Vectoring_2024_P.Clamping_zero_Value_e) {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant3_Value_op;
  } else {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant4_Value_e;
  }

  /* Switch: '<S51>/Switch' incorporates:
   *  Constant: '<S51>/Clamping_zero'
   *  Constant: '<S51>/Constant1'
   *  Logic: '<S51>/AND3'
   *  RelationalOperator: '<S51>/Equal1'
   *  RelationalOperator: '<S51>/Relational Operator'
   *  Switch: '<S51>/Switch1'
   *  Switch: '<S51>/Switch2'
   */
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value_e != rtb_DeadZone_c) && (i ==
       Memory_PreviousInput_tmp)) {
    rtb_Product_idx_1 = Torque_Vectoring_2024_P.Constant1_Value;
  } else {
    rtb_Product_idx_1 = rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  }

  /* End of Switch: '<S51>/Switch' */

  /* DeadZone: '<S203>/DeadZone' */
  if (rtb_DeadZone_i >
      Torque_Vectoring_2024_P.PIDController8_UpperSaturationLimit) {
    rtb_DeadZone_i -=
      Torque_Vectoring_2024_P.PIDController8_UpperSaturationLimit;
  } else if (rtb_DeadZone_i >=
             Torque_Vectoring_2024_P.PIDController8_LowerSaturationLimit) {
    rtb_DeadZone_i = 0.0;
  } else {
    rtb_DeadZone_i -=
      Torque_Vectoring_2024_P.PIDController8_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S203>/DeadZone' */

  /* Gain: '<S207>/Integral Gain' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
    Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Exp2;

  /* Switch: '<S201>/Switch1' incorporates:
   *  Constant: '<S201>/Clamping_zero'
   *  Constant: '<S201>/Constant'
   *  Constant: '<S201>/Constant2'
   *  RelationalOperator: '<S201>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_i > Torque_Vectoring_2024_P.Clamping_zero_Value_j) {
    i = Torque_Vectoring_2024_P.Constant_Value_ej;
  } else {
    i = Torque_Vectoring_2024_P.Constant2_Value_g;
  }

  /* Switch: '<S201>/Switch2' incorporates:
   *  Constant: '<S201>/Clamping_zero'
   *  Constant: '<S201>/Constant3'
   *  Constant: '<S201>/Constant4'
   *  RelationalOperator: '<S201>/fix for DT propagation issue1'
   */
  if (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >
      Torque_Vectoring_2024_P.Clamping_zero_Value_j) {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant3_Value_j;
  } else {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant4_Value_o;
  }

  /* Switch: '<S201>/Switch' incorporates:
   *  Constant: '<S201>/Clamping_zero'
   *  Constant: '<S201>/Constant1'
   *  Logic: '<S201>/AND3'
   *  RelationalOperator: '<S201>/Equal1'
   *  RelationalOperator: '<S201>/Relational Operator'
   *  Switch: '<S201>/Switch1'
   *  Switch: '<S201>/Switch2'
   */
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value_j != rtb_DeadZone_i) && (i ==
       Memory_PreviousInput_tmp)) {
    rtb_Switch_i = Torque_Vectoring_2024_P.Constant1_Value_j;
  } else {
    rtb_Switch_i = rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  }

  /* End of Switch: '<S201>/Switch' */

  /* DeadZone: '<S103>/DeadZone' */
  if (rtb_DeadZone_l >
      Torque_Vectoring_2024_P.PIDController3_UpperSaturationLimit) {
    rtb_DeadZone_l -=
      Torque_Vectoring_2024_P.PIDController3_UpperSaturationLimit;
  } else if (rtb_DeadZone_l >=
             Torque_Vectoring_2024_P.PIDController3_LowerSaturationLimit) {
    rtb_DeadZone_l = 0.0;
  } else {
    rtb_DeadZone_l -=
      Torque_Vectoring_2024_P.PIDController3_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S103>/DeadZone' */

  /* Gain: '<S107>/Integral Gain' */
  rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
    Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Exp3;

  /* Outport: '<Root>/vx_est' incorporates:
   *  Memory: '<Root>/Memory'
   */
  Torque_Vectoring_2024_Y.vx_est =
    Torque_Vectoring_2024_DW.Memory_PreviousInput_k;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] = rtb_Saturation;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  Torque_Vectoring_2024_DW.Memory2_PreviousInput[1] = rtb_Saturation1;

  /* Outport: '<Root>/T_neg' incorporates:
   *  Constant: '<Root>/Constant'
   */
  Torque_Vectoring_2024_Y.T_neg[0] = Torque_Vectoring_2024_P.Constant_Value_eh[0];
  Torque_Vectoring_2024_Y.T_neg[1] = Torque_Vectoring_2024_P.Constant_Value_eh[1];
  Torque_Vectoring_2024_Y.T_neg[2] = Torque_Vectoring_2024_P.Constant_Value_eh[2];
  Torque_Vectoring_2024_Y.T_neg[3] = Torque_Vectoring_2024_P.Constant_Value_eh[3];

  /* Sum: '<S12>/Add1' incorporates:
   *  Constant: '<S12>/Constant4'
   *  Constant: '<S12>/Constant6'
   *  Product: '<S12>/Product5'
   */
  rtb_DeadZone_i = Torque_Vectoring_2024_P.Constant6_Value[0] - rtb_B_tmp *
    Torque_Vectoring_2024_P.Constant4_Value[0];
  rtb_Exp3 = Torque_Vectoring_2024_P.Constant6_Value[1] -
    Torque_Vectoring_2024_P.Constant4_Value[0] * rtb_Integrator_g;
  rtb_DeadZone_c = Torque_Vectoring_2024_P.Constant6_Value[2] - rtb_B_tmp *
    Torque_Vectoring_2024_P.Constant4_Value[1];
  rtb_Exp2 = Torque_Vectoring_2024_P.Constant6_Value[3] - rtb_Integrator_g *
    Torque_Vectoring_2024_P.Constant4_Value[1];

  /* Update for Memory: '<S12>/Memory' incorporates:
   *  Product: '<S12>/Product6'
   */
  for (i = 0; i < 2; i++) {
    /* Product: '<S12>/Product6' */
    Memory_PreviousInput_tmp = i << 1U;
    Torque_Vectoring_2024_DW.Memory_PreviousInput[Memory_PreviousInput_tmp] =
      0.0;

    /* Product: '<S12>/Product6' incorporates:
     *  Gain: '<S12>/Gain3'
     */
    rtb_Saturation1 = rtb_B[Memory_PreviousInput_tmp];
    Torque_Vectoring_2024_DW.Memory_PreviousInput[Memory_PreviousInput_tmp] +=
      rtb_Saturation1 * rtb_DeadZone_i;

    /* Product: '<S12>/Product6' incorporates:
     *  Gain: '<S12>/Gain3'
     */
    rtb_Saturation = rtb_B[Memory_PreviousInput_tmp + 1];
    Torque_Vectoring_2024_DW.Memory_PreviousInput[Memory_PreviousInput_tmp] +=
      rtb_Saturation * rtb_DeadZone_c;
    Torque_Vectoring_2024_DW.Memory_PreviousInput[Memory_PreviousInput_tmp + 1] =
      0.0;
    Torque_Vectoring_2024_DW.Memory_PreviousInput[Memory_PreviousInput_tmp + 1] +=
      rtb_Saturation1 * rtb_Exp3;
    Torque_Vectoring_2024_DW.Memory_PreviousInput[Memory_PreviousInput_tmp + 1] +=
      rtb_Saturation * rtb_Exp2;
  }

  /* End of Update for Memory: '<S12>/Memory' */

  /* Update for Memory: '<S19>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[0] = rtb_vims_idx_0;
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[1] = rtb_vims_idx_1;
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[2] = rtb_vims_idx_2;
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[3] = rtb_vims_idx_3;

  /* Update for Memory: '<Root>/Memory' incorporates:
   *  Product: '<S12>/Divide'
   *  Product: '<S14>/Product1'
   *  Sum: '<S14>/Add1'
   */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_k = rtb_B_tmp *
    rtb_Product_idx_0 + rtb_Integrator_m;

  /* Update for Memory: '<S3>/Memory1' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S11>/Constant'
   *  Constant: '<S3>/Constant'
   *  Product: '<S12>/Divide'
   *  Product: '<S14>/Product1'
   *  Product: '<S3>/Product'
   *  RelationalOperator: '<S11>/Compare'
   *  Sum: '<S14>/Add1'
   *  Sum: '<S3>/Add'
   */
  Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] = rtb_vxms;
  Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] = (rtb_Integrator_g *
    rtb_Product_idx_0 + rtb_Max_a) * (Torque_Vectoring_2024_P.Constant_Value_e -
    (real_T)(fabsf(Torque_Vectoring_2024_DW.Memory4_PreviousInput) <=
             Torque_Vectoring_2024_P.R01));

  /* Switch: '<S101>/Switch1' incorporates:
   *  Constant: '<S101>/Clamping_zero'
   *  Constant: '<S101>/Constant'
   *  Constant: '<S101>/Constant2'
   *  RelationalOperator: '<S101>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_l > Torque_Vectoring_2024_P.Clamping_zero_Value_m) {
    i = Torque_Vectoring_2024_P.Constant_Value_d;
  } else {
    i = Torque_Vectoring_2024_P.Constant2_Value_dk;
  }

  /* Switch: '<S101>/Switch2' incorporates:
   *  Constant: '<S101>/Clamping_zero'
   *  Constant: '<S101>/Constant3'
   *  Constant: '<S101>/Constant4'
   *  RelationalOperator: '<S101>/fix for DT propagation issue1'
   */
  if (rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 >
      Torque_Vectoring_2024_P.Clamping_zero_Value_m) {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant3_Value_d;
  } else {
    Memory_PreviousInput_tmp = Torque_Vectoring_2024_P.Constant4_Value_j;
  }

  /* Switch: '<S101>/Switch' incorporates:
   *  Constant: '<S101>/Clamping_zero'
   *  Constant: '<S101>/Constant1'
   *  Logic: '<S101>/AND3'
   *  RelationalOperator: '<S101>/Equal1'
   *  RelationalOperator: '<S101>/Relational Operator'
   *  Switch: '<S101>/Switch1'
   *  Switch: '<S101>/Switch2'
   */
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value_m != rtb_DeadZone_l) && (i ==
       Memory_PreviousInput_tmp)) {
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3 =
      Torque_Vectoring_2024_P.Constant1_Value_g;
  }

  /* Update for DiscreteIntegrator: '<S110>/Integrator' incorporates:
   *  Switch: '<S101>/Switch'
   */
  Torque_Vectoring_2024_DW.u += Torque_Vectoring_2024_P.Integrator_gainval *
    rtb_TmpSignalConversionAtMathFunctionInport1_idx_3;
  if (Torque_Vectoring_2024_DW.u >=
      Torque_Vectoring_2024_P.PIDController3_UpperIntegratorSaturationLimit) {
    Torque_Vectoring_2024_DW.u =
      Torque_Vectoring_2024_P.PIDController3_UpperIntegratorSaturationLimit;
  } else if (Torque_Vectoring_2024_DW.u <=
             Torque_Vectoring_2024_P.PIDController3_LowerIntegratorSaturationLimit)
  {
    Torque_Vectoring_2024_DW.u =
      Torque_Vectoring_2024_P.PIDController3_LowerIntegratorSaturationLimit;
  }

  /* End of Update for DiscreteIntegrator: '<S110>/Integrator' */

  /* Update for DiscreteIntegrator: '<S210>/Integrator' */
  Torque_Vectoring_2024_DW.u_m += Torque_Vectoring_2024_P.Integrator_gainval_b *
    rtb_Switch_i;
  if (Torque_Vectoring_2024_DW.u_m >=
      Torque_Vectoring_2024_P.PIDController8_UpperIntegratorSaturationLimit) {
    Torque_Vectoring_2024_DW.u_m =
      Torque_Vectoring_2024_P.PIDController8_UpperIntegratorSaturationLimit;
  } else if (Torque_Vectoring_2024_DW.u_m <=
             Torque_Vectoring_2024_P.PIDController8_LowerIntegratorSaturationLimit)
  {
    Torque_Vectoring_2024_DW.u_m =
      Torque_Vectoring_2024_P.PIDController8_LowerIntegratorSaturationLimit;
  }

  /* End of Update for DiscreteIntegrator: '<S210>/Integrator' */

  /* Update for DiscreteIntegrator: '<S60>/Integrator' */
  Torque_Vectoring_2024_DW.u_a += Torque_Vectoring_2024_P.Integrator_gainval_h *
    rtb_Product_idx_1;
  if (Torque_Vectoring_2024_DW.u_a >=
      Torque_Vectoring_2024_P.PIDController1_UpperIntegratorSaturationLimit) {
    Torque_Vectoring_2024_DW.u_a =
      Torque_Vectoring_2024_P.PIDController1_UpperIntegratorSaturationLimit;
  } else if (Torque_Vectoring_2024_DW.u_a <=
             Torque_Vectoring_2024_P.PIDController1_LowerIntegratorSaturationLimit)
  {
    Torque_Vectoring_2024_DW.u_a =
      Torque_Vectoring_2024_P.PIDController1_LowerIntegratorSaturationLimit;
  }

  /* End of Update for DiscreteIntegrator: '<S60>/Integrator' */

  /* Update for DiscreteIntegrator: '<S160>/Integrator' */
  Torque_Vectoring_2024_DW.u_g += Torque_Vectoring_2024_P.Integrator_gainval_l *
    rtb_Integrator;
  if (Torque_Vectoring_2024_DW.u_g >=
      Torque_Vectoring_2024_P.PIDController7_UpperIntegratorSaturationLimit) {
    Torque_Vectoring_2024_DW.u_g =
      Torque_Vectoring_2024_P.PIDController7_UpperIntegratorSaturationLimit;
  } else if (Torque_Vectoring_2024_DW.u_g <=
             Torque_Vectoring_2024_P.PIDController7_LowerIntegratorSaturationLimit)
  {
    Torque_Vectoring_2024_DW.u_g =
      Torque_Vectoring_2024_P.PIDController7_LowerIntegratorSaturationLimit;
  }

  /* End of Update for DiscreteIntegrator: '<S160>/Integrator' */
}

/* Model initialize function */
void Torque_Vectoring_2024_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(Torque_Vectoring_2024_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&Torque_Vectoring_2024_DW, 0,
                sizeof(DW_Torque_Vectoring_2024_T));

  /* external inputs */
  (void)memset(&Torque_Vectoring_2024_U, 0, sizeof(ExtU_Torque_Vectoring_2024_T));

  /* external outputs */
  (void)memset(&Torque_Vectoring_2024_Y, 0, sizeof(ExtY_Torque_Vectoring_2024_T));

  /* InitializeConditions for Saturate: '<Root>/Saturation2' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  Torque_Vectoring_2024_DW.Memory4_PreviousInput =
    Torque_Vectoring_2024_P.Memory4_InitialCondition;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput[0] =
    Torque_Vectoring_2024_P.Memory_InitialCondition[0];

  /* InitializeConditions for Memory: '<S19>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[0] =
    Torque_Vectoring_2024_P.Memory_InitialCondition_l;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput[1] =
    Torque_Vectoring_2024_P.Memory_InitialCondition[1];

  /* InitializeConditions for Memory: '<S19>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[1] =
    Torque_Vectoring_2024_P.Memory_InitialCondition_l;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput[2] =
    Torque_Vectoring_2024_P.Memory_InitialCondition[2];

  /* InitializeConditions for Memory: '<S19>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[2] =
    Torque_Vectoring_2024_P.Memory_InitialCondition_l;

  /* InitializeConditions for Memory: '<S12>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput[3] =
    Torque_Vectoring_2024_P.Memory_InitialCondition[3];

  /* InitializeConditions for Memory: '<S19>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_h[3] =
    Torque_Vectoring_2024_P.Memory_InitialCondition_l;

  /* InitializeConditions for Memory: '<Root>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_k =
    Torque_Vectoring_2024_P.Memory_InitialCondition_n;

  /* InitializeConditions for DiscreteIntegrator: '<S110>/Integrator' */
  Torque_Vectoring_2024_DW.u =
    Torque_Vectoring_2024_P.PIDController3_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S210>/Integrator' */
  Torque_Vectoring_2024_DW.u_m =
    Torque_Vectoring_2024_P.PIDController8_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S60>/Integrator' */
  Torque_Vectoring_2024_DW.u_a =
    Torque_Vectoring_2024_P.PIDController1_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S160>/Integrator' */
  Torque_Vectoring_2024_DW.u_g =
    Torque_Vectoring_2024_P.PIDController7_InitialConditionForIntegrator;

  /* InitializeConditions for Memory: '<S3>/Memory1' */
  Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] =
    Torque_Vectoring_2024_P.Memory1_InitialCondition;

  /* InitializeConditions for Memory: '<S3>/Memory2' */
  Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] =
    Torque_Vectoring_2024_P.Memory2_InitialCondition[0];

  /* InitializeConditions for Memory: '<S3>/Memory1' */
  Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] =
    Torque_Vectoring_2024_P.Memory1_InitialCondition;

  /* InitializeConditions for Memory: '<S3>/Memory2' */
  Torque_Vectoring_2024_DW.Memory2_PreviousInput[1] =
    Torque_Vectoring_2024_P.Memory2_InitialCondition[1];
}

/* Model terminate function */
void Torque_Vectoring_2024_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
