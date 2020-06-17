#include "demosaic.h"



void RoughDemosaic(Word16u* in_data, int mask,int bayer_pattern, Word16u* out_data)
{
	
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



}

Word16u interpolation_G(Word16u* in_data,  float k_rb_g)
{
//	printf("input parameter k_rb_g = %f\n",k_rb_g);
	int G_h_lf, G_h_hf, G_h_l, G_h_r, G_h_hl;
	int G_v_lf, G_v_hf, G_v_t, G_v_b, G_v_hl;
	float G_ratio_l, G_ratio_r;
	float G_ratio_t, G_ratio_b;
	float f_weight;//low frequency weight
	//================g interpolation===============
		//==========edge detection============


	float gradient_h[9]; 
	float gradient_v[9];
	float gradient_h_cross[5]; 
	float gradient_v_cross[5];

	float gradient_factor[14];
	float gradient_symbol[14];
	float symbole_sum = 0.0f;
	int noise_factor[14] = { 0.1f };//1~14
	float detect_weight[14] = { 0.1,0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 ,0.1 };
	float gradient_ratio = 1.1f;
	//same channle
	gradient_v[0] = ABS((in_data[23] - in_data[9]) + ((in_data[30] - in_data[2]) / 2));


	gradient_v[0] = ((in_data[23] - in_data[9]) + ((in_data[30] - in_data[2]) / 2));
	gradient_v[1] = ((in_data[24] - in_data[10]) + ((in_data[31] - in_data[3]) / 2));
	gradient_v[2] = ((in_data[25] - in_data[11]) + ((in_data[32] - in_data[4]) / 2));
	gradient_v[3] = ((in_data[30] - in_data[16]) + ((in_data[37] - in_data[9]) / 2));
	gradient_v[4] = ((in_data[31] - in_data[17]) + ((in_data[38] - in_data[10]) / 2));
	gradient_v[5] = ((in_data[32] - in_data[18]) + ((in_data[39] - in_data[11]) / 2));
	gradient_v[6] = ((in_data[37] - in_data[23]) + ((in_data[44] - in_data[16]) / 2));
	gradient_v[7] = ((in_data[38] - in_data[24]) + ((in_data[45] - in_data[17]) / 2));
	gradient_v[8] = ((in_data[39] - in_data[25]) + ((in_data[46] - in_data[18]) / 2));
	gradient_h[0] = ((in_data[17] - in_data[15]) + ((in_data[18] - in_data[14]) / 2));
	gradient_h[1] = ((in_data[18] - (in_data[16]) + (in_data[19] - in_data[15]) / 2));
	gradient_h[2] = ((in_data[19] - (in_data[17]) + (in_data[20] - in_data[16]) / 2));
	gradient_h[3] = ((in_data[24] - (in_data[22]) + (in_data[25] - in_data[21]) / 2));
	gradient_h[4] = ((in_data[25] - (in_data[23]) + (in_data[26] - in_data[22]) / 2));
	gradient_h[5] = ((in_data[26] - (in_data[24]) + (in_data[27] - in_data[23]) / 2));
	gradient_h[6] = ((in_data[31] - (in_data[29]) + (in_data[32] - in_data[28]) / 2));
	gradient_h[7] = ((in_data[32] - (in_data[30]) + (in_data[33] - in_data[29]) / 2));
	gradient_h[8] = ((in_data[33] - (in_data[31]) + (in_data[34] - in_data[30]) / 2));


	gradient_v[0] = ABS(gradient_v[0]);
	gradient_v[1] = ABS(gradient_v[1]);
	gradient_v[2] = ABS(gradient_v[2]);
	gradient_v[3] = ABS(gradient_v[3]);
	gradient_v[4] = ABS(gradient_v[4]);
	gradient_v[5] = ABS(gradient_v[5]);
	gradient_v[6] = ABS(gradient_v[6]);
	gradient_v[7] = ABS(gradient_v[7]);
	gradient_v[8] = ABS(gradient_v[8]);
	gradient_h[0] = ABS(gradient_h[0]);
	gradient_h[1] = ABS(gradient_h[1]);
	gradient_h[2] = ABS(gradient_h[2]);
	gradient_h[3] = ABS(gradient_h[3]);
	gradient_h[4] = ABS(gradient_h[4]);
	gradient_h[5] = ABS(gradient_h[5]);
	gradient_h[6] = ABS(gradient_h[6]);
	gradient_h[7] = ABS(gradient_h[7]);
	gradient_h[8] = ABS(gradient_h[8]);

	//cross channle
	gradient_v_cross[0] = ABS((in_data[16] - in_data[9] ));
	gradient_v_cross[1] = ABS((in_data[18] - in_data[11]));
	gradient_v_cross[2] = ABS((in_data[24] - in_data[17]));
	gradient_v_cross[3] = ABS((in_data[30] - in_data[23]));
	gradient_v_cross[4] = ABS((in_data[32] - in_data[25]));
	gradient_h_cross[0] = ABS((in_data[16] - in_data[15]));
	gradient_h_cross[1] = ABS((in_data[18] - in_data[17]));
	gradient_h_cross[2] = ABS((in_data[24] - in_data[23]));
	gradient_h_cross[3] = ABS((in_data[30] - in_data[29]));
	gradient_h_cross[4] = ABS((in_data[32] - in_data[31]));

	gradient_v_cross[0] +=ABS((in_data[16] - in_data[23]));
	gradient_v_cross[1] +=ABS((in_data[18] - in_data[25]));
	gradient_v_cross[2] +=ABS((in_data[24] - in_data[31]));
	gradient_v_cross[3] +=ABS((in_data[30] - in_data[37]));
	gradient_v_cross[4] +=ABS((in_data[32] - in_data[39]));
	gradient_h_cross[0] +=ABS((in_data[16] - in_data[17]));
	gradient_h_cross[1] +=ABS((in_data[18] - in_data[19]));
	gradient_h_cross[2] +=ABS((in_data[24] - in_data[25]));
	gradient_h_cross[3] +=ABS((in_data[30] - in_data[31]));
	gradient_h_cross[4] +=ABS((in_data[32] - in_data[33]));

	for (int i = 0; i < 9; i++)
	{
		gradient_factor[i] = (float(gradient_h[i] + noise_factor[i])) / (float(gradient_v[i] + noise_factor[i]));
	}
	gradient_factor[9] = (float(gradient_h_cross[0] + noise_factor[9])) / (float(gradient_v_cross[0] + noise_factor[9]));
	gradient_factor[10] = (float(gradient_h_cross[1] + noise_factor[10])) / (float(gradient_v_cross[1] + noise_factor[10]));
	gradient_factor[11] = (float(gradient_h_cross[2] + noise_factor[11])) / (float(gradient_v_cross[2] + noise_factor[11]));
	gradient_factor[12] = (float(gradient_h_cross[3] + noise_factor[12])) / (float(gradient_v_cross[3] + noise_factor[12]));
	gradient_factor[13] = (float(gradient_h_cross[4] + noise_factor[13])) / (float(gradient_v_cross[4] + noise_factor[13]));

	for (int i = 0; i < 14; i++)
	{
		if (gradient_factor[i] > gradient_ratio)
			gradient_symbol[i] = 1.0f;
		else if (gradient_factor[i] < (1.0f / gradient_ratio))
			gradient_symbol[i] = -1.0f;
		else
			gradient_symbol[i] = 0.0f;
	//	printf("%f ", gradient_symbol[i]);
	}

	for (int i = 0; i < 14; i++)
	{
		symbole_sum += detect_weight[i] * gradient_symbol[i];
	}
	//symbole_sum = ABS(symbole_sum);

	float edge_decision;
	float symbole_tmp;
	symbole_tmp = MIN(symbole_sum + 1.0f, 2.0f);
	edge_decision = MAX(symbole_tmp, 0.0f);
	edge_decision/= 2.0f;
	//printf("edge_decision=%f\n", edge_decision);
	int g_lf;

	int g_lf_h = (1.0f - edge_decision) * (in_data[23] + in_data[25]) / 2;
	int g_lf_v = edge_decision * (in_data[17] + in_data[31]) / 2.0f;
//printf("g_lf_h g_lf_v = %d,%d\n", g_lf_h, g_lf_v);
	g_lf = g_lf_h + g_lf_v;
	//printf("g_lf=%d\n", g_lf);
	int g_l, g_r, g_t, g_b;
	g_l = int((2 * in_data[23] + (in_data[24] - in_data[22]) * k_rb_g) / 2);
	g_r = int((2 * in_data[25] + (in_data[24] - in_data[26]) * k_rb_g) / 2);
	g_t = int((2 * in_data[17] + (in_data[24] - in_data[10]) * k_rb_g) / 2);
	g_b = int((2 * in_data[31] + (in_data[24] - in_data[38]) * k_rb_g) / 2);
	//printf("g_l, g_r, g_t, g_b = %d,%d,%d,%d\n", g_l, g_r, g_t, g_b);
	float noise_l=0.1f;
	float ratio_l, ratio_r, ratio_t, ratio_b;
	int diff_l, diff_r, diff_t, diff_b;
	diff_l = ABS((in_data[24] - in_data[22]));
	diff_r = ABS((in_data[24] - in_data[26]));
	diff_t = ABS((in_data[24] - in_data[10]));
	diff_b = ABS((in_data[24] - in_data[38]));
	//printf("diff_l, diff_r, diff_t, diff_b = %d,%d,%d,%d\n", diff_l, diff_r, diff_t, diff_b);


	ratio_l = (diff_l + noise_l) / (diff_l+diff_r + 2*noise_l);
	ratio_r = (diff_r + noise_l) / (diff_l + diff_r + 2 * noise_l);
	ratio_t = (diff_t + noise_l) / (diff_t + diff_b + 2 * noise_l);
	ratio_b = (diff_b + noise_l) / (diff_t + diff_b + 2 * noise_l);
	//printf("ratio_l, ratio_r, ratio_t, ratio_b = %f,%f,%f,%f\n", ratio_l, ratio_r, ratio_t, ratio_b);
	int g_h_hf, g_v_hf;
	g_h_hf = int(ratio_l * g_l + ratio_r * g_r);
	

	g_v_hf = int(ratio_t * g_t + ratio_b * g_b);
//	printf("g_h_hf, g_v_hf = %d,%d\n", g_h_hf, g_v_hf);

	int g_hf;
	g_hf = int((1.0f - edge_decision) * g_h_hf + edge_decision * g_v_hf);
//	printf("g_hf = %d\n", g_hf);
	float freq_factor = 0.5f;//low frequency interpolator
	//float freq_factor = 1.0f;//low frequency interpolator
	int g_tmp;
	g_tmp = int(freq_factor * g_lf + (1.0f - freq_factor) * g_hf);
	g_tmp = g_tmp > 1023 ? 1023 : g_tmp;
//	printf("g_tmp = %d\n", g_tmp);
	return g_tmp;

}


void BilinDemosaic(Word16u* in_data,int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern, Word16u* out_data)
{

	
	
	if (mask == 0)//cur in_data R
	{

		//out_r
		*out_data = in_data[24];
		//================g interpolation===============
		//==========edge detection============

		*(out_data + 1) = interpolation_G(in_data, 0.0f);

		

		*(out_data + 2) = (in_data[16] + in_data[18] + in_data[30] + in_data[32]) / 4;
	}
	else if (mask == 1)//gr
	{
		*out_data = (in_data[23] + in_data[25]) / 2;
		*(out_data + 1) = in_data[24];
		*(out_data + 2) = (in_data[17] + in_data[31]) / 2;
	}
	else if (mask == 2)//gb
	{
		*out_data = (in_data[17] + in_data[31]) / 2;
		*(out_data + 1) = in_data[24];
		*(out_data + 2) = (in_data[23] + in_data[25]) / 2;
	}
	else if (mask == 3)//bvi
	{
		*out_data = (in_data[16] + in_data[18] + in_data[30] + in_data[32]) / 4;
		*(out_data + 1) = interpolation_G(in_data, 0.0f);
		//*(out_data + 1) = (in_data[17] + in_data[23] + in_data[25] + in_data[31]) / 4;
		*(out_data + 2) = in_data[24];
	}
}




int demosaic(Word16u* image, Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height, int bayer_pattern, Demosaic_Cfg* param_in, module_cp* cp)
{

	LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);


	Word16u* packed_5x5_raw = (Word16u*)calloc(5 * 5, sizeof(Word16u));
	Word16u* packed_7x7_raw = (Word16u*)calloc(7 * 7, sizeof(Word16u));


	int index;
	int mask;
	float r_ratio = 0;
	float b_ratio = 0;
	Word16u* out_rgb = (Word16u*)(malloc(3 * sizeof(Word16u)));
	memset(out_rgb, 0, 3 * sizeof(Word16u));
	for (int j = 0; j < height; j++)
	{

		for (int i = 0; i < width; i++)

		{

			index = j * width + i;
			mask = (j % 2 << 1) + (i % 2);
			packed_5x5_data(image, width, height, index, packed_5x5_raw);
		//	packed_7x7_data(image, width, height, index, packed_7x7_raw);



	//		if (i == 556 && j == 556)
	//		{
	//			for (int m = 0; m < 49; m++)
	//			{
	//				printf("%d\t", packed_7x7_raw[m]);
	//				if ((m + 1) % 7 == 0)
	//				{
	//					printf("\n");
	//				}
	//			}
	//		}


			RoughDemosaic(packed_5x5_raw,mask, bayer_pattern, out_rgb);
			int algo_enable = 0;
			//if ((i > 550 && i < 555) && j == 556)
			//{
				//printf("Demosaic mask = %d\n", mask);
			//	BilinDemosaic(packed_7x7_raw, algo_enable, mask, r_ratio, b_ratio, bayer_pattern, out_rgb);
			//}
			//MalvaDemosaic(packed_5x5_raw, mask, r_ratio, b_ratio,bayer_pattern, out_rgb);




			r_out[index] = (Word16u)(out_rgb[0] & 0XFFFF);
			g_out[index] = (Word16u)(out_rgb[1] & 0XFFFF);
			b_out[index] = (Word16u)(out_rgb[2] & 0XFFFF);

			if ((i > 540 && i < 555) && j == 556)
			{
				printf("r g b = %d\t%d\t%d\t\n", r_out[index], g_out[index], b_out[index]);
			}
		}
		
	}

	free(out_rgb);
	free(packed_5x5_raw);
	free(packed_7x7_raw);

	

	
	return 0;
}