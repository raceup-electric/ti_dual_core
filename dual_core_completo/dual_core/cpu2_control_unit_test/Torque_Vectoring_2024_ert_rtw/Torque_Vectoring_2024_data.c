/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Torque_Vectoring_2024_data.c
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

/* Block parameters (default storage) */
P_Torque_Vectoring_2024_T Torque_Vectoring_2024_P = {
  /* Variable: CLA
   * Referenced by: '<S11>/Fl'
   */
  4.5,

  /* Variable: FZ0
   * Referenced by:
   *   '<S1>/Constant1'
   *   '<S1>/Gain'
   *   '<S1>/Gain1'
   */
  667.461609,

  /* Variable: Ilim
   * Referenced by: '<S25>/MATLAB Function'
   */
  593.96969619669994,

  /* Variable: Ld
   * Referenced by:
   *   '<S25>/MATLAB Function'
   *   '<S28>/Gain6'
   */
  0.00012,

  /* Variable: Lq
   * Referenced by:
   *   '<S25>/MATLAB Function'
   *   '<S28>/Gain6'
   */
  0.00024,

  /* Variable: PDX1
   * Referenced by: '<S1>/Constant'
   */
  2.106129056,

  /* Variable: PDX2
   * Referenced by:
   *   '<S1>/Gain'
   *   '<S1>/Gain1'
   */
  -0.32974244,

  /* Variable: Pmax
   * Referenced by: '<S22>/Total Power Limit'
   */
  80000.0,

  /* Variable: Q
   * Referenced by: '<S14>/Constant7'
   */
  { 0.1, 0.0, 0.0, 0.1 },

  /* Variable: R
   * Referenced by: '<S14>/Constant5'
   */
  0.01,

  /* Variable: R0
   * Referenced by:
   *   '<S5>/Constant'
   *   '<S5>/Saturation'
   */
  0.2032,

  /* Variable: R_batt
   * Referenced by:
   *   '<S6>/Gain'
   *   '<S6>/Gain1'
   */
  0.36623,

  /* Variable: R_phase
   * Referenced by:
   *   '<S25>/Gain'
   *   '<S28>/Constant'
   */
  0.0675,

  /* Variable: TC_CL_I_R
   * Referenced by:
   *   '<S67>/Integral Gain'
   *   '<S117>/Integral Gain'
   *   '<S167>/Integral Gain'
   *   '<S217>/Integral Gain'
   */
  0.75,

  /* Variable: TC_CL_P_R
   * Referenced by:
   *   '<S75>/Proportional Gain'
   *   '<S125>/Proportional Gain'
   *   '<S175>/Proportional Gain'
   *   '<S225>/Proportional Gain'
   */
  1.25,

  /* Variable: TC_CL_TARGET_SLIP_F
   * Referenced by: '<S31>/Desired slip front1'
   */
  0.12,

  /* Variable: TC_CL_TARGET_SLIP_R
   * Referenced by: '<S31>/Desired slip rear1'
   */
  0.12,

  /* Variable: TC_MAX_CUT
   * Referenced by: '<S31>/Constant'
   */
  1.0,

  /* Variable: TC_VX_ON_F
   * Referenced by: '<S32>/Constant3'
   */
  0.25,

  /* Variable: TC_VX_ON_R
   * Referenced by: '<S32>/Constant2'
   */
  1.0,

  /* Variable: T_max
   * Referenced by: '<Root>/Constant1'
   */
  21.0,

  /* Variable: T_regen_max
   * Referenced by: '<S7>/Constant'
   */
  21.0,

  /* Variable: Voltage
   * Referenced by: '<S6>/Max battery voltage'
   */
  564.96,

  /* Variable: a
   * Referenced by:
   *   '<S11>/Constant1'
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  0.84425000000000006,

  /* Variable: a_a
   * Referenced by: '<S11>/Gain'
   */
  0.72035719999999992,

  /* Variable: ax0
   * Referenced by:
   *   '<S18>/Constant'
   *   '<S19>/Constant'
   *   '<S20>/Constant'
   */
  1.8,

  /* Variable: b
   * Referenced by:
   *   '<S11>/Constant'
   *   '<S11>/Gain3'
   */
  0.69075,

  /* Variable: b_a
   * Referenced by: '<S11>/Gain1'
   */
  0.8146428,

  /* Variable: directCurrent
   * Referenced by: '<S24>/Saturation'
   */
  65.0,

  /* Variable: eta_inv
   * Referenced by: '<S7>/Gain'
   */
  0.98,

  /* Variable: flux_mg
   * Referenced by:
   *   '<S25>/MATLAB Function'
   *   '<S28>/Gain3'
   */
  0.0296,

  /* Variable: g
   * Referenced by:
   *   '<Root>/Saturation'
   *   '<Root>/Saturation1'
   *   '<S11>/Constant'
   *   '<S11>/Constant1'
   */
  9.81,

  /* Variable: k_Re
   * Referenced by: '<S5>/Gain2'
   */
  -3.533E-6,

  /* Variable: kr_f1
   * Referenced by:
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  41163.867169638906,

  /* Variable: kr_r1
   * Referenced by:
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  56088.440312528044,

  /* Variable: m
   * Referenced by:
   *   '<S11>/Constant'
   *   '<S11>/Constant1'
   *   '<S11>/Gain2'
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  284.3733,

  /* Variable: maxCurrent
   * Referenced by:
   *   '<S6>/Constant'
   *   '<S24>/Constant1'
   *   '<S24>/Saturation'
   */
  100.0,

  /* Variable: mu_00
   * Referenced by: '<S10>/Constant7'
   */
  300.2078,

  /* Variable: mu_01
   * Referenced by: '<S10>/Gain'
   */
  0.2483,

  /* Variable: mu_02
   * Referenced by: '<S10>/Gain1'
   */
  0.0088,

  /* Variable: mu_03
   * Referenced by: '<S10>/Gain2'
   */
  -1.8682E-5,

  /* Variable: mu_04
   * Referenced by: '<S10>/Gain3'
   */
  1.8267E-8,

  /* Variable: mu_05
   * Referenced by: '<S10>/Gain4'
   */
  -8.8652E-12,

  /* Variable: mu_06
   * Referenced by: '<S10>/Gain5'
   */
  1.7349E-15,

  /* Variable: mu_10
   * Referenced by: '<S10>/Gain13'
   */
  1.146,

  /* Variable: mu_11
   * Referenced by: '<S10>/Gain17'
   */
  -0.00098788,

  /* Variable: mu_12
   * Referenced by: '<S10>/Gain22'
   */
  5.2321E-5,

  /* Variable: mu_13
   * Referenced by: '<S10>/Gain23'
   */
  -3.0722E-8,

  /* Variable: mu_14
   * Referenced by: '<S10>/Gain24'
   */
  -2.1326E-11,

  /* Variable: mu_15
   * Referenced by: '<S10>/Gain25'
   */
  1.417E-14,

  /* Variable: mu_20
   * Referenced by: '<S10>/Gain10'
   */
  -12185.0,

  /* Variable: mu_21
   * Referenced by: '<S10>/Gain26'
   */
  -34.6685,

  /* Variable: mu_22
   * Referenced by: '<S10>/Gain27'
   */
  2.9871E-5,

  /* Variable: mu_23
   * Referenced by: '<S10>/Gain21'
   */
  1.7183E-5,

  /* Variable: mu_24
   * Referenced by: '<S10>/Gain20'
   */
  -6.5431E-9,

  /* Variable: mu_30
   * Referenced by: '<S10>/Gain9'
   */
  -10.876,

  /* Variable: mu_31
   * Referenced by: '<S10>/Gain19'
   */
  -0.202,

  /* Variable: mu_32
   * Referenced by: '<S10>/Gain18'
   */
  0.00013761,

  /* Variable: mu_33
   * Referenced by: '<S10>/Gain12'
   */
  1.2868E-9,

  /* Variable: mu_40
   * Referenced by: '<S10>/Gain8'
   */
  260290.0,

  /* Variable: mu_41
   * Referenced by: '<S10>/Gain16'
   */
  202.6574,

  /* Variable: mu_42
   * Referenced by: '<S10>/Gain15'
   */
  -0.0863,

  /* Variable: mu_50
   * Referenced by: '<S10>/Gain7'
   */
  346.9631,

  /* Variable: mu_51
   * Referenced by: '<S10>/Gain14'
   */
  -0.1108,

  /* Variable: mu_60
   * Referenced by: '<S10>/Gain6'
   */
  -1.4028E+6,

  /* Variable: n_phase
   * Referenced by: '<S25>/Gain5'
   */
  5.0,

  /* Variable: offset_brake_csi
   * Referenced by:
   *   '<Root>/Constant2'
   *   '<Root>/Gain12'
   */
  0.0,

  /* Variable: offset_cornering
   * Referenced by:
   *   '<S237>/Constant1'
   *   '<S237>/Multiply'
   */
  0.5,

  /* Variable: offset_throttle_csi
   * Referenced by:
   *   '<S9>/Constant2'
   *   '<S9>/Gain4'
   */
  0.0,

  /* Variable: p_fl
   * Referenced by:
   *   '<S2>/Constant8'
   *   '<S2>/Gain1'
   *   '<S2>/Gain2'
   *   '<S2>/Gain4'
   *   '<S2>/Gain5'
   *   '<S2>/Gain6'
   */
  { 2.497E+7, -1.217E+6, 63090.0, -3034.0, 988.7, -0.0009525 },

  /* Variable: p_fr
   * Referenced by:
   *   '<S2>/Constant7'
   *   '<S2>/Gain10'
   *   '<S2>/Gain11'
   *   '<S2>/Gain7'
   *   '<S2>/Gain8'
   *   '<S2>/Gain9'
   */
  { 2.497E+7, 1.217E+6, 63090.0, 3034.0, 988.7, 0.0009525 },

  /* Variable: rho_air
   * Referenced by: '<S11>/Fl'
   */
  1.225,

  /* Variable: sigma_w1
   * Referenced by: '<S21>/Constant3'
   */
  7.0,

  /* Variable: sigma_w2
   * Referenced by: '<S21>/Constant1'
   */
  1.5,

  /* Variable: t_alpha
   * Referenced by:
   *   '<S28>/Gain1'
   *   '<S28>/Gain6'
   */
  -5.9197611211028844,

  /* Variable: t_f
   * Referenced by: '<S11>/Gain3'
   */
  1.23,

  /* Variable: t_r
   * Referenced by: '<S11>/Gain4'
   */
  1.2,

  /* Variable: tau
   * Referenced by: '<S10>/Gain11'
   */
  12.6667,

  /* Variable: toe_f
   * Referenced by: '<S12>/Constant2'
   */
  -0.017453292519943295,

  /* Variable: toe_r
   * Referenced by: '<S12>/Constant4'
   */
  0.0,

  /* Variable: w
   * Referenced by:
   *   '<S11>/Constant'
   *   '<S11>/Constant1'
   *   '<S11>/Gain'
   *   '<S11>/Gain1'
   *   '<S11>/Gain2'
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  1.535,

  /* Variable: zCoG
   * Referenced by:
   *   '<S11>/Gain2'
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  0.3,

  /* Variable: zRC_f
   * Referenced by:
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  0.01542,

  /* Variable: zRC_r
   * Referenced by:
   *   '<S11>/Gain3'
   *   '<S11>/Gain4'
   */
  0.03824,

  /* Variable: r0
   * Referenced by: '<S13>/Constant'
   */
  0.0349065848F,

  /* Mask Parameter: PIDController3_InitialConditionForIntegrator
   * Referenced by: '<S120>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController8_InitialConditionForIntegrator
   * Referenced by: '<S220>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialConditionForIntegrator
   * Referenced by: '<S70>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController7_InitialConditionForIntegrator
   * Referenced by: '<S170>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController3_LowerIntegratorSaturationLimit
   * Referenced by: '<S120>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController8_LowerIntegratorSaturationLimit
   * Referenced by: '<S220>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController1_LowerIntegratorSaturationLimit
   * Referenced by: '<S70>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController7_LowerIntegratorSaturationLimit
   * Referenced by: '<S170>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController3_LowerSaturationLimit
   * Referenced by:
   *   '<S127>/Saturation'
   *   '<S113>/DeadZone'
   */
  0.0,

  /* Mask Parameter: PIDController8_LowerSaturationLimit
   * Referenced by:
   *   '<S227>/Saturation'
   *   '<S213>/DeadZone'
   */
  0.0,

  /* Mask Parameter: PIDController1_LowerSaturationLimit
   * Referenced by:
   *   '<S77>/Saturation'
   *   '<S63>/DeadZone'
   */
  0.0,

  /* Mask Parameter: PIDController7_LowerSaturationLimit
   * Referenced by:
   *   '<S177>/Saturation'
   *   '<S163>/DeadZone'
   */
  0.0,

  /* Mask Parameter: PIDController3_UpperIntegratorSaturationLimit
   * Referenced by: '<S120>/Integrator'
   */
  1.0,

  /* Mask Parameter: PIDController8_UpperIntegratorSaturationLimit
   * Referenced by: '<S220>/Integrator'
   */
  1.0,

  /* Mask Parameter: PIDController1_UpperIntegratorSaturationLimit
   * Referenced by: '<S70>/Integrator'
   */
  1.0,

  /* Mask Parameter: PIDController7_UpperIntegratorSaturationLimit
   * Referenced by: '<S170>/Integrator'
   */
  1.0,

  /* Mask Parameter: PIDController3_UpperSaturationLimit
   * Referenced by:
   *   '<S127>/Saturation'
   *   '<S113>/DeadZone'
   */
  1.0,

  /* Mask Parameter: PIDController8_UpperSaturationLimit
   * Referenced by:
   *   '<S227>/Saturation'
   *   '<S213>/DeadZone'
   */
  1.0,

  /* Mask Parameter: PIDController1_UpperSaturationLimit
   * Referenced by:
   *   '<S77>/Saturation'
   *   '<S63>/DeadZone'
   */
  1.0,

  /* Mask Parameter: PIDController7_UpperSaturationLimit
   * Referenced by:
   *   '<S177>/Saturation'
   *   '<S163>/DeadZone'
   */
  1.0,

  /* Expression: Ilim^2
   * Referenced by: '<S28>/Constant1'
   */
  352800.0,

  /* Expression: 0
   * Referenced by: '<S23>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S61>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S111>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S161>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S211>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Delay'
   */
  0.0,

  /* Expression: 1e-5
   * Referenced by: '<S8>/Constant6'
   */
  1.0E-5,

  /* Expression: 1
   * Referenced by: '<S32>/Constant16'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S32>/Constant6'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S32>/Constant15'
   */
  0.0,

  /* Expression: 5
   * Referenced by: '<S2>/Constant3'
   */
  5.0,

  /* Expression: 4
   * Referenced by: '<S2>/Constant1'
   */
  4.0,

  /* Expression: 3
   * Referenced by: '<S2>/Constant2'
   */
  3.0,

  /* Expression: 3
   * Referenced by: '<S2>/Constant4'
   */
  3.0,

  /* Expression: 4
   * Referenced by: '<S2>/Constant5'
   */
  4.0,

  /* Expression: 5
   * Referenced by: '<S2>/Constant6'
   */
  5.0,

  /* Expression: pi/180
   * Referenced by: '<S2>/Gain'
   */
  0.017453292519943295,

  /* Expression: -1
   * Referenced by: '<S12>/Gain'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S3>/Memory1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S21>/Memory'
   */
  0.0,

  /* Expression: 1/T
   * Referenced by: '<S21>/Gain1'
   */
  100.0,

  /* Expression: 1/2
   * Referenced by: '<S21>/Gain'
   */
  0.5,

  /* Expression: 0.4
   * Referenced by: '<S10>/Saturation'
   */
  0.4,

  /* Expression: -0.4
   * Referenced by: '<S10>/Saturation'
   */
  -0.4,

  /* Expression: 3
   * Referenced by: '<S10>/Constant'
   */
  3.0,

  /* Expression: 4
   * Referenced by: '<S10>/Constant1'
   */
  4.0,

  /* Expression: 5
   * Referenced by: '<S10>/Constant2'
   */
  5.0,

  /* Expression: 6
   * Referenced by: '<S10>/Constant3'
   */
  6.0,

  /* Expression: 3
   * Referenced by: '<S10>/Constant4'
   */
  3.0,

  /* Expression: 4
   * Referenced by: '<S10>/Constant5'
   */
  4.0,

  /* Expression: 5
   * Referenced by: '<S10>/Constant6'
   */
  5.0,

  /* Expression: 6
   * Referenced by: '<S10>/Constant8'
   */
  6.0,

  /* Expression: 2500
   * Referenced by: '<S10>/Saturation1'
   */
  2500.0,

  /* Expression: 50
   * Referenced by: '<S10>/Saturation1'
   */
  50.0,

  /* Expression: 1
   * Referenced by: '<S9>/Constant'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S237>/Constant'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S8>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S31>/Constant5'
   */
  0.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S120>/Integrator'
   */
  0.2,

  /* Computed Parameter: Integrator_gainval_b
   * Referenced by: '<S220>/Integrator'
   */
  0.2,

  /* Computed Parameter: Integrator_gainval_h
   * Referenced by: '<S70>/Integrator'
   */
  0.2,

  /* Computed Parameter: Integrator_gainval_l
   * Referenced by: '<S170>/Integrator'
   */
  0.2,

  /* Expression: 0.1
   * Referenced by: '<S22>/Constant'
   */
  0.1,

  /* Expression: 0.1
   * Referenced by: '<S4>/Constant'
   */
  0.1,

  /* Expression: 20000*pi/30
   * Referenced by: '<S4>/Constant1'
   */
  2094.3951023931954,

  /* Expression: 20000*pi/30
   * Referenced by: '<S7>/Saturation1'
   */
  2094.3951023931954,

  /* Expression: 0
   * Referenced by: '<S7>/Saturation1'
   */
  0.0,

  /* Expression: [0 0; 0 0]
   * Referenced by: '<S14>/Memory'
   */
  { 0.0, 0.0, 0.0, 0.0 },

  /* Expression: 1
   * Referenced by: '<S14>/Constant'
   */
  1.0,

  /* Expression: eye(2)
   * Referenced by: '<S14>/Constant6'
   */
  { 1.0, 0.0, 0.0, 1.0 },

  /* Expression: [1 0]
   * Referenced by: '<S14>/Constant4'
   */
  { 1.0, 0.0 },

  /* Expression: [1 0; 0 1]
   * Referenced by: '<S14>/Constant1'
   */
  { 1.0, 0.0, 0.0, 1.0 },

  /* Expression: T
   * Referenced by: '<S14>/Gain3'
   */
  0.01,

  /* Expression: 600
   * Referenced by: '<Root>/Saturation8'
   */
  600.0,

  /* Expression: 0
   * Referenced by: '<Root>/Saturation8'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Saturation4'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Saturation4'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S24>/Memory'
   */
  0.0,

  /* Expression: kRamp*T
   * Referenced by: '<S24>/Constant'
   */
  0.35000000000000003,

  /* Expression: 0
   * Referenced by: '<S25>/Constant'
   */
  0.0,

  /* Expression: 3/2
   * Referenced by: '<S28>/Gain4'
   */
  1.5,

  /* Expression: -1
   * Referenced by: '<S28>/Gain2'
   */
  -1.0,

  /* Expression: 1/21
   * Referenced by: '<S25>/Gain7'
   */
  0.047619047619047616,

  /* Expression: 21
   * Referenced by: '<S26>/Constant1'
   */
  21.0,

  /* Expression: 1/4
   * Referenced by: '<S7>/Gain1'
   */
  0.25,

  /* Expression: 30/pi
   * Referenced by: '<S26>/Gain'
   */
  9.5492965855137211,

  /* Expression: 13000
   * Referenced by: '<S26>/Constant'
   */
  13000.0,

  /* Expression: 7000
   * Referenced by: '<S26>/Saturation'
   */
  7000.0,

  /* Expression: 0
   * Referenced by: '<S26>/Saturation'
   */
  0.0,

  /* Expression: 0.000857
   * Referenced by: '<S26>/Gain1'
   */
  0.000857,

  /* Expression: 0
   * Referenced by: '<S7>/Constant4'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S27>/Constant3'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S27>/Constant5'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S7>/Gain3'
   */
  -1.0,

  /* Expression: [1.3;0]
   * Referenced by: '<S3>/Memory2'
   */
  { 1.3, 0.0 },

  /* Expression: 1
   * Referenced by: '<S3>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S161>/Clamping_zero'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S61>/Clamping_zero'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S211>/Clamping_zero'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S111>/Clamping_zero'
   */
  0.0,

  /* Computed Parameter: Saturation5_UpperSat
   * Referenced by: '<Root>/Saturation5'
   */
  20000.0F,

  /* Computed Parameter: Saturation5_LowerSat
   * Referenced by: '<Root>/Saturation5'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_e
   * Referenced by: '<Root>/Gain'
   */
  0.104719758F,

  /* Computed Parameter: reduction_Gain
   * Referenced by: '<Root>/reduction'
   */
  0.0789471641F,

  /* Computed Parameter: Saturation6_UpperSat
   * Referenced by: '<Root>/Saturation6'
   */
  100.0F,

  /* Computed Parameter: Saturation6_LowerSat
   * Referenced by: '<Root>/Saturation6'
   */
  -100.0F,

  /* Computed Parameter: Gain3_Gain_a
   * Referenced by: '<S2>/Gain3'
   */
  0.000302291039F,

  /* Computed Parameter: Saturation2_UpperSat
   * Referenced by: '<Root>/Saturation2'
   */
  6.28318548F,

  /* Computed Parameter: Saturation2_LowerSat
   * Referenced by: '<Root>/Saturation2'
   */
  -6.28318548F,

  /* Computed Parameter: Multiply_Gain
   * Referenced by: '<S15>/Multiply'
   */
  0.615F,

  /* Computed Parameter: Multiply1_Gain
   * Referenced by: '<S15>/Multiply1'
   */
  -0.615F,

  /* Computed Parameter: Multiply2_Gain
   * Referenced by: '<S15>/Multiply2'
   */
  0.6F,

  /* Computed Parameter: Multiply3_Gain
   * Referenced by: '<S15>/Multiply3'
   */
  -0.6F,

  /* Computed Parameter: Saturation3_UpperSat
   * Referenced by: '<Root>/Saturation3'
   */
  1.0F,

  /* Computed Parameter: Saturation3_LowerSat
   * Referenced by: '<Root>/Saturation3'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_b
   * Referenced by: '<S9>/Gain'
   */
  42.0F,

  /* Computed Parameter: Gain1_Gain_l
   * Referenced by: '<Root>/Gain1'
   */
  0.104719758F,

  /* Computed Parameter: Memory4_InitialCondition
   * Referenced by: '<S3>/Memory4'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_i
   * Referenced by: '<S14>/Gain'
   */
  -0.01F,

  /* Expression: T
   * Referenced by: '<S14>/Gain1'
   */
  0.01F,

  /* Computed Parameter: Saturation7_UpperSat
   * Referenced by: '<Root>/Saturation7'
   */
  1.0E+7F,

  /* Computed Parameter: Saturation7_LowerSat
   * Referenced by: '<Root>/Saturation7'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain_o
   * Referenced by: '<S27>/Gain'
   */
  8.28628617E-5F,

  /* Computed Parameter: Saturation9_UpperSat
   * Referenced by: '<Root>/Saturation9'
   */
  1.0E+7F,

  /* Computed Parameter: Saturation9_LowerSat
   * Referenced by: '<Root>/Saturation9'
   */
  0.0F,

  /* Computed Parameter: Gain1_Gain_c
   * Referenced by: '<S27>/Gain1'
   */
  4.14937786E-5F,

  /* Computed Parameter: Delay1_InitialCondition
   * Referenced by: '<S24>/Delay1'
   */
  0,

  /* Computed Parameter: Constant_Value_hq
   * Referenced by: '<S61>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_j
   * Referenced by: '<S61>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_op
   * Referenced by: '<S61>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_e
   * Referenced by: '<S61>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S111>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_dk
   * Referenced by: '<S111>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_d
   * Referenced by: '<S111>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_j
   * Referenced by: '<S111>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_am
   * Referenced by: '<S161>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_p
   * Referenced by: '<S161>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_ob
   * Referenced by: '<S161>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_c
   * Referenced by: '<S161>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_ej
   * Referenced by: '<S211>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_g
   * Referenced by: '<S211>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_j
   * Referenced by: '<S211>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_oj
   * Referenced by: '<S211>/Constant4'
   */
  -1
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
