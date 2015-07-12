/**
  * ============================================================================
  * File Name          : USARTInTask_task.c
  * Description        : USARTInTask Body
  * ============================================================================
  */

  // == Includes ==
#include "userTasks_task.h"

// == Function Declarations ==
void interpretString(msg_stringMessage_t *stringMessageInPtr);
void fetchString(msg_stringMessage_t *messagePtr);

// == Function Definitions ==
/**
* @brief USARTInTask
* @param argument
*/
void StartUSARTInTask(void const * argument) {
  msg_stringMessage_t messageRx;

  /* Infinite loop */
  for (;;) {
    fetchString(&messageRx);

    switch (messageRx.messageSource) {
    case MSG_SRC_USB:
      interpretString(&messageRx);
    }

    osDelay(1);

  }
}

void interpretString(msg_stringMessage_t *stringMessageInPtr) {
  if (wifiCommState == COMM_STATE_MANUAL) {
    HAL_StatusTypeDef status = cHAL_USART_sTransmit_DMA(&huart1, stringMessageInPtr->stringPtr, stringMessageInPtr->stringLength);

    // If we run into issues, get rid of the string
    if (status != HAL_OK) {
      vPortFree(stringMessageInPtr->stringPtr);
    }
  }
}

void fetchString(msg_stringMessage_t *messagePtr) {
  osEvent messageEvent;
  msg_stringMessage_t *messageRxPtr;

  // Wait for a message in the message Q, msgQUSARTIn
  messageEvent = osMessageGet(msgQUSARTIn, osWaitForever);

  // If the recieved data is a message
  if (messageEvent.status == osEventMessage) {
    // Grab the pointer to the string message and copy out to an external struct
    messageRxPtr = messageEvent.value.p;
    memcpy(messagePtr, messageRxPtr, sizeof(msg_stringMessage_t));

    // Then free the message from the global memory pool
    osPoolFree(strBufMPool, messageRxPtr);
  }
}

