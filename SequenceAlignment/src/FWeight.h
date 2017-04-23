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

void SerializeFWeight(FWeight* lMe, unsigned int nSize, FILE* ptrFile);
FWeight* DeserializeFWeight(FWeight* lInto, unsigned int* ptrSize, FILE* ptrFile);

#endif