#ifndef BOARD_PARAMS_H
#define BOARD_PARAMS_H

#include <stdint.h>
#include <stdbool.h>
#include "can.h"

typedef struct {
	uint16_t ID;
	union {
		int32_t ival;
		bool bval;
		float fval;
	};
	uint8_t type;
	bool to_send;
	uint32_t timestamp;
	bool check_stale;
	bool stale;
} board_param_t;

enum {
	TO_SEND = 0,
	TO_RECEIVE
};

can_data_t convert_message(board_param_t* param);

void check_staleness(board_param_t** params, uint16_t num_params);

#endif
