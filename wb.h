#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"
#include"awb.h"
typedef struct
{
	float r_gain;
	float g_gain;
	float b_gain;

}Wb_param_cfg;

int wb(Word16u* r_in, Word16u* g_in, Word16u* b_in, Wb_param_cfg* param_in, int width, int height);