/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: powercontrol_RGe08_2022.c
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
#include <math.h>
#include "rtwtypes.h"
#include "powercontrol_RGe08_2022_types.h"
#include <string.h>

real_T ArtInf;
real_T ArtMinusInf;
real_T ArtNaN;
real32_T ArtInfF;
real32_T ArtMinusInfF;
real32_T ArtNaNF;

#define NumBitsPerChar                 16U

real_T ArtGetNaN(void);
real32_T AArtGetNaNF(void);
real_T ArtGetInf(void);
real32_T ArtGetInfF(void);
real_T ArtGetMinusInf(void);
real32_T ArtGetMinusInfF(void);
void Art_InitInfAndNaN(size_t realSize);
boolean_T ArtIsInf(real_T value);
boolean_T ArtIsInfF(real32_T value);
boolean_T ArtIsNaN(real_T value);
boolean_T ArtIsNaNF(real32_T value);



/*
 * Initialize ArtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real_T ArtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = AArtGetNaNF();
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
 * Initialize ArtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real32_T AArtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

real_T ArtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = ArtGetInfF();
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
 * Initialize AArtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T ArtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize ArtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T ArtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = ArtGetMinusInfF();
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
 * Initialize ArtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T ArtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

void Art_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  ArtNaN = ArtGetNaN();
  ArtNaNF = AArtGetNaNF();
  ArtInf = ArtGetInf();
  ArtInfF = ArtGetInfF();
  ArtMinusInf = ArtGetMinusInf();
  ArtMinusInfF = ArtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T ArtIsInf(real_T value)
{
  return (boolean_T)((value==ArtInf || value==ArtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T ArtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==ArtInfF || (value)==ArtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T ArtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = ArtIsNaNF((real32_T)value);
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
boolean_T ArtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}



/* Block states (default storage) */
DW_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_DW;

/* External inputs (root inport signals with default storage) */
ExtU_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_powercontrol_RGe08_2022_T powercontrol_RGe08_2022_Y;

/* Real-time model */
static RT_MODEL_powercontrol_RGe08_2_T powercontrol_RGe08_2022_M_;
RT_MODEL_powercontrol_RGe08_2_T *const powercontrol_RGe08_2022_M =
  &powercontrol_RGe08_2022_M_;

/* Model step function */
void powercontrol_RGe08_2022_step(void)
{
  b_dsp_FIRFilter_0_powercontro_T *obj_0;
  b_dspcodegen_FIRFilter_powerc_T *obj;
  real_T rtb_Divide3;
  real_T rtb_Fattorediriduzionedellacopp;
  real_T rtb_coppiatotalerichiestaaimoto;
  real_T rtb_limitemassimo_k;
  real32_T acc1;
  real32_T rtb_Pe;
  real32_T rtb_TSamp;
  real32_T zCurr;
  real32_T zNext;
  int16_T n;

  /* Sum: '<Root>/Somma delle 4 coppie richieste ai motori' incorporates:
   *  Inport: '<Root>/TorqueFL1'
   *  Inport: '<Root>/TorqueFR1'
   *  Inport: '<Root>/TorqueRL1'
   *  Inport: '<Root>/TorqueRR1'
   */
  rtb_Fattorediriduzionedellacopp = ((powercontrol_RGe08_2022_U.TorqueFL1 +
    powercontrol_RGe08_2022_U.TorqueFR1) + powercontrol_RGe08_2022_U.TorqueRL1)
    + powercontrol_RGe08_2022_U.TorqueRR1;

  /* Switch: '<Root>/switch logico  ' incorporates:
   *  Constant: '<Root>/err'
   */
  if (rtb_Fattorediriduzionedellacopp >
      powercontrol_RGe08_2022_P.switchlogico_Threshold) {
    rtb_coppiatotalerichiestaaimoto = rtb_Fattorediriduzionedellacopp;
  } else {
    rtb_coppiatotalerichiestaaimoto = powercontrol_RGe08_2022_P.err_Value;
  }

  /* End of Switch: '<Root>/switch logico  ' */

  /* Gain: '<Root>/Gain' incorporates:
   *  Abs: '<Root>/Abs'
   */
  rtb_Fattorediriduzionedellacopp = powercontrol_RGe08_2022_P.Gain_Gain * fabs
    (rtb_Fattorediriduzionedellacopp);

  /* Product: '<Root>/Product4' incorporates:
   *  Inport: '<Root>/DC_current'
   *  Inport: '<Root>/Vbatt'
   */
  rtb_Pe = powercontrol_RGe08_2022_U.Vbatt *
    powercontrol_RGe08_2022_U.DC_current;

  /* SampleTimeMath: '<S2>/TSamp'
   *
   * About '<S2>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_Pe * powercontrol_RGe08_2022_P.TSamp_WtEt;

  /* MATLABSystem: '<Root>/Lowpass Filter' incorporates:
   *  Sum: '<S2>/Diff'
   *  UnitDelay: '<S2>/UD'
   *
   * Block description for '<S2>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S2>/UD':
   *
   *  Store in Global RAM
   */
  obj = powercontrol_RGe08_2022_DW.obj.FilterObj;
  if (obj->isInitialized != 1L) {
    obj->isSetupComplete = 0;
    obj->isInitialized = 1L;
    obj->isSetupComplete = 1;

    /* System object Initialization function: dsp.FIRFilter */
    for (n = 0; n < 139; n++) {
      obj->cSFunObject.W0_states[n] = obj->cSFunObject.P0_InitialStates;
    }
  }

  obj_0 = &obj->cSFunObject;

  /* System object Outputs function: dsp.FIRFilter */
  acc1 = 0.0F;

  /* load input sample */
  zNext = rtb_TSamp - powercontrol_RGe08_2022_DW.UD_DSTATE;
  for (n = 0; n < 139; n++) {
    /* shift state */
    zCurr = zNext;
    zNext = obj_0->W0_states[(int32_T)n];
    obj_0->W0_states[(int32_T)n] = zCurr;

    /* compute one tap */
    zCurr *= obj_0->P1_Coefficients[(int32_T)n];
    acc1 += zCurr;
  }

  /* compute last tap */
  zCurr = obj->cSFunObject.P1_Coefficients[(int32_T)n] * zNext;

  /* store output sample */
  acc1 += zCurr;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant5'
   *  MATLABSystem: '<Root>/Lowpass Filter'
   */
  if (acc1 > 0.0F) {
    if (rtb_Pe - (real32_T)(powercontrol_RGe08_2022_P.Pe_lim - 2000.0) < 0.0F) {
      n = 1;
    } else {
      n = -1;
    }
  } else {
    n = 1;
  }

  /* Switch: '<Root>/Switch3' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain4'
   *  MATLAB Function: '<Root>/MATLAB Function'
   *  MATLABSystem: '<Root>/Lowpass Filter'
   *  Sum: '<Root>/Sum'
   */
  if (n > powercontrol_RGe08_2022_P.Switch3_Threshold) {
    rtb_Divide3 = rtb_Pe;
  } else {
    rtb_Divide3 = powercontrol_RGe08_2022_P.Gain1_Gain * acc1 +
      powercontrol_RGe08_2022_P.Gain4_Gain * rtb_Pe;
  }

  /* MinMax: '<Root>/Min' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant5'
   */
  if ((powercontrol_RGe08_2022_P.Constant_Value <=
       powercontrol_RGe08_2022_P.Pe_lim) || ArtIsNaN
      (powercontrol_RGe08_2022_P.Pe_lim)) {
    rtb_limitemassimo_k = powercontrol_RGe08_2022_P.Constant_Value;
  } else {
    rtb_limitemassimo_k = powercontrol_RGe08_2022_P.Pe_lim;
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  MinMax: '<Root>/Min'
   *  Switch: '<Root>/Switch3'
   */
  rtb_limitemassimo_k = rtb_Divide3 - rtb_limitemassimo_k;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Gain: '<S1>/Gain2'
   *  UnitDelay: '<S1>/Unit Delay1'
   */
  powercontrol_RGe08_2022_DW.UnitDelay1_DSTATE +=
    powercontrol_RGe08_2022_P.Gain2_Gain * rtb_limitemassimo_k;

  /* Saturate: '<S1>/  limite massimo' incorporates:
   *  Saturate: '<S1>/limite massimo  '
   */
  rtb_Divide3 = 2094.3951023931954 * powercontrol_RGe08_2022_P.Mmax * 4.0;
  if (powercontrol_RGe08_2022_DW.UnitDelay1_DSTATE > rtb_Divide3) {
    /* Sum: '<S1>/Sum1' */
    powercontrol_RGe08_2022_DW.UnitDelay1_DSTATE = rtb_Divide3;
  } else if (powercontrol_RGe08_2022_DW.UnitDelay1_DSTATE <
             powercontrol_RGe08_2022_P.limitemassimo_LowerSat) {
    /* Sum: '<S1>/Sum1' incorporates:
     *  Saturate: '<S1>/  limite massimo'
     */
    powercontrol_RGe08_2022_DW.UnitDelay1_DSTATE =
      powercontrol_RGe08_2022_P.limitemassimo_LowerSat;
  }

  /* End of Saturate: '<S1>/  limite massimo' */

  /* Sum: '<S1>/Sum2' incorporates:
   *  Gain: '<S1>/Gain1'
   *  UnitDelay: '<S1>/Unit Delay1'
   */
  rtb_limitemassimo_k = powercontrol_RGe08_2022_P.kp_pl * rtb_limitemassimo_k +
    powercontrol_RGe08_2022_DW.UnitDelay1_DSTATE;

  /* Saturate: '<S1>/limite massimo  ' */
  if (rtb_limitemassimo_k > rtb_Divide3) {
    rtb_limitemassimo_k = rtb_Divide3;
  } else if (rtb_limitemassimo_k <
             powercontrol_RGe08_2022_P.limitemassimo_LowerSat_o) {
    rtb_limitemassimo_k = powercontrol_RGe08_2022_P.limitemassimo_LowerSat_o;
  }

  /* Product: '<Root>/Divide3' incorporates:
   *  Constant: '<Root>/ constant'
   *  Saturate: '<S1>/limite massimo  '
   */
  rtb_Divide3 = rtb_limitemassimo_k / powercontrol_RGe08_2022_P.constant_Value;

  /* Switch: '<S4>/Switch2' incorporates:
   *  RelationalOperator: '<S4>/LowerRelop1'
   */
  if (!(rtb_Divide3 > rtb_Fattorediriduzionedellacopp)) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<Root>/minimo'
     *  RelationalOperator: '<S4>/UpperRelop'
     */
    if (rtb_Divide3 < powercontrol_RGe08_2022_P.minimo_Value) {
      rtb_Fattorediriduzionedellacopp = powercontrol_RGe08_2022_P.minimo_Value;
    } else {
      rtb_Fattorediriduzionedellacopp = rtb_Divide3;
    }

    /* End of Switch: '<S4>/Switch' */
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Product: '<Root>/Divide1' */
  rtb_Fattorediriduzionedellacopp /= rtb_coppiatotalerichiestaaimoto;

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/fattore di riduzione nullo '
   */
  if (!(rtb_Fattorediriduzionedellacopp >
        powercontrol_RGe08_2022_P.Switch_Threshold)) {
    rtb_Fattorediriduzionedellacopp =
      powercontrol_RGe08_2022_P.fattorediriduzionenullo_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* Outport: '<Root>/TorqueFL' incorporates:
   *  Inport: '<Root>/TorqueFL1'
   *  Product: '<Root>/Product'
   *  Sum: '<Root>/Sum1'
   */
  powercontrol_RGe08_2022_Y.TorqueFL = powercontrol_RGe08_2022_U.TorqueFL1 -
    powercontrol_RGe08_2022_U.TorqueFL1 * rtb_Fattorediriduzionedellacopp;

  /* Outport: '<Root>/TorqueFR' incorporates:
   *  Inport: '<Root>/TorqueFR1'
   *  Product: '<Root>/Product1'
   *  Sum: '<Root>/Sum2'
   */
  powercontrol_RGe08_2022_Y.TorqueFR = powercontrol_RGe08_2022_U.TorqueFR1 -
    powercontrol_RGe08_2022_U.TorqueFR1 * rtb_Fattorediriduzionedellacopp;

  /* Outport: '<Root>/TorqueRL' incorporates:
   *  Inport: '<Root>/TorqueRL1'
   *  Product: '<Root>/Product2'
   *  Sum: '<Root>/Sum4'
   */
  powercontrol_RGe08_2022_Y.TorqueRL = powercontrol_RGe08_2022_U.TorqueRL1 -
    powercontrol_RGe08_2022_U.TorqueRL1 * rtb_Fattorediriduzionedellacopp;

  /* Outport: '<Root>/TorqueRR' incorporates:
   *  Inport: '<Root>/TorqueRR1'
   *  Product: '<Root>/Product3'
   *  Sum: '<Root>/Sum5'
   */
  powercontrol_RGe08_2022_Y.TorqueRR = powercontrol_RGe08_2022_U.TorqueRR1 -
    powercontrol_RGe08_2022_U.TorqueRR1 * rtb_Fattorediriduzionedellacopp;

  /* Update for UnitDelay: '<S2>/UD'
   *
   * Block description for '<S2>/UD':
   *
   *  Store in Global RAM
   */
  powercontrol_RGe08_2022_DW.UD_DSTATE = rtb_TSamp;
}

/* Model initialize function */
void powercontrol_RGe08_2022_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  Art_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(powercontrol_RGe08_2022_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&powercontrol_RGe08_2022_DW, 0,
                sizeof(DW_powercontrol_RGe08_2022_T));

  /* external inputs */
  (void)memset(&powercontrol_RGe08_2022_U, 0, sizeof
               (ExtU_powercontrol_RGe08_2022_T));

  /* external outputs */
  (void)memset(&powercontrol_RGe08_2022_Y, 0, sizeof
               (ExtY_powercontrol_RGe08_2022_T));

  {
    b_dspcodegen_FIRFilter_powerc_T *iobj_0;
    int16_T i;
    static const real32_T tmp[140] = { 7.02495599E-5F, 4.94839151E-5F,
      6.65342595E-5F, 8.71645825E-5F, 0.0001118332F, 0.00014103303F,
      0.000175273337F, 0.000215092077F, 0.000261045381F, 0.000313710771F,
      0.00037368451F, 0.000441571814F, 0.000517989218F, 0.000603548309F,
      0.000698861317F, 0.000804542738F, 0.000921187864F, 0.00104938075F,
      0.00118968368F, 0.00134262687F, 0.00150871242F, 0.00168839516F,
      0.00188207871F, 0.00209017307F, 0.00231286301F, 0.00255059195F,
      0.00280329306F, 0.00307121128F, 0.00335438037F, 0.00365264108F,
      0.00396585977F, 0.00429384131F, 0.0046362346F, 0.00499256793F, 0.00536231F,
      0.00574485678F, 0.00613948796F, 0.00654536532F, 0.00696154404F,
      0.00738699781F, 0.00782063231F, 0.00826125499F, 0.00870757829F,
      0.00915823877F, 0.00961178355F, 0.0100667141F, 0.0105214771F,
      0.0109744631F, 0.0114240572F, 0.0118685309F, 0.0123062208F, 0.0127353715F,
      0.0131542701F, 0.013561232F, 0.0139545463F, 0.0143325599F, 0.01469367F,
      0.0150362952F, 0.0153589137F, 0.0156601015F, 0.0159385167F, 0.0161928944F,
      0.0164220706F, 0.0166249983F, 0.0168007277F, 0.0169484448F, 0.0170674603F,
      0.0171572044F, 0.0172172766F, 0.0172473807F, 0.0172473807F, 0.0172172766F,
      0.0171572044F, 0.0170674603F, 0.0169484448F, 0.0168007277F, 0.0166249983F,
      0.0164220706F, 0.0161928944F, 0.0159385167F, 0.0156601015F, 0.0153589137F,
      0.0150362952F, 0.01469367F, 0.0143325599F, 0.0139545463F, 0.013561232F,
      0.0131542701F, 0.0127353715F, 0.0123062208F, 0.0118685309F, 0.0114240572F,
      0.0109744631F, 0.0105214771F, 0.0100667141F, 0.00961178355F,
      0.00915823877F, 0.00870757829F, 0.00826125499F, 0.00782063231F,
      0.00738699781F, 0.00696154404F, 0.00654536532F, 0.00613948796F,
      0.00574485678F, 0.00536231F, 0.00499256793F, 0.0046362346F, 0.00429384131F,
      0.00396585977F, 0.00365264108F, 0.00335438037F, 0.00307121128F,
      0.00280329306F, 0.00255059195F, 0.00231286301F, 0.00209017307F,
      0.00188207871F, 0.00168839516F, 0.00150871242F, 0.00134262687F,
      0.00118968368F, 0.00104938075F, 0.000921187864F, 0.000804542738F,
      0.000698861317F, 0.000603548309F, 0.000517989218F, 0.000441571814F,
      0.00037368451F, 0.000313710771F, 0.000261045381F, 0.000215092077F,
      0.000175273337F, 0.00014103303F, 0.0001118332F, 8.71645825E-5F,
      6.65342595E-5F, 4.94839151E-5F, 7.02495599E-5F };

    /* InitializeConditions for UnitDelay: '<S2>/UD'
     *
     * Block description for '<S2>/UD':
     *
     *  Store in Global RAM
     */
    powercontrol_RGe08_2022_DW.UD_DSTATE =
      powercontrol_RGe08_2022_P.DiscreteDerivative_ICPrevScaled;

    /* InitializeConditions for Sum: '<S1>/Sum1' incorporates:
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    powercontrol_RGe08_2022_DW.UnitDelay1_DSTATE =
      powercontrol_RGe08_2022_P.UnitDelay1_InitialCondition;

    /* Start for MATLABSystem: '<Root>/Lowpass Filter' */
    powercontrol_RGe08_2022_DW.obj._pobj0.matlabCodegenIsDeleted = 1;
    powercontrol_RGe08_2022_DW.obj.NumChannels = -1L;
    powercontrol_RGe08_2022_DW.obj.matlabCodegenIsDeleted = 0;
    powercontrol_RGe08_2022_DW.obj.isInitialized = 1L;
    if (powercontrol_RGe08_2022_DW.obj.NumChannels == -1L) {
      powercontrol_RGe08_2022_DW.obj.NumChannels = 1L;
    }

    iobj_0 = &powercontrol_RGe08_2022_DW.obj._pobj0;
    iobj_0->isInitialized = 0L;
    iobj_0->isInitialized = 0L;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0F;
    for (i = 0; i < 140; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = tmp[i];
    }

    iobj_0->matlabCodegenIsDeleted = 0;
    powercontrol_RGe08_2022_DW.obj.FilterObj = iobj_0;
    powercontrol_RGe08_2022_DW.obj.isSetupComplete = 1;

    /* End of Start for MATLABSystem: '<Root>/Lowpass Filter' */

    /* InitializeConditions for MATLABSystem: '<Root>/Lowpass Filter' */
    iobj_0 = powercontrol_RGe08_2022_DW.obj.FilterObj;
    if (iobj_0->isInitialized == 1L) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 139; i++) {
        iobj_0->cSFunObject.W0_states[i] = iobj_0->cSFunObject.P0_InitialStates;
      }
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Lowpass Filter' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
