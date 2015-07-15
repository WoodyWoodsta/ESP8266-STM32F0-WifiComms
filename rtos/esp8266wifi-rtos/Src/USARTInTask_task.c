/**
  * ============================================================================
  * File Name          : USARTInTask_task.c
  * Description        : USARTInTask Body
  * Author             : Sean Wood
  * ============================================================================
  */

  // == Includes ==
#include "userTasks_task.h"

// == Private Function Declarations ==
void interpretUSBString(msg_stringMessage_t *pStringMessageIn);
void interpretWifiString(msg_stringMessage_t *pStringMessageIn);
void fetchString(msg_stringMessage_t *pMessage);

// == Function Definitions ==
/**
* @brief USARTInTask
* @param argument
*/
void StartUSARTInTask(void const * argument) {
  msg_stringMessage_t rxMessage;

  /* Infinite loop */
  for (;;) {
    fetchString(&rxMessage);

    switch (rxMessage.messageSource) {
    case MSG_SRC_USB:
      interpretUSBString(&rxMessage);
      break;
    case MSG_SRC_WIFI:
      interpretWifiString(&rxMessage);
      break;
    }
  }
}

/**
* @brief Interpret a string received from the USB USART peripheral
* @param *pStringMessageIn: Pointer to a generic message struct to interpret
*/
void interpretUSBString(msg_stringMessage_t *pStringMessageIn) {
  // If we are in manual mode, direct string to the Wifi module
  if (wifiCommState == COMM_STATE_MANUAL) {
    HAL_StatusTypeDef status = cHAL_USART_sTransmit_IT(&huart2, pStringMessageIn->pString, pStringMessageIn->stringLength);

    // If we run into issues, get rid of the string
    if (status != osOK) {
      vPortFree(pStringMessageIn->pString);
    }
  }
}

/**
* @brief Interpret a string received from the Wifi module
* @param *pStringMessageIn: Pointer to a generic message struct to interpret
*/
void interpretWifiString(msg_stringMessage_t *pStringMessageIn) {
  // If we are in manual mode, direct string to the USB module
  if (wifiCommState == COMM_STATE_MANUAL) {
    HAL_StatusTypeDef status = cHAL_USART_sTransmit_IT(&huart1, pStringMessageIn->pString, pStringMessageIn->stringLength);

    // If we run into issues, get rid of the string
    if (status != osOK) {
      vPortFree(pStringMessageIn->pString);
    }
  }
}

/**
* @brief Fetch a string message from the USARTIn Queue
* @param *messagePtr: Pointer to a generic message struct copy into
*/
void fetchString(msg_stringMessage_t *pMessage) {
  osEvent messageEvent;
  msg_stringMessage_t *pRxMessage;

  // Wait for a message in the message Q, msgQUSARTIn
  messageEvent = osMessageGet(msgQUSARTIn, osWaitForever);

  // If the recieved data is a message
  if (messageEvent.status == osEventMessage) {
    // Grab the pointer to the string message and copy out to an external struct
    pRxMessage = messageEvent.value.p;
    memcpy(pMessage, pRxMessage, sizeof(msg_stringMessage_t));

    // Then free the message from the string buffer memory pool
    osPoolFree(strBufMPool, pRxMessage);
  }
}

