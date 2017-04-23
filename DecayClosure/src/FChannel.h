#ifndef FCHANNEL_H
#define FCHANNEL_H

#include <stdio.h>

typedef struct FChannelInitialize
{
	unsigned int nMother;
	unsigned int nDaughter;
} FChannelInitialize;

typedef struct FChannel
{
	unsigned int iChannel;
	unsigned int eFlag;
	unsigned int nMother;
	unsigned int nDaughter;
	/* TODO more */
	int* lMother;
	int* lDaughter;
	void* _ptrTrack;
} FChannel;

FChannel* NewFChannel(unsigned int nSize);
void FreeFChannel(FChannel* lMe, unsigned int nSize);

void SerializeFChannel(FChannel* lMe, unsigned int nSize, FILE* ptrFile);
FChannel* DeserializeFChannel(FChannel* lInto, unsigned int* ptrSize, FILE* ptrFile);

#endif