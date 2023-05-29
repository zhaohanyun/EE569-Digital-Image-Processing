/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_getNearestVertex_api.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Feb-2022 21:23:15
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_getNearestVertex_api.h"
#include "_coder_getNearestVertex_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131466U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "getNearestVertex",                  /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y_data[], int32_T y_size[2]);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R, const
  char_T *identifier);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret_data[], int32_T ret_size[2]);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *mbvq, const
  char_T *identifier, char_T y_data[], int32_T y_size[2]);
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const char_T
  u_data[], const int32_T u_size[2]);
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char_T y_data[]
 *                int32_T y_size[2]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y_data[], int32_T y_size[2])
{
  e_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *R
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(R), &thisId);
  emlrtDestroyArray(&R);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char_T ret_data[]
 *                int32_T ret_size[2]
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret_data[], int32_T ret_size[2])
{
  static const int32_T dims[2] = { 1, 4 };

  const boolean_T bv0[2] = { false, true };

  int32_T iv0[2];
  emlrtCheckVsBuiltInR2012b(sp, (const emlrtMsgIdentifier *)msgId, src, "char",
    false, 2U, *(int32_T (*)[2])&dims[0], (boolean_T *)&bv0[0], iv0);
  ret_size[0] = iv0[0];
  ret_size[1] = iv0[1];
  emlrtImportArrayR2015b(sp, src, (void *)ret_data, 1, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *mbvq
 *                const char_T *identifier
 *                char_T y_data[]
 *                int32_T y_size[2]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *mbvq, const
  char_T *identifier, char_T y_data[], int32_T y_size[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(mbvq), &thisId, y_data, y_size);
  emlrtDestroyArray(&mbvq);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char_T u_data[]
 *                const int32_T u_size[2]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const char_T
  u_data[], const int32_T u_size[2])
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateCharArray(2, u_size);
  emlrtInitCharArrayR2013a(sp, u_size[1], m0, (char_T *)&u_data[0]);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, (const emlrtMsgIdentifier *)msgId, src, "double",
    false, 0U, (int32_T *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[4]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void getNearestVertex_api(const mxArray * const prhs[4], int32_T nlhs, const
  mxArray *plhs[1])
{
  char_T mbvq_data[4];
  int32_T mbvq_size[2];
  real_T R;
  real_T G;
  real_T B;
  char_T vertex_data[7];
  int32_T vertex_size[2];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "mbvq", mbvq_data, mbvq_size);
  R = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "R");
  G = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "G");
  B = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "B");

  /* Invoke the target function */
  getNearestVertex(mbvq_data, mbvq_size, R, G, B, vertex_data, vertex_size);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, vertex_data, vertex_size);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getNearestVertex_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  getNearestVertex_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getNearestVertex_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getNearestVertex_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_getNearestVertex_api.c
 *
 * [EOF]
 */
