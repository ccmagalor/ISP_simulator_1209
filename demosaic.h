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

Word16u interpolation_G(Word16u* in_data, float k_rb_g);


Word16u BilinDemosaicG(Word16u* in_data, int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern);
int BilinDemosaicRB(Word16u* in_data, Word16u* in_data_g, int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern);

Word16u interpolation_RB(Word16u* in_data, Word16u* in_data_g, float k_rb_g);

Word16u interpolation_RBofG_H(Word16u* in_data, Word16u* in_data_g, float k_rb_g);

Word16u interpolation_RBofG_V(Word16u* in_data, Word16u* in_data_g, float k_rb_g);

Word16u DynamicClampG(Word16u* packed_7x7_R, Word16u* packed_7x7_G, Word16u* packed_7x7_B, int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern);

int DynamicClampRB(Word16u* packed_7x7_R, Word16u* packed_7x7_G, Word16u* packed_7x7_B, int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern);