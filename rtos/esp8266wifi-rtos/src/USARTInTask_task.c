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
static void interpretUSBString(msg_stringMessage_t *pStringMessageIn);
static void interpretWifiString(msg_stringMessage_t *pStringMessageIn);
static void fetchString(msg_stringMessage_t *pMessage);

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
static void interpretUSBString(msg_stringMessage_t *pStringMessageIn) {
  // If we are in manual mode, direct string to the Wifi module
  if (globalFlags.states.commState == COMM_STATE_MANUAL) {
    if (strncmp(rxString_commStateAuto, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      globalFlags.states.commState = COMM_STATE_AUTO;
      cHAL_USART_sTransmit_IT(&huart1, txString_commStateAuto, strlen(txString_commStateAuto), 0);
    } else {
      HAL_StatusTypeDef status = cHAL_USART_sTransmit_IT(&huart2, pStringMessageIn->pString, pStringMessageIn->stringLength, 1);

      // If we run into issues, get rid of the string
      if (status != osOK) {
        vPortFree(pStringMessageIn->pString);
      }
    }
  } else if (globalFlags.states.commState == COMM_STATE_AUTO) {
    if (strncmp(rxString_commStateManual, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      globalFlags.states.commState = COMM_STATE_MANUAL;
      cHAL_USART_sTransmit_IT(&huart1, txString_commStateManual, strlen(txString_commStateManual), 0);
    } else if (strncmp(rxString_ATCommandTest, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_TEST_AT, osWaitForever);
    } else if (strncmp(rxString_wifiInit, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_INIT, osWaitForever);
    } else if (strncmp(rxString_wifiConnectAp, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_CONNECT_AP, osWaitForever);
    } else if (strncmp(rxString_wifiStartServer, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_RX_START_SERVER, osWaitForever);
    }

    vPortFree(pStringMessageIn->pString);
  }
}

/**
* @brief Interpret a string received from the Wifi module
* @param *pStringMessageIn: Pointer to a generic message struct to interpret
*/
static void interpretWifiString(msg_stringMessage_t *pStringMessageIn) {
  // If we are in manual mode, direct string to the USB module
  if (globalFlags.states.commState == COMM_STATE_MANUAL) {
    HAL_StatusTypeDef status = cHAL_USART_sTransmit_IT(&huart1, pStringMessageIn->pString, pStringMessageIn->stringLength, 1);

    // If we run into issues, get rid of the string
    if (status != osOK) {
      vPortFree(pStringMessageIn->pString);
    }
  } else if (globalFlags.states.commState == COMM_STATE_AUTO) {
    if (strncmp(rxString_OK, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_RX_OK, osWaitForever);

    } else if (strncmp(rxString_noChange, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_RX_NO_CHANGE, osWaitForever);

    } else if (strncmp(rxString_error, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_RX_ERROR, osWaitForever);

    } else if (strncmp(rxString_noSuchFunction, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_RX_NO_FUNCTION, osWaitForever);

    } else if (strncmp(rxString_fail, pStringMessageIn->pString, pStringMessageIn->stringLength) == 0) {
      sendCommand(msgQBoss, MSG_SRC_USART_IN_TASK, MSG_CMD_WIFI_RX_FAIL, osWaitForever);
    }

    vPortFree(pStringMessageIn->pString);
  }
}

/**
* @brief Fetch a string message from the USARTIn Queue
* @param *messagePtr: Pointer to a generic message struct copy into
*/
static void fetchString(msg_stringMessage_t *pMessage) {
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

