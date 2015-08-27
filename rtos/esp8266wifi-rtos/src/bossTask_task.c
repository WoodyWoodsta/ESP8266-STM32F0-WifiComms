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
static procStatus_t proc_wifiATTest(msgCommand_t rxCommand);
static procStatus_t proc_wifiInit(msgCommand_t rxCommand);
static procStatus_t proc_wifiConnectAP(msgCommand_t rxCommand);
static procStatus_t proc_wifiStartServer(msgCommand_t rxCommand);

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

  // If in AUTO mode, set off a WIFI startup
//  if (globalFlags.states.commState == COMM_STATE_AUTO) {
//    sendCommand(msgQBoss, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_INIT,
//        osWaitForever);
//  }

  /* Infinite loop */
  for (;;) {
    fetchMessage(msgQBoss, &rxMessage, 0);

    switch (rxMessage.messageType) {
    case MSG_TYPE_NO_MESSAGE:
      break;
    case MSG_TYPE_COMMAND:
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
  // Check first for known commands specific to the task
  // NOTE: If one of these are fired, nothing else should be executed, so return
  switch (rxCommand) {
  case MSG_CMD_WIFI_TEST_AT: {
    procStatus_t status;
    do {
      status = proc_wifiATTest(rxCommand);

      // Handle the error
      if (status == PROC_STATUS_ERROR) {
        cHAL_USART_sTransmit_IT(&huart1, txString_ATCommandTestError,
            strlen(txString_ATCommandTestError), 0);
        return;
      } else if (status == PROC_STATUS_BUSY) {
        osDelay(100);
      } // If the peripheral is busy, wait for a bit
    } while (status != PROC_STATUS_OK && status != PROC_STATUS_COMPLETED);
    return;
  }
  case MSG_CMD_WIFI_INIT: {
    procStatus_t status;
    do {
      status = proc_wifiInit(rxCommand);

      // Handle the error
      if (status == PROC_STATUS_ERROR) {
        cHAL_USART_sTransmit_IT(&huart1, txString_wifiInitError,
            strlen(txString_wifiInitError), 0);
        return;
      } else if (status == PROC_STATUS_BUSY) {
        osDelay(100);
      } // If the peripheral is busy, wait for a bit
    } while (status != PROC_STATUS_OK && status != PROC_STATUS_COMPLETED);
    return;
  }
  case MSG_CMD_WIFI_CONNECT_AP: {
    procStatus_t status;
    do {
      status = proc_wifiConnectAP(rxCommand);

      // Handle the error
      if (status == PROC_STATUS_ERROR) {
        cHAL_USART_sTransmit_IT(&huart1, txString_wifiInitError,
            strlen(txString_wifiInitError), 0);
        return;
      } else if (status == PROC_STATUS_BUSY) {
        osDelay(100);
      } // If the peripheral is busy, wait for a bit
    } while (status != PROC_STATUS_OK && status != PROC_STATUS_COMPLETED);
    return;
  }
  case MSG_CMD_WIFI_RX_START_SERVER: {
    procStatus_t status;
    do {
      status = proc_wifiStartServer(rxCommand);

      // Handle the error
      if (status == PROC_STATUS_ERROR) {
        cHAL_USART_sTransmit_IT(&huart1, txString_ATCommandTestError,
            strlen(txString_ATCommandTestError), 0);
        globalFlags.states.wifiState = GEN_STATE_READY;
        return;
      } else if (status == PROC_STATUS_BUSY) {
        osDelay(100);
      } // If the peripheral is busy, wait for a bit
    } while (status != PROC_STATUS_OK && status != PROC_STATUS_COMPLETED);
    return;
  }

  default:
    break;
  }

  // Then check for commands specific to the proceedures in progress
  switch (globalFlags.procedures.wifiProcedures) {
  case WIFI_PROC_AT_TEST:
    proc_wifiATTest(rxCommand);
    break;
  case WIFI_PROC_INIT:
    proc_wifiInit(rxCommand);
    break;
  case WIFI_PROC_CONNECT_AP:
    proc_wifiConnectAP(rxCommand);
    break;
  case WIFI_PROC_START_SERVER:
    proc_wifiStartServer(rxCommand);
    break;
  default:
    break;
  }
}

// == Proceedure Definitions ==
// NOTE: Proceedures are re-entered upon receiveing a command, or being called specifically
procStatus_t proc_wifiATTest(msgCommand_t rxCommand) {
  static uint8_t step = 0;

  // If we are not waiting on a CMD, but the proceedure function was called, we need to run through anyway
  // We also need to run through if the command is the one we are waiting for
  switch (step) {
  case 0:
    if (globalFlags.states.wifiState == GEN_STATE_READY) {
      globalFlags.states.wifiState = GEN_STATE_BUSY;
    } else if (globalFlags.states.wifiState == GEN_STATE_BUSY) {
      return PROC_STATUS_BUSY;
    } else if (globalFlags.states.wifiState == GEN_STATE_ERROR) {
      return PROC_STATUS_ERROR;
    }

    // Setup the proceedure
    globalFlags.procedures.wifiProcedures = WIFI_PROC_AT_TEST;

    // Step 0 body
    sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_AT,
    osWaitForever);

    // Setup re-entry details
    step = 1;
    break;
  case 1:
    if (rxCommand == MSG_CMD_WIFI_RX_OK) {
      // Step 1 body
      cHAL_USART_sTransmit_IT(&huart1, txString_OKReceived,
          strlen(txString_OKReceived), 0);

    } else if (rxCommand == MSG_CMD_WIFI_RX_NO_FUNCTION
        || rxCommand == MSG_CMD_WIFI_RX_ERROR) {
      cHAL_USART_sTransmit_IT(&huart1, txString_ATCommandTestError,
          strlen(txString_ATCommandTestError), 0);
    }

    // Exit the procedure
    step = 0;
    globalFlags.procedures.wifiProcedures = WIFI_PROC_NONE;
    globalFlags.states.wifiState = GEN_STATE_READY;
    return PROC_STATUS_COMPLETED;
    break;
  default:
    break;
  }

  return PROC_STATUS_OK;
}

procStatus_t proc_wifiInit(msgCommand_t rxCommand) {
  static step = 0;
  uint8_t finished = 0;

  // If we are not waiting on a CMD, but the proceedure function was called, we need to run through anyway
  // We also need to run through if the command is the one we are waiting for
  while (!finished) {
    switch (step) {
    case 0:
      if (globalFlags.states.wifiState == GEN_STATE_READY) {
        globalFlags.states.wifiState = GEN_STATE_BUSY;
      } else if (globalFlags.states.wifiState == GEN_STATE_BUSY) {
        return PROC_STATUS_BUSY;
      } else if (globalFlags.states.wifiState == GEN_STATE_ERROR) {
        return PROC_STATUS_ERROR;
      }

      // Setup the proceedure
      globalFlags.procedures.wifiProcedures = WIFI_PROC_INIT;

      // Step 0 body - Check AT command set
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_AT,
      osWaitForever);

      // Setup re-entry details
      step = 1;
      finished = 1;
      break;
    case 1:
      if (rxCommand == MSG_CMD_WIFI_RX_OK) {
        // Step 1 body - Turn off byte echo
        sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_ATE_0,
        osWaitForever);

        // Setup re-entry details
        step = 2;
        finished = 1;
      } else {
        step = 5;
      }

      break;
    case 2:
      if (rxCommand == MSG_CMD_WIFI_RX_OK) {
        // Step 2 body - Put module into dual mode
        sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_CWMODE_3,
        osWaitForever);

        // Setup re-entry details
        step = 3;
        finished = 1;
      } else {
        step = 5;
      }

      break;
    case 3:
      if (rxCommand == MSG_CMD_NO_CMD
          || rxCommand == MSG_CMD_WIFI_RX_NO_CHANGE) {
        sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_CIPMUX_1,
        osWaitForever);

        // Setup re-entry details
        step = 4;
        finished = 1;
      } else {
        step = 5;
      }

      break;
    case 4:
      if (rxCommand == MSG_CMD_WIFI_RX_OK) {
        // Exit the proceedure
        cHAL_USART_sTransmit_IT(&huart1, txString_wifiInitialised,
            strlen(txString_wifiInitialised), 0);

        step = 0;
        globalFlags.procedures.wifiProcedures = WIFI_PROC_NONE;
        globalFlags.states.wifiState = GEN_STATE_READY;
        return PROC_STATUS_COMPLETED;
      } else {
        step = 5;
      }

      break;
    case 5:
      globalFlags.procedures.wifiProcedures = WIFI_PROC_NONE;
      globalFlags.states.wifiState = GEN_STATE_ERROR;
      return PROC_STATUS_ERROR;
    default:
      break;
    }
  }
  return PROC_STATUS_OK;
}

procStatus_t proc_wifiConnectAP(msgCommand_t rxCommand) {
  static uint8_t step = 0;
  uint8_t finished = 0;

  // If we are not waiting on a CMD, but the proceedure function was called, we need to run through anyway
  // We also need to run through if the command is the one we are waiting for
  while (!finished) {
    switch (step) {
    case 0:
      if (globalFlags.states.wifiState == GEN_STATE_READY) {
        globalFlags.states.wifiState = GEN_STATE_BUSY;
      } else if (globalFlags.states.wifiState == GEN_STATE_BUSY) {
        return PROC_STATUS_BUSY;
      } else if (globalFlags.states.wifiState == GEN_STATE_ERROR) {
        return PROC_STATUS_ERROR;
      }

      // Setup the proceedure
      globalFlags.procedures.wifiProcedures = WIFI_PROC_CONNECT_AP;

      // Step 0 body - Check AT command set
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_AT,
      osWaitForever);

      // Setup re-entry details
      step = 1;
      finished = 1;
      break;
    case 1:
      if (rxCommand == MSG_CMD_WIFI_RX_OK) {
        // Exit the proceedure
        sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_CONNECT_AP,
        osWaitForever);

        step = 2;
        finished = 1;
      } else {
        step = 3;
      }

      break;
    case 2:
      if (rxCommand == MSG_CMD_WIFI_RX_OK) {
        cHAL_USART_sTransmit_IT(&huart1, txString_wifiConnected,
            strlen(txString_wifiConnected), 0);

      } else if (rxCommand == MSG_CMD_WIFI_RX_FAIL) {
        step = 3;
      }
      step = 0;
      globalFlags.procedures.wifiProcedures = WIFI_PROC_NONE;
      globalFlags.states.wifiState = GEN_STATE_READY;
      return PROC_STATUS_COMPLETED;
      break;
    case 3:
      globalFlags.procedures.wifiProcedures = WIFI_PROC_NONE;
      globalFlags.states.wifiState = GEN_STATE_READY;
      return PROC_STATUS_ERROR;
    default:
      break;
    }
  }
  return PROC_STATUS_OK;
}

static procStatus_t proc_wifiStartServer(msgCommand_t rxCommand) {
  static uint8_t step = 0;
  uint8_t finished = 0;

  // If we are not waiting on a CMD, but the procedure function was called, we need to run through anyway
  // We also need to run through if the command is the one we are waiting for
  while (!finished) {
    switch (step) {
    case 0:
      if (globalFlags.states.wifiState == GEN_STATE_READY) {
        globalFlags.states.wifiState = GEN_STATE_BUSY;
      } else if (globalFlags.states.wifiState == GEN_STATE_BUSY) {
        return PROC_STATUS_BUSY;
      } else if (globalFlags.states.wifiState == GEN_STATE_ERROR) {
        return PROC_STATUS_ERROR;
      }

      // Setup the proceedure
      globalFlags.procedures.wifiProcedures = WIFI_PROC_START_SERVER;

      // Step 0 body - Check AT command set
      sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK, MSG_CMD_WIFI_TX_AT,
      osWaitForever);

      // Setup re-entry details
      step = 1;
      finished = 1;
      break;
    case 1:
      if (rxCommand == MSG_CMD_WIFI_RX_OK) {
        // Send command to send command to start server
        sendCommand(msgQUSARTOut, MSG_SRC_BOSS_TASK,
            MSG_CMD_WIFI_TX_START_SERVER,
            osWaitForever);

        step = 2;
        finished = 1;
      } else {
        step = 3;
      }

      break;
    case 2:
      if (rxCommand == MSG_CMD_WIFI_RX_OK
          || rxCommand == MSG_CMD_WIFI_RX_NO_CHANGE) {
        cHAL_USART_sTransmit_IT(&huart1, txString_wifiServerStarted,
            strlen(txString_wifiServerStarted), 0);

        step = 0;
      }

      globalFlags.procedures.wifiProcedures = WIFI_PROC_NONE;
      globalFlags.states.wifiState = GEN_STATE_READY;
      return PROC_STATUS_COMPLETED;
      break;
    case 3:
      globalFlags.procedures.wifiProcedures = WIFI_PROC_NONE;
      globalFlags.states.wifiState = GEN_STATE_READY;
      return PROC_STATUS_ERROR;
    default:
      break;
    }
  }
  return PROC_STATUS_OK;
}
