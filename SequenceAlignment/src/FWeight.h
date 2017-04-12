#ifndef FWEIGHT_H
#define FWEIGHT_H

#include <stdio.h>

typedef struct FWeight
{
	unsigned int nSymbols;
	unsigned int nBytes;
	unsigned int** lData;
} FWeight;

FWeight* NewFWeight(unsigned int nSymbols, unsigned int nSize);
void FreeFWeight(FWeight* oScore, unsigned int nSize);
void _FreeFWeight(void* ptrMe, unsigned int nSize);
void* _NewFWeight(const void* ptrInitialize, unsigned int nSize);

void SerializeFWeight(FWeight* oSerialize, unsigned int nSize, FILE* ptrFile);
FWeight* DeserializeFWeight(FWeight* oDeserialize, unsigned int* ptrSize, FILE* ptrFile);

#endif