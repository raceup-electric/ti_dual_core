/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: powercontrol_RGe08_2022_types.h
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

#ifndef RTW_HEADER_powercontrol_RGe08_2022_types_h_
#define RTW_HEADER_powercontrol_RGe08_2022_types_h_
#include "rtwtypes.h"
#ifndef struct_tag_RucZ3WGNIOXxufCN808ZPG
#define struct_tag_RucZ3WGNIOXxufCN808ZPG

struct tag_RucZ3WGNIOXxufCN808ZPG
{
  int16_T S0_isInitialized;
  real32_T W0_states[139];
  real32_T P0_InitialStates;
  real32_T P1_Coefficients[140];
};

#endif                                 /* struct_tag_RucZ3WGNIOXxufCN808ZPG */

#ifndef typedef_b_dsp_FIRFilter_0_powercontro_T
#define typedef_b_dsp_FIRFilter_0_powercontro_T

typedef struct tag_RucZ3WGNIOXxufCN808ZPG b_dsp_FIRFilter_0_powercontro_T;

#endif                             /* typedef_b_dsp_FIRFilter_0_powercontro_T */

#ifndef struct_tag_ncyEhSbd3Nj2WJhKD1iXjH
#define struct_tag_ncyEhSbd3Nj2WJhKD1iXjH

struct tag_ncyEhSbd3Nj2WJhKD1iXjH
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  b_dsp_FIRFilter_0_powercontro_T cSFunObject;
};

#endif                                 /* struct_tag_ncyEhSbd3Nj2WJhKD1iXjH */

#ifndef typedef_b_dspcodegen_FIRFilter_powerc_T
#define typedef_b_dspcodegen_FIRFilter_powerc_T

typedef struct tag_ncyEhSbd3Nj2WJhKD1iXjH b_dspcodegen_FIRFilter_powerc_T;

#endif                             /* typedef_b_dspcodegen_FIRFilter_powerc_T */

#ifndef struct_tag_BlgwLpgj2bjudmbmVKWwDE
#define struct_tag_BlgwLpgj2bjudmbmVKWwDE

struct tag_BlgwLpgj2bjudmbmVKWwDE
{
  uint32_T f1[8];
};

#endif                                 /* struct_tag_BlgwLpgj2bjudmbmVKWwDE */

#ifndef typedef_cell_wrap_powercontrol_RGe08__T
#define typedef_cell_wrap_powercontrol_RGe08__T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_powercontrol_RGe08__T;

#endif                             /* typedef_cell_wrap_powercontrol_RGe08__T */

#ifndef struct_tag_wSJVPhiXoXBROepGUj1mOG
#define struct_tag_wSJVPhiXoXBROepGUj1mOG

struct tag_wSJVPhiXoXBROepGUj1mOG
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_powercontrol_RGe08__T inputVarSize;
  int32_T NumChannels;
  b_dspcodegen_FIRFilter_powerc_T *FilterObj;
  b_dspcodegen_FIRFilter_powerc_T _pobj0;
};

#endif                                 /* struct_tag_wSJVPhiXoXBROepGUj1mOG */

#ifndef typedef_dsp_simulink_LowpassFilter_po_T
#define typedef_dsp_simulink_LowpassFilter_po_T

typedef struct tag_wSJVPhiXoXBROepGUj1mOG dsp_simulink_LowpassFilter_po_T;

#endif                             /* typedef_dsp_simulink_LowpassFilter_po_T */

/* Parameters (default storage) */
typedef struct P_powercontrol_RGe08_2022_T_ P_powercontrol_RGe08_2022_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_powercontrol_RGe08_20_T RT_MODEL_powercontrol_RGe08_2_T;

#endif                         /* RTW_HEADER_powercontrol_RGe08_2022_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
