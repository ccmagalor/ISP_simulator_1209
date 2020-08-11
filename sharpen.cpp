#include"sharpen.h"




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





int sharpen(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Sharpen_Cfg* param_in, module_cp* cp)
{
	int Fsize = 3;
	float* Guass_filter = (float*)calloc(Fsize * Fsize, sizeof(float));


	gen_Guass_filter(Fsize, Guass_filter,1.5f);


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

		
			packed_3x3_data_8u(y_in, width, height,i, data3x3Y);

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
	LOGE("Sharpen2:WIDTH = %d,HEIGHT= %d", width, height);
	int edge = 0;
	int post_sharpen = 0;


	int bufferSize = width * height;

	Word8u* pYBuffer = (Word8u*)(malloc(bufferSize * sizeof(Word8u)));

	int median_central;

	int median_weight = 16;
	int central_tmp;
	
	int index;

	Word8u* packed_9x9_y = (Word8u*)calloc(9 * 9, sizeof(Word8u));
	//Word8u* cross_9x9_y = (Word8u*)calloc(5, sizeof(Word8u));

	Word8u* packed_7x7_y = (Word8u*)calloc(7 * 7, sizeof(Word8u));
	//Word8u* cross_9x9_y = (Word8u*)calloc(5, sizeof(Word8u));

	Word8u* packed_5x5_y = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	//Word8u* cross_3x3_y = (Word8u*)calloc(5, sizeof(Word8u));

	Word8u* packed_3x3_y = (Word8u*)calloc(3 * 3, sizeof(Word8u));
	Word8u* cross_3x3_y = (Word8u*)calloc(5, sizeof(Word8u));

	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = j * width + i;


			packed_3x3_data_8u(y_in, width, height, index, packed_3x3_y);
				//printf("==============================================\n");
				//}
				//=========================
				//    |1|
				//  |2|0|3|
				//	  |4|
				//====================
			cross_3x3_y[0] = packed_3x3_y[4];
			cross_3x3_y[1] = packed_3x3_y[1];
			cross_3x3_y[2] = packed_3x3_y[3];
			cross_3x3_y[3] = packed_3x3_y[5];
			cross_3x3_y[4] = packed_3x3_y[7];

			
			median_central = median_filter(cross_3x3_y, 5);
			central_tmp = median_weight * median_central + (16 - median_weight) * cross_3x3_y[0];
			central_tmp /= 16;
			central_tmp = central_tmp > 255 ? 255 : central_tmp;
				//packed_3x3_y[4] = central_tmp;
			pYBuffer[index] = central_tmp;
			
		}
	}


	int strength_lut[256]={
		0,	   4,   8,  12,  16,  20,  24,  28,  32,  36,  40,  44,  48,  52, 56, 60, 
		64,   68,  72,  76,  80,  84,  88,  92,  96, 100, 104, 108, 112, 116, 
		120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168,
		172, 176, 180, 184, 188, 192, 196, 200, 204, 208, 212, 216, 220, 
		224, 228, 232, 236, 240, 244, 248, 252, 255, 255, 255, 255, 255, 
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
		255, 255, 255, 255, 255, 255, 255, 255, 254, 252, 250, 248, 246, 
		244, 242, 240, 238, 236, 234, 232, 230, 228, 226, 224, 222, 220, 
		218, 216, 214, 212, 210, 208, 206, 204, 202, 200, 198, 196, 194, 
		192, 190, 188, 186, 184, 182, 180, 178, 176, 174, 172, 170, 168, 
		166, 164, 162, 160, 158, 156, 154, 152, 150, 148, 146, 144, 142, 
		140, 138, 136, 134, 132, 130, 128, 126, 124, 122, 120, 118, 116, 
		114, 112, 110, 108, 106, 104, 102, 100, 98, 96, 94, 92, 90, 88, 
		86, 84, 82, 80, 78, 76, 74, 72, 70, 68, 66, 64, 62, 60, 58, 56, 
		54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 
		22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2
	};

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = j * width + i;

			y_in[index] = pYBuffer[index];

		}
	}
	

	
	float* filter_lowpass_7x7 = (float*)calloc(7 * 7, sizeof(float));
	gen_Guass_filter(7, filter_lowpass_7x7, 0.5f);

	float* filter_lowpass_5x5_l = (float*)calloc(7 * 7, sizeof(float));
	gen_Guass_filter(7, filter_lowpass_5x5_l, 1.5f);

	float* filter_lowpass_5x5_h = (float*)calloc(7 * 7, sizeof(float));
	gen_Guass_filter(7, filter_lowpass_5x5_h, 0.5f);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = j * width + i;
			
		//	if ((i > 1850 && i < 1870) && (j > 2050 && j < 2100))
				//if (i == 1852 &&  j == 2050)
			//if ((i > 1860 && i < 1870) && (j > 2060 && j < 2080))
			if(1)

			{
				//printf("i=%d,j=%d\n", i, j);

				//if ((j==(height-1))      &&        (i==0||(i==(width-1))))
				//{
				//printf("\n====================index =%d===============\n", index);
				packed_9x9_data_8u(y_in, width, height, index, packed_9x9_y);
				packed_7x7_data_8u(y_in, width, height, index, packed_7x7_y);
				packed_5x5_data_8u(y_in, width, height, index, packed_5x5_y);
				packed_3x3_data_8u(y_in, width, height, index, packed_3x3_y);
				//printf("==============================================\n");
				//}
				//=========================
				//    |1|
				//  |2|0|3|
				//	  |4|
				//====================
				cross_3x3_y[0] = packed_7x7_y[24];
				cross_3x3_y[1] = packed_7x7_y[17];
				cross_3x3_y[2] = packed_7x7_y[23];
				cross_3x3_y[3] = packed_7x7_y[25];
				cross_3x3_y[4] = packed_7x7_y[31];

				int median_central;
				median_central = median_filter(cross_3x3_y, 5);
				int median_weight = 16;
				int central_tmp;
				central_tmp = median_weight * median_central + (16 - median_weight) * cross_3x3_y[0];
				central_tmp /= 16;
				central_tmp = central_tmp > 255 ? 255 : central_tmp;
				//packed_3x3_y[4] = central_tmp;



				float vert_filter[9] = {
					-1.0f,2.0f,-1.0f,
					-2.0f,4.0f,-2.0f,
					-1.0f,2.0f,-1.0f
				};
				float hori_filter[9] = {
					-1.0f,-2.0f,-1.0f,
					2.0f,4.0f,2.0f,
					-1.0f,-2.0f,-1.0f
				};

				float se_filter[25] = {
					 1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
					-1.0f, 4.0f,-1.0f,-2.0f, 0.0f,
					-1.0f,-1.0f, 6.0f,-1.0f,-1.0f,
					 0.0f,-2.0f,-1.0f, 4.0f,-1.0f,
					 0.0f, 0.0f,-1.0f,-1.0f, 1.0f
				};
				float ne_filter[25] = {
					 0.0f, 0.0f,-1.0f,-1.0f, 1.0f,
					 0.0f,-2.0f,-1.0f, 4.0f,-1.0f,
					-1.0f,-1.0f, 6.0f,-1.0f,-1.0f,
					-1.0f, 4.0f,-1.0f,-2.0f, 0.0f,
					 1.0f,-1.0f,-1.0f, 0.0f, 0.0f
				};
				float symmetric_filter[49] = {
					0.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 0.0f,
				   -1.0f,-1.0f,-2.0f,-2.0f,-2.0f,-1.0f,-1.0f,
				   -1.0f,-2.0f,-2.0f,-2.0f,-2.0f,-2.0f,-1.0f,
				   -1.0f,-2.0f,-2.0f,64.0f,-2.0f,-2.0f,-1.0f,
				   -1.0f,-2.0f,-2.0f,-2.0f,-2.0f,-2.0f,-1.0f,
				   -1.0f,-1.0f,-2.0f,-2.0f,-2.0f,-1.0f,-1.0f,
					0.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 0.0f,
				};


				float* sharpen_value = (float*)calloc(5, sizeof(float));
				float sharpen_value_hori = plot3x3(packed_3x3_y, hori_filter);
				float sharpen_value_vert = plot3x3(packed_3x3_y, vert_filter);

				float sharpen_value_hori_se = plot5x5(packed_5x5_y, se_filter);
				float sharpen_value_vert_ne = plot5x5(packed_5x5_y, ne_filter);

				float sharpen_value_symm = plot7x7(packed_7x7_y, symmetric_filter);

				//sharpen_value[0] = ABS((sharpen_value_hori));
				//sharpen_value[1] = ABS((sharpen_value_vert));
				//sharpen_value[2] = ABS((sharpen_value_hori_se));
				//sharpen_value[3] = ABS((sharpen_value_vert_ne));
				//sharpen_value[4] = ABS((sharpen_value_symm));
				sharpen_value[0] =ABS(sharpen_value_hori);
				sharpen_value[1] =ABS(sharpen_value_vert);
				sharpen_value[2] =ABS(sharpen_value_hori_se);
				sharpen_value[3] =ABS(sharpen_value_vert_ne);
				sharpen_value[0] *= 2;
				sharpen_value[1] *= 2;


				//printf("sharpen_value:\n");
				//printf("sharpen_value_symm:=%f\n",sharpen_value_symm);
				//for (int i = 0; i < 4; i++)
				//{
				//	printf("\t%f\t", sharpen_value[i]);
				//}
				//printf("\n");
				float max_sharpen_value;
				Mysort <float> cross_sort;
				//	Word8u* sort_data = (Word8u*)calloc(size, sizeof(Word8u));
					//LOGE("before:%d,%d,%d,%d,%d",input[0], input[1], input[2], input[3], input[4]);

				sharpen_value = cross_sort.Bubble_sort(sharpen_value, 4);

				//printf("sharpen_value:\n");
				//for (int i = 0; i < 4; i++)
				//{
				//	printf("\t%f\t", sharpen_value[i]);
				//}
				//printf("\n");
				max_sharpen_value = sharpen_value[3];
				int max_index;
				float sharpen_value_thld = 30.0f;
				if (max_sharpen_value < sharpen_value_thld)
				{

					max_sharpen_value = ABS(sharpen_value_symm);
					max_sharpen_value /= 64;
					max_index = 4;
				}
				else 
				{
					if (max_sharpen_value = ABS(sharpen_value_hori))
					{
						max_index = 0;
						if (sharpen_value_hori < 0)
							max_sharpen_value = 0 - max_sharpen_value;
						//max_sharpen_value /= 8;
						
					}
					else if (max_sharpen_value = ABS(sharpen_value_vert))
					{
						if (sharpen_value_vert < 0)
							max_sharpen_value = 0 - max_sharpen_value;
						//max_sharpen_value /= 8;
						max_index = 1;
					}
					else if (max_sharpen_value = ABS(sharpen_value_hori_se))
					{
						if (sharpen_value_hori_se < 0)
							max_sharpen_value = 0 - max_sharpen_value;
						//max_sharpen_value /= 16;
						max_index = 2;
					}
					else if (max_sharpen_value = ABS(sharpen_value_vert_ne))
					{
						if (sharpen_value_vert_ne < 0)
							max_sharpen_value = 0 - max_sharpen_value;
						//max_sharpen_value /= 16;
						max_index = 3;
					}
				}

				

				if (max_sharpen_value < sharpen_value_thld)
				{
			
					//max_sharpen_value = ABS(sharpen_value_symm);
					//max_sharpen_value /= 64;
					max_index = 4;
				}

				//max_sharpen_value > 1023 ? 1023 : max_sharpen_value;
			//	
			//	float local_brightness = plot7x7(packed_7x7_y, filter_lowpass_7x7);
			//
			//
			//	float y_filter_out_h = plot5x5(packed_5x5_y, filter_lowpass_5x5_h);
			//	float y_filter_out_l = plot5x5(packed_5x5_y, filter_lowpass_5x5_l);
			//
			//
			//	float y_local_activity = y_filter_out_h - y_filter_out_l;
			//
			//
			//
			//	y_local_activity = y_local_activity < 0 ? -y_local_activity : y_local_activity;
			//
			//	//pYBuffer[index] = local_brightness;
			//
			//
				int temp = y_in[index] + max_sharpen_value / 4;
				temp = temp < 0 ? 0 : temp>255 ? 255 : temp;
			//	pYBuffer[index] = (int)y_local_activity ;
				pYBuffer[index] = temp;
				//pYBuffer[index] = y_filter_out_l;
				//pYBuffer[index] = y_filter_out_h;









				//y_in[index] = 0;

			}









		}
	}
		

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = j * width + i;

			y_in[index] = pYBuffer[index];
			y_in[index] = y_in[index] > 255 ? 255 : y_in[index];
			//u_in[index] = 128;
			//v_in[index] = 128;

		}
	}



	free(pYBuffer);
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                         