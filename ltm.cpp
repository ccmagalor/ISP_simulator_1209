#include"ltm.h"

void simple_color_balance(Word8u* input, Word8u* output, int width, int height)
{
	int max_value = 0;
	int min_value = 255;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			max_value = MAX(max_value, input[j * height + i]);
			min_value = MIN(min_value, input[j * height + i]);
		}
	}
	if (max_value <= min_value)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				output[j * height + i] = max_value;
			}
		}

	}
	else
	{
		float scale = 255.0 / (max_value - min_value);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (input[j * height + i] < min_value)
				{
					output[j * height + i] = 0;
				}
				else if (input[j * height + i] > max_value)
				{
					output[j * height + i] = 255;
				}
				else
				{
					output[j * height + i] = (Word8u)(scale * (input[j * height + i] - min_value));
				}
			}
		}
	}
}

int ltm(Word8u* r_in, Word8u* g_in, Word8u* b_in, int width, int height, Ltm_Cfg* param_in, module_cp* cp)
{

	LOGE("LTM:WIDTH = %d,HEIGHT= %d", width, height);
	float* Lw;
	Lw = new float[width * height];
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
	for (int i = 0; i < width * height; i++)
	{
		//memcpy(r_in[j * height + i], 1);
	//	Lw[j * height + i] = 128;
		Lw[i] = (299 * (r_in[i]) + 587 * (g_in[i]) + 114 * (b_in[i])) / 1000;

		if (Lw[i] == 0)
		{
			Lw[i] = 1;
		}
		Lwmax = MAX(Lw[i], Lwmax);

	}
	
	LOGE("LWMAX = %f",Lwmax);
	float Lw_sum = 0;
	for (int i = 0; i < width * height; i++)
	{
		log_Lw[i] = log(0.001 + Lw[i]);
		Lw_sum += log_Lw[i];
	}
	

	float Lwaver = exp(Lw_sum / (width * height));
	LOGE("Lwaver = %f", Lwaver);


	float Lg_max = 0.0f;
	for (int i = 0; i < width * height; i++)
	{
		Lg[i] = log(Lw[i] / Lwaver + 1) / log(Lwmax / Lwaver + 1);

		Lg_max = MAX(Lg[i], Lg_max);
	}
	

	for (int i = 0; i < width * height; i++)


	{
		gain[i] = 1 + 36 * (Lg[i] / Lwmax);
	//	if (i %width==0&&i/width<200)
		//	LOGE("gain[%d] = %f", i, gain[i]);

	}
	float gain_ltm[256];
	for (int i = 0; i < 256; i++)
	{
		gain_ltm[i] = 0;
	}

	for (int i = 0; i < 256; i++)
	{
		gain_ltm[i] = 1 + 36 * ((log(i / Lwaver + 1) / log(Lwmax / Lwaver + 1)) / Lwmax);
	}

	for (int i = 0; i < 256; i++)
	{
		LOGE("gain_ltm[%d]=%f",i,gain_ltm[i]);
	}


	int y_idx;
	for (int i = 0; i < width * height; i++)
		{
		y_idx= (299 * (r_in[i]) + 587 * (g_in[i]) + 114 * (b_in[i])) / 1000;
			r_in[i] = (r_in[i] * gain[y_idx])>255?255:(r_in[i] * gain[y_idx]);
			g_in[i] = (g_in[i] * gain[y_idx])>255?255:(g_in[i] * gain[y_idx]);
			b_in[i] = (b_in[i] * gain[y_idx])>255?255:(b_in[i] * gain[y_idx]);
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
	delete log_Lw;
	delete Lg;
	delete gain;
	return 0;
}


int ltm1(Word8u* r_in, Word8u* g_in, Word8u* b_in, int width, int height, Ltm_Cfg* param_in, module_cp* cp)
{
	LOGE("LTM1:WIDTH = %d,HEIGHT= %d", width, height);
	Word8u* Lw;
	Lw = new Word8u[width * height];
	int k = 0;
	float r = 0.0f;
	float m = 0.0f;
	for (int i = 0; i < width * height; i++)
	{
		Lw[i] = (299 * (r_in[i]) + 587 * (g_in[i]) + 114 * (b_in[i])) / 1000;
		if (Lw[i] > 170)
		{
			k++;
		}
	}
	r = (k * 100) / (width * height);
	m = (190 * (100 - r)) / 100 + 10;
	LOGE("r=%f,m=%f",r,m);
	Word8u* packed_3x3_y = (Word8u*)calloc(3 * 3, sizeof(Word8u));
	
	Word16u y_temp1, y_temp2, y_temp3,y_temp4;
	float s=0.0f;
	float Q_s = 0.0f;
	float A_s = 0.0f;
	float ratio = 0.0f;
	for (int i = 0; i < width * height; i++)
	{
		packed_3x3_data_8u(Lw, width, height, i, packed_3x3_y);
		y_temp1 = packed_3x3_y[0] + packed_3x3_y[1] + packed_3x3_y[2];
		y_temp2 = packed_3x3_y[3] + packed_3x3_y[4] + packed_3x3_y[5];
		y_temp3 = packed_3x3_y[6] + packed_3x3_y[7] + packed_3x3_y[8];
		y_temp4 = (y_temp1 + y_temp2 + y_temp3) / 9;
		s = float(y_temp4);
		Q_s = (255 * s) / (255 - s);

		A_s = s + m + Q_s;
	
		ratio = (255 + A_s) / (A_s + Lw[i]);
		if (i < 20) {
			LOGE("s=%f,Q_s=%f,A_s=%f,ratio = %f", s, Q_s, A_s, ratio);
		}

		r_in[i] = (r_in[i] * ratio) > 255 ? 255 : (r_in[i] * ratio);
		g_in[i] = (g_in[i] * ratio) > 255 ? 255 : (g_in[i] * ratio);
		b_in[i] = (b_in[i] * ratio) > 255 ? 255 : (b_in[i] * ratio);
	}
	delete Lw;
	return 0;
}