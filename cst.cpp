#include"cst.h"
void cst(Word8u* r_in, Word8u* g_in, Word8u* b_in,
	Word8u* y_out, Word8u* u_out, Word8u* v_out, int width, int height, Cst_Cfg* param_in, module_cp* cp)
{
	LOGE("CST:WIDTH = %d,HEIGHT= %d",width,height);
	int i;
	Word8u y_temp, u_temp, v_temp;
	char r_temp, g_temp, b_temp;
	for (i = 0; i < width * height; i++)
	{
		y_temp = (77 * (r_in[i]) + 150 * (g_in[i]) + 29 * (b_in[i])) / 256 ;
		u_temp = (127 * (b_in[i]) - 43 * (r_in[i]) - 84 * (g_in[i])) / 256 + 128;
		v_temp = (131 * (r_in[i]) - 110 * (g_in[i]) - 21 * (b_in[i])) / 256 + 128;
	
		if (y_temp < 0)
			y_temp = 0;
		else if (y_temp > 255)
			y_temp = 255;
		if (u_temp < 0)
			u_temp = 0;
		else if (u_temp > 255)
			u_temp = 255;
		if (v_temp < 0)
			v_temp = 0;
		else if (v_temp > 255)
			v_temp = 255;


		y_out[i] =y_temp;
		u_out[i] = u_temp;
		v_out[i] = v_temp;
		


	}

	
}
void cstYUV2RGB(Word8u* y_in, Word8u* u_in, Word8u* v_in, Word8u* r_out, Word8u* g_out,Word8u* b_out,
	 int width, int height, Cst_Cfg* param_in, module_cp* cp)
{
	LOGE("CSTYUV2RGB:WIDTH = %d,HEIGHT= %d", width, height);
	int i;
	int r_temp, g_temp, b_temp;

	for (i = 0; i < width * height; i++)
	{
		r_temp = (298 * y_in[i] + 409 * v_in[i]) / 256 - 223;
		g_temp = (298 * y_in[i] - 100 * u_in[i] - 211 * v_in[i]) / 256 + 136;
		b_temp = (298 * y_in[i] + 516 * u_in[i]) / 256 - 277;

		if (r_temp < 0)
			r_temp = 0;
		else if (r_temp > 255)
			r_temp = 255;
		
		if (g_temp < 0)
			g_temp = 0;
		else if (g_temp > 255)
			g_temp = 255;

		if (b_temp < 0)
			b_temp = 0;
		else if (b_temp > 255)
			b_temp = 255;


		r_out[i] = r_temp;
		g_out[i] = g_temp;
		b_out[i] = b_temp;



	}


}

