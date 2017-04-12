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
void FreeFAlignment(FAlignment* oScore, unsigned int nSize);
void _FreeFAlignment(void* ptrMe, unsigned int nSize);
void* _NewFAlignment(const void* ptrInitialize, unsigned int nSize);

void SerializeFAlignment(FAlignment* oSerialize, unsigned int nSize, FILE* ptrFile);
FAlignment* DeserializeFAlignment(FAlignment* oDeserialize, unsigned int* ptrSize, FILE* ptrFile);

#endif