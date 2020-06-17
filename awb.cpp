#include"awb.h"
const float YCbCrYRF = 0.299F;              // RGB转YCbCr的系数(浮点类型）
const float YCbCrYGF = 0.587F;
const float YCbCrYBF = 0.114F;
const float YCbCrCbRF = -0.168736F;
const float YCbCrCbGF = -0.331264F;
const float YCbCrCbBF = 0.500000F;
const float YCbCrCrRF = 0.500000F;
const float YCbCrCrGF = -0.418688F;
const float YCbCrCrBF = -0.081312F;

const float RGBRYF = 1.00000F;            // YCbCr转RGB的系数(浮点类型）
const float RGBRCbF = 0.0000F;
const float RGBRCrF = 1.40200F;
const float RGBGYF = 1.00000F;
const float RGBGCbF = -0.34414F;
const float RGBGCrF = -0.71414F;
const float RGBBYF = 1.00000F;
const float RGBBCbF = 1.77200F;
const float RGBBCrF = 0.00000F;

const int Shift = 20;
const int HalfShiftValue = 1 << (Shift - 1);

const int YCbCrYRI = (int)(YCbCrYRF * (1 << Shift) + 0.5);         // RGB转YCbCr的系数(整数类型）
const int YCbCrYGI = (int)(YCbCrYGF * (1 << Shift) + 0.5);
const int YCbCrYBI = (int)(YCbCrYBF * (1 << Shift) + 0.5);
const int YCbCrCbRI = (int)(YCbCrCbRF * (1 << Shift) + 0.5);
const int YCbCrCbGI = (int)(YCbCrCbGF * (1 << Shift) + 0.5);
const int YCbCrCbBI = (int)(YCbCrCbBF * (1 << Shift) + 0.5);
const int YCbCrCrRI = (int)(YCbCrCrRF * (1 << Shift) + 0.5);
const int YCbCrCrGI = (int)(YCbCrCrGF * (1 << Shift) + 0.5);
const int YCbCrCrBI = (int)(YCbCrCrBF * (1 << Shift) + 0.5);

const int RGBRYI = (int)(RGBRYF * (1 << Shift) + 0.5);              // YCbCr转RGB的系数(整数类型）
const int RGBRCbI = (int)(RGBRCbF * (1 << Shift) + 0.5);
const int RGBRCrI = (int)(RGBRCrF * (1 << Shift) + 0.5);
const int RGBGYI = (int)(RGBGYF * (1 << Shift) + 0.5);
const int RGBGCbI = (int)(RGBGCbF * (1 << Shift) + 0.5);
const int RGBGCrI = (int)(RGBGCrF * (1 << Shift) + 0.5);
const int RGBBYI = (int)(RGBBYF * (1 << Shift) + 0.5);
const int RGBBCbI = (int)(RGBBCbF * (1 << Shift) + 0.5);
const int RGBBCrI = (int)(RGBBCrF * (1 << Shift) + 0.5);

int RGB2YCbCr(Word16u* r_in, Word16u* g_in, Word16u* b_in, Word16u* Y_out, Word16u* Cb_out, Word16u* Cr_out, int width,int height)
{
	for (int i = 0; i < width * height; i++)
	{
		Y_out[i] = (Word16u)((YCbCrYRI * r_in[i] + YCbCrYGI * g_in[i] + YCbCrYBI * g_in[i] + HalfShiftValue) >> Shift);
		Cb_out[i] = (Word16u)(128 + ((YCbCrCbRI * r_in[i] + YCbCrCbGI * g_in[i] + YCbCrCbBI * g_in[i] + HalfShiftValue) >> Shift));
		Cr_out[i] = (Word16u)(128 + ((YCbCrCrRI * r_in[i] + YCbCrCrGI * g_in[i] + YCbCrCrBI * g_in[i] + HalfShiftValue) >> Shift));
	}
	return 0;
}

int YCbCr2RGB(Word16u* Y_in, Word16u* Cb_in, Word16u* Cr_in, Word16u* r_out, Word16u* g_out, Word16u* b_out, int width, int height)
{
	for (int i=0;i<width*height;i++)
	{
		int Y = Y_in[i];
		int Cb = Cb_in[i] - 128;
		int Cr = Cr_in[i] - 128;
		int Red = Y + ((RGBRCrI * Cr + HalfShiftValue) >> Shift);
		int Green = Y + ((RGBGCbI * Cb + RGBGCrI * Cr + HalfShiftValue) >> Shift);
		int Blue = Y + ((RGBBCbI * Cb + HalfShiftValue) >> Shift);
		if (Red > 255) Red = 255; else if (Red < 0) Red = 0;
		if (Green > 255) Green = 255; else if (Green < 0) Green = 0;    // 编译后应该比三目运算符的效率高
		if (Blue > 255) Blue = 255; else if (Blue < 0) Blue = 0;
		r_out[i] = Blue;
		g_out[i] = Green;
		b_out[i] = Red;

	}
	return 0;
}

int awb_RGB(Word8u* r_in, Word8u* g_in, Word8u* b_in, int width, int height)
{
	LOGE("AWB:WIDTH = %d,HEIGHT= %d", width, height);
	Word32u* Hist_Y= (Word32u*)calloc(256, sizeof(Word32u));
	Word8u* Y  = (Word8u*)calloc(width * height, sizeof(Word8u));
	for (int i = 0; i < width * height; i++)
	{
		Y[i]= (76 * (r_in[i]) + 150 * (g_in[i]) + 29 * (b_in[i])) >> 8;

		Hist_Y[Y[i]]++;
	}

	for (int i = 0; i < 256; i++)
	{
		//printf("Hist_Y[%d] = %d",i,Hist_Y[i]);
	}
	Word32u Sum=0;
	int ratio = 2;
	int Threshold;
	for (int i = 255; i >= 0; i--)
	{
		Sum += Hist_Y[i];
		if (Sum > width * height * ratio / 100)
		{
			Threshold = i;
			break;
		}
	}

	LOGE("awb threshold = %d",Threshold);
	Word32u Average_R = 0;
	Word32u Average_G = 0;
	Word32u Average_B = 0;;
	Word32u Amount=1;
	for (int i = 0; i < width * height; i++)
	{
		if (Y[i] > Threshold)
		{
			Average_R += r_in[i];
			Average_G += g_in[i];
			Average_B += b_in[i];
			Amount++;
		}
	}
	Average_R = Average_R / Amount;
	Average_G = Average_G / Amount;
	Average_B = Average_B / Amount;
	int max_value = 255;
	int ratio_R = 0;
	int ratio_G = 0;
	int ratio_B=0;
	ratio_R = (max_value * 1000) / Average_R;
	ratio_G = (max_value *1000) / Average_G;
	ratio_B = (max_value *1000) / Average_B;
	ratio_B = 1200;
	LOGE("////Average_R=%d Average_G=%d Average_B=%d", Average_R, Average_G, Average_B);
	LOGE("////ratio_R=%d ratio_G=%d ratio_B=%d", ratio_R, ratio_G, ratio_B);
	ratio_R = ratio_R<ratio_G ? 1000 : ratio_R *1000/ratio_G ;
	ratio_G = 1000;
	ratio_B = ratio_B < ratio_G ? 1000 : ratio_B * 1000 / ratio_G;
	LOGE("ratio_R=%d ratio_G=%d ratio_B=%d", ratio_R, ratio_G, ratio_B);
	for (int i = 0; i < width * height; i++)
	{
		r_in[i] = (r_in[i] * ratio_R) /1000 >255?255: (r_in[i] * ratio_R) / 1000;
		g_in[i] = (g_in[i] * ratio_G) / 1000 > 255 ? 255 : (g_in[i] * ratio_G) / 1000;;
		b_in[i] = (b_in[i] * ratio_B) / 1000 > 255 ? 255 : (b_in[i] * ratio_B) / 1000;;
	}



	free(Y);
	return 0;
}

int awb(Word16u* image, Awb_out* param_out, int width, int height)
{
	int RbufferSize = width * height /4;
	int GrbufferSize = width * height / 4;
	int GbbufferSize = width * height / 4;
	int GbufferSize = width * height / 4;
	int BbufferSize = width * height / 4;
	Word16u* pRBuffer = (Word16u*)(malloc(RbufferSize * sizeof(Word16u)));
	Word16u* pGrBuffer = (Word16u*)(malloc(GbbufferSize * sizeof(Word16u)));
	Word16u* pGbBuffer = (Word16u*)(malloc(GrbufferSize * sizeof(Word16u)));
	Word16u* pGBuffer = (Word16u*)(malloc(GbufferSize * sizeof(Word16u)));
	Word16u* pBBuffer = (Word16u*)(malloc(BbufferSize * sizeof(Word16u)));
	memset(pRBuffer, 0, RbufferSize * sizeof(Word16u));
	memset(pGrBuffer, 0, GbbufferSize * sizeof(Word16u));
	memset(pGbBuffer, 0, GrbufferSize * sizeof(Word16u));
	memset(pGBuffer, 0, GbufferSize * sizeof(Word16u));
	memset(pBBuffer, 0, BbufferSize * sizeof(Word16u));

	int bayer_pattern = 0;

	separ_pixel(image, pRBuffer, pGrBuffer, pGbBuffer, pBBuffer, width, height, bayer_pattern);

	for (int i = 0; i < width * height/4; i++)
	{
		pGBuffer[i] = (pGrBuffer[i] + pGbBuffer[i]) / 2;
	}


	LOGE("AWB:WIDTH = %d,HEIGHT= %d", width, height);
	Word32u* Hist_Y = (Word32u*)calloc(1024, sizeof(Word32u));
	Word16u* Y = (Word16u*)calloc(width * height/4, sizeof(Word16u));
	for (int i = 0; i < width * height/4; i++)
	{
		Y[i] = (76 * (pRBuffer[i]) + 150 * (pGBuffer[i]) + 29 * (pBBuffer[i])) >> 8;

		Hist_Y[Y[i]]++;
	}

	for (int i = 0; i < 1024; i++)
	{
		//printf("Hist_Y[%d] = %d",i,Hist_Y[i]);
	}
	Word32u Sum = 0;
	int ratio = 2;
	int Threshold;
	for (int i = 1023; i >= 0; i--)
	{
		Sum += Hist_Y[i];
		if (Sum > width * height * ratio / 400)
		{
			Threshold = i;
			break;
		}
	}

	LOGE("awb threshold = %d", Threshold);
	Word32u Average_R = 0;
	Word32u Average_G = 0;
	Word32u Average_B = 0;
	Word32u Amount = 1;
	for (int i = 0; i < width * height/4; i++)
	{
		if (Y[i] > Threshold)
		{
			Average_R += pRBuffer[i];
			Average_G += pGBuffer[i];
			Average_B += pBBuffer[i];
			Amount++;
		}
	}
	Average_R = Average_R / Amount;
	Average_G = Average_G / Amount;
	Average_B = Average_B / Amount;
	int max_value = 255;
	int ratio_R = 0;
	int ratio_G = 0;
	int ratio_B = 0;
	ratio_R = (max_value * 1000) / Average_R;
	ratio_G = (max_value * 1000) / Average_G;
	ratio_B = (max_value * 1000) / Average_B;
	ratio_B = 1200;
	LOGE("////Average_R=%d Average_G=%d Average_B=%d", Average_R, Average_G, Average_B);
	LOGE("////ratio_R=%d ratio_G=%d ratio_B=%d", ratio_R, ratio_G, ratio_B);
	ratio_R = ratio_R < ratio_G ? 1000 : ratio_R * 1000 / ratio_G;
	ratio_G = 1000;
	ratio_B = ratio_B < ratio_G ? 1000 : ratio_B * 1000 / ratio_G;
	LOGE("ratio_R=%d ratio_G=%d ratio_B=%d", ratio_R, ratio_G, ratio_B);
	/*
	for (int i = 0; i < width * height/4; i++)
	{
		pRBuffer[i] = (pRBuffer[i] * ratio_R) / 1000 > 1023 ? 1023 : (pRBuffer[i] * ratio_R) / 1000;
		pGBuffer[i] = (pGBuffer[i] * ratio_G) / 1000 > 1023 ? 1023 : (pGBuffer[i] * ratio_G) / 1000;;
		pBBuffer[i] = (pBBuffer[i] * ratio_B) / 1000 > 1023 ? 1023 : (pBBuffer[i] * ratio_B) / 1000;;
	}
	*/
	param_out->r_gain = float(ratio_R) / 1000.0f;
	param_out->g_gain = float(ratio_G) / 1000.0f;
	param_out->b_gain = float(ratio_B) / 1000.0f;
	LOGE("r_ratio = %f,g_ratio = %f,b_ratio = %f", param_out->r_gain, param_out->g_gain, param_out->b_gain);
//	combo_pixel(pRBuffer, pGrBuffer, pGbBuffer, pBBuffer, image, width, height, bayer_pattern);
	free(pRBuffer);
	free(pGrBuffer);
	free(pGbBuffer);
	free(pGBuffer);
	free(pBBuffer);
	free(Hist_Y);
	free(Y);
	return 0;
}