#include"isp.h"


//namespace fs = std::experimental::filesystem;
//namespace fs = std::experimental::filesystem;
#include <filesystem>


using namespace std;
//#include <boost/filesystem.hpp>
namespace fs = std::filesystem;
//namespace fs = std::experimental::filesystem;
//namespace fsxx = std::filesystem;

int main(int argc, char* argv[])
{
	

	
	char* dirname = argv[1];
	LOGE("%s is working directory", dirname);
	
	if (fs::is_directory(dirname) == 0)
	{
		LOGE("%s is not a valid directory", dirname);
	}
	else
	{
		LOGE("%s is working directory", dirname);
	}
	
	/*char filename[200];
	sprintf_s(filename, 200, "%s\%s", dirname, "BAFconfig.txt");
	if (fs::exists(filename) == 0)
	{
		LOGE("configure file %s doesn't exists", filename);
	}
	else
	{
		LOGE("configure file %s  exists", filename);
	}
	*/
	//string configPATH;
	std::string configPATH(dirname);
	cout << "//...........configPATH............//" << endl;
	cout << configPATH << endl;
	
	string::size_type pos1 = 0;
	
	while ((pos1 = configPATH.find("\\", pos1)) != string::npos) {
		configPATH.insert(pos1, "\\");
		pos1 = pos1 + 2;
	}
	
	//std::replace_if(configPATH.begin(),configPATH.end(),"/","//");
	std::cout << "//...........configPATH11............//" << endl;
	std::cout << configPATH << endl;

	const char* Wpath;
	Wpath = configPATH.c_str();
	std::cout << "//...........debug path............//" << endl;
	std::cout << Wpath << endl;
	char filename[200];
	sprintf_s(filename, 200, "%s%s", Wpath, "BAFconfig.txt");
	if (fs::exists(filename) == 0)
	{
		LOGE("configure file %s doesn't exists", filename);
	}
	else
	{
		LOGE("configure file %s  exists", filename);
	}
	//ifstream in(configPATH.c_str());
	ifstream in(filename);
	string line;
	string s;
	
	string::size_type pos;

	unsigned int ImWidth=4656;
	unsigned int ImHeight= 3496;
	unsigned int  Bayer_pattern;
	if (in) // 有该文件	
	{
		while (getline(in, line)) // line中不包括每行的换行符	
		{
			pos = line.find("Bayer_pattern");
			if (pos != string::npos)
			{
				s = line.substr(pos + strlen("Bayer_pattern") + strlen("="));
				cout << s.c_str() << endl;
				//ImWidth = atoi(s.c_str());
				Bayer_pattern = atoi(s.c_str());
				cout << "Bayer_pattern = " << Bayer_pattern << endl;
		
			}
			pos = line.find("width");
			if (pos != string::npos)
			{
				s = line.substr(pos + strlen("width") + strlen("="));
				cout << s.c_str() << endl;
				ImWidth = atoi(s.c_str());
				cout << "Image Width = " << ImWidth << endl;
	
			}
			pos = line.find("height");
			if (pos != string::npos)
			{
				s = line.substr(pos + strlen("height") + strlen("="));
				cout << s.c_str() << endl;
				ImHeight = atoi(s.c_str());
				cout << "Image Height = " << ImHeight << endl;
			}
		}
	}
	else // 没有该文件	
	{
		cout << "no such file" << endl;
	}


	FILE* pFile = NULL;
	FILE* pFile1 = NULL;
	FILE* pFile2 = NULL;
	errno_t err;
	module_cp cp;
	Demosaic_Cfg demosaic_param_in;
	Blc_Cfg blc_param_in;
	Cst_Cfg cst_param_in;
	Ltm_Cfg ltm_param_in;
	Gtm_Cfg gtm_param_in;
	Gamma_Cfg gamma_param_in;
	Sharpen_Cfg Sharpen_param_in;
	Cc_Cfg cc_param_in;
	Nr_Cfg nr_param_in;
	Equal_Cfg Equal_param_in;
	Awb_out awb_param_out;

	Wb_param_cfg Wb_param_in;
	int MipiWidth = ((((ImWidth / 4) * 5)/16) + 1) * 16;
	LOGE("MipiWidth = %d",MipiWidth);
	int bufferSizeMIPI = MipiWidth * ImHeight;
	Word8u* pBufferMIPI = (Word8u*)(malloc(bufferSizeMIPI * sizeof(Word8u)));
	memset(pBufferMIPI, 0, bufferSizeMIPI * sizeof(Word8u));
	
	int bufferSize = ImWidth * ImHeight;
	Word16u* pBuffer = (Word16u*)(malloc(bufferSize * sizeof(Word16u)));
	memset(pBuffer, 0, bufferSize * sizeof(Word16u));
	
	int bufferSizeTmp = ImWidth * ImHeight*2;
	Word8u* pBufferTmp = (Word8u*)(malloc(bufferSizeTmp * sizeof(Word8u)));
	memset(pBufferTmp, 0, bufferSizeTmp * sizeof(Word8u));

	int bufferSize_blc = ImWidth * ImHeight;
	Word16u* pBuffer_blc = (Word16u*)(malloc(bufferSize_blc * sizeof(Word16u)));
	memset(pBuffer_blc, 0, bufferSize_blc * sizeof(Word16u));
	
	int RbufferSize = ImWidth * ImHeight;
	int GbufferSize = ImWidth * ImHeight;
	int BbufferSize = ImWidth * ImHeight;
	Word16u* pRBuffer = (Word16u*)(malloc(RbufferSize * sizeof(Word16u)));
	Word16u* pGBuffer = (Word16u*)(malloc(GbufferSize * sizeof(Word16u)));
	Word16u* pBBuffer = (Word16u*)(malloc(BbufferSize * sizeof(Word16u)));
	memset(pRBuffer, 0, RbufferSize * sizeof(Word16u));
	memset(pGBuffer, 0, GbufferSize * sizeof(Word16u));
	memset(pBBuffer, 0, BbufferSize * sizeof(Word16u));
	

	Word8u* pRBuffer_8 = (Word8u*)(malloc(RbufferSize * sizeof(Word8u)));
	Word8u* pGBuffer_8 = (Word8u*)(malloc(GbufferSize * sizeof(Word8u)));
	Word8u* pBBuffer_8 = (Word8u*)(malloc(BbufferSize * sizeof(Word8u)));
	memset(pRBuffer_8, 0, RbufferSize * sizeof(Word8u));
	memset(pGBuffer_8, 0, GbufferSize * sizeof(Word8u));
	memset(pBBuffer_8, 0, BbufferSize * sizeof(Word8u));


	int YbufferSize = ImWidth * ImHeight;
	int UbufferSize = ImWidth * ImHeight;
	int VbufferSize = ImWidth * ImHeight;
	Word8u* pYBuffer = (Word8u*)(malloc(YbufferSize * sizeof(Word8u)));
	Word8u* pUBuffer = (Word8u*)(malloc(UbufferSize * sizeof(Word8u)));
	Word8u* pVBuffer = (Word8u*)(malloc(VbufferSize * sizeof(Word8u)));
	memset(pYBuffer, 0, YbufferSize * sizeof(Word8u));
	memset(pUBuffer, 0, UbufferSize * sizeof(Word8u));
	memset(pVBuffer, 0, VbufferSize * sizeof(Word8u));


	for (const auto& file : fs::directory_iterator(dirname))
	{
	
		const string temp = file.path().string();
		if (temp.find(".RAWMIPI") == string::npos)
		{
			continue;
	
		}
		cout << temp << endl;

		ifstream rawinput(temp.c_str(),ios_base::in|ios_base::binary);
		const char* temp_dir;
		temp_dir = temp.c_str();
		std::cout << "//...........debug raw path............//" << endl;
		std::cout << temp_dir << endl;
		string temp_dir1;
		string temp_dir2;
		temp_dir1 = temp_dir;
		int end = temp_dir1.rfind(".RAWMIPI");
		temp_dir2 = temp_dir1.substr(0,end);
		std::cout << "//...........debug2 raw path............//" << endl;
		std::cout << temp_dir2 << endl;
		if (!rawinput)
		{

			LOGE("Can't read mipi file!");
			return 0;
		}
		else
		{

			LOGE("Read mipi raw finished");
		}

		if (rawinput.is_open())
		{
			rawinput.read((char*)pBufferMIPI, bufferSizeMIPI);
		}

		rawinput.close();

		convertMIPItoRAW(pBufferMIPI, pBuffer, ImWidth, ImHeight);

		bool convertDEBUG = false;
		if (convertDEBUG) {
			for (int i = 0; i < ImWidth * ImHeight; i++)
			{
				int idx0 = 0;
				int idx1 = 0;
				int idx2 = 0;
				int idx3 = 0;

				int dataMIPI, dataRAW;
				dataRAW = pBuffer[i];
			/*	//	dataMIPI = pBufferMIPI[(i / 4) * 5 + i % 4];
				if (i % 4 == 0)
				{
					dataMIPI = (pBufferMIPI[(i / 4) * 5 + i % 4] << 2) + ((pBufferMIPI[(i / 4) * 5 + 4] >> 0) & 0x3);
					if (dataRAW != dataMIPI)
						LOGE("data0 MIPI to RAW error!");
				}
				else if (i % 4 == 1)
				{
					dataMIPI = (pBufferMIPI[(i / 4) * 5 + i % 4] << 2) + ((pBufferMIPI[(i / 4) * 5 + 4] >> 2) & 0x3);
					if (dataRAW != dataMIPI)
						LOGE("data1 MIPI to RAW error!");
				}
				else if (i % 4 == 2)
				{
					dataMIPI = (pBufferMIPI[(i / 4) * 5 + i % 4] << 2) + ((pBufferMIPI[(i / 4) * 5 + 4] >> 4) & 0x3);
					if (dataRAW != dataMIPI)
						LOGE("data2 MIPI to RAW error!");
				}
				else if (i % 4 == 3)
				{
					dataMIPI = (pBufferMIPI[(i / 4) * 5 + i % 4] << 2) + ((pBufferMIPI[(i / 4) * 5 + 4] >> 6) & 0x3);
					if (dataRAW != dataMIPI)
						LOGE("data3 MIPI to RAW error!");
				}
				if (i < 20)
				{
					LOGE("mipiRAW unpacked to RAW = %d", dataRAW);
				}
				*/
			}
		}

		for (int i = 0; i < ImWidth * ImHeight; i++)
		{
			pBufferTmp[2 * i] = (Word8u)(pBuffer[i] & 0xFF);
			pBufferTmp[2 * i + 1] = (Word8u)((pBuffer[i] >> 8) & 0xFF);


		}


		string::size_type pos2 = 0;

		while ((pos2 = temp_dir2.find("\\", pos2)) != string::npos) {
			temp_dir2.insert(pos2, "\\");
			pos2 = pos2 + 2;
		}

		//std::replace_if(configPATH.begin(),configPATH.end(),"/","//");
		std::cout << "//...........temp_dir2............//" << endl;
		std::cout << temp_dir2 << endl;
		char raw_path[300];

		sprintf_s(raw_path, 200, "%s%s", temp_dir2.c_str(), ".raw");
		std::cout << "//...........debug3 raw path............//" << endl;
		std::cout << raw_path << endl;

		if (fs::exists(raw_path) == 0)
		{
			LOGE("configure file %s doesn't exists", raw_path);
		}
		else
		{
			LOGE("configure file %s  exists", raw_path);
		}

	ofstream rawunpacked(raw_path,ios::out|ios::binary);
	if (rawunpacked.fail())
	{
	
		LOGE("output fil error!");
		return 0;
	}
	


	if (rawunpacked.is_open())
	{
		if(rawunpacked.write((char*)pBufferTmp, bufferSizeTmp))
			LOGE("write file succced!");


	}
	rawunpacked.close();

//				
//		/////* -------------BLC-----------------
//		//////不同照明条件下，每个像素上每个通道的传感器相应的线性度和黑电平必须进行校正
//		////*/----------------------------------
//		//
		blc(pBuffer, pBuffer_blc, ImWidth, ImHeight, 0, &blc_param_in, &cp);
		
		awb(pBuffer_blc, &awb_param_out, ImWidth, ImHeight);


		Wb_param_in.r_gain = awb_param_out.r_gain;
		Wb_param_in.g_gain = awb_param_out.g_gain;
		Wb_param_in.b_gain = awb_param_out.b_gain;
		demosaic_param_in.r_gain = awb_param_out.r_gain;
		demosaic_param_in.g_gain = awb_param_out.g_gain;
		demosaic_param_in.b_gain = awb_param_out.b_gain;

		demosaic(pBuffer_blc, pRBuffer, pGBuffer, pBBuffer, ImWidth, ImHeight, 0, &demosaic_param_in, &cp);
		//cc(pRBuffer, pGBuffer, pBBuffer,pRBuffer, pGBuffer, pBBuffer, ImWidth, ImHeight, &cc_param_in, &cp);
		wb(pRBuffer, pGBuffer, pBBuffer, &Wb_param_in, ImWidth, ImHeight);


		gamma_correction(pRBuffer, pRBuffer_8, ImWidth, ImHeight, &gamma_param_in);
		gamma_correction(pGBuffer, pGBuffer_8, ImWidth, ImHeight, &gamma_param_in);
		gamma_correction(pBBuffer, pBBuffer_8, ImWidth, ImHeight, &gamma_param_in);
		
		//awb(pRBuffer_8, pGBuffer_8, pBBuffer_8, ImWidth, ImHeight);

		//ltm(pRBuffer_8, pGBuffer_8, pBBuffer_8, ImWidth, ImHeight, &ltm_param_in, &cp);
		//ltm1(pRBuffer_8, pGBuffer_8, pBBuffer_8, ImWidth, ImHeight, &ltm_param_in, &cp);
		//gtm(pRBuffer_8, pGBuffer_8, pBBuffer_8, ImWidth, ImHeight, &gtm_param_in, &cp);
		//=============================save to bmp===============
		//int size = ImWidth * ImHeight * 3 * sizeof(char); // 每个像素点3个字节
		
		
		int size = (3*ImWidth) * ImHeight; // 每个像素点3个字节
	  // 位图第一部分，文件信息
		BMPFILEHEADER_T bfh;
		bfh.bfType = (unsigned short)0x4d42;  //bm
		//bfh.bfSize = size  + sizeof(BMPFILEHEADER_T) + sizeof(BMPINFOHEADER_T); // second section size
		bfh.bfSize = size + 54;
		LOGE("SIZE = 0x%x", bfh.bfSize);
		bfh.bfReserved1 = 0; // reserved
		bfh.bfReserved2 = 0; // reserved
		bfh.bfOffBits = 54;// sizeof(BMPFILEHEADER_T) + sizeof(BMPINFOHEADER_T);//真正的数据的位置

		// 位图第二部分，数据信息
		BMPINFOHEADER_T bih;
		//bih.biSize = sizeof(BMPINFOHEADER_T);
		bih.biSize = 40;
		bih.biWidth = ImWidth;
		bih.biHeight = ImHeight;//BMP图片从最后一个点开始扫描，显示时图片是倒着的，所以用-height，这样图片就正了
		bih.biPlanes = 1;//为1，不用改
		bih.biBitCount = 24;
		bih.biCompression = 0;//不压缩
		//bih.biSizeImage = size;
		bih.biSizeImage = 0;
		bih.biXPelsPerMeter = 0;//像素每米
		bih.biYPelsPerMeter = 0;
		bih.biClrUsed = 0;//已用过的颜色，24位的为0
		bih.biClrImportant = 0;//每个像素都重要
		FILE* fp;

		char bmp_path[300];

		sprintf_s(bmp_path, 200, "%s%s", temp_dir2.c_str(), ".bmp");
		std::cout << "//...........debug3 raw path............//" << endl;
		std::cout << bmp_path << endl;

		if (err = fopen_s(&fp, bmp_path, "wb"))
		{
			LOGE("BMP file read error\n");
		}
		

		//fwrite(&bfh, 8, 1, fp);//由于linux上4字节对齐，而信息头大小为54字节，第一部分14字节，第二部分40字节，所以会将第一部分补齐为16自己，直接用sizeof，打开图片时就会遇到premature end-of-file encountered错误
		fwrite(&bfh.bfType, sizeof(bfh.bfType), 1, fp);
		fwrite(&bfh.bfSize, sizeof(bfh.bfSize), 1, fp);
		fwrite(&bfh.bfReserved1, sizeof(bfh.bfReserved1), 1, fp);
		fwrite(&bfh.bfReserved2, sizeof(bfh.bfReserved2), 1, fp);
		fwrite(&bfh.bfOffBits, sizeof(bfh.bfOffBits), 1, fp);
		fwrite(&bih, sizeof(BMPINFOHEADER_T), 1, fp);


		char* data1_temp = (char*)calloc(1, sizeof(char));
		for (int i = 0; i < 3*ImWidth * ImHeight; i++)
		{
			if (i % 3 == 0)
				*data1_temp = *(pBBuffer_8 + i / 3);
			else if(i % 3 == 1)
				*data1_temp = *(pGBuffer_8 + i / 3);
			else if(i % 3 == 2)
				*data1_temp = *(pRBuffer_8 + i / 3);
			//*data1_temp = 32;
			if (fwrite(data1_temp, sizeof(char), 1, fp) != 1)
				LOGE("BMP file write error\n");

		}
		fclose(fp);

		
		cst(pRBuffer_8, pGBuffer_8, pBBuffer_8, pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &cst_param_in, &cp);
		//nr(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &nr_param_in, &cp);
		//nr(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &nr_param_in, &cp);
		//nr(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &nr_param_in, &cp);
		//nr(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &nr_param_in, &cp);
		//nr(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &nr_param_in, &cp);
		//sharpen1(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &Sharpen_param_in, &cp);
		//sharpen2(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &Sharpen_param_in, &cp);
		//Equal(pYBuffer, pUBuffer, pVBuffer, ImWidth, ImHeight, &Equal_param_in, &cp);

		char yuv_path[300];

		sprintf_s(yuv_path, 200, "%s%s", temp_dir2.c_str(), ".yuv");
		std::cout << "//...........debug4 raw path............//" << endl;
		std::cout << yuv_path << endl;

		ofstream yuv422(yuv_path, ios::out | ios::binary);
		if (yuv422.fail())
		{

			LOGE("output yuv fil error!");
			return 0;
		}
		Word8u* data_temp = (Word8u*)calloc(1, sizeof(Word8u));

		if (yuv422.is_open())
		{


			for (int i = 0; i < 2 * ImWidth * ImHeight; i++)
			{
				if (i % 4 == 0)
				{
					*data_temp = *(pUBuffer + i / 2);
					//*data_temp = 0;
				}
				else if (i % 4 == 2)
				{
					*data_temp = *(pVBuffer + i / 2);
					//*data_temp = 0;
				}
				else 
				{
					*data_temp = *(pYBuffer + i / 2);
				}
				
				yuv422.write((char*)data_temp, 1);
		
			
			}
		}
	
		yuv422.close();

		
		cstYUV2RGB(pYBuffer, pUBuffer, pVBuffer, pRBuffer_8, pGBuffer_8, pBBuffer_8,  ImWidth, ImHeight, &cst_param_in, &cp);
		FILE* fp1;

		char bmp_path1[300];

		sprintf_s(bmp_path1, 200, "%s%s", temp_dir2.c_str(), "_final.bmp");
		std::cout << "//...........debug_final raw path............//" << endl;
		std::cout << bmp_path1 << endl;
	
		if (err = fopen_s(&fp1, bmp_path1, "wb"))
		{
			LOGE("BMP file read error\n");
		}


		//fwrite(&bfh, 8, 1, fp);//由于linux上4字节对齐，而信息头大小为54字节，第一部分14字节，第二部分40字节，所以会将第一部分补齐为16自己，直接用sizeof，打开图片时就会遇到premature end-of-file encountered错误
		fwrite(&bfh.bfType, sizeof(bfh.bfType), 1, fp1);
		fwrite(&bfh.bfSize, sizeof(bfh.bfSize), 1, fp1);
		fwrite(&bfh.bfReserved1, sizeof(bfh.bfReserved1), 1, fp1);
		fwrite(&bfh.bfReserved2, sizeof(bfh.bfReserved2), 1, fp1);
		fwrite(&bfh.bfOffBits, sizeof(bfh.bfOffBits), 1, fp1);
		fwrite(&bih, sizeof(BMPINFOHEADER_T), 1, fp1);

		char* data2_temp = (char*)calloc(1,sizeof(char));
		for (int i = 0; i < 3 * ImWidth * ImHeight; i++)
		{
			if (i % 3 == 0)
				*data2_temp = *(pBBuffer_8 + i / 3);
			else if (i % 3 == 1)
				*data2_temp = *(pGBuffer_8 + i / 3);
			else if (i % 3 == 2)
				*data2_temp = *(pRBuffer_8 + i / 3);
			//*data1_temp = 32;
			if (fwrite(data2_temp, sizeof(char), 1, fp1) != 1)
				LOGE("Final BMP file write error\n");

		}
		fclose(fp1);
	
	}//for end
	free(pBuffer);
	free(pBuffer_blc);
	free(pBufferTmp);
	free(pRBuffer);
	free(pGBuffer);
	free(pBBuffer);
	free(pRBuffer_8);
	free(pGBuffer_8);
	free(pBBuffer_8);
	free(pBufferMIPI);
	//

	return 0;
}