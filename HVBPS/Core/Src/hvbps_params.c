#include "hvbps_params.h"

board_param_t* get_params() {

	static board_param_t hvbps_parameters[2] = {
		{
			.ID = 1,
			.ival = 0,
			.type = TO_SEND,
			.to_send = false,
			.timestamp = 0
		},
		{
			.ID = 2,
			.ival = 0,
			.type = TO_RECEIVE,
			.to_send = false,
			.timestamp = 0
		}

	};

	return hvbps_parameters;

};
