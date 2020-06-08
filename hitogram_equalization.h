#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"
typedef struct
{}Equal_Cfg;
int Equal(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Equal_Cfg* param_in, module_cp* cp);