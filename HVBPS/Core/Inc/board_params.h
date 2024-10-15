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
} board_param_t;

enum {
	TO_SEND = 0,
	TO_RECIEVE
};

can_data_t convert_message(board_param_t* param);

#endif
