#ifndef FSCORE_H
#define FSCORE_H

#include <stdio.h>

#define SCOREFK 30
#define SCOREM 0x3FFFFFFF  /* 00111111 11111111 11111111 11111111 */
#define SCOREFM 0xC0000000 /* 11000000 00000000 00000000 00000000 */

#define SCOREF0 0x00000000
#define SCOREF1 0x40000000
#define SCOREF2 0x80000000
#define SCOREF3 0xC0000000

#define SCOREINF SCOREM
#define NOSCORE 0xFFFFFFFF

typedef struct FScore
{
	unsigned int eFlag;
	unsigned int nMin;
	unsigned int nMax;
	unsigned int nBytes;
	unsigned int** lData;
} FScore;

FScore* NewFScore(unsigned int nMin, unsigned int nMax, unsigned int nSize);
void FreeFScore(FScore* oScore, unsigned int nSize);

void SerializeFScore(FScore* lMe, unsigned int nSize, FILE* ptrFile);
FScore* DeserializeFScore(FScore* lInto, unsigned int* ptrSize, FILE* ptrFile);

#endif