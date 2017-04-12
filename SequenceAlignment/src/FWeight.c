#include "FWeight.h"
#include <stdlib.h>
#include "simple_serialize.h"

void Fx_FWeightLData(unsigned int** lData, unsigned int nMin, unsigned int nMax)
{
	lData[0] = (unsigned int*)(lData + nMin);
	while(nMin--) { lData[nMin] = lData[0] + nMin * nMax; }
}

FWeight* NewFWeight(unsigned int nSymbols, unsigned int nSize)
{
	FWeight* lNew;
	unsigned int nBytes;
	unsigned int** lData;
	if(!nSymbols || !nSize) { return 0; }
	lNew = (FWeight*) malloc(sizeof(FWeight) * nSize);
	nBytes = sizeof(unsigned int) * nSymbols * nSymbols + sizeof(unsigned int*) * nSymbols;
	while(nSize--)
	{
		lData = (unsigned int**) malloc(nBytes);
		Fx_FWeightLData(lData, nSymbols, nSymbols);
		lNew[nSize].nSymbols = nSymbols;
		lNew[nSize].nBytes = nBytes;
		lNew[nSize].lData = lData;
	}

	return lNew;
}

void FreeFWeight(FWeight* oMe, unsigned int nSize)
{
	_FreeFWeight(oMe, nSize);
}

void _FreeFWeight(void* ptrMe, unsigned int nSize)
{
	FWeight* oMe;
	if(!ptrMe || !nSize) { return; }
	oMe = (FWeight*)ptrMe;
	while(nSize--) { free(oMe[nSize].lData); }
	free(oMe);
}


void SerializeFWeight(FWeight* oSerialize, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!oSerialize || !nSize) { return; }

	SerializeRaw(oSerialize, sizeof(FWeight), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(oSerialize[iIndex].lData, 1, oSerialize[iIndex].nBytes, ptrFile);
	}
}

FWeight* DeserializeFWeight(FWeight* oDeserialize, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!oDeserialize) { return 0; }

	oDeserialize = DeserializeRaw(oDeserialize, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		oDeserialize[iIndex].lData = DeserializeRaw(oDeserialize[iIndex].lData, 0, ptrFile);
		Fx_FWeightLData(oDeserialize[iIndex].lData, oDeserialize[iIndex].nSymbols, oDeserialize[iIndex].nSymbols);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return oDeserialize;
}