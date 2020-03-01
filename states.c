#include "states.h"

#include <stdint.h>

uint32_t states[16] = {0};

_Bool states_healthy(){
	if(
		(
			states[0] |
			states[1] |
			states[2] |
			states[3] |
			states[4] |
			states[5] |
			states[6] |
			states[7] |
			states[8] |
			states[9] |
			states[10] |
			states[11] |
			states[12] |
			states[13] |
			states[14] |
			states[15]
		) != 0
	){
		return 0;
	}
	return 1;
}
