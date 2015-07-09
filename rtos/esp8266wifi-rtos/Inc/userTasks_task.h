/**
  * ============================================================================
  * File Name          : userTasks_task.h
  * Description        : Common task source header file
  * ============================================================================
  */

#ifndef USERTASKS_TASK_H
#define USERTASKS_TASK_H

// == Includes ==
#include "cmsis_os.h"
#include "hal_lib.h"
#include "genericMessaging_lib.h"
#include "string.h"
#include "stdio.h"

// == Definitions ==
#define AP_DETAILS "AWNetHome","awnethome92"

// == Type Declarations - General ==
// Method of communication with the wifi module. INTERPRET allows tasks to handle
// responses from the module. DIRECT routes all communication via USB<-->WIFI
typedef enum {
  COMM_STATE_AUTO,
  COMM_STATE_MANUAL
} commState_t;

// == Exported Variables ==
extern osThreadId bossTaskHandle;
extern osThreadId USARTInTaskHandle;
extern osThreadId USARTOutTaskHandle;
extern commState_t wifiCommState;

// USART In Task String Queue
extern osMessageQId msgQUSARTIn;

// USART Out Task String Queue
extern osMessageQId msgQUSARTOut;

// Boss Task Command Queue
extern osMessageQId msgQBoss;


// == Function Prototypes ==
void StartBossTask(void const * argument);
void StartUSARTInTask(void const * argument);
void StartUSARTOutTask(void const * argument);

#endif /*USERTASKS_TASK_H*/