#include "nr.h"






int nr(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Nr_Cfg* param_in, module_cp* cp)
{

	int Fsize = 5;
	float* Guass_filter = (float*)calloc(Fsize * Fsize, sizeof(float));


	gen_Guass_filter(Fsize, Guass_filter,1.5f);


	int Fsize1 = 5;
	float* Graydiff_filter = (float*)calloc(Fsize1 * Fsize1, sizeof(float));


	int Fsize2 = 5;
	float* Bilateral_filter_y = (float*)calloc(Fsize2 * Fsize2, sizeof(float));
	float* Bilateral_filter_u = (float*)calloc(Fsize2 * Fsize2, sizeof(float));
	float* Bilateral_filter_v = (float*)calloc(Fsize2 * Fsize2, sizeof(float));
	Word8u* packed_5x5_y = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	Word8u* packed_5x5_u = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	Word8u* packed_5x5_v = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	int index;
	int post_nr_y = 0;
	int post_nr_u = 0;
	int post_nr_v = 0;
	//for (int i = 0; i < width * height; i++)
	for (int i = 0; i <width*height; i++)
	{


		index = i;

		packed_5x5_data_8u(y_in, width, height, index, packed_5x5_y);
		packed_5x5_data_8u(u_in, width, height, index, packed_5x5_u);
		packed_5x5_data_8u(v_in, width, height, index, packed_5x5_v);

		gen_Graydiff_filter(5, packed_5x5_y, Graydiff_filter);

		float sum_bila_y = 0;
		float sum_bila_u = 0;
		float sum_bila_v = 0;
		for (int j = 0; j < 25; j++)
		{
			Bilateral_filter_y[j] = Guass_filter[j] * Graydiff_filter[j];
			sum_bila_y += Bilateral_filter_y[j];
		}
		for (int j = 0; j < 25; j++)
		{
			Bilateral_filter_y[j] /= sum_bila_y;
		}

		for (int j = 0; j < 25; j++)
		{
			Bilateral_filter_u[j] = Guass_filter[j] * Graydiff_filter[j];
			sum_bila_u += Bilateral_filter_u[j];
		}
		for (int j = 0; j < 25; j++)
		{
			Bilateral_filter_u[j] /= sum_bila_u;
		}

		for (int j = 0; j < 25; j++)
		{
			Bilateral_filter_v[j] = Guass_filter[j] * Graydiff_filter[j];
			sum_bila_v += Bilateral_filter_v[j];
		}
		for (int j = 0; j < 25; j++)
		{
			Bilateral_filter_v[j] /= sum_bila_v;
		}
	//	if (i>154444&&i<154488) {
	//		post_nr_y = plot5x5(packed_5x5_y, Graydiff_filter);
	//		LOGE("input  = %d,output = %d", y_in[i], post_nr_y);
	//
	//		y_in[i] = post_nr_y > 255 ? 255 : post_nr_y;
	//		//u_in[index] = post_nr_u > 255 ? 255 : post_nr_u;
	//		//v_in[index] = post_nr_v > 255 ? 255 : post_nr_v;
	//		LOGE("output  = %d,output = %d", y_in[i], post_nr_y);
	//	}
		post_nr_y = plot5x5(packed_5x5_y, Bilateral_filter_y);
		post_nr_u = plot5x5(packed_5x5_u, Bilateral_filter_u);
		post_nr_v = plot5x5(packed_5x5_v, Bilateral_filter_v);
		//LOGE("input  = %d,output = %d", y_in[i], post_nr_y);

		y_in[i] = post_nr_y > 255 ? 255 : post_nr_y;
		u_in[i] = post_nr_u > 255 ? 255 : post_nr_u;
		v_in[i] = post_nr_v > 255 ? 255 : post_nr_v;


	}





	return 0;
}