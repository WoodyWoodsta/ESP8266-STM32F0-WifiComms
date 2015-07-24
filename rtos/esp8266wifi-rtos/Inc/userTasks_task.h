/**
  * ============================================================================
  * File Name          : userTasks_task.h
  * Description        : Common task source header file
  * Author             : Sean Wood
  * ============================================================================
  */

#ifndef USERTASKS_TASK_H
#define USERTASKS_TASK_H

// == Includes ==
#include "cmsis_os.h"
#include "hal_lib.h"
#include "genericMessaging_lib.h"
#include "string.h"
#include "strings_res.h"
#include "stdio.h"

// == Definitions ==
#define AP_DETAILS "AWNetHome","awnethome92"

// == Type Declarations - General ==
// Method of communication with the wifi module. AUTO allows tasks to handle
// responses from the module. MANUAL routes all communication via USB<-->WIFI
typedef enum {
  COMM_STATE_AUTO,
  COMM_STATE_MANUAL
} commState_t;

// Wifi communication proceedures (flags)
typedef enum {
  WIFI_PROC_AT_TEST = 0b00000001,
  WIFI_PROC_INIT = 0b00000010,
  WIFI_PROC_CONNECT_AP = 0b00000100
} wifiProceedures_t;

typedef struct {
  uint8_t wifiProceedures; // Support for up to 8 proceedures
} globalProceedures_t;

typedef struct {
  commState_t commState;
  globalProceedures_t proceedures;
} globalFlags_t;

// == Exported Variables ==
extern osThreadId bossTaskHandle;
extern osThreadId USARTInTaskHandle;
extern osThreadId USARTInBufferTaskHandle;
extern osThreadId USARTOutTaskHandle;
extern globalFlags_t globalFlags;

// USART In Task String Queue
extern osMessageQId msgQUSARTIn;

// USART Out Task String Queue
extern osMessageQId msgQUSARTOut;

// Boss Task Command Queue
extern osMessageQId msgQBoss;


// == Function Prototypes ==
void StartBossTask(void const * argument);
void StartUSARTInTask(void const * argument);
void StartUSARTInBufferTask(void const * argument);
void StartUSARTOutTask(void const * argument);

#endif /*USERTASKS_TASK_H*/