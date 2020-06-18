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
	LOGE("Sharpen2:WIDTH = %d,HEIGHT= %d", width, height);
	int edge = 0;
	int post_sharpen = 0;


	


	
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
			median_central=median_filter(cross_3x3_y, 5);
			int median_weight;
			int central_tmp;
			central_tmp = median_weight * median_central + (16 - median_weight) * cross_3x3_y[0];
			central_tmp /= 16;
			central_tmp = central_tmp > 255 ? 255 : central_tmp;
			packed_3x3_y[24] = central_tmp;



			float vert_filter[9] = {
				-1.0f,2.0f,-1.0f,
				-2.0f,4.0f,-2.0f,
				-1.0f,2.0f,-1.0f };
			float hori_filter[9] = {
				-1.0f,-2.0f,-1.0f,
				2.0f,4.0f,2.0f,
				-1.0f,-2.0f,-1.0f };

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

			float sharpen_value_hori = plot3x3(packed_3x3_y, hori_filter);
			float sharpen_value_vert = plot3x3(packed_3x3_y, vert_filter);

			float sharpen_value_hori_se = plot5x5(packed_5x5_y, se_filter);
			float sharpen_value_vert_ne = plot5x5(packed_5x5_y, ne_filter);

			float sharpen_value_symm = plot7x7(packed_3x3_y, vert_filter);
	}
		/*
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
	*/
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                         