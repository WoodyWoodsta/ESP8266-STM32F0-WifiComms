/**
  * ============================================================================
  * File Name          : bossTask_task.c
  * Description        : USARTInTask Body
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Function Definitions ==

/**
* @brief bossTask
* @param argument
*/
void StartBossTask(void const * argument) {
  // Start the USART1 incomming stream
  uint8_t *UART1InBuff = pvPortMalloc(128); // Prep the memory
  cHAL_UART_TermReceive_IT(&huart1, UART1InBuff, 128);

  /* Infinite loop */
  for (;;) {
    size_t freeHeap = xPortGetFreeHeapSize();
    osDelay(500);
  }
}
