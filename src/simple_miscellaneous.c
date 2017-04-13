#include "simple_miscellaneous.h"

typedef struct _FMapEntry
{
	void* ptrValue;
	void* ptrKey;
	unsigned int eType;
} _FMapEntry;

typedef struct _FMap
{
	_FMapEntry* lEntry
	unsigned int nEntry;
	unsigned int _nNext;
	struct _FMap* _lNext; 	
} _FMap;