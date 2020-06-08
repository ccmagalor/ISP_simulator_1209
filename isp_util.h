#pragma once
#include "isp_type.h"
#include<stdio.h>
#include<iostream>
#include<filesystem>
#include<algorithm>
#include"isp.h"
#include <assert.h>
#define LOGE(fmt,...) printf("%s:%d:"fmt"\n",__FUNCTION__,__LINE__,__VA_ARGS__);



int convertMIPItoRAW(Word8u* mipiRAW, Word16u* image, unsigned int w, unsigned int h);
int readBayerImage(char* cfgFileName, Word16u* image, unsigned int w, unsigned int h, int inputBit);
int separ_pixel(Word16u* image, Word16u* r_buffer, Word16u* gr_buffer, Word16u* gb_buffer, Word16u* b_buffer, int width, int height, int bayer_pattern);
int combo_pixel(Word16u* r_buffer, Word16u* gr_buffer, Word16u* gb_buffer, Word16u* b_buffer, Word16u* image, int width, int height, int bayer_pattern);
void copy_1border(Word16u* in_data, int width, int height, int size, Word16u* out_data);
void packed_3x3_data(Word8u* in_data, int width, int height, int index, Word8u* out_data);
void packed_5x5_data(Word16u* in_data, int width, int height, int index, Word16u* out_data);
void packed_5x5_data_8u(Word8u* in_data, int width, int height, int index, Word8u* out_data);
void packed_7x7_data(Word16u* in_data, int width, int height, int index, Word16u* out_data);
int gen_Guass_filter(int size, float* filter);
int gen_Graydiff_filter(int size, Word8u* in_data, float* filter);

int riesz_filter(int size, int order, float* filter);
int dct_filter(Word8u* input, Word8u* output, int size, int order, float* filter);


template <class T>
class Mysort
{
public:
	Mysort(){}
	T* Bubble_sort(T* a, int size);
//private:
	//T* a;
	//T* b;
};


template <class T>

T* Mysort<T>::Bubble_sort(T* a, int size)
{
	
	T* b = a;
	for (int i = 0; i < size; i++)
	{
		//LOGE("before:%d,%d", i, b[i]);
	}
	for (int i = size; i > 0; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			//LOGE("before:b[%d] = %d,b[%d] = %d",j, b[j] , j + 1, b[j + 1]);
			if (b[j] > b[j + 1]) {

				std::swap(b[j], b[j + 1]);
			}
			//LOGE("after:b[%d] = %d,b[%d] = %d",j,b[j], j + 1, b[j + 1], b[j + 1]);
		}
		//LOGE("index=%d,data = %d",i-1,b[i-1])

	}
	for (int i = 0; i < size; i++)
	{
		//LOGE("after:%d,%d", i, b[i]);
	}
	
	return b;
}
