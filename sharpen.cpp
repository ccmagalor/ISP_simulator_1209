#include"sharpen.h"

int plot3x3(Word8u* in_3x3,float* coeff_3x3)
{
	float temp1, temp2, temp3;
	temp1 = in_3x3[0] * coeff_3x3[0] + in_3x3[1] * coeff_3x3[1] + in_3x3[2] * coeff_3x3[2];
	temp2 = in_3x3[3] * coeff_3x3[3] + in_3x3[4] * coeff_3x3[4] + in_3x3[5] * coeff_3x3[5];
	temp3 = in_3x3[6] * coeff_3x3[6] + in_3x3[7] * coeff_3x3[7] + in_3x3[8] * coeff_3x3[8];
	return (int)(temp1 + temp2 + temp3);
}


void sort(int a, int b, int c,int max,int middle,int min)
{ 
	if (a >= b && a >= c)
	{
		max = a;
		if (b >= c)
		{
			middle = b;
			min = c;
		}
		else
		{
			middle = c;
			min = b;
		}
	}
	if (b >= a && b >= c)
	{
		max = b;
		if (a >= c)
		{
			middle = a;
			min = c;
		}
		else
		{
			middle = c;
			min = a;
		}
	}
	if (c >= b && c >= a)
	{
		max = c;
		if (b >= a)
		{
			middle = b;
			min = a;
		}
		else
		{
			middle = a;
			min = b;
		}
	}
}



int plot5x5(Word8u* in_5x5, float* coeff_5x5)
{
	float temp1, temp2, temp3, temp4, temp5;
	temp1 = in_5x5[0] * coeff_5x5[0] + in_5x5[1] * coeff_5x5[1] + in_5x5[2] * coeff_5x5[2] + in_5x5[3] * coeff_5x5[3] + in_5x5[4] * coeff_5x5[4];
	temp2 = in_5x5[5] * coeff_5x5[5] + in_5x5[6] * coeff_5x5[6] + in_5x5[7] * coeff_5x5[7] + in_5x5[8] * coeff_5x5[8] + in_5x5[9] * coeff_5x5[9];
	temp3 = in_5x5[10] * coeff_5x5[10] + in_5x5[11] * coeff_5x5[11] + in_5x5[12] * coeff_5x5[12] + in_5x5[13] * coeff_5x5[13] + in_5x5[14] * coeff_5x5[14];
	temp4 = in_5x5[15] * coeff_5x5[15] + in_5x5[16] * coeff_5x5[16] + in_5x5[17] * coeff_5x5[17] + in_5x5[18] * coeff_5x5[18] + in_5x5[19] * coeff_5x5[19];
	temp5 = in_5x5[20] * coeff_5x5[20] + in_5x5[21] * coeff_5x5[21] + in_5x5[22] * coeff_5x5[22] + in_5x5[23] * coeff_5x5[23] + in_5x5[24] * coeff_5x5[24];
	
//	LOGE("%d,%d,%d,%d,%d", in_5x5[0] , in_5x5[1] , in_5x5[2] , in_5x5[3] , in_5x5[4]);
//	LOGE("%d,%d,%d,%d,%d", in_5x5[5], in_5x5[6], in_5x5[7], in_5x5[8], in_5x5[9]);
//	LOGE("%d,%d,%d,%d,%d", in_5x5[10], in_5x5[11], in_5x5[12], in_5x5[13], in_5x5[14]);
//	LOGE("%d,%d,%d,%d,%d", in_5x5[15], in_5x5[16], in_5x5[17], in_5x5[18], in_5x5[19]);
//	LOGE("%d,%d,%d,%d,%d", in_5x5[20], in_5x5[21], in_5x5[22], in_5x5[23], in_5x5[24]);
//	LOGE("%f,%f,%f,%f,%f", temp1, temp2, temp3, temp4, temp5);
//	LOGE("%d", (int)(temp1 + temp2 + temp3 + temp4 + temp5));
	return (int)(temp1 + temp2 + temp3 + temp4 + temp5);
}

int sharpen(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Sharpen_Cfg* param_in, module_cp* cp)
{
	int Fsize = 3;
	float* Guass_filter = (float*)calloc(Fsize * Fsize, sizeof(float));


	gen_Guass_filter(Fsize, Guass_filter);


	int Fsize1 = 3;
	float* Graydiff_filter = (float*)calloc(Fsize1 * Fsize1, sizeof(float));


	int Fsize2 = 3;
	float* Bilateral_filter = (float*)calloc(Fsize2 * Fsize2, sizeof(float));

	Word8u* data3x3Y = (Word8u*)calloc(9, sizeof(Word8u));
	int index;
	Word8u Y_3x3_in[9];
	int detail;
	float threshold = 1.5;
	for (int i = 0; i < width*height; i++)
	{

		
			packed_3x3_data(y_in, width, height,i, data3x3Y);

			gen_Graydiff_filter(3, data3x3Y, Graydiff_filter);

			float sum_bila=0;
			for (int j = 0; j < 9; j++)
			{
				Bilateral_filter[j] = Guass_filter[j] * Graydiff_filter[j];
				sum_bila += Bilateral_filter[j];
			}
			for (int j = 0; j < 9; j++)
			{
				Bilateral_filter[j] /= sum_bila;
			}

			detail = y_in[i] - plot3x3(data3x3Y, Graydiff_filter);
			y_in[i] = y_in[i] + threshold * detail;

			y_in[i] = plot3x3(data3x3Y, Bilateral_filter);
	
	}


	
	return 0;
}




int sharpen1(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Sharpen_Cfg* param_in, module_cp* cp)
{
	int Fsize = 5;
	int edge=0;
	int post_sharpen = 0;
	float* Riesz_filter = (float*)calloc(Fsize * Fsize, sizeof(float));

	riesz_filter(5, 5, Riesz_filter);
	Word8u* packed_5x5_y = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	int index;
	int mask;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = j * width + i;
			mask = (j % 2 << 1) + (i % 2);
			packed_5x5_data_8u(y_in, width, height, index, packed_5x5_y);
			
			
			
			edge=ABS(y_in[index] - plot5x5(packed_5x5_y, Riesz_filter));
		post_sharpen = y_in[index] + edge;
		y_in[index] = post_sharpen > 255 ? 255 : post_sharpen;
		}
	}
	
	return 0;
}

//based on local contrast
int median_filter(Word8u* input, int size);
int median_filter(Word8u* input,  int size)
{

			int output;
			Mysort <Word8u> cross_sort;
		//	Word8u* sort_data = (Word8u*)calloc(size, sizeof(Word8u));
			//LOGE("before:%d,%d,%d,%d,%d",input[0], input[1], input[2], input[3], input[4]);

			input = cross_sort.Bubble_sort(input, size);
			//LOGE("before:%d,%d,%d,%d,%d", sort_data[0], sort_data[1], sort_data[2], sort_data[3], sort_data[4]);
			
			output = (int)input[2];
			//free (sort_data);

return output;
}

int sharpen2(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Sharpen_Cfg* param_in, module_cp* cp)
{

	int edge = 0;
	int post_sharpen = 0;

	Word8u* packed_3x3_y = (Word8u*)calloc(3 * 3, sizeof(Word8u));
	Word8u* cross_3x3_y = (Word8u*)calloc(5, sizeof(Word8u));
	

	Word8u* packed_3x3_u = (Word8u*)calloc(3 * 3, sizeof(Word8u));
	Word8u* cross_3x3_u = (Word8u*)calloc(5, sizeof(Word8u));
	

	Word8u* packed_3x3_v = (Word8u*)calloc(3 * 3, sizeof(Word8u));
	Word8u* cross_3x3_v = (Word8u*)calloc(5, sizeof(Word8u));
	
	int index;

	



	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = j * width + i;

			packed_3x3_data(y_in, width, height, index, packed_3x3_y);
			packed_3x3_data(u_in, width, height, index, packed_3x3_u);
			packed_3x3_data(v_in, width, height, index, packed_3x3_v);
			cross_3x3_y[0] = packed_3x3_y[4];
			cross_3x3_y[1] = packed_3x3_y[1];
			cross_3x3_y[2] = packed_3x3_y[3];
			cross_3x3_y[3] = packed_3x3_y[5];
			cross_3x3_y[4] = packed_3x3_y[7];

			cross_3x3_u[0] = packed_3x3_u[4];
			cross_3x3_u[1] = packed_3x3_u[1];
			cross_3x3_u[2] = packed_3x3_u[3];
			cross_3x3_u[3] = packed_3x3_u[5];
			cross_3x3_u[4] = packed_3x3_u[7];

			cross_3x3_v[0] = packed_3x3_v[4];
			cross_3x3_v[1] = packed_3x3_v[1];
			cross_3x3_v[2] = packed_3x3_v[3];
			cross_3x3_v[3] = packed_3x3_v[5];
			cross_3x3_v[4] = packed_3x3_v[7];
			
		
			float hori_filter[9] = {1.0f,1.0f,1.0f,
									0.0f,0.0f,0.0f,
									-1.0f,-1.0f,-1.0f};
			float vert_filter[9] = {1.0f,0.0f,-1.0f,
									1.0f,0.0f,-1.0f,
									1.0f,0.0f,-1.0f};
			float diag_filter[9] = {0.0f,1.0f,0.0f,
									1.0f,0.0f,-1.0f,
									0.0f,-1.0f,0.0f};
			int hori_edge, vert_edge, diag_edge;
			packed_3x3_y[4] = median_filter(cross_3x3_y, 5);
			hori_edge = plot3x3(packed_3x3_y, hori_filter);
			vert_edge = plot3x3(packed_3x3_y, vert_filter);
			diag_edge = plot3x3(packed_3x3_y, diag_filter);
			//if (index <2) {
			//	y_in[index] = median_filter(cross_3x3_y, 5);
			//}
			//u_in[index] =  median_filter(cross_3x3_u, 5);
			//v_in[index] =  median_filter(cross_3x3_v, 5);

			//edge = ABS(y_in[index] - plot5x5(packed_5x5_y, Riesz_filter));
			//post_sharpen = packed_3x3_y[4];
			//y_in[index] = post_sharpen > 255 ? 255 : post_sharpen;
		}
	}

	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                         