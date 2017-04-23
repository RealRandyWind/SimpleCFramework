#include "FScore.h"
#include "simple_allocate.h"
#include "simple_serialize.h"

void _FScoreLData(unsigned int** lData, unsigned int nMin, unsigned int nMax)
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
	lNew = (FScore*) SMalloc(sizeof(FScore) * nSize);
	nBytes = sizeof(unsigned int) * nMin * nMax + sizeof(unsigned int*) * nMin;
	while(nSize--)
	{
		lData = (unsigned int**) SMalloc(nBytes);
		_FScoreLData(lData, nMin, nMax);
		lNew[nSize].eFlag = 0;
		lNew[nSize].nMin = nMin;
		lNew[nSize].nMax = nMax;
		lNew[nSize].nBytes = nBytes;
		lNew[nSize].lData = lData;
	}
	return lNew;
}

void FreeFScore(FScore* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--) { SFree(lMe[nSize].lData); }
	SFree(lMe);
}


void SerializeFScore(FScore* lMe, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!lMe || !nSize) { return; }

	SerializeRaw(lMe, sizeof(FScore), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(lMe[iIndex].lData, 1, lMe[iIndex].nBytes, ptrFile);
	}
}

FScore* DeserializeFScore(FScore* lInto, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!lInto) { return 0; }

	lInto = DeserializeRaw(lInto, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		lInto[iIndex].lData = DeserializeRaw(lInto[iIndex].lData, 0, ptrFile);
		_FScoreLData(lInto[iIndex].lData, lInto[iIndex].nMin, lInto[iIndex].nMax);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lInto;
}