#ifndef SIMPLE_THREAD_H
#define SIMPLE_THREAD_H

void OnThreadEvent(void (*Function)(unsigned int* ptrWhat, unsigned int eType), unsigned int eEvent, unsigned int bSet);

#endif