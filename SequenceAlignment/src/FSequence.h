#ifndef FSEQUENCE_H
#define FSEQUENCE_H

#include <stdio.h>

#define DNASYMS {'C','G','A','T'}
#define RNASYMS {'C','G','A','U'}
#define NSYMS 4
#define NBITS 8
#define NSYMBITS 2
#define NTRIPLE 3
                             /* compact  */
#define SEQT0M 0x03          /* 00000011 */
#define SEQT1M 0x0C          /* 00001100 */
#define SEQT2M 0x30          /* 00110000 */
#define SEQTM 0x3F           /* 00111111 */
#define SEQFM 0xC0           /* 11000000 */

#define TS0 0x00

#define T0S1 0x01
#define T0S2 0x02
#define T0S3 0x03

#define T1S1 0x04
#define T1S2 0x08
#define T1S3 0x0C

#define T2S1 0x10
#define T2S2 0x20
#define T2S3 0x30

/*        flags----------------   triple---------------           */
/* (16) [ (2) 00 | (6) 00 00 00 | (2) 00 | (6) 00 00 00 ] full    */
/*  (8) [                         (2) 00 | (6) 00 00 00 ] compact */
typedef struct FSequence
{
	unsigned int nLength;
	unsigned int nBytes;
	char* lData; /* compact */
} FSequence;

FSequence* NewFSequence(unsigned int nLength, unsigned int nSize);
void FreeFSequence(FSequence* oScore, unsigned int nSize);
void _FreeFSequence(void* ptrMe, unsigned int nSize);
void* _NewFSequence(const void* ptrInitialize, unsigned int nSize);

void SerializeFSequence(FSequence* oSerialize, unsigned int nSize, FILE* ptrFile);
FSequence* DeserializeFSequence(FSequence* oDeserialize, unsigned int* ptrSize, FILE* ptrFile);

#endif