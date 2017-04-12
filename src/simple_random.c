#include "simple_random.h"
#include <stdlib.h>
#include <time.h>

void Seed() { srand((double)time(0)); }
double DRand() { return rand()/(RAND_MAX + 1.); }
double DRandR(double dMin, double dMax) { return (rand()/(RAND_MAX + 1.))*(dMax - dMin) + dMin; }
double DSRand() { return 1. - (rand()/(RAND_MAX + 1.)) * 2.; }
int RandR(int iMin, int iMax) { return (rand() % (iMax- iMin)) + iMin; }