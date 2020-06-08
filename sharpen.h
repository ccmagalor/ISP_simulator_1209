#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"

typedef struct
{}Sharpen_Cfg;
int plot5x5(Word8u* in_3x3, float* coeff_3x3);
void sort(int a, int b, int c, int max, int middle, int min);
int sharpen(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Sharpen_Cfg* param_in, module_cp* cp);

int sharpen1(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Sharpen_Cfg* param_in, module_cp* cp);
int sharpen2(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Sharpen_Cfg* param_in, module_cp* cp);
