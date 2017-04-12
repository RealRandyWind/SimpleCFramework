#include "FScore.h"
#include <stdlib.h>
#include "simple_serialize.h"

void Fx_FScoreLData(unsigned int** lData, unsigned int nMin, unsigned int nMax)
{
	lData[0] = (unsigned int*)(lData + nMin);
	while(nMin--) { lData[nMin] = lData[0] + nMin * nMax; }
}

FScore* NewFScore(unsigned int nMin, unsigned int nMax, unsigned int nSize)
{
	FScore* lNew;
	unsigned int nBytes;
	unsigned int** lData;
	if(!nMin || !nMax || !nSize) { return 0; }
	lNew = (FScore*) malloc(sizeof(FScore) * nSize);
	nBytes = sizeof(unsigned int) * nMin * nMax + sizeof(unsigned int*) * nMin;
	while(nSize--)
	{
		lData = (unsigned int**) malloc(nBytes);
		Fx_FScoreLData(lData, nMin, nMax);
		lNew[nSize].eFlag = 0;
		lNew[nSize].nMin = nMin;
		lNew[nSize].nMax = nMax;
		lNew[nSize].nBytes = nBytes;
		lNew[nSize].lData = lData;
	}

	return lNew;
}

void FreeFScore(FScore* oMe, unsigned int nSize)
{
	_FreeFScore(oMe, nSize);
}

void _FreeFScore(void* ptrMe, unsigned int nSize)
{
	FScore* oMe;
	if(!ptrMe || !nSize) { return; }
	oMe = (FScore*)ptrMe;
	while(nSize--) { free(oMe[nSize].lData); }
	free(oMe);
}


void SerializeFScore(FScore* oSerialize, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!oSerialize || !nSize) { return; }

	SerializeRaw(oSerialize, sizeof(FScore), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(oSerialize[iIndex].lData, 1, oSerialize[iIndex].nBytes, ptrFile);
	}
}

FScore* DeserializeFScore(FScore* oDeserialize, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!oDeserialize) { return 0; }

	oDeserialize = DeserializeRaw(oDeserialize, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		oDeserialize[iIndex].lData = DeserializeRaw(oDeserialize[iIndex].lData, 0, ptrFile);
		Fx_FScoreLData(oDeserialize[iIndex].lData, oDeserialize[iIndex].nMin, oDeserialize[iIndex].nMax);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return oDeserialize;
}