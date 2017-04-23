#include "FParticle.h"
#include "simple_allocate.h"
#include "simple_serialize.h"

FParticle* NewFParticle(unsigned int nSize)
{
	FParticle* lNew;
	if(!nSize) { return 0; }
	lNew = SMalloc(sizeof(FParticle) * nSize);
	while(nSize--)
	{
		lNew[nSize].iParticle = 0;
		lNew[nSize].eFlag = 0;
		lNew[nSize].nChannel = 0;
		lNew[nSize].lChannel = 0;
	}
	return lNew;
}

void FreeFParticle(FParticle* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--)
	{
		if(lMe[nSize].lChannel) { SFree(lMe[nSize].lChannel); }
	}
	SFree(lMe);
}

void SerializeFParticle(FParticle* lMe, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!lMe || !nSize) { return; }

	SerializeRaw(lMe, sizeof(FParticle), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(lMe[iIndex].lChannel, lMe[iIndex].nChannel, sizeof(int), ptrFile);
	}
}

FParticle* DeserializeFParticle(FParticle* lInto, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!lInto) { return 0; }

	lInto = DeserializeRaw(lInto, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		lInto[iIndex].lChannel = DeserializeRaw(lInto[iIndex].lChannel, 0, ptrFile);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lInto;
}