#ifndef __c2_AssemControl3_h__
#define __c2_AssemControl3_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_c2_ResolvedFunctionInfo
#define typedef_c2_ResolvedFunctionInfo

typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c2_ResolvedFunctionInfo;

#endif                                 /*typedef_c2_ResolvedFunctionInfo*/

#ifndef typedef_SFc2_AssemControl3InstanceStruct
#define typedef_SFc2_AssemControl3InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_AssemControl3;
  real_T c2_v;
  boolean_T c2_v_not_empty;
  real_T c2_qd[20];
  boolean_T c2_qd_not_empty;
  real_T c2_dqd[15];
  boolean_T c2_dqd_not_empty;
  real_T c2_ddqd[20];
  boolean_T c2_ddqd_not_empty;
  real_T c2_td[3];
  boolean_T c2_td_not_empty;
  real_T c2_dqdNEW[5];
  boolean_T c2_dqdNEW_not_empty;
  real_T c2_state[10];
  boolean_T c2_state_not_empty;
} SFc2_AssemControl3InstanceStruct;

#endif                                 /*typedef_SFc2_AssemControl3InstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_AssemControl3_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_AssemControl3_get_check_sum(mxArray *plhs[]);
extern void c2_AssemControl3_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
