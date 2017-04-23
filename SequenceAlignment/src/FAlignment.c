#include "FAlignment.h"
#include "simple_allocate.h"
#include "simple_serialize.h"

FAlignment* NewFAlignment(unsigned int nLength, unsigned int nSize)
{
	FAlignment* lNew;
	unsigned int nBytes;
	char* lData;
	if(!nLength || !nSize) { return 0; }
	lNew = (FAlignment*) SMalloc(sizeof(FAlignment) * nSize);
	nBytes = sizeof(char) * nLength;
	while(nSize--)
	{
		lData = (char*) SMalloc(nBytes);
		lNew[nSize].nLength = nLength;
		lNew[nSize].nBytes = nBytes;
		lNew[nSize].lData = lData;
	}

	return lNew;
}

void FreeFAlignment(FAlignment* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--) { SFree(lMe[nSize].lData); }
	SFree(lMe);
}


void SerializeFAlignment(FAlignment* lMe, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!lMe || !nSize) { return; }

	SerializeRaw(lMe, sizeof(FAlignment), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(lMe[iIndex].lData, 1, lMe[iIndex].nBytes, ptrFile);
	}
}

FAlignment* DeserializeFAlignment(FAlignment* lInto, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!lInto) { return 0; }

	lInto = DeserializeRaw(lInto, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		lInto[iIndex].lData = DeserializeRaw(lInto[iIndex].lData, 0, ptrFile);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lInto;
}