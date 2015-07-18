/**
  * ============================================================================
  * File Name          : bossTask_task.c
  * Description        : Boss Task Body
  * Author             : Sean Wood
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Private Function Declarations ==
static void interpretCommand(msgCommand_t rxCommand);
static void proc_wifiATTest(msgCommand_t rxCommand);

// == Function Definitions ==
/**
* @brief bossTask
* @param argument
*/
void StartBossTask(void const * argument) {
  // Start receiving data via USB UART
  cHAL_UART_TermReceive_IT(&huart1, 512);
  cHAL_UART_TermReceive_IT(&huart2, 512);

  msg_genericMessage_t rxMessage;
  /* Infinite loop */
  for (;;) {
    fetchMessage(msgQBoss, &rxMessage, 0);

    switch (rxMessage.messageType) {
    case MSG_TYPE_NO_MESSAGE:
      break;
    case MSG_TYPE_COMMAND:
      interpretCommand(decodeCommand(&rxMessage));
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
  // Check first for known commands specific to the task
  switch (rxCommand) {
  case MSG_CMD_WIFI_TEST_AT:
    proc_wifiATTest(rxCommand);
  default:
    break;
  }

  // Then check for commands specific to the proceedures in progress
  switch (globalFlags.proceedures.wifiProceedure) {
  case WIFI_PROC_AT_TEST:
    proc_wifiATTest(rxCommand);
    break;
  default:

    break;
  }
}

// == Proceedure Definitions ==
void proc_wifiATTest(msgCommand_t rxCommand) {
  static uint8_t step = 0;
  static msgCommand_t waitingCmd = MSG_CMD_NO_CMD;

  if ((waitingCmd == MSG_CMD_NO_CMD) || (rxCommand == waitingCmd)) {
    switch (step) {
    case 0:
      globalFlags.proceedures.wifiProceedure = WIFI_PROC_AT_TEST;
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_AT, osWaitForever);
      waitingCmd = MSG_CMD_WIFI_RX_OK;
      step = 1;
      break;
    case 1:
      cHAL_USART_sTransmit_IT(&huart1, txString_OKReceived, strlen(txString_OKReceived), 0);
      step = 0;
      globalFlags.proceedures.wifiProceedure = WIFI_PROC_NONE;
      waitingCmd = MSG_CMD_NO_CMD;
    default:
      break;
    }
  }
}