/**
  * ============================================================================
  * File Name          : userTasks_task.c
  * Description        : Common source between all tasks, specific to tasks
  *                      Also includes source common to memory pools and
  *                      messaging cues
  * Author             : Sean Wood
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Exported Variables ==
osThreadId bossTaskHandle;
osThreadId USARTInTaskHandle;
osThreadId USARTInBufferTaskHandle;
osThreadId USARTOutTaskHandle;
commState_t wifiCommState = COMM_STATE_MANUAL;

// USART In Task String Queue
osMessageQId msgQUSARTIn;

// USART Out Task String Queue
osMessageQId msgQUSARTOut;

// Boss Task Command Queue
osMessageQId msgQBoss;
