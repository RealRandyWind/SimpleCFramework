#ifndef SIMPLE_AUTOMATON_H
#define SIMPLE_AUTOMATON_H

typedef struct FAutomaton
{
	unsigned int* lMap;
	unsigned int** lData;
} FAutomatom;

void OnAutomatonEvent(void (*Function)(unsigned int* ptrWhat, unsigned int eType), unsigned int eEvent, unsigned int bSet);

#endif