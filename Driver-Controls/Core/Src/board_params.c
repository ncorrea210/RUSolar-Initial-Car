#include "board_params.h"
#include "main.h"

#define STALE_TIME 2000

can_data_t convert_message(board_param_t* param) {
	can_data_t data = { .ID = param->ID, .ival = param->ival };
	return data;
}

void check_staleness(board_param_t** params, uint16_t num_params) {
	uint32_t current_time = HAL_GetTick();
	for (int i = 0; i < num_params; i++) {
		if (!params[i]->check_stale) continue;
		if (params[i]->timestamp + STALE_TIME < current_time) {
			params[i]->stale = true;
		}
	}
}
