#ifndef SIMPLE_DISPLAY_H
#define SIMPLE_DISPLAY_H

void OnDisplayEvent(void (*Function)(unsigned int* ptrWhat, unsigned int eType), unsigned int eEvent, unsigned int bSet);

#endif