#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"
typedef struct
{
	float r_gain;
	float g_gain;
	float b_gain;
}Demosaic_Cfg;
int demosaic(Word16u* image, Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height, int bayer_pattern, Demosaic_Cfg* param_in, module_cp* cp);
void RoughDemosaic(Word16u* in_data, int mask, int bayer_pattern, Word16u* out_data);
void MalvaDemosaic(Word16u* in_data, int mask, float r_ratio, float b_ratio, int bayer_pattern, Word16u* out_data);
void BilinDemosaic(Word16u* in_data, int mask, float r_ratio, float b_ratio, int bayer_pattern, Word16u* out_data);

