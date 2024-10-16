#include "sys_can_receive.h"
#include "main.h"

static CAN_HandleTypeDef* rx_hcan;
static board_param_t** rx_params;
static uint16_t num_params;

void can_rx_init(CAN_HandleTypeDef* hcan, board_param_t* param, uint16_t num_params) {
	rx_hcan = hcan;
	int index = 0;
	for (int i = 0; i < num_params; i++) {
		if (param[i].type == TO_RECEIVE) {
			rx_params[index] = &param[i];
			index++;
		}
	}
	num_params = index;
}

void can_receive_message() {
	static CAN_RxHeaderTypeDef RxHeader;
	static can_data_t data;
	if (HAL_CAN_GetRxMessage(rx_hcan, CAN_RX_FIFO0, &RxHeader, data.data) != HAL_OK ) return;
	for (int i = 0; i < num_params; i++) {
		if (rx_params[i]->ID != data.ID) continue;
		board_param_t* param = rx_params[i];
		param->ival = data.ival;
		param->timestamp = HAL_GetTick();
		param->stale = false;
	}
}
