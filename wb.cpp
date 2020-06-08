#include"wb.h"

int wb(Word16u* r_in, Word16u* g_in, Word16u* b_in, Wb_param_cfg* param_in, int width, int height)
{

	float r_ratio;
	float b_ratio;
	float g_ratio;
	r_ratio = param_in->r_gain;

	g_ratio = param_in->g_gain;
	b_ratio = param_in->b_gain;

	LOGE("r_ratio = %f,g_ratio = %f,b_ratio = %f", r_ratio, g_ratio, b_ratio);

	for (int i = 0; i < width * height; i++)
	{
		r_in[i] = int(r_ratio * r_in[i]);
		g_in[i] = int(r_ratio * g_in[i]);
		b_in[i] = int(r_ratio * b_in[i]);

		r_in[i] = r_in[i] > 1023 ? 1023 : r_in[i];
		g_in[i] = g_in[i] > 1023 ? 1023 : r_in[i];
		b_in[i] = b_in[i] > 1023 ? 1023 : r_in[i];

	}
	return 0;
}
