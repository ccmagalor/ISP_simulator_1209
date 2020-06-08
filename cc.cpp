#include"cc.h"
int cc(Word16u* r_in, Word16u* g_in, Word16u* b_in,
	Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height, Cc_Cfg* param_in, module_cp* cp)
{
	LOGE("CC:WIDTH = %d,HEIGHT= %d", width, height);
	double r_temp, g_temp, b_temp;
	for (int i = 0; i < width * height; i++)
	{
		r_temp = 1.625 * r_in[i] - 0.7745 * g_in[i] + 0.15 * b_in[i];
		g_temp = -0.099 * r_in[i] + 1.10174 * g_in[i] - 0.00271 * b_in[i];
		b_temp = 0.148267 * r_in[i] - 0.95620 * g_in[i] + 1.80793 * b_in[i];
		r_out[i] = r_temp < 0 ? 0 : r_temp>1023 ? 1023 : r_temp;
		g_out[i] = g_temp < 0 ? 0 : g_temp>1023 ? 1023 : g_temp;
		b_out[i] = b_temp < 0 ? 0 : b_temp>1023 ? 1023 : b_temp;
	}
	return 0;
}