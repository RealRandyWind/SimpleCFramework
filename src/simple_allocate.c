#include "simple_allocate.h"
#include <stdlib.h>

unsigned int nAllocations = 0;

void* SRealloc(void* ptrMe, unsigned int nBytes)
{
	if(!ptrMe || !nBytes) { return 0; }
	ptrMe = realloc(ptrMe, nBytes);
	return ptrMe;
}
void* SMalloc(unsigned int nBytes)
{
	void* ptrNew;
	if(!nBytes) { return 0; }
	ptrNew = malloc(nBytes);
	++nAllocations;
	return ptrNew;
}

void SFree(void* ptrMe)
{
	if(!ptrMe) { return; }
	--nAllocations;
}

unsigned int IsAllFree() { return !nAllocations; }