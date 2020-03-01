#ifndef PATH_H
#define PATH_H

#include "stdint.h"

typedef struct{
	int dist;
	int src_v;
	int dest_v;

	_Bool endpoints_selected;
	uint32_t* state;
} Path;

void p_init(Path*);
void p_reset(Path*);
void p_find_minimum(int const * const *, int, Path*);
void p_select_endpoints(_Bool, int, int, float const *, float const *, int, Path*);

#endif
