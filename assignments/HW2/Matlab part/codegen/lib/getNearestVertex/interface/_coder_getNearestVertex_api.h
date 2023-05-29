/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_getNearestVertex_api.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Feb-2022 21:23:15
 */

#ifndef _CODER_GETNEARESTVERTEX_API_H
#define _CODER_GETNEARESTVERTEX_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_getNearestVertex_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void getNearestVertex(char_T mbvq_data[], int32_T mbvq_size[2], real_T R,
  real_T G, real_T B, char_T vertex_data[], int32_T vertex_size[2]);
extern void getNearestVertex_api(const mxArray * const prhs[4], int32_T nlhs,
  const mxArray *plhs[1]);
extern void getNearestVertex_atexit(void);
extern void getNearestVertex_initialize(void);
extern void getNearestVertex_terminate(void);
extern void getNearestVertex_xil_terminate(void);

#endif

/*
 * File trailer for _coder_getNearestVertex_api.h
 *
 * [EOF]
 */
