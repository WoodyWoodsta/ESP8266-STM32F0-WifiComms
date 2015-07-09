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
    default:
      break;
    }

    osDelay(1);
  }
}
