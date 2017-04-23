#ifndef SIMPLE_FLAG_H
#define SIMPLE_FLAG_H

#include <stdio.h>

#define NFLAGENTRYBITS 16

typedef struct FFlag
{
	unsigned int nEntry;
	unsigned int* lEntry;
} FFlag;

FFlag* NewFFlag(unsigned int nEntry, unsigned int nSize);
void FreeFFlag(FFlag* lMe, unsigned int nSize);

void SerializeFFlag(FFlag* lMe, unsigned int nSize, FILE* ptrFile);
FFlag* DeserializeFFlag(FFlag* lInto, unsigned int* ptrSize, FILE* ptrFile);

void SetFFlag(unsigned long iBit, FFlag* oMe);
void UnSetFFlag(unsigned long iBit, FFlag* oMe);
void ToggleFFlag(unsigned long iBit, FFlag* oMe);
void RShiftFFlag(unsigned long nShift, FFlag* oMe, FFlag* oInto);
void LShiftFFlag(unsigned long nShift, FFlag* oMe, FFlag* oInto);
void OrFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto);
void AndFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto);
void XorFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto);
void DiffFFlag(FFlag* oMe, FFlag* oWith, FFlag* oInto);
void NotFFlag(FFlag* oMe, FFlag* oInto);
unsigned long LengthFFlag(FFlag* oMe);

#endif