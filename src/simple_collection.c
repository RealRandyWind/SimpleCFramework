#include "simple_collection.h"
#include "simple_allocate.h"

typedef void* _pointer;

typedef struct _FMap
{
	unsigned int nEntry;
	unsigned int nNext;
	FKeyValue* lEntry;
	struct _FMap* lNext;
} _FMap;

typedef struct _FSet
{
	unsigned int nValue;
	unsigned int nNext;
	_pointer* lValue;
	struct _FSet* lNext;
} _FSet;

typedef struct _FQueue
{
	void* ptrValue;
	struct _FQueue* oPrevious;
	struct _FQueue* oNext;
} _FQueue;

typedef struct _FStack
{
	void* ptrValue;
	struct _FStack* oNext;
} _FStack;


FMap* NewFMap(HashFunction Hash, CompareFunction Compare, unsigned int nSize)
{
	FMap* lNew;
	if(!nSize) { return 0; }
	lNew = SMalloc(sizeof(FMap) * nSize);
	while(nSize--)
	{
		lNew[nSize].nSize = 0;
		lNew[nSize].Hash = Hash;
		lNew[nSize].Compare = Compare;
		lNew[nSize]._ptrMap = 0;
	}
	return lNew;
}

void FreeFMap(FMap* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	SFree(lMe);
}

FSet* NewFSet(CompareFunction Compare, unsigned int nSize)
{
	FSet* lNew;
	if(!nSize) { return 0; }
	lNew = SMalloc(sizeof(FSet) * nSize);
	while(nSize--)
	{
		lNew[nSize].nSize = 0;
		lNew[nSize].Compare = Compare;
		lNew[nSize]._ptrSet = 0;
	}
	return lNew;
}

void FreeFSet(FSet* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	SFree(lMe);
}

FQueue* NewFQueue(unsigned int nSize)
{
	FQueue* lNew;
	if(!nSize) { return 0; }
	lNew = SMalloc(sizeof(FQueue) * nSize);
	while(nSize--)
	{
		lNew[nSize].nSize = 0;
		lNew[nSize]._nSize = 0;
		lNew[nSize]._iFirst = 0;
		lNew[nSize]._ptrFirst = 0;
		lNew[nSize]._ptrLast = 0;
	}
	return lNew;
}

void FreeFQueue(FQueue* lMe, unsigned int nSize)
{
	_FQueue* oFirst, *oFree;
	if(!lMe || !nSize) { return; }
	while(nSize--)
	{
		oFirst = lMe[nSize]._ptrFirst;
		while(oFirst) {
			oFree = oFirst;
			oFirst = oFirst->oNext;
			oFree->oNext = 0;
			SFree(oFree);
		}
	}
	SFree(lMe);
}

void* PeekFQueue(FQueue* oMe)
{
	if(!oMe) { return 0; }
	return oMe->_ptrFirst;
}

void* PollFQueue(FQueue* oMe)
{
	_FQueue* oFirst;
	void* ptrValue;
	if(!oMe || !oMe->_ptrFirst) { return 0; }
	oFirst = oMe->_ptrFirst;
	oMe->_ptrFirst = oFirst->oNext;
	if(oFirst->oNext) { oFirst->oNext->oPrevious = 0; }
	if(oFirst == oMe->_ptrLast) { oMe->_ptrLast = oMe->_ptrFirst; }
	ptrValue = oFirst->ptrValue;
	SFree(oFirst);
	--oMe->nSize;
	--oMe->_nSize;
	return ptrValue;
}

void OfferFQueue(void* ptrValue, FQueue* oMe)
{
	_FQueue* oLast;
	if(!oMe || !ptrValue) { return; }
	oLast = (_FQueue*) SMalloc(sizeof(_FQueue));
	oLast->ptrValue = ptrValue;
	oLast->oNext = 0;
	oLast->oPrevious = oMe->_ptrLast;
	if(oMe->_ptrLast) { oLast->oPrevious->oNext = oLast; }
	if(oMe->_ptrLast == oMe->_ptrFirst) { oMe->_ptrFirst = oLast; }
	oMe->_ptrLast = oLast;
	++oMe->nSize;
	++oMe->_nSize;
}

void* PeekLastFQueue(FQueue* oMe)
{
	if(!oMe) { return 0; }
	return oMe->_ptrLast;
}

void* PollLastFQueue(FQueue* oMe)
{
	_FQueue* oLast;
	void* ptrValue;
	if(!oMe || !oMe->_ptrLast) { return 0; }
	oLast = oMe->_ptrLast;
	oMe->_ptrLast = oLast->oPrevious;
	if(oLast->oPrevious) { oLast->oPrevious->oNext = 0; }
	if(oLast == oMe->_ptrFirst) { oMe->_ptrFirst = oMe->_ptrLast; }
	ptrValue = oLast->ptrValue;
	SFree(oLast);
	--oMe->nSize;
	--oMe->_nSize;
	return ptrValue;
}

void OfferFirstFQueue(void* ptrValue, FQueue* oMe)
{
	_FQueue* oFirst;
	if(!oMe || !ptrValue) { return; }
	oFirst = (_FQueue*) SMalloc(sizeof(_FQueue));
	oFirst->ptrValue = ptrValue;
	oFirst->oNext = oMe->_ptrFirst;
	oFirst->oPrevious = 0;
	if(oMe->_ptrFirst) { oFirst->oNext->oPrevious = oFirst; }
	if(oMe->_ptrLast == oMe->_ptrFirst) { oMe->_ptrLast = oFirst; }
	oMe->_ptrLast = oFirst;
	++oMe->nSize;
	++oMe->_nSize;
}


FStack* NewFStack(unsigned int nSize)
{
	FStack* lNew;
	if(!nSize) { return 0; }
	lNew = SMalloc(sizeof(FStack) * nSize);
	while(nSize--)
	{
		lNew[nSize].nSize = 0;
		lNew[nSize]._nSize = 0;
		lNew[nSize]._ptrTop = 0;
	}
	return lNew;
}

void FreeFStack(FStack* lMe, unsigned int nSize)
{
	_FStack* oTop, *oFree;
	if(!lMe || !nSize) { return; }
	while(nSize--)
	{
		oTop = lMe[nSize]._ptrTop;
		while(oTop) {
			oFree = oTop;
			oTop = oTop->oNext;
			oFree->oNext = 0;
			SFree(oFree);
		}
	}
	SFree(lMe);
}

void PushFStack(void* ptrValue, FStack* oMe)
{
	_FStack* oTop;
	if(!oMe || !ptrValue) { return; }
	oTop = (_FStack*) SMalloc(sizeof(_FStack));
	oTop->ptrValue = ptrValue;
	oTop->oNext = oMe->_ptrTop;
	oMe->_ptrTop = oTop;
	++oMe->nSize;
	++oMe->_nSize;
}

void* PeekFStack(FStack* oMe)
{
	if(!oMe) { return 0; }
	return oMe->_ptrTop;
}

void* PopFStack(FStack* oMe)
{
	_FStack* oTop;
	void* ptrValue;
	if(!oMe || !oMe->_ptrTop) { return 0; }
	oTop = oMe->_ptrTop;
	oMe->_ptrTop = oTop->oNext;
	ptrValue = oTop->ptrValue;
	SFree(oTop);
	--oMe->nSize;
	--oMe->_nSize;
	return ptrValue;
}

void OnCollectionEvent(EventFunction Function, unsigned int eEvent, unsigned int bSet)
{

}