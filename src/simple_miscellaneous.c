#include "simple_miscellaneous.h"
#include "simple_allocate.h"

FEvent* _lMiscellaneousEvents = 0;

FEvent* NewFEvent(unsigned int nFunction, unsigned int nSize)
{
	FEvent* oNew;
	if(!nFunction || !nSize) { return 0; }
	oNew = SMalloc(sizeof(FEvent) * nSize);
	oNew->nFunction = nFunction;
	oNew->lFunction = SMalloc(sizeof(EventFunction) * (nFunction + 1));
	oNew->lFunction[0] = 0;
	oNew->lFunction[nFunction] = 0;
	return oNew;
}

void FreeFEvent(FEvent* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	SFree(lMe->lFunction);
	SFree(lMe);
}

void OnEvent(EventFunction Function, unsigned int eEvent, unsigned int bSet, FEvent* lEvent)
{
	unsigned int iFunction, nFunction, nBytes;
	EventFunction* lFunction;
	if(!Function || !lEvent) { return; }
	iFunction = 0;
	lFunction = lEvent[eEvent].lFunction;
	while((*lFunction) != Function && ++lFunction) { ++iFunction; }
	if(lEvent[eEvent].nFunction >= iFunction) { return; }
	if(bSet) { (*lFunction) = Function; return; }
	while(++lFunction) { (*lFunction) = (*(lFunction - 1)); }
}

void TriggerEvent(unsigned int eEvent, void* ptrWhat, unsigned int eType, FEvent* lEvent)
{
	EventFunction* lFunction;
	if(!lEvent || !lEvent[eEvent].nFunction) { return; }
	lFunction = lEvent[eEvent].lFunction;
	while(++lFunction) { (*lFunction)(ptrWhat, eType); }
}

FMemory* NewFMemory(unsigned long nBytes, unsigned int nSize)
{
	FMemory* lNew;
	unsigned int nByte, nChunk, iChunk;
	if(!nBytes || !nSize) { return 0; }
	lNew = (FMemory*) SMalloc(sizeof(FMemory) * nSize);
	nChunk = nBytes / NCHUNKBYTES + 1;
	nByte = nBytes % NCHUNKBYTES;
	while(nSize--)
	{
		lNew[nSize].nChunk = nChunk;
		lNew[nSize].nByte = nByte;
		lNew[nSize].lChunk = SMalloc(sizeof(chunk) * nChunk);
		iChunk = nChunk;
		lNew[nSize].lChunk[--iChunk] = SMalloc(nByte);
		while(iChunk--)
		{
			lNew[nSize].lChunk[iChunk] = SMalloc(NCHUNKBYTES);
		}

	}
	return lNew;
}

void FreeFMemory(FMemory* oMe, unsigned int nSize)
{
	unsigned int iChunk;
	if(!oMe || !nSize) { return; }
	while(nSize--)
	{
		iChunk = oMe[nSize].nChunk;
		while(iChunk--) { SFree(oMe[nSize].lChunk[iChunk]); }
		SFree(oMe[nSize].lChunk);
	}
}

unsigned int StringSize(const char* sMe)
{
	unsigned int nSize;
	if(!sMe) { return 0; }
	nSize = 0;
	while(sMe[nSize]) { ++nSize; }
	return nSize;
}

unsigned int StringBytes(const char* sMe)
{
	unsigned int nSize;
	if(!sMe) { return 0; }
	return StringSize(sMe) * sizeof(char);
}

char* NewString(const char* sMe)
{
	unsigned int nSize;
	char* sToReturn;
	if(!sMe) { return 0; }
	nSize = StringSize(sMe);
	sToReturn = (char*) SMalloc(sizeof(char) * nSize);
	while(nSize--) { sToReturn[nSize] = sMe[nSize]; }
	return sToReturn;
}

void* CopyRaw(void* ptrMe, unsigned int nBytes, void* ptrInto)
{
	char* rawFrom, *rawTo;
	if(!ptrMe || !nBytes) { return 0; }
	if(!ptrInto) { ptrInto = SMalloc(nBytes); }
	rawTo = (char*)ptrInto;
	rawFrom = (char*)ptrMe;
	while(nBytes--) { rawTo[nBytes] = rawFrom[nBytes]; }
	return ptrInto;
}