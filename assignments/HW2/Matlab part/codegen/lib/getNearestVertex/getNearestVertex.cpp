//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: getNearestVertex.cpp
//
// MATLAB Coder version            : 4.0
// C/C++ source code generated on  : 20-Feb-2022 21:23:15
//

// Include Files
#include "rt_nonfinite.h"
#include "getNearestVertex.h"

// Function Definitions

//
// getNearestVertex: find nearst vertex in the given MBVQ for a target pixel
//
//  INPUT:
//  mbvq (char array): the mbvq the target pixel is related to
//  R, G, B (range:0~1): the R, G, B channel value of the target pixel
//
//  OUPUT:
//  vertex (char array): the name of the closest vertex
//
//  Ref: "Color Diffusion: Error-Diffusion for Color Halftones
//  by Shaked, Arad, Fitzhugh, and Sobel -- HP Labs
//  Hewlett-Packard Laboratories TR 96-128
//  and Electronic Imaging, Proc. SPIE 3648, 1999
//  Adapted from Halftoning Toolbox Version 1.2 released July 2005 (Univ. of Texas)
// Arguments    : const char mbvq_data[]
//                const int mbvq_size[2]
//                double R
//                double G
//                double B
//                char vertex_data[]
//                int vertex_size[2]
// Return Type  : void
//
void getNearestVertex(const char mbvq_data[], const int [2], double R, double G,
                      double B, char vertex_data[], int vertex_size[2])
{
  int k;
  boolean_T y;
  static const char cv0[4] = { 'f', 'u', 'c', 'k' };

  boolean_T x[4];
  static const char cv1[4] = { 'C', 'M', 'Y', 'W' };

  boolean_T exitg1;
  static const char cv2[4] = { 'M', 'Y', 'G', 'C' };

  static const char cv3[5] = { 'w', 'h', 'i', 't', 'e' };

  static const char cv4[6] = { 'y', 'e', 'l', 'l', 'o', 'w' };

  static const char cv5[7] = { 'm', 'a', 'g', 'e', 'n', 't', 'a' };

  static const char cv6[4] = { 'c', 'y', 'a', 'n' };

  static const char cv7[4] = { 'R', 'G', 'M', 'Y' };

  static const char cv8[5] = { 'g', 'r', 'e', 'e', 'n' };

  static const char cv9[4] = { 'K', 'R', 'G', 'B' };

  static const char cv10[3] = { 'r', 'e', 'd' };

  static const char cv11[4] = { 'R', 'G', 'B', 'M' };

  static const char cv12[5] = { 'b', 'l', 'a', 'c', 'k' };

  static const char cv13[4] = { 'b', 'l', 'u', 'e' };

  static const char cv14[4] = { 'C', 'M', 'G', 'B' };

  vertex_size[0] = 1;
  vertex_size[1] = 4;

  //  No.1 for CMYW
  for (k = 0; k < 4; k++) {
    vertex_data[k] = cv0[k];
    x[k] = (mbvq_data[k] == cv1[k]);
  }

  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 5)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    vertex_size[0] = 1;
    vertex_size[1] = 5;
    for (k = 0; k < 5; k++) {
      vertex_data[k] = cv3[k];
    }

    if ((B < 0.5) && (B <= R) && (B <= G)) {
      vertex_size[0] = 1;
      vertex_size[1] = 6;
      for (k = 0; k < 6; k++) {
        vertex_data[k] = cv4[k];
      }
    }

    if ((G < 0.5) && (G <= B) && (G <= R)) {
      vertex_size[0] = 1;
      vertex_size[1] = 7;
      for (k = 0; k < 7; k++) {
        vertex_data[k] = cv5[k];
      }
    }

    if ((R < 0.5) && (R <= B) && (R <= G)) {
      vertex_size[0] = 1;
      vertex_size[1] = 4;
      for (k = 0; k < 4; k++) {
        vertex_data[k] = cv6[k];
      }
    }
  }

  //  No.2 for MYGC
  for (k = 0; k < 4; k++) {
    x[k] = (mbvq_data[k] == cv2[k]);
  }

  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 5)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    vertex_size[0] = 1;
    vertex_size[1] = 7;
    for (k = 0; k < 7; k++) {
      vertex_data[k] = cv5[k];
    }

    if ((G >= B) && (R >= B)) {
      if (R >= 0.5) {
        vertex_size[0] = 1;
        vertex_size[1] = 6;
        for (k = 0; k < 6; k++) {
          vertex_data[k] = cv4[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 5;
        for (k = 0; k < 5; k++) {
          vertex_data[k] = cv8[k];
        }
      }
    }

    if ((G >= R) && (B >= R)) {
      if (B >= 0.5) {
        vertex_size[0] = 1;
        vertex_size[1] = 4;
        for (k = 0; k < 4; k++) {
          vertex_data[k] = cv6[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 5;
        for (k = 0; k < 5; k++) {
          vertex_data[k] = cv8[k];
        }
      }
    }
  }

  //  No.3 for RGMY
  for (k = 0; k < 4; k++) {
    x[k] = (mbvq_data[k] == cv7[k]);
  }

  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 5)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    if (B > 0.5) {
      if (R > 0.5) {
        if (B >= G) {
          vertex_size[0] = 1;
          vertex_size[1] = 7;
          for (k = 0; k < 7; k++) {
            vertex_data[k] = cv5[k];
          }
        } else {
          vertex_size[0] = 1;
          vertex_size[1] = 6;
          for (k = 0; k < 6; k++) {
            vertex_data[k] = cv4[k];
          }
        }
      } else if (G > B + R) {
        vertex_size[0] = 1;
        vertex_size[1] = 5;
        for (k = 0; k < 5; k++) {
          vertex_data[k] = cv8[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 7;
        for (k = 0; k < 7; k++) {
          vertex_data[k] = cv5[k];
        }
      }
    } else if (R >= 0.5) {
      if (G >= 0.5) {
        vertex_size[0] = 1;
        vertex_size[1] = 6;
        for (k = 0; k < 6; k++) {
          vertex_data[k] = cv4[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 3;
        for (k = 0; k < 3; k++) {
          vertex_data[k] = cv10[k];
        }
      }
    } else if (R >= G) {
      vertex_size[0] = 1;
      vertex_size[1] = 3;
      for (k = 0; k < 3; k++) {
        vertex_data[k] = cv10[k];
      }
    } else {
      vertex_size[0] = 1;
      vertex_size[1] = 5;
      for (k = 0; k < 5; k++) {
        vertex_data[k] = cv8[k];
      }
    }
  }

  //  No.4 for KRGB
  for (k = 0; k < 4; k++) {
    x[k] = (mbvq_data[k] == cv9[k]);
  }

  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 5)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    vertex_size[0] = 1;
    vertex_size[1] = 5;
    for (k = 0; k < 5; k++) {
      vertex_data[k] = cv12[k];
    }

    if ((B > 0.5) && (B >= R) && (B >= G)) {
      vertex_size[0] = 1;
      vertex_size[1] = 4;
      for (k = 0; k < 4; k++) {
        vertex_data[k] = cv13[k];
      }
    }

    if ((G > 0.5) && (G >= B) && (G >= R)) {
      vertex_size[0] = 1;
      vertex_size[1] = 5;
      for (k = 0; k < 5; k++) {
        vertex_data[k] = cv8[k];
      }
    }

    if ((R > 0.5) && (R >= B) && (R >= G)) {
      vertex_size[0] = 1;
      vertex_size[1] = 3;
      for (k = 0; k < 3; k++) {
        vertex_data[k] = cv10[k];
      }
    }
  }

  //  No.5 for RGBM
  for (k = 0; k < 4; k++) {
    x[k] = (mbvq_data[k] == cv11[k]);
  }

  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 5)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    vertex_size[0] = 1;
    vertex_size[1] = 5;
    for (k = 0; k < 5; k++) {
      vertex_data[k] = cv8[k];
    }

    if ((R > G) && (R >= B)) {
      if (B < 0.5) {
        vertex_size[0] = 1;
        vertex_size[1] = 3;
        for (k = 0; k < 3; k++) {
          vertex_data[k] = cv10[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 7;
        for (k = 0; k < 7; k++) {
          vertex_data[k] = cv5[k];
        }
      }
    }

    if ((B > G) && (B >= R)) {
      if (R < 0.5) {
        vertex_size[0] = 1;
        vertex_size[1] = 4;
        for (k = 0; k < 4; k++) {
          vertex_data[k] = cv13[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 7;
        for (k = 0; k < 7; k++) {
          vertex_data[k] = cv5[k];
        }
      }
    }
  }

  //  No.6 for CMGB
  for (k = 0; k < 4; k++) {
    x[k] = (mbvq_data[k] == cv14[k]);
  }

  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 5)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    if (B > 0.5) {
      if (R > 0.5) {
        if (G >= R) {
          vertex_size[0] = 1;
          vertex_size[1] = 4;
          for (k = 0; k < 4; k++) {
            vertex_data[k] = cv6[k];
          }
        } else {
          vertex_size[0] = 1;
          vertex_size[1] = 7;
          for (k = 0; k < 7; k++) {
            vertex_data[k] = cv5[k];
          }
        }
      } else if (G > 0.5) {
        vertex_size[0] = 1;
        vertex_size[1] = 4;
        for (k = 0; k < 4; k++) {
          vertex_data[k] = cv6[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 4;
        for (k = 0; k < 4; k++) {
          vertex_data[k] = cv13[k];
        }
      }
    } else if (R > 0.5) {
      if ((R - G) + B >= 0.5) {
        vertex_size[0] = 1;
        vertex_size[1] = 7;
        for (k = 0; k < 7; k++) {
          vertex_data[k] = cv5[k];
        }
      } else {
        vertex_size[0] = 1;
        vertex_size[1] = 5;
        for (k = 0; k < 5; k++) {
          vertex_data[k] = cv8[k];
        }
      }
    } else if (G >= B) {
      vertex_size[0] = 1;
      vertex_size[1] = 5;
      for (k = 0; k < 5; k++) {
        vertex_data[k] = cv8[k];
      }
    } else {
      vertex_size[0] = 1;
      vertex_size[1] = 4;
      for (k = 0; k < 4; k++) {
        vertex_data[k] = cv13[k];
      }
    }
  }

  // function
}

//
// File trailer for getNearestVertex.cpp
//
// [EOF]
//
