/**
  * ============================================================================
  * File Name          : USARTInTask_task.c
  * Description        : USARTInTask Body
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Function Definitions ==

/**
* @brief USARTInTask
* @param argument
*/
void StartUSARTInTask(void const * argument) {
  msg_StringMessage_t *msgRxPtr;
  osEvent msgRxEvent;

  /* Infinite loop */
  for (;;) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
    msgRxEvent = osMessageGet(msgQUSARTIn, osWaitForever); // Wait for a message

    // If there is a message in the queue
    if (msgRxEvent.status == osEventMessage) {
      msgRxPtr = msgRxEvent.value.p; // Grab the pointer

      // If this has come to the correct place (might be a bit redundant)
      if (msgRxPtr->messageDestination == MSG_DEST_USART_IN) {
        // If the command is received, do the thing!
        if (strncmp(msgRxPtr->string, "Toggle LED0", msgRxPtr->messageLength) == 0) {
          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        }
      }

      // Free the message
      msgStringStructFree(msgPoolUSARTIn, msgRxPtr);
    }

    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
    osDelay(1);
  }
}
