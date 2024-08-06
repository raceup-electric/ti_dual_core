/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024_forsecontiu.c
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
#include <math.h>
#include "rtwtypes.h"
#include <string.h>
#include <stddef.h>
#define NumBitsPerChar                 16U

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

#define NOT_USING_NONFINITE_LITERALS   1

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
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
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
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
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
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
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
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
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T tmp;
  real_T tmp_0;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
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
void Torque_Vectoring_2024_forsecontiu_step(void)
{
  real_T rtb_Integrator[4];
  real_T rtb_P_k1[4];
  real_T rtb_K_k[2];
  real_T Transpose2;
  real_T Transpose2_0;
  real_T rtb_Add1_e;
  real_T rtb_Csi;
  real_T rtb_Divide_d;
  real_T rtb_Gain12_0;
  real_T rtb_Gain20_0;
  real_T rtb_Gain21_0;
  real_T rtb_Gain23_0;
  real_T rtb_Gain24_0;
  real_T rtb_Gain25_0;
  real_T rtb_MathFunction5_0;
  real_T rtb_MathFunction6_idx_0;
  real_T rtb_MathFunction6_idx_0_tmp;
  real_T rtb_MathFunction6_idx_1;
  real_T rtb_Product2_h;
  real_T rtb_Product3_k;
  real_T rtb_Product_o;
  real_T rtb_Saturation;
  real_T rtb_Saturation1;
  real_T rtb_Saturation1_j_idx_0;
  real_T rtb_Saturation1_j_idx_1;
  real_T rtb_Saturation1_j_idx_2;
  real_T rtb_Saturation2;
  real_T rtb_Saturation_e_idx_0;
  real_T rtb_Saturation_e_idx_1;
  real_T rtb_Saturation_e_idx_2;
  real_T rtb_Saturation_g_0;
  real_T rtb_Saturation_g_idx_0;
  real_T rtb_Saturation_g_idx_1;
  real_T rtb_Saturation_g_idx_2;
  real_T rtb_Saturation_k;
  real_T rtb_Square_m_idx_0;
  real_T rtb_Square_m_idx_0_tmp;
  real_T rtb_Square_m_idx_1;
  real_T rtb_Square_m_idx_1_tmp;
  real_T rtb_Square_m_idx_2;
  real_T rtb_Square_m_idx_2_tmp;
  real_T rtb_Sum1_p;
  real_T rtb_SumofElements2;
  real_T rtb_delta_fldelta_frrad_idx_0;
  real_T rtb_delta_fldelta_frrad_idx_1;
  real_T rtb_vims_idx_0;
  real_T rtb_vims_idx_1;
  real_T rtb_vims_idx_2;
  real_T rtb_vims_idx_3;
  real_T rtb_vims_idx_3_tmp;
  real_T u;
  real_T u0;
  int16_T i;
  int16_T rtb_P_k1_tmp;
  boolean_T rtb_Compare_m;
  boolean_T tmp;

  /* Saturate: '<Root>/Saturation1' incorporates:
   *  Inport: '<Root>/ay'
   */
  if (rtU.ay > 25.506000000000004) {
    rtb_Saturation1 = 25.506000000000004;
  } else if (rtU.ay < -25.506000000000004) {
    rtb_Saturation1 = -25.506000000000004;
  } else {
    rtb_Saturation1 = rtU.ay;
  }

  /* End of Saturate: '<Root>/Saturation1' */

  /* Gain: '<S11>/Gain3' */
  rtb_Add1_e = 28.224717611553253 * rtb_Saturation1;

  /* Saturate: '<Root>/Saturation' incorporates:
   *  Inport: '<Root>/ax'
   */
  if (rtU.ax > 17.658) {
    rtb_Saturation = 17.658;
  } else if (rtU.ax < -20.601000000000003) {
    rtb_Saturation = -20.601000000000003;
  } else {
    rtb_Saturation = rtU.ax;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Gain: '<S11>/Gain2' */
  rtb_Sum1_p = 27.788921824104236 * rtb_Saturation;

  /* Gain: '<S11>/Fl' incorporates:
   *  Math: '<S11>/Square'
   *  Memory: '<Root>/Memory'
   */
  rtb_Divide_d = rtDW.Memory_PreviousInput * rtDW.Memory_PreviousInput * 2.75625;

  /* Gain: '<S11>/Gain1' */
  rtb_Product2_h = 0.26535596091205216 * rtb_Divide_d;

  /* Sum: '<S11>/Add' incorporates:
   *  Constant: '<S11>/Constant'
   */
  rtb_Saturation_k = ((627.682966425 - rtb_Add1_e) - rtb_Sum1_p) +
    rtb_Product2_h;

  /* Sum: '<S11>/Add1' incorporates:
   *  Constant: '<S11>/Constant'
   */
  rtb_Add1_e = ((rtb_Add1_e + 627.682966425) - rtb_Sum1_p) + rtb_Product2_h;

  /* Gain: '<S11>/Gain4' */
  rtb_Product2_h = 42.162989448157909 * rtb_Saturation1;

  /* Gain: '<S11>/Gain' */
  rtb_Divide_d *= 0.23464403908794787;

  /* Sum: '<S11>/Add2' incorporates:
   *  Constant: '<S11>/Constant1'
   */
  rtb_Product_o = ((767.16807007500006 - rtb_Product2_h) + rtb_Sum1_p) +
    rtb_Divide_d;

  /* Sum: '<S11>/Add3' incorporates:
   *  Constant: '<S11>/Constant1'
   */
  rtb_Product2_h = ((rtb_Product2_h + 767.16807007500006) + rtb_Sum1_p) +
    rtb_Divide_d;

  /* SignalConversion generated from: '<S10>/Math Function' */
  rtb_Sum1_p = rtb_Product2_h;

  /* Saturate: '<Root>/Saturation6' incorporates:
   *  Inport: '<Root>/steering'
   */
  if (rtU.steering > 100.0) {
    rtb_Square_m_idx_0 = 100.0;
  } else if (rtU.steering < -100.0) {
    rtb_Square_m_idx_0 = -100.0;
  } else {
    rtb_Square_m_idx_0 = rtU.steering;
  }

  /* Gain: '<S2>/Gain3' incorporates:
   *  Saturate: '<Root>/Saturation6'
   */
  rtb_Divide_d = 0.00030229102644541785 * rtb_Square_m_idx_0;

  /* Math: '<S2>/Math Function1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Math: '<S2>/Math Function5'
   */
  rtb_Saturation2 = rt_powd_snf(rtb_Divide_d, 4.0);

  /* Math: '<S2>/Square2' incorporates:
   *  Math: '<S2>/Square1'
   */
  rtb_Saturation_g_idx_2 = rtb_Divide_d * rtb_Divide_d;

  /* Gain: '<S2>/Gain2' incorporates:
   *  Constant: '<S2>/Constant2'
   *  Gain: '<S2>/Gain9'
   *  Math: '<S2>/Math Function2'
   */
  rtb_MathFunction6_idx_0_tmp = 63090.0 * rt_powd_snf(rtb_Divide_d, 3.0);

  /* Gain: '<S2>/Gain1' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Gain: '<S2>/Gain10'
   *  Math: '<S2>/Math Function3'
   */
  rtb_Saturation1_j_idx_0 = 2.497E+7 * rt_powd_snf(rtb_Divide_d, 5.0);

  /* SignalConversion generated from: '<S15>/Cos' incorporates:
   *  Constant: '<S12>/Constant2'
   *  Constant: '<S2>/Constant7'
   *  Gain: '<S2>/Gain'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S2>/Gain11'
   *  Gain: '<S2>/Gain2'
   *  Gain: '<S2>/Gain4'
   *  Gain: '<S2>/Gain5'
   *  Gain: '<S2>/Gain6'
   *  Gain: '<S2>/Gain7'
   *  Gain: '<S2>/Gain8'
   *  Math: '<S2>/Math Function1'
   *  Math: '<S2>/Square2'
   *  Sum: '<S12>/Add'
   *  Sum: '<S12>/Add1'
   *  Sum: '<S2>/Sum1'
   *  Sum: '<S2>/Sum2'
   */
  rtb_MathFunction6_idx_0 = (((((-1.217E+6 * rtb_Saturation2 +
    rtb_Saturation1_j_idx_0) + rtb_MathFunction6_idx_0_tmp) +
    rtb_Saturation_g_idx_2 * -3034.0) + 988.7 * rtb_Divide_d) - 0.0009525) *
    0.017453292519943295 - rtP.toe_f;
  rtb_MathFunction6_idx_1 = (((((988.7 * rtb_Divide_d + 0.0009525) +
    rtb_Saturation_g_idx_2 * 3034.0) + rtb_MathFunction6_idx_0_tmp) + 1.217E+6 *
    rtb_Saturation2) + rtb_Saturation1_j_idx_0) * 0.017453292519943295 +
    rtP.toe_f;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (rtU.rpm[0] > 20000.0) {
    rtb_MathFunction6_idx_0_tmp = 20000.0;
  } else if (rtU.rpm[0] < 0.0) {
    rtb_MathFunction6_idx_0_tmp = 0.0;
  } else {
    rtb_MathFunction6_idx_0_tmp = rtU.rpm[0];
  }

  rtb_Saturation1_j_idx_0 = rtb_MathFunction6_idx_0_tmp;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  u0 = -3.533E-6 * rtb_Saturation_k + 0.2032;

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
  rtb_Saturation_g_0 = 0.10471975511965977 * rtb_MathFunction6_idx_0_tmp *
    0.078947160665366667 * u0;
  rtb_Saturation_g_idx_0 = rtb_Saturation_g_0;

  /* Trigonometry: '<S15>/Cos' incorporates:
   *  Trigonometry: '<S8>/Cos'
   */
  rtb_Square_m_idx_0_tmp = cos(rtb_MathFunction6_idx_0);

  /* Product: '<S15>/Product1' incorporates:
   *  Trigonometry: '<S15>/Cos'
   */
  rtb_Square_m_idx_0 = rtb_Square_m_idx_0_tmp * rtb_Saturation_g_0;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (rtU.rpm[1] > 20000.0) {
    rtb_MathFunction6_idx_0_tmp = 20000.0;
  } else if (rtU.rpm[1] < 0.0) {
    rtb_MathFunction6_idx_0_tmp = 0.0;
  } else {
    rtb_MathFunction6_idx_0_tmp = rtU.rpm[1];
  }

  rtb_Saturation1_j_idx_1 = rtb_MathFunction6_idx_0_tmp;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  u0 = -3.533E-6 * rtb_Add1_e + 0.2032;

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
  rtb_Saturation_g_0 = 0.10471975511965977 * rtb_MathFunction6_idx_0_tmp *
    0.078947160665366667 * u0;
  rtb_Saturation_g_idx_1 = rtb_Saturation_g_0;

  /* Trigonometry: '<S15>/Cos' incorporates:
   *  Trigonometry: '<S8>/Cos'
   */
  rtb_Square_m_idx_1_tmp = cos(rtb_MathFunction6_idx_1);

  /* Product: '<S15>/Product1' incorporates:
   *  Trigonometry: '<S15>/Cos'
   */
  rtb_Square_m_idx_1 = rtb_Square_m_idx_1_tmp * rtb_Saturation_g_0;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (rtU.rpm[2] > 20000.0) {
    rtb_MathFunction6_idx_0_tmp = 20000.0;
  } else if (rtU.rpm[2] < 0.0) {
    rtb_MathFunction6_idx_0_tmp = 0.0;
  } else {
    rtb_MathFunction6_idx_0_tmp = rtU.rpm[2];
  }

  rtb_Saturation1_j_idx_2 = rtb_MathFunction6_idx_0_tmp;

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  u0 = -3.533E-6 * rtb_Product_o + 0.2032;

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
  rtb_Saturation_g_0 = 0.10471975511965977 * rtb_MathFunction6_idx_0_tmp *
    0.078947160665366667 * u0;
  rtb_Saturation_g_idx_2 = rtb_Saturation_g_0;

  /* Trigonometry: '<S15>/Cos' incorporates:
   *  Constant: '<S12>/Constant4'
   *  Gain: '<S12>/Gain'
   *  Trigonometry: '<S8>/Cos'
   */
  rtb_Square_m_idx_2_tmp = cos(-rtP.toe_r);

  /* Product: '<S15>/Product1' incorporates:
   *  Trigonometry: '<S15>/Cos'
   */
  rtb_Square_m_idx_2 = rtb_Square_m_idx_2_tmp * rtb_Saturation_g_0;

  /* Saturate: '<Root>/Saturation5' incorporates:
   *  Inport: '<Root>/rpm'
   */
  if (rtU.rpm[3] > 20000.0) {
    rtb_MathFunction6_idx_0_tmp = 20000.0;
  } else if (rtU.rpm[3] < 0.0) {
    rtb_MathFunction6_idx_0_tmp = 0.0;
  } else {
    rtb_MathFunction6_idx_0_tmp = rtU.rpm[3];
  }

  /* Sum: '<S5>/Add' incorporates:
   *  Constant: '<S5>/Constant'
   *  Gain: '<S5>/Gain2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  u0 = -3.533E-6 * rtb_Product2_h + 0.2032;

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
  rtb_Saturation_g_0 = 0.10471975511965977 * rtb_MathFunction6_idx_0_tmp *
    0.078947160665366667 * u0;

  /* Saturate: '<Root>/Saturation2' incorporates:
   *  Inport: '<Root>/yaw_r'
   */
  if (rtU.yaw_r > 6.2831853071795862) {
    rtb_Saturation2 = 6.2831853071795862;
  } else if (rtU.yaw_r < -6.2831853071795862) {
    rtb_Saturation2 = -6.2831853071795862;
  } else {
    rtb_Saturation2 = rtU.yaw_r;
  }

  /* End of Saturate: '<Root>/Saturation2' */

  /* Sum: '<S15>/Add' incorporates:
   *  Gain: '<S15>/Multiply'
   *  Gain: '<S15>/Multiply1'
   *  Gain: '<S15>/Multiply2'
   */
  rtb_vims_idx_0 = 0.615 * rtb_Saturation2 + rtb_Square_m_idx_0;
  rtb_vims_idx_1 = -0.615 * rtb_Saturation2 + rtb_Square_m_idx_1;
  rtb_vims_idx_2 = 0.6 * rtb_Saturation2 + rtb_Square_m_idx_2;

  /* Trigonometry: '<S15>/Cos' incorporates:
   *  Constant: '<S12>/Constant4'
   *  SignalConversion generated from: '<S15>/Cos'
   *  Trigonometry: '<S8>/Cos'
   */
  rtb_vims_idx_3_tmp = cos(rtP.toe_r);

  /* Sum: '<S15>/Add' incorporates:
   *  Gain: '<S15>/Multiply3'
   *  Product: '<S15>/Product1'
   *  Trigonometry: '<S15>/Cos'
   */
  rtb_vims_idx_3 = -0.6 * rtb_Saturation2 + rtb_vims_idx_3_tmp *
    rtb_Saturation_g_0;

  /* Sum: '<S21>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  rtb_delta_fldelta_frrad_idx_0 = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_0;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  u = rtb_Saturation - (rtb_vims_idx_0 - rtDW.Memory_PreviousInput_g[0]) * 100.0;

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
  rtb_SumofElements2 = exp(((0.0 - 1.0 / rtConstB.Exp2 *
    (rtb_delta_fldelta_frrad_idx_0 * rtb_delta_fldelta_frrad_idx_0)) - u * u /
    rtConstB.Exp3) * 0.5);
  rtb_P_k1[0] = rtb_SumofElements2;

  /* Product: '<S15>/Product' incorporates:
   *  Sum: '<S21>/Add1'
   */
  rtb_Square_m_idx_0 = rtb_vims_idx_0 * rtb_SumofElements2;

  /* Sum: '<S21>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  rtb_delta_fldelta_frrad_idx_0 = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_1;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  u = rtb_Saturation - (rtb_vims_idx_1 - rtDW.Memory_PreviousInput_g[1]) * 100.0;

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
  rtb_SumofElements2 = exp(((0.0 - 1.0 / rtConstB.Exp2 *
    (rtb_delta_fldelta_frrad_idx_0 * rtb_delta_fldelta_frrad_idx_0)) - u * u /
    rtConstB.Exp3) * 0.5);
  rtb_P_k1[1] = rtb_SumofElements2;

  /* Product: '<S15>/Product' incorporates:
   *  Sum: '<S21>/Add1'
   */
  rtb_Square_m_idx_1 = rtb_vims_idx_1 * rtb_SumofElements2;

  /* Sum: '<S21>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  rtb_delta_fldelta_frrad_idx_0 = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_2;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  u = rtb_Saturation - (rtb_vims_idx_2 - rtDW.Memory_PreviousInput_g[2]) * 100.0;

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
  rtb_SumofElements2 = exp(((0.0 - 1.0 / rtConstB.Exp2 *
    (rtb_delta_fldelta_frrad_idx_0 * rtb_delta_fldelta_frrad_idx_0)) - u * u /
    rtConstB.Exp3) * 0.5);
  rtb_P_k1[2] = rtb_SumofElements2;

  /* Product: '<S15>/Product' incorporates:
   *  Sum: '<S21>/Add1'
   */
  rtb_Square_m_idx_2 = rtb_vims_idx_2 * rtb_SumofElements2;

  /* Sum: '<S21>/Add1' incorporates:
   *  Memory: '<S3>/Memory1'
   */
  rtb_delta_fldelta_frrad_idx_0 = rtDW.Memory1_PreviousInput[0] - rtb_vims_idx_3;

  /* Sum: '<S21>/Add2' incorporates:
   *  Gain: '<S21>/Gain1'
   *  Memory: '<S21>/Memory'
   *  Sum: '<S21>/Add'
   *  Sum: '<S21>/Add1'
   */
  u = rtb_Saturation - (rtb_vims_idx_3 - rtDW.Memory_PreviousInput_g[3]) * 100.0;

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
  rtb_SumofElements2 = exp(((0.0 - 1.0 / rtConstB.Exp2 *
    (rtb_delta_fldelta_frrad_idx_0 * rtb_delta_fldelta_frrad_idx_0)) - u * u /
    rtConstB.Exp3) * 0.5);

  /* SignalConversion generated from: '<S14>/Vector Concatenate' incorporates:
   *  Constant: '<S14>/Constant'
   */
  rtb_Integrator[0] = 1.0;

  /* Gain: '<S14>/Gain' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_Integrator[1] = -0.01 * rtDW.Memory4_PreviousInput;

  /* Gain: '<S14>/Gain1' incorporates:
   *  Memory: '<S3>/Memory4'
   */
  rtb_Integrator[2] = 0.01 * rtDW.Memory4_PreviousInput;

  /* SignalConversion generated from: '<S14>/Vector Concatenate1' incorporates:
   *  Constant: '<S14>/Constant'
   */
  rtb_Integrator[3] = 1.0;

  /* Sum: '<S17>/Sum' incorporates:
   *  DiscreteIntegrator: '<S63>/Integrator'
   *  Gain: '<S14>/Gain3'
   *  Memory: '<S3>/Memory1'
   *  Memory: '<S3>/Memory2'
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   */
  rtb_delta_fldelta_frrad_idx_0 = (rtDW.Memory1_PreviousInput[1] *
    rtb_Integrator[2] + rtDW.Memory1_PreviousInput[0]) + (rtConstB.B_e[0] *
    rtDW.Memory2_PreviousInput[0] + rtDW.Memory2_PreviousInput[1] *
    rtConstB.B_e[2]);
  rtb_delta_fldelta_frrad_idx_1 = (rtDW.Memory1_PreviousInput[0] *
    rtb_Integrator[1] + rtDW.Memory1_PreviousInput[1]) +
    (rtDW.Memory2_PreviousInput[0] * rtConstB.B_e[1] +
     rtDW.Memory2_PreviousInput[1] * rtConstB.B_e[3]);

  /* MinMax: '<S15>/Min' incorporates:
   *  MinMax: '<S15>/Max'
   */
  rtb_Compare_m = rtIsNaN(rtb_vims_idx_1);
  if ((rtb_vims_idx_0 <= rtb_vims_idx_1) || rtb_Compare_m) {
    rtb_Product3_k = rtb_vims_idx_0;
  } else {
    rtb_Product3_k = rtb_vims_idx_1;
  }

  tmp = !rtIsNaN(rtb_vims_idx_2);
  if ((!(rtb_Product3_k <= rtb_vims_idx_2)) && tmp) {
    rtb_Product3_k = rtb_vims_idx_2;
  }

  /* Sum: '<S15>/Sum of Elements1' incorporates:
   *  Math: '<S21>/Exp4'
   *
   * About '<S21>/Exp4':
   *  Operator: exp
   */
  rtb_Csi = ((rtb_P_k1[0] + rtb_P_k1[1]) + rtb_P_k1[2]) + rtb_SumofElements2;

  /* MinMax: '<S15>/Max' */
  if ((rtb_vims_idx_0 >= rtb_vims_idx_1) || rtb_Compare_m) {
    rtb_Divide_d = rtb_vims_idx_0;
  } else {
    rtb_Divide_d = rtb_vims_idx_1;
  }

  if ((!(rtb_Divide_d >= rtb_vims_idx_2)) && tmp) {
    rtb_Divide_d = rtb_vims_idx_2;
  }

  /* MinMax: '<S15>/Min' incorporates:
   *  MinMax: '<S15>/Max'
   */
  tmp = !rtIsNaN(rtb_vims_idx_3);
  if ((!(rtb_Product3_k <= rtb_vims_idx_3)) && tmp) {
    rtb_Product3_k = rtb_vims_idx_3;
  }

  /* MinMax: '<S15>/Max1' */
  if (!(rtb_Csi >= 1.0E-7)) {
    rtb_Csi = 1.0E-7;
  }

  /* MinMax: '<S15>/Max' */
  if ((!(rtb_Divide_d >= rtb_vims_idx_3)) && tmp) {
    rtb_Divide_d = rtb_vims_idx_3;
  }

  /* Sum: '<S16>/Add' incorporates:
   *  Abs: '<S15>/Abs'
   *  Constant: '<S14>/Constant4'
   *  Constant: '<S18>/Constant'
   *  Constant: '<S19>/Constant'
   *  Constant: '<S20>/Constant'
   *  MinMax: '<S15>/Max'
   *  MinMax: '<S15>/Max1'
   *  MinMax: '<S15>/Min'
   *  Product: '<S15>/Divide'
   *  Product: '<S15>/Product'
   *  Product: '<S15>/Product of Elements'
   *  Product: '<S16>/Product'
   *  RelationalOperator: '<S18>/Compare'
   *  RelationalOperator: '<S19>/Compare'
   *  RelationalOperator: '<S20>/Compare'
   *  Sum: '<S15>/Sum of Elements'
   *  Sum: '<S15>/Sum of Elements2'
   *  Sum: '<S21>/Add1'
   */
  rtb_Square_m_idx_2 = (((((rtb_Square_m_idx_0 + rtb_Square_m_idx_1) +
    rtb_Square_m_idx_2) + rtb_vims_idx_3 * rtb_SumofElements2) / rtb_Csi *
    (real_T)(fabs(rtb_Saturation) <= 1.8) + (real_T)(rtb_Saturation >= 1.8) *
    rtb_Product3_k) + (real_T)(rtb_Saturation < -1.8) * rtb_Divide_d) - (0.0 *
    rtb_delta_fldelta_frrad_idx_1 + rtb_delta_fldelta_frrad_idx_0);

  /* Product: '<S14>/Product2' incorporates:
   *  DiscreteIntegrator: '<S63>/Integrator'
   *  Math: '<S14>/Transpose'
   *  Memory: '<S14>/Memory'
   */
  rtb_Square_m_idx_1 = rtb_Integrator[2];
  u = rtb_Integrator[1];
  for (i = 0; i < 2; i++) {
    rtb_Divide_d = rtDW.Memory_PreviousInput_o[i + 2];
    rtb_Csi = rtDW.Memory_PreviousInput_o[i];
    rtb_P_k1[i] = rtb_Divide_d * rtb_Square_m_idx_1 + rtb_Csi;
    rtb_P_k1[i + 2] = rtb_Csi * u + rtb_Divide_d;
  }

  /* Product: '<S14>/Product4' */
  rtb_Square_m_idx_0 = 0.0;

  /* Product: '<S14>/Product2' */
  rtb_Divide_d = rtb_P_k1[1];
  rtb_Csi = rtb_P_k1[0];
  rtb_Product3_k = rtb_P_k1[3];
  rtb_MathFunction5_0 = rtb_P_k1[2];

  /* Product: '<S14>/Product4' incorporates:
   *  Math: '<S14>/Transpose2'
   */
  Transpose2 = rtConstB.Transpose2[0];
  Transpose2_0 = rtConstB.Transpose2[1];
  for (i = 0; i < 2; i++) {
    /* Sum: '<S14>/Add' incorporates:
     *  DiscreteIntegrator: '<S63>/Integrator'
     *  Product: '<S14>/Product2'
     */
    rtb_Square_m_idx_1 = rtb_Integrator[i + 2];
    u = rtb_Integrator[i];
    rtb_SumofElements2 = rtb_Square_m_idx_1 * rtb_Divide_d + u * rtb_Csi;
    rtb_P_k1[i] = rtb_SumofElements2;
    rtb_Square_m_idx_1 = rtb_Square_m_idx_1 * rtb_Product3_k + u *
      rtb_MathFunction5_0;
    rtb_P_k1[i + 2] = rtb_Square_m_idx_1;

    /* Product: '<S14>/Product4' incorporates:
     *  Constant: '<S14>/Constant4'
     *  Math: '<S14>/Transpose2'
     *  Product: '<S14>/Product3'
     *  Sum: '<S14>/Add'
     */
    u = rtb_Square_m_idx_1 * Transpose2_0 + rtb_SumofElements2 * Transpose2;
    rtb_K_k[i] = u;
    rtb_Square_m_idx_0 += rtConstP.Constant4_Value[i] * u;
  }

  /* Product: '<S14>/Divide' incorporates:
   *  Constant: '<S14>/Constant5'
   *  Product: '<S14>/Product3'
   *  Product: '<S14>/Product4'
   *  Sum: '<S14>/Add2'
   */
  u = rtb_K_k[0] / (rtb_Square_m_idx_0 + 0.05);
  rtb_K_k[0] = u;

  /* Sum: '<S16>/Add1' incorporates:
   *  Product: '<S14>/Divide'
   *  Product: '<S16>/Product1'
   */
  rtb_delta_fldelta_frrad_idx_0 += u * rtb_Square_m_idx_2;

  /* Product: '<S14>/Divide' incorporates:
   *  Constant: '<S14>/Constant5'
   *  Product: '<S14>/Product3'
   *  Product: '<S14>/Product4'
   *  Sum: '<S14>/Add2'
   */
  u = rtb_K_k[1] / (rtb_Square_m_idx_0 + 0.05);

  /* Gain: '<S8>/Multiply1' */
  rtb_SumofElements2 = 0.615 * rtb_Saturation2;

  /* Gain: '<S8>/Multiply3' */
  rtb_Divide_d = 0.6 * rtb_Saturation2;

  /* Product: '<S8>/Product4' incorporates:
   *  Sum: '<S8>/Add3'
   *  Sum: '<S8>/Add6'
   */
  rtb_Square_m_idx_0 = (rtb_delta_fldelta_frrad_idx_0 - rtb_SumofElements2) *
    rtb_Square_m_idx_0_tmp;
  rtb_Square_m_idx_1 = (rtb_SumofElements2 + rtb_delta_fldelta_frrad_idx_0) *
    rtb_Square_m_idx_1_tmp;

  /* Product: '<S3>/Product' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<S13>/Constant'
   *  Constant: '<S3>/Constant'
   *  Product: '<S14>/Divide'
   *  Product: '<S16>/Product1'
   *  RelationalOperator: '<S13>/Compare'
   *  Sum: '<S16>/Add1'
   *  Sum: '<S3>/Add'
   */
  rtb_Square_m_idx_2 = (u * rtb_Square_m_idx_2 + rtb_delta_fldelta_frrad_idx_1) *
    (1.0 - (real_T)(fabs(rtb_Saturation2) <= 0.034906585039886591));

  /* Sum: '<S8>/Add' incorporates:
   *  Gain: '<S8>/Multiply4'
   */
  rtb_SumofElements2 = 0.84425000000000006 * rtb_Saturation2 +
    rtb_Square_m_idx_2;

  /* Sum: '<S8>/Add1' incorporates:
   *  Gain: '<S8>/Multiply7'
   */
  rtb_Csi = -0.69075 * rtb_Saturation2 - rtb_Square_m_idx_2;

  /* Product: '<S8>/Product5' incorporates:
   *  Constant: '<S12>/Constant4'
   *  Gain: '<S12>/Gain'
   *  Gain: '<S30>/Gain'
   *  Product: '<Root>/Product'
   *  Product: '<S8>/Product4'
   *  SignalConversion generated from: '<S15>/Cos'
   *  Sum: '<S30>/Sum'
   *  Sum: '<S8>/Add2'
   *  Sum: '<S8>/Add4'
   *  Sum: '<S8>/Add5'
   *  Trigonometry: '<S8>/Sin'
   */
  rtb_Square_m_idx_0_tmp = (sin(rtb_MathFunction6_idx_0) * rtb_SumofElements2 +
    rtb_Square_m_idx_0) * 1.12 - rtb_Saturation_g_idx_0;
  rtb_Saturation_g_idx_1 = (sin(rtb_MathFunction6_idx_1) * rtb_SumofElements2 +
    rtb_Square_m_idx_1) * 1.12 - rtb_Saturation_g_idx_1;
  rtb_Square_m_idx_2_tmp = ((rtb_delta_fldelta_frrad_idx_0 - rtb_Divide_d) *
    rtb_Square_m_idx_2_tmp + sin(-rtP.toe_r) * rtb_Csi) * 1.12 -
    rtb_Saturation_g_idx_2;
  rtb_Saturation_g_0 = ((rtb_Divide_d + rtb_delta_fldelta_frrad_idx_0) *
                        rtb_vims_idx_3_tmp + sin(rtP.toe_r) * rtb_Csi) * 1.12 -
    rtb_Saturation_g_0;

  /* Saturate: '<Root>/Saturation3' incorporates:
   *  Inport: '<Root>/throttle'
   */
  if (rtU.throttle > 1.0) {
    rtb_Square_m_idx_0 = 1.0;
  } else if (rtU.throttle < 0.0) {
    rtb_Square_m_idx_0 = 0.0;
  } else {
    rtb_Square_m_idx_0 = rtU.throttle;
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  Saturate: '<Root>/Saturation3'
   */
  rtb_SumofElements2 = 2.0 * rtP.T_max * rtb_Square_m_idx_0;

  /* Sum: '<S1>/Add' incorporates:
   *  Sum: '<S80>/Sum'
   *  Sum: '<S80>/Sum1'
   */
  rtb_Saturation_g_idx_2 = rtb_Saturation_k + rtb_Add1_e;

  /* Product: '<S1>/Product' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Add'
   *  Sum: '<S1>/Add2'
   *  Sum: '<S1>/Subtract'
   */
  rtb_Csi = ((rtb_Saturation_g_idx_2 - 667.461609) * -0.00049402457842335622 +
             2.106129056) * rtb_Saturation_g_idx_2;

  /* Sum: '<S1>/Add1' */
  rtb_Divide_d = rtb_Product_o + rtb_Product2_h;

  /* Product: '<S1>/Divide' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  Gain: '<S1>/Gain1'
   *  Product: '<S1>/Product1'
   *  Sum: '<S1>/Add3'
   *  Sum: '<S1>/Add4'
   *  Sum: '<S1>/Subtract1'
   */
  rtb_Csi /= ((rtb_Divide_d - 667.461609) * -0.00049402457842335622 +
              2.106129056) * rtb_Divide_d + rtb_Csi;

  /* Sum: '<S9>/Add5' incorporates:
   *  Constant: '<S9>/Constant2'
   *  Gain: '<S9>/Gain4'
   */
  rtb_Divide_d = (1.0 - rtP.offset_throttle_csi) * rtb_Csi +
    rtP.offset_throttle_csi;

  /* Product: '<S9>/Divide' incorporates:
   *  Constant: '<S9>/Constant'
   *  Product: '<S9>/Divide1'
   *  Sum: '<S9>/Add'
   */
  rtb_Divide_d = 1.0 / (1.0 - rtb_Divide_d) * (rtb_Divide_d * rtb_SumofElements2);

  /* Product: '<S80>/Divide' */
  rtb_Product3_k = rtb_Saturation_k / rtb_Saturation_g_idx_2;

  /* Product: '<S80>/Divide1' incorporates:
   *  Sum: '<S80>/Add2'
   *  Sum: '<S80>/Sum'
   */
  rtb_Product2_h *= 1.0 / (((rtb_Saturation_g_idx_2 + rtb_Product_o) +
    rtb_Product2_h) - rtb_Saturation_g_idx_2);

  /* Saturate: '<S30>/Saturation' */
  if (rtb_Square_m_idx_0_tmp <= 0.0) {
    rtb_Square_m_idx_0_tmp = 0.0;
  }

  rtb_Saturation_g_idx_0 = rtb_Square_m_idx_0_tmp;

  /* Math: '<S10>/Square' incorporates:
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Square_m_idx_0 = rtb_Saturation_k * rtb_Saturation_k;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_Saturation_k, 3.0);

  /* Gain: '<S10>/Gain2' */
  rtb_delta_fldelta_frrad_idx_1 = -1.8682E-5 * rtb_Square_m_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_Saturation_k, 4.0);

  /* Gain: '<S10>/Gain3' */
  Transpose2 = 1.8267E-8 * rtb_MathFunction5_0;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_Saturation_k, 5.0);

  /* Gain: '<S10>/Gain4' */
  Transpose2_0 = -8.8652E-12 * rtb_vims_idx_3_tmp;

  /* Saturate: '<S10>/Saturation' */
  if (rtb_MathFunction6_idx_0 > 0.4) {
    rtb_MathFunction6_idx_0 = 0.4;
  } else if (rtb_MathFunction6_idx_0 < -0.4) {
    rtb_MathFunction6_idx_0 = -0.4;
  }

  /* Gain: '<S10>/Gain23' incorporates:
   *  Product: '<S10>/Product13'
   */
  rtb_Gain23_0 = rtb_MathFunction6_idx_0 * rtb_Square_m_idx_1 * -3.0722E-8;

  /* Gain: '<S10>/Gain24' incorporates:
   *  Product: '<S10>/Product12'
   */
  rtb_Gain24_0 = rtb_MathFunction6_idx_0 * rtb_MathFunction5_0 * -2.1326E-11;

  /* Gain: '<S10>/Gain25' incorporates:
   *  Product: '<S10>/Product11'
   */
  rtb_Gain25_0 = rtb_MathFunction6_idx_0 * rtb_vims_idx_3_tmp * 1.417E-14;

  /* Math: '<S10>/Square1' */
  rtb_Square_m_idx_1_tmp = rtb_MathFunction6_idx_0 * rtb_MathFunction6_idx_0;

  /* Gain: '<S10>/Gain21' incorporates:
   *  Product: '<S10>/Product8'
   */
  rtb_Gain21_0 = rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_1 * 1.7183E-5;

  /* Gain: '<S10>/Gain20' incorporates:
   *  Product: '<S10>/Product7'
   */
  rtb_Gain20_0 = rtb_Square_m_idx_1_tmp * rtb_MathFunction5_0 * -6.5431E-9;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_MathFunction6_idx_0, 3.0);

  /* Gain: '<S10>/Gain12' incorporates:
   *  Product: '<S10>/Product4'
   */
  rtb_Gain12_0 = rtb_vims_idx_3_tmp * rtb_Square_m_idx_1 * 1.2868E-9;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_MathFunction6_idx_0, 4.0);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_MathFunction6_idx_0, 5.0);

  /* Saturate: '<S10>/Saturation1' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain22'
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
   *  Sum: '<S10>/Add'
   */
  rtb_Square_m_idx_1 = ((((((((((((((((((((((((((0.2483 * rtb_Saturation_k +
    0.0088 * rtb_Square_m_idx_0) + rtb_delta_fldelta_frrad_idx_1) + Transpose2)
    + Transpose2_0) + 1.7349E-15 * rt_powd_snf(rtb_Saturation_k, 6.0)) +
    rtb_MathFunction6_idx_0 * rtb_Saturation_k * -0.00098788) +
    rtb_MathFunction6_idx_0 * rtb_Square_m_idx_0 * 5.2321E-5) + rtb_Gain23_0) +
    rtb_Gain24_0) + rtb_Gain25_0) + rtb_Square_m_idx_1_tmp * rtb_Saturation_k *
    -34.6685) + rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_0 * 2.9871E-5) +
    rtb_Gain21_0) + rtb_Gain20_0) + rtb_vims_idx_3_tmp * rtb_Saturation_k *
    -0.202) + rtb_vims_idx_3_tmp * rtb_Square_m_idx_0 * 0.00013761) +
    rtb_Gain12_0) + rtb_MathFunction5_0 * rtb_Saturation_k * 202.6574) +
    rtb_MathFunction5_0 * rtb_Square_m_idx_0 * -0.0863) + rtb_Square_m_idx_1 *
    rtb_Saturation_k * -0.1108) + 1.146 * rtb_MathFunction6_idx_0) + -12185.0 *
    rtb_Square_m_idx_1_tmp) + -10.876 * rtb_vims_idx_3_tmp) + 260290.0 *
    rtb_MathFunction5_0) + 346.9631 * rtb_Square_m_idx_1) + -1.4028E+6 *
                        rt_powd_snf(rtb_MathFunction6_idx_0, 6.0)) + 300.2078;

  /* Gain: '<Root>/Gain1' */
  rtb_vims_idx_3_tmp = 0.10471975511965977 * rtb_Saturation1_j_idx_0;
  rtb_Saturation_k = rtb_vims_idx_3_tmp;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_Square_m_idx_1 > 2500.0) {
    rtb_Square_m_idx_1 = 2500.0;
  } else if (rtb_Square_m_idx_1 < 50.0) {
    rtb_Square_m_idx_1 = 50.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Gain: '<S10>/Gain11'
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   */
  rtb_MathFunction6_idx_0 = rtb_Square_m_idx_1 * rtb_Saturation_e_idx_0 *
    0.078947160665366667;
  if ((rtP.T_max <= rtb_MathFunction6_idx_0) || rtIsNaN(rtb_MathFunction6_idx_0))
  {
    rtb_MathFunction6_idx_0 = rtP.T_max;
  }

  /* Saturate: '<S70>/Saturation' incorporates:
   *  DiscreteIntegrator: '<S63>/Integrator'
   *  Gain: '<S68>/Proportional Gain'
   *  Product: '<S10>/Product1'
   *  Sum: '<S72>/Sum'
   */
  rtb_Square_m_idx_1 = rtP.TC_map[0] * rtb_Square_m_idx_0_tmp +
    rtDW.Integrator_DSTATE[0];
  if (rtb_Square_m_idx_1 > 1.0) {
    rtb_Square_m_idx_1 = 1.0;
  } else if (rtb_Square_m_idx_1 < 0.0) {
    rtb_Square_m_idx_1 = 0.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Constant: '<S30>/Constant'
   *  Constant: '<S80>/Constant1'
   *  Gain: '<S80>/Multiply'
   *  Product: '<Root>/Product1'
   *  Product: '<S9>/Product'
   *  Saturate: '<S70>/Saturation'
   *  Sum: '<S30>/Sum1'
   *  Sum: '<S80>/Add3'
   */
  rtb_Square_m_idx_1 = ((1.0 - rtP.offset_cornering) * rtb_Product3_k +
                        rtP.offset_cornering) * rtb_Divide_d * (1.0 -
    rtb_Square_m_idx_1);
  if ((rtb_MathFunction6_idx_0 <= rtb_Square_m_idx_1) || rtIsNaN
      (rtb_Square_m_idx_1)) {
    rtb_Square_m_idx_1 = rtb_MathFunction6_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   */
  rtb_Saturation_e_idx_0 = rtb_Square_m_idx_1 * rtb_vims_idx_3_tmp;

  /* Saturate: '<S30>/Saturation' */
  if (rtb_Saturation_g_idx_1 <= 0.0) {
    rtb_Square_m_idx_0_tmp = 0.0;
  } else {
    rtb_Square_m_idx_0_tmp = rtb_Saturation_g_idx_1;
  }

  rtb_Saturation_g_idx_1 = rtb_Square_m_idx_0_tmp;

  /* Math: '<S10>/Square' incorporates:
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Square_m_idx_0 = rtb_Add1_e * rtb_Add1_e;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_Add1_e, 3.0);

  /* Gain: '<S10>/Gain2' */
  rtb_delta_fldelta_frrad_idx_1 = -1.8682E-5 * rtb_Square_m_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_Add1_e, 4.0);

  /* Gain: '<S10>/Gain3' */
  Transpose2 = 1.8267E-8 * rtb_MathFunction5_0;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_Add1_e, 5.0);

  /* Gain: '<S10>/Gain4' */
  Transpose2_0 = -8.8652E-12 * rtb_vims_idx_3_tmp;

  /* Saturate: '<S10>/Saturation' */
  if (rtb_MathFunction6_idx_1 > 0.4) {
    rtb_MathFunction6_idx_0 = 0.4;
  } else if (rtb_MathFunction6_idx_1 < -0.4) {
    rtb_MathFunction6_idx_0 = -0.4;
  } else {
    rtb_MathFunction6_idx_0 = rtb_MathFunction6_idx_1;
  }

  /* Gain: '<S10>/Gain23' incorporates:
   *  Product: '<S10>/Product13'
   */
  rtb_Gain23_0 = rtb_MathFunction6_idx_0 * rtb_Square_m_idx_1 * -3.0722E-8;

  /* Gain: '<S10>/Gain24' incorporates:
   *  Product: '<S10>/Product12'
   */
  rtb_Gain24_0 = rtb_MathFunction6_idx_0 * rtb_MathFunction5_0 * -2.1326E-11;

  /* Gain: '<S10>/Gain25' incorporates:
   *  Product: '<S10>/Product11'
   */
  rtb_Gain25_0 = rtb_MathFunction6_idx_0 * rtb_vims_idx_3_tmp * 1.417E-14;

  /* Math: '<S10>/Square1' */
  rtb_Square_m_idx_1_tmp = rtb_MathFunction6_idx_0 * rtb_MathFunction6_idx_0;

  /* Gain: '<S10>/Gain21' incorporates:
   *  Product: '<S10>/Product8'
   */
  rtb_Gain21_0 = rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_1 * 1.7183E-5;

  /* Gain: '<S10>/Gain20' incorporates:
   *  Product: '<S10>/Product7'
   */
  rtb_Gain20_0 = rtb_Square_m_idx_1_tmp * rtb_MathFunction5_0 * -6.5431E-9;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_MathFunction6_idx_0, 3.0);

  /* Gain: '<S10>/Gain12' incorporates:
   *  Product: '<S10>/Product4'
   */
  rtb_Gain12_0 = rtb_vims_idx_3_tmp * rtb_Square_m_idx_1 * 1.2868E-9;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_MathFunction6_idx_0, 4.0);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_MathFunction6_idx_0, 5.0);

  /* Saturate: '<S10>/Saturation1' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain22'
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
   *  Sum: '<S10>/Add'
   */
  rtb_Square_m_idx_1 = ((((((((((((((((((((((((((0.2483 * rtb_Add1_e + 0.0088 *
    rtb_Square_m_idx_0) + rtb_delta_fldelta_frrad_idx_1) + Transpose2) +
    Transpose2_0) + 1.7349E-15 * rt_powd_snf(rtb_Add1_e, 6.0)) +
    rtb_MathFunction6_idx_0 * rtb_Add1_e * -0.00098788) +
    rtb_MathFunction6_idx_0 * rtb_Square_m_idx_0 * 5.2321E-5) + rtb_Gain23_0) +
    rtb_Gain24_0) + rtb_Gain25_0) + rtb_Square_m_idx_1_tmp * rtb_Add1_e *
    -34.6685) + rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_0 * 2.9871E-5) +
    rtb_Gain21_0) + rtb_Gain20_0) + rtb_vims_idx_3_tmp * rtb_Add1_e * -0.202) +
    rtb_vims_idx_3_tmp * rtb_Square_m_idx_0 * 0.00013761) + rtb_Gain12_0) +
    rtb_MathFunction5_0 * rtb_Add1_e * 202.6574) + rtb_MathFunction5_0 *
    rtb_Square_m_idx_0 * -0.0863) + rtb_Square_m_idx_1 * rtb_Add1_e * -0.1108) +
    1.146 * rtb_MathFunction6_idx_0) + -12185.0 * rtb_Square_m_idx_1_tmp) +
    -10.876 * rtb_vims_idx_3_tmp) + 260290.0 * rtb_MathFunction5_0) + 346.9631 *
    rtb_Square_m_idx_1) + -1.4028E+6 * rt_powd_snf(rtb_MathFunction6_idx_0, 6.0))
    + 300.2078;

  /* Gain: '<Root>/Gain1' */
  rtb_vims_idx_3_tmp = 0.10471975511965977 * rtb_Saturation1_j_idx_1;
  rtb_MathFunction6_idx_1 = rtb_vims_idx_3_tmp;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_Square_m_idx_1 > 2500.0) {
    rtb_Square_m_idx_1 = 2500.0;
  } else if (rtb_Square_m_idx_1 < 50.0) {
    rtb_Square_m_idx_1 = 50.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Gain: '<S10>/Gain11'
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   */
  rtb_MathFunction6_idx_0 = rtb_Square_m_idx_1 * rtb_Saturation_e_idx_1 *
    0.078947160665366667;
  if ((rtP.T_max <= rtb_MathFunction6_idx_0) || rtIsNaN(rtb_MathFunction6_idx_0))
  {
    rtb_MathFunction6_idx_0 = rtP.T_max;
  }

  /* Saturate: '<S70>/Saturation' incorporates:
   *  DiscreteIntegrator: '<S63>/Integrator'
   *  Gain: '<S68>/Proportional Gain'
   *  Product: '<S10>/Product1'
   *  Sum: '<S72>/Sum'
   */
  rtb_Square_m_idx_1 = rtP.TC_map[0] * rtb_Square_m_idx_0_tmp +
    rtDW.Integrator_DSTATE[1];
  if (rtb_Square_m_idx_1 > 1.0) {
    rtb_Square_m_idx_1 = 1.0;
  } else if (rtb_Square_m_idx_1 < 0.0) {
    rtb_Square_m_idx_1 = 0.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Constant: '<S30>/Constant'
   *  Constant: '<S80>/Constant'
   *  Constant: '<S80>/Constant1'
   *  Gain: '<S80>/Multiply'
   *  Product: '<Root>/Product1'
   *  Product: '<S9>/Product'
   *  Saturate: '<S70>/Saturation'
   *  Sum: '<S30>/Sum1'
   *  Sum: '<S80>/Add'
   *  Sum: '<S80>/Add3'
   */
  rtb_Square_m_idx_1 = ((1.0 - rtP.offset_cornering) * (1.0 - rtb_Product3_k) +
                        rtP.offset_cornering) * rtb_Divide_d * (1.0 -
    rtb_Square_m_idx_1);
  if ((rtb_MathFunction6_idx_0 <= rtb_Square_m_idx_1) || rtIsNaN
      (rtb_Square_m_idx_1)) {
    rtb_Square_m_idx_1 = rtb_MathFunction6_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   */
  rtb_Saturation_e_idx_1 = rtb_Square_m_idx_1 * rtb_vims_idx_3_tmp;

  /* Saturate: '<S30>/Saturation' */
  if (rtb_Square_m_idx_2_tmp <= 0.0) {
    rtb_Square_m_idx_0_tmp = 0.0;
  } else {
    rtb_Square_m_idx_0_tmp = rtb_Square_m_idx_2_tmp;
  }

  rtb_Saturation_g_idx_2 = rtb_Square_m_idx_0_tmp;

  /* Math: '<S10>/Square' incorporates:
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Square_m_idx_0 = rtb_Product_o * rtb_Product_o;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_Product_o, 3.0);

  /* Gain: '<S10>/Gain2' */
  rtb_delta_fldelta_frrad_idx_1 = -1.8682E-5 * rtb_Square_m_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_Product_o, 4.0);

  /* Gain: '<S10>/Gain3' */
  Transpose2 = 1.8267E-8 * rtb_MathFunction5_0;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  SignalConversion generated from: '<S10>/Math Function'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_Product_o, 5.0);

  /* Gain: '<S10>/Gain4' */
  Transpose2_0 = -8.8652E-12 * rtb_vims_idx_3_tmp;

  /* Saturate: '<S10>/Saturation' incorporates:
   *  Constant: '<S12>/Constant4'
   *  Gain: '<S12>/Gain'
   */
  if (-rtP.toe_r > 0.4) {
    rtb_MathFunction6_idx_0 = 0.4;
  } else if (-rtP.toe_r < -0.4) {
    rtb_MathFunction6_idx_0 = -0.4;
  } else {
    rtb_MathFunction6_idx_0 = -rtP.toe_r;
  }

  /* Gain: '<S10>/Gain23' incorporates:
   *  Product: '<S10>/Product13'
   */
  rtb_Gain23_0 = rtb_MathFunction6_idx_0 * rtb_Square_m_idx_1 * -3.0722E-8;

  /* Gain: '<S10>/Gain24' incorporates:
   *  Product: '<S10>/Product12'
   */
  rtb_Gain24_0 = rtb_MathFunction6_idx_0 * rtb_MathFunction5_0 * -2.1326E-11;

  /* Gain: '<S10>/Gain25' incorporates:
   *  Product: '<S10>/Product11'
   */
  rtb_Gain25_0 = rtb_MathFunction6_idx_0 * rtb_vims_idx_3_tmp * 1.417E-14;

  /* Math: '<S10>/Square1' */
  rtb_Square_m_idx_1_tmp = rtb_MathFunction6_idx_0 * rtb_MathFunction6_idx_0;

  /* Gain: '<S10>/Gain21' incorporates:
   *  Product: '<S10>/Product8'
   */
  rtb_Gain21_0 = rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_1 * 1.7183E-5;

  /* Gain: '<S10>/Gain20' incorporates:
   *  Product: '<S10>/Product7'
   */
  rtb_Gain20_0 = rtb_Square_m_idx_1_tmp * rtb_MathFunction5_0 * -6.5431E-9;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_MathFunction6_idx_0, 3.0);

  /* Gain: '<S10>/Gain12' incorporates:
   *  Product: '<S10>/Product4'
   */
  rtb_Gain12_0 = rtb_vims_idx_3_tmp * rtb_Square_m_idx_1 * 1.2868E-9;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_MathFunction6_idx_0, 4.0);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_MathFunction6_idx_0, 5.0);

  /* Saturate: '<S10>/Saturation1' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain22'
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
   *  Sum: '<S10>/Add'
   */
  rtb_Square_m_idx_1 = ((((((((((((((((((((((((((0.2483 * rtb_Product_o + 0.0088
    * rtb_Square_m_idx_0) + rtb_delta_fldelta_frrad_idx_1) + Transpose2) +
    Transpose2_0) + 1.7349E-15 * rt_powd_snf(rtb_Product_o, 6.0)) +
    rtb_MathFunction6_idx_0 * rtb_Product_o * -0.00098788) +
    rtb_MathFunction6_idx_0 * rtb_Square_m_idx_0 * 5.2321E-5) + rtb_Gain23_0) +
    rtb_Gain24_0) + rtb_Gain25_0) + rtb_Square_m_idx_1_tmp * rtb_Product_o *
    -34.6685) + rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_0 * 2.9871E-5) +
    rtb_Gain21_0) + rtb_Gain20_0) + rtb_vims_idx_3_tmp * rtb_Product_o * -0.202)
    + rtb_vims_idx_3_tmp * rtb_Square_m_idx_0 * 0.00013761) + rtb_Gain12_0) +
    rtb_MathFunction5_0 * rtb_Product_o * 202.6574) + rtb_MathFunction5_0 *
    rtb_Square_m_idx_0 * -0.0863) + rtb_Square_m_idx_1 * rtb_Product_o * -0.1108)
    + 1.146 * rtb_MathFunction6_idx_0) + -12185.0 * rtb_Square_m_idx_1_tmp) +
    -10.876 * rtb_vims_idx_3_tmp) + 260290.0 * rtb_MathFunction5_0) + 346.9631 *
    rtb_Square_m_idx_1) + -1.4028E+6 * rt_powd_snf(rtb_MathFunction6_idx_0, 6.0))
    + 300.2078;

  /* Gain: '<Root>/Gain1' */
  rtb_vims_idx_3_tmp = 0.10471975511965977 * rtb_Saturation1_j_idx_2;
  rtb_Product_o = rtb_vims_idx_3_tmp;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_Square_m_idx_1 > 2500.0) {
    rtb_Square_m_idx_1 = 2500.0;
  } else if (rtb_Square_m_idx_1 < 50.0) {
    rtb_Square_m_idx_1 = 50.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Gain: '<S10>/Gain11'
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   */
  rtb_MathFunction6_idx_0 = rtb_Square_m_idx_1 * rtb_Saturation_e_idx_2 *
    0.078947160665366667;
  if ((rtP.T_max <= rtb_MathFunction6_idx_0) || rtIsNaN(rtb_MathFunction6_idx_0))
  {
    rtb_MathFunction6_idx_0 = rtP.T_max;
  }

  /* Saturate: '<S70>/Saturation' incorporates:
   *  DiscreteIntegrator: '<S63>/Integrator'
   *  Gain: '<S68>/Proportional Gain'
   *  Product: '<S10>/Product1'
   *  Sum: '<S72>/Sum'
   */
  rtb_Square_m_idx_1 = rtP.TC_map[0] * rtb_Square_m_idx_0_tmp +
    rtDW.Integrator_DSTATE[2];
  if (rtb_Square_m_idx_1 > 1.0) {
    rtb_Square_m_idx_1 = 1.0;
  } else if (rtb_Square_m_idx_1 < 0.0) {
    rtb_Square_m_idx_1 = 0.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Constant: '<S30>/Constant'
   *  Constant: '<S80>/Constant'
   *  Constant: '<S80>/Constant1'
   *  Gain: '<S80>/Multiply'
   *  Product: '<Root>/Product1'
   *  Product: '<S9>/Product'
   *  Saturate: '<S70>/Saturation'
   *  Sum: '<S30>/Sum1'
   *  Sum: '<S80>/Add1'
   *  Sum: '<S80>/Add3'
   */
  rtb_Square_m_idx_1 = ((1.0 - rtP.offset_cornering) * (1.0 - rtb_Product2_h) +
                        rtP.offset_cornering) * rtb_SumofElements2 * (1.0 -
    rtb_Square_m_idx_1);
  if ((rtb_MathFunction6_idx_0 <= rtb_Square_m_idx_1) || rtIsNaN
      (rtb_Square_m_idx_1)) {
    rtb_Square_m_idx_1 = rtb_MathFunction6_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   */
  rtb_Saturation_e_idx_2 = rtb_Square_m_idx_1 * rtb_vims_idx_3_tmp;

  /* Saturate: '<S30>/Saturation' */
  if (rtb_Saturation_g_0 <= 0.0) {
    rtb_Square_m_idx_0_tmp = 0.0;
  } else {
    rtb_Square_m_idx_0_tmp = rtb_Saturation_g_0;
  }

  /* Math: '<S10>/Square' */
  rtb_Square_m_idx_0 = rtb_Sum1_p * rtb_Sum1_p;

  /* Math: '<S10>/Math Function' incorporates:
   *  Constant: '<S10>/Constant'
   *  Math: '<S10>/Square'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_Sum1_p, 3.0);

  /* Gain: '<S10>/Gain2' */
  rtb_delta_fldelta_frrad_idx_1 = -1.8682E-5 * rtb_Square_m_idx_1;

  /* Math: '<S10>/Math Function1' incorporates:
   *  Constant: '<S10>/Constant1'
   *  Math: '<S10>/Square'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_Sum1_p, 4.0);

  /* Gain: '<S10>/Gain3' */
  Transpose2 = 1.8267E-8 * rtb_MathFunction5_0;

  /* Math: '<S10>/Math Function3' incorporates:
   *  Constant: '<S10>/Constant2'
   *  Math: '<S10>/Square'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_Sum1_p, 5.0);

  /* Gain: '<S10>/Gain4' */
  Transpose2_0 = -8.8652E-12 * rtb_vims_idx_3_tmp;

  /* Saturate: '<S10>/Saturation' incorporates:
   *  Constant: '<S12>/Constant4'
   *  SignalConversion generated from: '<S15>/Cos'
   */
  if (rtP.toe_r > 0.4) {
    rtb_MathFunction6_idx_0 = 0.4;
  } else if (rtP.toe_r < -0.4) {
    rtb_MathFunction6_idx_0 = -0.4;
  } else {
    rtb_MathFunction6_idx_0 = rtP.toe_r;
  }

  /* Gain: '<S10>/Gain23' incorporates:
   *  Product: '<S10>/Product13'
   */
  rtb_Gain23_0 = rtb_MathFunction6_idx_0 * rtb_Square_m_idx_1 * -3.0722E-8;

  /* Gain: '<S10>/Gain24' incorporates:
   *  Product: '<S10>/Product12'
   */
  rtb_Gain24_0 = rtb_MathFunction6_idx_0 * rtb_MathFunction5_0 * -2.1326E-11;

  /* Gain: '<S10>/Gain25' incorporates:
   *  Product: '<S10>/Product11'
   */
  rtb_Gain25_0 = rtb_MathFunction6_idx_0 * rtb_vims_idx_3_tmp * 1.417E-14;

  /* Math: '<S10>/Square1' */
  rtb_Square_m_idx_1_tmp = rtb_MathFunction6_idx_0 * rtb_MathFunction6_idx_0;

  /* Gain: '<S10>/Gain21' incorporates:
   *  Product: '<S10>/Product8'
   */
  rtb_Gain21_0 = rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_1 * 1.7183E-5;

  /* Gain: '<S10>/Gain20' incorporates:
   *  Product: '<S10>/Product7'
   */
  rtb_Gain20_0 = rtb_Square_m_idx_1_tmp * rtb_MathFunction5_0 * -6.5431E-9;

  /* Math: '<S10>/Math Function4' incorporates:
   *  Constant: '<S10>/Constant4'
   */
  rtb_vims_idx_3_tmp = rt_powd_snf(rtb_MathFunction6_idx_0, 3.0);

  /* Gain: '<S10>/Gain12' incorporates:
   *  Product: '<S10>/Product4'
   */
  rtb_Gain12_0 = rtb_vims_idx_3_tmp * rtb_Square_m_idx_1 * 1.2868E-9;

  /* Math: '<S10>/Math Function5' incorporates:
   *  Constant: '<S10>/Constant5'
   */
  rtb_MathFunction5_0 = rt_powd_snf(rtb_MathFunction6_idx_0, 4.0);

  /* Math: '<S10>/Math Function7' incorporates:
   *  Constant: '<S10>/Constant6'
   */
  rtb_Square_m_idx_1 = rt_powd_snf(rtb_MathFunction6_idx_0, 5.0);

  /* Saturate: '<S10>/Saturation1' incorporates:
   *  Constant: '<S10>/Constant3'
   *  Constant: '<S10>/Constant7'
   *  Constant: '<S10>/Constant8'
   *  Gain: '<S10>/Gain'
   *  Gain: '<S10>/Gain1'
   *  Gain: '<S10>/Gain10'
   *  Gain: '<S10>/Gain13'
   *  Gain: '<S10>/Gain14'
   *  Gain: '<S10>/Gain15'
   *  Gain: '<S10>/Gain16'
   *  Gain: '<S10>/Gain17'
   *  Gain: '<S10>/Gain18'
   *  Gain: '<S10>/Gain19'
   *  Gain: '<S10>/Gain22'
   *  Gain: '<S10>/Gain26'
   *  Gain: '<S10>/Gain27'
   *  Gain: '<S10>/Gain5'
   *  Gain: '<S10>/Gain6'
   *  Gain: '<S10>/Gain7'
   *  Gain: '<S10>/Gain8'
   *  Gain: '<S10>/Gain9'
   *  Math: '<S10>/Math Function2'
   *  Math: '<S10>/Math Function6'
   *  Math: '<S10>/Square'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product10'
   *  Product: '<S10>/Product14'
   *  Product: '<S10>/Product15'
   *  Product: '<S10>/Product2'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product5'
   *  Product: '<S10>/Product6'
   *  Product: '<S10>/Product9'
   *  Sum: '<S10>/Add'
   */
  rtb_Square_m_idx_1 = ((((((((((((((((((((((((((0.2483 * rtb_Sum1_p + 0.0088 *
    rtb_Square_m_idx_0) + rtb_delta_fldelta_frrad_idx_1) + Transpose2) +
    Transpose2_0) + 1.7349E-15 * rt_powd_snf(rtb_Sum1_p, 6.0)) +
    rtb_MathFunction6_idx_0 * rtb_Sum1_p * -0.00098788) +
    rtb_MathFunction6_idx_0 * rtb_Square_m_idx_0 * 5.2321E-5) + rtb_Gain23_0) +
    rtb_Gain24_0) + rtb_Gain25_0) + rtb_Square_m_idx_1_tmp * rtb_Sum1_p *
    -34.6685) + rtb_Square_m_idx_1_tmp * rtb_Square_m_idx_0 * 2.9871E-5) +
    rtb_Gain21_0) + rtb_Gain20_0) + rtb_vims_idx_3_tmp * rtb_Sum1_p * -0.202) +
    rtb_vims_idx_3_tmp * rtb_Square_m_idx_0 * 0.00013761) + rtb_Gain12_0) +
    rtb_MathFunction5_0 * rtb_Sum1_p * 202.6574) + rtb_MathFunction5_0 *
    rtb_Square_m_idx_0 * -0.0863) + rtb_Square_m_idx_1 * rtb_Sum1_p * -0.1108) +
    1.146 * rtb_MathFunction6_idx_0) + -12185.0 * rtb_Square_m_idx_1_tmp) +
    -10.876 * rtb_vims_idx_3_tmp) + 260290.0 * rtb_MathFunction5_0) + 346.9631 *
    rtb_Square_m_idx_1) + -1.4028E+6 * rt_powd_snf(rtb_MathFunction6_idx_0, 6.0))
    + 300.2078;

  /* Gain: '<Root>/Gain1' incorporates:
   *  Saturate: '<Root>/Saturation5'
   */
  rtb_vims_idx_3_tmp = 0.10471975511965977 * rtb_MathFunction6_idx_0_tmp;

  /* Saturate: '<S10>/Saturation1' */
  if (rtb_Square_m_idx_1 > 2500.0) {
    rtb_Square_m_idx_1 = 2500.0;
  } else if (rtb_Square_m_idx_1 < 50.0) {
    rtb_Square_m_idx_1 = 50.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Gain: '<S10>/Gain11'
   *  Product: '<S10>/Product1'
   *  Saturate: '<S10>/Saturation1'
   *  Saturate: '<S5>/Saturation'
   */
  rtb_MathFunction6_idx_0 = rtb_Square_m_idx_1 * u0 * 0.078947160665366667;
  if ((rtP.T_max <= rtb_MathFunction6_idx_0) || rtIsNaN(rtb_MathFunction6_idx_0))
  {
    rtb_MathFunction6_idx_0 = rtP.T_max;
  }

  /* Saturate: '<S70>/Saturation' incorporates:
   *  DiscreteIntegrator: '<S63>/Integrator'
   *  Gain: '<S68>/Proportional Gain'
   *  Product: '<S10>/Product1'
   *  Sum: '<S72>/Sum'
   */
  u0 = rtP.TC_map[0] * rtb_Square_m_idx_0_tmp + rtDW.Integrator_DSTATE[3];
  if (u0 > 1.0) {
    u0 = 1.0;
  } else if (u0 < 0.0) {
    u0 = 0.0;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Constant: '<S30>/Constant'
   *  Constant: '<S80>/Constant1'
   *  Gain: '<S80>/Multiply'
   *  Product: '<Root>/Product1'
   *  Product: '<S9>/Product'
   *  Saturate: '<S70>/Saturation'
   *  Sum: '<S30>/Sum1'
   *  Sum: '<S80>/Add3'
   */
  rtb_Square_m_idx_1 = ((1.0 - rtP.offset_cornering) * rtb_Product2_h +
                        rtP.offset_cornering) * rtb_SumofElements2 * (1.0 - u0);
  if ((rtb_MathFunction6_idx_0 <= rtb_Square_m_idx_1) || rtIsNaN
      (rtb_Square_m_idx_1)) {
    rtb_Square_m_idx_1 = rtb_MathFunction6_idx_0;
  }

  /* Product: '<S4>/Product2' incorporates:
   *  MinMax: '<Root>/Min'
   *  Product: '<S10>/Product1'
   */
  rtb_Square_m_idx_1_tmp = rtb_Square_m_idx_1 * rtb_vims_idx_3_tmp;

  /* Sum: '<S22>/Add' incorporates:
   *  Product: '<S4>/Product2'
   */
  rtb_Add1_e = ((rtb_Saturation_e_idx_0 + rtb_Saturation_e_idx_1) +
                rtb_Saturation_e_idx_2) + rtb_Square_m_idx_1_tmp;

  /* MinMax: '<S22>/Max' */
  if (rtb_Add1_e >= 0.1) {
    rtb_SumofElements2 = rtb_Add1_e;
  } else {
    rtb_SumofElements2 = 0.1;
  }

  /* End of MinMax: '<S22>/Max' */

  /* MinMax: '<S22>/Min' */
  if ((!(rtb_Add1_e <= rtP.Pmax)) && (!rtIsNaN(rtP.Pmax))) {
    rtb_Add1_e = rtP.Pmax;
  }

  /* End of MinMax: '<S22>/Min' */

  /* MinMax: '<S4>/Max' */
  if (rtb_Saturation_k >= 0.1) {
    rtb_Square_m_idx_0 = rtb_Saturation_k;
  } else {
    rtb_Square_m_idx_0 = 0.1;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  rtY.T_pos[0] = rtb_Saturation_e_idx_0 / rtb_SumofElements2 * rtb_Add1_e /
    rtb_Square_m_idx_0 * (real_T)(rtb_Saturation_k <= 2094.3951023931954);

  /* MinMax: '<S4>/Max' */
  if (rtb_MathFunction6_idx_1 >= 0.1) {
    rtb_Square_m_idx_0 = rtb_MathFunction6_idx_1;
  } else {
    rtb_Square_m_idx_0 = 0.1;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  rtY.T_pos[1] = rtb_Saturation_e_idx_1 / rtb_SumofElements2 * rtb_Add1_e /
    rtb_Square_m_idx_0 * (real_T)(rtb_MathFunction6_idx_1 <= 2094.3951023931954);

  /* MinMax: '<S4>/Max' */
  if (rtb_Product_o >= 0.1) {
    rtb_Square_m_idx_0 = rtb_Product_o;
  } else {
    rtb_Square_m_idx_0 = 0.1;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  RelationalOperator: '<S4>/Equal'
   */
  rtY.T_pos[2] = rtb_Saturation_e_idx_2 / rtb_SumofElements2 * rtb_Add1_e /
    rtb_Square_m_idx_0 * (real_T)(rtb_Product_o <= 2094.3951023931954);

  /* MinMax: '<S4>/Max' incorporates:
   *  Gain: '<Root>/Gain1'
   */
  if (rtb_vims_idx_3_tmp >= 0.1) {
    rtb_Square_m_idx_0 = rtb_vims_idx_3_tmp;
  } else {
    rtb_Square_m_idx_0 = 0.1;
  }

  /* Outport: '<Root>/T_pos' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Gain: '<Root>/Gain1'
   *  MinMax: '<S4>/Max'
   *  Product: '<S22>/Divide'
   *  Product: '<S22>/Divide2'
   *  Product: '<S4>/Divide'
   *  Product: '<S4>/Divide1'
   *  Product: '<S4>/Product2'
   *  RelationalOperator: '<S4>/Equal'
   */
  rtY.T_pos[3] = rtb_Square_m_idx_1_tmp / rtb_SumofElements2 * rtb_Add1_e /
    rtb_Square_m_idx_0 * (real_T)(rtb_vims_idx_3_tmp <= 2094.3951023931954);

  /* Saturate: '<Root>/Saturation8' incorporates:
   *  Inport: '<Root>/voltage'
   */
  if (rtU.voltage > 600.0) {
    rtb_Add1_e = 600.0;
  } else if (rtU.voltage < 0.0) {
    rtb_Add1_e = 0.0;
  } else {
    rtb_Add1_e = rtU.voltage;
  }

  /* End of Saturate: '<Root>/Saturation8' */

  /* Saturate: '<Root>/Saturation4' incorporates:
   *  Inport: '<Root>/regen paddle'
   */
  if (rtU.regenpaddle > 1.0) {
    rtb_SumofElements2 = 1.0;
  } else if (rtU.regenpaddle < 0.0) {
    rtb_SumofElements2 = 0.0;
  } else {
    rtb_SumofElements2 = rtU.regenpaddle;
  }

  /* End of Saturate: '<Root>/Saturation4' */

  /* Sum: '<S24>/Add1' incorporates:
   *  Constant: '<S24>/Constant'
   *  Delay: '<S24>/Delay1'
   *  Memory: '<S24>/Memory'
   *  Product: '<S24>/Product2'
   */
  rtb_Product2_h = 0.70000000000000007 * (real_T)rtDW.Delay1_DSTATE[0] +
    rtDW.Memory_PreviousInput_b;

  /* RelationalOperator: '<S23>/Compare' incorporates:
   *  Constant: '<S23>/Constant'
   */
  rtb_Compare_m = (rtb_SumofElements2 > 0.0);

  /* Gain: '<S6>/Gain' incorporates:
   *  Constant: '<S6>/Max battery voltage'
   *  Sum: '<S6>/Subtract'
   */
  u0 = (564.96 - rtb_Add1_e) * 2.730524533762936;

  /* Product: '<S6>/Product' incorporates:
   *  Constant: '<S6>/Constant'
   */
  rtb_MathFunction6_idx_0 = 100.0 * rtb_SumofElements2;

  /* MinMax: '<S6>/Imax' */
  if ((u0 <= rtb_MathFunction6_idx_0) || rtIsNaN(rtb_MathFunction6_idx_0)) {
    rtb_MathFunction6_idx_0 = u0;
  }

  /* Saturate: '<S24>/Saturation' incorporates:
   *  Constant: '<S24>/Constant1'
   *  Sum: '<S24>/Add'
   */
  if (100.0 - rtb_Product2_h > 100.0) {
    rtb_Square_m_idx_0 = 100.0;
  } else if (100.0 - rtb_Product2_h < 65.0) {
    rtb_Square_m_idx_0 = 65.0;
  } else {
    rtb_Square_m_idx_0 = 100.0 - rtb_Product2_h;
  }

  /* Product: '<S24>/Product' incorporates:
   *  Saturate: '<S24>/Saturation'
   */
  rtb_Product3_k = rtb_Square_m_idx_0 * (real_T)rtb_Compare_m;

  /* MinMax: '<S6>/Imax' */
  if ((rtb_MathFunction6_idx_0 <= rtb_Product3_k) || rtIsNaN(rtb_Product3_k)) {
    rtb_Product3_k = rtb_MathFunction6_idx_0;
  }

  /* Gain: '<S7>/Gain' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Product: '<S6>/Product1'
   *  Sum: '<S6>/Tot voltage'
   */
  rtb_Saturation_k = (0.36623 * rtb_Product3_k + rtb_Add1_e) * rtb_Product3_k *
    1.0204081632653061;

  /* Saturate: '<S7>/Saturation1' incorporates:
   *  Saturate: '<Root>/Saturation5'
   */
  if (rtb_Saturation1_j_idx_0 > 2094.3951023931954) {
    rtb_Saturation1_j_idx_0 = 2094.3951023931954;
  }

  if (rtb_Saturation1_j_idx_1 > 2094.3951023931954) {
    rtb_Saturation1_j_idx_1 = 2094.3951023931954;
  }

  if (rtb_Saturation1_j_idx_2 > 2094.3951023931954) {
    rtb_Saturation1_j_idx_2 = 2094.3951023931954;
  }

  if (rtb_MathFunction6_idx_0_tmp > 2094.3951023931954) {
    rtb_MathFunction6_idx_0_tmp = 2094.3951023931954;
  }

  /* Gain: '<S7>/Gain1' incorporates:
   *  Saturate: '<S7>/Saturation1'
   *  Sum: '<S7>/Add1'
   */
  rtb_Add1_e = (((rtb_Saturation1_j_idx_0 + rtb_Saturation1_j_idx_1) +
                 rtb_Saturation1_j_idx_2) + rtb_MathFunction6_idx_0_tmp) * 0.25;

  /* Gain: '<S25>/Gain5' */
  rtb_Divide_d = 5.0 * rtb_Add1_e;

  /* Gain: '<S28>/Gain4' incorporates:
   *  Constant: '<S28>/Constant'
   *  Gain: '<S28>/Gain6'
   *  Sum: '<S28>/Add1'
   */
  rtb_Product3_k = (2.0271088232297343E-5 * rtb_Divide_d + 0.069426173522444928)
    * 1.5;

  /* Gain: '<S28>/2a' */
  rtb_Product_o = 2.0 * rtb_Product3_k;

  /* Gain: '<S28>/Gain3' */
  rtb_SumofElements2 = 0.0444 * rtb_Divide_d;

  /* Sum: '<S28>/Add3' incorporates:
   *  Gain: '<S28>/4a'
   *  Math: '<S28>/b^2'
   *  Product: '<S28>/4ac'
   */
  rtb_Product3_k = 4.0 * rtb_Product3_k * rtb_Saturation_k + rtb_SumofElements2 *
    rtb_SumofElements2;

  /* Sqrt: '<S28>/Signed Sqrt'
   *
   * About '<S28>/Signed Sqrt':
   *  Operator: signedSqrt
   */
  if (rtb_Product3_k < 0.0) {
    rtb_Square_m_idx_0 = -sqrt(fabs(rtb_Product3_k));
  } else {
    rtb_Square_m_idx_0 = sqrt(rtb_Product3_k);
  }

  /* Product: '<S28>/Iq' incorporates:
   *  Sqrt: '<S28>/Signed Sqrt'
   *  Sum: '<S28>/Subtract'
   *
   * About '<S28>/Signed Sqrt':
   *  Operator: signedSqrt
   */
  rtb_Product_o = 1.0 / rtb_Product_o * (rtb_Square_m_idx_0 - rtb_SumofElements2);

  /* Gain: '<S28>/Gain1' */
  rtb_Product3_k = -0.16892573526914451 * rtb_Product_o;

  /* Math: '<S28>/Power1' */
  rtb_Product3_k *= rtb_Product3_k;

  /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
   *  Constant: '<S25>/Constant'
   *  RelationalOperator: '<S25>/Equal1'
   */
  if (rtb_Saturation_k != 0.0) {
    rtb_Divide_d = 0.0;
    rtb_SumofElements2 = 0.0;
  } else {
    rtb_Divide_d = rtb_Saturation_k / 154.5855345755223 / rtb_Divide_d;
    rtb_SumofElements2 = (3.552E-6 - sqrt((0.02032128 - rtb_Divide_d *
      rtb_Divide_d) * 4.32E-8 + 5.0466816E-11)) / 4.32E-8;
    rtb_Divide_d = rtb_SumofElements2 * rtb_SumofElements2;
    rtb_SumofElements2 = 352800.0 - rtb_Divide_d * rtb_Divide_d;
  }

  /* End of MATLAB Function: '<S25>/MATLAB Function' */

  /* Switch: '<S25>/Switch1' incorporates:
   *  Gain: '<S25>/Gain7'
   *  RelationalOperator: '<S25>/Equal'
   *  Switch: '<S25>/Switch'
   */
  if (0.047619047619047616 * rtb_Saturation_k < rtb_Add1_e) {
    /* Math: '<S28>/Power2' */
    rtb_SumofElements2 = rtb_Product_o * rtb_Product_o;

    /* MinMax: '<S28>/Max' incorporates:
     *  Constant: '<S28>/Constant1'
     *  Sum: '<S28>/Add2'
     */
    if ((352800.0 - rtb_Product3_k >= rtb_SumofElements2) || rtIsNaN
        (rtb_SumofElements2)) {
      rtb_SumofElements2 = 352800.0 - rtb_Product3_k;
    }

    /* End of MinMax: '<S28>/Max' */
    rtb_Divide_d = rtb_Product3_k;
  }

  /* End of Switch: '<S25>/Switch1' */

  /* Sum: '<S26>/Subtract1' incorporates:
   *  Constant: '<S26>/Constant'
   *  Gain: '<S26>/Gain'
   */
  u0 = 9.5492965855137211 * rtb_Add1_e - 13000.0;

  /* MinMax: '<S7>/Max' */
  if (rtb_Add1_e >= 1.0E-7) {
    rtb_Square_m_idx_0 = rtb_Add1_e;
  } else {
    rtb_Square_m_idx_0 = 1.0E-7;
  }

  /* Product: '<S7>/Tmax' incorporates:
   *  Gain: '<S25>/Gain'
   *  MinMax: '<S7>/Max'
   *  Product: '<S25>/Divide'
   *  Sum: '<S25>/Add'
   *  Sum: '<S7>/Ptot'
   *  Switch: '<S25>/Switch'
   */
  rtb_Square_m_idx_1 = ((rtb_Divide_d + rtb_SumofElements2) * 0.10125 *
                        rtb_Saturation_k + rtb_Saturation_k) /
    rtb_Square_m_idx_0;

  /* Saturate: '<S26>/Saturation' */
  if (u0 < 0.0) {
    u0 = 0.0;
  }

  /* Sum: '<S26>/Subtract' incorporates:
   *  Constant: '<S26>/Constant1'
   *  Gain: '<S26>/Gain1'
   *  Saturate: '<S26>/Saturation'
   */
  rtb_MathFunction6_idx_0 = 21.0 - 0.000857 * u0;

  /* MinMax: '<S7>/Min' */
  if ((rtb_Square_m_idx_1 <= rtb_MathFunction6_idx_0) || rtIsNaN
      (rtb_MathFunction6_idx_0)) {
    rtb_MathFunction6_idx_0 = rtb_Square_m_idx_1;
  }

  /* Product: '<S7>/Divide1' incorporates:
   *  Constant: '<S7>/Constant4'
   *  MinMax: '<S7>/Min'
   *  RelationalOperator: '<S7>/GreaterThan'
   */
  rtb_Add1_e = (real_T)(rtb_Add1_e > 0.0) * rtb_MathFunction6_idx_0;

  /* Sum: '<Root>/Add5' incorporates:
   *  Constant: '<Root>/Constant2'
   *  Gain: '<Root>/Gain12'
   */
  rtb_Product3_k = (1.0 - rtP.offset_brake_csi) * rtb_Csi + rtP.offset_brake_csi;

  /* Saturate: '<Root>/Saturation7' incorporates:
   *  Inport: '<Root>/brake pressure front'
   */
  if (rtU.brakepressurefront > 1.0E+7) {
    rtb_Square_m_idx_0 = 1.0E+7;
  } else if (rtU.brakepressurefront < 0.0) {
    rtb_Square_m_idx_0 = 0.0;
  } else {
    rtb_Square_m_idx_0 = rtU.brakepressurefront;
  }

  /* Saturate: '<Root>/Saturation9' incorporates:
   *  Inport: '<Root>/brake pressure rear'
   */
  if (rtU.brakepressurerear > 1.0E+7) {
    rtb_Divide_d = 1.0E+7;
  } else if (rtU.brakepressurerear < 0.0) {
    rtb_Divide_d = 0.0;
  } else {
    rtb_Divide_d = rtU.brakepressurerear;
  }

  /* Sum: '<S27>/Add1' incorporates:
   *  Constant: '<S27>/Constant3'
   *  Gain: '<S27>/Gain'
   *  Gain: '<S27>/Gain1'
   *  Product: '<S27>/Divide1'
   *  Product: '<S27>/Divide2'
   *  Saturate: '<Root>/Saturation7'
   *  Saturate: '<Root>/Saturation9'
   *  Sum: '<S27>/Add'
   */
  u0 = ((1.0 - rtb_Product3_k) * (0.000207157153 * rtb_Square_m_idx_0) +
        rtb_Add1_e) - 0.00010373444249999999 * rtb_Divide_d * rtb_Product3_k;

  /* MinMax: '<S27>/Max' */
  if (!(u0 >= 1.0E-8)) {
    u0 = 1.0E-8;
  }

  /* Product: '<S27>/Product3' incorporates:
   *  Constant: '<S27>/Constant5'
   *  MinMax: '<S27>/Max'
   *  Product: '<S27>/Divide'
   *  Product: '<S27>/Divide3'
   *  Sum: '<S27>/Add6'
   */
  rtb_Product3_k = (1.0 - rtb_Add1_e * rtb_Product3_k / u0) * rtb_Add1_e;

  /* Outport: '<Root>/T_neg' incorporates:
   *  Gain: '<S7>/Gain3'
   */
  rtY.T_neg[0] = -rtb_Add1_e;
  rtY.T_neg[1] = -rtb_Add1_e;
  rtY.T_neg[2] = -rtb_Product3_k;
  rtY.T_neg[3] = -rtb_Product3_k;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  rtDW.Memory2_PreviousInput[0] = rtb_Saturation;

  /* SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
   *  Memory: '<S3>/Memory2'
   */
  rtDW.Memory2_PreviousInput[1] = rtb_Saturation1;

  /* Update for Memory: '<Root>/Memory' */
  rtDW.Memory_PreviousInput = rtb_delta_fldelta_frrad_idx_0;

  /* Update for Memory: '<S3>/Memory1' */
  rtDW.Memory1_PreviousInput[0] = rtb_delta_fldelta_frrad_idx_0;
  rtDW.Memory1_PreviousInput[1] = rtb_Square_m_idx_2;

  /* Update for Memory: '<S21>/Memory' */
  rtDW.Memory_PreviousInput_g[0] = rtb_vims_idx_0;
  rtDW.Memory_PreviousInput_g[1] = rtb_vims_idx_1;
  rtDW.Memory_PreviousInput_g[2] = rtb_vims_idx_2;
  rtDW.Memory_PreviousInput_g[3] = rtb_vims_idx_3;

  /* Update for Memory: '<S3>/Memory4' */
  rtDW.Memory4_PreviousInput = rtb_Saturation2;

  /* Sum: '<S14>/Add1' incorporates:
   *  Constant: '<S14>/Constant4'
   *  Constant: '<S14>/Constant6'
   *  Product: '<S14>/Divide'
   *  Product: '<S14>/Product5'
   */
  rtb_Saturation1 = 1.0 - rtb_K_k[0];
  rtb_Square_m_idx_2_tmp = 0.0 - rtb_K_k[0] * 0.0;
  rtb_Square_m_idx_0 = u * 0.0;

  /* Update for Memory: '<S14>/Memory' */
  for (i = 0; i < 2; i++) {
    /* Product: '<S14>/Product6' incorporates:
     *  Constant: '<S14>/Constant6'
     *  Product: '<S14>/Divide'
     *  Sum: '<S14>/Add'
     *  Sum: '<S14>/Add1'
     */
    rtb_P_k1_tmp = i << 1U;
    rtb_SumofElements2 = rtb_P_k1[rtb_P_k1_tmp + 1];
    rtb_Square_m_idx_1 = rtb_P_k1[rtb_P_k1_tmp];
    rtDW.Memory_PreviousInput_o[rtb_P_k1_tmp] = rtb_SumofElements2 *
      rtb_Square_m_idx_2_tmp + rtb_Square_m_idx_1 * rtb_Saturation1;
    rtDW.Memory_PreviousInput_o[rtb_P_k1_tmp + 1] = (1.0 - rtb_Square_m_idx_0) *
      rtb_SumofElements2 + (0.0 - u) * rtb_Square_m_idx_1;
  }

  /* End of Update for Memory: '<S14>/Memory' */

  /* Update for DiscreteIntegrator: '<S63>/Integrator' incorporates:
   *  Gain: '<S60>/Integral Gain'
   *  Saturate: '<S30>/Saturation'
   */
  rtb_Saturation1 = rtP.TC_map[1] * rtb_Saturation_g_idx_0 * 0.01 +
    rtDW.Integrator_DSTATE[0];
  rtDW.Integrator_DSTATE[0] = rtb_Saturation1;
  if (rtb_Saturation1 > 1.0) {
    rtDW.Integrator_DSTATE[0] = 1.0;
  } else if (rtb_Saturation1 < 0.0) {
    rtDW.Integrator_DSTATE[0] = 0.0;
  }

  rtb_Saturation1 = rtP.TC_map[1] * rtb_Saturation_g_idx_1 * 0.01 +
    rtDW.Integrator_DSTATE[1];
  rtDW.Integrator_DSTATE[1] = rtb_Saturation1;
  if (rtb_Saturation1 > 1.0) {
    rtDW.Integrator_DSTATE[1] = 1.0;
  } else if (rtb_Saturation1 < 0.0) {
    rtDW.Integrator_DSTATE[1] = 0.0;
  }

  rtb_Saturation1 = rtP.TC_map[1] * rtb_Saturation_g_idx_2 * 0.01 +
    rtDW.Integrator_DSTATE[2];
  rtDW.Integrator_DSTATE[2] = rtb_Saturation1;
  if (rtb_Saturation1 > 1.0) {
    rtDW.Integrator_DSTATE[2] = 1.0;
  } else if (rtb_Saturation1 < 0.0) {
    rtDW.Integrator_DSTATE[2] = 0.0;
  }

  rtb_Saturation1 = rtP.TC_map[1] * rtb_Square_m_idx_0_tmp * 0.01 +
    rtDW.Integrator_DSTATE[3];
  rtDW.Integrator_DSTATE[3] = rtb_Saturation1;
  if (rtb_Saturation1 > 1.0) {
    rtDW.Integrator_DSTATE[3] = 1.0;
  } else if (rtb_Saturation1 < 0.0) {
    rtDW.Integrator_DSTATE[3] = 0.0;
  }

  /* End of Update for DiscreteIntegrator: '<S63>/Integrator' */

  /* Update for Memory: '<S24>/Memory' */
  rtDW.Memory_PreviousInput_b = rtb_Product2_h;

  /* Update for Delay: '<S24>/Delay1' */
  for (i = 0; i < 149; i++) {
    rtDW.Delay1_DSTATE[i] = rtDW.Delay1_DSTATE[i + 1];
  }

  rtDW.Delay1_DSTATE[149] = rtb_Compare_m;

  /* End of Update for Delay: '<S24>/Delay1' */
}

/* Model initialize function */
void Torque_Vectoring_2024_forsecontiu_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(rtM, (NULL));

  /* states (dwork) */
  (void) memset((void *)&rtDW, 0,
                sizeof(DW));

  /* external inputs */
  (void)memset(&rtU, 0, sizeof(ExtU));

  /* external outputs */
  (void)memset(&rtY, 0, sizeof(ExtY));

  /* InitializeConditions for Memory: '<S3>/Memory2' */
  rtDW.Memory2_PreviousInput[0] = 1.3;
  rtDW.Memory2_PreviousInput[1] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
