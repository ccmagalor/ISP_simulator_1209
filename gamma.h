#pragma once
#include"isp.h"
#include"isp_util.h"
#include"isp_type.h"
#include<cmath>
typedef struct
{}Gamma_Cfg;
int gen_gamaTable(Word16u gamma_size, double gamma_set, int gamma_bit, Word16u* gamma_LUT);
int gamma_correction(Word16u* in_data, Word8u* out_data, int width, int height, Gamma_Cfg* param_in);