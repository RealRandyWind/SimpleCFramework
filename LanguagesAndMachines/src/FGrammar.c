#include "FCFG.h"
#include "simple_allocate.h"

void _FRuleLData(unsigned int** lData, unsigned int nSize, unsigned int* lSizes)
{
	unsigned int iData, iPointer;
	lData[0] = (unsigned int*)(lData + nSize);
	iPointer = 0;
	for (iData = 0; iData < nSize; ++iData)
	{
		lData[iData] = lData[0] + iPointer;
		iPointer += lSizes[iData];
	}
}

FCFG* NewFCFG(unsigned int nNonTerminals, unsigned int nTerminals, unsigned int nRules, unsigned int nSize)
{
	FCFG* lNew;
	if(!nSize) { return 0; }
	lNew = SMalloc(sizeof(FCFG) * nSize);
	while(nSize--)
	{
		lNew[nSize].nNonTerminals = nNonTerminals;
		lNew[nSize].nTerminals = nTerminals;
		lNew[nSize].nRules = nRules;
		lNew[nSize].lNonTerminals = SMalloc(sizeof(unsigned int) * nNonTerminals);
		lNew[nSize].lTerminals = SMalloc(sizeof(unsigned int) * nTerminals);
		lNew[nSize].lRules = SMalloc(sizeof(FRule) * nRules);
	}
	return lNew;
}

void FreeFCFG(FCFG* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--)
	{
		SFree(lMe[nSize].lNonTerminals);
		SFree(lMe[nSize].lTerminals);
		FreeFRule(lMe[nSize].lRules, lMe[nSize].nRules);
	}
	SFree(lMe);
}

void SerializeFCFG(FCFG* lMe, unsigned int nSize, FILE* ptrFile)
{
	unsigned int iIndex;
	if(!lMe || !nSize) { return; }

	SerializeRaw(lMe, sizeof(FCFG), nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		SerializeRaw(lMe[iIndex].lNonTerminals, sizeof(unsigned int), lMe[iIndex].nNonTerminals, ptrFile);
		SerializeRaw(lMe[iIndex].lTerminals, sizeof(unsigned int), lMe[iIndex].nTerminals, ptrFile);
		SerializeFRule(lMe[iIndex].lRules, lMe[iIndex].nRules, ptrFile);
	}
}

FCFG* DeserializeFCFG(FCFG* lInto, unsigned int* ptrSize, FILE* ptrFile)
{
	unsigned int iIndex, nSize;
	if(!lInto) { return 0; }

	lInto = DeserializeRaw(lInto, &nSize, ptrFile);
	for (iIndex = 0; iIndex < nSize; ++iIndex)
	{
		lInto[iIndex].lNonTerminals = DeserializeRaw(lInto[iIndex].lNonTerminals, 0, ptrFile);
		lInto[iIndex].lTerminals = DeserializeRaw(lInto[iIndex].lTerminals, 0, ptrFile);
		lInto[iIndex].lRules = DeserializeFRule(lInto[iIndex].lRules, 0, ptrFile);
	}
	if(ptrSize) { (*ptrSize) = nSize; }
	return lInto;
}

FRule* NewFRule(unsigned int nProducts, unsigned int* lSizes, unsigned int nSize)
{
	FRule* lNew;
	unsigned int nBytes, iProduct;
	unsigned int** lData;
	if(!nSize || !nProducts) { return 0; }
	lNew = SMalloc(sizeof(FRule) * nSize);
	nBytes = sizeof(unsigned int*) * nProducts;
	while(nSize--)
	{
		lNew[nSize].nProducts = nProducts;
		lNew[nSize].lSizes = SMalloc(sizeof(unsigned int) * nProducts);
		lNew[nSize].lProducts = SMalloc(sizeof(unsigned int) * nProducts);
	}
	return lNew;
}

void FreeFRule(FRule* lMe, unsigned int nSize)
{
	if(!lMe || !nSize) { return; }
	while(nSize--)
	{
		SFree(lMe[nSize].lSizes);
		SFree(lMe[nSize].lProducts);
	}
	SFree(lMe);
}

void SerializeFRule(FRule* lMe, unsigned int nSize, FILE* ptrFile)
{

}

FRule* DeserializeFRule(FRule* lInto, unsigned int* ptrSize, FILE* ptrFile)
{

}