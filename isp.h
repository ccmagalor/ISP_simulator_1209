#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <cstdint>
#include <map>
#include<stdlib.h>
#include<stdio.h>

//#include <filesystem>
#include<algorithm>

#include"isp_util.h"
#include"isp_type.h"
#include"demosaic.h"
#include"blc.h"
#include"gamma.h"
#include"cst.h"
#include "ltm.h"
#include"awb.h"
#include"sharpen.h"
#include "hitogram_equalization.h"
#include "gtm.h"
#include "cc.h"
#include "nr.h"
#include "wb.h"
typedef struct {
	Word16_u    bfType;
	unsigned int   bfSize;
	unsigned short    bfReserved1;
	unsigned short   bfReserved2;
	unsigned int    bfOffBits;
} BMPFILEHEADER_T;

typedef struct {
	unsigned int      biSize;
	int        biWidth;
	int       biHeight;
	unsigned short       biPlanes;
	unsigned short       biBitCount;
	unsigned int     biCompression;
	unsigned int      biSizeImage;
	int        biXPelsPerMeter;
	int       biYPelsPerMeter;
	unsigned int      biClrUsed;
	unsigned int      biClrImportant;
} BMPINFOHEADER_T;









#define RGGB_PATTERN 0
#define GRBG_PATTERN 1
#define GBRG_PATTERN 2
#define BGGR_PATTERN 3

#define CLAMP(x,y,z)  (x>y)?y£º(x<z£©z:x
#define FOR3 for(int i=0;i<3;i++)
#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b
#define ABS(X) X<0?0:X

#define PI 3.1416f