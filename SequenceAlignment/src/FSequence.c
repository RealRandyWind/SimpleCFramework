#include "FSequence.h"
#include <stdlib.h>
#include "simple_serialize.h"

FSequence* NewFSequence(unsigned int nLength, unsigned int nSize)
{
	FSequence* lNew;
	unsigned int nBytes;
	char* lData;
	if(!nLength || !nSize) { return 0; }
	lNew = (FSequence*) malloc(sizeof(FSequence) * nSize);
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

void FreeFSequence(FSequence* oMe, unsigned int nSize)
{
	_FreeFSequence(oMe, nSize);
}

void _FreeFSequence(void* ptrMe, unsigned int nSize)
{
	FSequence* oMe;
	if(!ptrMe || !nSize) { return; }
	oMe = (FSequence*)ptrMe;
	while(nSize--) { free(oMe[nSize].lData); }
	free(oMe);
}


void SerializeFSequence(FSequence* oSerialize, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!oSerialize || !nSize) { return; }

	SerializeRaw(oSerialize, sizeof(FSequence), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(oSerialize[iIndex].lData, 1, oSerialize[iIndex].nBytes, ptrFile);
	}
}

FSequence* DeserializeFSequence(FSequence* oDeserialize, unsigned int* ptrSize, FILE* ptrFile)
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