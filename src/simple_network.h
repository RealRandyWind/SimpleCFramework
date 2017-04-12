#ifndef SIMPLE_NETWORK_H
#define SIMPLE_NETWORK_H

void OnNetworkEvent(void (*Function)(unsigned int* ptrWhat, unsigned int eType), unsigned int eEvent, unsigned int bSet);

#endif