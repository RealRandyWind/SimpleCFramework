#ifndef SIMPLE_AUTOMATON_H
#define SIMPLE_AUTOMATON_H

#include "simple_miscellaneous.h"

typedef struct FAutomatonInitialize
{
	unsigned int nSymbol;
	unsigned int nStates;
} FParticleInitialize;

typedef struct FAutomaton
{
	unsigned int nSymbol;
	unsigned int nState;
	unsigned int** lDelta;
	void* lMap;
} FAutomatom;



void OnAutomatonEvent(EventFunction Function, unsigned int eEvent, unsigned int bSet);

#endif