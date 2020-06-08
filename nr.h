#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"

typedef struct
{}Nr_Cfg;

int nr(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Nr_Cfg* param_in, module_cp* cp);

