#include <stdio.h>
#include <stdlib.h>
#include "simple_allocate.h"
#include "simple_serialize.h"
#include "simple_random.h"
#include "simple_collection.h"
#include "FParticle.h"
#include "FChannel.h"

unsigned int  _nEntryMaxBits = sizeof(unsigned int) * NBYTEBITS;

typedef struct FParticleDB
{
	unsigned int nParticle;
	unsigned int nChannel;
	FParticle* lParticle;
	FChannel* lChannel;
} FParticleDB;

typedef struct FDecayClosureFlag
{
	unsigned int nFlag;
	unsigned int* _lEntry;
} FDecayClosureFlag;

typedef struct FDecayClosureStack
{
	unsigned int nSize;
	unsigned int* _lValue;
} FDecayClosureStack;

FDecayClosureFlag* NewFDecayClosureFlag(unsigned nEntry, unsigned int nSize)
{
	unsigned int iEntry;
	FDecayClosureFlag* lNew;
	if(!nSize || !nEntry) { return 0; }
	lNew = (FDecayClosureFlag*) SMalloc(sizeof(FDecayClosureFlag) * nSize);
	while(nSize--)
	{
		lNew[nSize].nFlag = 0;
		lNew[nSize]._lEntry = SMalloc(sizeof(unsigned int) * nEntry);
		iEntry = nEntry;
		while(iEntry--) { lNew[nSize]._lEntry[nEntry] = 0; }
	}
	return lNew;
}

FDecayClosureStack* NewFDecayClosureStack(unsigned int nMaxSize)
{
	FDecayClosureStack* oNew;
	if(!nMaxSize) { return 0; }
	oNew = (FDecayClosureStack*) SMalloc(sizeof(FDecayClosureStack));
	oNew->nSize = 0;
	oNew->_lValue = SMalloc(sizeof(unsigned int) * nMaxSize);
	return oNew;
}

int PopFDecayClosureStack(FDecayClosureStack* oMe)
{
	return oMe->_lValue[--oMe->nSize];
}

void PushFDecayClosureStack(int iValue, FDecayClosureStack* oMe)
{
	oMe->_lValue[oMe->nSize++] = iValue;
}

void FlagBit(unsigned int iBit, FDecayClosureFlag* oFlag)
{
	oFlag->_lEntry[iBit / _nEntryMaxBits] |= 1 << (iBit % _nEntryMaxBits);
	++oFlag->nFlag;
}

unsigned int CheckBit(unsigned int iBit, FDecayClosureFlag* oFlag)
{
	return oFlag->_lEntry[iBit / _nEntryMaxBits] & (1 << (iBit % _nEntryMaxBits));
}

FParticle* GenerateParticle(unsigned int nSize, unsigned int nChannel)
{
	FParticle* lNew;
	lNew = NewFParticle(nSize);
	while(nSize--)
	{

	}
	return lNew;
}

FChannel* GenerateChannel(unsigned int nSize, unsigned int nParticle)
{
	FChannel* lNew;
	lNew = NewFChannel(nSize);
	while(nSize--)
	{

	}
	return lNew;
}

unsigned int* DecayClosure(int* lParticle, unsigned int nParticle, FParticleDB* oData, unsigned int* ptrSize)
{

	unsigned int nSize, iParticle;
	unsigned int* lMother;
	FDecayClosureFlag* oFlag;
	FDecayClosureStack* oStack;
	if(!lParticle || !nParticle) { return 0; }
	oFlag = NewFDecayClosureFlag(nParticle, oData->nParticle);
	oStack = NewFDecayClosureStack(oData->nParticle);
	lMother = 0;
	nSize = 0;
	for (iParticle = 0; iParticle < nParticle; ++iParticle)
	{
		PushFDecayClosureStack(&lParticle[iParticle], oStack);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lMother;
}

int main(int argc, char const *argv[])
{
	DecayClosure(0,0,0,0);
	return 0;
}