#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"
typedef struct
{}Ltm_Cfg;

void simple_color_balance(Word8u* input, Word8u* output, int width, int height);

int ltm(Word8u* r_in, Word8u* g_in, Word8u* b_in, int width, int height, Ltm_Cfg* param_in, module_cp* cp);
int ltm1(Word8u* r_in, Word8u* g_in, Word8u* b_in, int width, int height, Ltm_Cfg* param_in, module_cp* cp);