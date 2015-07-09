/**
  * ============================================================================
  * File Name          : USARTOutTask_task.c
  * Description        : USARTOutTask Body
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Function Definitions ==

/**
* @brief USARTOutTask
* @param argument
*/
void StartUSARTOutTask(void const * argument) {

  // Strings to send
  const char sendATTxString[] = "AT\r\n";
  data_coords_t txData;
  txData.messageType = MSG_TYPE_COORDS;

  txData.x = 100;
  txData.y = 200;
  txData.z = 0;
  /* Infinite loop */
  for (;;) {
    txData.z++;
    sendMessage(msgQBoss, MSG_TYPE_COORDS, MSG_SRC_USART_OUT_TASK, MRSP_HANDLE, &txData, osWaitForever);

    osDelay(500);
  
  }

}
