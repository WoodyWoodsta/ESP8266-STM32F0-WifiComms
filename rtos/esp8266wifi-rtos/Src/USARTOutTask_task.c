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

  /* Infinite loop */
  for (;;) {
    sendCommand(msgQBoss, MSG_SRC_USART_OUT_TASK, MSG_COMMAND_LED2_TOGGLE, osWaitForever);

    osDelay(500);
  
  }

}
