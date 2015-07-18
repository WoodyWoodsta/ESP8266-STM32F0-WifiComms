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
    cHAL_USART_sTransmit_IT(&huart2, txString_ATCommandTest, strlen(txString_ATCommandTest), 0);
  default:
    break;
  }
}