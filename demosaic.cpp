#include "demosaic.h"



void RoughDemosaic(Word16u* in_data, int mask,int bayer_pattern, Word16u* out_data)
{
	int i, j;
	int data[25];

	data[0] = in_data[0];	data[1] = in_data[1];	data[2] = in_data[2];	data[3] = in_data[3];	data[4] = in_data[4];
	data[5] = in_data[5];	data[6] = in_data[6];	data[7] = in_data[7];	data[8] = in_data[8];	data[9] = in_data[9];
	data[10] = in_data[10]; data[11] = in_data[11]; data[12] = in_data[12]; data[13] = in_data[13]; data[14] = in_data[14];
	data[15] = in_data[15]; data[16] = in_data[16]; data[17] = in_data[17]; data[18] = in_data[18]; data[19] = in_data[19];
	data[20] = in_data[20]; data[21] = in_data[21]; data[22] = in_data[22]; data[23] = in_data[23]; data[24] = in_data[24];


	if (mask == 0)//cur in_data R
	{
		*out_data = data[12];
		*(out_data + 1) = (data[7] + data[17] + data[11] + data[13]) / 4;
		*(out_data + 2) = (data[6] + data[16] + data[8] + data[18]) / 4;
	}
	else if (mask == 1)
	{
		*out_data = (data[11] + data[13]) / 2;
		*(out_data + 1) = data[12];
		*(out_data + 2) = (data[7] + data[17]) / 2;
	}
	else if (mask == 2)
	{
		*out_data = (data[7] + data[17]) / 2;
		*(out_data + 1) = data[12];
		*(out_data + 2) = (data[11] + data[13]) / 2;
	}
	else if (mask == 3)
	{
		*out_data = (data[6] + data[16] + data[8] + data[18]) / 4;
		*(out_data + 1) = (data[7] + data[17] + data[11] + data[13]) / 4;
		*(out_data + 2) = data[12];
	}

	/*
	switch (bayer_pattern) {
	case RGGB_PATTERN:
		if (mask == 0)//cur in_data R
		{
			*out_data = data[12];
			*(out_data + 1) = (data[7] + data[17] + data[11] + data[13]) / 4;
			*(out_data + 2) = (data[6] + data[16] + data[8] + data[18]) / 4;
		}
		else if (mask == 1)
		{
			*out_data = (data[11] + data[13]) / 2;
			*(out_data + 1) = data[12];
			*(out_data + 2) = (data[7] + data[17]) / 2;
		}
		else if (mask == 2)
		{
			*out_data = (data[7] + data[17]) / 2;
			*(out_data + 1) = data[12];
			*(out_data + 2) = (data[11] + data[13]) / 2;
		}
		else if (mask == 3)
		{
			*out_data = (data[6] + data[16] + data[8] + data[18]) / 4;
			*(out_data + 1) = (data[7] + data[17] + data[11] + data[13]) / 4;
			*(out_data + 2) = data[12];
		}
		break;
	case GRBG_PATTERN:


		break;
	case BGGR_PATTERN:

		break;
	case GBRG_PATTERN:

		break;
	}
	*/

}


void MalvaDemosaic(Word16u* in_data, int mask,float r_ratio,float b_ratio, int bayer_pattern, Word16u* out_data)
{
	int i, j;
	int data[25];

	data[0] = in_data[0];	data[1] = in_data[1];	data[2] = in_data[2];	data[3] = in_data[3];	data[4] = in_data[4];
	data[5] = in_data[5];	data[6] = in_data[6];	data[7] = in_data[7];	data[8] = in_data[8];	data[9] = in_data[9];
	data[10] = in_data[10]; data[11] = in_data[11]; data[12] = in_data[12]; data[13] = in_data[13]; data[14] = in_data[14];
	data[15] = in_data[15]; data[16] = in_data[16]; data[17] = in_data[17]; data[18] = in_data[18]; data[19] = in_data[19];
	data[20] = in_data[20]; data[21] = in_data[21]; data[22] = in_data[22]; data[23] = in_data[23]; data[24] = in_data[24];


	if (mask == 0)//cur in_data R
	{

		//out_r
		*out_data = data[12];
		//out_g
		*(out_data + 1) = ((data[7] + data[17] + data[11] + data[13])+ (4* data[12]  - (data[2] + data[10] + data[14] + data[22])))/4;
		//out_b
		*(out_data + 2) = ((data[6] + data[16] + data[8] + data[18])  + (4 * data[12] - (data[2] + data[10] + data[14] + data[22])))/4;
	}
	else if (mask == 1)//gr
	{
		*out_data = (4*(data[11] + data[13])  + 8*data[12]-(data[2] + data[6] + data[10] + data[16]+ data[22] + data[18] + data[14] + data[8]))/8;
		*(out_data + 1) = data[12];
		*(out_data + 2) = (4 * (data[7] + data[17]) + 8 * data[12] - (data[2] + data[6] + data[10] + data[16] + data[22] + data[18] + data[14] + data[8])) / 8;
	}
	else if (mask == 2)//gb
	{
		*out_data = (4 * (data[7] + data[17]) + 8 * data[12] - (data[2] + data[6] + data[10] + data[16] + data[22] + data[18] + data[14] + data[8])) / 8;
		*(out_data + 1) = data[12];
		*(out_data + 2) = (4 * (data[11] + data[13]) + 8 * data[12] - (data[2] + data[6] + data[10] + data[16] + data[22] + data[18] + data[14] + data[8])) / 8;
	}
	else if (mask == 3)//b
	{
		*out_data = ((data[6] + data[16] + data[8] + data[18]) + (4 * data[12] - (data[2] + data[10] + data[14] + data[22]))) / 4;
		*(out_data + 1) = ((data[7] + data[17] + data[11] + data[13]) + (4 * data[12] - (data[2] + data[10] + data[14] + data[22]))) / 4;
		*(out_data + 2) = data[12];
	}

	/*
	switch (bayer_pattern) {
	case RGGB_PATTERN:
		if (mask == 0)//cur in_data R
		{
			*out_data = data[12];
			*(out_data + 1) = (data[7] + data[17] + data[11] + data[13]) / 4;
			*(out_data + 2) = (data[6] + data[16] + data[8] + data[18]) / 4;
		}
		else if (mask == 1)
		{
			*out_data = (data[11] + data[13]) / 2;
			*(out_data + 1) = data[12];
			*(out_data + 2) = (data[7] + data[17]) / 2;
		}
		else if (mask == 2)
		{
			*out_data = (data[7] + data[17]) / 2;
			*(out_data + 1) = data[12];
			*(out_data + 2) = (data[11] + data[13]) / 2;
		}
		else if (mask == 3)
		{
			*out_data = (data[6] + data[16] + data[8] + data[18]) / 4;
			*(out_data + 1) = (data[7] + data[17] + data[11] + data[13]) / 4;
			*(out_data + 2) = data[12];
		}
		break;
	case GRBG_PATTERN:


		break;
	case BGGR_PATTERN:

		break;
	case GBRG_PATTERN:

		break;
	}
	*/

}

void BilinDemosaic(Word16u* in_data, int mask, float r_ratio, float b_ratio, int bayer_pattern, Word16u* out_data)
{

	int i, j;

	int G_h_lf, G_h_hf, G_h_l, G_h_r,G_h_hl;
	int G_v_lf, G_v_hf, G_v_t, G_v_b,G_v_hl;
	float G_ratio_l, G_ratio_r;
	float G_ratio_t, G_ratio_b;
	float f_weight;//low frequency weight
	if (mask == 0)//cur in_data R
	{

		//out_r
		*out_data = in_data[24];
		//================g interpolation===============
		//==========edge detection============

		int gradient_h, gradient_v;
		int gradient_h0, gradient_h1, gradient_h2, gradient_h3, gradient_h4, gradient_h5, gradient_h6, gradient_h7, gradient_h8;
		int gradient_v0, gradient_v1, gradient_v2, gradient_v3, gradient_v4, gradient_v5, gradient_v6, gradient_v7, gradient_v8;
		int gradient_h_cross0, gradient_h_cross1, gradient_h_cross2, gradient_h_cross3, gradient_h_cross4;
		int gradient_v_cross0, gradient_v_cross1, gradient_v_cross2, gradient_v_cross3, gradient_v_cross4;
		float gradient_factor[14];
		float gradient_symbol[14];
		float symbole_sum=0.0f;
		int noise_factor[14] = {0.0f};//1~14
		float detect_weight[14] = { 0.1,0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 ,0.1 };
		float gradient_ratio = 1.1f;
//same channle
		gradient_h0 = ABS(in_data[30] - in_data[2]);
		gradient_h1 = ABS(in_data[31] - in_data[3]);
		gradient_h2 = ABS(in_data[32] - in_data[4]);
		gradient_h3 = ABS(in_data[37] - in_data[9]);
		gradient_h4 = ABS(in_data[38] - in_data[10]);
		gradient_h5 = ABS(in_data[39] - in_data[11]);
		gradient_h6 = ABS(in_data[44] - in_data[16]);
		gradient_h7 = ABS(in_data[45] - in_data[17]);
		gradient_h8 = ABS(in_data[46] - in_data[18]);
		
		gradient_v0 = ABS(in_data[18] - in_data[14]);
		gradient_v1 = ABS(in_data[19] - in_data[15]);
		gradient_v2 = ABS(in_data[20] - in_data[16]);
		gradient_v3 = ABS(in_data[25] - in_data[21]);
		gradient_v4 = ABS(in_data[26] - in_data[22]);
		gradient_v5 = ABS(in_data[27] - in_data[23]);
		gradient_v6 = ABS(in_data[32] - in_data[28]);
		gradient_v7 = ABS(in_data[33] - in_data[29]);
		gradient_v8 = ABS(in_data[34] - in_data[30]);


	
		//cross channle
		gradient_h_cross0 = ABS(in_data[16] - in_data[9]) + ABS(in_data[16] - in_data[23]);
		gradient_h_cross1 = ABS(in_data[18] - in_data[11]) + ABS(in_data[18] - in_data[25]);
		gradient_h_cross2 = ABS(in_data[24] - in_data[17]) + ABS(in_data[24] - in_data[31]);
		gradient_h_cross3 = ABS(in_data[30] - in_data[23]) + ABS(in_data[30] - in_data[37]);
		gradient_h_cross4 = ABS(in_data[32] - in_data[25]) + ABS(in_data[32] - in_data[39]);

		gradient_v_cross0 = ABS(in_data[16] - in_data[15]) + ABS(in_data[16] - in_data[17]);
		gradient_v_cross1 = ABS(in_data[18] - in_data[17]) + ABS(in_data[18] - in_data[19]);
		gradient_v_cross2 = ABS(in_data[24] - in_data[23]) + ABS(in_data[24] - in_data[25]);
		gradient_v_cross3 = ABS(in_data[30] - in_data[29]) + ABS(in_data[30] - in_data[31]);
		gradient_v_cross4 = ABS(in_data[32] - in_data[31]) + ABS(in_data[32] - in_data[33]);



		gradient_factor[0] = (float(gradient_h0 + noise_factor[0])) / (float(gradient_v0 + noise_factor[0]));
		gradient_factor[1] = (float(gradient_h1 + noise_factor[1])) / (float(gradient_v1 + noise_factor[1]));
		gradient_factor[2] = (float(gradient_h2 + noise_factor[2])) / (float(gradient_v2 + noise_factor[2]));
		gradient_factor[3] = (float(gradient_h3 + noise_factor[3])) / (float(gradient_v3 + noise_factor[3]));
		gradient_factor[4] = (float(gradient_h4 + noise_factor[4])) / (float(gradient_v4 + noise_factor[4]));
		gradient_factor[5] = (float(gradient_h5 + noise_factor[5])) / (float(gradient_v5 + noise_factor[5]));
		gradient_factor[6] = (float(gradient_h6 + noise_factor[6])) / (float(gradient_v6 + noise_factor[6]));
		gradient_factor[7] = (float(gradient_h7 + noise_factor[7])) / (float(gradient_v7 + noise_factor[7]));
		gradient_factor[8] = (float(gradient_h8 + noise_factor[8])) / (float(gradient_v8 + noise_factor[8]));
		gradient_factor[9] = (float(gradient_h_cross0 + noise_factor[9])) / (float(gradient_v_cross0 + noise_factor[0]));
		gradient_factor[10] = (float(gradient_h_cross1 + noise_factor[10])) / (float(gradient_v_cross1 + noise_factor[1]));
		gradient_factor[11] = (float(gradient_h_cross2 + noise_factor[11])) / (float(gradient_v_cross2 + noise_factor[2]));
		gradient_factor[12] = (float(gradient_h_cross3 + noise_factor[12])) / (float(gradient_v_cross3 + noise_factor[3]));
		gradient_factor[13] = (float(gradient_h_cross4 + noise_factor[13])) / (float(gradient_v_cross4 + noise_factor[4]));
	

		for (int i = 0; i < 14; i++)
		{
			if (gradient_factor[i] > gradient_ratio)
				gradient_symbol[i] = 1.0f;
			else if(gradient_factor[i] < (1.0f/gradient_ratio))
				gradient_symbol[i] = -1.0f;
			else
				gradient_symbol[i] = 0.0f;
		}

		for (int i = 0; i < 14; i++)
		{
			symbole_sum += detect_weight[i] * gradient_symbol[i];
		}
		
		float edge_decision;


		edge_decision = MAX(MIN(symbole_sum+1.0f, 2.0f), 0.0f)/2.0f;

		int g_lf;
		g_lf = int((1.0f - edge_decision) * (in_data[23] + in_data[25]) + edge_decision * (in_data[17] + in_data[31])/2);

		int g_l, g_r, g_t, g_b;
		g_l = int((2 * in_data[23] + (in_data[24] - in_data[22]) / r_ratio) / 2);
		g_r = int((2 * in_data[25] + (in_data[24] - in_data[26]) / r_ratio) / 2);
		g_t = int((2 * in_data[17] + (in_data[24] - in_data[10]) / r_ratio) / 2);
		g_b = int((2 * in_data[31] + (in_data[24] - in_data[38]) / r_ratio) / 2);

		float ratio_l, ratio_r, ratio_t, ratio_b;
		ratio_l = (float(ABS(in_data[24] - in_data[22]) + 1)) / (float(ABS(in_data[24] - in_data[22]) + ABS(in_data[24] - in_data[26]) + 2));
		ratio_r = (float(ABS(in_data[24] - in_data[26]) + 1)) / (float(ABS(in_data[24] - in_data[22]) + ABS(in_data[24] - in_data[26]) + 2));
		ratio_t = (float(ABS(in_data[24] - in_data[10]) + 1)) / (float(ABS(in_data[24] - in_data[10]) + ABS(in_data[24] - in_data[38]) + 2));
		ratio_b = (float(ABS(in_data[24] - in_data[38]) + 1)) / (float(ABS(in_data[24] - in_data[10]) + ABS(in_data[24] - in_data[38]) + 2));

		int g_h_hf, g_v_hf;
		g_h_hf = int(ratio_l * g_l + ratio_r * g_r);
		g_v_hf = int(ratio_t * g_t + ratio_b * g_b);


		int g_hf;
		g_hf = int((1.0f - edge_decision) * g_h_hf + edge_decision * g_v_hf);

		float freq_factor=0.5f;//low frequency interpolator

		int g_tmp;
		g_tmp = int(freq_factor * g_lf + (1.0f - freq_factor) * g_hf);

		*(out_data + 1) = g_tmp > 1023 ? 1023 : g_tmp;
		//G_h_lf = in_data[23] + in_data[25];
		//G_h_l = 2 * in_data[23] + (int)((in_data[24] - in_data[22]) / r_ratio);
		//G_h_r = 2 * in_data[23] + (int)((in_data[24] - in_data[26]) / r_ratio);
		//G_ratio_l = (float(ABS(in_data[24] - in_data[22]) + 1)) / (float(ABS(in_data[24] - in_data[22])+ABS(in_data[24] - in_data[26])+2));
		//G_ratio_r = (float(ABS(in_data[24] - in_data[26]) + 1)) / (float(ABS(in_data[24] - in_data[22]) + ABS(in_data[24] - in_data[26]) + 2));
		//
		//G_h_hf = G_ratio_l * G_h_l + G_ratio_r * G_h_r;
		//
		//G_h_hl = int((1.0f - f_weight) * G_h_hf + f_weight * G_h_lf);
		//
		//
		//
		//G_v_lf = in_data[23] + in_data[25];
		//G_v_t = 2 * in_data[23] + (int)((in_data[24] - in_data[22]) / r_ratio);
		//G_v_b = 2 * in_data[23] + (int)((in_data[24] - in_data[26]) / r_ratio);
		//G_ratio_t = (float(ABS(in_data[24] - in_data[22]) + 1)) / (float(ABS(in_data[24] - in_data[22]) + ABS(in_data[24] - in_data[26]) + 2));
		//G_ratio_b = (float(ABS(in_data[24] - in_data[26]) + 1)) / (float(ABS(in_data[24] - in_data[22]) + ABS(in_data[24] - in_data[26]) + 2));
		//
		//G_v_hf = G_ratio_t * G_v_t + G_ratio_b * G_v_b;
		//
		//G_v_hl = int((1.0f - f_weight) * G_v_hf + f_weight * G_v_lf);






		*(out_data + 1) = ((in_data[7] + in_data[17] + in_data[11] + in_data[13]) + (4 * in_data[12] - (in_data[2] + in_data[10] + in_data[14] + in_data[22]))) / 4;
		//out_b
		*(out_data + 2) = ((in_data[6] + in_data[16] + in_data[8] + in_data[18]) + (4 * in_data[12] - (in_data[2] + in_data[10] + in_data[14] + in_data[22]))) / 4;
	}
	else if (mask == 1)//gr
	{
		*out_data = (4 * (in_data[11] + in_data[13]) + 8 * in_data[12] - (in_data[2] + in_data[6] + in_data[10] + in_data[16] + in_data[22] + in_data[18] + in_data[14] + in_data[8])) / 8;
		*(out_data + 1) = in_data[12];
		*(out_data + 2) = (4 * (in_data[7] + in_data[17]) + 8 * in_data[12] - (in_data[2] + in_data[6] + in_data[10] + in_data[16] + in_data[22] + in_data[18] + in_data[14] + in_data[8])) / 8;
	}
	else if (mask == 2)//gb
	{
		*out_data = (4 * (in_data[7] + in_data[17]) + 8 * in_data[12] - (in_data[2] + in_data[6] + in_data[10] + in_data[16] + in_data[22] + in_data[18] + in_data[14] + in_data[8])) / 8;
		*(out_data + 1) = in_data[12];
		*(out_data + 2) = (4 * (in_data[11] + in_data[13]) + 8 * in_data[12] - (in_data[2] + in_data[6] + in_data[10] + in_data[16] + in_data[22] + in_data[18] + in_data[14] + in_data[8])) / 8;
	}
	else if (mask == 3)//b
	{
		*out_data = ((in_data[6] + in_data[16] + in_data[8] + in_data[18]) + (4 * in_data[12] - (in_data[2] + in_data[10] + in_data[14] + in_data[22]))) / 4;
		*(out_data + 1) = ((in_data[7] + in_data[17] + in_data[11] + in_data[13]) + (4 * in_data[12] - (in_data[2] + in_data[10] + in_data[14] + in_data[22]))) / 4;
		*(out_data + 2) = in_data[12];
	}



}




int demosaic(Word16u* image, Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height, int bayer_pattern, Demosaic_Cfg* param_in, module_cp* cp)
{

	LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);

	int idx0 = 0;
	int idx1 = 0;
	int idx2 = 0;
	Word16u* packed_5x5_raw = (Word16u*)calloc(5*5,sizeof(Word16u));

	float r_ratio;
	float b_ratio;
	float g_ratio;
	r_ratio = param_in->r_gain;
	g_ratio = param_in->g_gain;
	b_ratio = param_in->b_gain;


	int index;
	int mask;
	int rg_ratio, bg_ratio;//ratio from awb gain
	Word16u* out_rgb = (Word16u*)(malloc(3 * sizeof(Word16u)));
	memset(out_rgb, 0, 3 * sizeof(Word16u));

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			index = j * width + i;
			mask = (j % 2 << 1) + (i % 2);
			packed_5x5_data(image, width, height, index, packed_5x5_raw);
			//RoughDemosaic(packed_5x5_raw,mask, bayer_pattern, out_rgb);
			MalvaDemosaic(packed_5x5_raw, mask, r_ratio, b_ratio,bayer_pattern, out_rgb);
		//	if (index <5)
		//	{
		//		LOGE("R=%d,g=%d,b=%d", *out_rgb, *(out_rgb + 1), *(out_rgb + 2));
		//	}
	//	if (index<20)
	//	{
	//		LOGE("index = %d,mask =%d,indata[%d]=%d,R=%d,g=%d,b=%d", index,mask,index,image[index],out_rgb[0], out_rgb[1], out_rgb[2]);
	//	}



	r_out[index] = (Word16u)(out_rgb[0] & 0XFFFF);
	g_out[index] = (Word16u)(out_rgb[1] & 0XFFFF);
	b_out[index] = (Word16u)(out_rgb[2] & 0XFFFF);
		}
	}
//for (int i = 0; i < width; i++)
//{
//	for (int j = 0; j < height; j++)
//	{
//		if (i < width / 4)
//		{
//			r_out[j * width + i] = 8;
//			g_out[j * width + i] = 8;
//			b_out[j * width + i] = 8;
//		}
//		else if (i < width / 2)
//		{
//			r_out[j * width + i] = 330;
//			g_out[j * width + i] = 330;
//			b_out[j * width + i] = 330;
//		}
//		else if (i < width*3 / 4)
//		{
//			r_out[j * width + i] = 660;
//			g_out[j * width + i] = 660;
//			b_out[j * width + i] = 660;
//		}
//		else
//		{
//			r_out[j * width + i] = 1020;
//			g_out[j * width + i] = 1020;
//			b_out[j * width + i] = 1020;
//		}
//
//	}
//	
//}
	//for (int i = 0; i < width; i++)
	//{
	//	for (int j = 0; j < height; j++)
	//	{
	//		if (i % 400 < 200)
	//		{
	//			r_out[j * width + i] = 8;
	//			g_out[j * width + i] = 8;
	//			b_out[j * width + i] = 8;
	//		}
	//		else
	//		{
	//			r_out[j * width + i] = 240*4;
	//			g_out[j * width + i] = 240*4;
	//			b_out[j * width + i] = 240*4;
	//		}
	//
	//
	//	}
	//}
	
	/*
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (((j % 400 < 200) && (i % 400 < 200))|| ((j % 400 > 200) && (i % 400 > 200)))
			{
				r_out[j * width + i] = 8;
				g_out[j * width + i] = 8;
				b_out[j * width + i] = 8;
			}
			else
			{
				r_out[j * width + i] = 240 * 4;
				g_out[j * width + i] = 240 * 4;
				b_out[j * width + i] = 240 * 4;
			}


		}
	}
	*/
	free(out_rgb);

	
	return 0;
}