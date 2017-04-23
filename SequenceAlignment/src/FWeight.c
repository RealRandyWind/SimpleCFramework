#include "FWeight.h"
#include "simple_allocate.h"
#include "simple_serialize.h"

void _FWeightLData(unsigned int** lData, unsigned int nMin, unsigned int nMax)
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
	lNew = (FWeight*) SMalloc(sizeof(FWeight) * nSize);
	nBytes = sizeof(unsigned int) * nSymbols * nSymbols + sizeof(unsigned int*) * nSymbols;
	while(nSize--)
	{
		lData = (unsigned int**) SMalloc(nBytes);
		_FWeightLData(lData, nSymbols, nSymbols);
		lNew[nSize].nSymbols = nSymbols;
		lNew[nSize].nBytes = nBytes;
		lNew[nSize].lData = lData;
	}

	return lNew;
}

void FreeFWeight(FWeight* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--) { SFree(lMe[nSize].lData); }
	SFree(lMe);
}


void SerializeFWeight(FWeight* lMe, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!lMe || !nSize) { return; }

	SerializeRaw(lMe, sizeof(FWeight), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(lMe[iIndex].lData, 1, lMe[iIndex].nBytes, ptrFile);
	}
}

FWeight* DeserializeFWeight(FWeight* lInto, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!lInto) { return 0; }

	lInto = DeserializeRaw(lInto, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		lInto[iIndex].lData = DeserializeRaw(lInto[iIndex].lData, 0, ptrFile);
		_FWeightLData(lInto[iIndex].lData, lInto[iIndex].nSymbols, lInto[iIndex].nSymbols);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lInto;
}