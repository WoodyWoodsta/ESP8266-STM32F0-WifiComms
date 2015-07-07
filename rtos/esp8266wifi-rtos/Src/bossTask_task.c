/**
  * ============================================================================
  * File Name          : bossTask_task.c
  * Description        : USARTInTask Body
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Declarations ==
uint8_t UART1InBuff[128]; // Prep the memory
uint8_t UART2InBuff[128];
char freeHeapString[15];

// == Function Definitions ==
/**
* @brief bossTask
* @param argument
*/
void StartBossTask(void const * argument) {
  // Start the USART1 incomming stream
  
  cHAL_UART_TermReceive_IT(&huart1, UART1InBuff, 128);
  cHAL_UART_TermReceive_IT(&huart2, UART2InBuff, 128);

  /* Infinite loop */
  for (;;) {
    if (wifiCommState == COMM_STATE_AUTO) {
      size_t freeHeap = xPortGetFreeHeapSize();

      sprintf(freeHeapString, "%d\r\n", (int) freeHeap);
      HAL_UART_Transmit_DMA(&huart1, (uint8_t *) freeHeapString, 6);
    }

    osDelay(2000);
  }
}
