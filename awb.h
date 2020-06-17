#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"
typedef struct
{
	float r_gain;
	float g_gain;
	float b_gain;

}Awb_out;
int RGB2YCbCr(Word16u* r_in, Word16u* g_in, Word16u* b_in, Word16u* Y_out, Word16u* Cb_out, Word16u* Cr_out, int width, int height);

int YCbCr2RGB(Word16u* Y_in, Word16u* Cb_in, Word16u* Cr_in, Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height);

int awb(Word16u* image, Awb_out* param_out, int width, int height);

