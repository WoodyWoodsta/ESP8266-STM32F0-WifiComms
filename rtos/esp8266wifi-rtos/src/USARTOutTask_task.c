/**
 * ============================================================================
 * File Name          : USARTOutTask_task.c
 * Description        : USARTOutTask Body
 * Author             : Sean Wood
 * ============================================================================
 */

// == Includes ==
#include "userTasks_task.h"

// == Private Function Declerations ==
static void interpretCommand(msgCommand_t rxCommand);

// == Function Definitions ==

/**
 * @brief USARTOutTask
 * @param argument
 */
void StartUSARTOutTask(void const * argument) {
  size_t freeHeap;
  msg_genericMessage_t rxMessage;
  /* Infinite loop */
  for (;;) {
    // Wait for messages
    fetchMessage(msgQUSARTOut, &rxMessage, osWaitForever);

    // Indentify the type of message
    switch (rxMessage.messageType) {
    case MSG_TYPE_COMMAND:
      // If we have received a command, decode and interpret it
      interpretCommand(decodeCommand(&rxMessage));
      break;
    default:
      break;
    }
  }
}

/**
 * @brief Interpret the command received, and act on it
 * @param rxCommand: Command received in the message
 */
static void interpretCommand(msgCommand_t rxCommand) {
  switch (rxCommand) {
  case MSG_CMD_WIFI_TX_AT:
    cHAL_USART_sTransmit_IT(&huart2, txString_ATCommandTest,
        strlen(txString_ATCommandTest), 0);
    break;
  case MSG_CMD_WIFI_TX_ATE_0:
    cHAL_USART_sTransmit_IT(&huart2, txString_ATE0, strlen(txString_ATE0), 0);
    break;
  case MSG_CMD_WIFI_TX_CIPMUX_1:
    cHAL_USART_sTransmit_IT(&huart2, txString_multiConnect1,
        strlen(txString_multiConnect1), 0);
    break;
  case MSG_CMD_WIFI_TX_CWMODE_3:
    cHAL_USART_sTransmit_IT(&huart2, txString_stationMode3,
        strlen(txString_stationMode3), 0);
    break;
  case MSG_CMD_WIFI_TX_CONNECT_AP: {
    // Formulate the connect command
    uint8_t apSSID[] = "coreNet";
    uint8_t apKey[] = "electronics9663";
    uint8_t *txApCommand = pvPortMalloc(
        strlen(apSSID) + strlen(apKey) + strlen(txString_connectAPCommand) + 7);
    sprintf(txApCommand, "%s\"%s\",\"%s\"\r\n", txString_connectAPCommand,
        apSSID, apKey);

    HAL_StatusTypeDef status = cHAL_USART_sTransmit_IT(&huart2, txApCommand,
        strlen(txApCommand), 1);
    if (status != HAL_OK) {
      vPortFree(txApCommand);
    }

    break;
  }
  case MSG_CMD_WIFI_TX_START_SERVER:
    cHAL_USART_sTransmit_IT(&huart2, txString_startServer,
        strlen(txString_startServer), 0);

    break;
  default:
    break;
  }
}
