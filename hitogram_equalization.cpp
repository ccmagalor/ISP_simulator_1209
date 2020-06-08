#include "hitogram_equalization.h"
int Equal(Word8u* y_in, Word8u* u_in, Word8u* v_in, int width, int height, Equal_Cfg* param_in, module_cp* cp)
{
	LOGE("Equalization:WIDTH = %d,HEIGHT= %d", width, height);
	int gray[256];  //��¼ÿ���Ҷȼ����µ����ظ���
	float gray_prob[256];  //��¼�Ҷȷֲ��ܶ�
	float gray_distribution[256];  //��¼�ۼ��ܶ�
	Word8u gray_equal[256];  //���⻯��ĻҶ�ֵ

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


	//�����ۼ��ܶ�
	gray_distribution[0] = gray_prob[0];
	for (int i = 1; i < 256; i++)
	{
		gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
		//LOGE("gray_distribution[%d] = %f", i, gray_distribution[i]);
	}

	//���¼�����⻯��ĻҶ�ֵ���������롣�ο���ʽ��(N-1)*T+0.5
	for (int i = 0; i < 256; i++)
	{
		gray_equal[i] = (Word8u)(255 * gray_distribution[i] + 0.5);
		//LOGE("gray_equal[%d] = %d", i,gray_equal[i]);
	}


	//ֱ��ͼ���⻯,����ԭͼÿ���������ֵ
	for (int i = 0; i < width*height; i++)
	{
	
			y_in[i] = gray_equal[y_in[i]];
	
	}



	return 0;
}