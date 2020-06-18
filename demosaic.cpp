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
	float f_weight;//low frequency weightgo
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

Word16u interpolation_RB(Word16u* in_data, Word16u* in_data_g, float k_rb_g)
{
	int rb_lf = (in_data[16] + in_data[30] + in_data[32] + in_data[38]) / 4;
	
	float diff_tl, diff_tr, diff_bl, diff_br;
	float weight = 1.0f;;
	float noise_level = 0.1f;
	diff_tl = ABS((in_data_g[24] - in_data_g[16]));
	diff_tr = ABS((in_data_g[24] - in_data_g[18]));
	diff_bl = ABS((in_data_g[24] - in_data_g[30]));
	diff_br = ABS((in_data_g[24] - in_data_g[32]));

	diff_tl += ABS((in_data[32] - in_data[16]))*weight;
	diff_tr += ABS((in_data[30] - in_data[18]))*weight;
	diff_bl += ABS((in_data[18] - in_data[30]))*weight;
	diff_br += ABS((in_data[16] - in_data[32]))*weight;

	diff_tl += noise_level;
	diff_tr += noise_level;
	diff_bl += noise_level;
	diff_br += noise_level;

	diff_tl = 1.0f / diff_tl;
	diff_tr = 1.0f / diff_tr;
	diff_bl = 1.0f / diff_bl;
	diff_br = 1.0f / diff_br;

	float diff_sum;
	diff_sum = diff_tl+ diff_tr+ diff_bl+ diff_br;

	float ratio_tl, ratio_tr, ratio_bl, ratio_br;

	ratio_tl = diff_tl / diff_sum;
	ratio_tr = diff_tr / diff_sum;
	ratio_bl = diff_bl / diff_sum;
	ratio_br = diff_br / diff_sum;

	int rb_hf = in_data[16] * ratio_tl + in_data[18] * ratio_tr + in_data[30] * ratio_bl + in_data[32] * ratio_br;
	//printf("ratio_tl, ratio_tr, ratio_bl, ratio_br = %f,%f,%f,%f\n",ratio_tl, ratio_tr, ratio_bl, ratio_br);
	float low_fre_factor = 0.0f;

	float rb_temp = low_fre_factor * rb_lf + (1.0f - low_fre_factor) * rb_hf;

	if (rb_temp > 1023)
		rb_temp = 1023;

	return rb_temp;

}


Word16u interpolation_RBofG_H(Word16u* in_data, Word16u* in_data_g, float k_rb_g)
{
	int rb_lf = (in_data[23] + in_data[25]) / 4;

	float diff_l, diff_r;
	float weight = 1.0f;;
	float noise_level = 0.1f;
	diff_l = ABS((in_data_g[24] - in_data_g[23]));
	diff_r = ABS((in_data_g[24] - in_data_g[25]));


	diff_l += ABS((in_data[23] - in_data[25])) * weight;
	diff_r += ABS((in_data[23] - in_data[25])) * weight;


	diff_l += noise_level;
	diff_r += noise_level;




	float diff_sum;
	diff_sum = diff_l + diff_r;

	float ratio_l, ratio_r;

	ratio_l = diff_r / diff_sum;
	ratio_r = diff_l / diff_sum;


	int rb_hf = in_data[23] * ratio_l + in_data[25] * ratio_r;

	float low_fre_factor = 0.0f;

	float rb_temp = low_fre_factor * rb_lf + (1.0f - low_fre_factor) * rb_hf;

	if (rb_temp > 1023)
		rb_temp = 1023;

	return rb_temp;


}

Word16u interpolation_RBofG_V(Word16u* in_data, Word16u* in_data_g, float k_rb_g)
{
	int rb_lf = (in_data[17] + in_data[31]) / 2;
	float ratio_t, ratio_b;
	float diff_t, diff_b;
	float weight = 1.0f;;
	float noise_level = 0.1f;
	diff_t = ABS((in_data_g[24] - in_data_g[17]));
	diff_b = ABS((in_data_g[24] - in_data_g[31]));


	diff_t += ABS((in_data[17] - in_data[31])) * weight;
	diff_b += ABS((in_data[17] - in_data[31])) * weight;


	diff_t += noise_level;
	diff_b += noise_level;




	float diff_sum;
	diff_sum = diff_t + diff_b;



	ratio_t = diff_b / diff_sum;
	ratio_b = diff_t / diff_sum;


	int rb_hf = in_data[17] * ratio_t + in_data[31] * ratio_b;

	float low_fre_factor = 0.0f;

	float rb_temp = low_fre_factor * rb_lf + (1.0f - low_fre_factor) * rb_hf;

	if (rb_temp > 1023)
		rb_temp = 1023;

	return rb_temp;


}



int BilinDemosaicRB(Word16u* in_data, Word16u* in_data_g, int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern)
{
	Word16u r_out, b_out;
	int data_rb;
	if (mask == 0)//cur in_data R
	{


		r_out = in_data[24];
		b_out = interpolation_RB(in_data, in_data_g,0.0f );
		//b_out = (in_data[16]+in_data[18]+ in_data[30] + in_data[32])/4;

	}
	else if (mask == 1)//gr
	{

		r_out = interpolation_RBofG_H(in_data, in_data_g, 0.0f);
		b_out = interpolation_RBofG_V(in_data, in_data_g, 0.0f);

	//	r_out = (in_data[23] + in_data[25]) / 2;
	//	b_out = (in_data[17] + in_data[31]) / 2;

	}
	else if (mask == 2)//gb
	{
		r_out = interpolation_RBofG_V(in_data, in_data_g, 0.0f);
		b_out = interpolation_RBofG_H(in_data, in_data_g, 0.0f);

	//	r_out = (in_data[17] + in_data[31]) / 2;
	//	b_out = (in_data[23] + in_data[25]) / 2;
	}
	else if (mask == 3)//b
	{

		r_out = interpolation_RB(in_data, in_data_g, 0.0f);
		//r_out = (in_data[16] + in_data[18] + in_data[30] + in_data[32]) / 4;

		b_out = in_data[24];

	}
	data_rb = (r_out << 16)+ b_out;

	//printf("r b rb = %d\t%d\t%x\n",r_out,b_out,data_rb);
	return data_rb;
}

Word16u BilinDemosaicG(Word16u* in_data,int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern)
{

	Word16u g_out;
	
	if (mask == 0)//cur in_data R
	{


		g_out = interpolation_G(in_data, 0.0f);
	//	g_out = (in_data[17] + in_data[23] + in_data[25] + in_data[31]) / 4;


	}
	else if (mask == 1)//gr
	{

		g_out = in_data[24];

	}
	else if (mask == 2)//gb
	{
		g_out = in_data[24];
	}
	else if (mask == 3)//bvi
	{

		g_out = interpolation_G(in_data, 0.0f);
		//g_out = (in_data[17] + in_data[23] + in_data[25] + in_data[31]) / 4;

	}
//	printf("g_out = %d\n",g_out);


	return g_out;
}

Word16u DynamicClampG(Word16u* packed_7x7_R, Word16u* packed_7x7_G, Word16u* packed_7x7_B, int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern)
{
	int min_g, max_g, g_tmp1, g_tmp2;
	int g_out;
	if (mask == 0)//cur in_data R
	{
		min_g = min4(packed_7x7_G[17], packed_7x7_G[23], packed_7x7_G[25], packed_7x7_G[31]);
		max_g = max4(packed_7x7_G[17], packed_7x7_G[23], packed_7x7_G[25], packed_7x7_G[31]);
		g_tmp1 = MAX(packed_7x7_G[24], min_g);
		g_tmp2 = MIN(g_tmp1, max_g);
			
		g_out = g_tmp2;
		//	g_out = (in_data[17] + in_data[23] + in_data[25] + in_data[31]) / 4;


	}
	else if (mask == 1)//gr
	{

		g_out = packed_7x7_G[24];

	}
	else if (mask == 2)//gb
	{
		g_out = packed_7x7_G[24];
	}
	else if (mask == 3)//bvi
	{

		min_g = min4(packed_7x7_G[17], packed_7x7_G[23], packed_7x7_G[25], packed_7x7_G[31]);
		max_g = max4(packed_7x7_G[17], packed_7x7_G[23], packed_7x7_G[25], packed_7x7_G[31]);
		g_tmp1 = MAX(packed_7x7_G[24], min_g);
		g_tmp2 = MIN(g_tmp1, max_g);
		g_out = g_tmp2;
	}
	//	printf("g_out = %d\n",g_out);

	
	return g_out;

}

int DynamicClampRB(Word16u* packed_7x7_R, Word16u* packed_7x7_G, Word16u* packed_7x7_B, int algo_enable, int mask, float r_ratio, float b_ratio, int bayer_pattern)
{
	int min_r, max_r, r_tmp1, r_tmp2;
	int min_b, max_b, b_tmp1, b_tmp2;
	int r_out;
	int b_out;
	int data_rb;
	if (mask == 0)//cur in_data R
	{

		r_out = packed_7x7_R[24];

		min_b = min4(packed_7x7_B[16], packed_7x7_B[18], packed_7x7_B[30], packed_7x7_B[32]);
		max_b = max4(packed_7x7_B[16], packed_7x7_B[18], packed_7x7_B[30], packed_7x7_B[32]);
		b_tmp1 = MAX(packed_7x7_B[24], min_b);
		b_tmp2 = MIN(b_tmp1, max_b);
		b_out = b_tmp2;

	}
	else if (mask == 1)//gr
	{

		min_r = MIN(packed_7x7_R[23], packed_7x7_R[25]);
		max_r = MAX(packed_7x7_R[23], packed_7x7_R[25]);
		r_tmp1 = MAX(packed_7x7_R[24], min_r);
		r_tmp2 = MIN(r_tmp1, max_r);
		r_out = r_tmp2;

		min_b = MIN(packed_7x7_B[17], packed_7x7_B[31]);
		max_b = MAX(packed_7x7_B[17], packed_7x7_B[31]);
		b_tmp1 = MAX(packed_7x7_B[24], min_b);
		b_tmp2 = MIN(b_tmp1, max_b);
		b_out = b_tmp2;


	}
	else if (mask == 2)//gb
	{
		min_r = MIN(packed_7x7_B[17], packed_7x7_B[31]);
		max_r = MAX(packed_7x7_B[17], packed_7x7_B[31]);
		r_tmp1 = MAX(packed_7x7_R[24], min_r);
		r_tmp2 = MIN(r_tmp1, max_r);
		r_out = r_tmp2;

		min_b = MIN(packed_7x7_R[23], packed_7x7_R[25]);
		max_b = MAX(packed_7x7_R[23], packed_7x7_R[25]);
		b_tmp1 = MAX(packed_7x7_B[24], min_b);
		b_tmp2 = MIN(b_tmp1, max_b);
		b_out = b_tmp2;
	}
	else if (mask == 3)//bvi
	{

		b_out = packed_7x7_B[24];

		min_r = min4(packed_7x7_R[16], packed_7x7_R[18], packed_7x7_R[30], packed_7x7_R[32]);
		max_r = max4(packed_7x7_R[16], packed_7x7_R[18], packed_7x7_R[30], packed_7x7_R[32]);
		r_tmp1 = MAX(packed_7x7_R[24], min_r);
		r_tmp2 = MIN(r_tmp1, max_r);
		r_out = r_tmp2;
	}
	//	printf("g_out = %d\n",g_out);
	data_rb = (r_out << 16) + b_out;

	return data_rb;

}

int demosaic(Word16u* image, Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height, int bayer_pattern, Demosaic_Cfg* param_in, module_cp* cp)
{

	LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);


	//Word16u* packed_5x5_raw = (Word16u*)calloc(5 * 5, sizeof(Word16u));
	Word16u* packed_7x7_raw = (Word16u*)calloc(7 * 7, sizeof(Word16u));
	Word16u* packed_7x7_R = (Word16u*)calloc(7 * 7, sizeof(Word16u));
	Word16u* packed_7x7_G = (Word16u*)calloc(7 * 7, sizeof(Word16u));
	Word16u* packed_7x7_B = (Word16u*)calloc(7 * 7, sizeof(Word16u));
	int index;
	int mask;
	float r_ratio = 0.0f;
	float b_ratio = 0.0f;
	//Word16u* out_rgb = (Word16u*)(malloc(3 * sizeof(Word16u)));
	//memset(out_rgb, 0, 3 * sizeof(Word16u));





	int GbufferSize = width * height;

	Word16u* pGBuffer = (Word16u*)(malloc(GbufferSize * sizeof(Word16u)));

	memset(pGBuffer, 0, GbufferSize * sizeof(Word16u));

	int RbufferSize = width * height;

	Word16u* pRBuffer = (Word16u*)(malloc(RbufferSize * sizeof(Word16u)));

	memset(pRBuffer, 0, RbufferSize * sizeof(Word16u));

	int BbufferSize = width * height;

	Word16u* pBBuffer = (Word16u*)(malloc(BbufferSize * sizeof(Word16u)));

	memset(pRBuffer, 0, BbufferSize * sizeof(Word16u));

	Word16u r_inter, b_inter, g_inter;
	r_inter = 0;
	b_inter = 0;
	g_inter = 0;

	int algo_enable = 0;
	for (int j = 0; j < height; j++)
	{

		for (int i = 0; i < width; i++)

		{

			index = j * width + i;
			mask = (j % 2 << 1) + (i % 2);
	
			packed_7x7_data(image, width, height, index, packed_7x7_raw);

			int algo_enable = 0;
			//if ((i > 550 && i < 555) && j == 556)
			//{
			//if ((i > 550 && i < 555) && j == 556)
			//{
				*(pGBuffer + index) = BilinDemosaicG(packed_7x7_raw, algo_enable, mask, r_ratio, b_ratio, bayer_pattern);

			
			//}
			//MalvaDemosaic(packed_5x5_raw, mask, r_ratio, b_ratio,bayer_pattern, out_rgb);

				//printf("g_inter = %d\n", *(pGBuffer + index));
			//}
			g_out[index] = (Word16u)(*(pGBuffer + index) & 0XFFFF);


		}
		
	}
	int rb_out;
	for (int j = 0; j < height; j++)
	{

		for (int i = 0; i < width; i++)

		{

			index = j * width + i;
			mask = (j % 2 << 1) + (i % 2);

			packed_7x7_data(image, width, height, index, packed_7x7_raw);
			packed_7x7_data(pGBuffer, width, height, index, packed_7x7_G);
			
			//if ((i > 550 && i < 555) && j == 556)
			//{

				rb_out = BilinDemosaicRB(packed_7x7_raw, packed_7x7_G, algo_enable, mask, r_ratio, b_ratio, bayer_pattern);

				//*(pGBuffer + index) = out_G;

				//MalvaDemosaic(packed_5x5_raw, mask, r_ratio, b_ratio,bayer_pattern, out_rgb);

				r_out[index] = (Word16u)((rb_out >> 16) & 0XFFFF);
				b_out[index] = (Word16u)(rb_out & 0XFFFF);

				*(pRBuffer + index) = r_out[index];
				*(pBBuffer + index) = b_out[index];

			//}

		}

	}


	for (int j = 0; j < height; j++)
	{

		for (int i = 0; i < width; i++)

		{

			index = j * width + i;
			mask = (j % 2 << 1) + (i % 2);
			packed_7x7_data(pRBuffer, width, height, index, packed_7x7_R);
			packed_7x7_data(pGBuffer, width, height, index, packed_7x7_G);
			packed_7x7_data(pBBuffer, width, height, index, packed_7x7_B);
		
		//	g_out[index] = DynamicClampG(packed_7x7_R, packed_7x7_G, packed_7x7_B, algo_enable, mask, r_ratio, b_ratio, bayer_pattern);
			//rb_out = DynamicClampRB(packed_7x7_R, packed_7x7_G, packed_7x7_B, algo_enable, mask, r_ratio, b_ratio, bayer_pattern);
			//r_out[index] = (Word16u)((rb_out >> 16) & 0XFFFF);
			//b_out[index] = (Word16u)(rb_out & 0XFFFF);

		}
	}











	for (int j = 0; j < height; j++)
	{

		for (int i = 0; i < width; i++)

		{
			index = j * width + i;
			if ((i > 550 && i < 555) && j == 556)
			{
				//printf("r g b = %d\t%d\t%d\t\n", r_out[index] , g_out[index], b_out[index]);
			}


		}
	}
	free(pRBuffer);
	free(pGBuffer);
	free(pBBuffer);
	free(packed_7x7_R);
	free(packed_7x7_G);
	free(packed_7x7_B);
	free(packed_7x7_raw);

	

	
	return 0;
}