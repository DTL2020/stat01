// stat01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "math.h"

int ArrSamples[10] = { 52, 46, 54, 20, 50, 48, 51, 53, 45, 50 };

int ArrSADs[10][10] = {};

int ArrOut[10] = {};

int VectMinSumSADs[10] = {};

int iVectIncludedSamples[10] = {};

int thSAD = 5;

int main()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			ArrSADs[i][j] = abs(ArrSamples[i] - ArrSamples[j]);
		}
	}

	//calc vect min sums sads
	for (int i = 0; i < 10; i++)
	{
		int minsunsads = 0;
		for (int j = 0; j < 10; j++)
		{
			minsunsads += ArrSADs[i][j];
		}

		VectMinSumSADs[i] = minsunsads;
	}

	int idx_minsad = 0;
	int minsumsads = 10e10;
	for (int i = 0; i < 10; i++)
	{
		if (VectMinSumSADs[i] < minsumsads)
		{
			minsumsads = VectMinSumSADs[i];
			idx_minsad = i;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (ArrSADs[idx_minsad][i] < thSAD )
		{
			iVectIncludedSamples[i] = 1;
		}
		else
		{
			iVectIncludedSamples[i] = 0;
		}

	}


	//calc output
	for (int i = 0; i < 10; i++)
	{
		float fMidval2 = 0;
		int cnt = 0;

		if (iVectIncludedSamples[i] == 0) // skip proc
		{
			ArrOut[i] = ArrSamples[i];
			continue;
		}

		for (int j = 0; j < 10; j++)
		{
			if ((iVectIncludedSamples[j] != 0) || (ArrSADs[i][j] < thSAD))
			{
				fMidval2 += ArrSamples[j];
				cnt++;
			}
			else
				if (j == i)
				{
					fMidval2 += ArrSamples[j];
					cnt++;
				}
/*			if (ArrSADs[i][j] < thSAD)
			{
				fMidval2 += ArrSamples[j];
				cnt++;
			}*/
		}

		fMidval2 /= cnt;
		ArrOut[i] = round(fMidval2);
	}

	// calc psnr
	float fMid_val = 0;
	for (int i = 0; i < 10; i++)
	{
		fMid_val += ArrSamples[i];
	}
	fMid_val /= 10;


	float fNoise = 0;
	for(int i=0; i<10; i++)
	{ 
		fNoise += (ArrOut[i] - fMid_val)*(ArrOut[i] - fMid_val);
	}

	fNoise /= 10;

	float fpsnr = 10e10;
	
	if (fNoise != 0)
	{
		fpsnr = fMid_val* fMid_val / fNoise;
	}

	int idbr = 0;

}

