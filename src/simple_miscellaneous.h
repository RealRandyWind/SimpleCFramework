#ifndef SIMPLE_MISCELLANEOUS_H
#define SIMPLE_MISCELLANEOUS_H

enum EMiscellaneousEvent
{
	MiscellaneousEError,
	MiscellaneousEWarning,
	_EMiscellaneousSize
};

typedef void (*FreeFunction)(void* ptrMe, unsigned int nSize);
typedef void* (*NewFunction)(void* ptrIninitialize, unsigned int nSize);
typedef void* (*CopyFunction)(void* ptrMe);
typedef void (*EventFunction)(void* ptrWhat, unsigned int eType);
typedef int (*CompareFunction)(void* ptrMe, void* ptrWith);
typedef void* (*HashFunction)(void* ptrMe);

typedef struct FMap
{
	unsigned int nSize;
	HashFunction _Hash;
	CompareFunction _Compare;
	void* _ptrMap; 	
} FMap;

typedef struct FQueue
{
	unsigned int nSize;
	CompareFunction _Compare;
	void* _ptrFirst;
	void* _ptrLast;
} FQueue;

typedef struct FStack
{
	unsigned int nSize;
	void* _ptrTop;
} FStack;

typedef struct FEvent
{
	EventFunction* lFunction;
	unsigned int nFunction;
	unsigned int eEvent;
} FEvent;

FEvent* NewFEvent(unsigned int nFunction, unsigned int nSize);
void FreeFEvent(FEvent* oMe, unsigned int nSize);
void _FreeFEvent(void* ptrMe, unsigned int nSize);
void* _NewFEvent(const void* ptrInitialize, unsigned int nSize);

void OnMiscellaneousEvent(EventFunction Function, unsigned int eEvent, unsigned int bSet);

#endif