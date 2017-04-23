#ifndef SIMPLE_COLLECTION_H
#define SIMPLE_COLLECTION_H

#include "simple_miscellaneous.h"

typedef struct FKeyValue
{
	void* ptrKey;
	void* ptrValue;
} FKeyValue;

typedef struct FMap
{
	unsigned int nSize;
	unsigned int _nSize;
	HashFunction Hash;
	CompareFunction Compare;
	void* _ptrMap;
} FMap;

typedef struct FSet
{
	unsigned int nSize;
	unsigned int _nSize;
	CompareFunction Compare;
	void* _ptrSet;	
} FSet;

typedef struct FQueue
{
	unsigned int nSize;
	unsigned int _nSize;
	unsigned int _iFirst;
	void* _ptrFirst;
	void* _ptrLast;
} FQueue;

typedef struct FStack
{
	unsigned int nSize;
	unsigned int _nSize;
	void* _ptrTop;
} FStack;

FMap* NewFMap(HashFunction Hash, CompareFunction Compare, unsigned int nSize);
void FreeFMap(FMap* lMe, unsigned int nSize);
void* GetFMap(void* ptrKey, FMap* oMap);
void* SetFMap(void* ptrKey, void* ptrValue, FMap* oMap);
void* UnsetFMap(void* ptrKey, FMap* oMap);

FSet* NewFSet(CompareFunction Compare, unsigned int nSize);
void FreeFSet(FSet* lMe, unsigned int nSize);
void AddFSet(void* ptrValue, FSet* oMe);
void* RemoveFSet(void* ptrValue, FSet* oMe);
void* FindFSet(void* ptrValue, FSet* oMe);

FQueue* NewFQueue(unsigned int nSize);
void FreeFQueue(FQueue* lMe, unsigned int nSize);
void* PeekFQueue(FQueue* oMe);
void* PollFQueue(FQueue* oMe);
void OfferFQueue(void* ptrValue, FQueue* oMe);
void* PeekLastFQueue(FQueue* oMe);
void* PollLastFQueue(FQueue* oMe);
void OfferFirstFQueue(void* ptrValue, FQueue* oMe);

FStack* NewFStack(unsigned int nSize);
void FreeFStack(FStack* lMe, unsigned int nSize);
void PushFStack(void* ptrValue, FStack* oMe);
void* PeekFStack(FStack* oMe);
void* PopFStack(FStack* oMe);

void OnCollectionEvent(EventFunction Function, unsigned int eEvent, unsigned int bSet);

#endif