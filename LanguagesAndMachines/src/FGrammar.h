#ifndef FGRAMMAR_H
#define FGRAMMAR_H

#include <stdio.h>

typedef struct FRule
{
	unsigned int nProducts;
	unsigned int* lSizes;
	unsigned int** lProducts;
	unsigned int _nBytes;
} FRule;

typedef struct FCFG
{
	unsigned int nNonTerminals;
	unsigned int nTerminals;
	unsigned int nRules;
	unsigned int* lNonTerminals;
	unsigned int* lTerminals;
	FRule* lRules;
} FCFG;

FCFG* NewFCFG(unsigned int nNonTerminals, unsigned int nTerminals, unsigned int nRules, unsigned int nSize);
void FreeFCFG(FCFG* lMe, unsigned int nSize);

void SerializeFCFG(FCFG* lMe, unsigned int nSize, FILE* ptrFile);
FCFG* DeserializeFCFG(FCFG* lInto, unsigned int* ptrSize, FILE* ptrFile);

FRule* NewFRule(unsigned int nProducts, unsigned int nReferences, unsigned int nSize);
void FreeFRule(FRule* lMe, unsigned int nSize);

void SerializeFRule(FRule* lMe, unsigned int nSize, FILE* ptrFile);
FRule* DeserializeFRule(FRule* lInto, unsigned int* ptrSize, FILE* ptrFile);

#endif