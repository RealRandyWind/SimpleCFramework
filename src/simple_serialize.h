#ifndef SIMPLE_SERIALIZE_H
#define SIMPLE_SERIALIZE_H

#define SERIALIZE_NEW (void*)1

unsigned int StringSize(const char* sString);
unsigned int StringBytes(const char* sString);
char* MemoryString(const char* sString);
void SerializeRaw(void* ptrRaw, unsigned int nBytes, unsigned int nSize, FILE* ptrFile);
void* DeserializeRaw(void* ptrRaw, unsigned int* ptrSize, FILE* ptrFile);
void* CopyRaw(void* ptrFrom, unsigned int nBytes, void* ptrTo);
void SerializeType(unsigned int eType, unsigned int iVersion, FILE* ptrFile);
unsigned int DeserializeType(unsigned int* ptrVersion, FILE* ptrFile);

void OnSerializeEvent(void (*Function)(unsigned int* ptrWhat, unsigned int eType), unsigned int eEvent, unsigned int bSet);

/*
TODO find a way to serialize references, assign numbers to pointers before writing away,
support for circular references and prevent duplication.

#### private helpers
typedef struct _Ref
{
	void* ptrRef;
	unsigned int iRef;
} _Ref;

typedef struct _RefTable
{
	struct _RefTable* _lNext;
} _RefTable;

# zero index is null pointer
_Ref* _lRefs = 0;
_RefTable* _oRefTable = 0;

unsigned int Fx_PutRef(void* ptrRef);
void* Fx_GetRef(unsigned int iRef);

#### public
void SerializeRef(void* ptrRef, unsigned int nBytes, unsigned int nSize, FILE* ptrFile);
void* DeserializeRef(void* ptrRef, unsigned int* ptrSize, FILE* ptrFile);
*/

#endif