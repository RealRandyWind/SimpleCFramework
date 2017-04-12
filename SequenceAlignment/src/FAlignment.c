#include "FAlignment.h"
#include <stdlib.h>
#include "simple_serialize.h"

FAlignment* NewFAlignment(unsigned int nLength, unsigned int nSize)
{
	FAlignment* lNew;
	unsigned int nBytes;
	char* lData;
	if(!nLength || !nSize) { return 0; }
	lNew = (FAlignment*) malloc(sizeof(FAlignment) * nSize);
	nBytes = sizeof(char) * nLength;
	while(nSize--)
	{
		lData = (char*) malloc(nBytes);
		lNew[nSize].nLength = nLength;
		lNew[nSize].nBytes = nBytes;
		lNew[nSize].lData = lData;
	}

	return lNew;
}

void FreeFAlignment(FAlignment* oMe, unsigned int nSize)
{
	_FreeFAlignment(oMe, nSize);
}

void _FreeFAlignment(void* ptrMe, unsigned int nSize)
{
	FAlignment* oMe;
	if(!ptrMe || !nSize) { return; }
	oMe = (FAlignment*)ptrMe;
	while(nSize--) { free(oMe[nSize].lData); }
	free(oMe);
}


void SerializeFAlignment(FAlignment* oSerialize, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!oSerialize || !nSize) { return; }

	SerializeRaw(oSerialize, sizeof(FAlignment), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(oSerialize[iIndex].lData, 1, oSerialize[iIndex].nBytes, ptrFile);
	}
}

FAlignment* DeserializeFAlignment(FAlignment* oDeserialize, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!oDeserialize) { return 0; }

	oDeserialize = DeserializeRaw(oDeserialize, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		oDeserialize[iIndex].lData = DeserializeRaw(oDeserialize[iIndex].lData, 0, ptrFile);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return oDeserialize;
}