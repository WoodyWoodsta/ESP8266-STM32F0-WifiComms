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
  uint8_t *UART2InBuff = pvPortMalloc(128);
  char *freeHeapString = pvPortMalloc(15);
  cHAL_UART_TermReceive_IT(&huart1, UART1InBuff, 128);
  cHAL_UART_TermReceive_IT(&huart2, UART2InBuff, 128);

  /* Infinite loop */
  for (;;) {
    if (wifiCommState == COMM_STATE_AUTO) {
      size_t freeHeap = xPortGetFreeHeapSize();

      sprintf(freeHeapString, "%d\r\n", freeHeap);
      HAL_UART_Transmit_DMA(&huart1, freeHeapString, 6);
    }

    osDelay(2000);
  }
}
