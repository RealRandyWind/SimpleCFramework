#ifndef SIMPLE_ALLOCATE_H
#define SIMPLE_ALLOCATE_H

void* SRealloc(void* ptrMe, unsigned int nBytes);
void* SMalloc(unsigned int nBytes);
void SFree(void* ptrMe);

unsigned int IsAllFree();

#endif