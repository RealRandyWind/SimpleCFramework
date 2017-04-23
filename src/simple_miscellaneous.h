#ifndef SIMPLE_MISCELLANEOUS_H
#define SIMPLE_MISCELLANEOUS_H

#include "simple_miscellaneous.h"
#include <stdio.h>

#define NBYTEBITS 8
#define NCHUNKBYTES 0xFFFFFFFF

typedef void* pointer;
typedef void* chunk;

typedef void (*FreeFunction)(void* ptrMe, unsigned int nSize);
typedef void* (*NewFunction)(const void* ptrIninitialize, unsigned int nSize);
typedef void* (*CopyFunction)(void* ptrMe);
typedef void (*EventFunction)(void* ptrWhat, unsigned int eType);
typedef int (*CompareFunction)(void* ptrMe, void* ptrWith);
typedef void* (*HashFunction)(void* ptrMe);
typedef unsigned int (*IndexFunction)(void* ptrMe);
typedef void (*SerializeFunction)(void* ptrMe, unsigned int nSize, FILE* ptrFile);
typedef void* (*DeserializeFunction)(void* ptrInto, unsigned int* ptrSize, FILE* ptrFile);

typedef struct FEvent
{
	EventFunction* lFunction;
	unsigned int nFunction;
	unsigned int eEvent;
} FEvent;

typedef struct FMemory
{
	unsigned int nByte;
	unsigned int nChunk;
	chunk* lChunk;
} FMemory;

FEvent* NewFEvent(unsigned int nFunction, unsigned int nSize);
void FreeFEvent(FEvent* lMe, unsigned int nSize);
void OnEvent(EventFunction Function, unsigned int eEvent, unsigned int bSet, FEvent* lEvent);
void TriggerEvent(unsigned int eEvent, void* ptrWhat, unsigned int eType, FEvent* lEvent);

FMemory* NewFMemory(unsigned long nBytes, unsigned int nSize);
void FreeFMemory(FMemory* oMe, unsigned int nSize);

unsigned int StringSize(const char* sMe);
unsigned int StringBytes(const char* sMe);
char* NewString(const char* sMe);
void* CopyRaw(void* ptrMe, unsigned int nBytes, void* ptrInto);

#endif