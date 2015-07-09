/**
  * ============================================================================
  * File Name          : bossTask_task.c
  * Description        : USARTInTask Body
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
      if (decodeCommand(&rxMessage) == MSG_COMMAND_LED2_TOGGLE) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, SET);

      } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);

      }
      break;
    default:
      break;
    }

    osDelay(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET);

  }
}
