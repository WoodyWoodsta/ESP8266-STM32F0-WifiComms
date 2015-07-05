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

      const char led0ToggleString[] = "Toggle LED0";
      const char led1ToggleString[] = "Toggle LED1";
      const char led2ToggleString[] = "Toggle LED2";
      // If this has come to the correct place (might be a bit redundant)
      if (msgRxPtr->messageDestination == MSG_DEST_USART_IN) {
        // If the command is the expected length and correct, do the thing!
        if ((msgRxPtr->messageLength == (sizeof(led0ToggleString) - 1))
            && (strncmp(msgRxPtr->string, led0ToggleString, msgRxPtr->messageLength) == 0)) {
          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        } else if ((msgRxPtr->messageLength == (sizeof(led1ToggleString) - 1))
                   && (strncmp(msgRxPtr->string, led1ToggleString, msgRxPtr->messageLength) == 0)) {
          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
        } else if ((msgRxPtr->messageLength == (sizeof(led2ToggleString) - 1))
                   && (strncmp(msgRxPtr->string, led2ToggleString, msgRxPtr->messageLength) == 0)) {
          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
        }
      }

      // Free the message
      msgStringStructFree(msgPoolUSARTIn, msgRxPtr);
    }

    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
    osDelay(1);
  }
}
