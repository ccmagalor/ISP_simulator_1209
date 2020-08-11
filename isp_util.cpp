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


void packed_3x3_data_8u(Word8u* in_data, int width, int height, int index, Word8u* out_data)
{


	int i,j;
	int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;

	int h_offset, b_offset, l_offset, r_offset;

	int idx0, idx1, idx2, idx3, idx4, idx5, idx6, idx7, idx8;


	idx4 = index;

	h_offset = -width;
	b_offset = width;



	l_offset = -1;
	r_offset = 1;

	if (row == 0)
	{
		h_offset = 0;
		
	}
	else if (row == (height - 1))
	{
	
		b_offset = 0;
	}


	if (col == 0)
	{
		l_offset = 0;

	}
	else if (col = (width - 1))
	{
	
		r_offset = 0;
	}




	idx0 = idx4 + h_offset + l_offset;
	idx1 = idx4 + h_offset;
	idx2 = idx4 + h_offset + r_offset;
	idx3 = idx4 + l_offset;
	idx5 = idx4 + r_offset;
	idx6 = idx4 + l_offset + b_offset;
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

	for (int i = 0; i < 9; i++)
	{


		//printf("%d\t", out_data[i]);
		if ((i + 1) % 3 == 0)
		{
		//	printf("\n");
		}

	}

	//printf("\n");

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

	for (int i = 0; i < 25; i++)
	{


	//	printf("%d\t", out_data[i]);
		if ((i + 1) % 5 == 0)
		{
		//	printf("\n");
		}
		
	}
	//printf("\n");



}


void packed_7x7_data(Word16u* in_data, int width, int height, int index, Word16u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	//int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;

	
	int idx[49];



	int h0_offset, h1_offset, h2_offset;
	int l0_offset, l1_offset, l2_offset;
	int r4_offset, r5_offset, r6_offset;
	int b4_offset, b5_offset, b6_offset;


	idx[24] = index;
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

	idx[0] = idx[24] + h0_offset + l0_offset;
	idx[1] = idx[24] + h0_offset + l1_offset;
	idx[2] = idx[24] + h0_offset + l2_offset;
	idx[3] = idx[24] + h0_offset;
	idx[4] = idx[24] + h0_offset + r4_offset;
	idx[5] = idx[24] + h0_offset + r5_offset;
	idx[6] = idx[24] + h0_offset + r6_offset;
			
	idx[7] = idx[24] + h1_offset + l0_offset;
	idx[8] = idx[24] + h1_offset + l1_offset;
	idx[9] = idx[24] + h1_offset + l2_offset;
	idx[10] = idx[24] + h1_offset;
	idx[11] = idx[24] + h1_offset + r4_offset;
	idx[12] = idx[24] + h1_offset + r5_offset;
	idx[13] = idx[24] + h1_offset + r6_offset;
			
	idx[14] = idx[24] + h2_offset + l0_offset;
	idx[15] = idx[24] + h2_offset + l1_offset;
	idx[16] = idx[24] + h2_offset + l2_offset;
	idx[17] = idx[24] + h2_offset;
	idx[18] = idx[24] + h2_offset + r4_offset;
	idx[19] = idx[24] + h2_offset + r5_offset;
	idx[20] = idx[24] + h2_offset + r6_offset;
		   		
	idx[21] = idx[24]  + l0_offset;
	idx[22] = idx[24]  + l1_offset;
	idx[23] = idx[24]  + l2_offset;
	idx[24] = idx[24];
	idx[25] = idx[24]  + r4_offset;
	idx[26] = idx[24]  + r5_offset;
	idx[27] = idx[24]  + r6_offset;
		  	
	idx[28] = idx[24] + b4_offset + l0_offset;
	idx[29] = idx[24] + b4_offset + l1_offset;
	idx[30] = idx[24] + b4_offset + l2_offset;
	idx[31] = idx[24] + b4_offset;
	idx[32] = idx[24] + b4_offset + r4_offset;
	idx[33] = idx[24] + b4_offset + r5_offset;
	idx[34] = idx[24] + b4_offset + r6_offset;
		   		
	idx[35] = idx[24] + b5_offset + l0_offset;
	idx[36] = idx[24] + b5_offset + l1_offset;
	idx[37] = idx[24] + b5_offset + l2_offset;
	idx[38] = idx[24] + b5_offset;
	idx[39] = idx[24] + b5_offset + r4_offset;
	idx[40] = idx[24] + b5_offset + r5_offset;
	idx[41] = idx[24] + b5_offset + r6_offset;
			   
	idx[42] = idx[24] + b6_offset + l0_offset;
	idx[43] = idx[24] + b6_offset + l1_offset;
	idx[44] = idx[24] + b6_offset + l2_offset;
	idx[45] = idx[24] + b6_offset;
	idx[46] = idx[24] + b6_offset + r4_offset;
	idx[47] = idx[24] + b6_offset + r5_offset;
	idx[48] = idx[24] + b6_offset + r6_offset;

	for (int i = 0; i < 49; i++)
	{
		out_data[i] = in_data[idx[i]];
	}
	


	/*
		if (row==3494&&col==4655)
		{
			for (int m = 0; m < 49; m++)
			{
				printf("%d\t", idx[m]);
				if ((m + 1) % 7 == 0)
				{
					printf("\n");
				}
			}
		}
	*/	
}


void packed_7x7_data_8u(Word8u* in_data, int width, int height, int index, Word8u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	//int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;


	int idx[49];



	int h0_offset, h1_offset, h2_offset;
	int l0_offset, l1_offset, l2_offset;
	int r4_offset, r5_offset, r6_offset;
	int b4_offset, b5_offset, b6_offset;


	idx[24] = index;
	h0_offset = 0 - (3 * width);
	h1_offset = 0 - (2 * width);
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
		l0_offset = l1_offset = l2_offset = 0;
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

	idx[0] = idx[24] + h0_offset + l0_offset;
	idx[1] = idx[24] + h0_offset + l1_offset;
	idx[2] = idx[24] + h0_offset + l2_offset;
	idx[3] = idx[24] + h0_offset;
	idx[4] = idx[24] + h0_offset + r4_offset;
	idx[5] = idx[24] + h0_offset + r5_offset;
	idx[6] = idx[24] + h0_offset + r6_offset;

	idx[7] = idx[24] + h1_offset + l0_offset;
	idx[8] = idx[24] + h1_offset + l1_offset;
	idx[9] = idx[24] + h1_offset + l2_offset;
	idx[10] = idx[24] + h1_offset;
	idx[11] = idx[24] + h1_offset + r4_offset;
	idx[12] = idx[24] + h1_offset + r5_offset;
	idx[13] = idx[24] + h1_offset + r6_offset;

	idx[14] = idx[24] + h2_offset + l0_offset;
	idx[15] = idx[24] + h2_offset + l1_offset;
	idx[16] = idx[24] + h2_offset + l2_offset;
	idx[17] = idx[24] + h2_offset;
	idx[18] = idx[24] + h2_offset + r4_offset;
	idx[19] = idx[24] + h2_offset + r5_offset;
	idx[20] = idx[24] + h2_offset + r6_offset;

	idx[21] = idx[24] + l0_offset;
	idx[22] = idx[24] + l1_offset;
	idx[23] = idx[24] + l2_offset;
	idx[24] = idx[24];
	idx[25] = idx[24] + r4_offset;
	idx[26] = idx[24] + r5_offset;
	idx[27] = idx[24] + r6_offset;

	idx[28] = idx[24] + b4_offset + l0_offset;
	idx[29] = idx[24] + b4_offset + l1_offset;
	idx[30] = idx[24] + b4_offset + l2_offset;
	idx[31] = idx[24] + b4_offset;
	idx[32] = idx[24] + b4_offset + r4_offset;
	idx[33] = idx[24] + b4_offset + r5_offset;
	idx[34] = idx[24] + b4_offset + r6_offset;

	idx[35] = idx[24] + b5_offset + l0_offset;
	idx[36] = idx[24] + b5_offset + l1_offset;
	idx[37] = idx[24] + b5_offset + l2_offset;
	idx[38] = idx[24] + b5_offset;
	idx[39] = idx[24] + b5_offset + r4_offset;
	idx[40] = idx[24] + b5_offset + r5_offset;
	idx[41] = idx[24] + b5_offset + r6_offset;

	idx[42] = idx[24] + b6_offset + l0_offset;
	idx[43] = idx[24] + b6_offset + l1_offset;
	idx[44] = idx[24] + b6_offset + l2_offset;
	idx[45] = idx[24] + b6_offset;
	idx[46] = idx[24] + b6_offset + r4_offset;
	idx[47] = idx[24] + b6_offset + r5_offset;
	idx[48] = idx[24] + b6_offset + r6_offset;

	for (int i = 0; i < 49; i++)
	{
		out_data[i] = in_data[idx[i]];

		//printf("%d\t", out_data[i]);
		if ((i + 1) % 7 == 0)
		{
		//	printf("\n");
		}
		
	}

	//printf("\n");

	/*
		if (row==3494&&col==4655)
		{
			for (int m = 0; m < 49; m++)
			{
				printf("%d\t", idx[m]);
				if ((m + 1) % 7 == 0)
				{
					printf("\n");
				}
			}
		}
	*/
}

void packed_9x9_data(Word16u* in_data, int width, int height, int index, Word16u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	//int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;


	int idx[81];

	int h_offset[9], v_offset[9];




	idx[40] = index;

	for (int i = 0; i < 9; i++)
	{
		v_offset[i] = (i - 4) * width;
		
		h_offset[i] = i - 4;

		if (row < 4 && i < (4 - row))
		{
				v_offset[i] = v_offset[4 - row];
		}

		if (row > height - 5 && i >8-(height-1-row) )
		{
			v_offset[i] = 8 - (row - (height - 5));
		}
		if (col < 4 && i < (4 - col))
		{
		
				h_offset[i] = h_offset[4 - col];
		}

		if (col > width - 5 && i > 8 - (width - 1 - col))
		{
			h_offset[i] = 8 - (col - (width - 5));
		}
	}

	for (int i = 0; i < 81; i++)
	{

		idx[i] = idx[40] + v_offset[i / 9] + h_offset[i % 9];
		
	}


	for (int i = 0; i < 49; i++)
	{
		out_data[i] = in_data[idx[i]];
	}


}


void packed_9x9_data_8u(Word8u* in_data, int width, int height, int index, Word8u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	//int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;

	//printf("row  = %d, col = %d\n",row,col);

	int idx[81];

	int h_offset[9], v_offset[9];




	idx[40] = index;

	for (int i = 0; i < 9; i++)
	{
		v_offset[i] = (i - 4) * width;

		h_offset[i] = i - 4;


	}

	for (int i = 0; i < 9; i++)
	{
		if (row < 4 && i < (4 - row))
		{
			v_offset[i] = v_offset[4 - row];
		}

		if (row > height - 5 && i > 8 - (row+5 - height))
		{
			v_offset[i] = v_offset[8 - (row + 5 - height)];
		}
		if (col < 4 && i < (4 - col))
		{

			h_offset[i] = h_offset[4 - col];
		}

		if (col > width - 5 && i > 8 - (col+5-width))
		{
			h_offset[i] = h_offset[8 - (col + 5 - width)];
		}
	}










	for (int i = 0; i < 81; i++)
	{

		idx[i] = idx[40] + v_offset[i / 9] + h_offset[i % 9];

	}


	for (int i = 0; i < 81; i++)
	{
	out_data[i] = in_data[idx[i]];
		//printf("%d\t", out_data[i]);
		if ((i+1) % 9 == 0)
		{
		//	printf("\n");
		}
	}
	//printf("\n");

}


/*

//H V must be odd
void packed_HxV_data(Word16u* in_data, Word16u* index_offset_h, Word16u* index_offset_v, int width, int height, int index, int size_h, int size_v, Word16u* out_data)
{
	///LOGE("DEMOSAIC:WIDTH = %d,HEIGHT= %d,BAYER_PATTERN=%d", width, height, bayer_pattern);
	int i, j;
	//int data[3][3];
	int col, row;
	col = index % width;
	row = index / width;
	int copy_h ;
	int copy_b ;
	int copy_l ;
	int copy_r ;
	copy_h = size_v / 2 - row;
	copy_b = size_v / 2 + row - height - 1;
	copy_l = size_h / 2 - col;
	copy_r = size_h / 2 + col - width - 1;
	copy_h = copy_h < 0 ? 0 : copy_h;
	copy_b = copy_b < 0 ? 0 : copy_b;
	copy_l = copy_l < 0 ? 0 : copy_l;
	copy_r = copy_r < 0 ? 0 : copy_r;

	for (int i = 0; i < size_h; i++)
	{
		if (i < copy_l)
			index_offset_h[i] = 0;
		else
			index_offset_h[i] = i-copy_l;
	}
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
	h1_offset = 0 - (2 * width);
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
		l0_offset = l1_offset = l2_offset = 0;
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

	idx21 = idx24 + l0_offset;
	idx22 = idx24 + l1_offset;
	idx23 = idx24 + l2_offset;
	idx24 = idx24;
	idx25 = idx24 + r4_offset;
	idx26 = idx24 + r5_offset;
	idx27 = idx24 + r6_offset;

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




*/







int gen_Guass_filter(int size,float* filter,float delta)
{
	int i, j,k,index;
	float e = delta;
	float sum = 0.0f;
	for (i = 0; i < size ; i++)
	{
		for (j = 0; j < size; j++)
		{
			index = j * size + i;
			int delta = (j - size / 2) * (j - size / 2) + (i - size / 2) * (i - size / 2);
			filter[index] = 0.5f / e / e;
			filter[index]  = filter[index] / exp(delta / (2 * (e * e)));
		//	LOGE("Gauss filter[%d] = %f",index, filter[index]);
			sum += filter[index];
		}

	}
	//LOGE("BEFORE NORMALIZE sum = %f",sum);
	for (k = 0; k < size*size; k++)
	{

			filter[k] /= sum;
			//LOGE("Gauss filter[%d] = %f", k, filter[k]);
		
	}


		for (int m = 0; m < 49; m++)
		{
			printf("%f\t", filter[m]);
			if ((m + 1) % 7 == 0)
			{
				printf("\n");
			}
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

Word16u min4(Word16u data1, Word16u data2, Word16u data3, Word16u data4)
{
	Word16u data_tmp=9999;

	if (data_tmp > data1)
		data_tmp = data1;
	else if (data_tmp > data2)
		data_tmp = data2;
	else if (data_tmp > data3)
		data_tmp = data3;
	else if (data_tmp > data4)
		data_tmp = data4;
	
	return data_tmp;
}

Word16u max4(Word16u data1, Word16u data2, Word16u data3, Word16u data4)
{
	Word16u data_tmp = 0;

	if (data_tmp < data1)
		data_tmp = data1;
	else if (data_tmp < data2)
		data_tmp = data2;
	else if (data_tmp < data3)
		data_tmp = data3;
	else if (data_tmp < data4)
		data_tmp = data4;

	return data_tmp;
}

Word16u min3(Word16u data1, Word16u data2, Word16u data3)
{
	Word16u data_tmp = 9999;

	if (data_tmp > data1)
		data_tmp = data1;
	else if (data_tmp > data2)
		data_tmp = data2;
	else if (data_tmp > data3)
		data_tmp = data3;


	return data_tmp;
}

Word16u max3(Word16u data1, Word16u data2, Word16u data3)
{
	Word16u data_tmp = 0;

	if (data_tmp < data1)
		data_tmp = data1;
	else if (data_tmp < data2)
		data_tmp = data2;
	else if (data_tmp < data3)
		data_tmp = data3;


	return data_tmp;
}

void mirror_vector_lr(float* in_data, float* outdata,int vector_size_h,int vector_size_v)
{
	for (int i = 0; i < vector_size_v; i++)
	{
		for (int j = 0; j < vector_size_h; j++)
		{
			outdata[i * vector_size_h + j] = in_data[i * vector_size_h + vector_size_h - 1 - j];

		}
		
	}

}

void mirror_vector_tb(float* in_data, float* outdata, int vector_size_h, int vector_size_v)
{
	for (int i = 0; i < vector_size_v; i++)
	{
		for (int j = 0; j < vector_size_h; j++)
		{
			outdata[i * vector_size_h + j] = in_data[(vector_size_v - 1-i) * vector_size_h +   j];

		}

	}

}

int plot3x3(Word8u* in_3x3, float* coeff_3x3)
{
	float temp1, temp2, temp3;
	temp1 = in_3x3[0] * coeff_3x3[0] + in_3x3[1] * coeff_3x3[1] + in_3x3[2] * coeff_3x3[2];
	temp2 = in_3x3[3] * coeff_3x3[3] + in_3x3[4] * coeff_3x3[4] + in_3x3[5] * coeff_3x3[5];
	temp3 = in_3x3[6] * coeff_3x3[6] + in_3x3[7] * coeff_3x3[7] + in_3x3[8] * coeff_3x3[8];
	return (int)(temp1 + temp2 + temp3);
}



int plot5x5(Word8u* in_5x5, float* coeff_5x5)
{
	float temp1, temp2, temp3, temp4, temp5;
	temp1 = in_5x5[0] * coeff_5x5[0] + in_5x5[1] * coeff_5x5[1] + in_5x5[2] * coeff_5x5[2] + in_5x5[3] * coeff_5x5[3] + in_5x5[4] * coeff_5x5[4];
	temp2 = in_5x5[5] * coeff_5x5[5] + in_5x5[6] * coeff_5x5[6] + in_5x5[7] * coeff_5x5[7] + in_5x5[8] * coeff_5x5[8] + in_5x5[9] * coeff_5x5[9];
	temp3 = in_5x5[10] * coeff_5x5[10] + in_5x5[11] * coeff_5x5[11] + in_5x5[12] * coeff_5x5[12] + in_5x5[13] * coeff_5x5[13] + in_5x5[14] * coeff_5x5[14];
	temp4 = in_5x5[15] * coeff_5x5[15] + in_5x5[16] * coeff_5x5[16] + in_5x5[17] * coeff_5x5[17] + in_5x5[18] * coeff_5x5[18] + in_5x5[19] * coeff_5x5[19];
	temp5 = in_5x5[20] * coeff_5x5[20] + in_5x5[21] * coeff_5x5[21] + in_5x5[22] * coeff_5x5[22] + in_5x5[23] * coeff_5x5[23] + in_5x5[24] * coeff_5x5[24];

	//	LOGE("%d,%d,%d,%d,%d", in_5x5[0] , in_5x5[1] , in_5x5[2] , in_5x5[3] , in_5x5[4]);
	//	LOGE("%d,%d,%d,%d,%d", in_5x5[5], in_5x5[6], in_5x5[7], in_5x5[8], in_5x5[9]);
	//	LOGE("%d,%d,%d,%d,%d", in_5x5[10], in_5x5[11], in_5x5[12], in_5x5[13], in_5x5[14]);
	//	LOGE("%d,%d,%d,%d,%d", in_5x5[15], in_5x5[16], in_5x5[17], in_5x5[18], in_5x5[19]);
	//	LOGE("%d,%d,%d,%d,%d", in_5x5[20], in_5x5[21], in_5x5[22], in_5x5[23], in_5x5[24]);
	//	LOGE("%f,%f,%f,%f,%f", temp1, temp2, temp3, temp4, temp5);
	//	LOGE("%d", (int)(temp1 + temp2 + temp3 + temp4 + temp5));
	return (int)(temp1 + temp2 + temp3 + temp4 + temp5);
}

int plot7x7(Word8u* in_7x7, float* coeff_7x7)
{
	float data_temp=0;
	for (int i = 0; i < 49; i++)
	{
		data_temp += in_7x7[i] * coeff_7x7[i];

	}
	return (int)(data_temp);


}


int plot9x9(Word8u* in_9x9, float* coeff_9x9)
{
	float data_temp = 0;
	for (int i = 0; i < 81; i++)
	{
		data_temp += in_9x9[i] * coeff_9x9[i];

	}
	return (int)(data_temp);


}