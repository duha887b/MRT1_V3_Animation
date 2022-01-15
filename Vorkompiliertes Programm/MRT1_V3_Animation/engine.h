#ifndef ENGINE_HH
#define ENGINE_HH

// Engine Schnittstelle
#include "runtime_data.h"
#include <stdio.h>

//berechnet den nächsten Animationschritt ausgehend von dem Array in der Liste
void cal_nextAnimaionStep(list_header* list);

#endif //ENGINE_HH
