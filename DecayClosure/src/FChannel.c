#include "FChannel.h"
#include "simple_allocate.h"
#include "simple_serialize.h"

FChannel* NewFChannel(unsigned int nSize)
{
	FChannel* lNew;
	if(!nSize) { return 0; }
	lNew = SMalloc(sizeof(FChannel) * nSize);
	while(nSize--)
	{
		lNew[nSize].iChannel = 0;
		lNew[nSize].eFlag = 0;
		lNew[nSize].nMother = 0;
		lNew[nSize].nDaughter = 0;
		lNew[nSize].lMother = 0;
		lNew[nSize].lDaughter = 0;
	}
	return lNew;
}

void FreeFChannel(FChannel* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--)
	{
		if(lMe[nSize].lMother) { SFree(lMe[nSize].lMother); };
		if(lMe[nSize].lDaughter) { SFree(lMe[nSize].lDaughter); }
	}
	SFree(lMe);
}

void SerializeFChannel(FChannel* lMe, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!lMe || !nSize) { return; }

	SerializeRaw(lMe, sizeof(FChannel), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(lMe[iIndex].lMother, lMe[iIndex].nMother, sizeof(int), ptrFile);
		SerializeRaw(lMe[iIndex].lDaughter, lMe[iIndex].nDaughter, sizeof(int), ptrFile);
	}
}

FChannel* DeserializeFChannel(FChannel* lInto, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!lInto) { return 0; }

	lInto = DeserializeRaw(lInto, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		lInto[iIndex].lMother = DeserializeRaw(lInto[iIndex].lMother, 0, ptrFile);
		lInto[iIndex].lDaughter = DeserializeRaw(lInto[iIndex].lDaughter, 0, ptrFile);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lInto;
}