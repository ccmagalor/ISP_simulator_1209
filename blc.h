#pragma once
#include"isp_util.h"
#include"isp_type.h"
#include"isp.h"
typedef struct
{
}Blc_Cfg;

int blc(Word16u* image, Word16u* image_out, int width, int height, int bayer_pattern,Blc_Cfg* param_in, module_cp* cp);