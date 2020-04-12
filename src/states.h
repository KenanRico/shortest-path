#ifndef STATES_H
#define STATES_H

#include <stdint.h>

enum STATES { RENDER=0, EVENTS=1, GRAPH=2, PATH=3};
extern uint32_t states[16];

enum Phase {BUILD_MAP=0, SET_ENDPOINTS=1, FIND_SHORTEST_PATH=2, MIN_PATH_FOUND=3};
extern uint8_t phase;

_Bool states_healthy();

#endif
