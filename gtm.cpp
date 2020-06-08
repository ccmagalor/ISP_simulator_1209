#include"gtm.h"


int gtm(Word8u* r_in, Word8u* g_in, Word8u* b_in, int width, int height, Gtm_Cfg* param_in, module_cp* cp)
{

	LOGE("GTM:WIDTH = %d,HEIGHT= %d", width, height);
	int* Lw;
	Lw = new int[width * height];
	for (int i = 0; i < width * height; i++)
	{
		Lw[i] = 0;
	}


	float* log_Lw;
	log_Lw = new float[width * height];

	for (int i = 0; i < width * height; i++)
	{
		log_Lw[i] = 0;
	}


	float* Lg;
	Lg = new float[width * height];

	for (int i = 0; i < width * height; i++)
	{
		Lg[i] = 0;
	}


	float* gain;
	gain = new float[width * height];

	for (int i = 0; i < width * height; i++)
	{
		gain[i] = 0;
	}

	double r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	float Lwmax = 0.0f;

	int gray[256] = {0};  //记录每个灰度级别下的像素个数

	for (int i = 0; i < width * height; i++)
	{

		Lw[i] = (299 * (r_in[i]) + 587 * (g_in[i]) + 114 * (b_in[i])) / 1000;
		gray[Lw[i]]++;
	}
	float GTM_key_hist_bin_weight = 0.5f;
	int n_hist = 0; int sum = 0;

	for (int i = 0; i < 256; i++)
	{
		sum += (gray[i]) * log((float)(i+GTM_key_hist_bin_weight)*4.0f);
		
	}
	float key = exp(sum/(width*height));
	int maxval_th = 128;
	int middletone_w = 1;
	//key = (maxval_th*key*middletone_w) / dynamic_range;
	key = (maxval_th * key * middletone_w) / 255;
	LOGE("key = %f", key);
	float a_middletone = 120.0f;
	float tmp = 0.0f;
	float y_out = 0.0f;
	float ratio = 0.0f;
	for (int i = 0; i < width * height; i++)
	{
		tmp = (a_middletone * Lw[i]) / key;
		//y_out = tmp / (tmp + 1);
		y_out = tmp;
		ratio = 1 + y_out / Lw[i];
		if (i < 20)
			LOGE("ratio = %f",ratio);
	}
	
	for (int i = 0; i < width * height; i++)
	{
		
		//r_in[i] = (r_in[i] * ratio) > 255 ? 255 : (r_in[i] * ratio);
		//g_in[i] = (g_in[i] * ratio) > 255 ? 255 : (g_in[i] * ratio);
		//b_in[i] = (b_in[i] * ratio) > 255 ? 255 : (b_in[i] * ratio);
		//r_in[i] = r_in[i] * gain[i]>255?255:r_in[i] * gain[i];
		//g_in[i] = g_in[i] * gain[i]>255?255:g_in[i] * gain[i];
		//b_in[i] = b_in[i] * gain[i]>255?255:b_in[i] * gain[i];
		if (i < 30)
		{

			//	LOGE("OUT//r_in = %d,g_in = %d,b_in = %d", r_in[i],g_in[i],b_in[i]);
		}

	}

	//simple_color_balance(r_in, r_in, width, height);
	//simple_color_balance(g_in, g_in, width, height);
	//simple_color_balance(b_in, b_in, width, height);

	delete Lw;

	return 0;
}
