/* Include files */

#include <stddef.h>
#include "blas.h"
#include "AssemControl_sfun.h"
#include "c2_AssemControl.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "AssemControl_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[8] = { "qd", "nargin", "nargout", "q",
  "t", "qp", "xyz", "delta_xyz" };

static const char * c2_b_debug_family_names[7] = { "x", "y", "z", "nargin",
  "nargout", "qd", "xyz" };

/* Function Declarations */
static void initialize_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance);
static void initialize_params_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance);
static void enable_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance);
static void disable_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_AssemControl
  (SFc2_AssemControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_AssemControl
  (SFc2_AssemControlInstanceStruct *chartInstance);
static void set_sim_state_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance);
static void sf_c2_AssemControl(SFc2_AssemControlInstanceStruct *chartInstance);
static void initSimStructsc2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance);
static void registerMessagesc2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static void c2_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_GlavnaPrograma, const char_T *c2_identifier, real_T c2_y[6]);
static void c2_b_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6]);
static void c2_c_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_q2xyz, const char_T *c2_identifier, real_T c2_y[3]);
static void c2_d_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3]);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_f_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_g_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_AssemControl, const char_T
  *c2_identifier);
static uint8_T c2_h_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_AssemControlInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_AssemControl = 0U;
}

static void initialize_params_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance)
{
}

static void enable_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_AssemControl
  (SFc2_AssemControlInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_AssemControl
  (SFc2_AssemControlInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[3];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[6];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  real_T c2_c_u[3];
  const mxArray *c2_d_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real_T (*c2_xyz)[3];
  real_T (*c2_qp)[6];
  real_T (*c2_delta_xyz)[3];
  c2_delta_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(4), FALSE);
  for (c2_i0 = 0; c2_i0 < 3; c2_i0++) {
    c2_u[c2_i0] = (*c2_delta_xyz)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 6; c2_i1++) {
    c2_b_u[c2_i1] = (*c2_qp)[c2_i1];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 1, 6),
                FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i2 = 0; c2_i2 < 3; c2_i2++) {
    c2_c_u[c2_i2] = (*c2_xyz)[c2_i2];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 1, 3),
                FALSE);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_AssemControl;
  c2_d_u = c2_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[3];
  int32_T c2_i3;
  real_T c2_dv1[6];
  int32_T c2_i4;
  real_T c2_dv2[3];
  int32_T c2_i5;
  real_T (*c2_xyz)[3];
  real_T (*c2_qp)[6];
  real_T (*c2_delta_xyz)[3];
  c2_delta_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                        "delta_xyz", c2_dv0);
  for (c2_i3 = 0; c2_i3 < 3; c2_i3++) {
    (*c2_delta_xyz)[c2_i3] = c2_dv0[c2_i3];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "qp",
                      c2_dv1);
  for (c2_i4 = 0; c2_i4 < 6; c2_i4++) {
    (*c2_qp)[c2_i4] = c2_dv1[c2_i4];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
                        "xyz", c2_dv2);
  for (c2_i5 = 0; c2_i5 < 3; c2_i5++) {
    (*c2_xyz)[c2_i5] = c2_dv2[c2_i5];
  }

  chartInstance->c2_is_active_c2_AssemControl = c2_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 3)),
     "is_active_c2_AssemControl");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_AssemControl(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance)
{
}

static void sf_c2_AssemControl(SFc2_AssemControlInstanceStruct *chartInstance)
{
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  real_T c2_hoistedGlobal;
  int32_T c2_i10;
  real_T c2_q[5];
  real_T c2_t;
  uint32_T c2_debug_family_var_map[8];
  real_T c2_qd[6];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 3.0;
  real_T c2_qp[6];
  real_T c2_xyz[3];
  real_T c2_delta_xyz[3];
  int32_T c2_i11;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  real_T c2_dv3[6];
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  int32_T c2_i16;
  real_T c2_b_u[6];
  const mxArray *c2_b_y = NULL;
  real_T c2_dv4[3];
  int32_T c2_i17;
  int32_T c2_i18;
  real_T c2_b_qd[6];
  uint32_T c2_b_debug_family_var_map[7];
  real_T c2_x;
  real_T c2_c_y;
  real_T c2_z;
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_b_xyz[3];
  int32_T c2_i19;
  static real_T c2_dv5[6] = { -1.0, -1.0, 1.0, -1.0, 1.0, -1.0 };

  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_b;
  real_T c2_d_y;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_b_b;
  real_T c2_e_y;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_c_b;
  real_T c2_f_y;
  real_T c2_a;
  real_T c2_d_b;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_e_b;
  real_T c2_g_y;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_f_b;
  real_T c2_h_y;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_g_b;
  real_T c2_i_y;
  real_T c2_b_a;
  real_T c2_h_b;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_i_b;
  real_T c2_j_y;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_j_b;
  real_T c2_k_y;
  real_T c2_v_x;
  real_T c2_w_x;
  real_T c2_k_b;
  real_T c2_l_y;
  int32_T c2_i20;
  int32_T c2_i21;
  int32_T c2_i22;
  int32_T c2_i23;
  real_T *c2_b_t;
  real_T (*c2_b_delta_xyz)[3];
  real_T (*c2_c_xyz)[3];
  real_T (*c2_b_qp)[6];
  real_T (*c2_b_q)[5];
  c2_b_delta_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_c_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_q = (real_T (*)[5])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i6 = 0; c2_i6 < 5; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_q)[c2_i6], 0U);
  }

  for (c2_i7 = 0; c2_i7 < 6; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_qp)[c2_i7], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_b_t, 2U);
  for (c2_i8 = 0; c2_i8 < 3; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_c_xyz)[c2_i8], 3U);
  }

  for (c2_i9 = 0; c2_i9 < 3; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_delta_xyz)[c2_i9], 4U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_t;
  for (c2_i10 = 0; c2_i10 < 5; c2_i10++) {
    c2_q[c2_i10] = (*c2_b_q)[c2_i10];
  }

  c2_t = c2_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qd, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_q, 3U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_t, 4U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qp, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_xyz, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_delta_xyz, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  for (c2_i11 = 0; c2_i11 < 6; c2_i11++) {
    c2_qp[c2_i11] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_u = c2_t;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  c2_emlrt_marshallIn(chartInstance, sf_mex_call_debug("GlavnaPrograma", 1U, 1U,
    14, c2_y), "GlavnaPrograma", c2_dv3);
  for (c2_i12 = 0; c2_i12 < 6; c2_i12++) {
    c2_qp[c2_i12] = c2_dv3[c2_i12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
    c2_xyz[c2_i13] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  for (c2_i14 = 0; c2_i14 < 6; c2_i14++) {
    c2_qd[c2_i14] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  for (c2_i15 = 0; c2_i15 < 5; c2_i15++) {
    c2_qd[c2_i15] = c2_q[c2_i15];
  }

  c2_qd[5] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  for (c2_i16 = 0; c2_i16 < 6; c2_i16++) {
    c2_b_u[c2_i16] = c2_qd[c2_i16];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 1, 6),
                FALSE);
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_call_debug("q2xyz", 1U, 1U, 14,
    c2_b_y), "q2xyz", c2_dv4);
  for (c2_i17 = 0; c2_i17 < 3; c2_i17++) {
    c2_xyz[c2_i17] = c2_dv4[c2_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  for (c2_i18 = 0; c2_i18 < 6; c2_i18++) {
    c2_b_qd[c2_i18] = c2_qp[c2_i18];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_x, 0U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_y, 1U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_z, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 4U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_qd, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_xyz, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 3);
  for (c2_i19 = 0; c2_i19 < 6; c2_i19++) {
    c2_b_qd[c2_i19] *= c2_dv5[c2_i19];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_b_x = c2_b_qd[0];
  c2_c_x = c2_b_x;
  c2_c_x = muDoubleScalarCos(c2_c_x);
  c2_d_x = c2_b_qd[1];
  c2_e_x = c2_d_x;
  c2_e_x = muDoubleScalarSin(c2_e_x);
  c2_b = c2_e_x;
  c2_d_y = 150.0 * c2_b;
  c2_f_x = (-c2_b_qd[1] - c2_b_qd[2]) + 1.5707963267948966;
  c2_g_x = c2_f_x;
  c2_g_x = muDoubleScalarSin(c2_g_x);
  c2_b_b = c2_g_x;
  c2_e_y = 213.3 * c2_b_b;
  c2_h_x = ((-c2_b_qd[1] - c2_b_qd[2]) - c2_b_qd[3]) + 1.5707963267948966;
  c2_i_x = c2_h_x;
  c2_i_x = muDoubleScalarSin(c2_i_x);
  c2_c_b = c2_i_x;
  c2_f_y = 197.82 * c2_c_b;
  c2_a = c2_c_x;
  c2_d_b = (c2_d_y + c2_e_y) + c2_f_y;
  c2_x = c2_a * c2_d_b;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_j_x = c2_b_qd[0];
  c2_k_x = c2_j_x;
  c2_k_x = muDoubleScalarSin(c2_k_x);
  c2_l_x = c2_b_qd[1];
  c2_m_x = c2_l_x;
  c2_m_x = muDoubleScalarSin(c2_m_x);
  c2_e_b = c2_m_x;
  c2_g_y = 150.0 * c2_e_b;
  c2_n_x = (-c2_b_qd[1] - c2_b_qd[2]) + 1.5707963267948966;
  c2_o_x = c2_n_x;
  c2_o_x = muDoubleScalarSin(c2_o_x);
  c2_f_b = c2_o_x;
  c2_h_y = 213.3 * c2_f_b;
  c2_p_x = ((-c2_b_qd[1] - c2_b_qd[2]) - c2_b_qd[3]) + 1.5707963267948966;
  c2_q_x = c2_p_x;
  c2_q_x = muDoubleScalarSin(c2_q_x);
  c2_g_b = c2_q_x;
  c2_i_y = 197.82 * c2_g_b;
  c2_b_a = c2_k_x;
  c2_h_b = (c2_g_y + c2_h_y) + c2_i_y;
  c2_c_y = c2_b_a * c2_h_b;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_r_x = c2_b_qd[1];
  c2_s_x = c2_r_x;
  c2_s_x = muDoubleScalarCos(c2_s_x);
  c2_i_b = c2_s_x;
  c2_j_y = 150.0 * c2_i_b;
  c2_t_x = (-c2_b_qd[1] - c2_b_qd[2]) + 1.5707963267948966;
  c2_u_x = c2_t_x;
  c2_u_x = muDoubleScalarCos(c2_u_x);
  c2_j_b = c2_u_x;
  c2_k_y = 213.3 * c2_j_b;
  c2_v_x = ((-c2_b_qd[1] - c2_b_qd[2]) - c2_b_qd[3]) + 1.5707963267948966;
  c2_w_x = c2_v_x;
  c2_w_x = muDoubleScalarCos(c2_w_x);
  c2_k_b = c2_w_x;
  c2_l_y = 197.82 * c2_k_b;
  c2_z = (c2_j_y - c2_k_y) - c2_l_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_b_xyz[0] = c2_x;
  c2_b_xyz[1] = c2_c_y;
  c2_b_xyz[2] = c2_z;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -8);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i20 = 0; c2_i20 < 3; c2_i20++) {
    c2_delta_xyz[c2_i20] = c2_xyz[c2_i20] - c2_b_xyz[c2_i20];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -11);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i21 = 0; c2_i21 < 6; c2_i21++) {
    (*c2_b_qp)[c2_i21] = c2_qp[c2_i21];
  }

  for (c2_i22 = 0; c2_i22 < 3; c2_i22++) {
    (*c2_c_xyz)[c2_i22] = c2_xyz[c2_i22];
  }

  for (c2_i23 = 0; c2_i23 < 3; c2_i23++) {
    (*c2_b_delta_xyz)[c2_i23] = c2_delta_xyz[c2_i23];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_AssemControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc2_AssemControl(SFc2_AssemControlInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 0U, sf_debug_get_script_id(
    "C:/Users/Martin/Desktop/dipl/D 2/obid 10/Prostorot na zglobovi zavrsena/qd2xyz.m"));
}

static void c2_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_GlavnaPrograma, const char_T *c2_identifier, real_T c2_y[6])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_GlavnaPrograma), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_GlavnaPrograma);
}

static void c2_b_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6])
{
  real_T c2_dv6[6];
  int32_T c2_i24;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv6, 1, 0, 0U, 1, 0U, 2, 1, 6);
  for (c2_i24 = 0; c2_i24 < 6; c2_i24++) {
    c2_y[c2_i24] = c2_dv6[c2_i24];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_q2xyz, const char_T *c2_identifier, real_T c2_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_q2xyz), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_q2xyz);
}

static void c2_d_emlrt_marshallIn(SFc2_AssemControlInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3])
{
  real_T c2_dv7[3];
  int32_T c2_i25;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv7, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
    c2_y[c2_i25] = c2_dv7[c2_i25];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i26;
  real_T c2_b_inData[3];
  int32_T c2_i27;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i26 = 0; c2_i26 < 3; c2_i26++) {
    c2_b_inData[c2_i26] = (*(real_T (*)[3])c2_inData)[c2_i26];
  }

  for (c2_i27 = 0; c2_i27 < 3; c2_i27++) {
    c2_u[c2_i27] = c2_b_inData[c2_i27];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_q2xyz;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i28;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_q2xyz = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_q2xyz), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_q2xyz);
  for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
    (*(real_T (*)[3])c2_outData)[c2_i28] = c2_y[c2_i28];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i29;
  real_T c2_b_inData[6];
  int32_T c2_i30;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i29 = 0; c2_i29 < 6; c2_i29++) {
    c2_b_inData[c2_i29] = (*(real_T (*)[6])c2_inData)[c2_i29];
  }

  for (c2_i30 = 0; c2_i30 < 6; c2_i30++) {
    c2_u[c2_i30] = c2_b_inData[c2_i30];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_GlavnaPrograma;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[6];
  int32_T c2_i31;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_GlavnaPrograma = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_GlavnaPrograma), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_GlavnaPrograma);
  for (c2_i31 = 0; c2_i31 < 6; c2_i31++) {
    (*(real_T (*)[6])c2_outData)[c2_i31] = c2_y[c2_i31];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i32;
  real_T c2_b_inData[5];
  int32_T c2_i33;
  real_T c2_u[5];
  const mxArray *c2_y = NULL;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i32 = 0; c2_i32 < 5; c2_i32++) {
    c2_b_inData[c2_i32] = (*(real_T (*)[5])c2_inData)[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 5; c2_i33++) {
    c2_u[c2_i33] = c2_b_inData[c2_i33];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 5), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_AssemControl_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[10];
  c2_ResolvedFunctionInfo (*c2_b_info)[10];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i34;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_b_info = (c2_ResolvedFunctionInfo (*)[10])c2_info;
  (*c2_b_info)[0].context = "";
  (*c2_b_info)[0].name = "qd2xyz";
  (*c2_b_info)[0].dominantType = "double";
  (*c2_b_info)[0].resolved =
    "[E]C:/Users/Martin/Desktop/dipl/D 2/obid 10/Prostorot na zglobovi zavrsena/qd2xyz.m";
  (*c2_b_info)[0].fileTimeLo = 1421252516U;
  (*c2_b_info)[0].fileTimeHi = 0U;
  (*c2_b_info)[0].mFileTimeLo = 0U;
  (*c2_b_info)[0].mFileTimeHi = 0U;
  (*c2_b_info)[1].context =
    "[E]C:/Users/Martin/Desktop/dipl/D 2/obid 10/Prostorot na zglobovi zavrsena/qd2xyz.m";
  (*c2_b_info)[1].name = "cos";
  (*c2_b_info)[1].dominantType = "double";
  (*c2_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c2_b_info)[1].fileTimeLo = 1343830372U;
  (*c2_b_info)[1].fileTimeHi = 0U;
  (*c2_b_info)[1].mFileTimeLo = 0U;
  (*c2_b_info)[1].mFileTimeHi = 0U;
  (*c2_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c2_b_info)[2].name = "eml_scalar_cos";
  (*c2_b_info)[2].dominantType = "double";
  (*c2_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  (*c2_b_info)[2].fileTimeLo = 1286818722U;
  (*c2_b_info)[2].fileTimeHi = 0U;
  (*c2_b_info)[2].mFileTimeLo = 0U;
  (*c2_b_info)[2].mFileTimeHi = 0U;
  (*c2_b_info)[3].context =
    "[E]C:/Users/Martin/Desktop/dipl/D 2/obid 10/Prostorot na zglobovi zavrsena/qd2xyz.m";
  (*c2_b_info)[3].name = "sin";
  (*c2_b_info)[3].dominantType = "double";
  (*c2_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c2_b_info)[3].fileTimeLo = 1343830386U;
  (*c2_b_info)[3].fileTimeHi = 0U;
  (*c2_b_info)[3].mFileTimeLo = 0U;
  (*c2_b_info)[3].mFileTimeHi = 0U;
  (*c2_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c2_b_info)[4].name = "eml_scalar_sin";
  (*c2_b_info)[4].dominantType = "double";
  (*c2_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  (*c2_b_info)[4].fileTimeLo = 1286818736U;
  (*c2_b_info)[4].fileTimeHi = 0U;
  (*c2_b_info)[4].mFileTimeLo = 0U;
  (*c2_b_info)[4].mFileTimeHi = 0U;
  (*c2_b_info)[5].context =
    "[E]C:/Users/Martin/Desktop/dipl/D 2/obid 10/Prostorot na zglobovi zavrsena/qd2xyz.m";
  (*c2_b_info)[5].name = "mtimes";
  (*c2_b_info)[5].dominantType = "double";
  (*c2_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c2_b_info)[5].fileTimeLo = 1289519692U;
  (*c2_b_info)[5].fileTimeHi = 0U;
  (*c2_b_info)[5].mFileTimeLo = 0U;
  (*c2_b_info)[5].mFileTimeHi = 0U;
  (*c2_b_info)[6].context =
    "[E]C:/Users/Martin/Desktop/dipl/D 2/obid 10/Prostorot na zglobovi zavrsena/qd2xyz.m";
  (*c2_b_info)[6].name = "mrdivide";
  (*c2_b_info)[6].dominantType = "double";
  (*c2_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c2_b_info)[6].fileTimeLo = 1357951548U;
  (*c2_b_info)[6].fileTimeHi = 0U;
  (*c2_b_info)[6].mFileTimeLo = 1319729966U;
  (*c2_b_info)[6].mFileTimeHi = 0U;
  (*c2_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c2_b_info)[7].name = "rdivide";
  (*c2_b_info)[7].dominantType = "double";
  (*c2_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c2_b_info)[7].fileTimeLo = 1346510388U;
  (*c2_b_info)[7].fileTimeHi = 0U;
  (*c2_b_info)[7].mFileTimeLo = 0U;
  (*c2_b_info)[7].mFileTimeHi = 0U;
  (*c2_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c2_b_info)[8].name = "eml_scalexp_compatible";
  (*c2_b_info)[8].dominantType = "double";
  (*c2_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  (*c2_b_info)[8].fileTimeLo = 1286818796U;
  (*c2_b_info)[8].fileTimeHi = 0U;
  (*c2_b_info)[8].mFileTimeLo = 0U;
  (*c2_b_info)[8].mFileTimeHi = 0U;
  (*c2_b_info)[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c2_b_info)[9].name = "eml_div";
  (*c2_b_info)[9].dominantType = "double";
  (*c2_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c2_b_info)[9].fileTimeLo = 1313347810U;
  (*c2_b_info)[9].fileTimeHi = 0U;
  (*c2_b_info)[9].mFileTimeLo = 0U;
  (*c2_b_info)[9].mFileTimeHi = 0U;
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 10), FALSE);
  for (c2_i34 = 0; c2_i34 < 10; c2_i34++) {
    c2_r0 = &c2_info[c2_i34];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i34);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_f_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i35;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i35, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i35;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_AssemControl, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_AssemControl), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_AssemControl);
  return c2_y;
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_AssemControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_AssemControlInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_AssemControl_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3667661400U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4185560299U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(558146626U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4091231412U);
}

mxArray *sf_c2_AssemControl_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("jueN0SfJ0O1NVdz1pxrLqF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(6);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(3);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(3);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_AssemControl_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c2_AssemControl(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[17],T\"delta_xyz\",},{M[1],M[5],T\"qp\",},{M[1],M[16],T\"xyz\",},{M[8],M[0],T\"is_active_c2_AssemControl\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_AssemControl_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_AssemControlInstanceStruct *chartInstance;
    chartInstance = (SFc2_AssemControlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _AssemControlMachineNumber_,
           2,
           1,
           1,
           5,
           0,
           0,
           0,
           0,
           1,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_AssemControlMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_AssemControlMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _AssemControlMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"q");
          _SFD_SET_DATA_PROPS(1,2,0,1,"qp");
          _SFD_SET_DATA_PROPS(2,1,1,0,"t");
          _SFD_SET_DATA_PROPS(3,2,0,1,"xyz");
          _SFD_SET_DATA_PROPS(4,2,0,1,"delta_xyz");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,314);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"qd2xyz",0,-1,492);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          real_T *c2_t;
          real_T (*c2_q)[5];
          real_T (*c2_qp)[6];
          real_T (*c2_xyz)[3];
          real_T (*c2_delta_xyz)[3];
          c2_delta_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            3);
          c2_xyz = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c2_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_q = (real_T (*)[5])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_qp);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_t);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_xyz);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_delta_xyz);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _AssemControlMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "4HMLWWoZI4YPUQs1uF3FZC";
}

static void sf_opaque_initialize_c2_AssemControl(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_AssemControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_AssemControl((SFc2_AssemControlInstanceStruct*)
    chartInstanceVar);
  initialize_c2_AssemControl((SFc2_AssemControlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_AssemControl(void *chartInstanceVar)
{
  enable_c2_AssemControl((SFc2_AssemControlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_AssemControl(void *chartInstanceVar)
{
  disable_c2_AssemControl((SFc2_AssemControlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_AssemControl(void *chartInstanceVar)
{
  sf_c2_AssemControl((SFc2_AssemControlInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_AssemControl(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_AssemControl
    ((SFc2_AssemControlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_AssemControl();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_AssemControl(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_AssemControl();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_AssemControl((SFc2_AssemControlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_AssemControl(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_AssemControl(S);
}

static void sf_opaque_set_sim_state_c2_AssemControl(SimStruct* S, const mxArray *
  st)
{
  sf_internal_set_sim_state_c2_AssemControl(S, st);
}

static void sf_opaque_terminate_c2_AssemControl(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_AssemControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_AssemControl_optimization_info();
    }

    finalize_c2_AssemControl((SFc2_AssemControlInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_AssemControl((SFc2_AssemControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_AssemControl(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_AssemControl((SFc2_AssemControlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_AssemControl(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_AssemControl_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3296916400U));
  ssSetChecksum1(S,(1273763604U));
  ssSetChecksum2(S,(2440910701U));
  ssSetChecksum3(S,(3537429908U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_AssemControl(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_AssemControl(SimStruct *S)
{
  SFc2_AssemControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControlInstanceStruct *)utMalloc(sizeof
    (SFc2_AssemControlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_AssemControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_AssemControl;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_AssemControl;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_AssemControl;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_AssemControl;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_AssemControl;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_AssemControl;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_AssemControl;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_AssemControl;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_AssemControl;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_AssemControl;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_AssemControl;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_AssemControl_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_AssemControl(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_AssemControl(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_AssemControl(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_AssemControl_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
