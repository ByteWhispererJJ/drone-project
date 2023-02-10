#pragma once
#include <iostream>
#include "Utils.h"

class Data 
{
	public:
	static unsigned char* decryptWebSocketData(unsigned char* input, unsigned char mask[4], int lnt)
	{
		unsigned char* result = (unsigned char*)malloc(lnt);
		for (int a = 0;a < lnt;a++) 
		{
			result[a] = input[a] ^ mask[a % 4];
		}
		return result;
	}

	static void convertWebSocketData(unsigned char* data, int lnt, unsigned char*& dataout, int& lntout)
	{
		unsigned char descriptor = data[0];
		if (descriptor != 129) 
		{
			std::cout << "error data conv!" << std::endl;
		}
		unsigned char mask_msglnt = data[1];
		unsigned char mask[4] = {data[2], data[3], data[4], data[5]};
		unsigned char useMask = (mask_msglnt & 0b1000000) != 0;
		unsigned char msglength = mask != 0 ? mask_msglnt - 128 : mask_msglnt;
		unsigned char* temp = (unsigned char*)malloc(msglength);
		memcpy(temp, data + 6, msglength);
		dataout = Data::decryptWebSocketData(temp , mask, msglength);
		lntout = msglength;
	}

	static void createWebSocketData(char* datain, int lnt, unsigned char*& dataout, int& lntout) 
	{
		lntout = lnt + 2;
		dataout = (unsigned char*)malloc(lntout);
		
		dataout[0] = 129;
		dataout[1] = lnt;
		for (int a = 0; a < lnt; a++) 
		{
			dataout[a + 2] = datain[a];
		}


	}
};