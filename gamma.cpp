#include"gamma.h"
int gen_gamaTable(Word16u gamma_size, double gamma_set, int gamma_bit, Word16u* gamma_LUT)
{
	int x, y;
	//const int GAMMA_TABLE_SIZE = 32;
	int maxRange = (1 << gamma_bit);
	int step = maxRange / gamma_size;
	int i, j;
	//double test;
	///for (i = 0; i < gamma_size; i++)
	///{
	///	f = (i + 0.5f) / gamma_size;
	///	f = (double)pow(f, 1.0f / gamma_set);
	///	gamma_LUT[i] = (Word16u)(f * gamma_size - 0.5f);
	///	LOGE("gamma_LUT[%d] = %d",i,gamma_LUT[i]);
	///}
   ///



	for (i = 0; i < gamma_size; i++)
	{
		j = i * step;
	//	test = pow((double)j / maxRange, 1.0 / gamma_set);
		x = (int)(maxRange * pow((double)j / maxRange, 1.0 / gamma_set));

		if (j + step < maxRange)
			y = (int)(maxRange * pow(((double)j + step) / maxRange, 1.0 / gamma_set));
		else
			y = (int)(maxRange * pow(((double)j + step - 1) / maxRange, 1.0 / gamma_set));
	
	//	lut_delta = y - x;
	//	LOGE("y= %d,x=%d",y,x);
	//	if (j + step >= maxRange)
	//	{
	//		lut_delta = (lut_delta * step * 2 + (step - 1)) / ((step - 1) * 2);
	//	}
	//	lut_delta = (lut_delta < -8192) ? -8192 : (lut_delta > 8191) ? 8191 : lut_delta;
			
	
		gamma_LUT[i] = (int)y;// (int)(x | (lut_delta << 10));
		//LOGE("gamma_LUT[%d] = %d",i,gamma_LUT[i]);
	}
	return 0;
}

int gamma_correction(Word16u* in_data, Word8u* out_data, int width, int height,Gamma_Cfg* param_in)
{
	LOGE("GAMMA:WIDTH = %d,HEIGHT= %d", width, height);
	int i;
	int enable=1;
	Word16u gamma_size = 64;
	double gamma_set = 2.2f;
	Word16u* gamma_LUT = (Word16u*)calloc(gamma_size, sizeof(Word16u));
	int gamma_bits = 8;
	gen_gamaTable(gamma_size, gamma_set, gamma_bits, gamma_LUT);

	int step = (1 << 10) / gamma_size;
	int pos0, pos1, dx;
	Word16u input_data;
	for (i = 0; i < width * height; i++)
	{
		input_data = in_data[i];
		//if (i < 5)
		//{
		//	LOGE("in_data = %d", input_data);
		//}
	
		pos0 = input_data / step;
		pos1 = pos0 + 1;

	    dx = input_data % step;
		if (pos1 == gamma_size)
			pos1 = gamma_size - 1;
		

		int dy = ((gamma_LUT[pos1] - gamma_LUT[pos0])*10)/ step;
		
		if (enable == 0)
			out_data[i] = (Word8u)(input_data>>2);
		else
		out_data[i] =(Word8u)( gamma_LUT[pos0] + ((Word8u)((dx * dy)/10)) );
		

		if (i < 20)
		{
			//LOGE("step = %d,dx=%d,dy=%d",step,dx,dy);
			//LOGE("((dx * dy)/10) = %d,input_data =%d,out_data = %d,pos0=%d,pos1=%d", ((dx * dy) /10), input_data,out_data[i],gamma_LUT[pos0],gamma_LUT[pos1]);
		}
	}
	free(gamma_LUT);
	LOGE("GAMMA end");

	return 0;
	
}