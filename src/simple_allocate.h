#ifndef SIMPLE_ALLOCATE_H
#define SIMPLE_ALLOCATE_H

void* SRealloc(void* ptrMe, unsigned int nBytes);
void* SMalloc(unsigned int nBytes);
void* SURef(void* ptrMe);
void* SRef(void* ptrMe);
void SFree(void* ptrMe);
void SNullFree(void* ptrMe);

void OnAllocateEvent(void (*Function)(void* ptrWhat, unsigned int eType), unsigned int eEvent, unsigned int bSet);

unsigned int IsAllFree();

#endif