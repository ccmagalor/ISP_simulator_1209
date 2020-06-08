#include "blc.h"

int blc(Word16u* image, Word16u* image_out, int width, int height, int bayer_pattern, Blc_Cfg* param_in, module_cp* cp)
{
	int i;
	Word16u* r_buf = (Word16u*)malloc(width / 2 * height / 2 * sizeof(Word16u));
	Word16u* gr_buf = (Word16u*)malloc(width / 2 * height / 2 * sizeof(Word16u));
	Word16u* gb_buf = (Word16u*)malloc(width / 2 * height / 2 * sizeof(Word16u));
	Word16u* b_buf = (Word16u*)malloc(width / 2 * height / 2 * sizeof(Word16u));
	memset(r_buf, 0x0, width / 2 * height / 2 * sizeof(Word16u));
	memset(gr_buf, 0x0, width / 2 * height / 2 * sizeof(Word16u));
	memset(gb_buf, 0x0, width / 2 * height / 2 * sizeof(Word16u));
	memset(b_buf, 0x0, width / 2 * height / 2 * sizeof(Word16u));

	int r_offset, gr_offset, gb_offset, b_offset;
	r_offset = 64;
	gr_offset = 64;
	gb_offset = 64;
	b_offset = 64;
	separ_pixel(image, r_buf, gr_buf, gb_buf, b_buf, width, height, bayer_pattern);

	for (i = 0; i < (width * height) / 4; i++)
	{
		//if (i < 3)
		//{
		//	LOGE("//---------------INPUT----------------//");
		//	LOGE("r_buf[%d] = %d", i, r_buf[i]);
		//	LOGE("gr_buf[%d] = %d", i, gr_buf[i]);
		//	LOGE("gb_buf[%d] = %d", i, gb_buf[i]);
		//	LOGE("b_buf[%d] = %d", i, b_buf[i]);
		//}
		r_buf[i] = r_buf[i] < r_offset?0: r_buf[i] - r_offset;
		gr_buf[i] = gr_buf[i] < gr_offset ? 0 : gr_buf[i] - gr_offset;
		gb_buf[i] = gb_buf[i] < gb_offset ? 0 : gb_buf[i] - gb_offset;
		b_buf[i] = b_buf[i] < b_offset ? 0 : b_buf[i] - b_offset;
	
		//r_buf[i] = Cclamp_s((Word32)r_buf[i],10,0,1024,10,cp->clamp_s);
		//gr_buf[i] = Cclamp_s((Word32)gr_buf[i], 10, 0, 1024, 10, cp->clamp_s);
		//gb_buf[i] = Cclamp_s((Word32)gb_buf[i], 10, 0, 1024, 10, cp->clamp_s);
		//b_buf[i] = Cclamp_s((Word32)b_buf[i], 10, 0, 1024, 10, cp->clamp_s);

		//if (i < 3)
		//{
		//	LOGE("//---------------OUTPUT----------------//");
		//	LOGE("r_buf[%d] = %d",i,r_buf[i]);
		//	LOGE("gr_buf[%d] = %d", i,gr_buf[i]);
		//	LOGE("gb_buf[%d] = %d", i,gb_buf[i]);
		//	LOGE("b_buf[%d] = %d", i,b_buf[i]);
		//}

	}

	combo_pixel( r_buf, gr_buf, gb_buf, b_buf, image_out, width, height, bayer_pattern);


	free(r_buf);
	free(gr_buf);
	free(gb_buf);
	free(b_buf);

	return 0;
}