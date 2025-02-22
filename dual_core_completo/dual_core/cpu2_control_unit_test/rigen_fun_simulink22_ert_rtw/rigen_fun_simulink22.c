/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rigen_fun_simulink22.c
 *
 * Code generated for Simulink model 'rigen_fun_simulink22'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Wed Nov 20 09:59:02 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "rigen_fun_simulink22.h"

#include <math.h>
#include "rtwtypes.h"
#include <string.h>

#define NOT_USING_NONFINITE_LITERALS   1


/* External outputs (root outports fed by signals with default storage) */
ExtY_rigen_fun_simulink22_T rigen_fun_simulink22_Y;
ExtU_rigen_fun_simulink22_T rigen_fun_simulink22_U;

/* Real-time model */
static RT_MODEL_rigen_fun_simulink22_T rigen_fun_simulink22_M_;
RT_MODEL_rigen_fun_simulink22_T *const rigen_fun_simulink22_M =
  &rigen_fun_simulink22_M_;

#define NumBitsPerChar                 16U

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}


/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}


/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/* Model step function */
void rigen_fun_simulink22_step(void)
{
  real_T rtb_Gain1_a;
  real_T rtb_Gain_m;
  real_T rtb_Power_front;

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant6'
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/rpm2rad//s'
   *  Sum: '<Root>/Sum'
   */
  rigen_fun_simulink22_Y.TorqueRR = (((rigen_fun_simulink22_U.rpmFL +
          rigen_fun_simulink22_U.rpmFR) + rigen_fun_simulink22_U.rpmRL) +
          rigen_fun_simulink22_U.rpmRR) * rigen_fun_simulink22_P.Gain_Gain *
    rigen_fun_simulink22_P.rpm2rads_Gain;

  /* Product: '<S2>/Divide' incorporates:
   *  Constant: '<Root>/tensione'
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Rbatt'
   *  Constant: '<S2>/max_voltage'
   *  Sum: '<S2>/Sum'
   *  Sum: '<S2>/Sum1'
   */
  rtb_Power_front = (rigen_fun_simulink22_U.voltage -
                     rigen_fun_simulink22_P.max_voltage_Value) /
    (rigen_fun_simulink22_P.Rbatt_Value + rigen_fun_simulink22_P.Constant2_Value);

  /* MinMax: '<S2>/MinMax' incorporates:
   *  Constant: '<Root>/max_curr'
   */
  if ((rigen_fun_simulink22_U.max_curr <= rtb_Power_front) || rtIsNaN
      (rtb_Power_front)) {
    rtb_Power_front = rigen_fun_simulink22_U.max_curr;
  }

  /* Product: '<Root>/Product' incorporates:
   *  Constant: '<Root>/csi_opt'
   *  Constant: '<Root>/max_curr'
   *  Constant: '<Root>/tensione'
   *  Constant: '<S2>/Rbatt'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<S2>/Gain'
   *  MinMax: '<S2>/MinMax'
   *  Product: '<S2>/Product'
   *  Product: '<S2>/Product1'
   *  Sum: '<S2>/Sum2'
   */
  rtb_Power_front = (rtb_Power_front * rigen_fun_simulink22_P.Rbatt_Value +
          rigen_fun_simulink22_U.voltage) *
                  rigen_fun_simulink22_U.max_curr * rigen_fun_simulink22_P.Gain_Gain_h *
    (rigen_fun_simulink22_P.Gain1_Gain * rigen_fun_simulink22_P.csi_opt);

  /* Gain: '<Root>/rad//s2rad//s elettrici' */
  rtb_Gain1_a = rigen_fun_simulink22_P.rads2radselettrici_Gain *
    rigen_fun_simulink22_Y.TorqueRR;

  /* Gain: '<S4>/Gain' incorporates:
   *  Constant: '<S1>/flux_PM'
   *  Product: '<S4>/Product'
   */
  rtb_Gain_m = rigen_fun_simulink22_P.flux_PM_Value * rtb_Gain1_a *
    rigen_fun_simulink22_P.Gain_Gain_e;

  /* Gain: '<S3>/Gain1' incorporates:
   *  Constant: '<S1>/Ld'
   *  Constant: '<S1>/Lq'
   *  Constant: '<S1>/tan_alfa'
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/R'
   *  Math: '<S3>/Square'
   *  Product: '<S3>/Divide'
   *  Product: '<S3>/Divide1'
   *  Product: '<S3>/Product'
   *  Product: '<S3>/Product1'
   *  Sum: '<S3>/Subtract'
   *  Sum: '<S3>/Sum'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Gain1_a = ((rigen_fun_simulink22_P.Constant_Value /
                  (rigen_fun_simulink22_P.tan_alfa_Value *
                   rigen_fun_simulink22_P.tan_alfa_Value) +
                  rigen_fun_simulink22_P.Constant_Value) *
                 rigen_fun_simulink22_P.R_Value_m +
                 (rigen_fun_simulink22_P.Ld_Value -
                  rigen_fun_simulink22_P.Lq_Value) * rtb_Gain1_a /
                 rigen_fun_simulink22_P.tan_alfa_Value) *
    rigen_fun_simulink22_P.Gain1_Gain_g;

  /* Product: '<S1>/Divide' incorporates:
   *  Gain: '<S1>/Gain'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Math: '<S1>/Square'
   *  Product: '<S1>/Product'
   *  Sqrt: '<S1>/Square Root'
   *  Sum: '<S1>/Subtract'
   *  Sum: '<S1>/Subtract1'
   */
  rtb_Gain1_a = (sqrt(rtb_Gain_m * rtb_Gain_m -
                      rigen_fun_simulink22_P.Gain_Gain_o * rtb_Power_front *
                      rtb_Gain1_a * rigen_fun_simulink22_P.Gain1_Gain_l) -
                 rtb_Gain_m) / (rigen_fun_simulink22_P.Gain2_Gain * rtb_Gain1_a);

  /* Math: '<S1>/Square2' */
  rtb_Gain_m = rtb_Gain1_a * rtb_Gain1_a;

  /* Product: '<S1>/Divide1' incorporates:
   *  Constant: '<S1>/tan_alfa'
   */
  rtb_Gain1_a /= rigen_fun_simulink22_P.tan_alfa_Value;

  /* Product: '<Root>/Divide2' incorporates:
   *  Constant: '<S1>/R'
   *  Gain: '<S1>/Gain3'
   *  Math: '<S1>/Square1'
   *  Product: '<S1>/Product1'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<S1>/Sum'
   */
  rtb_Power_front = ((rtb_Gain1_a * rtb_Gain1_a + rtb_Gain_m) *
                     rigen_fun_simulink22_P.R_Value *
                     rigen_fun_simulink22_P.Gain3_Gain + rtb_Power_front) * (1.0
    / rigen_fun_simulink22_Y.TorqueRR);

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Power_front > rigen_fun_simulink22_P.Tmax) {
    rtb_Power_front = rigen_fun_simulink22_P.Tmax;
  } else if (rtb_Power_front < rigen_fun_simulink22_P.Saturation_LowerSat) {
    rtb_Power_front = rigen_fun_simulink22_P.Saturation_LowerSat;
  }

  /* Product: '<Root>/Product1' incorporates:
   *  Gain: '<Root>/Gain3'
   *  Saturate: '<Root>/Saturation'
   */
  rigen_fun_simulink22_Y.TorqueRR = rigen_fun_simulink22_P.Gain3_Gain_f *
    rtb_Power_front;

  /* Outport: '<Root>/TorqueFL' */
  rigen_fun_simulink22_Y.TorqueFL = rigen_fun_simulink22_Y.TorqueRR;

  /* Outport: '<Root>/TorqueFR' */
  rigen_fun_simulink22_Y.TorqueFR = rigen_fun_simulink22_Y.TorqueRR;

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<Root>/Constant7'
   *  Constant: '<Root>/csi_opt'
   *  Product: '<Root>/Divide4'
   *  Sum: '<Root>/Sum1'
   */
  rigen_fun_simulink22_Y.TorqueRR *= 1.0 / rigen_fun_simulink22_P.csi_opt *
    (rigen_fun_simulink22_P.Constant7_Value - rigen_fun_simulink22_P.csi_opt);

  /* Outport: '<Root>/TorqueRL' */
  rigen_fun_simulink22_Y.TorqueRL = rigen_fun_simulink22_Y.TorqueRR;
}

/* Model initialize function */
void rigen_fun_simulink22_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(rigen_fun_simulink22_M, (NULL));

  /* external outputs */
  (void)memset(&rigen_fun_simulink22_Y, 0, sizeof(ExtY_rigen_fun_simulink22_T));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
