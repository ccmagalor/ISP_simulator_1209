#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"

typedef struct
{}Cc_Cfg;

int cc(Word16u* r_in, Word16u* g_in, Word16u* b_in,
	Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height, Cc_Cfg* param_in, module_cp* cp);