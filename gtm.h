#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"
typedef struct
{}Gtm_Cfg;



int gtm(Word8u* r_in, Word8u* g_in, Word8u* b_in, int width, int height, Gtm_Cfg* param_in, module_cp* cp);
