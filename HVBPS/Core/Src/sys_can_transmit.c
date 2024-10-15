#include "sys_can_transmit.h"
#include "main.h"

static int num_tx_params = 1;
static board_param_t* tx_params[1] = {0};
static CAN_TxHeaderTypeDef std_header = {
		.StdId = CAN_ID,
		.IDE = CAN_ID_STD,
		.RTR = CAN_RTR_DATA,
		.DLC = 8,
		.TransmitGlobalTime = DISABLE
};

static uint32_t* TxMailbox;
static CAN_HandleTypeDef* hcan1;

static HAL_StatusTypeDef send_can_message(board_param_t* param) {
	return HAL_CAN_AddTxMessage(hcan1, &std_header, convert_message(param).data, TxMailbox);
}

void can_tx_init(CAN_HandleTypeDef* hcan, uint32_t* mailbox, board_param_t* params, uint16_t num_params) {

	hcan1 = hcan;
	TxMailbox = mailbox;
	int index = 0;
	for (int i = 0; i < num_params; i++) {
		if (params[i].type == TO_SEND) {
			tx_params[index] = &params[i];
			index++;
		}
	}

}

void can_incremental_update() {
	for (int i = 0; i < num_tx_params; i++) {
		if (!tx_params[i]->to_send) continue;
		if (send_can_message(tx_params[i]) == HAL_OK) {
			tx_params[i]->to_send = false;
		}
	}
}

void can_tx_refresh() {
	for (int i = 0; i < num_tx_params; i++) {
		tx_params[i]->to_send = true;
	}
}
