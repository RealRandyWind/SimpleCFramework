#include <stdio.h>

#include "simple_allocate.h"
#include "simple_serialize.h"

typedef struct _FHeader
{
	unsigned int nBytes;
	unsigned int nSize;
} _FHeader;

typedef struct _FTypeHeader
{
	unsigned int eType;
	unsigned int iVersion;
} _FTypeHeader;

void SerializeRaw(void* ptrRaw, unsigned int nBytes, unsigned int nSize, FILE* ptrFile)
{
	_FHeader oHeader;
	if(!ptrRaw || !nBytes || !nSize || !ptrFile) { return; }
	oHeader.nBytes = nBytes;
	oHeader.nSize = nSize;
	fwrite(&oHeader, sizeof(_FHeader), 1, ptrFile);
	fwrite(ptrRaw, oHeader.nBytes, oHeader.nSize, ptrFile);
}

void* DeserializeRaw(void* ptrRaw, unsigned int* ptrSize, FILE* ptrFile)
{
	_FHeader oHeader;
	if(!ptrRaw || !ptrFile) { return 0; }
	fread(&oHeader, sizeof(_FHeader), 1, ptrFile);
	ptrRaw = SMalloc(oHeader.nBytes * oHeader.nSize);
	fread(ptrRaw, oHeader.nBytes, oHeader.nSize, ptrFile);
	if(ptrSize) { (*ptrSize) = oHeader.nSize; }
	return ptrRaw;
}

void SerializeType(unsigned int eType, unsigned int iVersion, FILE* ptrFile)
{
	_FTypeHeader oTypeHeader;
	if(!ptrFile) { return; }
	oTypeHeader.eType = eType;
	oTypeHeader.iVersion = iVersion;
	fwrite(&oTypeHeader, sizeof(_FTypeHeader), 1, ptrFile);
}

unsigned int DeserializeType(unsigned int* ptrVersion, FILE* ptrFile)
{
	_FTypeHeader oTypeHeader;
	if(!ptrFile) { return 0; }
	fread(&oTypeHeader, sizeof(oTypeHeader), 1, ptrFile);
	if(ptrVersion) { (*ptrVersion) = oTypeHeader.iVersion; }
	return oTypeHeader.eType;
}