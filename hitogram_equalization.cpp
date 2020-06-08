#include "hitogram_equalization.h"
int Equal(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Equal_Cfg* param_in, module_cp* cp)
{
	LOGE("Equalization:WIDTH = %d,HEIGHT= %d", width, height);
	int gray[256];  //记录每个灰度级别下的像素个数
	float gray_prob[256];  //记录灰度分布密度
	float gray_distribution[256];  //记录累计密度
	Word8u gray_equal[256];  //均衡化后的灰度值

	for (int i = 0; i < 256; i++)
	{

		gray[i] = 0;
		gray_prob[i] = 0.0f;
		gray_distribution[i] = 0.0f;
		gray_equal[i] = 0;  
	
	}

	for (int i = 0; i < width * height; i++)
	{
		gray[y_in[i]]++;
	}
	for (int i = 0; i < 256; i++)
	{
		
	gray_prob[i] = (float)(gray[i])/(width*height);
		//LOGE("gray_prob[%d] = %f,gray[i]=%d", i, gray_prob[i], gray[i]);
	}


	//计算累计密度
	gray_distribution[0] = gray_prob[0];
	for (int i = 1; i < 256; i++)
	{
		gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
		//LOGE("gray_distribution[%d] = %f", i, gray_distribution[i]);
	}

	//重新计算均衡化后的灰度值，四舍五入。参考公式：(N-1)*T+0.5
	for (int i = 0; i < 256; i++)
	{
		gray_equal[i] = (Word8u)(255 * gray_distribution[i] + 0.5);
		//LOGE("gray_equal[%d] = %d", i,gray_equal[i]);
	}


	//直方图均衡化,更新原图每个点的像素值
	for (int i = 0; i < width*height; i++)
	{
	
			y_in[i] = gray_equal[y_in[i]];
	
	}



	return 0;
}