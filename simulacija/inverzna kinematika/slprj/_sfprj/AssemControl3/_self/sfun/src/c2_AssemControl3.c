/* Include files */

#include <stddef.h>
#include "blas.h"
#include "AssemControl3_sfun.h"
#include "c2_AssemControl3.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "AssemControl3_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[13] = { "dqp", "qp_initial", "qp1",
  "qp2", "nargin", "nargout", "t", "qp", "v", "qd", "dqd", "ddqd", "td" };

static const char * c2_b_debug_family_names[13] = { "t1", "t2", "nargin",
  "nargout", "qd1", "dqd", "dqd1", "dqd2", "ddqd1", "ddqd2", "td", "t", "qp" };

static const char * c2_c_debug_family_names[12] = { "i", "nargin", "nargout",
  "qd1", "dqd", "dqd1", "dqd2", "ddqd1", "ddqd2", "td", "t", "qp" };

static const char * c2_d_debug_family_names[13] = { "a", "b", "c", "x", "nargin",
  "nargout", "qd1", "qd2", "dqd1", "ddqd1", "ddqd2", "td", "dqd" };

static const char * c2_e_debug_family_names[9] = { "nargin", "nargout", "qd1",
  "qd2", "dqd2", "ddqd1", "ddqd2", "td", "dqd" };

static const char * c2_f_debug_family_names[14] = { "dqd_1", "dqd_2", "dqd_3",
  "dqd_4", "dqd_5", "nargin", "nargout", "qd1", "qd2", "dqd1", "ddqd1", "ddqd2",
  "td", "dqd" };

static const char * c2_g_debug_family_names[12] = { "state1", "state2", "nargin",
  "nargout", "qd", "dqd", "ddqd", "td", "t", "qp", "dqdNEW", "state" };

/* Function Declarations */
static void initialize_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance);
static void initialize_params_c2_AssemControl3(SFc2_AssemControl3InstanceStruct *
  chartInstance);
static void enable_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance);
static void disable_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_AssemControl3
  (SFc2_AssemControl3InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_AssemControl3
  (SFc2_AssemControl3InstanceStruct *chartInstance);
static void set_sim_state_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance);
static void sf_c2_AssemControl3(SFc2_AssemControl3InstanceStruct *chartInstance);
static void c2_chartstep_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance);
static void initSimStructsc2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance);
static void registerMessagesc2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance);
static void c2_Matrica_qp(SFc2_AssemControl3InstanceStruct *chartInstance,
  real_T c2_qd1[5], real_T c2_b_dqd[5], real_T c2_dqd1[5], real_T c2_dqd2[5],
  real_T c2_ddqd1[5], real_T c2_ddqd2[5], real_T c2_b_td, real_T c2_t, real_T
  c2_qp[5]);
static real_T c2_UNTITLED_dqd_new1(SFc2_AssemControl3InstanceStruct
  *chartInstance, real_T c2_qd1, real_T c2_qd2, real_T c2_dqd2, real_T c2_ddqd1,
  real_T c2_ddqd2, real_T c2_b_td);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct *chartInstance,
  const mxArray *c2_b_td, const char_T *c2_identifier, real_T c2_y[3]);
static void c2_b_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_ddqd, const char_T *c2_identifier, real_T
  c2_y[20]);
static void c2_d_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[20]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_dqd, const char_T *c2_identifier, real_T
  c2_y[15]);
static void c2_f_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[15]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_qd, const char_T *c2_identifier, real_T
  c2_y[20]);
static void c2_h_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[20]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_i_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_v, const char_T *c2_identifier);
static real_T c2_j_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_k_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_qp, const char_T *c2_identifier, real_T
  c2_y[6]);
static void c2_l_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_m_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_n_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[5]);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_o_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_state, const char_T *c2_identifier, real_T
  c2_y[10]);
static void c2_p_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[10]);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_q_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_dqdNEW, const char_T *c2_identifier,
  real_T c2_y[5]);
static void c2_r_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[5]);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[23]);
static void c2_eml_error(SFc2_AssemControl3InstanceStruct *chartInstance);
static void c2_s_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_mrdivide, const char_T *c2_identifier,
  real_T c2_y[3]);
static void c2_t_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_u_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_qd, const char_T *c2_identifier, real_T
  c2_y[20]);
static void c2_v_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[20]);
static void c2_w_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_dqd, const char_T *c2_identifier, real_T
  c2_y[15]);
static void c2_x_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[15]);
static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_y_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_ab_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_AssemControl3, const char_T
  *c2_identifier);
static uint8_T c2_bb_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_AssemControl3InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_v_not_empty = FALSE;
  chartInstance->c2_qd_not_empty = FALSE;
  chartInstance->c2_dqd_not_empty = FALSE;
  chartInstance->c2_ddqd_not_empty = FALSE;
  chartInstance->c2_td_not_empty = FALSE;
  chartInstance->c2_dqdNEW_not_empty = FALSE;
  chartInstance->c2_state_not_empty = FALSE;
  chartInstance->c2_is_active_c2_AssemControl3 = 0U;
}

static void initialize_params_c2_AssemControl3(SFc2_AssemControl3InstanceStruct *
  chartInstance)
{
}

static void enable_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_AssemControl3
  (SFc2_AssemControl3InstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_AssemControl3
  (SFc2_AssemControl3InstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[6];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[20];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  real_T c2_c_u[15];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i3;
  real_T c2_d_u[5];
  const mxArray *c2_e_y = NULL;
  int32_T c2_i4;
  real_T c2_e_u[20];
  const mxArray *c2_f_y = NULL;
  int32_T c2_i5;
  real_T c2_f_u[10];
  const mxArray *c2_g_y = NULL;
  int32_T c2_i6;
  real_T c2_g_u[3];
  const mxArray *c2_h_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_h_u;
  const mxArray *c2_i_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_i_u;
  const mxArray *c2_j_y = NULL;
  real_T (*c2_qp)[6];
  c2_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(9), FALSE);
  for (c2_i0 = 0; c2_i0 < 6; c2_i0++) {
    c2_u[c2_i0] = (*c2_qp)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 6), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 20; c2_i1++) {
    c2_b_u[c2_i1] = chartInstance->c2_ddqd[c2_i1];
  }

  c2_c_y = NULL;
  if (!chartInstance->c2_ddqd_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 4, 5),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i2 = 0; c2_i2 < 15; c2_i2++) {
    c2_c_u[c2_i2] = chartInstance->c2_dqd[c2_i2];
  }

  c2_d_y = NULL;
  if (!chartInstance->c2_dqd_not_empty) {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 3, 5),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 2, c2_d_y);
  for (c2_i3 = 0; c2_i3 < 5; c2_i3++) {
    c2_d_u[c2_i3] = chartInstance->c2_dqdNEW[c2_i3];
  }

  c2_e_y = NULL;
  if (!chartInstance->c2_dqdNEW_not_empty) {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 1, 5),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 3, c2_e_y);
  for (c2_i4 = 0; c2_i4 < 20; c2_i4++) {
    c2_e_u[c2_i4] = chartInstance->c2_qd[c2_i4];
  }

  c2_f_y = NULL;
  if (!chartInstance->c2_qd_not_empty) {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 4, 5),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 4, c2_f_y);
  for (c2_i5 = 0; c2_i5 < 10; c2_i5++) {
    c2_f_u[c2_i5] = chartInstance->c2_state[c2_i5];
  }

  c2_g_y = NULL;
  if (!chartInstance->c2_state_not_empty) {
    sf_mex_assign(&c2_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_f_u, 0, 0U, 1U, 0U, 2, 2, 5),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 5, c2_g_y);
  for (c2_i6 = 0; c2_i6 < 3; c2_i6++) {
    c2_g_u[c2_i6] = chartInstance->c2_td[c2_i6];
  }

  c2_h_y = NULL;
  if (!chartInstance->c2_td_not_empty) {
    sf_mex_assign(&c2_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_h_y, sf_mex_create("y", c2_g_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 6, c2_h_y);
  c2_hoistedGlobal = chartInstance->c2_v;
  c2_h_u = c2_hoistedGlobal;
  c2_i_y = NULL;
  if (!chartInstance->c2_v_not_empty) {
    sf_mex_assign(&c2_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_h_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c2_y, 7, c2_i_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_AssemControl3;
  c2_i_u = c2_b_hoistedGlobal;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_i_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 8, c2_j_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[6];
  int32_T c2_i7;
  real_T c2_dv1[20];
  int32_T c2_i8;
  real_T c2_dv2[15];
  int32_T c2_i9;
  real_T c2_dv3[5];
  int32_T c2_i10;
  real_T c2_dv4[20];
  int32_T c2_i11;
  real_T c2_dv5[10];
  int32_T c2_i12;
  real_T c2_dv6[3];
  int32_T c2_i13;
  real_T (*c2_qp)[6];
  c2_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "qp",
                        c2_dv0);
  for (c2_i7 = 0; c2_i7 < 6; c2_i7++) {
    (*c2_qp)[c2_i7] = c2_dv0[c2_i7];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
                        "ddqd", c2_dv1);
  for (c2_i8 = 0; c2_i8 < 20; c2_i8++) {
    chartInstance->c2_ddqd[c2_i8] = c2_dv1[c2_i8];
  }

  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
                        "dqd", c2_dv2);
  for (c2_i9 = 0; c2_i9 < 15; c2_i9++) {
    chartInstance->c2_dqd[c2_i9] = c2_dv2[c2_i9];
  }

  c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 3)),
                        "dqdNEW", c2_dv3);
  for (c2_i10 = 0; c2_i10 < 5; c2_i10++) {
    chartInstance->c2_dqdNEW[c2_i10] = c2_dv3[c2_i10];
  }

  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 4)), "qd",
                        c2_dv4);
  for (c2_i11 = 0; c2_i11 < 20; c2_i11++) {
    chartInstance->c2_qd[c2_i11] = c2_dv4[c2_i11];
  }

  c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 5)),
                        "state", c2_dv5);
  for (c2_i12 = 0; c2_i12 < 10; c2_i12++) {
    chartInstance->c2_state[c2_i12] = c2_dv5[c2_i12];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 6)), "td",
                      c2_dv6);
  for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
    chartInstance->c2_td[c2_i13] = c2_dv6[c2_i13];
  }

  chartInstance->c2_v = c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 7)), "v");
  chartInstance->c2_is_active_c2_AssemControl3 = c2_ab_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 8)),
     "is_active_c2_AssemControl3");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_AssemControl3(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance)
{
}

static void sf_c2_AssemControl3(SFc2_AssemControl3InstanceStruct *chartInstance)
{
  int32_T c2_i14;
  real_T *c2_t;
  real_T (*c2_qp)[6];
  c2_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c2_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i14 = 0; c2_i14 < 6; c2_i14++) {
    _SFD_DATA_RANGE_CHECK((*c2_qp)[c2_i14], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_t, 1U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_AssemControl3(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_AssemControl3MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_t;
  uint32_T c2_debug_family_var_map[13];
  real_T c2_dqp[5];
  real_T c2_qp_initial[6];
  real_T c2_qp1[6];
  real_T c2_qp2[6];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  real_T c2_qp[6];
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  static real_T c2_dv7[20] = { 0.0, 0.0, 30.0, 60.0, 0.0, 60.0, 45.0, -30.0, 0.0,
    60.0, 45.0, -30.0, 0.0, -30.0, -15.0, -30.0, 0.0, 0.0, 0.0, 10.0 };

  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_i21;
  real_T c2_b_hoistedGlobal[20];
  int32_T c2_i22;
  real_T c2_u[20];
  const mxArray *c2_y = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_dv8[3];
  int32_T c2_i23;
  int32_T c2_i24;
  real_T c2_c_hoistedGlobal[3];
  int32_T c2_i25;
  real_T c2_c_u[3];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i26;
  int32_T c2_i27;
  real_T c2_d_u[20];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i28;
  int32_T c2_i29;
  real_T c2_e_u[3];
  const mxArray *c2_e_y = NULL;
  const mxArray *c2_b_ddqd = NULL;
  const mxArray *c2_b_dqd = NULL;
  const mxArray *c2_b_qd = NULL;
  real_T c2_dv9[20];
  int32_T c2_i30;
  real_T c2_dv10[15];
  int32_T c2_i31;
  real_T c2_dv11[20];
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  real_T c2_f_u[20];
  const mxArray *c2_f_y = NULL;
  int32_T c2_i35;
  real_T c2_d_hoistedGlobal[15];
  int32_T c2_i36;
  real_T c2_g_u[15];
  const mxArray *c2_g_y = NULL;
  int32_T c2_i37;
  int32_T c2_i38;
  real_T c2_h_u[20];
  const mxArray *c2_h_y = NULL;
  int32_T c2_i39;
  static real_T c2_dv12[6] = { 0.0, -1.5707963267948966, 0.0,
    9.0194944897658678E-16, 0.0, -0.25590713012667893 };

  int32_T c2_i40;
  int32_T c2_i41;
  int32_T c2_i42;
  real_T c2_e_hoistedGlobal[20];
  int32_T c2_i43;
  int32_T c2_i44;
  real_T c2_c_qd[20];
  int32_T c2_i45;
  real_T c2_c_dqd[15];
  int32_T c2_i46;
  real_T c2_c_ddqd[20];
  int32_T c2_i47;
  real_T c2_b_td[3];
  real_T c2_b_t;
  uint32_T c2_b_debug_family_var_map[12];
  real_T c2_state1[5];
  real_T c2_state2[5];
  real_T c2_b_nargin = 5.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_b_qp[5];
  int32_T c2_i48;
  int32_T c2_i49;
  real_T c2_A[5];
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  real_T c2_d_qd[5];
  int32_T c2_i53;
  int32_T c2_i54;
  real_T c2_d_dqd[5];
  int32_T c2_i55;
  real_T c2_dv13[5];
  int32_T c2_i56;
  real_T c2_b_A[5];
  int32_T c2_i57;
  int32_T c2_i58;
  real_T c2_d_ddqd[5];
  int32_T c2_i59;
  int32_T c2_i60;
  real_T c2_e_ddqd[5];
  real_T c2_dv14[5];
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  int32_T c2_i66;
  real_T c2_c_A[5];
  int32_T c2_i67;
  int32_T c2_i68;
  real_T c2_b_state1[5];
  int32_T c2_i69;
  int32_T c2_i70;
  real_T c2_e_dqd[5];
  int32_T c2_i71;
  real_T c2_d_A[5];
  int32_T c2_i72;
  real_T c2_e_A[5];
  int32_T c2_i73;
  int32_T c2_i74;
  real_T c2_f_ddqd[5];
  int32_T c2_i75;
  int32_T c2_i76;
  real_T c2_g_ddqd[5];
  real_T c2_dv15[5];
  int32_T c2_i77;
  int32_T c2_i78;
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  real_T c2_f_hoistedGlobal[10];
  int32_T c2_i83;
  real_T c2_i_u[10];
  const mxArray *c2_i_y = NULL;
  int32_T c2_i84;
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  real_T c2_qd1[5];
  int32_T c2_i90;
  int32_T c2_i91;
  real_T c2_qd2[5];
  int32_T c2_i92;
  real_T c2_dqd1[5];
  int32_T c2_i93;
  int32_T c2_i94;
  real_T c2_ddqd1[5];
  int32_T c2_i95;
  int32_T c2_i96;
  real_T c2_ddqd2[5];
  real_T c2_c_td;
  uint32_T c2_c_debug_family_var_map[14];
  real_T c2_dqd_1;
  real_T c2_dqd_2;
  real_T c2_dqd_3;
  real_T c2_dqd_4;
  real_T c2_dqd_5;
  real_T c2_c_nargin = 6.0;
  real_T c2_c_nargout = 1.0;
  real_T c2_f_dqd[5];
  int32_T c2_i97;
  int32_T c2_i98;
  int32_T c2_i99;
  real_T c2_j_u[5];
  const mxArray *c2_j_y = NULL;
  int32_T c2_i100;
  int32_T c2_i101;
  int32_T c2_i102;
  int32_T c2_i103;
  int32_T c2_i104;
  real_T c2_e_qd[5];
  int32_T c2_i105;
  int32_T c2_i106;
  real_T c2_g_dqd[5];
  int32_T c2_i107;
  real_T c2_dv16[5];
  int32_T c2_i108;
  real_T c2_f_A[5];
  int32_T c2_i109;
  int32_T c2_i110;
  real_T c2_h_ddqd[5];
  int32_T c2_i111;
  int32_T c2_i112;
  real_T c2_i_ddqd[5];
  real_T c2_dv17[5];
  int32_T c2_i113;
  int32_T c2_i114;
  int32_T c2_i115;
  int32_T c2_i116;
  int32_T c2_i117;
  int32_T c2_i118;
  int32_T c2_i119;
  int32_T c2_i120;
  int32_T c2_i121;
  int32_T c2_i122;
  real_T c2_g_hoistedGlobal[5];
  int32_T c2_i123;
  int32_T c2_i124;
  real_T c2_h_dqd[5];
  int32_T c2_i125;
  real_T c2_g_A[5];
  int32_T c2_i126;
  real_T c2_h_A[5];
  int32_T c2_i127;
  int32_T c2_i128;
  real_T c2_j_ddqd[5];
  int32_T c2_i129;
  int32_T c2_i130;
  real_T c2_k_ddqd[5];
  real_T c2_dv18[5];
  int32_T c2_i131;
  int32_T c2_i132;
  int32_T c2_i133;
  int32_T c2_i134;
  int32_T c2_i135;
  int32_T c2_i136;
  int32_T c2_i137;
  int32_T c2_i138;
  real_T c2_h_hoistedGlobal[5];
  int32_T c2_i139;
  real_T c2_i_A[5];
  int32_T c2_i140;
  real_T c2_j_A[5];
  int32_T c2_i141;
  real_T c2_dv19[5];
  int32_T c2_i142;
  int32_T c2_i143;
  real_T c2_l_ddqd[5];
  int32_T c2_i144;
  int32_T c2_i145;
  real_T c2_m_ddqd[5];
  real_T c2_dv20[5];
  int32_T c2_i146;
  int32_T c2_i147;
  int32_T c2_i148;
  int32_T c2_i149;
  real_T c2_a[6];
  int32_T c2_i150;
  int32_T c2_i151;
  int32_T c2_i152;
  static real_T c2_dv21[6] = { 0.0, 0.0, 0.0, 0.0, -1.5707963267948966,
    -0.52359877559829882 };

  int32_T c2_i153;
  int32_T c2_i154;
  real_T *c2_c_t;
  real_T (*c2_c_qp)[6];
  boolean_T guard1 = FALSE;
  c2_c_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c2_c_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_c_t;
  c2_t = c2_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dqp, 0U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qp_initial, 1U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qp1, 2U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qp2, 3U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 5U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_t, 6U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qp, 7U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_v, 8U,
    c2_e_sf_marshallOut, c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_qd, 9U,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_dqd, 10U,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_ddqd, 11U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_td, 12U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  for (c2_i15 = 0; c2_i15 < 6; c2_i15++) {
    c2_qp[c2_i15] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  for (c2_i16 = 0; c2_i16 < 5; c2_i16++) {
    c2_dqp[c2_i16] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_v_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
    for (c2_i17 = 0; c2_i17 < 20; c2_i17++) {
      chartInstance->c2_qd[c2_i17] = c2_dv7[c2_i17];
    }

    chartInstance->c2_qd_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
    for (c2_i18 = 0; c2_i18 < 3; c2_i18++) {
      chartInstance->c2_td[c2_i18] = 0.0;
    }

    chartInstance->c2_td_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
    for (c2_i19 = 0; c2_i19 < 15; c2_i19++) {
      chartInstance->c2_dqd[c2_i19] = 0.0;
    }

    chartInstance->c2_dqd_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
    for (c2_i20 = 0; c2_i20 < 20; c2_i20++) {
      chartInstance->c2_ddqd[c2_i20] = 0.0;
    }

    chartInstance->c2_ddqd_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
    for (c2_i21 = 0; c2_i21 < 20; c2_i21++) {
      c2_b_hoistedGlobal[c2_i21] = chartInstance->c2_qd[c2_i21];
    }

    for (c2_i22 = 0; c2_i22 < 20; c2_i22++) {
      c2_u[c2_i22] = c2_b_hoistedGlobal[c2_i22];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 5), FALSE);
    c2_b_u = 30.0;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), FALSE);
    c2_s_emlrt_marshallIn(chartInstance, sf_mex_call_debug("mrdivide", 1U, 2U,
      14, sf_mex_call_debug("PosakuvaniVremetraenja", 1U, 1U, 14, c2_y), 14,
      c2_b_y), "mrdivide", c2_dv8);
    for (c2_i23 = 0; c2_i23 < 3; c2_i23++) {
      chartInstance->c2_td[c2_i23] = c2_dv8[c2_i23];
    }

    sf_mex_printf("%s =\\n", "td");
    for (c2_i24 = 0; c2_i24 < 3; c2_i24++) {
      c2_c_hoistedGlobal[c2_i24] = chartInstance->c2_td[c2_i24];
    }

    for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
      c2_c_u[c2_i25] = c2_c_hoistedGlobal[c2_i25];
    }

    c2_c_y = NULL;
    sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  FALSE);
    sf_mex_call_debug("disp", 0U, 1U, 14, c2_c_y);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
    for (c2_i26 = 0; c2_i26 < 20; c2_i26++) {
      c2_b_hoistedGlobal[c2_i26] = chartInstance->c2_qd[c2_i26];
    }

    for (c2_i27 = 0; c2_i27 < 20; c2_i27++) {
      c2_d_u[c2_i27] = c2_b_hoistedGlobal[c2_i27];
    }

    c2_d_y = NULL;
    sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 4, 5),
                  FALSE);
    for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
      c2_c_hoistedGlobal[c2_i28] = chartInstance->c2_td[c2_i28];
    }

    for (c2_i29 = 0; c2_i29 < 3; c2_i29++) {
      c2_e_u[c2_i29] = c2_c_hoistedGlobal[c2_i29];
    }

    c2_e_y = NULL;
    sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  FALSE);
    sf_mex_call_debug("GenerirajTraektorija", 3U, 2U, 14, c2_d_y, 14, c2_e_y,
                      &c2_b_qd, &c2_b_dqd, &c2_b_ddqd);
    c2_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_qd), "qd", c2_dv9);
    for (c2_i30 = 0; c2_i30 < 20; c2_i30++) {
      chartInstance->c2_qd[c2_i30] = c2_dv9[c2_i30];
    }

    c2_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dqd), "dqd", c2_dv10);
    for (c2_i31 = 0; c2_i31 < 15; c2_i31++) {
      chartInstance->c2_dqd[c2_i31] = c2_dv10[c2_i31];
    }

    c2_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_ddqd), "ddqd", c2_dv11);
    for (c2_i32 = 0; c2_i32 < 20; c2_i32++) {
      chartInstance->c2_ddqd[c2_i32] = c2_dv11[c2_i32];
    }

    sf_mex_printf("%s =\\n", "qd");
    for (c2_i33 = 0; c2_i33 < 20; c2_i33++) {
      c2_b_hoistedGlobal[c2_i33] = chartInstance->c2_qd[c2_i33];
    }

    for (c2_i34 = 0; c2_i34 < 20; c2_i34++) {
      c2_f_u[c2_i34] = c2_b_hoistedGlobal[c2_i34];
    }

    c2_f_y = NULL;
    sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_f_u, 0, 0U, 1U, 0U, 2, 4, 5),
                  FALSE);
    sf_mex_call_debug("disp", 0U, 1U, 14, c2_f_y);
    sf_mex_printf("%s =\\n", "dqd");
    for (c2_i35 = 0; c2_i35 < 15; c2_i35++) {
      c2_d_hoistedGlobal[c2_i35] = chartInstance->c2_dqd[c2_i35];
    }

    for (c2_i36 = 0; c2_i36 < 15; c2_i36++) {
      c2_g_u[c2_i36] = c2_d_hoistedGlobal[c2_i36];
    }

    c2_g_y = NULL;
    sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_g_u, 0, 0U, 1U, 0U, 2, 3, 5),
                  FALSE);
    sf_mex_call_debug("disp", 0U, 1U, 14, c2_g_y);
    sf_mex_printf("%s =\\n", "ddqd");
    for (c2_i37 = 0; c2_i37 < 20; c2_i37++) {
      c2_b_hoistedGlobal[c2_i37] = chartInstance->c2_ddqd[c2_i37];
    }

    for (c2_i38 = 0; c2_i38 < 20; c2_i38++) {
      c2_h_u[c2_i38] = c2_b_hoistedGlobal[c2_i38];
    }

    c2_h_y = NULL;
    sf_mex_assign(&c2_h_y, sf_mex_create("y", c2_h_u, 0, 0U, 1U, 0U, 2, 4, 5),
                  FALSE);
    sf_mex_call_debug("disp", 0U, 1U, 14, c2_h_y);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
    chartInstance->c2_v = 1.0;
    chartInstance->c2_v_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  for (c2_i39 = 0; c2_i39 < 6; c2_i39++) {
    c2_qp_initial[c2_i39] = c2_dv12[c2_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  for (c2_i40 = 0; c2_i40 < 20; c2_i40++) {
    c2_b_hoistedGlobal[c2_i40] = chartInstance->c2_qd[c2_i40];
  }

  for (c2_i41 = 0; c2_i41 < 15; c2_i41++) {
    c2_d_hoistedGlobal[c2_i41] = chartInstance->c2_dqd[c2_i41];
  }

  for (c2_i42 = 0; c2_i42 < 20; c2_i42++) {
    c2_e_hoistedGlobal[c2_i42] = chartInstance->c2_ddqd[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 3; c2_i43++) {
    c2_c_hoistedGlobal[c2_i43] = chartInstance->c2_td[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 20; c2_i44++) {
    c2_c_qd[c2_i44] = c2_b_hoistedGlobal[c2_i44];
  }

  for (c2_i45 = 0; c2_i45 < 15; c2_i45++) {
    c2_c_dqd[c2_i45] = c2_d_hoistedGlobal[c2_i45];
  }

  for (c2_i46 = 0; c2_i46 < 20; c2_i46++) {
    c2_c_ddqd[c2_i46] = c2_e_hoistedGlobal[c2_i46];
  }

  for (c2_i47 = 0; c2_i47 < 3; c2_i47++) {
    c2_b_td[c2_i47] = c2_c_hoistedGlobal[c2_i47];
  }

  c2_b_t = c2_t;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c2_g_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_state1, 0U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_state2, 1U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 2U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 3U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c_qd, 4U, c2_l_sf_marshallOut,
    c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c_dqd, 5U, c2_m_sf_marshallOut,
    c2_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_c_ddqd, 6U, c2_l_sf_marshallOut,
    c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_td, 7U, c2_k_sf_marshallOut,
    c2_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_t, 8U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_qp, 9U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_dqdNEW, 10U,
    c2_j_sf_marshallOut, c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_state, 11U,
    c2_i_sf_marshallOut, c2_i_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 12);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 19);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 20);
  if (CV_SCRIPT_IF(0, 0, !chartInstance->c2_dqdNEW_not_empty)) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 21);
    c2_i48 = 0;
    for (c2_i49 = 0; c2_i49 < 5; c2_i49++) {
      c2_A[c2_i49] = c2_c_dqd[c2_i48] + c2_c_dqd[c2_i48 + 1];
      c2_i48 += 3;
    }

    for (c2_i50 = 0; c2_i50 < 5; c2_i50++) {
      c2_A[c2_i50] /= 2.0;
    }

    c2_i51 = 0;
    for (c2_i52 = 0; c2_i52 < 5; c2_i52++) {
      c2_d_qd[c2_i52] = c2_c_qd[c2_i51];
      c2_i51 += 4;
    }

    c2_i53 = 0;
    for (c2_i54 = 0; c2_i54 < 5; c2_i54++) {
      c2_d_dqd[c2_i54] = c2_c_dqd[c2_i53];
      c2_i53 += 3;
    }

    for (c2_i55 = 0; c2_i55 < 5; c2_i55++) {
      c2_dv13[c2_i55] = 0.0;
    }

    for (c2_i56 = 0; c2_i56 < 5; c2_i56++) {
      c2_b_A[c2_i56] = c2_A[c2_i56];
    }

    c2_i57 = 0;
    for (c2_i58 = 0; c2_i58 < 5; c2_i58++) {
      c2_d_ddqd[c2_i58] = c2_c_ddqd[c2_i57];
      c2_i57 += 4;
    }

    c2_i59 = 0;
    for (c2_i60 = 0; c2_i60 < 5; c2_i60++) {
      c2_e_ddqd[c2_i60] = c2_c_ddqd[c2_i59 + 1];
      c2_i59 += 4;
    }

    c2_Matrica_qp(chartInstance, c2_d_qd, c2_d_dqd, c2_dv13, c2_b_A, c2_d_ddqd,
                  c2_e_ddqd, c2_b_td[0], c2_b_td[0], c2_dv14);
    for (c2_i61 = 0; c2_i61 < 5; c2_i61++) {
      c2_state1[c2_i61] = c2_dv14[c2_i61];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 22);
    c2_i62 = 0;
    for (c2_i63 = 0; c2_i63 < 5; c2_i63++) {
      c2_A[c2_i63] = c2_c_dqd[c2_i62] + c2_c_dqd[c2_i62 + 1];
      c2_i62 += 3;
    }

    for (c2_i64 = 0; c2_i64 < 5; c2_i64++) {
      c2_A[c2_i64] /= 2.0;
    }

    c2_i65 = 0;
    for (c2_i66 = 0; c2_i66 < 5; c2_i66++) {
      c2_c_A[c2_i66] = c2_c_dqd[c2_i65 + 1] + c2_c_dqd[c2_i65 + 2];
      c2_i65 += 3;
    }

    for (c2_i67 = 0; c2_i67 < 5; c2_i67++) {
      c2_c_A[c2_i67] /= 2.0;
    }

    for (c2_i68 = 0; c2_i68 < 5; c2_i68++) {
      c2_b_state1[c2_i68] = c2_state1[c2_i68];
    }

    c2_i69 = 0;
    for (c2_i70 = 0; c2_i70 < 5; c2_i70++) {
      c2_e_dqd[c2_i70] = c2_c_dqd[c2_i69 + 1];
      c2_i69 += 3;
    }

    for (c2_i71 = 0; c2_i71 < 5; c2_i71++) {
      c2_d_A[c2_i71] = c2_A[c2_i71];
    }

    for (c2_i72 = 0; c2_i72 < 5; c2_i72++) {
      c2_e_A[c2_i72] = c2_c_A[c2_i72];
    }

    c2_i73 = 0;
    for (c2_i74 = 0; c2_i74 < 5; c2_i74++) {
      c2_f_ddqd[c2_i74] = c2_c_ddqd[c2_i73 + 1];
      c2_i73 += 4;
    }

    c2_i75 = 0;
    for (c2_i76 = 0; c2_i76 < 5; c2_i76++) {
      c2_g_ddqd[c2_i76] = c2_c_ddqd[c2_i75 + 2];
      c2_i75 += 4;
    }

    c2_Matrica_qp(chartInstance, c2_b_state1, c2_e_dqd, c2_d_A, c2_e_A,
                  c2_f_ddqd, c2_g_ddqd, c2_b_td[1], c2_b_td[1], c2_dv15);
    for (c2_i77 = 0; c2_i77 < 5; c2_i77++) {
      c2_state2[c2_i77] = c2_dv15[c2_i77];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 23);
    c2_i78 = 0;
    for (c2_i79 = 0; c2_i79 < 5; c2_i79++) {
      chartInstance->c2_state[c2_i78] = c2_state1[c2_i79];
      c2_i78 += 2;
    }

    c2_i80 = 0;
    for (c2_i81 = 0; c2_i81 < 5; c2_i81++) {
      chartInstance->c2_state[c2_i80 + 1] = c2_state2[c2_i81];
      c2_i80 += 2;
    }

    chartInstance->c2_state_not_empty = TRUE;
    sf_mex_printf("%s =\\n", "state");
    for (c2_i82 = 0; c2_i82 < 10; c2_i82++) {
      c2_f_hoistedGlobal[c2_i82] = chartInstance->c2_state[c2_i82];
    }

    for (c2_i83 = 0; c2_i83 < 10; c2_i83++) {
      c2_i_u[c2_i83] = c2_f_hoistedGlobal[c2_i83];
    }

    c2_i_y = NULL;
    sf_mex_assign(&c2_i_y, sf_mex_create("y", c2_i_u, 0, 0U, 1U, 0U, 2, 2, 5),
                  FALSE);
    sf_mex_call_debug("disp", 0U, 1U, 14, c2_i_y);
    _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 24);
    for (c2_i84 = 0; c2_i84 < 10; c2_i84++) {
      c2_f_hoistedGlobal[c2_i84] = chartInstance->c2_state[c2_i84];
    }

    c2_i85 = 0;
    for (c2_i86 = 0; c2_i86 < 5; c2_i86++) {
      c2_A[c2_i86] = c2_c_dqd[c2_i85 + 1] + c2_c_dqd[c2_i85 + 2];
      c2_i85 += 3;
    }

    for (c2_i87 = 0; c2_i87 < 5; c2_i87++) {
      c2_A[c2_i87] /= 2.0;
    }

    c2_i88 = 0;
    for (c2_i89 = 0; c2_i89 < 5; c2_i89++) {
      c2_qd1[c2_i89] = c2_f_hoistedGlobal[c2_i88 + 1];
      c2_i88 += 2;
    }

    c2_i90 = 0;
    for (c2_i91 = 0; c2_i91 < 5; c2_i91++) {
      c2_qd2[c2_i91] = c2_c_qd[c2_i90 + 3];
      c2_i90 += 4;
    }

    for (c2_i92 = 0; c2_i92 < 5; c2_i92++) {
      c2_dqd1[c2_i92] = c2_A[c2_i92];
    }

    c2_i93 = 0;
    for (c2_i94 = 0; c2_i94 < 5; c2_i94++) {
      c2_ddqd1[c2_i94] = c2_c_ddqd[c2_i93 + 2];
      c2_i93 += 4;
    }

    c2_i95 = 0;
    for (c2_i96 = 0; c2_i96 < 5; c2_i96++) {
      c2_ddqd2[c2_i96] = c2_c_ddqd[c2_i95 + 3];
      c2_i95 += 4;
    }

    c2_c_td = c2_b_td[2];
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 14U, 14U, c2_f_debug_family_names,
      c2_c_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dqd_1, 0U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dqd_2, 1U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dqd_3, 2U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dqd_4, 3U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dqd_5, 4U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargin, 5U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargout, 6U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qd1, 7U, c2_h_sf_marshallOut,
      c2_h_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qd2, 8U, c2_h_sf_marshallOut,
      c2_h_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dqd1, 9U, c2_h_sf_marshallOut,
      c2_h_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ddqd1, 10U, c2_h_sf_marshallOut,
      c2_h_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ddqd2, 11U, c2_h_sf_marshallOut,
      c2_h_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_td, 12U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_f_dqd, 13U, c2_h_sf_marshallOut,
      c2_h_sf_marshallIn);
    CV_SCRIPT_FCN(3, 0);
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 6);
    c2_dqd_1 = c2_UNTITLED_dqd_new1(chartInstance, c2_qd1[0], c2_qd2[0],
      c2_dqd1[0], c2_ddqd1[0], c2_ddqd2[0], c2_c_td);
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 7);
    c2_dqd_2 = c2_UNTITLED_dqd_new1(chartInstance, c2_qd1[1], c2_qd2[1],
      c2_dqd1[1], c2_ddqd1[1], c2_ddqd2[1], c2_c_td);
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 8);
    c2_dqd_3 = c2_UNTITLED_dqd_new1(chartInstance, c2_qd1[2], c2_qd2[2],
      c2_dqd1[2], c2_ddqd1[2], c2_ddqd2[2], c2_c_td);
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 9);
    c2_dqd_4 = c2_UNTITLED_dqd_new1(chartInstance, c2_qd1[3], c2_qd2[3],
      c2_dqd1[3], c2_ddqd1[3], c2_ddqd2[3], c2_c_td);
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 10);
    c2_dqd_5 = c2_UNTITLED_dqd_new1(chartInstance, c2_qd1[4], c2_qd2[4],
      c2_dqd1[4], c2_ddqd1[4], c2_ddqd2[4], c2_c_td);
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 12);
    c2_f_dqd[0] = c2_dqd_1;
    c2_f_dqd[1] = c2_dqd_2;
    c2_f_dqd[2] = c2_dqd_3;
    c2_f_dqd[3] = c2_dqd_4;
    c2_f_dqd[4] = c2_dqd_5;
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, -12);
    _SFD_SYMBOL_SCOPE_POP();
    for (c2_i97 = 0; c2_i97 < 5; c2_i97++) {
      chartInstance->c2_dqdNEW[c2_i97] = c2_f_dqd[c2_i97];
    }

    chartInstance->c2_dqdNEW_not_empty = TRUE;
    sf_mex_printf("%s =\\n", "dqdNEW");
    for (c2_i98 = 0; c2_i98 < 5; c2_i98++) {
      c2_c_A[c2_i98] = chartInstance->c2_dqdNEW[c2_i98];
    }

    for (c2_i99 = 0; c2_i99 < 5; c2_i99++) {
      c2_j_u[c2_i99] = c2_c_A[c2_i99];
    }

    c2_j_y = NULL;
    sf_mex_assign(&c2_j_y, sf_mex_create("y", c2_j_u, 0, 0U, 1U, 0U, 2, 1, 5),
                  FALSE);
    sf_mex_call_debug("disp", 0U, 1U, 14, c2_j_y);
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 31);
  if (CV_SCRIPT_IF(0, 1, c2_b_t <= c2_b_td[0])) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 37);
    c2_i100 = 0;
    for (c2_i101 = 0; c2_i101 < 5; c2_i101++) {
      c2_A[c2_i101] = c2_c_dqd[c2_i100] + c2_c_dqd[c2_i100 + 1];
      c2_i100 += 3;
    }

    for (c2_i102 = 0; c2_i102 < 5; c2_i102++) {
      c2_A[c2_i102] /= 2.0;
    }

    c2_i103 = 0;
    for (c2_i104 = 0; c2_i104 < 5; c2_i104++) {
      c2_e_qd[c2_i104] = c2_c_qd[c2_i103];
      c2_i103 += 4;
    }

    c2_i105 = 0;
    for (c2_i106 = 0; c2_i106 < 5; c2_i106++) {
      c2_g_dqd[c2_i106] = c2_c_dqd[c2_i105];
      c2_i105 += 3;
    }

    for (c2_i107 = 0; c2_i107 < 5; c2_i107++) {
      c2_dv16[c2_i107] = 0.0;
    }

    for (c2_i108 = 0; c2_i108 < 5; c2_i108++) {
      c2_f_A[c2_i108] = c2_A[c2_i108];
    }

    c2_i109 = 0;
    for (c2_i110 = 0; c2_i110 < 5; c2_i110++) {
      c2_h_ddqd[c2_i110] = c2_c_ddqd[c2_i109];
      c2_i109 += 4;
    }

    c2_i111 = 0;
    for (c2_i112 = 0; c2_i112 < 5; c2_i112++) {
      c2_i_ddqd[c2_i112] = c2_c_ddqd[c2_i111 + 1];
      c2_i111 += 4;
    }

    c2_Matrica_qp(chartInstance, c2_e_qd, c2_g_dqd, c2_dv16, c2_f_A, c2_h_ddqd,
                  c2_i_ddqd, c2_b_td[0], c2_b_t, c2_dv17);
    for (c2_i113 = 0; c2_i113 < 5; c2_i113++) {
      c2_b_qp[c2_i113] = c2_dv17[c2_i113];
    }
  } else {
    _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 38);
    if (CV_SCRIPT_IF(0, 2, c2_b_t <= c2_b_td[0] + c2_b_td[1])) {
      _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 44);
      for (c2_i114 = 0; c2_i114 < 10; c2_i114++) {
        c2_f_hoistedGlobal[c2_i114] = chartInstance->c2_state[c2_i114];
      }

      c2_i115 = 0;
      for (c2_i116 = 0; c2_i116 < 5; c2_i116++) {
        c2_A[c2_i116] = c2_c_dqd[c2_i115] + c2_c_dqd[c2_i115 + 1];
        c2_i115 += 3;
      }

      for (c2_i117 = 0; c2_i117 < 5; c2_i117++) {
        c2_A[c2_i117] /= 2.0;
      }

      c2_i118 = 0;
      for (c2_i119 = 0; c2_i119 < 5; c2_i119++) {
        c2_c_A[c2_i119] = c2_c_dqd[c2_i118 + 1] + c2_c_dqd[c2_i118 + 2];
        c2_i118 += 3;
      }

      for (c2_i120 = 0; c2_i120 < 5; c2_i120++) {
        c2_c_A[c2_i120] /= 2.0;
      }

      c2_i121 = 0;
      for (c2_i122 = 0; c2_i122 < 5; c2_i122++) {
        c2_g_hoistedGlobal[c2_i122] = c2_f_hoistedGlobal[c2_i121];
        c2_i121 += 2;
      }

      c2_i123 = 0;
      for (c2_i124 = 0; c2_i124 < 5; c2_i124++) {
        c2_h_dqd[c2_i124] = c2_c_dqd[c2_i123 + 1];
        c2_i123 += 3;
      }

      for (c2_i125 = 0; c2_i125 < 5; c2_i125++) {
        c2_g_A[c2_i125] = c2_A[c2_i125];
      }

      for (c2_i126 = 0; c2_i126 < 5; c2_i126++) {
        c2_h_A[c2_i126] = c2_c_A[c2_i126];
      }

      c2_i127 = 0;
      for (c2_i128 = 0; c2_i128 < 5; c2_i128++) {
        c2_j_ddqd[c2_i128] = c2_c_ddqd[c2_i127 + 1];
        c2_i127 += 4;
      }

      c2_i129 = 0;
      for (c2_i130 = 0; c2_i130 < 5; c2_i130++) {
        c2_k_ddqd[c2_i130] = c2_c_ddqd[c2_i129 + 2];
        c2_i129 += 4;
      }

      c2_Matrica_qp(chartInstance, c2_g_hoistedGlobal, c2_h_dqd, c2_g_A, c2_h_A,
                    c2_j_ddqd, c2_k_ddqd, c2_b_td[1], c2_b_t - c2_b_td[0],
                    c2_dv18);
      for (c2_i131 = 0; c2_i131 < 5; c2_i131++) {
        c2_b_qp[c2_i131] = c2_dv18[c2_i131];
      }
    } else {
      _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 45);
      guard1 = FALSE;
      if (CV_SCRIPT_COND(0, 0, c2_b_t >= c2_b_td[0] + c2_b_td[1])) {
        if (CV_SCRIPT_COND(0, 1, c2_b_t <= (c2_b_td[0] + c2_b_td[1]) + c2_b_td[2]))
        {
          CV_SCRIPT_MCDC(0, 0, TRUE);
          CV_SCRIPT_IF(0, 3, TRUE);
          _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 56);
          for (c2_i132 = 0; c2_i132 < 10; c2_i132++) {
            c2_f_hoistedGlobal[c2_i132] = chartInstance->c2_state[c2_i132];
          }

          for (c2_i133 = 0; c2_i133 < 5; c2_i133++) {
            c2_c_A[c2_i133] = chartInstance->c2_dqdNEW[c2_i133];
          }

          c2_i134 = 0;
          for (c2_i135 = 0; c2_i135 < 5; c2_i135++) {
            c2_A[c2_i135] = c2_c_dqd[c2_i134 + 1] + c2_c_dqd[c2_i134 + 2];
            c2_i134 += 3;
          }

          for (c2_i136 = 0; c2_i136 < 5; c2_i136++) {
            c2_A[c2_i136] /= 2.0;
          }

          c2_i137 = 0;
          for (c2_i138 = 0; c2_i138 < 5; c2_i138++) {
            c2_h_hoistedGlobal[c2_i138] = c2_f_hoistedGlobal[c2_i137 + 1];
            c2_i137 += 2;
          }

          for (c2_i139 = 0; c2_i139 < 5; c2_i139++) {
            c2_i_A[c2_i139] = c2_c_A[c2_i139];
          }

          for (c2_i140 = 0; c2_i140 < 5; c2_i140++) {
            c2_j_A[c2_i140] = c2_A[c2_i140];
          }

          for (c2_i141 = 0; c2_i141 < 5; c2_i141++) {
            c2_dv19[c2_i141] = 0.0;
          }

          c2_i142 = 0;
          for (c2_i143 = 0; c2_i143 < 5; c2_i143++) {
            c2_l_ddqd[c2_i143] = c2_c_ddqd[c2_i142 + 2];
            c2_i142 += 4;
          }

          c2_i144 = 0;
          for (c2_i145 = 0; c2_i145 < 5; c2_i145++) {
            c2_m_ddqd[c2_i145] = c2_c_ddqd[c2_i144 + 3];
            c2_i144 += 4;
          }

          c2_Matrica_qp(chartInstance, c2_h_hoistedGlobal, c2_i_A, c2_j_A,
                        c2_dv19, c2_l_ddqd, c2_m_ddqd, c2_b_td[2], c2_b_t -
                        (c2_b_td[0] + c2_b_td[1]), c2_dv20);
          for (c2_i146 = 0; c2_i146 < 5; c2_i146++) {
            c2_b_qp[c2_i146] = c2_dv20[c2_i146];
          }
        } else {
          guard1 = TRUE;
        }
      } else {
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        CV_SCRIPT_MCDC(0, 0, FALSE);
        CV_SCRIPT_IF(0, 3, FALSE);
        _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 58);
        c2_i147 = 0;
        for (c2_i148 = 0; c2_i148 < 5; c2_i148++) {
          c2_b_qp[c2_i148] = c2_c_qd[c2_i147 + 3];
          c2_i147 += 4;
        }
      }
    }
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -58);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i149 = 0; c2_i149 < 5; c2_i149++) {
    c2_a[c2_i149] = c2_b_qp[c2_i149];
  }

  c2_a[5] = 0.0;
  for (c2_i150 = 0; c2_i150 < 6; c2_i150++) {
    c2_a[c2_i150] *= 3.1415926535897931;
  }

  for (c2_i151 = 0; c2_i151 < 6; c2_i151++) {
    c2_qp1[c2_i151] = c2_a[c2_i151] / 180.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  for (c2_i152 = 0; c2_i152 < 6; c2_i152++) {
    c2_qp2[c2_i152] = c2_dv21[c2_i152] + c2_qp_initial[c2_i152];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  for (c2_i153 = 0; c2_i153 < 6; c2_i153++) {
    c2_qp[c2_i153] = c2_qp1[c2_i153] + c2_qp2[c2_i153];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -30);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c2_b_qd);
  sf_mex_destroy(&c2_b_dqd);
  sf_mex_destroy(&c2_b_ddqd);
  for (c2_i154 = 0; c2_i154 < 6; c2_i154++) {
    (*c2_c_qp)[c2_i154] = c2_qp[c2_i154];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance)
{
}

static void registerMessagesc2_AssemControl3(SFc2_AssemControl3InstanceStruct
  *chartInstance)
{
}

static void c2_Matrica_qp(SFc2_AssemControl3InstanceStruct *chartInstance,
  real_T c2_qd1[5], real_T c2_b_dqd[5], real_T c2_dqd1[5], real_T c2_dqd2[5],
  real_T c2_ddqd1[5], real_T c2_ddqd2[5], real_T c2_b_td, real_T c2_t, real_T
  c2_qp[5])
{
  uint32_T c2_debug_family_var_map[12];
  real_T c2_i;
  real_T c2_nargin = 8.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i155;
  int32_T c2_b_i;
  real_T c2_b_qd1;
  real_T c2_c_dqd;
  real_T c2_b_dqd1;
  real_T c2_b_dqd2;
  real_T c2_b_ddqd1;
  real_T c2_b_ddqd2;
  real_T c2_c_td;
  real_T c2_b_t;
  uint32_T c2_b_debug_family_var_map[13];
  real_T c2_t1;
  real_T c2_t2;
  real_T c2_b_nargin = 8.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_b_qp;
  real_T c2_A;
  real_T c2_B;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_b_A;
  real_T c2_b_B;
  real_T c2_e_x;
  real_T c2_d_y;
  real_T c2_f_x;
  real_T c2_e_y;
  real_T c2_f_y;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_g_y;
  real_T c2_a;
  real_T c2_b;
  real_T c2_h_y;
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_i_y;
  real_T c2_c_a;
  real_T c2_c_b;
  real_T c2_j_y;
  real_T c2_c_A;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_y;
  real_T c2_d_a;
  real_T c2_d_b;
  real_T c2_l_y;
  real_T c2_e_a;
  real_T c2_e_b;
  real_T c2_m_y;
  real_T c2_f_a;
  real_T c2_f_b;
  real_T c2_n_y;
  real_T c2_d_A;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_o_y;
  real_T c2_g_a;
  real_T c2_g_b;
  real_T c2_p_y;
  real_T c2_h_a;
  real_T c2_h_b;
  real_T c2_q_y;
  real_T c2_i_a;
  real_T c2_i_b;
  real_T c2_r_y;
  real_T c2_j_a;
  real_T c2_j_b;
  real_T c2_s_y;
  real_T c2_e_A;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_t_y;
  real_T c2_k_a;
  real_T c2_k_b;
  real_T c2_u_y;
  real_T c2_l_a;
  real_T c2_l_b;
  real_T c2_v_y;
  real_T c2_m_a;
  real_T c2_m_b;
  real_T c2_w_y;
  real_T c2_n_a;
  real_T c2_n_b;
  real_T c2_x_y;
  real_T c2_f_A;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_y_y;
  real_T c2_q_x;
  boolean_T c2_b0;
  boolean_T c2_b1;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 12U, 12U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i, 0U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 1U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 2U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qd1, 3U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_dqd, 4U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dqd1, 5U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_dqd2, 6U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ddqd1, 7U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_ddqd2, 8U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_td, 9U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_t, 10U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qp, 11U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 12);
  for (c2_i155 = 0; c2_i155 < 5; c2_i155++) {
    c2_qp[c2_i155] = 0.0;
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 13);
  c2_i = 1.0;
  c2_b_i = 0;
  while (c2_b_i < 5) {
    c2_i = 1.0 + (real_T)c2_b_i;
    CV_SCRIPT_FOR(1, 0, 1);
    _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 14);
    c2_b_qd1 = c2_qd1[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("qd1",
      (int32_T)_SFD_INTEGER_CHECK("i", c2_i), 1, 5, 1, 0) - 1];
    c2_c_dqd = c2_b_dqd[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("dqd",
      (int32_T)_SFD_INTEGER_CHECK("i", c2_i), 1, 5, 1, 0) - 1];
    c2_b_dqd1 = c2_dqd1[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("dqd1",
      (int32_T)_SFD_INTEGER_CHECK("i", c2_i), 1, 5, 1, 0) - 1];
    c2_b_dqd2 = c2_dqd2[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("dqd2",
      (int32_T)_SFD_INTEGER_CHECK("i", c2_i), 1, 5, 1, 0) - 1];
    c2_b_ddqd1 = c2_ddqd1[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("ddqd1",
      (int32_T)_SFD_INTEGER_CHECK("i", c2_i), 1, 5, 1, 0) - 1];
    c2_b_ddqd2 = c2_ddqd2[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("ddqd2",
      (int32_T)_SFD_INTEGER_CHECK("i", c2_i), 1, 5, 1, 0) - 1];
    c2_c_td = c2_b_td;
    c2_b_t = c2_t;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c2_b_debug_family_names,
      c2_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_t1, 0U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_t2, 1U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 2U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 3U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_qd1, 4U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_dqd, 5U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_dqd1, 6U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_dqd2, 7U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_ddqd1, 8U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_ddqd2, 9U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_td, 10U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_t, 11U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_qp, 12U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    CV_SCRIPT_FCN(2, 0);
    _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 17);
    guard1 = FALSE;
    if (CV_SCRIPT_COND(2, 0, c2_b_ddqd1 != 0.0)) {
      if (CV_SCRIPT_COND(2, 1, c2_b_ddqd2 != 0.0)) {
        CV_SCRIPT_MCDC(2, 0, TRUE);
        CV_SCRIPT_IF(2, 0, TRUE);
        _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 18);
        c2_A = c2_c_dqd - c2_b_dqd1;
        c2_B = c2_b_ddqd1;
        c2_x = c2_A;
        c2_y = c2_B;
        c2_b_x = c2_x;
        c2_b_y = c2_y;
        c2_c_y = c2_b_x / c2_b_y;
        c2_c_x = c2_c_y;
        c2_d_x = c2_c_x;
        c2_t1 = muDoubleScalarAbs(c2_d_x);
        _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 19);
        c2_b_A = c2_b_dqd2 - c2_c_dqd;
        c2_b_B = c2_b_ddqd2;
        c2_e_x = c2_b_A;
        c2_d_y = c2_b_B;
        c2_f_x = c2_e_x;
        c2_e_y = c2_d_y;
        c2_f_y = c2_f_x / c2_e_y;
        c2_g_x = c2_f_y;
        c2_h_x = c2_g_x;
        c2_g_y = muDoubleScalarAbs(c2_h_x);
        c2_t2 = c2_c_td - c2_g_y;
        _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 21);
        if (CV_SCRIPT_IF(2, 1, c2_b_t < c2_t1)) {
          _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 31);
          c2_a = c2_b_dqd1;
          c2_b = c2_b_t;
          c2_h_y = c2_a * c2_b;
          c2_b_a = c2_b_ddqd1;
          c2_b_b = c2_b_t;
          c2_i_y = c2_b_a * c2_b_b;
          c2_c_a = c2_i_y;
          c2_c_b = c2_b_t;
          c2_j_y = c2_c_a * c2_c_b;
          c2_c_A = c2_j_y;
          c2_i_x = c2_c_A;
          c2_j_x = c2_i_x;
          c2_k_y = c2_j_x / 2.0;
          c2_b_qp = (c2_b_qd1 + c2_h_y) + c2_k_y;
        } else {
          _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 32);
          guard2 = FALSE;
          if (CV_SCRIPT_COND(2, 2, c2_b_t >= c2_t1)) {
            if (CV_SCRIPT_COND(2, 3, c2_b_t <= c2_t2)) {
              CV_SCRIPT_MCDC(2, 1, TRUE);
              CV_SCRIPT_IF(2, 2, TRUE);
              _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 38);
              c2_d_a = c2_b_dqd1;
              c2_d_b = c2_t1;
              c2_l_y = c2_d_a * c2_d_b;
              c2_e_a = c2_b_ddqd1;
              c2_e_b = c2_t1;
              c2_m_y = c2_e_a * c2_e_b;
              c2_f_a = c2_m_y;
              c2_f_b = c2_t1;
              c2_n_y = c2_f_a * c2_f_b;
              c2_d_A = c2_n_y;
              c2_k_x = c2_d_A;
              c2_l_x = c2_k_x;
              c2_o_y = c2_l_x / 2.0;
              c2_g_a = c2_c_dqd;
              c2_g_b = c2_b_t - c2_t1;
              c2_p_y = c2_g_a * c2_g_b;
              c2_b_qp = ((c2_b_qd1 + c2_l_y) + c2_o_y) + c2_p_y;
            } else {
              guard2 = TRUE;
            }
          } else {
            guard2 = TRUE;
          }

          if (guard2 == TRUE) {
            CV_SCRIPT_MCDC(2, 1, FALSE);
            CV_SCRIPT_IF(2, 2, FALSE);
            _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 45);
            c2_h_a = c2_b_dqd1;
            c2_h_b = c2_t1;
            c2_q_y = c2_h_a * c2_h_b;
            c2_i_a = c2_b_ddqd1;
            c2_i_b = c2_t1;
            c2_r_y = c2_i_a * c2_i_b;
            c2_j_a = c2_r_y;
            c2_j_b = c2_t1;
            c2_s_y = c2_j_a * c2_j_b;
            c2_e_A = c2_s_y;
            c2_m_x = c2_e_A;
            c2_n_x = c2_m_x;
            c2_t_y = c2_n_x / 2.0;
            c2_k_a = c2_c_dqd;
            c2_k_b = c2_t2 - c2_t1;
            c2_u_y = c2_k_a * c2_k_b;
            c2_l_a = c2_c_dqd;
            c2_l_b = c2_b_t - c2_t2;
            c2_v_y = c2_l_a * c2_l_b;
            c2_m_a = c2_b_ddqd2;
            c2_m_b = c2_b_t - c2_t2;
            c2_w_y = c2_m_a * c2_m_b;
            c2_n_a = c2_w_y;
            c2_n_b = c2_b_t - c2_t2;
            c2_x_y = c2_n_a * c2_n_b;
            c2_f_A = c2_x_y;
            c2_o_x = c2_f_A;
            c2_p_x = c2_o_x;
            c2_y_y = c2_p_x / 2.0;
            c2_b_qp = ((((c2_b_qd1 + c2_q_y) + c2_t_y) + c2_u_y) + c2_v_y) +
              c2_y_y;
          }
        }
      } else {
        guard1 = TRUE;
      }
    } else {
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      CV_SCRIPT_MCDC(2, 0, FALSE);
      CV_SCRIPT_IF(2, 0, FALSE);
      _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 48);
      c2_b_qp = 0.0;
    }

    _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 50);
    c2_q_x = c2_b_qp;
    c2_b0 = muDoubleScalarIsNaN(c2_q_x);
    c2_b1 = (c2_b_qp == rtInf);
    if (CV_SCRIPT_IF(2, 3, c2_b0 || c2_b1)) {
      _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 51);
      c2_b_qp = 0.0;
    }

    _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, -51);
    _SFD_SYMBOL_SCOPE_POP();
    c2_qp[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("qp", (int32_T)
      _SFD_INTEGER_CHECK("i", c2_i), 1, 5, 1, 0) - 1] = c2_b_qp;
    c2_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_SCRIPT_FOR(1, 0, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, -14);
  _SFD_SYMBOL_SCOPE_POP();
}

static real_T c2_UNTITLED_dqd_new1(SFc2_AssemControl3InstanceStruct
  *chartInstance, real_T c2_qd1, real_T c2_qd2, real_T c2_dqd2, real_T c2_ddqd1,
  real_T c2_ddqd2, real_T c2_b_td)
{
  real_T c2_b_dqd;
  uint32_T c2_debug_family_var_map[9];
  real_T c2_nargin = 6.0;
  real_T c2_nargout = 1.0;
  real_T c2_b_qd1;
  real_T c2_b_qd2;
  real_T c2_dqd1;
  real_T c2_b_ddqd1;
  real_T c2_b_ddqd2;
  real_T c2_c_td;
  uint32_T c2_b_debug_family_var_map[13];
  real_T c2_a;
  real_T c2_b;
  real_T c2_c;
  real_T c2_x;
  real_T c2_b_nargin = 6.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_B;
  real_T c2_y;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_b_B;
  real_T c2_d_y;
  real_T c2_e_y;
  real_T c2_f_y;
  real_T c2_A;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_b_A;
  real_T c2_c_B;
  real_T c2_d_x;
  real_T c2_g_y;
  real_T c2_e_x;
  real_T c2_h_y;
  real_T c2_i_y;
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_j_y;
  real_T c2_c_b;
  real_T c2_k_y;
  real_T c2_c_A;
  real_T c2_d_B;
  real_T c2_f_x;
  real_T c2_l_y;
  real_T c2_g_x;
  real_T c2_m_y;
  real_T c2_n_y;
  real_T c2_d_A;
  real_T c2_e_B;
  real_T c2_h_x;
  real_T c2_o_y;
  real_T c2_i_x;
  real_T c2_p_y;
  real_T c2_c_a;
  real_T c2_d_b;
  real_T c2_q_y;
  real_T c2_e_b;
  real_T c2_r_y;
  real_T c2_d_a;
  real_T c2_f_b;
  real_T c2_s_y;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_t_y;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_g_b;
  real_T c2_u_y;
  real_T c2_e_A;
  real_T c2_f_B;
  real_T c2_n_x;
  real_T c2_v_y;
  real_T c2_o_x;
  real_T c2_w_y;
  boolean_T c2_u;
  const mxArray *c2_x_y = NULL;
  real_T c2_e_a;
  real_T c2_h_b;
  real_T c2_y_y;
  real_T c2_i_b;
  real_T c2_ab_y;
  real_T c2_f_a;
  real_T c2_j_b;
  real_T c2_bb_y;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_cb_y;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_k_b;
  real_T c2_db_y;
  real_T c2_f_A;
  real_T c2_g_B;
  real_T c2_t_x;
  real_T c2_eb_y;
  real_T c2_u_x;
  real_T c2_fb_y;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c2_e_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 0U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 1U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_qd1, 2U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_qd2, 3U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dqd2, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ddqd1, 5U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ddqd2, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_td, 7U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_dqd, 8U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  CV_SCRIPT_FCN(4, 0);
  _SFD_SCRIPT_CALL(4U, chartInstance->c2_sfEvent, 4);
  c2_b_qd1 = c2_qd1;
  c2_b_qd2 = c2_qd2;
  c2_dqd1 = c2_dqd2;
  c2_b_ddqd1 = -c2_ddqd2;
  c2_b_ddqd2 = -c2_ddqd1;
  c2_c_td = c2_b_td;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c2_d_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_a, 0U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b, 1U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c, 2U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_x, 3U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 5U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_qd1, 6U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_qd2, 7U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_dqd1, 8U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_ddqd1, 9U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_ddqd2, 10U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_td, 11U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_dqd, 12U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  CV_SCRIPT_FCN(5, 0);
  _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 6);
  c2_B = c2_b_ddqd2;
  c2_y = c2_B;
  c2_b_y = c2_y;
  c2_c_y = 1.0 / c2_b_y;
  c2_b_B = c2_b_ddqd1;
  c2_d_y = c2_b_B;
  c2_e_y = c2_d_y;
  c2_f_y = 1.0 / c2_e_y;
  c2_A = c2_c_y - c2_f_y;
  c2_b_x = c2_A;
  c2_c_x = c2_b_x;
  c2_a = c2_c_x / 2.0;
  _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 7);
  c2_b_A = c2_dqd1;
  c2_c_B = c2_b_ddqd2;
  c2_d_x = c2_b_A;
  c2_g_y = c2_c_B;
  c2_e_x = c2_d_x;
  c2_h_y = c2_g_y;
  c2_i_y = c2_e_x / c2_h_y;
  c2_b = c2_c_td - c2_i_y;
  _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 8);
  c2_b_a = c2_dqd1;
  c2_b_b = c2_dqd1;
  c2_j_y = c2_b_a * c2_b_b;
  c2_c_b = c2_b_ddqd2;
  c2_k_y = 2.0 * c2_c_b;
  c2_c_A = c2_j_y;
  c2_d_B = c2_k_y;
  c2_f_x = c2_c_A;
  c2_l_y = c2_d_B;
  c2_g_x = c2_f_x;
  c2_m_y = c2_l_y;
  c2_n_y = c2_g_x / c2_m_y;
  c2_c = (c2_b_qd1 - c2_b_qd2) + c2_n_y;
  _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 17);
  if (CV_SCRIPT_IF(5, 0, c2_a == 0.0)) {
    _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 18);
    if (CV_SCRIPT_IF(5, 1, c2_b == 0.0)) {
      _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 19);
      c2_x = 0.0;
    } else {
      _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 21);
      c2_d_A = -c2_c;
      c2_e_B = c2_b;
      c2_h_x = c2_d_A;
      c2_o_y = c2_e_B;
      c2_i_x = c2_h_x;
      c2_p_y = c2_o_y;
      c2_x = c2_i_x / c2_p_y;
    }
  } else {
    _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 24);
    if (CV_SCRIPT_IF(5, 2, c2_b >= 0.0)) {
      _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 25);
      c2_c_a = c2_b;
      c2_d_b = c2_b;
      c2_q_y = c2_c_a * c2_d_b;
      c2_e_b = c2_a;
      c2_r_y = 4.0 * c2_e_b;
      c2_d_a = c2_r_y;
      c2_f_b = c2_c;
      c2_s_y = c2_d_a * c2_f_b;
      c2_j_x = c2_q_y - c2_s_y;
      c2_k_x = c2_j_x;
      c2_t_y = muDoubleScalarAbs(c2_k_x);
      c2_l_x = c2_t_y;
      c2_m_x = c2_l_x;
      if (c2_m_x < 0.0) {
        c2_eml_error(chartInstance);
      }

      c2_m_x = muDoubleScalarSqrt(c2_m_x);
      c2_g_b = c2_a;
      c2_u_y = 2.0 * c2_g_b;
      c2_e_A = -c2_b + c2_m_x;
      c2_f_B = c2_u_y;
      c2_n_x = c2_e_A;
      c2_v_y = c2_f_B;
      c2_o_x = c2_n_x;
      c2_w_y = c2_v_y;
      c2_x = c2_o_x / c2_w_y;
    } else {
      _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 26);
      sf_mex_printf("%s =\\n", "ans");
      c2_u = (c2_b < 0.0);
      c2_x_y = NULL;
      sf_mex_assign(&c2_x_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), FALSE);
      sf_mex_call_debug("disp", 0U, 1U, 14, c2_x_y);
      _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 27);
      c2_e_a = c2_b;
      c2_h_b = c2_b;
      c2_y_y = c2_e_a * c2_h_b;
      c2_i_b = c2_a;
      c2_ab_y = 4.0 * c2_i_b;
      c2_f_a = c2_ab_y;
      c2_j_b = c2_c;
      c2_bb_y = c2_f_a * c2_j_b;
      c2_p_x = c2_y_y - c2_bb_y;
      c2_q_x = c2_p_x;
      c2_cb_y = muDoubleScalarAbs(c2_q_x);
      c2_r_x = c2_cb_y;
      c2_s_x = c2_r_x;
      if (c2_s_x < 0.0) {
        c2_eml_error(chartInstance);
      }

      c2_s_x = muDoubleScalarSqrt(c2_s_x);
      c2_k_b = c2_a;
      c2_db_y = 2.0 * c2_k_b;
      c2_f_A = -c2_b - c2_s_x;
      c2_g_B = c2_db_y;
      c2_t_x = c2_f_A;
      c2_eb_y = c2_g_B;
      c2_u_x = c2_t_x;
      c2_fb_y = c2_eb_y;
      c2_x = c2_u_x / c2_fb_y;
    }
  }

  _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 30);
  if (CV_SCRIPT_IF(5, 3, c2_a == rtInf)) {
    _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 31);
    c2_x = 0.0;
  }

  _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, 33);
  c2_b_dqd = c2_x;
  _SFD_SCRIPT_CALL(5U, chartInstance->c2_sfEvent, -33);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_SCRIPT_CALL(4U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  return c2_b_dqd;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 0U, sf_debug_get_script_id(
    "C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_qp.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 1U, sf_debug_get_script_id(
    "C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Matrica_qp.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 2U, sf_debug_get_script_id(
    "C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Zglob_qp.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 3U, sf_debug_get_script_id(
    "C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_dqd_new.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 4U, sf_debug_get_script_id(
    "C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new1.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 5U, sf_debug_get_script_id(
    "C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i156;
  real_T c2_b_inData[3];
  int32_T c2_i157;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i156 = 0; c2_i156 < 3; c2_i156++) {
    c2_b_inData[c2_i156] = (*(real_T (*)[3])c2_inData)[c2_i156];
  }

  for (c2_i157 = 0; c2_i157 < 3; c2_i157++) {
    c2_u[c2_i157] = c2_b_inData[c2_i157];
  }

  c2_y = NULL;
  if (!chartInstance->c2_td_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct *chartInstance,
  const mxArray *c2_b_td, const char_T *c2_identifier, real_T c2_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_td), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_td);
}

static void c2_b_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv22[3];
  int32_T c2_i158;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_td_not_empty = FALSE;
  } else {
    chartInstance->c2_td_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv22, 1, 0, 0U, 1, 0U, 2, 1,
                  3);
    for (c2_i158 = 0; c2_i158 < 3; c2_i158++) {
      c2_y[c2_i158] = c2_dv22[c2_i158];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_td;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i159;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_td = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_td), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_td);
  for (c2_i159 = 0; c2_i159 < 3; c2_i159++) {
    (*(real_T (*)[3])c2_outData)[c2_i159] = c2_y[c2_i159];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i160;
  int32_T c2_i161;
  int32_T c2_i162;
  real_T c2_b_inData[20];
  int32_T c2_i163;
  int32_T c2_i164;
  int32_T c2_i165;
  real_T c2_u[20];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i160 = 0;
  for (c2_i161 = 0; c2_i161 < 5; c2_i161++) {
    for (c2_i162 = 0; c2_i162 < 4; c2_i162++) {
      c2_b_inData[c2_i162 + c2_i160] = (*(real_T (*)[20])c2_inData)[c2_i162 +
        c2_i160];
    }

    c2_i160 += 4;
  }

  c2_i163 = 0;
  for (c2_i164 = 0; c2_i164 < 5; c2_i164++) {
    for (c2_i165 = 0; c2_i165 < 4; c2_i165++) {
      c2_u[c2_i165 + c2_i163] = c2_b_inData[c2_i165 + c2_i163];
    }

    c2_i163 += 4;
  }

  c2_y = NULL;
  if (!chartInstance->c2_ddqd_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 5), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_ddqd, const char_T *c2_identifier, real_T
  c2_y[20])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_ddqd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_ddqd);
}

static void c2_d_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[20])
{
  real_T c2_dv23[20];
  int32_T c2_i166;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_ddqd_not_empty = FALSE;
  } else {
    chartInstance->c2_ddqd_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv23, 1, 0, 0U, 1, 0U, 2, 4,
                  5);
    for (c2_i166 = 0; c2_i166 < 20; c2_i166++) {
      c2_y[c2_i166] = c2_dv23[c2_i166];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_ddqd;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[20];
  int32_T c2_i167;
  int32_T c2_i168;
  int32_T c2_i169;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_ddqd = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_ddqd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_ddqd);
  c2_i167 = 0;
  for (c2_i168 = 0; c2_i168 < 5; c2_i168++) {
    for (c2_i169 = 0; c2_i169 < 4; c2_i169++) {
      (*(real_T (*)[20])c2_outData)[c2_i169 + c2_i167] = c2_y[c2_i169 + c2_i167];
    }

    c2_i167 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i170;
  int32_T c2_i171;
  int32_T c2_i172;
  real_T c2_b_inData[15];
  int32_T c2_i173;
  int32_T c2_i174;
  int32_T c2_i175;
  real_T c2_u[15];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i170 = 0;
  for (c2_i171 = 0; c2_i171 < 5; c2_i171++) {
    for (c2_i172 = 0; c2_i172 < 3; c2_i172++) {
      c2_b_inData[c2_i172 + c2_i170] = (*(real_T (*)[15])c2_inData)[c2_i172 +
        c2_i170];
    }

    c2_i170 += 3;
  }

  c2_i173 = 0;
  for (c2_i174 = 0; c2_i174 < 5; c2_i174++) {
    for (c2_i175 = 0; c2_i175 < 3; c2_i175++) {
      c2_u[c2_i175 + c2_i173] = c2_b_inData[c2_i175 + c2_i173];
    }

    c2_i173 += 3;
  }

  c2_y = NULL;
  if (!chartInstance->c2_dqd_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 5), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_dqd, const char_T *c2_identifier, real_T
  c2_y[15])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dqd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_dqd);
}

static void c2_f_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[15])
{
  real_T c2_dv24[15];
  int32_T c2_i176;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_dqd_not_empty = FALSE;
  } else {
    chartInstance->c2_dqd_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv24, 1, 0, 0U, 1, 0U, 2, 3,
                  5);
    for (c2_i176 = 0; c2_i176 < 15; c2_i176++) {
      c2_y[c2_i176] = c2_dv24[c2_i176];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_dqd;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[15];
  int32_T c2_i177;
  int32_T c2_i178;
  int32_T c2_i179;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_dqd = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dqd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_dqd);
  c2_i177 = 0;
  for (c2_i178 = 0; c2_i178 < 5; c2_i178++) {
    for (c2_i179 = 0; c2_i179 < 3; c2_i179++) {
      (*(real_T (*)[15])c2_outData)[c2_i179 + c2_i177] = c2_y[c2_i179 + c2_i177];
    }

    c2_i177 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i180;
  int32_T c2_i181;
  int32_T c2_i182;
  real_T c2_b_inData[20];
  int32_T c2_i183;
  int32_T c2_i184;
  int32_T c2_i185;
  real_T c2_u[20];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i180 = 0;
  for (c2_i181 = 0; c2_i181 < 5; c2_i181++) {
    for (c2_i182 = 0; c2_i182 < 4; c2_i182++) {
      c2_b_inData[c2_i182 + c2_i180] = (*(real_T (*)[20])c2_inData)[c2_i182 +
        c2_i180];
    }

    c2_i180 += 4;
  }

  c2_i183 = 0;
  for (c2_i184 = 0; c2_i184 < 5; c2_i184++) {
    for (c2_i185 = 0; c2_i185 < 4; c2_i185++) {
      c2_u[c2_i185 + c2_i183] = c2_b_inData[c2_i185 + c2_i183];
    }

    c2_i183 += 4;
  }

  c2_y = NULL;
  if (!chartInstance->c2_qd_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 5), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_qd, const char_T *c2_identifier, real_T
  c2_y[20])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_qd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_qd);
}

static void c2_h_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[20])
{
  real_T c2_dv25[20];
  int32_T c2_i186;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_qd_not_empty = FALSE;
  } else {
    chartInstance->c2_qd_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv25, 1, 0, 0U, 1, 0U, 2, 4,
                  5);
    for (c2_i186 = 0; c2_i186 < 20; c2_i186++) {
      c2_y[c2_i186] = c2_dv25[c2_i186];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_qd;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[20];
  int32_T c2_i187;
  int32_T c2_i188;
  int32_T c2_i189;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_qd = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_qd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_qd);
  c2_i187 = 0;
  for (c2_i188 = 0; c2_i188 < 5; c2_i188++) {
    for (c2_i189 = 0; c2_i189 < 4; c2_i189++) {
      (*(real_T (*)[20])c2_outData)[c2_i189 + c2_i187] = c2_y[c2_i189 + c2_i187];
    }

    c2_i187 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_v_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_i_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_v, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_v), &c2_thisId);
  sf_mex_destroy(&c2_b_v);
  return c2_y;
}

static real_T c2_j_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_v_not_empty = FALSE;
  } else {
    chartInstance->c2_v_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d0;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_v;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_v = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_v), &c2_thisId);
  sf_mex_destroy(&c2_b_v);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i190;
  real_T c2_b_inData[6];
  int32_T c2_i191;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i190 = 0; c2_i190 < 6; c2_i190++) {
    c2_b_inData[c2_i190] = (*(real_T (*)[6])c2_inData)[c2_i190];
  }

  for (c2_i191 = 0; c2_i191 < 6; c2_i191++) {
    c2_u[c2_i191] = c2_b_inData[c2_i191];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_k_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_qp, const char_T *c2_identifier, real_T
  c2_y[6])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_qp), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_qp);
}

static void c2_l_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6])
{
  real_T c2_dv26[6];
  int32_T c2_i192;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv26, 1, 0, 0U, 1, 0U, 2, 1, 6);
  for (c2_i192 = 0; c2_i192 < 6; c2_i192++) {
    c2_y[c2_i192] = c2_dv26[c2_i192];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_qp;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[6];
  int32_T c2_i193;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_qp = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_qp), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_qp);
  for (c2_i193 = 0; c2_i193 < 6; c2_i193++) {
    (*(real_T (*)[6])c2_outData)[c2_i193] = c2_y[c2_i193];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_m_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d1;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d1, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d1;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i194;
  real_T c2_b_inData[5];
  int32_T c2_i195;
  real_T c2_u[5];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i194 = 0; c2_i194 < 5; c2_i194++) {
    c2_b_inData[c2_i194] = (*(real_T (*)[5])c2_inData)[c2_i194];
  }

  for (c2_i195 = 0; c2_i195 < 5; c2_i195++) {
    c2_u[c2_i195] = c2_b_inData[c2_i195];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 5), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_n_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[5])
{
  real_T c2_dv27[5];
  int32_T c2_i196;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv27, 1, 0, 0U, 1, 0U, 2, 1, 5);
  for (c2_i196 = 0; c2_i196 < 5; c2_i196++) {
    c2_y[c2_i196] = c2_dv27[c2_i196];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_dqp;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[5];
  int32_T c2_i197;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_dqp = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_dqp), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_dqp);
  for (c2_i197 = 0; c2_i197 < 5; c2_i197++) {
    (*(real_T (*)[5])c2_outData)[c2_i197] = c2_y[c2_i197];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i198;
  int32_T c2_i199;
  int32_T c2_i200;
  real_T c2_b_inData[10];
  int32_T c2_i201;
  int32_T c2_i202;
  int32_T c2_i203;
  real_T c2_u[10];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i198 = 0;
  for (c2_i199 = 0; c2_i199 < 5; c2_i199++) {
    for (c2_i200 = 0; c2_i200 < 2; c2_i200++) {
      c2_b_inData[c2_i200 + c2_i198] = (*(real_T (*)[10])c2_inData)[c2_i200 +
        c2_i198];
    }

    c2_i198 += 2;
  }

  c2_i201 = 0;
  for (c2_i202 = 0; c2_i202 < 5; c2_i202++) {
    for (c2_i203 = 0; c2_i203 < 2; c2_i203++) {
      c2_u[c2_i203 + c2_i201] = c2_b_inData[c2_i203 + c2_i201];
    }

    c2_i201 += 2;
  }

  c2_y = NULL;
  if (!chartInstance->c2_state_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 2, 5), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_o_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_state, const char_T *c2_identifier, real_T
  c2_y[10])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_state), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_state);
}

static void c2_p_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[10])
{
  real_T c2_dv28[10];
  int32_T c2_i204;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_state_not_empty = FALSE;
  } else {
    chartInstance->c2_state_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv28, 1, 0, 0U, 1, 0U, 2, 2,
                  5);
    for (c2_i204 = 0; c2_i204 < 10; c2_i204++) {
      c2_y[c2_i204] = c2_dv28[c2_i204];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_state;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[10];
  int32_T c2_i205;
  int32_T c2_i206;
  int32_T c2_i207;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_state = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_state), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_state);
  c2_i205 = 0;
  for (c2_i206 = 0; c2_i206 < 5; c2_i206++) {
    for (c2_i207 = 0; c2_i207 < 2; c2_i207++) {
      (*(real_T (*)[10])c2_outData)[c2_i207 + c2_i205] = c2_y[c2_i207 + c2_i205];
    }

    c2_i205 += 2;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i208;
  real_T c2_b_inData[5];
  int32_T c2_i209;
  real_T c2_u[5];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i208 = 0; c2_i208 < 5; c2_i208++) {
    c2_b_inData[c2_i208] = (*(real_T (*)[5])c2_inData)[c2_i208];
  }

  for (c2_i209 = 0; c2_i209 < 5; c2_i209++) {
    c2_u[c2_i209] = c2_b_inData[c2_i209];
  }

  c2_y = NULL;
  if (!chartInstance->c2_dqdNEW_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 5), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_q_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_dqdNEW, const char_T *c2_identifier,
  real_T c2_y[5])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dqdNEW), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_dqdNEW);
}

static void c2_r_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[5])
{
  real_T c2_dv29[5];
  int32_T c2_i210;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_dqdNEW_not_empty = FALSE;
  } else {
    chartInstance->c2_dqdNEW_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv29, 1, 0, 0U, 1, 0U, 2, 1,
                  5);
    for (c2_i210 = 0; c2_i210 < 5; c2_i210++) {
      c2_y[c2_i210] = c2_dv29[c2_i210];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_dqdNEW;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[5];
  int32_T c2_i211;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_dqdNEW = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dqdNEW), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_dqdNEW);
  for (c2_i211 = 0; c2_i211 < 5; c2_i211++) {
    (*(real_T (*)[5])c2_outData)[c2_i211] = c2_y[c2_i211];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i212;
  real_T c2_b_inData[3];
  int32_T c2_i213;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i212 = 0; c2_i212 < 3; c2_i212++) {
    c2_b_inData[c2_i212] = (*(real_T (*)[3])c2_inData)[c2_i212];
  }

  for (c2_i213 = 0; c2_i213 < 3; c2_i213++) {
    c2_u[c2_i213] = c2_b_inData[c2_i213];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_mrdivide;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i214;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mrdivide = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_mrdivide), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_mrdivide);
  for (c2_i214 = 0; c2_i214 < 3; c2_i214++) {
    (*(real_T (*)[3])c2_outData)[c2_i214] = c2_y[c2_i214];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i215;
  int32_T c2_i216;
  int32_T c2_i217;
  real_T c2_b_inData[20];
  int32_T c2_i218;
  int32_T c2_i219;
  int32_T c2_i220;
  real_T c2_u[20];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i215 = 0;
  for (c2_i216 = 0; c2_i216 < 5; c2_i216++) {
    for (c2_i217 = 0; c2_i217 < 4; c2_i217++) {
      c2_b_inData[c2_i217 + c2_i215] = (*(real_T (*)[20])c2_inData)[c2_i217 +
        c2_i215];
    }

    c2_i215 += 4;
  }

  c2_i218 = 0;
  for (c2_i219 = 0; c2_i219 < 5; c2_i219++) {
    for (c2_i220 = 0; c2_i220 < 4; c2_i220++) {
      c2_u[c2_i220 + c2_i218] = c2_b_inData[c2_i220 + c2_i218];
    }

    c2_i218 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 5), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_qd;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[20];
  int32_T c2_i221;
  int32_T c2_i222;
  int32_T c2_i223;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_qd = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_qd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_qd);
  c2_i221 = 0;
  for (c2_i222 = 0; c2_i222 < 5; c2_i222++) {
    for (c2_i223 = 0; c2_i223 < 4; c2_i223++) {
      (*(real_T (*)[20])c2_outData)[c2_i223 + c2_i221] = c2_y[c2_i223 + c2_i221];
    }

    c2_i221 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i224;
  int32_T c2_i225;
  int32_T c2_i226;
  real_T c2_b_inData[15];
  int32_T c2_i227;
  int32_T c2_i228;
  int32_T c2_i229;
  real_T c2_u[15];
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i224 = 0;
  for (c2_i225 = 0; c2_i225 < 5; c2_i225++) {
    for (c2_i226 = 0; c2_i226 < 3; c2_i226++) {
      c2_b_inData[c2_i226 + c2_i224] = (*(real_T (*)[15])c2_inData)[c2_i226 +
        c2_i224];
    }

    c2_i224 += 3;
  }

  c2_i227 = 0;
  for (c2_i228 = 0; c2_i228 < 5; c2_i228++) {
    for (c2_i229 = 0; c2_i229 < 3; c2_i229++) {
      c2_u[c2_i229 + c2_i227] = c2_b_inData[c2_i229 + c2_i227];
    }

    c2_i227 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 5), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_dqd;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[15];
  int32_T c2_i230;
  int32_T c2_i231;
  int32_T c2_i232;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_dqd = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dqd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_dqd);
  c2_i230 = 0;
  for (c2_i231 = 0; c2_i231 < 5; c2_i231++) {
    for (c2_i232 = 0; c2_i232 < 3; c2_i232++) {
      (*(real_T (*)[15])c2_outData)[c2_i232 + c2_i230] = c2_y[c2_i232 + c2_i230];
    }

    c2_i230 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_AssemControl3_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[23];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i233;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 23), FALSE);
  for (c2_i233 = 0; c2_i233 < 23; c2_i233++) {
    c2_r0 = &c2_info[c2_i233];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i233);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i233);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i233);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i233);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i233);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i233);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i233);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i233);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[23])
{
  c2_info[0].context = "";
  c2_info[0].name = "mrdivide";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[0].fileTimeLo = 1357951548U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 1319729966U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[1].name = "rdivide";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[1].fileTimeLo = 1346510388U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[2].name = "eml_scalexp_compatible";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[2].fileTimeLo = 1286818796U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[3].name = "eml_div";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[3].fileTimeLo = 1313347810U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "";
  c2_info[4].name = "mtimes";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[4].fileTimeLo = 1289519692U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "";
  c2_info[5].name = "Presmetaj_qp";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_qp.m";
  c2_info[5].fileTimeLo = 1406813803U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_qp.m";
  c2_info[6].name = "mrdivide";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[6].fileTimeLo = 1357951548U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 1319729966U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_qp.m";
  c2_info[7].name = "Matrica_qp";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Matrica_qp.m";
  c2_info[7].fileTimeLo = 1401632572U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Matrica_qp.m";
  c2_info[8].name = "Zglob_qp";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Zglob_qp.m";
  c2_info[8].fileTimeLo = 1407706515U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Zglob_qp.m";
  c2_info[9].name = "mrdivide";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[9].fileTimeLo = 1357951548U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 1319729966U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Zglob_qp.m";
  c2_info[10].name = "abs";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[10].fileTimeLo = 1343830366U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[11].name = "eml_scalar_abs";
  c2_info[11].dominantType = "double";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[11].fileTimeLo = 1286818712U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Zglob_qp.m";
  c2_info[12].name = "mtimes";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[12].fileTimeLo = 1289519692U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Zglob_qp.m";
  c2_info[13].name = "isnan";
  c2_info[13].dominantType = "double";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[13].fileTimeLo = 1286818760U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_qp.m";
  c2_info[14].name = "Presmetaj_dqd_new";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_dqd_new.m";
  c2_info[14].fileTimeLo = 1407432142U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_dqd_new.m";
  c2_info[15].name = "UNTITLED_dqd_new1";
  c2_info[15].dominantType = "double";
  c2_info[15].resolved =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new1.m";
  c2_info[15].fileTimeLo = 1407431671U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new1.m";
  c2_info[16].name = "UNTITLED_dqd_new";
  c2_info[16].dominantType = "double";
  c2_info[16].resolved =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new.m";
  c2_info[16].fileTimeLo = 1407534763U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new.m";
  c2_info[17].name = "mrdivide";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[17].fileTimeLo = 1357951548U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 1319729966U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new.m";
  c2_info[18].name = "mtimes";
  c2_info[18].dominantType = "double";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[18].fileTimeLo = 1289519692U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new.m";
  c2_info[19].name = "abs";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[19].fileTimeLo = 1343830366U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[E]C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/UNTITLED_dqd_new.m";
  c2_info[20].name = "sqrt";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[20].fileTimeLo = 1343830386U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[21].name = "eml_error";
  c2_info[21].dominantType = "char";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[21].fileTimeLo = 1343830358U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[22].name = "eml_scalar_sqrt";
  c2_info[22].dominantType = "double";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c2_info[22].fileTimeLo = 1286818738U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
}

static void c2_eml_error(SFc2_AssemControl3InstanceStruct *chartInstance)
{
  int32_T c2_i234;
  static char_T c2_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c2_u[30];
  const mxArray *c2_y = NULL;
  int32_T c2_i235;
  static char_T c2_cv1[4] = { 's', 'q', 'r', 't' };

  char_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  for (c2_i234 = 0; c2_i234 < 30; c2_i234++) {
    c2_u[c2_i234] = c2_cv0[c2_i234];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  for (c2_i235 = 0; c2_i235 < 4; c2_i235++) {
    c2_b_u[c2_i235] = c2_cv1[c2_i235];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U, 14,
    c2_y, 14, c2_b_y));
}

static void c2_s_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_mrdivide, const char_T *c2_identifier,
  real_T c2_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_mrdivide), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_mrdivide);
}

static void c2_t_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv30[3];
  int32_T c2_i236;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv30, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c2_i236 = 0; c2_i236 < 3; c2_i236++) {
    c2_y[c2_i236] = c2_dv30[c2_i236];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_u_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_qd, const char_T *c2_identifier, real_T
  c2_y[20])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_qd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_qd);
}

static void c2_v_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[20])
{
  real_T c2_dv31[20];
  int32_T c2_i237;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv31, 1, 0, 0U, 1, 0U, 2, 4, 5);
  for (c2_i237 = 0; c2_i237 < 20; c2_i237++) {
    c2_y[c2_i237] = c2_dv31[c2_i237];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_w_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_dqd, const char_T *c2_identifier, real_T
  c2_y[15])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dqd), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_dqd);
}

static void c2_x_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[15])
{
  real_T c2_dv32[15];
  int32_T c2_i238;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv32, 1, 0, 0U, 1, 0U, 2, 3, 5);
  for (c2_i238 = 0; c2_i238 < 15; c2_i238++) {
    c2_y[c2_i238] = c2_dv32[c2_i238];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_y_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i239;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i239, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i239;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_ab_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_AssemControl3, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_bb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_AssemControl3), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_AssemControl3);
  return c2_y;
}

static uint8_T c2_bb_emlrt_marshallIn(SFc2_AssemControl3InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_AssemControl3InstanceStruct
  *chartInstance)
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

void sf_c2_AssemControl3_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1852993781U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2812423980U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2884693234U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(39258389U);
}

mxArray *sf_c2_AssemControl3_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("RIrnkhset9gK0hZHd3QJVD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_AssemControl3_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c2_AssemControl3(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x9'type','srcId','name','auxInfo'{{M[1],M[5],T\"qp\",},{M[4],M[0],T\"ddqd\",S'l','i','p'{{M1x2[347 351],M[0],}}},{M[4],M[0],T\"dqd\",S'l','i','p'{{M1x2[327 330],M[0],}}},{M[4],M[0],T\"dqdNEW\",S'l','i','p'{{M1x2[542 548],M[1],T\"C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_qp.m\"}}},{M[4],M[0],T\"qd\",S'l','i','p'{{M1x2[308 310],M[0],}}},{M[4],M[0],T\"state\",S'l','i','p'{{M1x2[635 640],M[1],T\"C:/Users/Martin/Desktop/dipl/Diplomska gotova/RSM2G_3/Presmetaj_qp.m\"}}},{M[4],M[0],T\"td\",S'l','i','p'{{M1x2[368 370],M[0],}}},{M[4],M[0],T\"v\",S'l','i','p'{{M1x2[290 291],M[0],}}},{M[8],M[0],T\"is_active_c2_AssemControl3\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 9, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_AssemControl3_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_AssemControl3InstanceStruct *chartInstance;
    chartInstance = (SFc2_AssemControl3InstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _AssemControl3MachineNumber_,
           2,
           1,
           1,
           2,
           0,
           0,
           0,
           0,
           6,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_AssemControl3MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_AssemControl3MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _AssemControl3MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"qp");
          _SFD_SET_DATA_PROPS(1,1,1,0,"t");
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
        _SFD_CV_INIT_EML(0,1,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1053);
        _SFD_CV_INIT_EML_IF(0,1,0,377,390,-1,795);
        _SFD_CV_INIT_SCRIPT(0,1,4,0,0,0,0,0,2,1);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"Presmetaj_qp",0,-1,2552);
        _SFD_CV_INIT_SCRIPT_IF(0,0,646,664,-1,1311);
        _SFD_CV_INIT_SCRIPT_IF(0,1,1317,1330,1591,2548);
        _SFD_CV_INIT_SCRIPT_IF(0,2,1591,1616,1883,2548);
        _SFD_CV_INIT_SCRIPT_IF(0,3,1883,1937,2513,2548);

        {
          static int condStart[] = { 1890, 1911 };

          static int condEnd[] = { 1908, 1937 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(0,0,1890,1937,2,0,&(condStart[0]),&(condEnd[0]),
            3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,1,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"Matrica_qp",0,-1,744);
        _SFD_CV_INIT_SCRIPT_FOR(1,0,633,643,739);
        _SFD_CV_INIT_SCRIPT(2,1,4,0,0,0,0,0,4,2);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"Zglob_qp",0,-1,1781);
        _SFD_CV_INIT_SCRIPT_IF(2,0,684,710,1695,1723);
        _SFD_CV_INIT_SCRIPT_IF(2,1,806,815,1152,1690);
        _SFD_CV_INIT_SCRIPT_IF(2,2,1152,1176,1398,1690);
        _SFD_CV_INIT_SCRIPT_IF(2,3,1728,1752,-1,1776);

        {
          static int condStart[] = { 687, 700 };

          static int condEnd[] = { 697, 710 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(2,0,687,710,2,0,&(condStart[0]),&(condEnd[0]),
            3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 1159, 1169 };

          static int condEnd[] = { 1166, 1176 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(2,1,1159,1176,2,2,&(condStart[0]),&(condEnd[0]),
            3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(3,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"Presmetaj_dqd_new",0,-1,716);
        _SFD_CV_INIT_SCRIPT(4,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(4,0,"UNTITLED_dqd_new1",0,-1,222);
        _SFD_CV_INIT_SCRIPT(5,1,4,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(5,0,"UNTITLED_dqd_new",0,-1,873);
        _SFD_CV_INIT_SCRIPT_IF(5,0,563,572,661,820);
        _SFD_CV_INIT_SCRIPT_IF(5,1,581,590,618,656);
        _SFD_CV_INIT_SCRIPT_IF(5,2,674,683,741,812);
        _SFD_CV_INIT_SCRIPT_IF(5,3,825,834,-1,855);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)
            c2_f_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c2_t;
          real_T (*c2_qp)[6];
          c2_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c2_qp = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_qp);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_t);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _AssemControl3MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "vkpq7EMjF6FD7455sNM4wE";
}

static void sf_opaque_initialize_c2_AssemControl3(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_AssemControl3InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*)
    chartInstanceVar);
  initialize_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_AssemControl3(void *chartInstanceVar)
{
  enable_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_AssemControl3(void *chartInstanceVar)
{
  disable_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_AssemControl3(void *chartInstanceVar)
{
  sf_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_AssemControl3(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_AssemControl3
    ((SFc2_AssemControl3InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_AssemControl3();/* state var info */
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

extern void sf_internal_set_sim_state_c2_AssemControl3(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_AssemControl3();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_AssemControl3(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_AssemControl3(S);
}

static void sf_opaque_set_sim_state_c2_AssemControl3(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c2_AssemControl3(S, st);
}

static void sf_opaque_terminate_c2_AssemControl3(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_AssemControl3InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_AssemControl3_optimization_info();
    }

    finalize_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_AssemControl3((SFc2_AssemControl3InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_AssemControl3(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_AssemControl3((SFc2_AssemControl3InstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_AssemControl3(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_AssemControl3_optimization_info();
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(93644951U));
  ssSetChecksum1(S,(524773700U));
  ssSetChecksum2(S,(1143608949U));
  ssSetChecksum3(S,(192021453U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_AssemControl3(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_AssemControl3(SimStruct *S)
{
  SFc2_AssemControl3InstanceStruct *chartInstance;
  chartInstance = (SFc2_AssemControl3InstanceStruct *)utMalloc(sizeof
    (SFc2_AssemControl3InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_AssemControl3InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_AssemControl3;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_AssemControl3;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_AssemControl3;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_AssemControl3;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_AssemControl3;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_AssemControl3;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_AssemControl3;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_AssemControl3;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_AssemControl3;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_AssemControl3;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_AssemControl3;
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

void c2_AssemControl3_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_AssemControl3(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_AssemControl3(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_AssemControl3(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_AssemControl3_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
