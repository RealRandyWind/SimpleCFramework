#include <stdio.h>
#include <stdlib.h>
#include "simple_serialize.h"
#include "simple_random.h"
#include "simple_display.h"
#include "FSequence.h"
#include "FAlignment.h"
#include "FScore.h"
#include "FWeight.h"

#define ACT_MATCHF SCOREF0
#define ACT_DELETEF SCOREF1
#define ACT_INSERTF SCOREF2
#define ACT_MISMATCHF SCOREF3
#define ACT_SYMS0 {'=','-','+','~'}
#define ACT_SYMS1 {'|','-','-',' '}
#define ACT_MATCH 0
#define ACT_DELETE 1
#define ACT_INSERT 2
#define ACT_MISMATCH 3
#define SYMGAP 4

#define SYMIDX(TRIPLE,I) ((TRIPLE) >> ((I % (NTRIPLE)) * 2)) & SEQT0M

void DisplaySequence(FSequence* oMe, unsigned int nSize, unsigned int nColumn)
{
	unsigned int nLength, iLenght;
	char oTriple;
	char lMap[NSYMS] = DNASYMS;
	//char* lBuffer = (char*)malloc(sizeof(char) * (nColumn + nLength + 1));
	if(!oMe || !nSize) { return; }
	while(nSize--)
	{
		nLength = oMe[nSize].nLength;
		if(!nLength) { continue; }
		for(iLenght = 0; iLenght < nLength; ++iLenght) {
			if(!(iLenght % nColumn)) { printf("\n"); }
			oTriple = oMe[nSize].lData[iLenght];
			printf("%c%c%c"
				,lMap[oTriple & SEQT0M]
				,lMap[(oTriple >> 2) & SEQT0M]
				,lMap[(oTriple >> 4) & SEQT0M]);
		}
	}
}

void DisplayAlignment(FAlignment* oMe, unsigned int nSize, unsigned int nColumn)
{
	unsigned int nLength, iLenght;
	char oTriple;
	char lMap[NSYMS] = ACT_SYMS0;
	if(!oMe || !nSize) { return; }
	while(nSize--)
	{
		nLength = oMe[nSize].nLength;
		if(!nLength) { continue; }
		for(iLenght = 0; iLenght < nLength; ++iLenght) {
			if(!(iLenght % nColumn)) { printf("\n"); }
			oTriple = oMe[nSize].lData[iLenght];
			printf("%c%c%c"
				,lMap[oTriple & SEQT0M]
				,lMap[(oTriple >> 2) & SEQT0M]
				,lMap[(oTriple >> 4) & SEQT0M]);
		}
	}
}

void DisplayWeight(FWeight* oMe, unsigned int nSize)
{
	unsigned int nLength, nSymbols, iLenght;
	unsigned int nValue;
	if(!oMe || !nSize) { return; }
	while(nSize--)
	{
		nSymbols = oMe[nSize].nSymbols;
		nLength = nSymbols * nSymbols;
		if(!nLength) { continue; }
		for(iLenght = 0; iLenght < nLength; ++iLenght) {
			if(!(iLenght % nSymbols)) { printf("\n"); }
			nValue = oMe[nSize].lData[0][iLenght];
			printf("%2u ", nValue);
		}
	}
}

void DisplayScore(FScore* oMe, unsigned int nSize)
{
	unsigned int nLength, nColumn, iLenght;
	unsigned int nValue;
	if(!oMe || !nSize) { return; }
	while(nSize--)
	{
		nColumn = oMe[nSize].nMax;
		nLength = oMe[nSize].nMin * nColumn;
		if(!nLength) { continue; }
		for(iLenght = 0; iLenght < nLength; ++iLenght) {
			if(!(iLenght % nColumn)) { printf("\n"); }
			nValue = oMe[nSize].lData[0][iLenght];
			printf("%1u|%03u ", nValue >> SCOREFK, nValue & SCOREM);
		}
	}
}

void DisplayAlignedSequence(FAlignment* oMe, FSequence* oSequenceS, FSequence* oSequenceL, unsigned int nSize, unsigned int nColumn)
{
	unsigned int nA, iA, iL, iS, iColumn, nBuffer;
	char oA, oS, oL, eFlag;
	char lMap[NSYMS] = DNASYMS;
	char *sA, *sS, *sL;
	if(!oMe || !oSequenceS || !oSequenceL || !nSize) { return; }
	while(nSize--)
	{
		iColumn = 0;
		nA = oMe[nSize].nLength * 3;
		if(!nA) { continue; }
		nBuffer = 0 + nA * 3 + 2;
		char* lBuffer = malloc(sizeof(char) * nBuffer + 1);
		lBuffer[nBuffer] = '\0';
		sS = &lBuffer[0]; sS[nA] = '\n';
		sA = &lBuffer[nA + 1]; sA[nA] = '\n';
		sL = &lBuffer[2 * nA + 2];
		iS = 0; iL = 0;
		for(iA = 0; iA < nA; ++iA) {
			oS = oSequenceS[nSize].lData[iS / NTRIPLE];
			oA = oMe[nSize].lData[iA / NTRIPLE];
			oL = oSequenceL[nSize].lData[iL / NTRIPLE];
			eFlag = (oA >> ((iA % NTRIPLE) * NSYMBITS)) & SEQT0M;
			if(eFlag == ACT_DELETE) { sS[iA] = '-'; }
			else { sS[iA] = lMap[(oS >> ((iS % NTRIPLE) * NSYMBITS)) & SEQT0M]; ++iS; }
			sA[iA] = (eFlag == ACT_MATCH ? '|' : ' ');
			if(eFlag == ACT_INSERT) { sL[iA] = '-'; }
			else { sL[iA] = lMap[(oL >> ((iL % NTRIPLE) * NSYMBITS)) & SEQT0M]; ++iL; }
		}
		printf("%s", lBuffer);
		free(lBuffer);
	}
}

FSequence* GenerateSequence(unsigned int nLength)
{
	char oTriple;
	FSequence* oSequence;
	oSequence = NewFSequence(nLength, 1);
	while(nLength--)
	{
		oTriple = RandR(TS0, NSYMS) | (RandR(TS0, NSYMS) << 2) | (RandR(TS0, NSYMS) << 4);
		oSequence->lData[nLength] = oTriple;
	}
	return oSequence;
}

unsigned int MinScore(unsigned int nMatch, unsigned int nDelete, unsigned int nInsert, unsigned int isMatch)
{
	if(nMatch <= nDelete && nMatch <= nInsert) { return nMatch | (isMatch ? ACT_MATCHF : ACT_MISMATCHF); }
	if(nDelete <= nInsert && nDelete <= nMatch) { return nDelete | ACT_DELETEF; }
	return nInsert | ACT_INSERTF;
}

FAlignment* Align(FSequence* oSequenceS, FSequence* oSequenceL, FWeight* oWeight, unsigned int* ptrSize, FScore** ptrScore) {
	FAlignment* oAlignment;
	FScore* oScore;
	unsigned int nLength, nBuffer, nS, nL, nIndex, iS, iL, isMatch;
	unsigned int nMatch, nInsert, nDelete, eFlag, nSize, iK;
	unsigned int** lWeight, **lScore;
	char cS, cL, oT;
	char* lAlignment;
	if(!oSequenceL || !oSequenceS) { return 0; }

	nS = oSequenceS->nLength * NTRIPLE + 1;
	nL = oSequenceL->nLength * NTRIPLE + 1;
	oScore = NewFScore(nS, nL, 1);
	
	lScore = oScore->lData;
	lWeight = oWeight->lData;
	lScore[0][0] = ACT_MATCHF;
	isMatch = 0;
	for (iS = 1; iS < nS; ++iS)
	{
		oT = oSequenceS->lData[(iS - 1) / NTRIPLE];
		cS = (oT >> ((iS % NTRIPLE) * NSYMBITS)) & SEQT0M;	
		lScore[iS][0] = (iS * lWeight[cS][SYMGAP]) | ACT_DELETEF;
		for (iL = 1; iL < nL; ++iL)
		{
			oT = oSequenceL->lData[(iL - 1) / NTRIPLE];
			cL = ( oT >> ((iL % NTRIPLE) * NSYMBITS)) & SEQT0M;
			isMatch = cS == cL;
			lScore[0][iL] = (iL * lWeight[SYMGAP][cL]) | ACT_INSERTF;
			nMatch = (lScore[iS - 1][iL - 1] & SCOREM) + lWeight[cS][cL];
			nDelete = (lScore[iS - 1][iL] & SCOREM) + lWeight[cS][SYMGAP];
			nInsert = (lScore[iS][iL - 1] & SCOREM) + lWeight[SYMGAP][cL];
			lScore[iS][iL] = MinScore(nMatch, nDelete, nInsert, isMatch);
			/**
			Track maximum score and drop search in these directions larger,
			lScore[iS + 1][iL - 1] = NOSCORE;
			lScore[iS + 1][iL + 1] = NOSCORE;
			/**/
		}
	}

	nSize = 1;
	nBuffer = oSequenceS->nLength + oSequenceL->nLength - 1;
	oAlignment = NewFAlignment(nBuffer, 1);

	/*debug*/
	char _dna[NSYMS] = DNASYMS;
	char _alg[NSYMS] = ACT_SYMS0;
	/**/

	/**/
	lAlignment = oAlignment->lData;
	nLength = 0; --nS; --nL;
	oT = (isMatch ? ACT_MATCHF : ACT_MISMATCHF);
	while(nS + nL)
	{
		iK = (nS + nL) % NTRIPLE;
		eFlag = lScore[nS][nL] >> SCOREFK;
		/*debug */
		char _s = (oSequenceS->lData[nS / NTRIPLE] >> ((nS % NTRIPLE) * NSYMBITS)) & SEQT0M;
		char _l = (oSequenceL->lData[nL / NTRIPLE] >> ((nL % NTRIPLE) * NSYMBITS)) & SEQT0M;
		unsigned int _q = lScore[nS][nL] & SCOREM;
		printf("(%c:%d,%c:%d) -> %3d | %c \n", _dna[_s], nS,_dna[_l], nL,_q,_alg[eFlag]);
		/**/
		if(eFlag == ACT_DELETE) { --nS; }
		else if(eFlag == ACT_INSERT) { --nL; }
		else if(eFlag == ACT_MATCH || eFlag == ACT_MISMATCH) { --nS; --nL; }
		if(!iK) { lAlignment[(nS + nL) / NTRIPLE] = oT; oT = 0; }
		oT |= eFlag << (iK * NSYMBITS);
		++nLength;
	}
	oAlignment->nLength = nLength / NTRIPLE;
	/**/
	
	if(ptrScore) { (*ptrScore) = oScore; }
	else { FreeFScore(oScore,1); }
	if(ptrSize) { (*ptrSize) = nSize; }
	return oAlignment;
}

int main(int argc, char const *argv[])
{
	char* sFileSequenceL, *sFileSequenceS, *sFileAlignment ,*sFileScore, *sFileWeight;
	FILE* ptrFile;
	FSequence* oSequenceS, *oSequenceL;
	FAlignment* oAlignment;
	FScore* oScore;
	FWeight* oWeight;
	unsigned int nAlignments;
	nAlignments = 0;

	sFileSequenceS = "FSequence.S2.bin";
	sFileSequenceL = "FSequence.L2.bin";
	sFileWeight = "FWeight.bin";
	sFileAlignment = "FAlignment.bin";
	sFileScore = "FScore.bin";

	/* read squences S */
	ptrFile = fopen(sFileSequenceS,"rb");
	oSequenceS = DeserializeFSequence(SERIALIZE_NEW, 0, ptrFile);
	fclose(ptrFile);
	printf(" read sequence S(%d) from \"%s\" - done\n",oSequenceS->nLength, sFileSequenceS);

	/* read squences L */
	ptrFile = fopen(sFileSequenceL,"rb");
	oSequenceL = DeserializeFSequence(SERIALIZE_NEW, 0, ptrFile);
	fclose(ptrFile);
	printf(" read sequence L(%d) from \"%s\" - done\n",oSequenceL->nLength, sFileSequenceL);

	/* read weights */
	ptrFile = fopen(sFileWeight,"rb");
	oWeight = DeserializeFWeight(SERIALIZE_NEW, 0, ptrFile);
	fclose(ptrFile);
	printf(" read weights from \"%s\" - done\n", sFileWeight);

	oAlignment = Align(oSequenceS, oSequenceL, oWeight, &nAlignments, &oScore);

	/* write alignments */
	ptrFile = fopen(sFileAlignment,"wb");
	SerializeFAlignment(oAlignment, nAlignments, ptrFile);
	fclose(ptrFile);
	printf(" write alignments to \"%s\" - done\n", sFileAlignment);
	DisplayAlignment(oAlignment, 1, oAlignment->nLength);
	printf("\n");
	DisplayAlignedSequence(oAlignment, oSequenceS, oSequenceL, 1, 0);

	/* write score *
	ptrFile = fopen(sFileScore,"wb");
	SerializeFScore(oScore, 1, ptrFile);
	fclose(ptrFile);
	printf(" write score(%d,%d) to \"%s\" - done\n", oScore->nMin, oScore->nMax, sFileScore);
	/**/
	DisplayScore(oScore,1);

	FreeFSequence(oSequenceL,1);
	FreeFSequence(oSequenceS,1);
	FreeFWeight(oWeight,1);
	FreeFAlignment(oAlignment,1);
	FreeFScore(oScore,1);
	return 0;
}