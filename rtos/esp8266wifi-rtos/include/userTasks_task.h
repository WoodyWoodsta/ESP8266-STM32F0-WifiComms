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
#define AP_SSID   "coreNet"
#define AP_KEY    "electronics9663"

// == Type Declarations - General ==
// Procedure statuses
typedef enum {
  PROC_STATUS_OK,
  PROC_STATUS_BUSY,
  PROC_STATUS_COMPLETED,
  PROC_STATUS_ERROR
} procStatus_t;

// Method of communication with the wifi module. AUTO allows tasks to handle
// responses from the module. MANUAL routes all communication via USB<-->WIFI
typedef enum {
  COMM_STATE_AUTO,
  COMM_STATE_MANUAL
} commState_t;

// Peripheral states - to be used for locking out peripherals during procedures etc.
typedef enum {
  GEN_STATE_READY,
  GEN_STATE_BUSY,
  GEN_STATE_ERROR
} genericStates_t;

// Wifi communication procedures (flags)
typedef enum {
  WIFI_PROC_NONE,
  WIFI_PROC_AT_TEST,
  WIFI_PROC_INIT,
  WIFI_PROC_CONNECT_AP
} wifiProcedures_t;

// Proceedure flags
typedef struct {
  wifiProcedures_t wifiProcedures;
} globalProcedures_t;

// Custom peripheral states
typedef struct {
  commState_t commState;
  genericStates_t wifiState; // Task level peripheral state flag (for task level locking)
} globalStates_t;

// Global program flags
typedef struct {
  globalStates_t states;
  globalProcedures_t procedures;
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
