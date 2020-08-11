#include"cac.h"
/*
Chromatic aberration is an effect resulting from optical dispersion in which a lens fails to focus the light of all colors to the same convergence point. 
Chromatic aberration is refers to undesirable "fringers" of color along boundaries that separate the dark and bright regions, especially saturation regions.
It is becoming a more critical problem as digital cameras are becoming smaller,while the image's resolution is increasing.
It causes in unacceptable image quality in professional photography.Chromatic aberration offer manifests itself as color(purple or blue) thick lines.

Chromatic artifacts refer to the color artifacts resulting from under-Nyquist sampling and imperfect processing of the image sensor pipeling,
such as false correction of Bad Pixel Correctiong and imperfect interpolation of Demosaic. In most cases, chromatic artifacts manifests themselves as color spots and
color thin lines.

resolution:
1.photoShop and PTLens
2.improvement of lens design
3.software solution: pre-calibration the color channels for optimal focus,magnification and shift.


Algrithm
1.downscale to yuv420

for pixel P, detectin map R is denoted as follows:
R = 2: P is detected as color aberration
R = 1£ºP is detected as color artifacts
R = 0: else

color aberration and color artifacts should be located at or colse to the following regions:
1. Luma saturation regions
2. High-contrast luma spots/lines
3. Colorful regions
4. High-contrast color spots/lines


*/

void cac(Word8u* y_in, Word8u* u_in, Word8u* v_in, Word8u* r_out, Word8u* g_out, Word8u* b_out,
	int width, int height, Cst_Cfg* param_in, module_cp* cp)
{
	Word8u* packed_5x5_Y = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	Word8u* packed_3x3_Y = (Word8u*)calloc(3 * 3, sizeof(Word8u));
	Word8u* packed_5x5_Cb = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	Word8u* packed_5x5_Cr = (Word8u*)calloc(5 * 5, sizeof(Word8u));
	int index, mask;

	int YbufferSize = width * height / 4;

	Word8u* pYBuffer = (Word8u*)(malloc(YbufferSize * sizeof(Word8u)));

	memset(pYBuffer, 0, YbufferSize * sizeof(Word8u));


	Word8u* pYsBuffer = (Word8u*)(malloc(YbufferSize * sizeof(Word8u)));

	memset(pYsBuffer, 0, YbufferSize * sizeof(Word8u));


	int CbufferSize = width * height / 4;

	Word8u* pCbBuffer = (Word8u*)(malloc(CbufferSize * sizeof(Word8u)));

	memset(pCbBuffer, 0, CbufferSize * sizeof(Word8u));

	Word8u* pCrBuffer = (Word8u*)(malloc(CbufferSize * sizeof(Word8u)));

	memset(pCrBuffer, 0, CbufferSize * sizeof(Word8u));


	int RbufferSize = width * height / 4;

	Word8u* pRBuffer = (Word8u*)(malloc(RbufferSize * sizeof(Word8u)));

	memset(pRBuffer, 0, RbufferSize * sizeof(Word8u));


	int RsbufferSize = width * height;

	Word8u* pRsBuffer = (Word8u*)(malloc(RsbufferSize * sizeof(Word8u)));

	memset(pRsBuffer, 0, RsbufferSize * sizeof(Word8u));


	int index_1, index_2, index_3, index_4;
	int y_spot_thr = 220;
	int y_saturation_thr = 10;

	int c_spot_thr = 10;
	int c_saturation_thr = 5;
	for (int j = 0; j < height / 2; j++)
	{

		for (int i = 0; i < width / 2; i++)

		{
			index = j * width / 2 + i;
			index_1 = (j * width + i) * 2;
			index_2 = index_1 + 1;

			index_3 = index_1 + width;
			index_4 = index_2 + width;

			pYBuffer[index] = y_in[index_1] + y_in[index_2] + y_in[index_3] + y_in[index_4];

		}
	}


	for (int j = 0; j < height / 2; j++)
	{

		for (int i = 0; i < width / 2; i++)

		{

			index = j * width / 2 + i;
			mask = (j % 2 << 1) + (i % 2);

			packed_5x5_data_8u(pYBuffer, width, height, index, packed_5x5_Y);

			int filter_y_h1 = packed_5x5_Y[12];

			int filter_y_h2 = packed_5x5_Y[6] + packed_5x5_Y[7] + packed_5x5_Y[8] +
				packed_5x5_Y[11] + packed_5x5_Y[13] +
				packed_5x5_Y[16] + packed_5x5_Y[17] + packed_5x5_Y[18];

			int filter_y_h3 = packed_5x5_Y[0] + packed_5x5_Y[1] + packed_5x5_Y[2] + packed_5x5_Y[3] + packed_5x5_Y[4] +
				packed_5x5_Y[5] + packed_5x5_Y[9] +
				packed_5x5_Y[10] + packed_5x5_Y[14] +
				packed_5x5_Y[15] + packed_5x5_Y[19] +
				packed_5x5_Y[20] + packed_5x5_Y[21] + packed_5x5_Y[22] + packed_5x5_Y[23] + packed_5x5_Y[24];



			//normalize

			int y = filter_y_h1 / 4;

			float y1_s = y * (filter_y_h1 / 4);

			float y2_s = y * (filter_y_h2 / 28);

			float y3_s = y * (filter_y_h1 / 32);


			//relative difference

			float y12 = (y1_s - y2_s) / y2_s;


			float y13 = (y1_s - y3_s) / y3_s;


			float y_s_max = MAX(y12, y13);

			pYsBuffer[index] = y_s_max;
		}
	}

	for (int j = 0; j < height / 2; j++)
	{

		for (int i = 0; i < width / 2; i++)

		{

			index = j * width / 2 + i;
			mask = (j % 2 << 1) + (i % 2);

			packed_5x5_data_8u(pYBuffer, width, height, index, packed_5x5_Y);

			packed_3x3_data_8u(pYsBuffer, width, height, index, packed_3x3_Y);

			//int y0 = max5x5(packed_5x5_Y);
			//int y0_s = max3x3(packed_3x3_Y);
			int y0 = 0;
			int y0_s = 0;

			int y_spot_thr = 220;
			int y_saturation_thr = 10;
			if (y0_s > y_spot_thr)
				pRBuffer[index] = 1;
			if (y0 > y_saturation_thr)
				pRBuffer[index] = 2;
		}
	}





	for (int j = 0; j < height / 2; j++)
	{

		for (int i = 0; i < width / 2; i++)

		{

			index = j * width / 2 + i;
			mask = (j % 2 << 1) + (i % 2);

			packed_5x5_data_8u(u_in, width, height, index, packed_5x5_Cb);
			packed_5x5_data_8u(v_in, width, height, index, packed_5x5_Cr);

			int filter_cb_central = packed_5x5_Y[12];

			int filter_cb_middle = packed_5x5_Y[6] + packed_5x5_Y[7] + packed_5x5_Y[8] +
				packed_5x5_Y[11] + packed_5x5_Y[13] +
				packed_5x5_Y[16] + packed_5x5_Y[17] + packed_5x5_Y[18];
			filter_cb_middle = filter_cb_middle / 8;

			int filter_cb_peripheral = packed_5x5_Y[0] + packed_5x5_Y[1] + packed_5x5_Y[2] + packed_5x5_Y[3] + packed_5x5_Y[4] +
				packed_5x5_Y[5] + packed_5x5_Y[9] +
				packed_5x5_Y[10] + packed_5x5_Y[14] +
				packed_5x5_Y[15] + packed_5x5_Y[19] +
				packed_5x5_Y[20] + packed_5x5_Y[21] + packed_5x5_Y[22] + packed_5x5_Y[23] + packed_5x5_Y[24];
			filter_cb_peripheral = filter_cb_peripheral / 16;

			int filter_cb_h4 = filter_cb_central - filter_cb_middle;
		
			int filter_cb_h5 = filter_cb_central + filter_cb_middle - filter_cb_peripheral;

		


			int filter_cr_central = packed_5x5_Y[12];

			int filter_cr_middle = packed_5x5_Y[6] + packed_5x5_Y[7] + packed_5x5_Y[8] +
				packed_5x5_Y[11] + packed_5x5_Y[13] +
				packed_5x5_Y[16] + packed_5x5_Y[17] + packed_5x5_Y[18];
			filter_cr_middle = filter_cr_middle / 8;

			int filter_cr_peripheral = packed_5x5_Y[0] + packed_5x5_Y[1] + packed_5x5_Y[2] + packed_5x5_Y[3] + packed_5x5_Y[4] +
				packed_5x5_Y[5] + packed_5x5_Y[9] +
				packed_5x5_Y[10] + packed_5x5_Y[14] +
				packed_5x5_Y[15] + packed_5x5_Y[19] +
				packed_5x5_Y[20] + packed_5x5_Y[21] + packed_5x5_Y[22] + packed_5x5_Y[23] + packed_5x5_Y[24];
			filter_cr_peripheral = filter_cr_peripheral / 16;

			int filter_cr_h4 = filter_cr_central - filter_cr_middle;

			int filter_cr_h5 = filter_cr_central + filter_cr_middle - filter_cr_peripheral;


			filter_cb_h4 = ABS(filter_cb_h4);
			filter_cb_h5 = ABS(filter_cb_h5);
			filter_cr_h4 = ABS(filter_cr_h4);
			filter_cr_h5 = ABS(filter_cr_h5);

			int filter_c_max = MAX(MAX(filter_cb_h4, filter_cb_h5),MAX(filter_cb_h4, filter_cb_h5));

			if (filter_c_max < c_saturation_thr)
				pRBuffer[index] = 0;

			if((ABS(filter_cr_central-128)<c_spot_thr)&& (ABS(filter_cr_central - 128) < c_spot_thr))
				pRBuffer[index] = 0;
		}
	}



	int index_rs, index_r;
	for (int j = 0; j < height; j++)
	{

		for (int i = 0; i < width; i++)

		{
			index_rs = j * width + i;
			index_r = j / 2 * width / 2 + i / 2;

			pRsBuffer[index_rs] = pRBuffer[index_r];

		}
	}


	//correction












}

