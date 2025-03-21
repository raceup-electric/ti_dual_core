/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rt_nonfinite.c
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

#include "rtGetNaN.h"
#include "rtGetInf.h"
#include <stddef.h>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#define NumBitsPerChar                 16U

real_T BrtInf;
real_T BrtMinusInf;
real_T BrtNaN;
real32_T BrtInfF;
real32_T BrtMinusInfF;
real32_T BrtNaNF;

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

/*
 * Initialize the BrtInf, BrtMinusInf, and BrtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void Brt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  BrtNaN = rtGetNaN();
  BrtNaNF = rtGetNaNF();
  BrtInf = rtGetInf();
  BrtInfF = rtGetInfF();
  BrtMinusInf = rtGetMinusInf();
  BrtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T BrtIsInf(real_T value)
{
  return (boolean_T)((value==BrtInf || value==BrtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T BrtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==BrtInfF || (value)==BrtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T BrtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = BrtIsNaNF((real32_T)value);
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
boolean_T BrtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
