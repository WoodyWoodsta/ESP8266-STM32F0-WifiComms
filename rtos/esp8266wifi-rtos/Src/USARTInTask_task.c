/**
  * ============================================================================
  * File Name          : USARTInTask_task.c
  * Description        : USARTInTask Body
  * ============================================================================
  */

  // == Includes ==
#include "userTasks_task.h"

// == Function Declarations ==
void usartHandleString(msg_StringMessage_t *msgStringRxPtr);
void usartHandleStringAutoUSB(msg_StringMessage_t *msgStringRxPtr);
void usartHandleStringManUSB(msg_StringMessage_t *msgStringRxPtr);
void usartHandleStringAutoWifi(msg_StringMessage_t *msgStringRxPtr);
void usartHandleStringManWifi(msg_StringMessage_t *msgStringRxPtr);
// == Function Definitions ==
/**
* @brief USARTInTask
* @param argument
*/
void StartUSARTInTask(void const * argument) {
  msg_StringMessage_t *msgStringRxPtr;
  msg_CommandMessage_t *msgCommandTxPtr;
  osEvent msgRxEvent;
  char *directInBuff;
  char *directOutBuff;

  directInBuff = pvPortMalloc(100);
  directOutBuff = pvPortMalloc(100);

  // Strings to send
  const char commStateManualTxString[] = "MANUAL Mode Started\r\n";
  const char commStateAutoTxString[] = "AUTO Mode Started\r\n";

  // Strings to compare with
  const char led0ToggleRxString[] = "Toggle LED0";
  const char commStateManualRxString[] = "MANUAL";
  const char commStateAutoRxString[] = "AUTO";
  const char testATRxString[] = "Test AT";

  /* Infinite loop */
  for (;;) {
    msgRxEvent = osMessageGet(msgQUSARTIn, osWaitForever); // Wait for a message

    // If there is a message in the queue
    if (msgRxEvent.status == osEventMessage) {
      msgStringRxPtr = msgRxEvent.value.p; // Grab the pointer

      // If the message is from the USB port
      if (msgStringRxPtr->messageSource == MSG_SRC_USB) {
        // If the current routing is to AUTO (i.e. if this task must handle input commands)
        if (wifiCommState == COMM_STATE_AUTO) {
          // If the command is the expected length and correct, do the thing!
          if ((msgStringRxPtr->messageLength == (sizeof(testATRxString) - 1))
              && (strncmp(msgStringRxPtr->string, testATRxString, msgStringRxPtr->messageLength) == 0)) {
            // Send the "Send AT" command to USART Out Task
            msgCommandSend(msgPoolUSARTOut, msgQUSARTOut, msgCommandTxPtr, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_SEND_AT);

          } else if ((msgStringRxPtr->messageLength == (sizeof(led0ToggleRxString) - 1))
                     && (strncmp(msgStringRxPtr->string, led0ToggleRxString, msgStringRxPtr->messageLength) == 0)) {
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

          } else if ((msgStringRxPtr->messageLength == (sizeof(commStateManualRxString) - 1))
                     && (strncmp(msgStringRxPtr->string, commStateManualRxString, msgStringRxPtr->messageLength) == 0)) {
            wifiCommState = COMM_STATE_MANUAL;
            HAL_UART_Transmit_DMA(&huart1, commStateManualTxString, sizeof(commStateManualTxString) - 1);

          }
          // Or, if current routing is MANUAL (i.e. all comms get routed wifi<-->usb)
        } else if (wifiCommState == COMM_STATE_MANUAL) {
          if ((msgStringRxPtr->messageLength == (sizeof(commStateAutoRxString) - 1))
              && (strncmp(msgStringRxPtr->string, commStateAutoRxString, msgStringRxPtr->messageLength) == 0)) {
            wifiCommState = COMM_STATE_AUTO;
            HAL_UART_Transmit_DMA(&huart1, commStateAutoTxString, sizeof(commStateManualTxString) - 1);

          } else {
            memcpy(directInBuff, msgStringRxPtr->string, msgStringRxPtr->messageLength);

            // Not sure if this is the right (or at least best) way to do this
            directInBuff[msgStringRxPtr->messageLength] = '\r';
            directInBuff[msgStringRxPtr->messageLength + 1] = '\n';

            HAL_UART_Transmit_DMA(&huart2, directInBuff, msgStringRxPtr->messageLength + 2);

          }
        }
      } else if ((msgStringRxPtr->messageSource == MSG_SRC_WIFI) && (wifiCommState == COMM_STATE_MANUAL)) {
        // Echo wifi module
        memcpy(directOutBuff, msgStringRxPtr->string, msgStringRxPtr->messageLength);

        directOutBuff[msgStringRxPtr->messageLength] = '\r';
        directOutBuff[msgStringRxPtr->messageLength + 1] = '\n';

        HAL_UART_Transmit_DMA(&huart1, directOutBuff, msgStringRxPtr->messageLength + 2);
      }

      // Free the message
      msgStringStructFree(msgPoolUSARTIn, msgStringRxPtr);
    }
  }
}
