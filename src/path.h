#ifndef PATH_H
#define PATH_H

#include "renderunit.h"

#include <stdint.h>

typedef struct{
	int dist;
	int* jumps; int size;
	int src_v; int dest_v;
	uint32_t* state;
} Path;

void p_init(Path*, int);
void p_reset(Path*);
void p_find_minimum(int const * const *, int, Path*);
void p_select_endpoints(_Bool, _Bool, int, int, float const *, float const *, int, Path*);
void p_draw_path(Path*);
void p_free(Path*);

#endif
