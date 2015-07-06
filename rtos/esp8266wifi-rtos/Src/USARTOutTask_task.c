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
  msg_CommandMessage_t *msgCommandRxPtr;
  osEvent msgRxEvent;

  // Strings to send
  const char sendATTxString[] = "AT\r\n";

  /* Infinite loop */
  for (;;) {
    msgRxEvent = osMessageGet(msgQUSARTOut, osWaitForever);

    if (msgRxEvent.status == osEventMessage) {
      msgCommandRxPtr = msgRxEvent.value.p;

      if (msgCommandRxPtr->command == MSG_CMD_WIFI_SEND_AT) {
        HAL_UART_Transmit_DMA(&huart2, (uint8_t *) &sendATTxString, sizeof(sendATTxString) - 1);
      }
    }

    osPoolFree(msgPoolUSARTOut, msgCommandRxPtr);
  }
}
