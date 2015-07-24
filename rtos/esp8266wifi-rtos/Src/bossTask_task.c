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
static void proc_wifiInit(msgCommand_t rxCommand);

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
  // NOTE: If one of these are fired, nothing else should be executed, so return
  switch (rxCommand) {
  case MSG_CMD_WIFI_TEST_AT:
    proc_wifiATTest(rxCommand);
    return;
  case MSG_CMD_WIFI_INIT:
    proc_wifiInit(rxCommand);
    return;
  default:
    break;
  }

  // Then check for commands specific to the proceedures in progress
  uint8_t wifiProceedures = globalFlags.proceedures.wifiProceedures;
  if (wifiProceedures & WIFI_PROC_AT_TEST) {
    proc_wifiATTest(rxCommand);
  }
  
  if (wifiProceedures & WIFI_PROC_INIT) {
    proc_wifiInit(rxCommand);
  }
}

// == Proceedure Definitions ==
// NOTE: Proceedures are re-entered upon receiveing a command, or being called specifically
void proc_wifiATTest(msgCommand_t rxCommand) {
  static uint8_t step = 0;
  static msgCommand_t waitingCmd = MSG_CMD_NO_CMD;

  // If we are not waiting on a CMD, but the proceedure function was called, we need to run through anyway
  // We also need to run through if the command is the one we are waiting for
  if ((waitingCmd == MSG_CMD_NO_CMD) || (rxCommand == waitingCmd)) {
    switch (step) {
    case 0:
      // Setup the proceedure
      globalFlags.proceedures.wifiProceedures |= WIFI_PROC_AT_TEST;

      // Step 0 body
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_AT, osWaitForever);

      // Setup re-entry details
      waitingCmd = MSG_CMD_WIFI_RX_OK;
      step = 1;
      break;
    case 1:
      // Step 1 body
      cHAL_USART_sTransmit_IT(&huart1, txString_OKReceived, strlen(txString_OKReceived), 0);

      // Exit the proceedure
      step = 0;
      globalFlags.proceedures.wifiProceedures &= ~WIFI_PROC_AT_TEST;
      waitingCmd = MSG_CMD_NO_CMD;
    default:
      break;
    }
  }
}

void proc_wifiInit(msgCommand_t rxCommand) {
  static uint8_t step = 0;
  static msgCommand_t waitingCmd = MSG_CMD_NO_CMD;

  // If we are not waiting on a CMD, but the proceedure function was called, we need to run through anyway
  // We also need to run through if the command is the one we are waiting for
  if ((waitingCmd == MSG_CMD_NO_CMD) || (rxCommand == waitingCmd)) {
    switch (step) {
    case 0:
      // Setup the proceedure
      globalFlags.proceedures.wifiProceedures |= WIFI_PROC_INIT;

      // Step 0 body - Check AT command set
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_AT, osWaitForever);

      // Setup re-entry details
      waitingCmd = MSG_CMD_WIFI_RX_OK;
      step = 1;
      break;
    case 1:
      // Step 1 body - Turn off byte echo
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_ATE_0, osWaitForever);

      // Setup re-entry details
      waitingCmd = MSG_CMD_WIFI_RX_OK;
      step = 2;
      break;

    case 2:
      // Step 2 body - Put module into dual mode
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_CWMODE_3, osWaitForever);

      // Setup re-entry details
      waitingCmd = MSG_CMD_NO_CMD;
      step = 3;
      break;

    case 3:
      if (rxCommand == MSG_CMD_NO_CMD || rxCommand == MSG_CMD_WIFI_RX_NO_CHANGE) {
        sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_CIPMUX_1, osWaitForever);

        // Setup re-entry details
        step = 4;
        waitingCmd = MSG_CMD_WIFI_RX_OK;
      }

      break;

    case 4:
      // Exit the proceedure
      cHAL_USART_sTransmit_IT(&huart1, txString_wifiInitialised, strlen(txString_wifiInitialised), 0);

      step = 0;
      globalFlags.proceedures.wifiProceedures &= ~WIFI_PROC_INIT;
      waitingCmd = MSG_CMD_NO_CMD;
    default:
      break;
    }
  }
}