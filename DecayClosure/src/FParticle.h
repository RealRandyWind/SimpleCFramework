#ifndef FPARTICLE_H
#define FPARTICLE_H

#include <stdio.h>

typedef struct FParticleInitialize
{
	unsigned int nChannel;
} FParticleInitialize;

typedef struct FParticle
{
	unsigned int iParticle;
	unsigned int eFlag;
	unsigned int nChannel;
	/* TODO more */
	unsigned int* lChannel;
	void* _ptrTrack;
} FParticle;

FParticle* NewFParticle(unsigned int nSize);
void FreeFParticle(FParticle* lMe, unsigned int nSize);

void SerializeFParticle(FParticle* lMe, unsigned int nSize, FILE* ptrFile);
FParticle* DeserializeFParticle(FParticle* lInto, unsigned int* ptrSize, FILE* ptrFile);

#endif