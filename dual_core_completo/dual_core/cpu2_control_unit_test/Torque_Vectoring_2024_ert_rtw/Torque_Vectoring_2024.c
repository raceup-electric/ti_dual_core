/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024.c
 *
 * Code generated for Simulink model 'Torque_Vectoring_2024'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Fri Mar 21 01:15:47 2025
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
#include "rt_nonfinite.h"
#include "Torque_Vectoring_2024_private.h"
#include <math.h>
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
  real_T rtb_P_k_m[4];
  real_T tmp[4];
  real_T rtb_K_k[2];
  real_T rtb_B_idx_0;
  real_T rtb_B_idx_1;
  real_T rtb_B_idx_2;
  real_T rtb_B_idx_3;
  real_T rtb_Csi;
  real_T rtb_DeadZone;
  real_T rtb_DeadZone_c;
  real_T rtb_DeadZone_i;
  real_T rtb_DeadZone_l;
  real_T rtb_Exp3;
  real_T rtb_Exp4_g;
  real_T rtb_Exp4_idx_0;
  real_T rtb_Exp4_idx_1;
  real_T rtb_Exp4_idx_2;
  real_T rtb_Gain3_o;
  real_T rtb_Imax;
  real_T rtb_Integrator_h;
  real_T rtb_Integrator_m;
  real_T rtb_Product13_h;
  real_T rtb_Product4_k;
  real_T rtb_Product7_l;
  real_T rtb_Product8_f;
  real_T rtb_Product_idx_0;
  real_T rtb_Product_idx_1;
  real_T rtb_Product_idx_2;
  real_T rtb_Saturation;
  real_T rtb_Saturation1;
  real_T rtb_Saturation1_j_idx_3;
  real_T rtb_Saturation4;
  real_T rtb_Saturation8;
  real_T rtb_Saturation_e_idx_0;
  real_T rtb_Saturation_e_idx_1;
  real_T rtb_Saturation_e_idx_2;
  real_T rtb_Sliperror_idx_0;
  real_T rtb_Sliperror_idx_1;
  real_T rtb_TmpSignalConversionAtMathFunctionInport1_c;
  real_T rtb_TmpSignalConversionAtMathFunctionInport1_g;
  real_T rtb_omega_e;
  real_T rtb_vims_idx_1;
  real_T rtb_vims_idx_2;
  real_T rtb_vims_idx_3;
  real_T rtb_vxms;
  real_T y;
  real_T y_0;
  real32_T rtb_Saturation2;
  real32_T rtb_Saturation5_h;
  real32_T rtb_Saturation5_idx_0;
  real32_T rtb_Saturation5_idx_1;
  real32_T rtb_Saturation5_idx_2;
  real32_T tmp_0;
  int16_T Memory_PreviousInput_d_tmp;
  int_T idxDelay;
  boolean_T rtb_Compare;
  boolean_T rtb_fw_inactive;
  boolean_T tmp_1;

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

  /* Gain: '<S11>/Gain3' incorporates:
   *  Gain: '<S11>/Gain4'
   */
  rtb_DeadZone_i = Torque_Vectoring_2024_P.kr_f1 + Torque_Vectoring_2024_P.kr_r1;
  rtb_vims_idx_1 = Torque_Vectoring_2024_P.zCoG -
    ((Torque_Vectoring_2024_P.zRC_r1 - Torque_Vectoring_2024_P.zRC_f1) *
     Torque_Vectoring_2024_P.a / Torque_Vectoring_2024_P.w +
     Torque_Vectoring_2024_P.zRC_f1);
  rtb_Saturation4 = (Torque_Vectoring_2024_P.kr_f1 / rtb_DeadZone_i *
                     rtb_vims_idx_1 + Torque_Vectoring_2024_P.b *
                     Torque_Vectoring_2024_P.zRC_f1 / Torque_Vectoring_2024_P.w) *
    Torque_Vectoring_2024_P.m / Torque_Vectoring_2024_P.t_f * rtb_Saturation1;

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

  /* Gain: '<S11>/Gain2' */
  rtb_Integrator_h = Torque_Vectoring_2024_P.m * Torque_Vectoring_2024_P.zCoG /
    (2.0 * Torque_Vectoring_2024_P.w) * rtb_Saturation;

  /* Delay: '<Root>/Delay' */
  rtb_vxms = Torque_Vectoring_2024_DW.Delay_DSTATE;

  /* Gain: '<S11>/Fl' incorporates:
   *  Delay: '<Root>/Delay'
   *  Math: '<S11>/Square'
   */
  rtb_DeadZone_c = Torque_Vectoring_2024_P.rho_air * Torque_Vectoring_2024_P.CLA1
    / 2.0 * (Torque_Vectoring_2024_DW.Delay_DSTATE *
             Torque_Vectoring_2024_DW.Delay_DSTATE);

  /* Gain: '<S11>/Gain1' */
  rtb_Imax = 0.5 * Torque_Vectoring_2024_P.b_a / Torque_Vectoring_2024_P.w *
    rtb_DeadZone_c;

  /* Sum: '<S11>/Add' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant1'
   *  Sum: '<S11>/Add1'
   *  Sum: '<S11>/Add2'
   */
  rtb_vims_idx_2 = Torque_Vectoring_2024_P.m * Torque_Vectoring_2024_P.g;
  rtb_vims_idx_3 = rtb_vims_idx_2 * Torque_Vectoring_2024_P.b / (2.0 *
    Torque_Vectoring_2024_P.w);
  rtb_Integrator_m = ((rtb_vims_idx_3 - rtb_Saturation4) - rtb_Integrator_h) +
    rtb_Imax;

  /* Sum: '<S11>/Add1' */
  rtb_Saturation4 = ((rtb_vims_idx_3 + rtb_Saturation4) - rtb_Integrator_h) +
    rtb_Imax;

  /* Gain: '<S11>/Gain4' */
  rtb_Imax = (Torque_Vectoring_2024_P.kr_r1 / rtb_DeadZone_i * rtb_vims_idx_1 +
              Torque_Vectoring_2024_P.a * Torque_Vectoring_2024_P.zRC_r1 /
              Torque_Vectoring_2024_P.w) * Torque_Vectoring_2024_P.m /
    Torque_Vectoring_2024_P.t_r * rtb_Saturation1;

  /* Gain: '<S11>/Gain' */
  rtb_DeadZone_c *= 0.5 * Torque_Vectoring_2024_P.a_a /
    Torque_Vectoring_2024_P.w;

  /* Sum: '<S11>/Add2' incorporates:
   *  Constant: '<S11>/Constant1'
   *  Sum: '<S11>/Add3'
   */
  rtb_vims_idx_1 = rtb_vims_idx_2 * Torque_Vectoring_2024_P.a / (2.0 *
    Torque_Vectoring_2024_P.w);
  rtb_DeadZone_i = ((rtb_vims_idx_1 - rtb_Imax) + rtb_Integrator_h) +
    rtb_DeadZone_c;

  /* Sum: '<S11>/Add3' */
  rtb_Imax = ((rtb_vims_idx_1 + rtb_Imax) + rtb_Integrator_h) + rtb_DeadZone_c;

  /* Saturate: '<S5>/Saturation' */
  rtb_Gain3_o = 0.95 * Torque_Vectoring_2024_P.R01;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_U.rpm[0] >
      Torque_Vectoring_2024_P.Saturation5_UpperSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_UpperSat;
  } else if (Torque_Vectoring_2024_U.rpm[0] <
             Torque_Vectoring_2024_P.Saturation5_LowerSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_LowerSat;
  } else {
    rtb_Saturation5_h = Torque_Vectoring_2024_U.rpm[0];
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.k_Re1 * rtb_Integrator_m +
    Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (rtb_Saturation1_j_idx_3 > Torque_Vectoring_2024_P.R01) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.R01;
  } else if (rtb_Saturation1_j_idx_3 < rtb_Gain3_o) {
    rtb_Saturation1_j_idx_3 = rtb_Gain3_o;
  }

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Exp4_g = (real_T)(Torque_Vectoring_2024_P.Gain_Gain_e * rtb_Saturation5_h)
    * Torque_Vectoring_2024_P.reduction_Gain * rtb_Saturation1_j_idx_3;

  /* MinMax: '<S8>/Max' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  rtb_Compare = BrtIsNaN(Torque_Vectoring_2024_P.Constant6_Value);
  if ((rtb_Exp4_g >= Torque_Vectoring_2024_P.Constant6_Value) || rtb_Compare) {
    y = rtb_Exp4_g;
  } else {
    y = Torque_Vectoring_2024_P.Constant6_Value;
  }

  /* Saturate: '<Root>/Saturation5' */
  rtb_Saturation5_idx_0 = rtb_Saturation5_h;

  /* Saturate: '<S5>/Saturation' */
  rtb_Saturation_e_idx_0 = rtb_Saturation1_j_idx_3;

  /* Product: '<Root>/Product' */
  rtb_Exp4_idx_0 = rtb_Exp4_g;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_U.rpm[1] >
      Torque_Vectoring_2024_P.Saturation5_UpperSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_UpperSat;
  } else if (Torque_Vectoring_2024_U.rpm[1] <
             Torque_Vectoring_2024_P.Saturation5_LowerSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_LowerSat;
  } else {
    rtb_Saturation5_h = Torque_Vectoring_2024_U.rpm[1];
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.k_Re1 * rtb_Saturation4 +
    Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (rtb_Saturation1_j_idx_3 > Torque_Vectoring_2024_P.R01) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.R01;
  } else if (rtb_Saturation1_j_idx_3 < rtb_Gain3_o) {
    rtb_Saturation1_j_idx_3 = rtb_Gain3_o;
  }

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Exp4_g = (real_T)(Torque_Vectoring_2024_P.Gain_Gain_e * rtb_Saturation5_h)
    * Torque_Vectoring_2024_P.reduction_Gain * rtb_Saturation1_j_idx_3;

  /* MinMax: '<S8>/Max' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  if ((rtb_Exp4_g >= Torque_Vectoring_2024_P.Constant6_Value) || rtb_Compare) {
    rtb_Saturation8 = rtb_Exp4_g;
  } else {
    rtb_Saturation8 = Torque_Vectoring_2024_P.Constant6_Value;
  }

  /* Saturate: '<Root>/Saturation5' */
  rtb_Saturation5_idx_1 = rtb_Saturation5_h;

  /* Saturate: '<S5>/Saturation' */
  rtb_Saturation_e_idx_1 = rtb_Saturation1_j_idx_3;

  /* Product: '<Root>/Product' */
  rtb_Exp4_idx_1 = rtb_Exp4_g;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_U.rpm[2] >
      Torque_Vectoring_2024_P.Saturation5_UpperSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_UpperSat;
  } else if (Torque_Vectoring_2024_U.rpm[2] <
             Torque_Vectoring_2024_P.Saturation5_LowerSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_LowerSat;
  } else {
    rtb_Saturation5_h = Torque_Vectoring_2024_U.rpm[2];
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.k_Re1 * rtb_DeadZone_i +
    Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (rtb_Saturation1_j_idx_3 > Torque_Vectoring_2024_P.R01) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.R01;
  } else if (rtb_Saturation1_j_idx_3 < rtb_Gain3_o) {
    rtb_Saturation1_j_idx_3 = rtb_Gain3_o;
  }

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Exp4_g = (real_T)(Torque_Vectoring_2024_P.Gain_Gain_e * rtb_Saturation5_h)
    * Torque_Vectoring_2024_P.reduction_Gain * rtb_Saturation1_j_idx_3;

  /* MinMax: '<S8>/Max' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  if ((rtb_Exp4_g >= Torque_Vectoring_2024_P.Constant6_Value) || rtb_Compare) {
    y_0 = rtb_Exp4_g;
  } else {
    y_0 = Torque_Vectoring_2024_P.Constant6_Value;
  }

  /* Saturate: '<Root>/Saturation5' */
  rtb_Saturation5_idx_2 = rtb_Saturation5_h;

  /* Saturate: '<S5>/Saturation' */
  rtb_Saturation_e_idx_2 = rtb_Saturation1_j_idx_3;

  /* Product: '<Root>/Product' */
  rtb_Exp4_idx_2 = rtb_Exp4_g;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (Torque_Vectoring_2024_U.rpm[3] >
      Torque_Vectoring_2024_P.Saturation5_UpperSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_UpperSat;
  } else if (Torque_Vectoring_2024_U.rpm[3] <
             Torque_Vectoring_2024_P.Saturation5_LowerSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation5_LowerSat;
  } else {
    rtb_Saturation5_h = Torque_Vectoring_2024_U.rpm[3];
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.k_Re1 * rtb_Imax +
    Torque_Vectoring_2024_P.R01;

  /* Saturate: '<S5>/Saturation' */
  if (rtb_Saturation1_j_idx_3 > Torque_Vectoring_2024_P.R01) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.R01;
  } else if (rtb_Saturation1_j_idx_3 < rtb_Gain3_o) {
    rtb_Saturation1_j_idx_3 = rtb_Gain3_o;
  }

  /* Product: '<Root>/Product' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/reduction'
   */
  rtb_Exp4_g = (real_T)(Torque_Vectoring_2024_P.Gain_Gain_e * rtb_Saturation5_h)
    * Torque_Vectoring_2024_P.reduction_Gain * rtb_Saturation1_j_idx_3;

  /* MinMax: '<S32>/Max1' incorporates:
   *  Delay: '<Root>/Delay'
   */
  rtb_fw_inactive = rtIsNaN(Torque_Vectoring_2024_DW.Delay_DSTATE);
  if ((Torque_Vectoring_2024_P.TC_VX_ON_F >=
       Torque_Vectoring_2024_DW.Delay_DSTATE) || rtb_fw_inactive) {
    rtb_Gain3_o = Torque_Vectoring_2024_P.TC_VX_ON_F;
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_DW.Delay_DSTATE;
  }

  /* Product: '<S32>/Divide1' incorporates:
   *  Constant: '<S32>/Constant16'
   *  MinMax: '<S32>/Max1'
   *  MinMax: '<S8>/Max'
   *  Sum: '<S32>/Sum3'
   */
  rtb_DeadZone_l = y / rtb_Gain3_o - Torque_Vectoring_2024_P.Constant16_Value;

  /* MinMax: '<S32>/Max2' incorporates:
   *  Delay: '<Root>/Delay'
   */
  tmp_1 = rtIsNaN(Torque_Vectoring_2024_P.TC_VX_ON_R);
  if ((Torque_Vectoring_2024_DW.Delay_DSTATE >=
       Torque_Vectoring_2024_P.TC_VX_ON_R) || tmp_1) {
    rtb_Gain3_o = Torque_Vectoring_2024_DW.Delay_DSTATE;
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_P.TC_VX_ON_R;
  }

  /* Product: '<S32>/Divide1' incorporates:
   *  Constant: '<S32>/Constant16'
   *  MinMax: '<S32>/Max2'
   *  MinMax: '<S8>/Max'
   *  Sum: '<S32>/Sum3'
   */
  rtb_Integrator_h = y_0 / rtb_Gain3_o -
    Torque_Vectoring_2024_P.Constant16_Value;

  /* MinMax: '<S32>/Max1' incorporates:
   *  Delay: '<Root>/Delay'
   */
  if ((Torque_Vectoring_2024_P.TC_VX_ON_F >=
       Torque_Vectoring_2024_DW.Delay_DSTATE) || rtb_fw_inactive) {
    rtb_Gain3_o = Torque_Vectoring_2024_P.TC_VX_ON_F;
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_DW.Delay_DSTATE;
  }

  /* Product: '<S32>/Divide1' incorporates:
   *  Constant: '<S32>/Constant16'
   *  MinMax: '<S32>/Max1'
   *  MinMax: '<S8>/Max'
   *  Sum: '<S32>/Sum3'
   */
  rtb_vims_idx_1 = rtb_Saturation8 / rtb_Gain3_o -
    Torque_Vectoring_2024_P.Constant16_Value;

  /* MinMax: '<S8>/Max' incorporates:
   *  Constant: '<S8>/Constant6'
   */
  if ((rtb_Exp4_g >= Torque_Vectoring_2024_P.Constant6_Value) || rtb_Compare) {
    rtb_Gain3_o = rtb_Exp4_g;
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_P.Constant6_Value;
  }

  /* MinMax: '<S32>/Max2' incorporates:
   *  Delay: '<Root>/Delay'
   */
  if ((Torque_Vectoring_2024_DW.Delay_DSTATE >=
       Torque_Vectoring_2024_P.TC_VX_ON_R) || tmp_1) {
    rtb_B_idx_2 = Torque_Vectoring_2024_DW.Delay_DSTATE;
  } else {
    rtb_B_idx_2 = Torque_Vectoring_2024_P.TC_VX_ON_R;
  }

  /* Product: '<S32>/Divide1' incorporates:
   *  Constant: '<S32>/Constant16'
   *  MinMax: '<S32>/Max2'
   *  MinMax: '<S8>/Max'
   *  Sum: '<S32>/Sum3'
   */
  rtb_vims_idx_2 = rtb_Gain3_o / rtb_B_idx_2 -
    Torque_Vectoring_2024_P.Constant16_Value;

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
  rtb_DeadZone_c = (real_T)Torque_Vectoring_2024_P.Gain3_Gain_a * tmp_0;

  /* Math: '<S2>/Square2' incorporates:
   *  Math: '<S2>/Square1'
   */
  rtb_vims_idx_3 = rtb_DeadZone_c * rtb_DeadZone_c;

  /* SignalConversion generated from: '<S15>/Cos' incorporates:
   *  Constant: '<S12>/Constant2'
   *  Constant: '<S12>/Constant4'
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant4'
   *  Constant: '<S2>/Constant5'
   *  Constant: '<S2>/Constant6'
   *  Constant: '<S2>/Constant7'
   *  Constant: '<S2>/Constant8'
   *  Gain: '<S12>/Gain'
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
   *  Sum: '<S12>/Add'
   *  Sum: '<S12>/Add1'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S2>/Sum2'
   */
  rtb_B_idx_0 = (((((Torque_Vectoring_2024_P.p_fl[0] * Brt_powd_snf
                     (rtb_DeadZone_c, Torque_Vectoring_2024_P.Constant3_Value) +
                     Torque_Vectoring_2024_P.p_fl[1] * Brt_powd_snf
                     (rtb_DeadZone_c, Torque_Vectoring_2024_P.Constant1_Value_k))
                    + Torque_Vectoring_2024_P.p_fl[2] * Brt_powd_snf
                    (rtb_DeadZone_c, Torque_Vectoring_2024_P.Constant2_Value)) +
                   rtb_vims_idx_3 * Torque_Vectoring_2024_P.p_fl[3]) +
                  Torque_Vectoring_2024_P.p_fl[4] * rtb_DeadZone_c) +
                 Torque_Vectoring_2024_P.p_fl[5]) *
    Torque_Vectoring_2024_P.Gain_Gain - Torque_Vectoring_2024_P.toe_f;
  rtb_B_idx_1 = (((((Torque_Vectoring_2024_P.p_fr[4] * rtb_DeadZone_c +
                     Torque_Vectoring_2024_P.p_fr[5]) + rtb_vims_idx_3 *
                    Torque_Vectoring_2024_P.p_fr[3]) +
                   Torque_Vectoring_2024_P.p_fr[2] * Brt_powd_snf(rtb_DeadZone_c,
    Torque_Vectoring_2024_P.Constant4_Value)) + Torque_Vectoring_2024_P.p_fr[1] *
                  Brt_powd_snf(rtb_DeadZone_c,
    Torque_Vectoring_2024_P.Constant5_Value)) + Torque_Vectoring_2024_P.p_fr[0] *
                 Brt_powd_snf(rtb_DeadZone_c,
    Torque_Vectoring_2024_P.Constant6_Value_f)) *
    Torque_Vectoring_2024_P.Gain_Gain + Torque_Vectoring_2024_P.toe_f;
  rtb_B_idx_2 = Torque_Vectoring_2024_P.Gain_Gain_j *
    Torque_Vectoring_2024_P.toe_r;

  /* MinMax: '<S32>/Min3' incorporates:
   *  Constant: '<S32>/Constant6'
   */
  tmp_1 = !rtIsNaN(Torque_Vectoring_2024_P.Constant6_Value_j);
  if ((!(rtb_DeadZone_l <= Torque_Vectoring_2024_P.Constant6_Value_j)) && tmp_1)
  {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S32>/Max9' incorporates:
   *  Constant: '<S32>/Constant15'
   */
  rtb_fw_inactive = rtIsNaN(Torque_Vectoring_2024_P.Constant15_Value);
  if ((!(rtb_DeadZone_l >= Torque_Vectoring_2024_P.Constant15_Value)) &&
      (!rtb_fw_inactive)) {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* Outport: '<Root>/lambda' */
  Torque_Vectoring_2024_Y.lambda[0] = rtb_DeadZone_l;

  /* Outport: '<Root>/wR' */
  Torque_Vectoring_2024_Y.wR[0] = rtb_Exp4_idx_0;

  /* MinMax: '<S32>/Max9' incorporates:
   *  MinMax: '<S32>/Min3'
   */
  rtb_P_k_m[0] = rtb_DeadZone_l;

  /* MinMax: '<S32>/Min3' incorporates:
   *  Constant: '<S32>/Constant6'
   */
  if ((!(rtb_vims_idx_1 <= Torque_Vectoring_2024_P.Constant6_Value_j)) && tmp_1)
  {
    rtb_vims_idx_1 = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S32>/Max9' incorporates:
   *  Constant: '<S32>/Constant15'
   */
  if ((rtb_vims_idx_1 >= Torque_Vectoring_2024_P.Constant15_Value) ||
      rtb_fw_inactive) {
    rtb_DeadZone_l = rtb_vims_idx_1;
  } else {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* Outport: '<Root>/lambda' */
  Torque_Vectoring_2024_Y.lambda[1] = rtb_DeadZone_l;

  /* Outport: '<Root>/wR' */
  Torque_Vectoring_2024_Y.wR[1] = rtb_Exp4_idx_1;

  /* MinMax: '<S32>/Max9' incorporates:
   *  MinMax: '<S32>/Min3'
   */
  rtb_P_k_m[1] = rtb_DeadZone_l;

  /* MinMax: '<S32>/Min3' incorporates:
   *  Constant: '<S32>/Constant6'
   */
  if ((!(rtb_Integrator_h <= Torque_Vectoring_2024_P.Constant6_Value_j)) &&
      tmp_1) {
    rtb_Integrator_h = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S32>/Max9' incorporates:
   *  Constant: '<S32>/Constant15'
   */
  if ((rtb_Integrator_h >= Torque_Vectoring_2024_P.Constant15_Value) ||
      rtb_fw_inactive) {
    rtb_DeadZone_l = rtb_Integrator_h;
  } else {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* Outport: '<Root>/lambda' */
  Torque_Vectoring_2024_Y.lambda[2] = rtb_DeadZone_l;

  /* Outport: '<Root>/wR' */
  Torque_Vectoring_2024_Y.wR[2] = rtb_Exp4_idx_2;

  /* MinMax: '<S32>/Max9' incorporates:
   *  MinMax: '<S32>/Min3'
   */
  rtb_P_k_m[2] = rtb_DeadZone_l;

  /* MinMax: '<S32>/Min3' incorporates:
   *  Constant: '<S32>/Constant6'
   */
  if ((!(rtb_vims_idx_2 <= Torque_Vectoring_2024_P.Constant6_Value_j)) && tmp_1)
  {
    rtb_vims_idx_2 = Torque_Vectoring_2024_P.Constant6_Value_j;
  }

  /* MinMax: '<S32>/Max9' incorporates:
   *  Constant: '<S32>/Constant15'
   */
  if ((rtb_vims_idx_2 >= Torque_Vectoring_2024_P.Constant15_Value) ||
      rtb_fw_inactive) {
    rtb_DeadZone_l = rtb_vims_idx_2;
  } else {
    rtb_DeadZone_l = Torque_Vectoring_2024_P.Constant15_Value;
  }

  /* Outport: '<Root>/lambda' */
  Torque_Vectoring_2024_Y.lambda[3] = rtb_DeadZone_l;

  /* Outport: '<Root>/wR' */
  Torque_Vectoring_2024_Y.wR[3] = rtb_Exp4_g;

  /* Saturate: '<Root>/Saturation2' incorporates:
   *  Inport: '<Root>/yaw_r'
   */
  if (Torque_Vectoring_2024_U.yaw_r >
      Torque_Vectoring_2024_P.Saturation2_UpperSat) {
    rtb_Saturation2 = Torque_Vectoring_2024_P.Saturation2_UpperSat;
  } else if (Torque_Vectoring_2024_U.yaw_r <
             Torque_Vectoring_2024_P.Saturation2_LowerSat) {
    rtb_Saturation2 = Torque_Vectoring_2024_P.Saturation2_LowerSat;
  } else {
    rtb_Saturation2 = Torque_Vectoring_2024_U.yaw_r;
  }

  /* End of Saturate: '<Root>/Saturation2' */

  /* Sum: '<S15>/Add' incorporates:
   *  Constant: '<S12>/Constant4'
   *  Gain: '<S15>/Multiply'
   *  Gain: '<S15>/Multiply1'
   *  Gain: '<S15>/Multiply2'
   *  Gain: '<S15>/Multiply3'
   *  Outport: '<Root>/wR'
   *  Product: '<S15>/Product1'
   *  SignalConversion generated from: '<S15>/Cos'
   *  Trigonometry: '<S15>/Cos'
   */
  rtb_Integrator_h = (real_T)Torque_Vectoring_2024_P.Multiply_Gain *
    rtb_Saturation2 + cos(rtb_B_idx_0) * rtb_Exp4_idx_0;
  rtb_vims_idx_1 = (real_T)Torque_Vectoring_2024_P.Multiply1_Gain *
    rtb_Saturation2 + cos(rtb_B_idx_1) * rtb_Exp4_idx_1;
  rtb_vims_idx_2 = (real_T)Torque_Vectoring_2024_P.Multiply2_Gain *
    rtb_Saturation2 + cos(rtb_B_idx_2) * rtb_Exp4_idx_2;
  rtb_vims_idx_3 = (real_T)Torque_Vectoring_2024_P.Multiply3_Gain *
    rtb_Saturation2 + cos(Torque_Vectoring_2024_P.toe_r) * rtb_Exp4_g;

  /* Math: '<S21>/Exp2' incorporates:
   *  Constant: '<S21>/Constant1'
   *
   * About '<S21>/Exp2':
   *  Operator: magnitude^2
   */
  rtb_DeadZone_c = Torque_Vectoring_2024_P.sigma_w2 *
    Torque_Vectoring_2024_P.sigma_w2;

  /* Math: '<S21>/Exp3' incorporates:
   *  Constant: '<S21>/Constant3'
   *
   * About '<S21>/Exp3':
   *  Operator: magnitude^2
   */
  rtb_Exp3 = Torque_Vectoring_2024_P.sigma_w1 * Torque_Vectoring_2024_P.sigma_w1;

  /* Sum: '<S21>/Add1' */
  rtb_Exp4_g = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_Integrator_h;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  rtb_Sliperror_idx_0 = rtb_Saturation - (rtb_Integrator_h -
    Torque_Vectoring_2024_DW.Memory_PreviousInput[0]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

  /* Math: '<S21>/Exp4' incorporates:
   *  Gain: '<S21>/Gain'
   *  Math: '<S21>/Exp'
   *  Math: '<S21>/Exp1'
   *  Product: '<S21>/Divide'
   *  Product: '<S21>/Divide1'
   *  Sum: '<S21>/Add3'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   *
   * About '<S21>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S21>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Exp4_g = exp(((0.0 - 1.0 / rtb_DeadZone_c * (rtb_Exp4_g * rtb_Exp4_g)) -
                    rtb_Sliperror_idx_0 * rtb_Sliperror_idx_0 / rtb_Exp3) *
                   Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Product: '<S15>/Product' incorporates:
   *  Sum: '<S21>/Add1'
   */
  rtb_Product_idx_0 = rtb_Integrator_h * rtb_Exp4_g;

  /* Saturate: '<S10>/Saturation' */
  if (rtb_B_idx_0 > Torque_Vectoring_2024_P.Saturation_UpperSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (rtb_B_idx_0 < Torque_Vectoring_2024_P.Saturation_LowerSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_LowerSat;
  }

  /* Math: '<S10>/Square' incorporates:
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_0 = rtb_Integrator_m * rtb_Integrator_m;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_Integrator_m,
    Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S10>/Gain2' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_03 * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Csi = Brt_powd_snf(rtb_Integrator_m,
                        Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S10>/Gain3' */
  rtb_Gain3_o = Torque_Vectoring_2024_P.mu_04 * rtb_Csi;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Memory: '<S14>/Memory'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = Brt_powd_snf(rtb_Integrator_m,
    Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S10>/Gain4' */
  rtb_Saturation8 = Torque_Vectoring_2024_P.mu_05 *
    Torque_Vectoring_2024_Y.T_pos[0];

  /* Product: '<S10>/Product13' */
  rtb_Product13_h = rtb_B_idx_0 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product12' */
  y_0 = rtb_B_idx_0 * rtb_Csi;

  /* Product: '<S10>/Product11' */
  y = rtb_B_idx_0 * Torque_Vectoring_2024_Y.T_pos[0];

  /* Math: '<S10>/Square1' */
  rtb_B_idx_3 = rtb_B_idx_0 * rtb_B_idx_0;

  /* Product: '<S10>/Product8' */
  rtb_Product8_f = rtb_B_idx_3 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product7' */
  rtb_Product7_l = rtb_B_idx_3 * rtb_Csi;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Product: '<S10>/Product4' */
  rtb_Product4_k = Torque_Vectoring_2024_Y.T_pos[0] * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_Csi = Brt_powd_snf(rtb_B_idx_0, Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Sum: '<S10>/Add' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain12'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain20'
   *  Gain: '<S10>/Gain21'
   *  Gain: '<S10>/Gain22'
   *  Gain: '<S10>/Gain23'
   *  Gain: '<S10>/Gain24'
   *  Gain: '<S10>/Gain25'
   *  Gain: '<S10>/Gain26'
   *  Gain: '<S10>/Gain27'
   *  Gain: '<S10>/Gain5'
   *  Gain: '<S10>/Gain6'
   *  Gain: '<S10>/Gain7'
   *  Gain: '<S10>/Gain8'
   *  Gain: '<S10>/Gain9'
   *  Math: '<S10>/Math Function2'
   *  Math: '<S10>/Math Function6'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product10'
   *  Product: '<S10>/Product14'
   *  Product: '<S10>/Product15'
   *  Product: '<S10>/Product2'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product5'
   *  Product: '<S10>/Product6'
   *  Product: '<S10>/Product9'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_TmpSignalConversionAtMathFunctionInport1_c =
    ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 * rtb_Integrator_m +
    Torque_Vectoring_2024_P.mu_02 * rtb_Sliperror_idx_0) + rtb_DeadZone) +
    rtb_Gain3_o) + rtb_Saturation8) + Torque_Vectoring_2024_P.mu_06 *
    Brt_powd_snf(rtb_Integrator_m, Torque_Vectoring_2024_P.Constant3_Value_o)) +
    rtb_B_idx_0 * rtb_Integrator_m * Torque_Vectoring_2024_P.mu_11) +
    rtb_B_idx_0 * rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_12) +
                       Torque_Vectoring_2024_P.mu_13 * rtb_Product13_h) +
                      Torque_Vectoring_2024_P.mu_14 * y_0) +
                     Torque_Vectoring_2024_P.mu_15 * y) + rtb_B_idx_3 *
                    rtb_Integrator_m * Torque_Vectoring_2024_P.mu_21) +
                   rtb_B_idx_3 * rtb_Sliperror_idx_0 *
                   Torque_Vectoring_2024_P.mu_22) +
                  Torque_Vectoring_2024_P.mu_23 * rtb_Product8_f) +
                 Torque_Vectoring_2024_P.mu_24 * rtb_Product7_l) +
                Torque_Vectoring_2024_Y.T_pos[0] * rtb_Integrator_m *
                Torque_Vectoring_2024_P.mu_31) + Torque_Vectoring_2024_Y.T_pos[0]
               * rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_32) +
              Torque_Vectoring_2024_P.mu_33 * rtb_Product4_k) + rtb_Csi *
             rtb_Integrator_m * Torque_Vectoring_2024_P.mu_41) + rtb_Csi *
            rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_42) +
           rtb_Sliperror_idx_1 * rtb_Integrator_m *
           Torque_Vectoring_2024_P.mu_51) + Torque_Vectoring_2024_P.mu_10 *
          rtb_B_idx_0) + Torque_Vectoring_2024_P.mu_20 * rtb_B_idx_3) +
        Torque_Vectoring_2024_P.mu_30 * Torque_Vectoring_2024_Y.T_pos[0]) +
       Torque_Vectoring_2024_P.mu_40 * rtb_Csi) + Torque_Vectoring_2024_P.mu_50 *
      rtb_Sliperror_idx_1) + Torque_Vectoring_2024_P.mu_60 * Brt_powd_snf
     (rtb_B_idx_0, Torque_Vectoring_2024_P.Constant8_Value)) +
    Torque_Vectoring_2024_P.mu_00;

  /* Math: '<S21>/Exp4'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   */
  rtb_Exp4_idx_0 = rtb_Exp4_g;

  /* Sum: '<S21>/Add1' */
  rtb_Exp4_g = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_1;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  rtb_Sliperror_idx_0 = rtb_Saturation - (rtb_vims_idx_1 -
    Torque_Vectoring_2024_DW.Memory_PreviousInput[1]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

  /* Math: '<S21>/Exp4' incorporates:
   *  Gain: '<S21>/Gain'
   *  Math: '<S21>/Exp'
   *  Math: '<S21>/Exp1'
   *  Product: '<S21>/Divide'
   *  Product: '<S21>/Divide1'
   *  Sum: '<S21>/Add3'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   *
   * About '<S21>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S21>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Exp4_g = exp(((0.0 - 1.0 / rtb_DeadZone_c * (rtb_Exp4_g * rtb_Exp4_g)) -
                    rtb_Sliperror_idx_0 * rtb_Sliperror_idx_0 / rtb_Exp3) *
                   Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Product: '<S15>/Product' incorporates:
   *  Sum: '<S21>/Add1'
   */
  rtb_Product_idx_1 = rtb_vims_idx_1 * rtb_Exp4_g;

  /* Saturate: '<S10>/Saturation' */
  if (rtb_B_idx_1 > Torque_Vectoring_2024_P.Saturation_UpperSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (rtb_B_idx_1 < Torque_Vectoring_2024_P.Saturation_LowerSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_LowerSat;
  } else {
    rtb_B_idx_0 = rtb_B_idx_1;
  }

  /* Math: '<S10>/Square' incorporates:
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_0 = rtb_Saturation4 * rtb_Saturation4;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_Saturation4,
    Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S10>/Gain2' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_03 * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Csi = Brt_powd_snf(rtb_Saturation4,
                        Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S10>/Gain3' */
  rtb_Gain3_o = Torque_Vectoring_2024_P.mu_04 * rtb_Csi;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Memory: '<S14>/Memory'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  Torque_Vectoring_2024_Y.T_pos[1] = Brt_powd_snf(rtb_Saturation4,
    Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S10>/Gain4' */
  rtb_Saturation8 = Torque_Vectoring_2024_P.mu_05 *
    Torque_Vectoring_2024_Y.T_pos[1];

  /* Product: '<S10>/Product13' */
  rtb_Product13_h = rtb_B_idx_0 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product12' */
  y_0 = rtb_B_idx_0 * rtb_Csi;

  /* Product: '<S10>/Product11' */
  y = rtb_B_idx_0 * Torque_Vectoring_2024_Y.T_pos[1];

  /* Math: '<S10>/Square1' */
  rtb_B_idx_3 = rtb_B_idx_0 * rtb_B_idx_0;

  /* Product: '<S10>/Product8' */
  rtb_Product8_f = rtb_B_idx_3 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product7' */
  rtb_Product7_l = rtb_B_idx_3 * rtb_Csi;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[1] = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Product: '<S10>/Product4' */
  rtb_Product4_k = Torque_Vectoring_2024_Y.T_pos[1] * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_Csi = Brt_powd_snf(rtb_B_idx_0, Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Sum: '<S10>/Add' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain12'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain20'
   *  Gain: '<S10>/Gain21'
   *  Gain: '<S10>/Gain22'
   *  Gain: '<S10>/Gain23'
   *  Gain: '<S10>/Gain24'
   *  Gain: '<S10>/Gain25'
   *  Gain: '<S10>/Gain26'
   *  Gain: '<S10>/Gain27'
   *  Gain: '<S10>/Gain5'
   *  Gain: '<S10>/Gain6'
   *  Gain: '<S10>/Gain7'
   *  Gain: '<S10>/Gain8'
   *  Gain: '<S10>/Gain9'
   *  Math: '<S10>/Math Function2'
   *  Math: '<S10>/Math Function6'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product10'
   *  Product: '<S10>/Product14'
   *  Product: '<S10>/Product15'
   *  Product: '<S10>/Product2'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product5'
   *  Product: '<S10>/Product6'
   *  Product: '<S10>/Product9'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_TmpSignalConversionAtMathFunctionInport1_g =
    ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 * rtb_Saturation4 +
    Torque_Vectoring_2024_P.mu_02 * rtb_Sliperror_idx_0) + rtb_DeadZone) +
    rtb_Gain3_o) + rtb_Saturation8) + Torque_Vectoring_2024_P.mu_06 *
    Brt_powd_snf(rtb_Saturation4, Torque_Vectoring_2024_P.Constant3_Value_o)) +
    rtb_B_idx_0 * rtb_Saturation4 * Torque_Vectoring_2024_P.mu_11) + rtb_B_idx_0
    * rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_12) +
                       Torque_Vectoring_2024_P.mu_13 * rtb_Product13_h) +
                      Torque_Vectoring_2024_P.mu_14 * y_0) +
                     Torque_Vectoring_2024_P.mu_15 * y) + rtb_B_idx_3 *
                    rtb_Saturation4 * Torque_Vectoring_2024_P.mu_21) +
                   rtb_B_idx_3 * rtb_Sliperror_idx_0 *
                   Torque_Vectoring_2024_P.mu_22) +
                  Torque_Vectoring_2024_P.mu_23 * rtb_Product8_f) +
                 Torque_Vectoring_2024_P.mu_24 * rtb_Product7_l) +
                Torque_Vectoring_2024_Y.T_pos[1] * rtb_Saturation4 *
                Torque_Vectoring_2024_P.mu_31) + Torque_Vectoring_2024_Y.T_pos[1]
               * rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_32) +
              Torque_Vectoring_2024_P.mu_33 * rtb_Product4_k) + rtb_Csi *
             rtb_Saturation4 * Torque_Vectoring_2024_P.mu_41) + rtb_Csi *
            rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_42) +
           rtb_Sliperror_idx_1 * rtb_Saturation4 * Torque_Vectoring_2024_P.mu_51)
          + Torque_Vectoring_2024_P.mu_10 * rtb_B_idx_0) +
         Torque_Vectoring_2024_P.mu_20 * rtb_B_idx_3) +
        Torque_Vectoring_2024_P.mu_30 * Torque_Vectoring_2024_Y.T_pos[1]) +
       Torque_Vectoring_2024_P.mu_40 * rtb_Csi) + Torque_Vectoring_2024_P.mu_50 *
      rtb_Sliperror_idx_1) + Torque_Vectoring_2024_P.mu_60 * Brt_powd_snf
     (rtb_B_idx_0, Torque_Vectoring_2024_P.Constant8_Value)) +
    Torque_Vectoring_2024_P.mu_00;

  /* Math: '<S21>/Exp4'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   */
  rtb_Exp4_idx_1 = rtb_Exp4_g;

  /* Sum: '<S21>/Add1' */
  rtb_Exp4_g = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_2;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  rtb_Sliperror_idx_0 = rtb_Saturation - (rtb_vims_idx_2 -
    Torque_Vectoring_2024_DW.Memory_PreviousInput[2]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

  /* Math: '<S21>/Exp4' incorporates:
   *  Gain: '<S21>/Gain'
   *  Math: '<S21>/Exp'
   *  Math: '<S21>/Exp1'
   *  Product: '<S21>/Divide'
   *  Product: '<S21>/Divide1'
   *  Sum: '<S21>/Add3'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   *
   * About '<S21>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S21>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Exp4_g = exp(((0.0 - 1.0 / rtb_DeadZone_c * (rtb_Exp4_g * rtb_Exp4_g)) -
                    rtb_Sliperror_idx_0 * rtb_Sliperror_idx_0 / rtb_Exp3) *
                   Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Product: '<S15>/Product' incorporates:
   *  Sum: '<S21>/Add1'
   */
  rtb_Product_idx_2 = rtb_vims_idx_2 * rtb_Exp4_g;

  /* Saturate: '<S10>/Saturation' */
  if (rtb_B_idx_2 > Torque_Vectoring_2024_P.Saturation_UpperSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (rtb_B_idx_2 < Torque_Vectoring_2024_P.Saturation_LowerSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_LowerSat;
  } else {
    rtb_B_idx_0 = rtb_B_idx_2;
  }

  /* Math: '<S10>/Square' incorporates:
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_0 = rtb_DeadZone_i * rtb_DeadZone_i;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_DeadZone_i,
    Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S10>/Gain2' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_03 * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Csi = Brt_powd_snf(rtb_DeadZone_i,
                        Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S10>/Gain3' */
  rtb_Gain3_o = Torque_Vectoring_2024_P.mu_04 * rtb_Csi;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Memory: '<S14>/Memory'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  Torque_Vectoring_2024_Y.T_pos[2] = Brt_powd_snf(rtb_DeadZone_i,
    Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S10>/Gain4' */
  rtb_Saturation8 = Torque_Vectoring_2024_P.mu_05 *
    Torque_Vectoring_2024_Y.T_pos[2];

  /* Product: '<S10>/Product13' */
  rtb_Product13_h = rtb_B_idx_0 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product12' */
  y_0 = rtb_B_idx_0 * rtb_Csi;

  /* Product: '<S10>/Product11' */
  y = rtb_B_idx_0 * Torque_Vectoring_2024_Y.T_pos[2];

  /* Math: '<S10>/Square1' */
  rtb_B_idx_3 = rtb_B_idx_0 * rtb_B_idx_0;

  /* Product: '<S10>/Product8' */
  rtb_Product8_f = rtb_B_idx_3 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product7' */
  rtb_Product7_l = rtb_B_idx_3 * rtb_Csi;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[2] = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Product: '<S10>/Product4' */
  rtb_Product4_k = Torque_Vectoring_2024_Y.T_pos[2] * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_Csi = Brt_powd_snf(rtb_B_idx_0, Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Sum: '<S10>/Add' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain12'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain20'
   *  Gain: '<S10>/Gain21'
   *  Gain: '<S10>/Gain22'
   *  Gain: '<S10>/Gain23'
   *  Gain: '<S10>/Gain24'
   *  Gain: '<S10>/Gain25'
   *  Gain: '<S10>/Gain26'
   *  Gain: '<S10>/Gain27'
   *  Gain: '<S10>/Gain5'
   *  Gain: '<S10>/Gain6'
   *  Gain: '<S10>/Gain7'
   *  Gain: '<S10>/Gain8'
   *  Gain: '<S10>/Gain9'
   *  Math: '<S10>/Math Function2'
   *  Math: '<S10>/Math Function6'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product10'
   *  Product: '<S10>/Product14'
   *  Product: '<S10>/Product15'
   *  Product: '<S10>/Product2'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product5'
   *  Product: '<S10>/Product6'
   *  Product: '<S10>/Product9'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_omega_e = ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 *
    rtb_DeadZone_i + Torque_Vectoring_2024_P.mu_02 * rtb_Sliperror_idx_0) +
    rtb_DeadZone) + rtb_Gain3_o) + rtb_Saturation8) +
    Torque_Vectoring_2024_P.mu_06 * Brt_powd_snf(rtb_DeadZone_i,
    Torque_Vectoring_2024_P.Constant3_Value_o)) + rtb_B_idx_0 * rtb_DeadZone_i *
    Torque_Vectoring_2024_P.mu_11) + rtb_B_idx_0 * rtb_Sliperror_idx_0 *
    Torque_Vectoring_2024_P.mu_12) + Torque_Vectoring_2024_P.mu_13 *
    rtb_Product13_h) + Torque_Vectoring_2024_P.mu_14 * y_0) +
    Torque_Vectoring_2024_P.mu_15 * y) + rtb_B_idx_3 * rtb_DeadZone_i *
    Torque_Vectoring_2024_P.mu_21) + rtb_B_idx_3 * rtb_Sliperror_idx_0 *
    Torque_Vectoring_2024_P.mu_22) + Torque_Vectoring_2024_P.mu_23 *
    rtb_Product8_f) + Torque_Vectoring_2024_P.mu_24 * rtb_Product7_l) +
    Torque_Vectoring_2024_Y.T_pos[2] * rtb_DeadZone_i *
    Torque_Vectoring_2024_P.mu_31) + Torque_Vectoring_2024_Y.T_pos[2] *
    rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_32) +
    Torque_Vectoring_2024_P.mu_33 * rtb_Product4_k) + rtb_Csi * rtb_DeadZone_i *
    Torque_Vectoring_2024_P.mu_41) + rtb_Csi * rtb_Sliperror_idx_0 *
                        Torque_Vectoring_2024_P.mu_42) + rtb_Sliperror_idx_1 *
                       rtb_DeadZone_i * Torque_Vectoring_2024_P.mu_51) +
                      Torque_Vectoring_2024_P.mu_10 * rtb_B_idx_0) +
                     Torque_Vectoring_2024_P.mu_20 * rtb_B_idx_3) +
                    Torque_Vectoring_2024_P.mu_30 *
                    Torque_Vectoring_2024_Y.T_pos[2]) +
                   Torque_Vectoring_2024_P.mu_40 * rtb_Csi) +
                  Torque_Vectoring_2024_P.mu_50 * rtb_Sliperror_idx_1) +
                 Torque_Vectoring_2024_P.mu_60 * Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant8_Value)) + Torque_Vectoring_2024_P.mu_00;

  /* Math: '<S21>/Exp4'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   */
  rtb_Exp4_idx_2 = rtb_Exp4_g;

  /* Sum: '<S21>/Add1' */
  rtb_Exp4_g = Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] -
    rtb_vims_idx_3;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  rtb_Sliperror_idx_0 = rtb_Saturation - (rtb_vims_idx_3 -
    Torque_Vectoring_2024_DW.Memory_PreviousInput[3]) *
    Torque_Vectoring_2024_P.Gain1_Gain;

  /* Math: '<S21>/Exp4' incorporates:
   *  Gain: '<S21>/Gain'
   *  Math: '<S21>/Exp'
   *  Math: '<S21>/Exp1'
   *  Product: '<S21>/Divide'
   *  Product: '<S21>/Divide1'
   *  Sum: '<S21>/Add3'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   *
   * About '<S21>/Exp':
   *  Operator: magnitude^2
   *
   * About '<S21>/Exp1':
   *  Operator: magnitude^2
   */
  rtb_Exp4_g = exp(((0.0 - 1.0 / rtb_DeadZone_c * (rtb_Exp4_g * rtb_Exp4_g)) -
                    rtb_Sliperror_idx_0 * rtb_Sliperror_idx_0 / rtb_Exp3) *
                   Torque_Vectoring_2024_P.Gain_Gain_f);

  /* Saturate: '<S10>/Saturation' incorporates:
   *  Constant: '<S12>/Constant4'
   *  SignalConversion generated from: '<S15>/Cos'
   */
  if (Torque_Vectoring_2024_P.toe_r >
      Torque_Vectoring_2024_P.Saturation_UpperSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_UpperSat;
  } else if (Torque_Vectoring_2024_P.toe_r <
             Torque_Vectoring_2024_P.Saturation_LowerSat) {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.Saturation_LowerSat;
  } else {
    rtb_B_idx_0 = Torque_Vectoring_2024_P.toe_r;
  }

  /* Math: '<S10>/Square' incorporates:
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_0 = rtb_Imax * rtb_Imax;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_Imax,
    Torque_Vectoring_2024_P.Constant_Value_b);

  /* Gain: '<S10>/Gain2' */
  rtb_DeadZone = Torque_Vectoring_2024_P.mu_03 * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Csi = Brt_powd_snf(rtb_Imax, Torque_Vectoring_2024_P.Constant1_Value_c);

  /* Gain: '<S10>/Gain3' */
  rtb_Gain3_o = Torque_Vectoring_2024_P.mu_04 * rtb_Csi;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Memory: '<S14>/Memory'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  Torque_Vectoring_2024_Y.T_pos[3] = Brt_powd_snf(rtb_Imax,
    Torque_Vectoring_2024_P.Constant2_Value_d);

  /* Gain: '<S10>/Gain4' */
  rtb_Saturation8 = Torque_Vectoring_2024_P.mu_05 *
    Torque_Vectoring_2024_Y.T_pos[3];

  /* Product: '<S10>/Product13' */
  rtb_Product13_h = rtb_B_idx_0 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product12' */
  y_0 = rtb_B_idx_0 * rtb_Csi;

  /* Product: '<S10>/Product11' */
  y = rtb_B_idx_0 * Torque_Vectoring_2024_Y.T_pos[3];

  /* Math: '<S10>/Square1' */
  rtb_B_idx_3 = rtb_B_idx_0 * rtb_B_idx_0;

  /* Product: '<S10>/Product8' */
  rtb_Product8_f = rtb_B_idx_3 * rtb_Sliperror_idx_1;

  /* Product: '<S10>/Product7' */
  rtb_Product7_l = rtb_B_idx_3 * rtb_Csi;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[3] = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant4_Value_p);

  /* Product: '<S10>/Product4' */
  rtb_Product4_k = Torque_Vectoring_2024_Y.T_pos[3] * rtb_Sliperror_idx_1;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_Csi = Brt_powd_snf(rtb_B_idx_0, Torque_Vectoring_2024_P.Constant5_Value_a);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Sliperror_idx_1 = Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant6_Value_p);

  /* Sum: '<S10>/Add' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain12'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain20'
   *  Gain: '<S10>/Gain21'
   *  Gain: '<S10>/Gain22'
   *  Gain: '<S10>/Gain23'
   *  Gain: '<S10>/Gain24'
   *  Gain: '<S10>/Gain25'
   *  Gain: '<S10>/Gain26'
   *  Gain: '<S10>/Gain27'
   *  Gain: '<S10>/Gain5'
   *  Gain: '<S10>/Gain6'
   *  Gain: '<S10>/Gain7'
   *  Gain: '<S10>/Gain8'
   *  Gain: '<S10>/Gain9'
   *  Math: '<S10>/Math Function2'
   *  Math: '<S10>/Math Function6'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product10'
   *  Product: '<S10>/Product14'
   *  Product: '<S10>/Product15'
   *  Product: '<S10>/Product2'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product5'
   *  Product: '<S10>/Product6'
   *  Product: '<S10>/Product9'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Product13_h = ((((((((((((((((((((((((((Torque_Vectoring_2024_P.mu_01 *
    rtb_Imax + Torque_Vectoring_2024_P.mu_02 * rtb_Sliperror_idx_0) +
    rtb_DeadZone) + rtb_Gain3_o) + rtb_Saturation8) +
    Torque_Vectoring_2024_P.mu_06 * Brt_powd_snf(rtb_Imax,
    Torque_Vectoring_2024_P.Constant3_Value_o)) + rtb_B_idx_0 * rtb_Imax *
    Torque_Vectoring_2024_P.mu_11) + rtb_B_idx_0 * rtb_Sliperror_idx_0 *
    Torque_Vectoring_2024_P.mu_12) + Torque_Vectoring_2024_P.mu_13 *
    rtb_Product13_h) + Torque_Vectoring_2024_P.mu_14 * y_0) +
    Torque_Vectoring_2024_P.mu_15 * y) + rtb_B_idx_3 * rtb_Imax *
    Torque_Vectoring_2024_P.mu_21) + rtb_B_idx_3 * rtb_Sliperror_idx_0 *
    Torque_Vectoring_2024_P.mu_22) + Torque_Vectoring_2024_P.mu_23 *
    rtb_Product8_f) + Torque_Vectoring_2024_P.mu_24 * rtb_Product7_l) +
    Torque_Vectoring_2024_Y.T_pos[3] * rtb_Imax * Torque_Vectoring_2024_P.mu_31)
    + Torque_Vectoring_2024_Y.T_pos[3] * rtb_Sliperror_idx_0 *
    Torque_Vectoring_2024_P.mu_32) + Torque_Vectoring_2024_P.mu_33 *
    rtb_Product4_k) + rtb_Csi * rtb_Imax * Torque_Vectoring_2024_P.mu_41) +
    rtb_Csi * rtb_Sliperror_idx_0 * Torque_Vectoring_2024_P.mu_42) +
    rtb_Sliperror_idx_1 * rtb_Imax * Torque_Vectoring_2024_P.mu_51) +
    Torque_Vectoring_2024_P.mu_10 * rtb_B_idx_0) + Torque_Vectoring_2024_P.mu_20
    * rtb_B_idx_3) + Torque_Vectoring_2024_P.mu_30 *
                        Torque_Vectoring_2024_Y.T_pos[3]) +
                       Torque_Vectoring_2024_P.mu_40 * rtb_Csi) +
                      Torque_Vectoring_2024_P.mu_50 * rtb_Sliperror_idx_1) +
                     Torque_Vectoring_2024_P.mu_60 * Brt_powd_snf(rtb_B_idx_0,
    Torque_Vectoring_2024_P.Constant8_Value)) + Torque_Vectoring_2024_P.mu_00;

  /* Gain: '<S10>/Gain11' */
  rtb_Gain3_o = 1.0 / Torque_Vectoring_2024_P.tau;

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

  /* Gain: '<S9>/Gain' incorporates:
   *  Saturate: '<Root>/Saturation3'
   */
  rtb_Saturation8 = (real_T)Torque_Vectoring_2024_P.Gain_Gain_b * tmp_0;

  /* Sum: '<S1>/Add' incorporates:
   *  Sum: '<S237>/Sum'
   *  Sum: '<S237>/Sum1'
   */
  rtb_Exp3 = rtb_Integrator_m + rtb_Saturation4;

  /* Gain: '<S1>/Gain' incorporates:
   *  Gain: '<S1>/Gain1'
   */
  rtb_Sliperror_idx_0 = Torque_Vectoring_2024_P.PDX2 /
    Torque_Vectoring_2024_P.FZ0;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Add'
   *  Sum: '<S1>/Add2'
   *  Sum: '<S1>/Subtract'
   */
  rtb_Csi = ((rtb_Exp3 - Torque_Vectoring_2024_P.FZ0) * rtb_Sliperror_idx_0 +
             Torque_Vectoring_2024_P.PDX1) * rtb_Exp3;

  /* Sum: '<S1>/Add1' */
  rtb_DeadZone_c = rtb_DeadZone_i + rtb_Imax;

  /* Product: '<S1>/Divide' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain1'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Add3'
   *  Sum: '<S1>/Add4'
   *  Sum: '<S1>/Subtract1'
   */
  rtb_Csi /= ((rtb_DeadZone_c - Torque_Vectoring_2024_P.FZ0) *
              rtb_Sliperror_idx_0 + Torque_Vectoring_2024_P.PDX1) *
    rtb_DeadZone_c + rtb_Csi;

  /* Sum: '<S9>/Add5' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Gain: '<S9>/Gain4'
   */
  rtb_DeadZone_c = (1.0 - Torque_Vectoring_2024_P.offset_throttle_csi) * rtb_Csi
    + Torque_Vectoring_2024_P.offset_throttle_csi;

  /* Product: '<S9>/Divide' incorporates:
   *  Constant: '<S9>/Constant'
   *  Product: '<S9>/Divide1'
   *  Sum: '<S9>/Add'
   */
  rtb_DeadZone_c = 1.0 / (Torque_Vectoring_2024_P.Constant_Value_n -
    rtb_DeadZone_c) * (rtb_DeadZone_c * rtb_Saturation8);

  /* Product: '<S237>/Divide' */
  rtb_Integrator_m /= rtb_Exp3;

  /* Product: '<S237>/Divide1' incorporates:
   *  Sum: '<S237>/Add2'
   *  Sum: '<S237>/Sum'
   */
  rtb_Imax *= 1.0 / (((rtb_Exp3 + rtb_DeadZone_i) + rtb_Imax) - rtb_Exp3);

  /* Sum: '<S237>/Add3' incorporates:
   *  Constant: '<S237>/Constant'
   *  Constant: '<S237>/Constant1'
   *  Gain: '<S237>/Multiply'
   *  Memory: '<S14>/Memory'
   *  Sum: '<S237>/Add'
   *  Sum: '<S237>/Add1'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = (1.0 -
    Torque_Vectoring_2024_P.offset_cornering) * rtb_Integrator_m +
    Torque_Vectoring_2024_P.offset_cornering;
  Torque_Vectoring_2024_Y.T_pos[1] = (1.0 -
    Torque_Vectoring_2024_P.offset_cornering) *
    (Torque_Vectoring_2024_P.Constant_Value_h - rtb_Integrator_m) +
    Torque_Vectoring_2024_P.offset_cornering;
  Torque_Vectoring_2024_Y.T_pos[2] = (1.0 -
    Torque_Vectoring_2024_P.offset_cornering) *
    (Torque_Vectoring_2024_P.Constant_Value_h - rtb_Imax) +
    Torque_Vectoring_2024_P.offset_cornering;
  Torque_Vectoring_2024_Y.T_pos[3] = (1.0 -
    Torque_Vectoring_2024_P.offset_cornering) * rtb_Imax +
    Torque_Vectoring_2024_P.offset_cornering;

  /* Product: '<S9>/Product' */
  rtb_B_idx_0 = rtb_DeadZone_c * Torque_Vectoring_2024_Y.T_pos[0];
  rtb_B_idx_1 = rtb_DeadZone_c * Torque_Vectoring_2024_Y.T_pos[1];
  rtb_B_idx_2 = rtb_Saturation8 * Torque_Vectoring_2024_Y.T_pos[2];
  rtb_B_idx_3 = rtb_Saturation8 * Torque_Vectoring_2024_Y.T_pos[3];

  /* Sum: '<S31>/Sum2' incorporates:
   *  Constant: '<S31>/Desired slip front1'
   */
  rtb_Integrator_m = rtb_P_k_m[0] - Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_F;

  /* Sum: '<S31>/Sum1' incorporates:
   *  Constant: '<S31>/Desired slip rear1'
   */
  rtb_Sliperror_idx_0 = rtb_P_k_m[2] -
    Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_R;

  /* Sum: '<S31>/Sum2' incorporates:
   *  Constant: '<S31>/Desired slip front1'
   */
  rtb_Exp3 = rtb_P_k_m[1] - Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_F;

  /* Sum: '<S31>/Sum1' incorporates:
   *  Constant: '<S31>/Desired slip rear1'
   */
  rtb_Sliperror_idx_1 = rtb_DeadZone_l -
    Torque_Vectoring_2024_P.TC_CL_TARGET_SLIP_R;

  /* Sum: '<S129>/Sum' incorporates:
   *  DiscreteIntegrator: '<S120>/Integrator'
   *  Gain: '<S125>/Proportional Gain'
   */
  rtb_DeadZone_l = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Integrator_m +
    Torque_Vectoring_2024_DW.u;

  /* Sum: '<S229>/Sum' incorporates:
   *  DiscreteIntegrator: '<S220>/Integrator'
   *  Gain: '<S225>/Proportional Gain'
   */
  rtb_DeadZone_i = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Exp3 +
    Torque_Vectoring_2024_DW.u_m;

  /* Sum: '<S79>/Sum' incorporates:
   *  DiscreteIntegrator: '<S70>/Integrator'
   *  Gain: '<S75>/Proportional Gain'
   */
  rtb_DeadZone_c = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Sliperror_idx_0 +
    Torque_Vectoring_2024_DW.u_a;

  /* Sum: '<S179>/Sum' incorporates:
   *  DiscreteIntegrator: '<S170>/Integrator'
   *  Gain: '<S175>/Proportional Gain'
   */
  rtb_DeadZone = Torque_Vectoring_2024_P.TC_CL_P_R * rtb_Sliperror_idx_1 +
    Torque_Vectoring_2024_DW.u_g;

  /* Saturate: '<S127>/Saturation' */
  if (rtb_DeadZone_l >
      Torque_Vectoring_2024_P.PIDController3_UpperSaturationLimit) {
    y = Torque_Vectoring_2024_P.PIDController3_UpperSaturationLimit;
  } else if (rtb_DeadZone_l <
             Torque_Vectoring_2024_P.PIDController3_LowerSaturationLimit) {
    y = Torque_Vectoring_2024_P.PIDController3_LowerSaturationLimit;
  } else {
    y = rtb_DeadZone_l;
  }

  /* End of Saturate: '<S127>/Saturation' */

  /* MinMax: '<S31>/Min' */
  tmp_1 = !rtIsNaN(Torque_Vectoring_2024_P.TC_MAX_CUT);
  if ((!(y <= Torque_Vectoring_2024_P.TC_MAX_CUT)) && tmp_1) {
    y = Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S31>/Min1' incorporates:
   *  Constant: '<S31>/Constant5'
   */
  rtb_Compare = !rtIsNaN(Torque_Vectoring_2024_P.Constant5_Value_h);
  if ((!(y >= Torque_Vectoring_2024_P.Constant5_Value_h)) && rtb_Compare) {
    y = Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Saturate: '<S227>/Saturation' */
  if (rtb_DeadZone_i >
      Torque_Vectoring_2024_P.PIDController8_UpperSaturationLimit) {
    rtb_Saturation8 =
      Torque_Vectoring_2024_P.PIDController8_UpperSaturationLimit;
  } else if (rtb_DeadZone_i <
             Torque_Vectoring_2024_P.PIDController8_LowerSaturationLimit) {
    rtb_Saturation8 =
      Torque_Vectoring_2024_P.PIDController8_LowerSaturationLimit;
  } else {
    rtb_Saturation8 = rtb_DeadZone_i;
  }

  /* End of Saturate: '<S227>/Saturation' */

  /* MinMax: '<S31>/Min' */
  if ((!(rtb_Saturation8 <= Torque_Vectoring_2024_P.TC_MAX_CUT)) && tmp_1) {
    rtb_Saturation8 = Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S31>/Min1' incorporates:
   *  Constant: '<S31>/Constant5'
   */
  if ((!(rtb_Saturation8 >= Torque_Vectoring_2024_P.Constant5_Value_h)) &&
      rtb_Compare) {
    rtb_Saturation8 = Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Saturate: '<S77>/Saturation' */
  if (rtb_DeadZone_c >
      Torque_Vectoring_2024_P.PIDController1_UpperSaturationLimit) {
    y_0 = Torque_Vectoring_2024_P.PIDController1_UpperSaturationLimit;
  } else if (rtb_DeadZone_c <
             Torque_Vectoring_2024_P.PIDController1_LowerSaturationLimit) {
    y_0 = Torque_Vectoring_2024_P.PIDController1_LowerSaturationLimit;
  } else {
    y_0 = rtb_DeadZone_c;
  }

  /* End of Saturate: '<S77>/Saturation' */

  /* MinMax: '<S31>/Min' */
  if ((!(y_0 <= Torque_Vectoring_2024_P.TC_MAX_CUT)) && tmp_1) {
    y_0 = Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S31>/Min1' incorporates:
   *  Constant: '<S31>/Constant5'
   */
  if ((!(y_0 >= Torque_Vectoring_2024_P.Constant5_Value_h)) && rtb_Compare) {
    y_0 = Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Saturate: '<S177>/Saturation' */
  if (rtb_DeadZone > Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit)
  {
    rtb_Imax = Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit;
  } else if (rtb_DeadZone <
             Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit) {
    rtb_Imax = Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit;
  } else {
    rtb_Imax = rtb_DeadZone;
  }

  /* End of Saturate: '<S177>/Saturation' */

  /* MinMax: '<S31>/Min' */
  if ((!(rtb_Imax <= Torque_Vectoring_2024_P.TC_MAX_CUT)) && tmp_1) {
    rtb_Imax = Torque_Vectoring_2024_P.TC_MAX_CUT;
  }

  /* MinMax: '<S31>/Min1' incorporates:
   *  Constant: '<S31>/Constant5'
   */
  if ((!(rtb_Imax >= Torque_Vectoring_2024_P.Constant5_Value_h)) && rtb_Compare)
  {
    rtb_Imax = Torque_Vectoring_2024_P.Constant5_Value_h;
  }

  /* Gain: '<Root>/Gain1' incorporates:
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = (real_T)
    Torque_Vectoring_2024_P.Gain1_Gain_l * rtb_Saturation5_idx_0;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_TmpSignalConversionAtMathFunctionInport1_c >
      Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    rtb_TmpSignalConversionAtMathFunctionInport1_c =
      Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (rtb_TmpSignalConversionAtMathFunctionInport1_c <
             Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    rtb_TmpSignalConversionAtMathFunctionInport1_c =
      Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S10>/Gain11' incorporates:
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   */
  rtb_Saturation4 = rtb_TmpSignalConversionAtMathFunctionInport1_c *
    rtb_Saturation_e_idx_0 * rtb_Gain3_o;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation4) || rtIsNaN
      (rtb_Saturation4)) {
    rtb_Saturation4 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S8>/Constant'
   *  MinMax: '<S31>/Min1'
   *  Sum: '<S8>/Sum'
   */
  rtb_Saturation_e_idx_0 = (Torque_Vectoring_2024_P.Constant_Value_a - y) *
    rtb_B_idx_0;

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation4 <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = rtb_Saturation4;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   */
  rtb_B_idx_0 = rtb_Saturation_e_idx_0 * Torque_Vectoring_2024_Y.T_pos[0];

  /* Gain: '<Root>/Gain1' incorporates:
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[1] = (real_T)
    Torque_Vectoring_2024_P.Gain1_Gain_l * rtb_Saturation5_idx_1;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_TmpSignalConversionAtMathFunctionInport1_g >
      Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    rtb_TmpSignalConversionAtMathFunctionInport1_g =
      Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (rtb_TmpSignalConversionAtMathFunctionInport1_g <
             Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    rtb_TmpSignalConversionAtMathFunctionInport1_g =
      Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S10>/Gain11' incorporates:
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   */
  rtb_Saturation4 = rtb_TmpSignalConversionAtMathFunctionInport1_g *
    rtb_Saturation_e_idx_1 * rtb_Gain3_o;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation4) || rtIsNaN
      (rtb_Saturation4)) {
    rtb_Saturation4 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S8>/Constant'
   *  MinMax: '<S31>/Min1'
   *  Sum: '<S8>/Sum'
   */
  rtb_Saturation_e_idx_0 = (Torque_Vectoring_2024_P.Constant_Value_a -
    rtb_Saturation8) * rtb_B_idx_1;

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation4 <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = rtb_Saturation4;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   */
  rtb_Saturation_e_idx_1 = rtb_Saturation_e_idx_0 *
    Torque_Vectoring_2024_Y.T_pos[1];

  /* Gain: '<Root>/Gain1' incorporates:
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[2] = (real_T)
    Torque_Vectoring_2024_P.Gain1_Gain_l * rtb_Saturation5_idx_2;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_omega_e > Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    rtb_omega_e = Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (rtb_omega_e < Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    rtb_omega_e = Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S10>/Gain11' incorporates:
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   */
  rtb_Saturation4 = rtb_omega_e * rtb_Saturation_e_idx_2 * rtb_Gain3_o;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation4) || rtIsNaN
      (rtb_Saturation4)) {
    rtb_Saturation4 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S8>/Constant'
   *  MinMax: '<S31>/Min1'
   *  Sum: '<S8>/Sum'
   */
  rtb_Saturation_e_idx_0 = (Torque_Vectoring_2024_P.Constant_Value_a - y_0) *
    rtb_B_idx_2;

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation4 <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = rtb_Saturation4;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   */
  rtb_Saturation_e_idx_2 = rtb_Saturation_e_idx_0 *
    Torque_Vectoring_2024_Y.T_pos[2];

  /* Gain: '<Root>/Gain1' incorporates:
   *  Memory: '<S14>/Memory'
   */
  Torque_Vectoring_2024_Y.T_pos[3] = (real_T)
    Torque_Vectoring_2024_P.Gain1_Gain_l * rtb_Saturation5_h;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_Product13_h > Torque_Vectoring_2024_P.Saturation1_UpperSat) {
    rtb_Product13_h = Torque_Vectoring_2024_P.Saturation1_UpperSat;
  } else if (rtb_Product13_h < Torque_Vectoring_2024_P.Saturation1_LowerSat) {
    rtb_Product13_h = Torque_Vectoring_2024_P.Saturation1_LowerSat;
  }

  /* Gain: '<S10>/Gain11' incorporates:
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   */
  rtb_Saturation4 = rtb_Product13_h * rtb_Saturation1_j_idx_3 * rtb_Gain3_o;

  /* MinMax: '<Root>/Min' */
  if ((Torque_Vectoring_2024_P.T_max <= rtb_Saturation4) || rtIsNaN
      (rtb_Saturation4)) {
    rtb_Saturation4 = Torque_Vectoring_2024_P.T_max;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<S8>/Constant'
   *  MinMax: '<S31>/Min1'
   *  Sum: '<S8>/Sum'
   */
  rtb_Saturation_e_idx_0 = (Torque_Vectoring_2024_P.Constant_Value_a - rtb_Imax)
    * rtb_B_idx_3;

  /* MinMax: '<Root>/Min' */
  if ((rtb_Saturation4 <= rtb_Saturation_e_idx_0) || rtIsNaN
      (rtb_Saturation_e_idx_0)) {
    rtb_Saturation_e_idx_0 = rtb_Saturation4;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   */
  rtb_Saturation1_j_idx_3 = rtb_Saturation_e_idx_0 *
    Torque_Vectoring_2024_Y.T_pos[3];

  /* Sum: '<S22>/Add' */
  rtb_Saturation_e_idx_0 = ((rtb_B_idx_0 + rtb_Saturation_e_idx_1) +
    rtb_Saturation_e_idx_2) + rtb_Saturation1_j_idx_3;

  /* MinMax: '<S22>/Max' incorporates:
   *  Constant: '<S22>/Constant'
   */
  if ((rtb_Saturation_e_idx_0 >= Torque_Vectoring_2024_P.Constant_Value_an) ||
      rtIsNaN(Torque_Vectoring_2024_P.Constant_Value_an)) {
    rtb_Saturation4 = rtb_Saturation_e_idx_0;
  } else {
    rtb_Saturation4 = Torque_Vectoring_2024_P.Constant_Value_an;
  }

  /* End of MinMax: '<S22>/Max' */

  /* MinMax: '<S22>/Min' */
  if ((!(rtb_Saturation_e_idx_0 <= Torque_Vectoring_2024_P.Pmax)) && (!rtIsNaN
       (Torque_Vectoring_2024_P.Pmax))) {
    rtb_Saturation_e_idx_0 = Torque_Vectoring_2024_P.Pmax;
  }

  /* End of MinMax: '<S22>/Min' */

  /* MinMax: '<S4>/Max' incorporates:
   *  Constant: '<S4>/Constant'
   *  Product: '<S22>/Divide'
   */
  rtb_Compare = rtIsNaN(Torque_Vectoring_2024_P.Constant_Value_k);
  if ((Torque_Vectoring_2024_Y.T_pos[0] >=
       Torque_Vectoring_2024_P.Constant_Value_k) || rtb_Compare) {
    rtb_Gain3_o = Torque_Vectoring_2024_Y.T_pos[0];
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_P.Constant_Value_k;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Memory: '<S14>/Memory'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_Y.T_pos[0] = rtb_B_idx_0 / rtb_Saturation4 *
    rtb_Saturation_e_idx_0 / rtb_Gain3_o * (real_T)
    (Torque_Vectoring_2024_Y.T_pos[0] <=
     Torque_Vectoring_2024_P.Constant1_Value_m);

  /* Outport: '<Root>/TC_CUT' incorporates:
   *  MinMax: '<S31>/Min1'
   */
  Torque_Vectoring_2024_Y.TC_CUT[0] = y;

  /* MinMax: '<S4>/Max' incorporates:
   *  Constant: '<S4>/Constant'
   *  Product: '<S22>/Divide'
   */
  if ((Torque_Vectoring_2024_Y.T_pos[1] >=
       Torque_Vectoring_2024_P.Constant_Value_k) || rtb_Compare) {
    rtb_Gain3_o = Torque_Vectoring_2024_Y.T_pos[1];
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_P.Constant_Value_k;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Memory: '<S14>/Memory'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_Y.T_pos[1] = rtb_Saturation_e_idx_1 / rtb_Saturation4 *
    rtb_Saturation_e_idx_0 / rtb_Gain3_o * (real_T)
    (Torque_Vectoring_2024_Y.T_pos[1] <=
     Torque_Vectoring_2024_P.Constant1_Value_m);

  /* Outport: '<Root>/TC_CUT' incorporates:
   *  MinMax: '<S31>/Min1'
   */
  Torque_Vectoring_2024_Y.TC_CUT[1] = rtb_Saturation8;

  /* MinMax: '<S4>/Max' incorporates:
   *  Constant: '<S4>/Constant'
   *  Product: '<S22>/Divide'
   */
  if ((Torque_Vectoring_2024_Y.T_pos[2] >=
       Torque_Vectoring_2024_P.Constant_Value_k) || rtb_Compare) {
    rtb_Gain3_o = Torque_Vectoring_2024_Y.T_pos[2];
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_P.Constant_Value_k;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Memory: '<S14>/Memory'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_Y.T_pos[2] = rtb_Saturation_e_idx_2 / rtb_Saturation4 *
    rtb_Saturation_e_idx_0 / rtb_Gain3_o * (real_T)
    (Torque_Vectoring_2024_Y.T_pos[2] <=
     Torque_Vectoring_2024_P.Constant1_Value_m);

  /* Outport: '<Root>/TC_CUT' incorporates:
   *  MinMax: '<S31>/Min1'
   */
  Torque_Vectoring_2024_Y.TC_CUT[2] = y_0;

  /* MinMax: '<S4>/Max' incorporates:
   *  Constant: '<S4>/Constant'
   *  Product: '<S22>/Divide'
   */
  if ((Torque_Vectoring_2024_Y.T_pos[3] >=
       Torque_Vectoring_2024_P.Constant_Value_k) || rtb_Compare) {
    rtb_Gain3_o = Torque_Vectoring_2024_Y.T_pos[3];
  } else {
    rtb_Gain3_o = Torque_Vectoring_2024_P.Constant_Value_k;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Memory: '<S14>/Memory'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  Torque_Vectoring_2024_Y.T_pos[3] = rtb_Saturation1_j_idx_3 / rtb_Saturation4 *
    rtb_Saturation_e_idx_0 / rtb_Gain3_o * (real_T)
    (Torque_Vectoring_2024_Y.T_pos[3] <=
     Torque_Vectoring_2024_P.Constant1_Value_m);

  /* Outport: '<Root>/TC_CUT' incorporates:
   *  MinMax: '<S31>/Min1'
   */
  Torque_Vectoring_2024_Y.TC_CUT[3] = rtb_Imax;

  /* SignalConversion generated from: '<S14>/Vector Concatenate' incorporates:
   *  Constant: '<S14>/Constant'
   */
  rtb_A_k[0] = Torque_Vectoring_2024_P.Constant_Value_nt;

  /* Gain: '<S14>/Gain' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[1] = (real_T)Torque_Vectoring_2024_P.Gain_Gain_i *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput;

  /* Gain: '<S14>/Gain1' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_A_k[2] = (real_T)Torque_Vectoring_2024_P.Gain1_Gain_d *
    Torque_Vectoring_2024_DW.Memory4_PreviousInput;

  /* SignalConversion generated from: '<S14>/Vector Concatenate1' incorporates:
   *  Constant: '<S14>/Constant'
   */
  rtb_A_k[3] = Torque_Vectoring_2024_P.Constant_Value_nt;

  /* Product: '<S14>/Product2' incorporates:
   *  Concatenate: '<S14>/Vector Concatenate2'
   *  Constant: '<S14>/Constant'
   *  Math: '<S14>/Transpose'
   *  Memory: '<S14>/Memory'
   */
  for (idxDelay = 0; idxDelay < 2; idxDelay++) {
    tmp[idxDelay] = 0.0;
    tmp[idxDelay] += Torque_Vectoring_2024_DW.Memory_PreviousInput_d[idxDelay] *
      Torque_Vectoring_2024_P.Constant_Value_nt;
    rtb_Gain3_o = Torque_Vectoring_2024_DW.Memory_PreviousInput_d[idxDelay + 2];
    tmp[idxDelay] += rtb_Gain3_o * rtb_A_k[2];
    tmp[idxDelay + 2] = 0.0;
    tmp[idxDelay + 2] +=
      Torque_Vectoring_2024_DW.Memory_PreviousInput_d[idxDelay] * rtb_A_k[1];
    tmp[idxDelay + 2] += rtb_Gain3_o * Torque_Vectoring_2024_P.Constant_Value_nt;
  }

  /* Product: '<S14>/Product4' */
  rtb_Gain3_o = 0.0;
  for (idxDelay = 0; idxDelay < 2; idxDelay++) {
    /* Sum: '<S14>/Add' incorporates:
     *  Concatenate: '<S14>/Vector Concatenate2'
     *  Constant: '<S14>/Constant7'
     *  Product: '<S14>/Product2'
     */
    rtb_Saturation1_j_idx_3 = rtb_A_k[idxDelay + 2];
    rtb_Imax = (rtb_Saturation1_j_idx_3 * tmp[1] + rtb_A_k[idxDelay] * tmp[0]) +
      Torque_Vectoring_2024_P.Q[idxDelay];
    rtb_P_k_m[idxDelay] = rtb_Imax;

    /* Product: '<S14>/Product4' incorporates:
     *  Constant: '<S14>/Constant4'
     *  Math: '<S14>/Transpose2'
     */
    rtb_Saturation4 = rtb_Imax * Torque_Vectoring_2024_P.Constant4_Value_g[0];

    /* Sum: '<S14>/Add' incorporates:
     *  Concatenate: '<S14>/Vector Concatenate2'
     *  Constant: '<S14>/Constant7'
     *  Product: '<S14>/Product2'
     */
    rtb_Imax = (rtb_Saturation1_j_idx_3 * tmp[3] + rtb_A_k[idxDelay] * tmp[2]) +
      Torque_Vectoring_2024_P.Q[idxDelay + 2];
    rtb_P_k_m[idxDelay + 2] = rtb_Imax;

    /* Product: '<S14>/Product4' incorporates:
     *  Constant: '<S14>/Constant4'
     *  Math: '<S14>/Transpose2'
     *  Product: '<S14>/Product3'
     */
    rtb_Saturation4 += rtb_Imax * Torque_Vectoring_2024_P.Constant4_Value_g[1];
    rtb_Gain3_o += Torque_Vectoring_2024_P.Constant4_Value_g[idxDelay] *
      rtb_Saturation4;
    rtb_K_k[idxDelay] = rtb_Saturation4;
  }

  /* Sum: '<S14>/Add2' incorporates:
   *  Constant: '<S14>/Constant5'
   *  Product: '<S14>/Product4'
   */
  rtb_Saturation_e_idx_0 = rtb_Gain3_o + Torque_Vectoring_2024_P.R1;

  /* Product: '<S14>/Divide' incorporates:
   *  Product: '<S14>/Product3'
   */
  rtb_Saturation_e_idx_1 = rtb_K_k[0] / rtb_Saturation_e_idx_0;
  rtb_Saturation_e_idx_2 = rtb_K_k[1] / rtb_Saturation_e_idx_0;

  /* Saturate: '<S7>/Saturation1' */
  if (rtb_Saturation5_idx_0 > Torque_Vectoring_2024_P.Saturation1_UpperSat_m) {
    rtb_Gain3_o = Torque_Vectoring_2024_P.Saturation1_UpperSat_m;
  } else if (rtb_Saturation5_idx_0 <
             Torque_Vectoring_2024_P.Saturation1_LowerSat_p) {
    rtb_Gain3_o = Torque_Vectoring_2024_P.Saturation1_LowerSat_p;
  } else {
    rtb_Gain3_o = rtb_Saturation5_idx_0;
  }

  if (rtb_Saturation5_idx_1 > Torque_Vectoring_2024_P.Saturation1_UpperSat_m) {
    rtb_B_idx_2 = Torque_Vectoring_2024_P.Saturation1_UpperSat_m;
  } else if (rtb_Saturation5_idx_1 <
             Torque_Vectoring_2024_P.Saturation1_LowerSat_p) {
    rtb_B_idx_2 = Torque_Vectoring_2024_P.Saturation1_LowerSat_p;
  } else {
    rtb_B_idx_2 = rtb_Saturation5_idx_1;
  }

  if (rtb_Saturation5_idx_2 > Torque_Vectoring_2024_P.Saturation1_UpperSat_m) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.Saturation1_UpperSat_m;
  } else if (rtb_Saturation5_idx_2 <
             Torque_Vectoring_2024_P.Saturation1_LowerSat_p) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.Saturation1_LowerSat_p;
  } else {
    rtb_Saturation1_j_idx_3 = rtb_Saturation5_idx_2;
  }

  if (rtb_Saturation5_h > Torque_Vectoring_2024_P.Saturation1_UpperSat_m) {
    rtb_Imax = Torque_Vectoring_2024_P.Saturation1_UpperSat_m;
  } else if (rtb_Saturation5_h < Torque_Vectoring_2024_P.Saturation1_LowerSat_p)
  {
    rtb_Imax = Torque_Vectoring_2024_P.Saturation1_LowerSat_p;
  } else {
    rtb_Imax = rtb_Saturation5_h;
  }

  /* Sum: '<S7>/Add1' incorporates:
   *  Saturate: '<S7>/Saturation1'
   */
  rtb_Saturation_e_idx_0 = ((rtb_Gain3_o + rtb_B_idx_2) +
    rtb_Saturation1_j_idx_3) + rtb_Imax;

  /* Saturate: '<Root>/Saturation8' incorporates:
   *  Inport: '<Root>/voltage'
   */
  if (Torque_Vectoring_2024_U.voltage >
      Torque_Vectoring_2024_P.Saturation8_UpperSat) {
    rtb_Saturation8 = Torque_Vectoring_2024_P.Saturation8_UpperSat;
  } else if (Torque_Vectoring_2024_U.voltage <
             Torque_Vectoring_2024_P.Saturation8_LowerSat) {
    rtb_Saturation8 = Torque_Vectoring_2024_P.Saturation8_LowerSat;
  } else {
    rtb_Saturation8 = Torque_Vectoring_2024_U.voltage;
  }

  /* End of Saturate: '<Root>/Saturation8' */

  /* Saturate: '<Root>/Saturation4' incorporates:
   *  Inport: '<Root>/regen paddle'
   */
  if (Torque_Vectoring_2024_U.regenpaddle >
      Torque_Vectoring_2024_P.Saturation4_UpperSat) {
    rtb_Saturation4 = Torque_Vectoring_2024_P.Saturation4_UpperSat;
  } else if (Torque_Vectoring_2024_U.regenpaddle <
             Torque_Vectoring_2024_P.Saturation4_LowerSat) {
    rtb_Saturation4 = Torque_Vectoring_2024_P.Saturation4_LowerSat;
  } else {
    rtb_Saturation4 = Torque_Vectoring_2024_U.regenpaddle;
  }

  /* End of Saturate: '<Root>/Saturation4' */

  /* Sum: '<S24>/Add1' incorporates:
   *  Constant: '<S24>/Constant'
   *  Delay: '<S24>/Delay1'
   *  Memory: '<S24>/Memory'
   *  Product: '<S24>/Product2'
   */
  Torque_Vectoring_2024_DW.Memory_PreviousInput_b +=
    Torque_Vectoring_2024_P.Constant_Value_nb * (real_T)
    Torque_Vectoring_2024_DW.Delay1_DSTATE[0];

  /* RelationalOperator: '<S23>/Compare' incorporates:
   *  Constant: '<S23>/Constant'
   */
  rtb_Compare = (rtb_Saturation4 > Torque_Vectoring_2024_P.Constant_Value);

  /* Gain: '<S6>/Gain' incorporates:
   *  Constant: '<S6>/Max battery voltage'
   *  Sum: '<S6>/Subtract'
   */
  rtb_Saturation1_j_idx_3 = 1.0 / Torque_Vectoring_2024_P.R_batt *
    (Torque_Vectoring_2024_P.Voltage - rtb_Saturation8);

  /* Product: '<S6>/Product' incorporates:
   *  Constant: '<S6>/Constant'
   */
  rtb_Saturation4 *= Torque_Vectoring_2024_P.maxCurrent;

  /* MinMax: '<S6>/Imax' */
  if ((rtb_Saturation1_j_idx_3 <= rtb_Saturation4) || rtIsNaN(rtb_Saturation4))
  {
    rtb_Saturation4 = rtb_Saturation1_j_idx_3;
  }

  /* Sum: '<S24>/Add' incorporates:
   *  Constant: '<S24>/Constant1'
   */
  rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.maxCurrent -
    Torque_Vectoring_2024_DW.Memory_PreviousInput_b;

  /* Saturate: '<S24>/Saturation' */
  if (rtb_Saturation1_j_idx_3 > Torque_Vectoring_2024_P.maxCurrent) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.maxCurrent;
  } else if (rtb_Saturation1_j_idx_3 < Torque_Vectoring_2024_P.directCurrent) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.directCurrent;
  }

  /* Product: '<S24>/Product' incorporates:
   *  Saturate: '<S24>/Saturation'
   */
  rtb_Imax = rtb_Saturation1_j_idx_3 * (real_T)rtb_Compare;

  /* MinMax: '<S6>/Imax' */
  if ((rtb_Saturation4 <= rtb_Imax) || rtIsNaN(rtb_Imax)) {
    rtb_Imax = rtb_Saturation4;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Product: '<S6>/Product1'
   *  Sum: '<S6>/Tot voltage'
   */
  rtb_Imax = (Torque_Vectoring_2024_P.R_batt * rtb_Imax + rtb_Saturation8) *
    rtb_Imax * (1.0 / Torque_Vectoring_2024_P.eta_inv);

  /* RelationalOperator: '<S25>/Equal1' incorporates:
   *  Constant: '<S25>/Constant'
   */
  rtb_fw_inactive = (rtb_Imax != Torque_Vectoring_2024_P.Constant_Value_e);

  /* Gain: '<S25>/Gain5' */
  rtb_omega_e = Torque_Vectoring_2024_P.n_phase * rtb_Saturation_e_idx_0;

  /* Gain: '<S28>/Gain4' incorporates:
   *  Constant: '<S28>/Constant'
   *  Gain: '<S28>/Gain6'
   *  Sum: '<S28>/Add1'
   */
  rtb_Saturation4 = ((Torque_Vectoring_2024_P.Ld - Torque_Vectoring_2024_P.Lq) /
                     Torque_Vectoring_2024_P.t_alpha * rtb_omega_e +
                     Torque_Vectoring_2024_P.R_phase * 1.0285359040362212) *
    Torque_Vectoring_2024_P.Gain4_Gain;

  /* Gain: '<S28>/Gain3' */
  rtb_B_idx_2 = 1.5 * Torque_Vectoring_2024_P.flux_mg * rtb_omega_e;

  /* MATLAB Function: '<S28>/MATLAB Function' incorporates:
   *  Gain: '<S28>/Gain2'
   */
  rtb_B_idx_1 = sqrt(rtb_B_idx_2 * rtb_B_idx_2 - 4.0 * rtb_Saturation4 *
                     (Torque_Vectoring_2024_P.Gain2_Gain * rtb_Imax));
  rtb_Saturation1_j_idx_3 = (-rtb_B_idx_2 + rtb_B_idx_1) / (2.0 *
    rtb_Saturation4);
  rtb_Saturation4 = (-rtb_B_idx_2 - rtb_B_idx_1) / (2.0 * rtb_Saturation4);
  if ((rtb_Saturation1_j_idx_3 >= rtb_Saturation4) || rtIsNaN(rtb_Saturation4))
  {
    rtb_Saturation4 = rtb_Saturation1_j_idx_3;
  }

  /* End of MATLAB Function: '<S28>/MATLAB Function' */

  /* Gain: '<S28>/Gain1' */
  rtb_B_idx_2 = 1.0 / Torque_Vectoring_2024_P.t_alpha * rtb_Saturation4;

  /* Math: '<S28>/Power1' */
  rtb_B_idx_2 *= rtb_B_idx_2;

  /* MATLAB Function: '<S25>/MATLAB Function' */
  if (rtb_fw_inactive) {
    rtb_Saturation1_j_idx_3 = 0.0;
    rtb_omega_e = 0.0;
  } else {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.flux_mg *
      Torque_Vectoring_2024_P.Lq;
    rtb_B_idx_1 = Torque_Vectoring_2024_P.Lq * Torque_Vectoring_2024_P.Ilim;
    rtb_omega_e = rtb_Imax / 154.5855345755223 / rtb_omega_e;
    rtb_TmpSignalConversionAtMathFunctionInport1_g = Torque_Vectoring_2024_P.Lq *
      Torque_Vectoring_2024_P.Lq - Torque_Vectoring_2024_P.Ld *
      Torque_Vectoring_2024_P.Ld;
    rtb_Saturation1_j_idx_3 = (Torque_Vectoring_2024_P.flux_mg *
      Torque_Vectoring_2024_P.Ld - sqrt((rtb_B_idx_1 * rtb_B_idx_1 - rtb_omega_e
      * rtb_omega_e) * rtb_TmpSignalConversionAtMathFunctionInport1_g +
      rtb_Saturation1_j_idx_3 * rtb_Saturation1_j_idx_3)) /
      rtb_TmpSignalConversionAtMathFunctionInport1_g;
    rtb_Saturation1_j_idx_3 *= rtb_Saturation1_j_idx_3;
    rtb_omega_e = Torque_Vectoring_2024_P.Ilim * Torque_Vectoring_2024_P.Ilim -
      rtb_Saturation1_j_idx_3 * rtb_Saturation1_j_idx_3;
  }

  /* End of MATLAB Function: '<S25>/MATLAB Function' */

  /* Switch: '<S25>/Switch1' incorporates:
   *  Gain: '<S25>/Gain7'
   *  RelationalOperator: '<S25>/Equal'
   *  Switch: '<S25>/Switch'
   */
  if (Torque_Vectoring_2024_P.Gain7_Gain * rtb_Imax < rtb_Saturation_e_idx_0) {
    /* Sum: '<S28>/Add2' incorporates:
     *  Constant: '<S28>/Constant1'
     */
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.Constant1_Value -
      rtb_B_idx_2;

    /* Math: '<S28>/Power2' */
    rtb_omega_e = rtb_Saturation4 * rtb_Saturation4;

    /* MinMax: '<S28>/Max' */
    if ((rtb_Saturation1_j_idx_3 >= rtb_omega_e) || rtIsNaN(rtb_omega_e)) {
      rtb_omega_e = rtb_Saturation1_j_idx_3;
    }

    /* End of MinMax: '<S28>/Max' */
    rtb_Saturation1_j_idx_3 = rtb_B_idx_2;
  }

  /* End of Switch: '<S25>/Switch1' */

  /* Product: '<S7>/Tmax' incorporates:
   *  Gain: '<S25>/Gain'
   *  Product: '<S25>/Divide'
   *  Sum: '<S25>/Add'
   *  Sum: '<S7>/Ptot'
   *  Switch: '<S25>/Switch'
   */
  rtb_B_idx_2 = (1.5 * Torque_Vectoring_2024_P.R_phase *
                 (rtb_Saturation1_j_idx_3 + rtb_omega_e) * (real_T)
                 rtb_fw_inactive + rtb_Imax) / rtb_Saturation_e_idx_0;

  /* Gain: '<S7>/Gain1' */
  rtb_Saturation_e_idx_0 *= Torque_Vectoring_2024_P.Gain1_Gain_i;

  /* MinMax: '<S7>/Min' */
  if ((Torque_Vectoring_2024_P.T_regen_max <= rtb_B_idx_2) || rtIsNaN
      (rtb_B_idx_2)) {
    rtb_B_idx_2 = Torque_Vectoring_2024_P.T_regen_max;
  }

  /* Sum: '<S26>/Subtract1' incorporates:
   *  Constant: '<S26>/Constant'
   *  Gain: '<S26>/Gain'
   */
  rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.Gain_Gain_k *
    rtb_Saturation_e_idx_0 - Torque_Vectoring_2024_P.Constant_Value_f;

  /* Saturate: '<S26>/Saturation' */
  if (rtb_Saturation1_j_idx_3 > Torque_Vectoring_2024_P.Saturation_UpperSat_a) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.Saturation_UpperSat_a;
  } else if (rtb_Saturation1_j_idx_3 <
             Torque_Vectoring_2024_P.Saturation_LowerSat_i) {
    rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.Saturation_LowerSat_i;
  }

  /* Sum: '<S26>/Subtract' incorporates:
   *  Constant: '<S26>/Constant1'
   *  Gain: '<S26>/Gain1'
   *  Saturate: '<S26>/Saturation'
   */
  rtb_Saturation4 = Torque_Vectoring_2024_P.Constant1_Value_ca -
    Torque_Vectoring_2024_P.Gain1_Gain_f * rtb_Saturation1_j_idx_3;

  /* MinMax: '<S7>/Min' */
  if ((rtb_B_idx_2 <= rtb_Saturation4) || rtIsNaN(rtb_Saturation4)) {
    rtb_Saturation4 = rtb_B_idx_2;
  }

  /* Product: '<S7>/Divide1' incorporates:
   *  Constant: '<S7>/Constant4'
   *  MinMax: '<S7>/Min'
   *  RelationalOperator: '<S7>/GreaterThan'
   */
  rtb_omega_e = (real_T)(rtb_Saturation_e_idx_0 >
    Torque_Vectoring_2024_P.Constant4_Value_o) * rtb_Saturation4;

  /* Sum: '<Root>/Add5' incorporates:
   *  Constant: '<Root>/Constant2'
   *  Gain: '<Root>/Gain12'
   */
  rtb_B_idx_2 = (1.0 - Torque_Vectoring_2024_P.offset_brake_csi) * rtb_Csi +
    Torque_Vectoring_2024_P.offset_brake_csi;

  /* Saturate: '<Root>/Saturation7' incorporates:
   *  Inport: '<Root>/brake pressure front'
   */
  if (Torque_Vectoring_2024_U.brakepressurefront >
      Torque_Vectoring_2024_P.Saturation7_UpperSat) {
    tmp_0 = Torque_Vectoring_2024_P.Saturation7_UpperSat;
  } else if (Torque_Vectoring_2024_U.brakepressurefront <
             Torque_Vectoring_2024_P.Saturation7_LowerSat) {
    tmp_0 = Torque_Vectoring_2024_P.Saturation7_LowerSat;
  } else {
    tmp_0 = Torque_Vectoring_2024_U.brakepressurefront;
  }

  /* Saturate: '<Root>/Saturation9' incorporates:
   *  Inport: '<Root>/brake pressure rear'
   */
  if (Torque_Vectoring_2024_U.brakepressurerear >
      Torque_Vectoring_2024_P.Saturation9_UpperSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation9_UpperSat;
  } else if (Torque_Vectoring_2024_U.brakepressurerear <
             Torque_Vectoring_2024_P.Saturation9_LowerSat) {
    rtb_Saturation5_h = Torque_Vectoring_2024_P.Saturation9_LowerSat;
  } else {
    rtb_Saturation5_h = Torque_Vectoring_2024_U.brakepressurerear;
  }

  /* Product: '<S27>/Divide3' incorporates:
   *  Constant: '<S27>/Constant3'
   *  Gain: '<S27>/Gain'
   *  Gain: '<S27>/Gain1'
   *  Product: '<S27>/Divide'
   *  Product: '<S27>/Divide1'
   *  Product: '<S27>/Divide2'
   *  Saturate: '<Root>/Saturation7'
   *  Saturate: '<Root>/Saturation9'
   *  Sum: '<S27>/Add'
   *  Sum: '<S27>/Add1'
   */
  rtb_B_idx_2 = rtb_omega_e * rtb_B_idx_2 /
    (((Torque_Vectoring_2024_P.Constant3_Value_k - rtb_B_idx_2) * ((real_T)
       Torque_Vectoring_2024_P.Gain_Gain_o * tmp_0) + rtb_omega_e) - (real_T)
     Torque_Vectoring_2024_P.Gain1_Gain_c * rtb_Saturation5_h * rtb_B_idx_2);

  /* Gain: '<S7>/Gain3' */
  rtb_Saturation1_j_idx_3 = Torque_Vectoring_2024_P.Gain3_Gain_o * rtb_omega_e;

  /* Outport: '<Root>/T_neg' incorporates:
   *  Gain: '<S7>/Gain3'
   */
  Torque_Vectoring_2024_Y.T_neg[0] = rtb_Saturation1_j_idx_3;
  Torque_Vectoring_2024_Y.T_neg[1] = rtb_Saturation1_j_idx_3;

  /* Gain: '<S7>/Gain3' incorporates:
   *  Constant: '<S27>/Constant5'
   *  Product: '<S27>/Divide4'
   *  Product: '<S27>/Product3'
   *  Sum: '<S27>/Add6'
   */
  rtb_Saturation1_j_idx_3 = (Torque_Vectoring_2024_P.Constant5_Value_c -
    rtb_B_idx_2) * rtb_omega_e / rtb_B_idx_2 *
    Torque_Vectoring_2024_P.Gain3_Gain_o;

  /* Outport: '<Root>/T_neg' incorporates:
   *  Gain: '<S7>/Gain3'
   */
  Torque_Vectoring_2024_Y.T_neg[2] = rtb_Saturation1_j_idx_3;
  Torque_Vectoring_2024_Y.T_neg[3] = rtb_Saturation1_j_idx_3;

  /* MinMax: '<S15>/Max' incorporates:
   *  MinMax: '<S15>/Min'
   */
  tmp_1 = rtIsNaN(rtb_vims_idx_1);
  if ((rtb_Integrator_h >= rtb_vims_idx_1) || tmp_1) {
    rtb_Imax = rtb_Integrator_h;
  } else {
    rtb_Imax = rtb_vims_idx_1;
  }

  /* MinMax: '<S15>/Min' */
  if ((rtb_Integrator_h <= rtb_vims_idx_1) || tmp_1) {
    rtb_Saturation4 = rtb_Integrator_h;
  } else {
    rtb_Saturation4 = rtb_vims_idx_1;
  }

  /* MinMax: '<S15>/Max' incorporates:
   *  MinMax: '<S15>/Min'
   */
  tmp_1 = !rtIsNaN(rtb_vims_idx_2);
  if ((!(rtb_Imax >= rtb_vims_idx_2)) && tmp_1) {
    rtb_Imax = rtb_vims_idx_2;
  }

  /* MinMax: '<S15>/Min' */
  if ((!(rtb_Saturation4 <= rtb_vims_idx_2)) && tmp_1) {
    rtb_Saturation4 = rtb_vims_idx_2;
  }

  /* Sum: '<S17>/Sum' incorporates:
   *  Concatenate: '<S14>/Vector Concatenate2'
   *  Constant: '<S14>/Constant'
   *  Constant: '<S14>/Constant1'
   *  Gain: '<S14>/Gain3'
   *  Memory: '<S3>/Memory2'
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   */
  rtb_Saturation1_j_idx_3 = (Torque_Vectoring_2024_P.Gain3_Gain *
    Torque_Vectoring_2024_P.Constant1_Value_ir[0] *
    Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] +
    Torque_Vectoring_2024_P.Gain3_Gain *
    Torque_Vectoring_2024_P.Constant1_Value_ir[2] *
    Torque_Vectoring_2024_DW.Memory2_PreviousInput[1]) +
    (Torque_Vectoring_2024_P.Constant_Value_nt *
     Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] +
     Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] * rtb_A_k[2]);
  rtb_Csi = (Torque_Vectoring_2024_P.Gain3_Gain *
             Torque_Vectoring_2024_P.Constant1_Value_ir[1] *
             Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] +
             Torque_Vectoring_2024_P.Gain3_Gain *
             Torque_Vectoring_2024_P.Constant1_Value_ir[3] *
             Torque_Vectoring_2024_DW.Memory2_PreviousInput[1]) +
    (Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] * rtb_A_k[1] +
     Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] *
     Torque_Vectoring_2024_P.Constant_Value_nt);

  /* MinMax: '<S15>/Min' incorporates:
   *  MinMax: '<S15>/Max'
   */
  tmp_1 = !rtIsNaN(rtb_vims_idx_3);
  if ((!(rtb_Saturation4 <= rtb_vims_idx_3)) && tmp_1) {
    rtb_Saturation4 = rtb_vims_idx_3;
  }

  /* MinMax: '<S15>/Max' */
  if ((!(rtb_Imax >= rtb_vims_idx_3)) && tmp_1) {
    rtb_Imax = rtb_vims_idx_3;
  }

  /* Sum: '<S16>/Add' incorporates:
   *  Abs: '<S15>/Abs'
   *  Constant: '<S14>/Constant4'
   *  Constant: '<S18>/Constant'
   *  Constant: '<S19>/Constant'
   *  Constant: '<S20>/Constant'
   *  MinMax: '<S15>/Max'
   *  MinMax: '<S15>/Min'
   *  Product: '<S15>/Divide'
   *  Product: '<S15>/Product'
   *  Product: '<S15>/Product of Elements'
   *  Product: '<S16>/Product'
   *  RelationalOperator: '<S18>/Compare'
   *  RelationalOperator: '<S19>/Compare'
   *  RelationalOperator: '<S20>/Compare'
   *  Sum: '<S15>/Sum of Elements'
   *  Sum: '<S15>/Sum of Elements1'
   *  Sum: '<S15>/Sum of Elements2'
   *  Sum: '<S21>/Add1'
   */
  rtb_Exp4_idx_0 = (((((rtb_Product_idx_0 + rtb_Product_idx_1) +
                       rtb_Product_idx_2) + rtb_vims_idx_3 * rtb_Exp4_g) /
                     (((rtb_Exp4_idx_0 + rtb_Exp4_idx_1) + rtb_Exp4_idx_2) +
                      rtb_Exp4_g) * (real_T)(fabs(rtb_Saturation) <=
    Torque_Vectoring_2024_P.ax0) + (real_T)(rtb_Saturation >=
    Torque_Vectoring_2024_P.ax0) * rtb_Saturation4) + (real_T)(rtb_Saturation <
    -Torque_Vectoring_2024_P.ax0) * rtb_Imax) -
    (Torque_Vectoring_2024_P.Constant4_Value_g[0] * rtb_Saturation1_j_idx_3 +
     Torque_Vectoring_2024_P.Constant4_Value_g[1] * rtb_Csi);

  /* DeadZone: '<S163>/DeadZone' */
  if (rtb_DeadZone > Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit)
  {
    rtb_DeadZone -= Torque_Vectoring_2024_P.PIDController7_UpperSaturationLimit;
  } else if (rtb_DeadZone >=
             Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit) {
    rtb_DeadZone = 0.0;
  } else {
    rtb_DeadZone -= Torque_Vectoring_2024_P.PIDController7_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S163>/DeadZone' */

  /* Gain: '<S167>/Integral Gain' */
  rtb_B_idx_2 = Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Sliperror_idx_1;

  /* Switch: '<S161>/Switch1' incorporates:
   *  Constant: '<S161>/Clamping_zero'
   *  Constant: '<S161>/Constant'
   *  Constant: '<S161>/Constant2'
   *  RelationalOperator: '<S161>/fix for DT propagation issue'
   */
  if (rtb_DeadZone > Torque_Vectoring_2024_P.Clamping_zero_Value) {
    idxDelay = Torque_Vectoring_2024_P.Constant_Value_am;
  } else {
    idxDelay = Torque_Vectoring_2024_P.Constant2_Value_p;
  }

  /* Switch: '<S161>/Switch2' incorporates:
   *  Constant: '<S161>/Clamping_zero'
   *  Constant: '<S161>/Constant3'
   *  Constant: '<S161>/Constant4'
   *  RelationalOperator: '<S161>/fix for DT propagation issue1'
   */
  if (rtb_B_idx_2 > Torque_Vectoring_2024_P.Clamping_zero_Value) {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant3_Value_ob;
  } else {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant4_Value_c;
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
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value != rtb_DeadZone) && (idxDelay
       == Memory_PreviousInput_d_tmp)) {
    rtb_Exp4_idx_1 = Torque_Vectoring_2024_P.Constant1_Value_l;
  } else {
    rtb_Exp4_idx_1 = rtb_B_idx_2;
  }

  /* End of Switch: '<S161>/Switch' */

  /* DeadZone: '<S63>/DeadZone' */
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

  /* End of DeadZone: '<S63>/DeadZone' */

  /* Gain: '<S67>/Integral Gain' */
  rtb_B_idx_2 = Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Sliperror_idx_0;

  /* Switch: '<S61>/Switch1' incorporates:
   *  Constant: '<S61>/Clamping_zero'
   *  Constant: '<S61>/Constant'
   *  Constant: '<S61>/Constant2'
   *  RelationalOperator: '<S61>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_c > Torque_Vectoring_2024_P.Clamping_zero_Value_e) {
    idxDelay = Torque_Vectoring_2024_P.Constant_Value_hq;
  } else {
    idxDelay = Torque_Vectoring_2024_P.Constant2_Value_j;
  }

  /* Switch: '<S61>/Switch2' incorporates:
   *  Constant: '<S61>/Clamping_zero'
   *  Constant: '<S61>/Constant3'
   *  Constant: '<S61>/Constant4'
   *  RelationalOperator: '<S61>/fix for DT propagation issue1'
   */
  if (rtb_B_idx_2 > Torque_Vectoring_2024_P.Clamping_zero_Value_e) {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant3_Value_op;
  } else {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant4_Value_e;
  }

  /* Switch: '<S61>/Switch' incorporates:
   *  Constant: '<S61>/Clamping_zero'
   *  Constant: '<S61>/Constant1'
   *  Logic: '<S61>/AND3'
   *  RelationalOperator: '<S61>/Equal1'
   *  RelationalOperator: '<S61>/Relational Operator'
   *  Switch: '<S61>/Switch1'
   *  Switch: '<S61>/Switch2'
   */
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value_e != rtb_DeadZone_c) &&
      (idxDelay == Memory_PreviousInput_d_tmp)) {
    rtb_Exp4_idx_2 = Torque_Vectoring_2024_P.Constant1_Value_i;
  } else {
    rtb_Exp4_idx_2 = rtb_B_idx_2;
  }

  /* End of Switch: '<S61>/Switch' */

  /* DeadZone: '<S213>/DeadZone' */
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

  /* End of DeadZone: '<S213>/DeadZone' */

  /* Gain: '<S217>/Integral Gain' */
  rtb_B_idx_2 = Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Exp3;

  /* Switch: '<S211>/Switch1' incorporates:
   *  Constant: '<S211>/Clamping_zero'
   *  Constant: '<S211>/Constant'
   *  Constant: '<S211>/Constant2'
   *  RelationalOperator: '<S211>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_i > Torque_Vectoring_2024_P.Clamping_zero_Value_j) {
    idxDelay = Torque_Vectoring_2024_P.Constant_Value_ej;
  } else {
    idxDelay = Torque_Vectoring_2024_P.Constant2_Value_g;
  }

  /* Switch: '<S211>/Switch2' incorporates:
   *  Constant: '<S211>/Clamping_zero'
   *  Constant: '<S211>/Constant3'
   *  Constant: '<S211>/Constant4'
   *  RelationalOperator: '<S211>/fix for DT propagation issue1'
   */
  if (rtb_B_idx_2 > Torque_Vectoring_2024_P.Clamping_zero_Value_j) {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant3_Value_j;
  } else {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant4_Value_oj;
  }

  /* Switch: '<S211>/Switch' incorporates:
   *  Constant: '<S211>/Clamping_zero'
   *  Constant: '<S211>/Constant1'
   *  Logic: '<S211>/AND3'
   *  RelationalOperator: '<S211>/Equal1'
   *  RelationalOperator: '<S211>/Relational Operator'
   *  Switch: '<S211>/Switch1'
   *  Switch: '<S211>/Switch2'
   */
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value_j != rtb_DeadZone_i) &&
      (idxDelay == Memory_PreviousInput_d_tmp)) {
    rtb_DeadZone_i = Torque_Vectoring_2024_P.Constant1_Value_j;
  } else {
    rtb_DeadZone_i = rtb_B_idx_2;
  }

  /* End of Switch: '<S211>/Switch' */

  /* DeadZone: '<S113>/DeadZone' */
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

  /* End of DeadZone: '<S113>/DeadZone' */

  /* Gain: '<S117>/Integral Gain' */
  rtb_B_idx_2 = Torque_Vectoring_2024_P.TC_CL_I_R * rtb_Integrator_m;

  /* Outport: '<Root>/vx_est' incorporates:
   *  Delay: '<Root>/Delay'
   */
  Torque_Vectoring_2024_Y.vx_est = Torque_Vectoring_2024_DW.Delay_DSTATE;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] = rtb_Saturation;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  Torque_Vectoring_2024_DW.Memory2_PreviousInput[1] = rtb_Saturation1;

  /* Update for Delay: '<Root>/Delay' incorporates:
   *  Product: '<S14>/Divide'
   *  Product: '<S16>/Product1'
   *  Sum: '<S16>/Add1'
   */
  Torque_Vectoring_2024_DW.Delay_DSTATE = rtb_Saturation_e_idx_1 *
    rtb_Exp4_idx_0 + rtb_Saturation1_j_idx_3;

  /* Update for Memory: '<S3>/Memory1' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S13>/Constant'
   *  Constant: '<S3>/Constant'
   *  Product: '<S14>/Divide'
   *  Product: '<S16>/Product1'
   *  Product: '<S3>/Product'
   *  RelationalOperator: '<S13>/Compare'
   *  Sum: '<S16>/Add1'
   *  Sum: '<S3>/Add'
   */
  Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] = rtb_vxms;
  Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] = (rtb_Saturation_e_idx_2 *
    rtb_Exp4_idx_0 + rtb_Csi) * (Torque_Vectoring_2024_P.Constant_Value_er -
    (real_T)(fabsf(rtb_Saturation2) <= Torque_Vectoring_2024_P.r0));

  /* Update for Memory: '<S21>/Memory' */
  Torque_Vectoring_2024_DW.Memory_PreviousInput[0] = rtb_Integrator_h;
  Torque_Vectoring_2024_DW.Memory_PreviousInput[1] = rtb_vims_idx_1;
  Torque_Vectoring_2024_DW.Memory_PreviousInput[2] = rtb_vims_idx_2;
  Torque_Vectoring_2024_DW.Memory_PreviousInput[3] = rtb_vims_idx_3;

  /* Switch: '<S111>/Switch1' incorporates:
   *  Constant: '<S111>/Clamping_zero'
   *  Constant: '<S111>/Constant'
   *  Constant: '<S111>/Constant2'
   *  RelationalOperator: '<S111>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_l > Torque_Vectoring_2024_P.Clamping_zero_Value_m) {
    idxDelay = Torque_Vectoring_2024_P.Constant_Value_d;
  } else {
    idxDelay = Torque_Vectoring_2024_P.Constant2_Value_dk;
  }

  /* Switch: '<S111>/Switch2' incorporates:
   *  Constant: '<S111>/Clamping_zero'
   *  Constant: '<S111>/Constant3'
   *  Constant: '<S111>/Constant4'
   *  RelationalOperator: '<S111>/fix for DT propagation issue1'
   */
  if (rtb_B_idx_2 > Torque_Vectoring_2024_P.Clamping_zero_Value_m) {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant3_Value_d;
  } else {
    Memory_PreviousInput_d_tmp = Torque_Vectoring_2024_P.Constant4_Value_j;
  }

  /* Switch: '<S111>/Switch' incorporates:
   *  Constant: '<S111>/Clamping_zero'
   *  Constant: '<S111>/Constant1'
   *  Logic: '<S111>/AND3'
   *  RelationalOperator: '<S111>/Equal1'
   *  RelationalOperator: '<S111>/Relational Operator'
   *  Switch: '<S111>/Switch1'
   *  Switch: '<S111>/Switch2'
   */
  if ((Torque_Vectoring_2024_P.Clamping_zero_Value_m != rtb_DeadZone_l) &&
      (idxDelay == Memory_PreviousInput_d_tmp)) {
    rtb_B_idx_2 = Torque_Vectoring_2024_P.Constant1_Value_g;
  }

  /* Update for DiscreteIntegrator: '<S120>/Integrator' incorporates:
   *  Switch: '<S111>/Switch'
   */
  Torque_Vectoring_2024_DW.u += Torque_Vectoring_2024_P.Integrator_gainval *
    rtb_B_idx_2;
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

  /* End of Update for DiscreteIntegrator: '<S120>/Integrator' */

  /* Update for DiscreteIntegrator: '<S220>/Integrator' */
  Torque_Vectoring_2024_DW.u_m += Torque_Vectoring_2024_P.Integrator_gainval_b *
    rtb_DeadZone_i;
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

  /* End of Update for DiscreteIntegrator: '<S220>/Integrator' */

  /* Update for DiscreteIntegrator: '<S70>/Integrator' */
  Torque_Vectoring_2024_DW.u_a += Torque_Vectoring_2024_P.Integrator_gainval_h *
    rtb_Exp4_idx_2;
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

  /* End of Update for DiscreteIntegrator: '<S70>/Integrator' */

  /* Update for DiscreteIntegrator: '<S170>/Integrator' */
  Torque_Vectoring_2024_DW.u_g += Torque_Vectoring_2024_P.Integrator_gainval_l *
    rtb_Exp4_idx_1;
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

  /* End of Update for DiscreteIntegrator: '<S170>/Integrator' */

  /* Sum: '<S14>/Add1' incorporates:
   *  Constant: '<S14>/Constant4'
   *  Constant: '<S14>/Constant6'
   *  Product: '<S14>/Product5'
   */
  rtb_Saturation1 = Torque_Vectoring_2024_P.Constant6_Value_h[0] -
    rtb_Saturation_e_idx_1 * Torque_Vectoring_2024_P.Constant4_Value_g[0];
  rtb_Saturation = Torque_Vectoring_2024_P.Constant6_Value_h[1] -
    Torque_Vectoring_2024_P.Constant4_Value_g[0] * rtb_Saturation_e_idx_2;
  rtb_vxms = Torque_Vectoring_2024_P.Constant6_Value_h[2] -
    rtb_Saturation_e_idx_1 * Torque_Vectoring_2024_P.Constant4_Value_g[1];
  rtb_DeadZone_i = Torque_Vectoring_2024_P.Constant6_Value_h[3] -
    rtb_Saturation_e_idx_2 * Torque_Vectoring_2024_P.Constant4_Value_g[1];

  /* Update for Memory: '<S14>/Memory' incorporates:
   *  Product: '<S14>/Product6'
   */
  for (idxDelay = 0; idxDelay < 2; idxDelay++) {
    /* Product: '<S14>/Product6' */
    Memory_PreviousInput_d_tmp = idxDelay << 1U;
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[Memory_PreviousInput_d_tmp] =
      0.0;

    /* Product: '<S14>/Product6' incorporates:
     *  Sum: '<S14>/Add'
     */
    rtb_Integrator_h = rtb_P_k_m[Memory_PreviousInput_d_tmp];
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[Memory_PreviousInput_d_tmp] +=
      rtb_Integrator_h * rtb_Saturation1;

    /* Product: '<S14>/Product6' incorporates:
     *  Sum: '<S14>/Add'
     */
    rtb_vims_idx_1 = rtb_P_k_m[Memory_PreviousInput_d_tmp + 1];
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[Memory_PreviousInput_d_tmp] +=
      rtb_vims_idx_1 * rtb_vxms;
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[Memory_PreviousInput_d_tmp +
      1] = 0.0;
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[Memory_PreviousInput_d_tmp +
      1] += rtb_Integrator_h * rtb_Saturation;
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[Memory_PreviousInput_d_tmp +
      1] += rtb_vims_idx_1 * rtb_DeadZone_i;
  }

  /* End of Update for Memory: '<S14>/Memory' */

  /* Update for Memory: '<S3>/Memory4' */
  Torque_Vectoring_2024_DW.Memory4_PreviousInput = rtb_Saturation2;

  /* Update for Delay: '<S24>/Delay1' */
  for (idxDelay = 0; idxDelay < 99; idxDelay++) {
    Torque_Vectoring_2024_DW.Delay1_DSTATE[idxDelay] =
      Torque_Vectoring_2024_DW.Delay1_DSTATE[idxDelay + 1];
  }

  Torque_Vectoring_2024_DW.Delay1_DSTATE[99] = rtb_Compare;

  /* End of Update for Delay: '<S24>/Delay1' */
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

  {
    int16_T i;

    /* InitializeConditions for Delay: '<Root>/Delay' */
    Torque_Vectoring_2024_DW.Delay_DSTATE =
      Torque_Vectoring_2024_P.Delay_InitialCondition;

    /* InitializeConditions for Memory: '<S3>/Memory1' */
    Torque_Vectoring_2024_DW.Memory1_PreviousInput[0] =
      Torque_Vectoring_2024_P.Memory1_InitialCondition;
    Torque_Vectoring_2024_DW.Memory1_PreviousInput[1] =
      Torque_Vectoring_2024_P.Memory1_InitialCondition;

    /* InitializeConditions for DiscreteIntegrator: '<S120>/Integrator' */
    Torque_Vectoring_2024_DW.u =
      Torque_Vectoring_2024_P.PIDController3_InitialConditionForIntegrator;

    /* InitializeConditions for DiscreteIntegrator: '<S220>/Integrator' */
    Torque_Vectoring_2024_DW.u_m =
      Torque_Vectoring_2024_P.PIDController8_InitialConditionForIntegrator;

    /* InitializeConditions for DiscreteIntegrator: '<S70>/Integrator' */
    Torque_Vectoring_2024_DW.u_a =
      Torque_Vectoring_2024_P.PIDController1_InitialConditionForIntegrator;

    /* InitializeConditions for DiscreteIntegrator: '<S170>/Integrator' */
    Torque_Vectoring_2024_DW.u_g =
      Torque_Vectoring_2024_P.PIDController7_InitialConditionForIntegrator;

    /* InitializeConditions for Memory: '<S21>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput[0] =
      Torque_Vectoring_2024_P.Memory_InitialCondition;

    /* InitializeConditions for Memory: '<S14>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[0] =
      Torque_Vectoring_2024_P.Memory_InitialCondition_i[0];

    /* InitializeConditions for Memory: '<S21>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput[1] =
      Torque_Vectoring_2024_P.Memory_InitialCondition;

    /* InitializeConditions for Memory: '<S14>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[1] =
      Torque_Vectoring_2024_P.Memory_InitialCondition_i[1];

    /* InitializeConditions for Memory: '<S21>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput[2] =
      Torque_Vectoring_2024_P.Memory_InitialCondition;

    /* InitializeConditions for Memory: '<S14>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[2] =
      Torque_Vectoring_2024_P.Memory_InitialCondition_i[2];

    /* InitializeConditions for Memory: '<S21>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput[3] =
      Torque_Vectoring_2024_P.Memory_InitialCondition;

    /* InitializeConditions for Memory: '<S14>/Memory' */
    Torque_Vectoring_2024_DW.Memory_PreviousInput_d[3] =
      Torque_Vectoring_2024_P.Memory_InitialCondition_i[3];

    /* InitializeConditions for Memory: '<S3>/Memory4' */
    Torque_Vectoring_2024_DW.Memory4_PreviousInput =
      Torque_Vectoring_2024_P.Memory4_InitialCondition;

    /* InitializeConditions for Sum: '<S24>/Add1' incorporates:
     *  Memory: '<S24>/Memory'
     */
    Torque_Vectoring_2024_DW.Memory_PreviousInput_b =
      Torque_Vectoring_2024_P.Memory_InitialCondition_ir;

    /* InitializeConditions for Delay: '<S24>/Delay1' */
    for (i = 0; i < 100; i++) {
      Torque_Vectoring_2024_DW.Delay1_DSTATE[i] =
        Torque_Vectoring_2024_P.Delay1_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S24>/Delay1' */

    /* InitializeConditions for Memory: '<S3>/Memory2' */
    Torque_Vectoring_2024_DW.Memory2_PreviousInput[0] =
      Torque_Vectoring_2024_P.Memory2_InitialCondition[0];
    Torque_Vectoring_2024_DW.Memory2_PreviousInput[1] =
      Torque_Vectoring_2024_P.Memory2_InitialCondition[1];
  }
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
