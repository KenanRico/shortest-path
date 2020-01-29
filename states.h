#ifndef STATES_H
#define STATES_H

#include <stdint.h>

enum STATES { RENDER=0, EVENTS=1, GRAPH=2 };
extern uint32_t states[16];

#endif
