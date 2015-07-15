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
  size_t freeHeap;
  /* Infinite loop */
  for (;;) {
    sendCommand(msgQBoss, MSG_SRC_USART_OUT_TASK, MSG_COMMAND_LED0_TOGGLE, osWaitForever);

    freeHeap = xPortGetFreeHeapSize();
    osDelay(100);
  
  }

}
