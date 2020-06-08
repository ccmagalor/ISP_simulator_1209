#include "isp_util.h"

int convertMIPItoRAW(Word8u* mipiRAW, Word16u* RAW, unsigned int w, unsigned int h)
{
	int i, j, k;
	int index_raw;
	int index_mipi;
	//for (i = 0; i < w * h * 2 / 8;i++)
	LOGE("width = %d", w);
	LOGE("height = %d", h);

	

	int mipi_w = ((((w / 4) * 5) / 16) + 1) * 16;
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			index_raw = j * w + i;
			//index_mipi = ((index_raw / 4) * 5) + index_raw % 4;
			index_mipi = j * mipi_w + ((i / 4) * 5) + i % 4;
			if (index_raw % 4 == 0)
			{
				RAW[index_raw] = (((Word16u)(mipiRAW[index_mipi])) << 2) + (Word16u)(mipiRAW[j * mipi_w + ((i / 4) * 5) + 4] & 0x3);
			}
			else if (index_raw % 4 == 1)
			{
				RAW[index_raw] = (((Word16u)(mipiRAW[index_mipi])) << 2) + (Word16u)(mipiRAW[j * mipi_w + ((i / 4) * 5) + 4] >> 2 & 0x3);
			}
			else if (index_raw % 4 == 2)
			{
				RAW[index_raw] = (((Word16u)(mipiRAW[index_mipi])) << 2 )+ (Word16u)(mipiRAW[j * mipi_w + ((i / 4) * 5) + 4] >> 4 & 0x3);
			}
			else if (index_raw % 4 == 3)
			{
				RAW[index_raw] = (((Word16u)(mipiRAW[index_mipi])) << 2) + (Word16u)(mipiRAW[j * mipi_w + ((i / 4) * 5) + 4] >> 6 & 0x3);
			}
			//if (j == 0 && i > w-16)
			if (index_raw>(2*w-16) && index_raw < (2*w + 16))
			{
				//LOGE("H= %d,%d",i, index_raw % 4);
				//LOGE("MIPI_IDX5 = 0x%x", mipiRAW[(index_raw / 4) * 5 + 4]);
			//	LOGE("index_raw = \t%d,index_mipi=\t%d,index_mipi5=/t%d ,MIPI_IDX5 = \t0x%x,MIPI = \t0x%x, RAW = \t0x%x", index_raw, index_mipi, j * mipi_w + ((i / 4) * 5) + 4,  mipiRAW[j * mipi_w + ((i / 4) * 5) + 4], mipiRAW[index_mipi], RAW[index_raw]);
			}
			if (j == 1 && i < 24)
			{
				//LOGE("H= %d,%d",i, index_raw % 4);
				//LOGE("MIPI_IDX5 = 0x%x", mipiRAW[(index_raw / 4) * 5 + 4]);
				//LOGE("index_raw = \t%d,\t%d,MIPI_IDX5 = \t0x%x,MIPI = \t0x%x, RAW = \t0x%x", index_raw,  index_raw % 4, mipiRAW[(index_raw / 4) * 5 + 4],mipiRAW[index_mipi], RAW[index_raw]);
			}


		}
	}
	//for (i = 0; i < w * h * 2 / 8; i++)
	//{
	//	int j = i * 4;
	//	int k = i * 5;
	//	//LOGE("testdata1 = 0x%x", *(mipiRAW+i));
	//	//LOGE("testdata2 = 0x%x", static_cast<uint16_t>(*(mipiRAW + k + 0)));
	//	*(RAW + j + 0) = (static_cast<Word16u>(*(mipiRAW + k + 0)) << 2) + ((static_cast<Word16u>(*(mipiRAW + k + 4)) >> 0) & 0x3);
	//	*(RAW + j + 1) = (static_cast<Word16u>(*(mipiRAW + k + 1)) << 2) + ((static_cast<Word16u>(*(mipiRAW + k + 4)) >> 2) & 0x3);
	//	*(RAW + j + 2) = (static_cast<Word16u>(*(mipiRAW + k + 2)) << 2) + ((static_cast<Word16u>(*(mipiRAW + k + 4)) >> 4) & 0x3);
	//	*(RAW + j + 3) = (static_cast<Word16u>(*(mipiRAW + k + 3)) << 2) + ((static_cast<Word16u>(*(mipiRAW + k + 4)) >> 6) & 0x3);
	//	//	*(RAW + j + 0) = 12;
	//	//	*(RAW + j + 1) = 12;
	//	//	*(RAW + j + 2) = 12;
	//	//	*(RAW + j + 3) = 12;
	//
	//}
	int width = w;
	int height = h;
	//for (int i = 0; i < width; i++)
	//{
	//	for (int j = 0; j < height; j++)
	//	{
	//		if (((j % 400 < 200) && (i % 400 < 200)) || ((j % 400 > 200) && (i % 400 > 200)))
	//		{
	//			RAW[j * width + i] = 8;
	//	
	//		}
	//		else
	//		{
	//			RAW[j * width + i] = 240 * 4;
	//
	//		}
	//
	//
	//	}
	//}


	return 1;
}

int readBayerImage(char* cfgFileName, Word16u* image, unsigned int w, unsigned int h, int inputBit)
{
	FILE* file;
	unsigned long fileLen;
	srand(100);
	int e = 14 - inputBit;

	//Open file
	fopen_s(&file, cfgFileName, "rb");

	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", cfgFileName);
		return 0;
	}

	//Get file length
	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);
	fseek(file, 0, SEEK_SET);

	//Read file contents intu buffer
	fread(image, sizeof(short), w * h, file);
	fclose(file);

	int random = 1;
	for (unsigned int i = 0; i < w * h; i++) {
		image[i] = image[i] << e;
		if (random) image[i] = image[i] + rand() % (1 << e);
	}

	return 1;
}

int separ_pixel(Word16u* image, Word16u* r_buffer, Word16u* gr_buffer, Word16u* gb_buffer, Word16u* b_buffer, int width, int height, int bayer_pattern)
{

	Word16u* bf_image;
	Word16u mask = 0xFFFF;
	bf_image = image;
	unsigned int row_idx = 0, col_idx = 0, pix_idx = 0;
	unsigned int ch0_idx = 0, ch1_idx = 0, ch2_idx = 0, ch3_idx = 0;
	for (row_idx = 0; row_idx < (unsigned int)height; row_idx++)
	{
		for (col_idx = 0; col_idx < (unsigned int)width; col_idx++)
		{
			pix_idx = (row_idx * width) + col_idx;
			switch (bayer_pattern) {
			case RGGB_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					r_buffer[ch0_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					gr_buffer[ch1_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					gb_buffer[ch2_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					b_buffer[ch3_idx++] = bf_image[pix_idx] & mask;
				break;
			case GRBG_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					gr_buffer[ch0_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					r_buffer[ch1_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					b_buffer[ch2_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					gb_buffer[ch3_idx++] = bf_image[pix_idx] & mask;
				break;
			case BGGR_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					b_buffer[ch0_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					gb_buffer[ch1_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					gr_buffer[ch2_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					r_buffer[ch3_idx++] = bf_image[pix_idx] & mask;
				break;
			case GBRG_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					gb_buffer[ch0_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					b_buffer[ch1_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					r_buffer[ch2_idx++] = bf_image[pix_idx] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					gr_buffer[ch3_idx++] = bf_image[pix_idx] & mask;
				break;

			}

		}

	}
	return 0;
}

int combo_pixel(Word16u* r_buffer, Word16u* gr_buffer, Word16u* gb_buffer, Word16u* b_buffer, Word16u* image, int width, int height, int bayer_pattern)
{

	Word16u* bf_image;
	Word16u mask = 0xFFFF;
	bf_image = image;
	unsigned int row_idx = 0, col_idx = 0, pix_idx = 0;
	unsigned int ch0_idx = 0, ch1_idx = 0, ch2_idx = 0, ch3_idx = 0;
	for (row_idx = 0; row_idx < (unsigned int)height; row_idx++)
	{
		for (col_idx = 0; col_idx < (unsigned int)width; col_idx++)
		{
			pix_idx = (row_idx * width) + col_idx;
			switch (bayer_pattern) {
			case RGGB_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					bf_image[pix_idx]= r_buffer[ch0_idx++] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					bf_image[pix_idx] = gr_buffer[ch1_idx++] & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = gb_buffer[ch2_idx++] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = b_buffer[ch3_idx++] & mask;
				break;
			case GRBG_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					bf_image[pix_idx] = gr_buffer[ch0_idx++]  & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					bf_image[pix_idx] = r_buffer[ch1_idx++]  & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = b_buffer[ch2_idx++]& mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = gb_buffer[ch3_idx++]  & mask;
				break;
			case BGGR_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					bf_image[pix_idx] = b_buffer[ch0_idx++]  & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					bf_image[pix_idx] = gb_buffer[ch1_idx++]  & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = gr_buffer[ch2_idx++]  & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = r_buffer[ch3_idx++]  & mask;
				break;
			case GBRG_PATTERN:
				if (((col_idx % 2) == 0) && ((row_idx % 2) == 0))
					bf_image[pix_idx] = gb_buffer[ch0_idx++] & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 0))
					bf_image[pix_idx] = b_buffer[ch1_idx++] & mask;
				else if (((col_idx % 2) == 0) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = r_buffer[ch2_idx++]  & mask;
				else if (((col_idx % 2) == 1) && ((row_idx % 2) == 1))
					bf_image[pix_idx] = gr_buffer[ch3_idx++]  & mask;
				break;

			}

		}

	}
	return 0;
}

void copy_1border(Word16u* in_data, int width, int height, int size, Word16u* out_data)
{
	int i, j;
	if (size == 1)
	{
		for (i = 0; i < width; i++)
		{
			out_data[i] = in_data[i];									//border H
			out_data[width + i] = in_data[width * (height - 1) + i];    //border B
		}
		for (j = 0; j < height; j++)
		{
			out_data[2 * width + j] = in_data[j * width];                         //border L
			out_data[2 * width + height + j] = in_data[(j + 1) * width - 1];	   //border R
		}
	}
	return;
}


void packed_3x3_data(Word8u* in_data, int width, int height, int index, Word8u* out_data)
{


	int i,j;
	int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;

	int h_offset, b_offset, l_offset, r_offset;

	int idx0, idx1, idx2, idx3, idx4, idx5, idx6, idx7, idx8;


	idx4 = index;

	if (row == 0)
	{
		h_offset = 0;
		b_offset = width;
	}
	else if (row == (height - 1))
	{
		h_offset = -width;
		b_offset = 0;
	}
	else
	{
		h_offset = -width;
		b_offset = width;
	}

	if (col == 0)
	{
		l_offset = 0;
		r_offset = 1;
	}
	else if (col = (width - 1))
	{
		l_offset = -1;
		r_offset = 0;
	}
	else
	{
		l_offset = -1;
		r_offset = 1;
	}



	idx0 = idx4 + h_offset + l_offset;
	idx1 = idx4 + h_offset;
	idx2 = idx4 + h_offset + r_offset;
	idx3 = idx4 + l_offset;
	idx5 = idx4 + r_offset;
	idx6 = idx4 - l_offset + b_offset;
	idx7 = idx4 + b_offset;
	idx8 = idx4 + r_offset + b_offset;

	out_data[0] = in_data[idx0];
	out_data[1] = in_data[idx1];
	out_data[2] = in_data[idx2];
	out_data[3] = in_data[idx3];
	out_data[4] = in_data[idx4];
	out_data[5] = in_data[idx5];
	out_data[6] = in_data[idx6];
	out_data[7] = in_data[idx7];
	out_data[8] = in_data[idx8];


}

void packed_5x5_data(Word16u* in_data, int width, int height, int index, Word16u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;

	int h_offset, b_offset, l_offset, r_offset;

	int idx0, idx1, idx2, idx3, idx4, idx5, idx6, idx7, idx8, idx9, idx10, idx11, idx12, idx13, idx14, idx15, idx16, idx17, idx18, idx19, idx20, idx21, idx22, idx23, idx24;


	int h0_offset, h1_offset;
	int l0_offset, l1_offset;
	int r3_offset, r4_offset;
	int b3_offset, b4_offset;
	idx12 = index;
	h0_offset = 0 - (2 * width);
	h1_offset = 0 - width;
	l0_offset = 0 - 2;
	l1_offset = 0 - 1;
	r3_offset = 1;
	r4_offset = 2;
	b3_offset = width;
	b4_offset = 2 * width;


	if (row == 0)
	{
		h0_offset = h1_offset = 0;
	}
	else if (row == 1)
	{
		h0_offset = h1_offset;
	}
	else if (row == (height - 2))
	{
		b4_offset = b3_offset;
	}
	else if (row == (height - 1))
	{
		b3_offset = b4_offset = 0;
	}

	if (col == 0)
	{
		l0_offset = l1_offset = 0;
	}
	else if (col == 1)
	{
		l0_offset = l1_offset;
	}
	else if (col == (width - 2))
	{
		r4_offset = r3_offset;

	}
	else if (col == (width - 1))
	{
		r4_offset = r3_offset = 0;
	}

	idx0 = idx12 + h0_offset + l0_offset;
	idx1 = idx12 + h0_offset + l1_offset;
	idx2 = idx12 + h0_offset;
	idx3 = idx12 + h0_offset + r3_offset;
	idx4 = idx12 + h0_offset + r4_offset;

	idx5 = idx12 + h1_offset + l0_offset;
	idx6 = idx12 + h1_offset + l1_offset;
	idx7 = idx12 + h1_offset;
	idx8 = idx12 + h1_offset + r3_offset;
	idx9 = idx12 + h1_offset + r4_offset;

	idx10 = idx12 + l0_offset;
	idx11 = idx12 + l1_offset;
	idx13 = idx12 + r3_offset;
	idx14 = idx12 + r4_offset;

	idx15 = idx12 + b3_offset + l0_offset;
	idx16 = idx12 + b3_offset + l1_offset;
	idx17 = idx12 + b3_offset;
	idx18 = idx12 + b3_offset + r3_offset;
	idx19 = idx12 + b3_offset + r4_offset;

	idx20 = idx12 + b4_offset + l0_offset;
	idx21 = idx12 + b4_offset + l1_offset;
	idx22 = idx12 + b4_offset;
	idx23 = idx12 + b4_offset + r3_offset;
	idx24 = idx12 + b4_offset + r4_offset;

	out_data[0] = in_data[idx0];
	out_data[1] = in_data[idx1];
	out_data[2] = in_data[idx2];
	out_data[3] = in_data[idx3];
	out_data[4] = in_data[idx4];
	out_data[5] = in_data[idx5];
	out_data[6] = in_data[idx6];
	out_data[7] = in_data[idx7];
	out_data[8] = in_data[idx8];
	out_data[9] = in_data[idx9];

	out_data[10] = in_data[idx10];
	out_data[11] = in_data[idx11];
	out_data[12] = in_data[idx12];
	out_data[13] = in_data[idx13];
	out_data[14] = in_data[idx14];
	out_data[15] = in_data[idx15];
	out_data[16] = in_data[idx16];
	out_data[17] = in_data[idx17];
	out_data[18] = in_data[idx18];
	out_data[19] = in_data[idx19];

	out_data[20] = in_data[idx20];
	out_data[21] = in_data[idx21];
	out_data[22] = in_data[idx22];
	out_data[23] = in_data[idx23];
	out_data[24] = in_data[idx24];
//	if ((index == 0) || (index = 1) || (index == width + 1))
	//if (index ==37254)
	//{
	//	LOGE("/////---------central pix idx = %d--------------/////", idx12);
	//	LOGE("%2d %2d %2d %2d %2d", idx0, idx1, idx2, idx3, idx4);
	//	LOGE("%2d %2d %2d %2d %2d", idx5, idx6, idx7, idx8, idx9);
	//	LOGE("%2d %2d %2d %2d %2d", idx10, idx11, idx12, idx13, idx14);
	//	LOGE("%2d %2d %2d %2d %2d", idx15, idx16, idx17, idx18, idx19);
	//	LOGE("%2d %2d %2d %2d %2d", idx20, idx21, idx22, idx23, idx24);
	//	LOGE("/////---------data array = %d,col = %d,row = %d--------------/////", idx12,col,row);
	//	LOGE("%2d %2d %2d %2d %2d", in_data[idx0], in_data[idx1], in_data[idx2], in_data[idx3], in_data[idx4]);
	//	LOGE("%2d %2d %2d %2d %2d", in_data[idx5], in_data[idx6], in_data[idx7], in_data[idx8], in_data[idx9]);
	//	LOGE("%2d %2d %2d %2d %2d", in_data[idx10], in_data[idx11], in_data[idx12], in_data[idx13], in_data[idx14]);
	//	LOGE("%2d %2d %2d %2d %2d", in_data[idx15], in_data[idx16], in_data[idx17], in_data[idx18], in_data[idx19]);
	//	LOGE("%2d %2d %2d %2d %2d", in_data[idx20], in_data[idx21], in_data[idx22], in_data[idx23], in_data[idx24]);
	//}
}



void packed_5x5_data_8u(Word8u* in_data, int width, int height, int index, Word8u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;

	int h_offset, b_offset, l_offset, r_offset;

	int idx0, idx1, idx2, idx3, idx4, idx5, idx6, idx7, idx8, idx9, idx10, idx11, idx12, idx13, idx14, idx15, idx16, idx17, idx18, idx19, idx20, idx21, idx22, idx23, idx24;


	int h0_offset, h1_offset;
	int l0_offset, l1_offset;
	int r3_offset, r4_offset;
	int b3_offset, b4_offset;
	idx12 = index;
	h0_offset = 0 - (2 * width);
	h1_offset = 0 - width;
	l0_offset = 0 - 2;
	l1_offset = 0 - 1;
	r3_offset = 1;
	r4_offset = 2;
	b3_offset = width;
	b4_offset = 2 * width;


	if (row == 0)
	{
		h0_offset = h1_offset = 0;
	}
	else if (row == 1)
	{
		h0_offset = h1_offset;
	}
	else if (row == (height - 2))
	{
		b4_offset = b3_offset;
	}
	else if (row == (height - 1))
	{
		b3_offset = b4_offset = 0;
	}

	if (col == 0)
	{
		l0_offset = l1_offset = 0;
	}
	else if (col == 1)
	{
		l0_offset = l1_offset;
	}
	else if (col == (width - 2))
	{
		r4_offset = r3_offset;

	}
	else if (col == (width - 1))
	{
		r4_offset = r3_offset = 0;
	}

	idx0 = idx12 + h0_offset + l0_offset;
	idx1 = idx12 + h0_offset + l1_offset;
	idx2 = idx12 + h0_offset;
	idx3 = idx12 + h0_offset + r3_offset;
	idx4 = idx12 + h0_offset + r4_offset;

	idx5 = idx12 + h1_offset + l0_offset;
	idx6 = idx12 + h1_offset + l1_offset;
	idx7 = idx12 + h1_offset;
	idx8 = idx12 + h1_offset + r3_offset;
	idx9 = idx12 + h1_offset + r4_offset;

	idx10 = idx12 + l0_offset;
	idx11 = idx12 + l1_offset;
	idx13 = idx12 + r3_offset;
	idx14 = idx12 + r4_offset;

	idx15 = idx12 + b3_offset + l0_offset;
	idx16 = idx12 + b3_offset + l1_offset;
	idx17 = idx12 + b3_offset;
	idx18 = idx12 + b3_offset + r3_offset;
	idx19 = idx12 + b3_offset + r4_offset;

	idx20 = idx12 + b4_offset + l0_offset;
	idx21 = idx12 + b4_offset + l1_offset;
	idx22 = idx12 + b4_offset;
	idx23 = idx12 + b4_offset + r3_offset;
	idx24 = idx12 + b4_offset + r4_offset;

	out_data[0] = in_data[idx0];
	out_data[1] = in_data[idx1];
	out_data[2] = in_data[idx2];
	out_data[3] = in_data[idx3];
	out_data[4] = in_data[idx4];
	out_data[5] = in_data[idx5];
	out_data[6] = in_data[idx6];
	out_data[7] = in_data[idx7];
	out_data[8] = in_data[idx8];
	out_data[9] = in_data[idx9];

	out_data[10] = in_data[idx10];
	out_data[11] = in_data[idx11];
	out_data[12] = in_data[idx12];
	out_data[13] = in_data[idx13];
	out_data[14] = in_data[idx14];
	out_data[15] = in_data[idx15];
	out_data[16] = in_data[idx16];
	out_data[17] = in_data[idx17];
	out_data[18] = in_data[idx18];
	out_data[19] = in_data[idx19];

	out_data[20] = in_data[idx20];
	out_data[21] = in_data[idx21];
	out_data[22] = in_data[idx22];
	out_data[23] = in_data[idx23];
	out_data[24] = in_data[idx24];
	//	if ((index == 0) || (index = 1) || (index == width + 1))
		//if (index ==37254)
		//{
		//	LOGE("/////---------central pix idx = %d--------------/////", idx12);
		//	LOGE("%2d %2d %2d %2d %2d", idx0, idx1, idx2, idx3, idx4);
		//	LOGE("%2d %2d %2d %2d %2d", idx5, idx6, idx7, idx8, idx9);
		//	LOGE("%2d %2d %2d %2d %2d", idx10, idx11, idx12, idx13, idx14);
		//	LOGE("%2d %2d %2d %2d %2d", idx15, idx16, idx17, idx18, idx19);
		//	LOGE("%2d %2d %2d %2d %2d", idx20, idx21, idx22, idx23, idx24);
		//	LOGE("/////---------data array = %d,col = %d,row = %d--------------/////", idx12,col,row);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx0], in_data[idx1], in_data[idx2], in_data[idx3], in_data[idx4]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx5], in_data[idx6], in_data[idx7], in_data[idx8], in_data[idx9]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx10], in_data[idx11], in_data[idx12], in_data[idx13], in_data[idx14]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx15], in_data[idx16], in_data[idx17], in_data[idx18], in_data[idx19]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx20], in_data[idx21], in_data[idx22], in_data[idx23], in_data[idx24]);
		//}
}


void packed_7x7_data(Word16u* in_data, int width, int height, int index, Word16u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	//int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;

	

	int idx0, idx1, idx2, idx3, idx4, idx5, idx6, 
		idx7, idx8, idx9, idx10, idx11, idx12, idx13,
		idx14, idx15, idx16, idx17, idx18, idx19, idx20,
		idx21, idx22, idx23, idx24, idx25, idx26, idx27, 
		idx28, idx29, idx30, idx31, idx32, idx33, idx34, 
		idx35, idx36, idx37, idx38, idx39, idx40, idx41, 
		idx42, idx43, idx44, idx45, idx46, idx47, idx48;


	int h0_offset, h1_offset, h2_offset;
	int l0_offset, l1_offset, l2_offset;
	int r4_offset, r5_offset, r6_offset;
	int b4_offset, b5_offset, b6_offset;


	idx24 = index;
	h0_offset = 0 - (3 * width);
	h1_offset = 0 - (2*width);
	h2_offset = 0 - width;
	b4_offset = width;
	b5_offset = 2 * width;
	b6_offset = 3 * width;


	l0_offset = -3;
	l1_offset = -2;
	l2_offset = -1;
	r4_offset = 1;
	r5_offset = 2;
	r6_offset = 3;



	if (row == 0)
	{
		h0_offset = h1_offset = h2_offset = 0;
	}
	else if (row == 1)
	{
		h0_offset = h1_offset = h2_offset;
	}
	else if (row == 2)
	{
		h0_offset = h1_offset;;
	}
	else if (row == (height - 3))
	{
		b6_offset = b5_offset;
	}
	else if (row == (height - 2))
	{
		b6_offset = b5_offset = b4_offset;
	}
	else if (row == (height - 1))
	{
		b6_offset = b5_offset = b4_offset = 0;
	}

	if (col == 0)
	{
		l0_offset = l1_offset = l2_offset=0;
	}
	else if (col == 1)
	{
		l0_offset = l1_offset = l2_offset;
	}
	else if (col == 2)
	{
		l0_offset = l1_offset;
	}
	else if (col == (width - 3))
	{
		r6_offset = r5_offset;

	}
	else if (col == (width - 2))
	{
		r6_offset = r5_offset = r4_offset;

	}
	else if (col == (width - 1))
	{
		r6_offset = r5_offset = r4_offset = 0;
	}

	idx0 = idx24 + h0_offset + l0_offset;
	idx1 = idx24 + h0_offset + l1_offset;
	idx2 = idx24 + h0_offset + l2_offset;
	idx3 = idx24 + h0_offset;
	idx4 = idx24 + h0_offset + r4_offset;
	idx5 = idx24 + h0_offset + r5_offset;
	idx6 = idx24 + h0_offset + r6_offset;

	idx7 = idx24 + h1_offset + l0_offset;
	idx8 = idx24 + h1_offset + l1_offset;
	idx9 = idx24 + h1_offset + l2_offset;
	idx10 = idx24 + h1_offset;
	idx11 = idx24 + h1_offset + r4_offset;
	idx12 = idx24 + h1_offset + r5_offset;
	idx13 = idx24 + h1_offset + r6_offset;

	idx14 = idx24 + h2_offset + l0_offset;
	idx15 = idx24 + h2_offset + l1_offset;
	idx16 = idx24 + h2_offset + l2_offset;
	idx17 = idx24 + h2_offset;
	idx18 = idx24 + h2_offset + r4_offset;
	idx19 = idx24 + h2_offset + r5_offset;
	idx20 = idx24 + h2_offset + r6_offset;
			   
	idx21 = idx24  + l0_offset;
	idx22 = idx24  + l1_offset;
	idx23 = idx24  + l2_offset;
	idx24 = idx24;
	idx25 = idx24  + r4_offset;
	idx26 = idx24  + r5_offset;
	idx27 = idx24  + r6_offset;
			   
	idx28 = idx24 + b4_offset + l0_offset;
	idx29 = idx24 + b4_offset + l1_offset;
	idx30 = idx24 + b4_offset + l2_offset;
	idx31 = idx24 + b4_offset;
	idx32 = idx24 + b4_offset + r4_offset;
	idx33 = idx24 + b4_offset + r5_offset;
	idx34 = idx24 + b4_offset + r6_offset;
			   
	idx35 = idx24 + b5_offset + l0_offset;
	idx36 = idx24 + b5_offset + l1_offset;
	idx37 = idx24 + b5_offset + l2_offset;
	idx38 = idx24 + b5_offset;
	idx39 = idx24 + b5_offset + r4_offset;
	idx40 = idx24 + b5_offset + r5_offset;
	idx41 = idx24 + b5_offset + r6_offset;
			   
	idx42 = idx24 + b6_offset + l0_offset;
	idx43 = idx24 + b6_offset + l1_offset;
	idx44 = idx24 + b6_offset + l2_offset;
	idx45 = idx24 + b6_offset;
	idx46 = idx24 + b6_offset + r4_offset;
	idx47 = idx24 + b6_offset + r5_offset;
	idx48 = idx24 + b6_offset + r6_offset;



	out_data[0] = in_data[idx0];
	out_data[1] = in_data[idx1];
	out_data[2] = in_data[idx2];
	out_data[3] = in_data[idx3];
	out_data[4] = in_data[idx4];
	out_data[5] = in_data[idx5];
	out_data[6] = in_data[idx6];
	out_data[7] = in_data[idx7];
	out_data[8] = in_data[idx8];
	out_data[9] = in_data[idx9];

	out_data[10] = in_data[idx10];
	out_data[11] = in_data[idx11];
	out_data[12] = in_data[idx12];
	out_data[13] = in_data[idx13];
	out_data[14] = in_data[idx14];
	out_data[15] = in_data[idx15];
	out_data[16] = in_data[idx16];
	out_data[17] = in_data[idx17];
	out_data[18] = in_data[idx18];
	out_data[19] = in_data[idx19];

	out_data[20] = in_data[idx20];
	out_data[21] = in_data[idx21];
	out_data[22] = in_data[idx22];
	out_data[23] = in_data[idx23];
	out_data[24] = in_data[idx24];

	out_data[25] = in_data[idx25];
	out_data[26] = in_data[idx26];
	out_data[27] = in_data[idx27];
	out_data[28] = in_data[idx28];
	out_data[29] = in_data[idx29];
	out_data[30] = in_data[idx30];
	out_data[31] = in_data[idx31];
	out_data[32] = in_data[idx32];
	out_data[33] = in_data[idx33];
	out_data[34] = in_data[idx34];
	out_data[35] = in_data[idx35];
	out_data[36] = in_data[idx36];
	out_data[37] = in_data[idx37];
	out_data[38] = in_data[idx38];
	out_data[39] = in_data[idx39];
	out_data[40] = in_data[idx40];
	out_data[41] = in_data[idx41];
	out_data[42] = in_data[idx42];
	out_data[43] = in_data[idx43];
	out_data[44] = in_data[idx44];
	out_data[45] = in_data[idx45];
	out_data[46] = in_data[idx46];
	out_data[47] = in_data[idx47];
	out_data[48] = in_data[idx48];


	//	if ((index == 0) || (index = 1) || (index == width + 1))
		//if (index ==37254)
		//{
		//	LOGE("/////---------central pix idx = %d--------------/////", idx12);
		//	LOGE("%2d %2d %2d %2d %2d", idx0, idx1, idx2, idx3, idx4);
		//	LOGE("%2d %2d %2d %2d %2d", idx5, idx6, idx7, idx8, idx9);
		//	LOGE("%2d %2d %2d %2d %2d", idx10, idx11, idx12, idx13, idx14);
		//	LOGE("%2d %2d %2d %2d %2d", idx15, idx16, idx17, idx18, idx19);
		//	LOGE("%2d %2d %2d %2d %2d", idx20, idx21, idx22, idx23, idx24);
		//	LOGE("/////---------data array = %d,col = %d,row = %d--------------/////", idx12,col,row);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx0], in_data[idx1], in_data[idx2], in_data[idx3], in_data[idx4]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx5], in_data[idx6], in_data[idx7], in_data[idx8], in_data[idx9]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx10], in_data[idx11], in_data[idx12], in_data[idx13], in_data[idx14]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx15], in_data[idx16], in_data[idx17], in_data[idx18], in_data[idx19]);
		//	LOGE("%2d %2d %2d %2d %2d", in_data[idx20], in_data[idx21], in_data[idx22], in_data[idx23], in_data[idx24]);
		//}
}



















int gen_Guass_filter(int size,float* filter)
{
	int i, j,k,index;
	float e = 1.5f;
	float sum = 0.0f;
	for (i = 0; i < size ; i++)
	{
		for (j = 0; j < size; j++)
		{
			index = j * size + i;
			int delta = (j - size / 2) * (j - size / 2) + (i - size / 2) * (i - size / 2);
			filter[index] = 0.5f / e / e;
			filter[index]  = filter[index] / exp(delta / (2 * (e * e)));
			LOGE("Gauss filter[%d] = %f",index, filter[index]);
			sum += filter[index];
		}

	}
	LOGE("BEFORE NORMALIZE sum = %f",sum);
	for (k = 0; k < size*size; k++)
	{

			filter[k] /= sum;
			LOGE("Gauss filter[%d] = %f", k, filter[k]);
		
	}
	return *filter;

}

int gen_Graydiff_filter(int size,Word8u* in_data, float* filter)
{
	int i, j, k, index;
	float e = 1.5f;
	float sum = 0.0f;
	int central = (size * size )/ 2;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			index = j * size + i;
			int delta = (in_data[index] - in_data[central]) * (in_data[index] - in_data[central]);;
			filter[index] = 0.5f / e / e;
			filter[index] = filter[index] / exp(delta / (2 * (e * e)));
			//LOGE("Gray diff filter[%d] = %f", index, filter[index]);
			sum += filter[index];
		}

	}
	//LOGE("BEFORE NORMALIZE sum = %f", sum);
	for (k = 0; k < size * size; k++)
	{

		filter[k] /= sum;
	//	LOGE("Gray diff filter[%d] = %f", k, filter[k]);

	}
	return *filter;

}

int riesz_filter(int size, int order,float* filter)
{
	float factor_N;
	float factor_lap;
	float sum=0.0f;
	float filter_sum = 0.0f;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				factor_N = pow((((k + 0.5) * 3.1415926f) / size), order);
				factor_lap = sin(((i + 0.5) * (k + 0.5) * 3.1415926f) / size) * sin(((j + 0.5) * (k + 0.5) * 3.1415926f) / size);
				sum += factor_N * factor_lap;
			}
			filter[j * size + i] = (sum * 2) / size;
			filter_sum += filter[j * size + i];
		}
	}

	for (int k = 0; k < size * size; k++)
	{

	    filter[k] /= filter_sum;
		LOGE("resiz diff filter[%d] = %f", k, filter[k]);

	}
	return 0;
}



int dct_filter(Word8u* input , Word8u* output,int size, int order, float* filter)
{
	float factor_x;
	float factor_y;
	float sum = 0.0f;
	float filter_sum = 0.0f;
	int index;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			
			for (int x = 0; x < size; x++)
			{
				for (int y = 0; y < size; y++)
				{
					index = y * size + x;
					factor_y = input[index] * cos((float(y)+0.5f)*j*PI/size);
				}
				factor_x = cos((float(x) + 0.5f) * j * PI / size) * factor_y;
			}
			//dct_out[j * size + i] = factor_x * 2.0f / size;
		}
	}
	return 0;
}



