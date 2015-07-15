/**
  * ============================================================================
  * File Name          : bossTask_task.c
  * Description        : Boss Task Body
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Declarations ==

// == Function Definitions ==
/**
* @brief bossTask
* @param argument
*/
void StartBossTask(void const * argument) {
  // Start receiving data via USB UART
  cHAL_UART_TermReceive_IT(&huart1, 512);
  cHAL_UART_TermReceive_IT(&huart2, 512);

  msg_genericMessage_t rxMessage;
  /* Infinite loop */
  for (;;) {
    fetchMessage(msgQBoss, &rxMessage, osWaitForever);

    switch (rxMessage.messageType) {
    case MSG_TYPE_COORDS: {
        data_coords_t rxData;
        decodeMessage(&rxMessage, &rxData);
        if (rxData.x == 100 && rxData.y == 200) {
          GPIOB->ODR = rxData.z;
        }
      }
      break;
    case MSG_TYPE_COMMAND:
      if (decodeCommand(&rxMessage) == MSG_COMMAND_LED0_TOGGLE) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);

      } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);

      }
      break;
    default:
      break;
    }

    osDelay(25);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);

  }
}
