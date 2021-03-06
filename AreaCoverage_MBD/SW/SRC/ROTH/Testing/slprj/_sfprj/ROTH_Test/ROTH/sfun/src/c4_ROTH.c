/* Include files */

#include "ROTH_sfun.h"
#include "c4_ROTH.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ROTH_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c4_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c4_IN_GTSP_Active              ((uint8_T)1U)
#define c4_IN_Idle                     ((uint8_T)2U)
#define c4_IN_Forward                  ((uint8_T)1U)
#define c4_IN_TurnLeft                 ((uint8_T)2U)
#define c4_IN_finishedGTSP             ((uint8_T)3U)
#define c4_IN_preFinishBlockedN        ((uint8_T)4U)
#define c4_IN_preFinishBlockedW        ((uint8_T)5U)
#define c4_IN_preFinishLeftBlockedN    ((uint8_T)6U)
#define c4_IN_preFinishLeftBlockedW    ((uint8_T)7U)
#define c4_IN_preFinishNormal          ((uint8_T)8U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void initialize_params_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void enable_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void disable_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_ROTH(SFc4_ROTHInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_ROTH(SFc4_ROTHInstanceStruct
  *chartInstance);
static void set_sim_state_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance, const
  mxArray *c4_st);
static void c4_set_sim_state_side_effects_c4_ROTH(SFc4_ROTHInstanceStruct
  *chartInstance);
static void finalize_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void sf_gateway_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void mdl_start_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void initSimStructsc4_ROTH(SFc4_ROTHInstanceStruct *chartInstance);
static void c4_GTSP_Active(SFc4_ROTHInstanceStruct *chartInstance);
static void c4_exit_internal_GTSP_Active(SFc4_ROTHInstanceStruct *chartInstance);
static void c4_Forward(SFc4_ROTHInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static int32_T c4_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance, const
  mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static uint8_T c4_b_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_b_tp_GTSP_Active, const char_T *c4_identifier);
static uint8_T c4_c_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static boolean_T c4_d_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_b_GT_active, const char_T *c4_identifier);
static boolean_T c4_e_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_f_emlrt_marshallIn(SFc4_ROTHInstanceStruct
  *chartInstance, const mxArray *c4_b_setSimStateSideEffectsInfo, const char_T
  *c4_identifier);
static const mxArray *c4_g_emlrt_marshallIn(SFc4_ROTHInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static const mxArray *sf_get_hover_data_for_msg(SFc4_ROTHInstanceStruct
  *chartInstance, int32_T c4_ssid);
static void c4_init_sf_message_store_memory(SFc4_ROTHInstanceStruct
  *chartInstance);
static void init_dsm_address_info(SFc4_ROTHInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc4_ROTHInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc4_ROTH(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_doSetSimStateSideEffects = 0U;
  chartInstance->c4_setSimStateSideEffectsInfo = NULL;
  chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
  chartInstance->c4_tp_GTSP_Active = 0U;
  chartInstance->c4_tp_Forward = 0U;
  chartInstance->c4_tp_TurnLeft = 0U;
  chartInstance->c4_tp_finishedGTSP = 0U;
  chartInstance->c4_tp_preFinishBlockedN = 0U;
  chartInstance->c4_tp_preFinishBlockedW = 0U;
  chartInstance->c4_tp_preFinishLeftBlockedN = 0U;
  chartInstance->c4_tp_preFinishLeftBlockedW = 0U;
  chartInstance->c4_tp_preFinishNormal = 0U;
  chartInstance->c4_tp_Idle = 0U;
  chartInstance->c4_is_active_c4_ROTH = 0U;
  chartInstance->c4_is_c4_ROTH = c4_IN_NO_ACTIVE_CHILD;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c4_moveRequest = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 1U, 1U,
                          chartInstance->c4_sfEvent, false);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c4_GT_active = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_GT_active, 24U, 1U, 1U,
                          chartInstance->c4_sfEvent, false);
  }
}

static void initialize_params_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_ROTH(SFc4_ROTHInstanceStruct
  *chartInstance)
{
  uint32_T c4_prevAniVal;
  c4_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c4_is_active_c4_ROTH == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_c4_ROTH == c4_IN_GTSP_Active) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_Forward) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_TurnLeft) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishLeftBlockedN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishLeftBlockedW) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishNormal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishBlockedW) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishBlockedN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_GTSP_Active == c4_IN_finishedGTSP) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_c4_ROTH == c4_IN_Idle) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c4_sfEvent);
  }

  _SFD_SET_ANIMATION(c4_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c4_ROTH(SFc4_ROTHInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  boolean_T c4_hoistedGlobal;
  boolean_T c4_u;
  const mxArray *c4_b_y = NULL;
  uint8_T c4_b_hoistedGlobal;
  uint8_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  uint8_T c4_c_hoistedGlobal;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  uint8_T c4_d_hoistedGlobal;
  uint8_T c4_d_u;
  const mxArray *c4_e_y = NULL;
  uint8_T c4_e_hoistedGlobal;
  uint8_T c4_e_u;
  const mxArray *c4_f_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(5, 1), false);
  c4_hoistedGlobal = *chartInstance->c4_GT_active;
  c4_u = c4_hoistedGlobal;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_b_hoistedGlobal = *chartInstance->c4_moveRequest;
  c4_b_u = c4_b_hoistedGlobal;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_c_hoistedGlobal = chartInstance->c4_is_active_c4_ROTH;
  c4_c_u = c4_c_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_d_hoistedGlobal = chartInstance->c4_is_c4_ROTH;
  c4_d_u = c4_d_hoistedGlobal;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 3, c4_e_y);
  c4_e_hoistedGlobal = chartInstance->c4_is_GTSP_Active;
  c4_e_u = c4_e_hoistedGlobal;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 4, c4_f_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance, const
  mxArray *c4_st)
{
  const mxArray *c4_u;
  c4_u = sf_mex_dup(c4_st);
  *chartInstance->c4_GT_active = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("GT_active", c4_u, 0)), "GT_active");
  *chartInstance->c4_moveRequest = c4_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("moveRequest", c4_u, 1)), "moveRequest");
  chartInstance->c4_is_active_c4_ROTH = c4_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c4_ROTH", c4_u, 2)),
    "is_active_c4_ROTH");
  chartInstance->c4_is_c4_ROTH = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("is_c4_ROTH", c4_u, 3)), "is_c4_ROTH");
  chartInstance->c4_is_GTSP_Active = c4_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_GTSP_Active", c4_u, 4)), "is_GTSP_Active");
  sf_mex_assign(&chartInstance->c4_setSimStateSideEffectsInfo,
                c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "setSimStateSideEffectsInfo", c4_u, 5)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c4_u);
  chartInstance->c4_doSetSimStateSideEffects = 1U;
  c4_update_debugger_state_c4_ROTH(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void c4_set_sim_state_side_effects_c4_ROTH(SFc4_ROTHInstanceStruct
  *chartInstance)
{
  if (chartInstance->c4_doSetSimStateSideEffects != 0) {
    chartInstance->c4_tp_GTSP_Active = (uint8_T)(chartInstance->c4_is_c4_ROTH ==
      c4_IN_GTSP_Active);
    chartInstance->c4_tp_Forward = (uint8_T)(chartInstance->c4_is_GTSP_Active ==
      c4_IN_Forward);
    chartInstance->c4_tp_TurnLeft = (uint8_T)(chartInstance->c4_is_GTSP_Active ==
      c4_IN_TurnLeft);
    chartInstance->c4_tp_finishedGTSP = (uint8_T)
      (chartInstance->c4_is_GTSP_Active == c4_IN_finishedGTSP);
    chartInstance->c4_tp_preFinishBlockedN = (uint8_T)
      (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishBlockedN);
    chartInstance->c4_tp_preFinishBlockedW = (uint8_T)
      (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishBlockedW);
    chartInstance->c4_tp_preFinishLeftBlockedN = (uint8_T)
      (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishLeftBlockedN);
    chartInstance->c4_tp_preFinishLeftBlockedW = (uint8_T)
      (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishLeftBlockedW);
    chartInstance->c4_tp_preFinishNormal = (uint8_T)
      (chartInstance->c4_is_GTSP_Active == c4_IN_preFinishNormal);
    chartInstance->c4_tp_Idle = (uint8_T)(chartInstance->c4_is_c4_ROTH ==
      c4_IN_Idle);
    chartInstance->c4_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c4_setSimStateSideEffectsInfo);
}

static void sf_gateway_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  boolean_T c4_out;
  real_T c4_d0;
  uint8_T c4_u0;
  c4_set_sim_state_side_effects_c4_ROTH(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_STOP, 22U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_MOVE_U_TURN, 21U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_MOVE_TURN_RIGHT, 20U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_MOVE_TURN_LEFT, 19U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_sensorView, 18U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_ROB_EAST, 17U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_ROB_WEST, 16U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_ROB_SOUTH, 15U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_ROB_NORTH, 14U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_CLEANED_RIGHT_BUSY, 13U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_BUSY_RIGHT_CLEANED, 12U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_CLEANED_RIGHT_CLEANED, 11U, 1U,
                        0U, chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_BUSY_RIGHT_BUSY, 10U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_EMPTY_RIGHT_EMPTY, 9U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_EMPTY_RIGHT_CLEANED, 8U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_EMPTY_RIGHT_BUSY, 7U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_CLEANED_RIGHT_EMPTY, 6U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_LEFT_BUSY_RIGHT_EMPTY, 5U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_FORWARD, 4U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_GTSP, 3U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_currentHeading, 2U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_currentRoutine, 1U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_pumperInterrupt_BOOL, 0U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  chartInstance->c4_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
  if (chartInstance->c4_is_active_c4_ROTH == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
    chartInstance->c4_is_active_c4_ROTH = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
    chartInstance->c4_is_c4_ROTH = c4_IN_Idle;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c4_sfEvent);
    chartInstance->c4_tp_Idle = 1U;
  } else {
    switch (chartInstance->c4_is_c4_ROTH) {
     case c4_IN_GTSP_Active:
      CV_CHART_EVAL(1, 0, 1);
      c4_GTSP_Active(chartInstance);
      break;

     case c4_IN_Idle:
      CV_CHART_EVAL(1, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   chartInstance->c4_sfEvent);
      c4_out = (CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1U, 0,
                  CV_RELATIONAL_EVAL(5U, 1U, 0, (real_T)
        *chartInstance->c4_currentRoutine, *chartInstance->c4_GTSP, -1, 0U,
        (real_T)*chartInstance->c4_currentRoutine == *chartInstance->c4_GTSP) !=
                  0U, chartInstance->c4_sfEvent)) != 0);
      if (c4_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_Idle = 0U;
        chartInstance->c4_is_c4_ROTH = c4_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c4_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 1U,
                     chartInstance->c4_sfEvent);
        *chartInstance->c4_GT_active = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_GT_active, 24U, 5U, 1U,
                              chartInstance->c4_sfEvent, false);
        chartInstance->c4_is_c4_ROTH = c4_IN_GTSP_Active;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_GTSP_Active = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
        chartInstance->c4_is_GTSP_Active = c4_IN_Forward;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_Forward = 1U;
        c4_d0 = *chartInstance->c4_FORWARD;
        if (c4_d0 < 256.0) {
          if (CV_SATURATION_EVAL(4, 1, 0, 1, c4_d0 >= 0.0)) {
            c4_u0 = (uint8_T)c4_d0;
          } else {
            c4_u0 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 1, 0, 0, c4_d0 >= 256.0)) {
          c4_u0 = MAX_uint8_T;
        } else {
          c4_u0 = 0U;
        }

        *chartInstance->c4_moveRequest = c4_u0;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 4U,
                              1U, chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                     chartInstance->c4_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c4_sfEvent);
      break;

     default:
      CV_CHART_EVAL(1, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c4_is_c4_ROTH = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ROTHMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  c4_init_sf_message_store_memory(chartInstance);
}

static void initSimStructsc4_ROTH(SFc4_ROTHInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_GTSP_Active(SFc4_ROTHInstanceStruct *chartInstance)
{
  boolean_T c4_out;
  boolean_T c4_b_out;
  boolean_T c4_c_out;
  boolean_T c4_d_out;
  boolean_T c4_e_out;
  boolean_T c4_f_out;
  real_T c4_d1;
  uint8_T c4_u1;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, chartInstance->c4_sfEvent);
  c4_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
              CV_RELATIONAL_EVAL(5U, 2U, 0, (real_T)
    *chartInstance->c4_currentRoutine, *chartInstance->c4_GTSP, -1, 1U, (real_T)*
    chartInstance->c4_currentRoutine != *chartInstance->c4_GTSP) != 0U,
              chartInstance->c4_sfEvent)) != 0);
  if (c4_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
    c4_exit_internal_GTSP_Active(chartInstance);
    chartInstance->c4_tp_GTSP_Active = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
    chartInstance->c4_is_c4_ROTH = c4_IN_Idle;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c4_sfEvent);
    chartInstance->c4_tp_Idle = 1U;
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
    switch (chartInstance->c4_is_GTSP_Active) {
     case c4_IN_Forward:
      CV_STATE_EVAL(0, 0, 1);
      c4_Forward(chartInstance);
      break;

     case c4_IN_TurnLeft:
      CV_STATE_EVAL(0, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                   chartInstance->c4_sfEvent);
      c4_b_out = (CV_TRANSITION_EVAL(6U, (int32_T)_SFD_CCP_CALL(6U, 0,
        CV_RELATIONAL_EVAL(5U, 6U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_WEST, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_WEST) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_TurnLeft = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
        chartInstance->c4_is_GTSP_Active = c4_IN_Forward;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_Forward = 1U;
        c4_d1 = *chartInstance->c4_FORWARD;
        if (c4_d1 < 256.0) {
          if (CV_SATURATION_EVAL(4, 1, 0, 1, c4_d1 >= 0.0)) {
            c4_u1 = (uint8_T)c4_d1;
          } else {
            c4_u1 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 1, 0, 0, c4_d1 >= 256.0)) {
          c4_u1 = MAX_uint8_T;
        } else {
          c4_u1 = 0U;
        }

        *chartInstance->c4_moveRequest = c4_u1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 4U,
                              1U, chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     chartInstance->c4_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_finishedGTSP:
      CV_STATE_EVAL(0, 0, 3);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                   chartInstance->c4_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_preFinishBlockedN:
      CV_STATE_EVAL(0, 0, 4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 17U,
                   chartInstance->c4_sfEvent);
      c4_c_out = (CV_TRANSITION_EVAL(17U, (int32_T)_SFD_CCP_CALL(17U, 0,
        CV_RELATIONAL_EVAL(5U, 17U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_NORTH, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_NORTH) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_preFinishBlockedN = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
        chartInstance->c4_is_GTSP_Active = c4_IN_finishedGTSP;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_finishedGTSP = 1U;
        *chartInstance->c4_GT_active = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_GT_active, 24U, 4U, 3U,
                              chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     chartInstance->c4_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_preFinishBlockedW:
      CV_STATE_EVAL(0, 0, 5);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c4_sfEvent);
      chartInstance->c4_tp_preFinishBlockedW = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
      chartInstance->c4_is_GTSP_Active = c4_IN_finishedGTSP;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
      chartInstance->c4_tp_finishedGTSP = 1U;
      *chartInstance->c4_GT_active = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_GT_active, 24U, 4U, 3U,
                            chartInstance->c4_sfEvent, false);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_preFinishLeftBlockedN:
      CV_STATE_EVAL(0, 0, 6);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 18U,
                   chartInstance->c4_sfEvent);
      c4_d_out = (CV_TRANSITION_EVAL(18U, (int32_T)_SFD_CCP_CALL(18U, 0,
        CV_RELATIONAL_EVAL(5U, 18U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_SOUTH, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_SOUTH) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_preFinishLeftBlockedN = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
        chartInstance->c4_is_GTSP_Active = c4_IN_finishedGTSP;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_finishedGTSP = 1U;
        *chartInstance->c4_GT_active = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_GT_active, 24U, 4U, 3U,
                              chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                     chartInstance->c4_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_preFinishLeftBlockedW:
      CV_STATE_EVAL(0, 0, 7);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                   chartInstance->c4_sfEvent);
      c4_e_out = (CV_TRANSITION_EVAL(19U, (int32_T)_SFD_CCP_CALL(19U, 0,
        CV_RELATIONAL_EVAL(5U, 19U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_NORTH, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_NORTH) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_preFinishLeftBlockedW = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
        chartInstance->c4_is_GTSP_Active = c4_IN_finishedGTSP;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_finishedGTSP = 1U;
        *chartInstance->c4_GT_active = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_GT_active, 24U, 4U, 3U,
                              chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                     chartInstance->c4_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_preFinishNormal:
      CV_STATE_EVAL(0, 0, 8);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                   chartInstance->c4_sfEvent);
      c4_f_out = (CV_TRANSITION_EVAL(15U, (int32_T)_SFD_CCP_CALL(15U, 0,
        CV_RELATIONAL_EVAL(5U, 15U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_SOUTH, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_SOUTH) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_preFinishNormal = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
        chartInstance->c4_is_GTSP_Active = c4_IN_finishedGTSP;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_finishedGTSP = 1U;
        *chartInstance->c4_GT_active = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_GT_active, 24U, 4U, 3U,
                              chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                     chartInstance->c4_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c4_sfEvent);
      break;

     default:
      CV_STATE_EVAL(0, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
}

static void c4_exit_internal_GTSP_Active(SFc4_ROTHInstanceStruct *chartInstance)
{
  switch (chartInstance->c4_is_GTSP_Active) {
   case c4_IN_Forward:
    CV_STATE_EVAL(0, 1, 1);
    chartInstance->c4_tp_Forward = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_TurnLeft:
    CV_STATE_EVAL(0, 1, 2);
    chartInstance->c4_tp_TurnLeft = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_finishedGTSP:
    CV_STATE_EVAL(0, 1, 3);
    chartInstance->c4_tp_finishedGTSP = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_preFinishBlockedN:
    CV_STATE_EVAL(0, 1, 4);
    chartInstance->c4_tp_preFinishBlockedN = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_preFinishBlockedW:
    CV_STATE_EVAL(0, 1, 5);
    chartInstance->c4_tp_preFinishBlockedW = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_preFinishLeftBlockedN:
    CV_STATE_EVAL(0, 1, 6);
    chartInstance->c4_tp_preFinishLeftBlockedN = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_preFinishLeftBlockedW:
    CV_STATE_EVAL(0, 1, 7);
    chartInstance->c4_tp_preFinishLeftBlockedW = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_preFinishNormal:
    CV_STATE_EVAL(0, 1, 8);
    chartInstance->c4_tp_preFinishNormal = 0U;
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 1, 0);
    chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
    break;
  }
}

static void c4_Forward(SFc4_ROTHInstanceStruct *chartInstance)
{
  boolean_T c4_out;
  boolean_T c4_temp;
  boolean_T c4_b_temp;
  boolean_T c4_b_out;
  boolean_T c4_c_temp;
  boolean_T c4_c_out;
  boolean_T c4_d_out;
  boolean_T c4_e_out;
  boolean_T c4_d_temp;
  boolean_T c4_f_out;
  real_T c4_d2;
  boolean_T c4_e_temp;
  boolean_T c4_g_out;
  real_T c4_d3;
  uint8_T c4_u2;
  boolean_T c4_f_temp;
  uint8_T c4_u3;
  real_T c4_d4;
  boolean_T c4_h_out;
  real_T c4_d5;
  uint8_T c4_u4;
  real_T c4_d6;
  boolean_T c4_i_out;
  uint8_T c4_u5;
  real_T c4_d7;
  uint8_T c4_u6;
  boolean_T c4_j_out;
  uint8_T c4_u7;
  real_T c4_d8;
  real_T c4_d9;
  real_T c4_d10;
  uint8_T c4_u8;
  real_T c4_d11;
  uint8_T c4_u9;
  uint8_T c4_u10;
  uint8_T c4_u11;
  real_T c4_d12;
  uint8_T c4_u12;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, chartInstance->c4_sfEvent);
  c4_out = (CV_TRANSITION_EVAL(4U, (int32_T)_SFD_CCP_CALL(4U, 0,
              *chartInstance->c4_pumperInterrupt_BOOL != 0U,
              chartInstance->c4_sfEvent)) != 0);
  guard1 = false;
  guard2 = false;
  guard3 = false;
  if (c4_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U, chartInstance->c4_sfEvent);
    c4_temp = (_SFD_CCP_CALL(5U, 0, CV_RELATIONAL_EVAL(5U, 5U, 0, (real_T)
      *chartInstance->c4_sensorView, *chartInstance->c4_LEFT_EMPTY_RIGHT_EMPTY,
      -1, 0U, (real_T)*chartInstance->c4_sensorView ==
      *chartInstance->c4_LEFT_EMPTY_RIGHT_EMPTY) != 0U,
                chartInstance->c4_sfEvent) != 0);
    if (!c4_temp) {
      c4_temp = (_SFD_CCP_CALL(5U, 1, CV_RELATIONAL_EVAL(5U, 5U, 1, (real_T)
        *chartInstance->c4_sensorView,
        *chartInstance->c4_LEFT_EMPTY_RIGHT_CLEANED, -1, 0U, (real_T)
        *chartInstance->c4_sensorView ==
        *chartInstance->c4_LEFT_EMPTY_RIGHT_CLEANED) != 0U,
                  chartInstance->c4_sfEvent) != 0);
    }

    c4_b_temp = c4_temp;
    if (!c4_b_temp) {
      c4_b_temp = (_SFD_CCP_CALL(5U, 2, CV_RELATIONAL_EVAL(5U, 5U, 2, (real_T)
        *chartInstance->c4_sensorView, *chartInstance->c4_LEFT_EMPTY_RIGHT_BUSY,
        -1, 0U, (real_T)*chartInstance->c4_sensorView ==
        *chartInstance->c4_LEFT_EMPTY_RIGHT_BUSY) != 0U,
        chartInstance->c4_sfEvent) != 0);
    }

    c4_b_out = (CV_TRANSITION_EVAL(5U, (int32_T)c4_b_temp) != 0);
    if (c4_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                   chartInstance->c4_sfEvent);
      c4_c_out = (CV_TRANSITION_EVAL(7U, (int32_T)_SFD_CCP_CALL(7U, 0,
        CV_RELATIONAL_EVAL(5U, 7U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_NORTH, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_NORTH) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_Forward = 0U;
        chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 4U,
                     chartInstance->c4_sfEvent);
        c4_d2 = *chartInstance->c4_STOP;
        if (c4_d2 < 256.0) {
          if (CV_SATURATION_EVAL(5, 4, 0, 1, c4_d2 >= 0.0)) {
            c4_u2 = (uint8_T)c4_d2;
          } else {
            c4_u2 = 0U;
          }
        } else if (CV_SATURATION_EVAL(5, 4, 0, 0, c4_d2 >= 256.0)) {
          c4_u2 = MAX_uint8_T;
        } else {
          c4_u2 = 0U;
        }

        *chartInstance->c4_moveRequest = c4_u2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 5U,
                              4U, chartInstance->c4_sfEvent, false);
        chartInstance->c4_is_GTSP_Active = c4_IN_TurnLeft;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_TurnLeft = 1U;
        c4_d6 = *chartInstance->c4_MOVE_TURN_LEFT;
        if (c4_d6 < 256.0) {
          if (CV_SATURATION_EVAL(4, 2, 0, 1, c4_d6 >= 0.0)) {
            c4_u6 = (uint8_T)c4_d6;
          } else {
            c4_u6 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 2, 0, 0, c4_d6 >= 256.0)) {
          c4_u6 = MAX_uint8_T;
        } else {
          c4_u6 = 0U;
        }

        *chartInstance->c4_moveRequest = c4_u6;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 4U,
                              2U, chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c4_sfEvent);
        c4_e_out = (CV_TRANSITION_EVAL(8U, (int32_T)_SFD_CCP_CALL(8U, 0,
          CV_RELATIONAL_EVAL(5U, 8U, 0, *chartInstance->c4_currentHeading,
                             *chartInstance->c4_ROB_WEST, -1, 0U,
                             *chartInstance->c4_currentHeading ==
                             *chartInstance->c4_ROB_WEST) != 0U,
          chartInstance->c4_sfEvent)) != 0);
        if (c4_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
          chartInstance->c4_tp_Forward = 0U;
          chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 4U,
                       chartInstance->c4_sfEvent);
          c4_d3 = *chartInstance->c4_STOP;
          if (c4_d3 < 256.0) {
            if (CV_SATURATION_EVAL(5, 4, 0, 1, c4_d3 >= 0.0)) {
              c4_u3 = (uint8_T)c4_d3;
            } else {
              c4_u3 = 0U;
            }
          } else if (CV_SATURATION_EVAL(5, 4, 0, 0, c4_d3 >= 256.0)) {
            c4_u3 = MAX_uint8_T;
          } else {
            c4_u3 = 0U;
          }

          *chartInstance->c4_moveRequest = c4_u3;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 5U,
                                4U, chartInstance->c4_sfEvent, false);
          chartInstance->c4_is_GTSP_Active = c4_IN_preFinishNormal;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
          chartInstance->c4_tp_preFinishNormal = 1U;
          c4_d7 = *chartInstance->c4_MOVE_TURN_LEFT;
          if (c4_d7 < 256.0) {
            if (CV_SATURATION_EVAL(4, 8, 0, 1, c4_d7 >= 0.0)) {
              c4_u7 = (uint8_T)c4_d7;
            } else {
              c4_u7 = 0U;
            }
          } else if (CV_SATURATION_EVAL(4, 8, 0, 0, c4_d7 >= 256.0)) {
            c4_u7 = MAX_uint8_T;
          } else {
            c4_u7 = 0U;
          }

          *chartInstance->c4_moveRequest = c4_u7;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 4U,
                                8U, chartInstance->c4_sfEvent, false);
        } else {
          guard3 = true;
        }
      }
    } else {
      guard3 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard3 == true) {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U, chartInstance->c4_sfEvent);
    c4_c_temp = (_SFD_CCP_CALL(9U, 0, CV_RELATIONAL_EVAL(5U, 9U, 0, (real_T)
      *chartInstance->c4_sensorView, *chartInstance->c4_LEFT_CLEANED_RIGHT_EMPTY,
      -1, 0U, (real_T)*chartInstance->c4_sensorView ==
      *chartInstance->c4_LEFT_CLEANED_RIGHT_EMPTY) != 0U,
      chartInstance->c4_sfEvent) != 0);
    if (!c4_c_temp) {
      c4_c_temp = (_SFD_CCP_CALL(9U, 1, CV_RELATIONAL_EVAL(5U, 9U, 1, (real_T)
        *chartInstance->c4_sensorView, *chartInstance->c4_LEFT_BUSY_RIGHT_EMPTY,
        -1, 0U, (real_T)*chartInstance->c4_sensorView ==
        *chartInstance->c4_LEFT_BUSY_RIGHT_EMPTY) != 0U,
        chartInstance->c4_sfEvent) != 0);
    }

    c4_d_out = (CV_TRANSITION_EVAL(9U, (int32_T)c4_c_temp) != 0);
    if (c4_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c4_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                   chartInstance->c4_sfEvent);
      c4_f_out = (CV_TRANSITION_EVAL(10U, (int32_T)_SFD_CCP_CALL(10U, 0,
        CV_RELATIONAL_EVAL(5U, 10U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_NORTH, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_NORTH) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_Forward = 0U;
        chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 4U,
                     chartInstance->c4_sfEvent);
        c4_d4 = *chartInstance->c4_STOP;
        if (c4_d4 < 256.0) {
          if (CV_SATURATION_EVAL(5, 4, 0, 1, c4_d4 >= 0.0)) {
            c4_u4 = (uint8_T)c4_d4;
          } else {
            c4_u4 = 0U;
          }
        } else if (CV_SATURATION_EVAL(5, 4, 0, 0, c4_d4 >= 256.0)) {
          c4_u4 = MAX_uint8_T;
        } else {
          c4_u4 = 0U;
        }

        *chartInstance->c4_moveRequest = c4_u4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 5U,
                              4U, chartInstance->c4_sfEvent, false);
        chartInstance->c4_is_GTSP_Active = c4_IN_preFinishLeftBlockedN;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_preFinishLeftBlockedN = 1U;
        c4_d8 = *chartInstance->c4_MOVE_U_TURN;
        if (c4_d8 < 256.0) {
          if (CV_SATURATION_EVAL(4, 6, 0, 1, c4_d8 >= 0.0)) {
            c4_u8 = (uint8_T)c4_d8;
          } else {
            c4_u8 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 6, 0, 0, c4_d8 >= 256.0)) {
          c4_u8 = MAX_uint8_T;
        } else {
          c4_u8 = 0U;
        }

        *chartInstance->c4_moveRequest = c4_u8;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 4U,
                              6U, chartInstance->c4_sfEvent, false);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                     chartInstance->c4_sfEvent);
        c4_g_out = (CV_TRANSITION_EVAL(11U, (int32_T)_SFD_CCP_CALL(11U, 0,
          CV_RELATIONAL_EVAL(5U, 11U, 0, *chartInstance->c4_currentHeading,
                             *chartInstance->c4_ROB_WEST, -1, 0U,
                             *chartInstance->c4_currentHeading ==
                             *chartInstance->c4_ROB_WEST) != 0U,
          chartInstance->c4_sfEvent)) != 0);
        if (c4_g_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c4_sfEvent);
          chartInstance->c4_tp_Forward = 0U;
          chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 4U,
                       chartInstance->c4_sfEvent);
          c4_d5 = *chartInstance->c4_STOP;
          if (c4_d5 < 256.0) {
            if (CV_SATURATION_EVAL(5, 4, 0, 1, c4_d5 >= 0.0)) {
              c4_u5 = (uint8_T)c4_d5;
            } else {
              c4_u5 = 0U;
            }
          } else if (CV_SATURATION_EVAL(5, 4, 0, 0, c4_d5 >= 256.0)) {
            c4_u5 = MAX_uint8_T;
          } else {
            c4_u5 = 0U;
          }

          *chartInstance->c4_moveRequest = c4_u5;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 5U,
                                4U, chartInstance->c4_sfEvent, false);
          chartInstance->c4_is_GTSP_Active = c4_IN_preFinishLeftBlockedW;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
          chartInstance->c4_tp_preFinishLeftBlockedW = 1U;
          c4_d10 = *chartInstance->c4_MOVE_TURN_RIGHT;
          if (c4_d10 < 256.0) {
            if (CV_SATURATION_EVAL(4, 7, 0, 1, c4_d10 >= 0.0)) {
              c4_u10 = (uint8_T)c4_d10;
            } else {
              c4_u10 = 0U;
            }
          } else if (CV_SATURATION_EVAL(4, 7, 0, 0, c4_d10 >= 256.0)) {
            c4_u10 = MAX_uint8_T;
          } else {
            c4_u10 = 0U;
          }

          *chartInstance->c4_moveRequest = c4_u10;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 4U,
                                7U, chartInstance->c4_sfEvent, false);
        } else {
          guard2 = true;
        }
      }
    } else {
      guard2 = true;
    }
  }

  if (guard2 == true) {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                 chartInstance->c4_sfEvent);
    c4_d_temp = (_SFD_CCP_CALL(12U, 0, CV_RELATIONAL_EVAL(5U, 12U, 0, (real_T)
      *chartInstance->c4_sensorView, *chartInstance->c4_LEFT_BUSY_RIGHT_BUSY, -1,
      0U, (real_T)*chartInstance->c4_sensorView ==
      *chartInstance->c4_LEFT_BUSY_RIGHT_BUSY) != 0U, chartInstance->c4_sfEvent)
                 != 0);
    if (!c4_d_temp) {
      c4_d_temp = (_SFD_CCP_CALL(12U, 1, CV_RELATIONAL_EVAL(5U, 12U, 1, (real_T)*
        chartInstance->c4_sensorView, *chartInstance->c4_LEFT_BUSY_RIGHT_CLEANED,
        -1, 0U, (real_T)*chartInstance->c4_sensorView ==
        *chartInstance->c4_LEFT_BUSY_RIGHT_CLEANED) != 0U,
        chartInstance->c4_sfEvent) != 0);
    }

    c4_e_temp = c4_d_temp;
    if (!c4_e_temp) {
      c4_e_temp = (_SFD_CCP_CALL(12U, 2, CV_RELATIONAL_EVAL(5U, 12U, 2, (real_T)*
        chartInstance->c4_sensorView, *chartInstance->c4_LEFT_CLEANED_RIGHT_BUSY,
        -1, 0U, (real_T)*chartInstance->c4_sensorView ==
        *chartInstance->c4_LEFT_CLEANED_RIGHT_BUSY) != 0U,
        chartInstance->c4_sfEvent) != 0);
    }

    c4_f_temp = c4_e_temp;
    if (!c4_f_temp) {
      c4_f_temp = (_SFD_CCP_CALL(12U, 3, CV_RELATIONAL_EVAL(5U, 12U, 3, (real_T)*
        chartInstance->c4_sensorView,
        *chartInstance->c4_LEFT_CLEANED_RIGHT_CLEANED, -1, 0U, (real_T)
        *chartInstance->c4_sensorView ==
        *chartInstance->c4_LEFT_CLEANED_RIGHT_CLEANED) != 0U,
        chartInstance->c4_sfEvent) != 0);
    }

    c4_h_out = (CV_TRANSITION_EVAL(12U, (int32_T)c4_f_temp) != 0);
    if (c4_h_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c4_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                   chartInstance->c4_sfEvent);
      c4_i_out = (CV_TRANSITION_EVAL(13U, (int32_T)_SFD_CCP_CALL(13U, 0,
        CV_RELATIONAL_EVAL(5U, 13U, 0, *chartInstance->c4_currentHeading,
                           *chartInstance->c4_ROB_WEST, -1, 0U,
                           *chartInstance->c4_currentHeading ==
                           *chartInstance->c4_ROB_WEST) != 0U,
        chartInstance->c4_sfEvent)) != 0);
      if (c4_i_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_Forward = 0U;
        chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 4U,
                     chartInstance->c4_sfEvent);
        c4_d9 = *chartInstance->c4_STOP;
        if (c4_d9 < 256.0) {
          if (CV_SATURATION_EVAL(5, 4, 0, 1, c4_d9 >= 0.0)) {
            c4_u9 = (uint8_T)c4_d9;
          } else {
            c4_u9 = 0U;
          }
        } else if (CV_SATURATION_EVAL(5, 4, 0, 0, c4_d9 >= 256.0)) {
          c4_u9 = MAX_uint8_T;
        } else {
          c4_u9 = 0U;
        }

        *chartInstance->c4_moveRequest = c4_u9;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 5U,
                              4U, chartInstance->c4_sfEvent, false);
        chartInstance->c4_is_GTSP_Active = c4_IN_preFinishBlockedW;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
        chartInstance->c4_tp_preFinishBlockedW = 1U;
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                     chartInstance->c4_sfEvent);
        c4_j_out = (CV_TRANSITION_EVAL(14U, (int32_T)_SFD_CCP_CALL(14U, 0,
          CV_RELATIONAL_EVAL(5U, 14U, 0, *chartInstance->c4_currentHeading,
                             *chartInstance->c4_ROB_NORTH, -1, 0U,
                             *chartInstance->c4_currentHeading ==
                             *chartInstance->c4_ROB_NORTH) != 0U,
          chartInstance->c4_sfEvent)) != 0);
        if (c4_j_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c4_sfEvent);
          chartInstance->c4_tp_Forward = 0U;
          chartInstance->c4_is_GTSP_Active = c4_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_TRANS_ACTION_TAG, 4U,
                       chartInstance->c4_sfEvent);
          c4_d11 = *chartInstance->c4_STOP;
          if (c4_d11 < 256.0) {
            if (CV_SATURATION_EVAL(5, 4, 0, 1, c4_d11 >= 0.0)) {
              c4_u11 = (uint8_T)c4_d11;
            } else {
              c4_u11 = 0U;
            }
          } else if (CV_SATURATION_EVAL(5, 4, 0, 0, c4_d11 >= 256.0)) {
            c4_u11 = MAX_uint8_T;
          } else {
            c4_u11 = 0U;
          }

          *chartInstance->c4_moveRequest = c4_u11;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 5U,
                                4U, chartInstance->c4_sfEvent, false);
          chartInstance->c4_is_GTSP_Active = c4_IN_preFinishBlockedN;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
          chartInstance->c4_tp_preFinishBlockedN = 1U;
          c4_d12 = *chartInstance->c4_MOVE_U_TURN;
          if (c4_d12 < 256.0) {
            if (CV_SATURATION_EVAL(4, 4, 0, 1, c4_d12 >= 0.0)) {
              c4_u12 = (uint8_T)c4_d12;
            } else {
              c4_u12 = 0U;
            }
          } else if (CV_SATURATION_EVAL(4, 4, 0, 0, c4_d12 >= 256.0)) {
            c4_u12 = MAX_uint8_T;
          } else {
            c4_u12 = 0U;
          }

          *chartInstance->c4_moveRequest = c4_u12;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_moveRequest, 23U, 4U,
                                4U, chartInstance->c4_sfEvent, false);
        } else {
          guard1 = true;
        }
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1 == true) {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

const mxArray *sf_c4_ROTH_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c4_nameCaptureInfo;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance, const
  mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i0, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent), &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(uint8_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static uint8_T c4_b_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_b_tp_GTSP_Active, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_tp_GTSP_Active),
    &c4_thisId);
  sf_mex_destroy(&c4_b_tp_GTSP_Active);
  return c4_y;
}

static uint8_T c4_c_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u13;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u13, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u13;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_tp_GTSP_Active;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y;
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)chartInstanceVoid;
  c4_b_tp_GTSP_Active = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_tp_GTSP_Active),
    &c4_thisId);
  sf_mex_destroy(&c4_b_tp_GTSP_Active);
  *(uint8_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  boolean_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(boolean_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static boolean_T c4_d_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_b_GT_active, const char_T *c4_identifier)
{
  boolean_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_GT_active),
    &c4_thisId);
  sf_mex_destroy(&c4_b_GT_active);
  return c4_y;
}

static boolean_T c4_e_emlrt_marshallIn(SFc4_ROTHInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  boolean_T c4_y;
  boolean_T c4_b0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_b0, 1, 11, 0U, 0, 0U, 0);
  c4_y = c4_b0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_GT_active;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  boolean_T c4_y;
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)chartInstanceVoid;
  c4_b_GT_active = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_GT_active),
    &c4_thisId);
  sf_mex_destroy(&c4_b_GT_active);
  *(boolean_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_f_emlrt_marshallIn(SFc4_ROTHInstanceStruct
  *chartInstance, const mxArray *c4_b_setSimStateSideEffectsInfo, const char_T
  *c4_identifier)
{
  const mxArray *c4_y = NULL;
  emlrtMsgIdentifier c4_thisId;
  c4_y = NULL;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  sf_mex_assign(&c4_y, c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_setSimStateSideEffectsInfo), &c4_thisId), false);
  sf_mex_destroy(&c4_b_setSimStateSideEffectsInfo);
  return c4_y;
}

static const mxArray *c4_g_emlrt_marshallIn(SFc4_ROTHInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  (void)c4_parentId;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_duplicatearraysafe(&c4_u), false);
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static const mxArray *sf_get_hover_data_for_msg(SFc4_ROTHInstanceStruct
  *chartInstance, int32_T c4_ssid)
{
  (void)chartInstance;
  (void)c4_ssid;
  return NULL;
}

static void c4_init_sf_message_store_memory(SFc4_ROTHInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_dsm_address_info(SFc4_ROTHInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc4_ROTHInstanceStruct *chartInstance)
{
  chartInstance->c4_pumperInterrupt_BOOL = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 0);
  chartInstance->c4_currentRoutine = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_currentHeading = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_GTSP = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c4_FORWARD = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c4_LEFT_BUSY_RIGHT_EMPTY = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 5);
  chartInstance->c4_LEFT_CLEANED_RIGHT_EMPTY = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 6);
  chartInstance->c4_LEFT_EMPTY_RIGHT_BUSY = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 7);
  chartInstance->c4_LEFT_EMPTY_RIGHT_CLEANED = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 8);
  chartInstance->c4_LEFT_EMPTY_RIGHT_EMPTY = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 9);
  chartInstance->c4_LEFT_BUSY_RIGHT_BUSY = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 10);
  chartInstance->c4_LEFT_CLEANED_RIGHT_CLEANED = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 11);
  chartInstance->c4_LEFT_BUSY_RIGHT_CLEANED = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 12);
  chartInstance->c4_LEFT_CLEANED_RIGHT_BUSY = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 13);
  chartInstance->c4_ROB_NORTH = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 14);
  chartInstance->c4_ROB_SOUTH = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 15);
  chartInstance->c4_ROB_WEST = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c4_ROB_EAST = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 17);
  chartInstance->c4_sensorView = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 18);
  chartInstance->c4_moveRequest = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_MOVE_TURN_LEFT = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 19);
  chartInstance->c4_MOVE_TURN_RIGHT = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 20);
  chartInstance->c4_MOVE_U_TURN = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 21);
  chartInstance->c4_GT_active = (boolean_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_STOP = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 22);
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

void sf_c4_ROTH_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2914744039U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3783877287U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2515163675U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(23600391U);
}

mxArray* sf_c4_ROTH_get_post_codegen_info(void);
mxArray *sf_c4_ROTH_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Yn5zg2lEgxmcY7DWELKYFC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,23,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,20,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,20,"type",mxType);
    }

    mxSetField(mxData,20,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,21,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,21,"type",mxType);
    }

    mxSetField(mxData,21,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,22,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,22,"type",mxType);
    }

    mxSetField(mxData,22,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c4_ROTH_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_ROTH_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_ROTH_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c4_ROTH_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c4_ROTH_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c4_ROTH(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[57],T\"GT_active\",},{M[1],M[58],T\"moveRequest\",},{M[8],M[0],T\"is_active_c4_ROTH\",},{M[9],M[0],T\"is_c4_ROTH\",},{M[9],M[7],T\"is_GTSP_Active\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_ROTH_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc4_ROTHInstanceStruct *) chartInstance,
    msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_ROTHInstanceStruct *chartInstance = (SFc4_ROTHInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ROTHMachineNumber_,
           4,
           10,
           20,
           0,
           25,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_ROTHMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ROTHMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ROTHMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"pumperInterrupt_BOOL");
          _SFD_SET_DATA_PROPS(1,1,1,0,"currentRoutine");
          _SFD_SET_DATA_PROPS(2,1,1,0,"currentHeading");
          _SFD_SET_DATA_PROPS(3,1,1,0,"GTSP");
          _SFD_SET_DATA_PROPS(4,1,1,0,"FORWARD");
          _SFD_SET_DATA_PROPS(5,1,1,0,"LEFT_BUSY_RIGHT_EMPTY");
          _SFD_SET_DATA_PROPS(6,1,1,0,"LEFT_CLEANED_RIGHT_EMPTY");
          _SFD_SET_DATA_PROPS(7,1,1,0,"LEFT_EMPTY_RIGHT_BUSY");
          _SFD_SET_DATA_PROPS(8,1,1,0,"LEFT_EMPTY_RIGHT_CLEANED");
          _SFD_SET_DATA_PROPS(9,1,1,0,"LEFT_EMPTY_RIGHT_EMPTY");
          _SFD_SET_DATA_PROPS(10,1,1,0,"LEFT_BUSY_RIGHT_BUSY");
          _SFD_SET_DATA_PROPS(11,1,1,0,"LEFT_CLEANED_RIGHT_CLEANED");
          _SFD_SET_DATA_PROPS(12,1,1,0,"LEFT_BUSY_RIGHT_CLEANED");
          _SFD_SET_DATA_PROPS(13,1,1,0,"LEFT_CLEANED_RIGHT_BUSY");
          _SFD_SET_DATA_PROPS(14,1,1,0,"ROB_NORTH");
          _SFD_SET_DATA_PROPS(15,1,1,0,"ROB_SOUTH");
          _SFD_SET_DATA_PROPS(16,1,1,0,"ROB_WEST");
          _SFD_SET_DATA_PROPS(17,1,1,0,"ROB_EAST");
          _SFD_SET_DATA_PROPS(18,1,1,0,"sensorView");
          _SFD_SET_DATA_PROPS(19,1,1,0,"MOVE_TURN_LEFT");
          _SFD_SET_DATA_PROPS(20,1,1,0,"MOVE_TURN_RIGHT");
          _SFD_SET_DATA_PROPS(21,1,1,0,"MOVE_U_TURN");
          _SFD_SET_DATA_PROPS(22,1,1,0,"STOP");
          _SFD_SET_DATA_PROPS(23,2,0,1,"moveRequest");
          _SFD_SET_DATA_PROPS(24,2,0,1,"GT_active");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,9);
          _SFD_ST_SUBSTATE_COUNT(0,8);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,2);
          _SFD_ST_SUBSTATE_INDEX(0,2,3);
          _SFD_ST_SUBSTATE_INDEX(0,3,4);
          _SFD_ST_SUBSTATE_INDEX(0,4,5);
          _SFD_ST_SUBSTATE_INDEX(0,5,6);
          _SFD_ST_SUBSTATE_INDEX(0,6,7);
          _SFD_ST_SUBSTATE_INDEX(0,7,8);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,8,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 29 };

          static unsigned int sEndSaturateMap[] = { 36 };

          _SFD_CV_INIT_STATE_SATURATION(1,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 30 };

          static unsigned int sEndSaturateMap[] = { 44 };

          _SFD_CV_INIT_STATE_SATURATION(2,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 39 };

          static unsigned int sEndSaturateMap[] = { 50 };

          _SFD_CV_INIT_STATE_SATURATION(4,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 43 };

          static unsigned int sEndSaturateMap[] = { 54 };

          _SFD_CV_INIT_STATE_SATURATION(6,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 43 };

          static unsigned int sEndSaturateMap[] = { 58 };

          _SFD_CV_INIT_STATE_SATURATION(7,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 37 };

          static unsigned int sEndSaturateMap[] = { 51 };

          _SFD_CV_INIT_STATE_SATURATION(8,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 23 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 23 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(4,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 38 };

          static unsigned int sEndSaturateMap[] = { 42 };

          _SFD_CV_INIT_TRANSITION_SATURATION(4,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 47, 94 };

          static unsigned int sEndGuardMap[] = { 38, 85, 129 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(5,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 47, 94 };

          static unsigned int sEndRelationalopMap[] = { 38, 85, 129 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 49 };

          static unsigned int sEndGuardMap[] = { 40, 84 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(9,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 49 };

          static unsigned int sEndRelationalopMap[] = { 40, 84 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(9,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 45, 91, 137 };

          static unsigned int sEndGuardMap[] = { 36, 82, 128, 177 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2 };

          _SFD_CV_INIT_TRANS(12,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 45, 91, 137 };

          static unsigned int sEndRelationalopMap[] = { 36, 82, 128, 177 };

          static int sRelationalopEps[] = { -1, -1, -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(12,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(7,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(11,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(10,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(13,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(13,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(14,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(18,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(18,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(19,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(19,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(15,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(15,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(17,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(17,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)c4_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_d_sf_marshallOut,(MexInFcnForType)c4_c_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ROTHMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_ROTHInstanceStruct *chartInstance = (SFc4_ROTHInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c4_pumperInterrupt_BOOL);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c4_currentRoutine);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c4_currentHeading);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c4_GTSP);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c4_FORWARD);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c4_LEFT_BUSY_RIGHT_EMPTY);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c4_LEFT_CLEANED_RIGHT_EMPTY);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c4_LEFT_EMPTY_RIGHT_BUSY);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c4_LEFT_EMPTY_RIGHT_CLEANED);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c4_LEFT_EMPTY_RIGHT_EMPTY);
        _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c4_LEFT_BUSY_RIGHT_BUSY);
        _SFD_SET_DATA_VALUE_PTR(11U,
          chartInstance->c4_LEFT_CLEANED_RIGHT_CLEANED);
        _SFD_SET_DATA_VALUE_PTR(12U, chartInstance->c4_LEFT_BUSY_RIGHT_CLEANED);
        _SFD_SET_DATA_VALUE_PTR(13U, chartInstance->c4_LEFT_CLEANED_RIGHT_BUSY);
        _SFD_SET_DATA_VALUE_PTR(14U, chartInstance->c4_ROB_NORTH);
        _SFD_SET_DATA_VALUE_PTR(15U, chartInstance->c4_ROB_SOUTH);
        _SFD_SET_DATA_VALUE_PTR(16U, chartInstance->c4_ROB_WEST);
        _SFD_SET_DATA_VALUE_PTR(17U, chartInstance->c4_ROB_EAST);
        _SFD_SET_DATA_VALUE_PTR(18U, chartInstance->c4_sensorView);
        _SFD_SET_DATA_VALUE_PTR(23U, chartInstance->c4_moveRequest);
        _SFD_SET_DATA_VALUE_PTR(19U, chartInstance->c4_MOVE_TURN_LEFT);
        _SFD_SET_DATA_VALUE_PTR(20U, chartInstance->c4_MOVE_TURN_RIGHT);
        _SFD_SET_DATA_VALUE_PTR(21U, chartInstance->c4_MOVE_U_TURN);
        _SFD_SET_DATA_VALUE_PTR(24U, chartInstance->c4_GT_active);
        _SFD_SET_DATA_VALUE_PTR(22U, chartInstance->c4_STOP);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "stf0xXIDgbw9gEvtEewlW8C";
}

static void sf_opaque_initialize_c4_ROTH(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_ROTHInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c4_ROTH((SFc4_ROTHInstanceStruct*) chartInstanceVar);
  initialize_c4_ROTH((SFc4_ROTHInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_ROTH(void *chartInstanceVar)
{
  enable_c4_ROTH((SFc4_ROTHInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_ROTH(void *chartInstanceVar)
{
  disable_c4_ROTH((SFc4_ROTHInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_ROTH(void *chartInstanceVar)
{
  sf_gateway_c4_ROTH((SFc4_ROTHInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c4_ROTH(SimStruct* S)
{
  return get_sim_state_c4_ROTH((SFc4_ROTHInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c4_ROTH(SimStruct* S, const mxArray *st)
{
  set_sim_state_c4_ROTH((SFc4_ROTHInstanceStruct*)sf_get_chart_instance_ptr(S),
                        st);
}

static void sf_opaque_terminate_c4_ROTH(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_ROTHInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ROTH_optimization_info();
    }

    finalize_c4_ROTH((SFc4_ROTHInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_ROTH((SFc4_ROTHInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_ROTH(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_ROTH((SFc4_ROTHInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c4_ROTH(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ROTH_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 4);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 15, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 16, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 17, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 18, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 19, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 20, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 21, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 22, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,23);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 23; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2695247560U));
  ssSetChecksum1(S,(59641475U));
  ssSetChecksum2(S,(1689195911U));
  ssSetChecksum3(S,(3278477898U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_ROTH(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c4_ROTH(SimStruct *S)
{
  SFc4_ROTHInstanceStruct *chartInstance;
  chartInstance = (SFc4_ROTHInstanceStruct *)utMalloc(sizeof
    (SFc4_ROTHInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc4_ROTHInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_ROTH;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_ROTH;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_ROTH;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_ROTH;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_ROTH;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_ROTH;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_ROTH;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_ROTH;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_ROTH;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_ROTH;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_ROTH;
  chartInstance->chartInfo.callGetHoverDataForMsg =
    sf_opaque_get_hover_data_for_msg;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c4_ROTH(chartInstance);
}

void c4_ROTH_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_ROTH(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_ROTH(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_ROTH(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_ROTH_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
