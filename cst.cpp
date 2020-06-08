#include"cst.h"
int cst(Word8u* r_in, Word8u* g_in, Word8u* b_in,
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
	return 0;
	
}