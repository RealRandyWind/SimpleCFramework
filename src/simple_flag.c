#include "simple_flag.h"
#include "simple_allocate.h"
#include "simple_miscellaneous.h"
#include "simple_serialize.h"
#include <stdlib.h>

unsigned long  _nEntryBits = sizeof(unsigned int) * NBYTEBITS;

FFlag* NewFFlag(unsigned int nEntry, unsigned int nSize)
{
	FFlag* lNew;
	if(!nSize || !nEntry) { return 0; }
	lNew = (FFlag*)SMalloc(sizeof(FFlag));
	while(nSize--)
	{
		lNew[nSize].nEntry = nEntry;
		lNew[nSize].lEntry = (unsigned int*) SMalloc(sizeof(unsigned int) * nEntry);
	}
	return lNew;
}

void FreeFFlag(FFlag* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--) { SFree(lMe[nSize].lEntry); }
	SFree(lMe);
}

void SerializeFFlag(FFlag* lMe, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!lMe || !nSize) { return; }

	SerializeRaw(lMe, sizeof(FFlag), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(lMe[iIndex].lEntry, sizeof(unsigned int), lMe[iIndex].nEntry, ptrFile);
	}
}

FFlag* DeserializeFFlag(FFlag* lInto, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!lInto) { return 0; }

	lInto = DeserializeRaw(lInto, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		lInto[iIndex].lEntry = DeserializeRaw(lInto[iIndex].lEntry, 0, ptrFile);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lInto;
}

void SetFFlag(unsigned long iBit, FFlag* oMe)
{
	if(iBit >= oMe->nEntry * _nEntryBits) { return; }
	oMe->lEntry[iBit / _nEntryBits] |= 1 << (iBit % _nEntryBits);
}

void UnSetFFlag(unsigned long iBit, FFlag* oMe)
{
	if(iBit >= oMe->nEntry * _nEntryBits) { return; }
	oMe->lEntry[iBit / _nEntryBits] &= ~(1 << (iBit % _nEntryBits));
}

void ToggleFFlag(unsigned long iBit, FFlag* oMe)
{
	if(iBit >= oMe->nEntry * _nEntryBits) { return; }
	oMe->lEntry[iBit / _nEntryBits] ^= 1 << (iBit % _nEntryBits);
}

void RShiftFFlag(unsigned long nShift, FFlag* oMe, FFlag* oInto)
{
	unsigned int iEntry;
	if(!oMe) { return; }
	if(!oInto) { oInto = oMe; }
	iEntry = oMe->nEntry;
	while(iEntry--) { oInto->lEntry[iEntry] = oMe->lEntry[iEntry] >> nShift; }
}

void LShiftFFlag(unsigned long nShift, FFlag* oMe, FFlag* oInto)
{
	unsigned int iEntry;
	if(!oMe) { return; }
	if(!oInto) { oInto = oMe; }
	iEntry = oMe->nEntry;
	while(iEntry--) { oInto->lEntry[iEntry] = oMe->lEntry[iEntry] << nShift; }
}

void OrFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto)
{
	unsigned int iEntry;
	if(!oMe) { return; }
	if(!oInto) { oInto = oMe; }
	iEntry = oMe->nEntry;
	while(iEntry--)
	{
		oInto->lEntry[iEntry] = oMe->lEntry[iEntry] | oWith->lEntry[iEntry];
	}
}

void AndFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto)
{
	unsigned int iEntry;
	if(!oMe) { return; }
	if(!oInto) { oInto = oMe; }
	iEntry = oMe->nEntry;
	while(iEntry--)
	{
		oInto->lEntry[iEntry] = oMe->lEntry[iEntry] | oWith->lEntry[iEntry];
	}
}

void XorFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto)
{
	unsigned int iEntry;
	if(!oMe) { return; }
	if(!oInto) { oInto = oMe; }
	iEntry = oMe->nEntry;
	while(iEntry--)
	{
		oInto->lEntry[iEntry] = oMe->lEntry[iEntry] ^ oWith->lEntry[iEntry];
	}
}

void DiffFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto)
{
	unsigned int iEntry;
	if(!oMe) { return; }
	if(!oInto) { oInto = oMe; }
	iEntry = oMe->nEntry;
	while(iEntry--)
	{
		oInto->lEntry[iEntry] = (~oMe->lEntry[iEntry]) & oWith->lEntry[iEntry];
	}
}

void NotFFlag(FFlag* oMe, FFlag* oInto)
{
	unsigned int iEntry;
	if(!oMe) { return; }
	if(!oInto) { oInto = oMe; }
	iEntry = oMe->nEntry;
	while(iEntry--) { oInto->lEntry[iEntry] = ~oMe->lEntry[iEntry]; }
}

unsigned long LengthFFlag(FFlag* oMe)
{
	unsigned long nLength;
	unsigned int iEntry, eEntry, iBit;
	if(!oMe) { return 0; }
	iEntry = oMe->nEntry;
	nLength = 0;
	while(iEntry--)
	{
		eEntry = oMe->lEntry[iEntry];
		/* TODO implement less ignorant version */
		iBit = NFLAGENTRYBITS;
		while(iBit--) { nLength += (eEntry << iBit) & 1; }
	}
	return nLength;
}