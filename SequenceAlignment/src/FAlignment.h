#ifndef FALIGNMENT_H
#define FALIGNMENT_H

#include <stdio.h>

typedef struct FAlignment
{
	unsigned int nLength;
	unsigned int nBytes;
	char* lData;
} FAlignment;

FAlignment* NewFAlignment(unsigned int nLength, unsigned int nSize);
void FreeFAlignment(FAlignment* lMe, unsigned int nSize);

void SerializeFAlignment(FAlignment* lMe, unsigned int nSize, FILE* ptrFile);
FAlignment* DeserializeFAlignment(FAlignment* lInto, unsigned int* ptrSize, FILE* ptrFile);

#endif