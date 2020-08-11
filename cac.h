#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"

typedef struct
{}Cac_Cfg;

void cac(Word8u* y_in, Word8u* u_in, Word8u* v_in, Word8u* r_out, Word8u* g_out, Word8u* b_out,
	int width, int height, Cst_Cfg* param_in, module_cp* cp);