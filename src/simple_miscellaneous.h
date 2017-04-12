#ifndef SIMPLE_MISCELLANEOUS_H
#define SIMPLE_MISCELLANEOUS_H

enum EMiscellaneousEvent
{
	EMiscellaneousError,
	EMiscellaneousWarning,
	NEMiscellaneous
};

typedef struct FMap
{
	void* ptrValue;
	unsigned int _nNext;
	struct FMap* _lNext; 	
} FMap;

typedef struct FEvent
{
	unsigned int eType;
	void (*Function)(unsigned int* ptrWhat, unsigned int eType);
	unsigned int _nNext;
	struct FEvent* _lNext;
} FEvent;

FEvent* NewFEvent(unsigned int nEvents, unsigned int nSize);
void FreeFEvent(FEvent* oMe, unsigned int nSize);
void _FreeFEvent(void* ptrMe, unsigned int nSize);
void* _NewFEvent(const void* ptrInitialize, unsigned int nSize);

void OnMiscellaneousEvent(void (*Function)(unsigned int* ptrWhat, unsigned int eType), unsigned int eEvent, unsigned int bSet);

#endif