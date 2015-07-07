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

// == Type Declarations - Messaging ==
// Types of messages
typedef enum {
  MSG_TYPE_STRING,
  MSG_TYPE_COMMAND
} msgType_t;

// Destination of messages
typedef enum {
  MSG_SRC_USB,
  MSG_SRC_WIFI,
  MSG_SRC_USART_IN_TASK,
  MSG_SRC_USART_OUT_TASK,
  MSG_SRC_BOSS_TASK
} msgSource_t;

// Commands usable in messages
typedef enum {
  MSG_CMD_WIFI_SEND_AT,
  MSG_CMD_WIFI_CONNECT_AP,
  MSG_COMMAND_LED2_TOGGLE
} msgCommand_t;

// Message to use to send strings
typedef struct {
  msgType_t messageType; // Type of message content
  msgSource_t messageSource; // Where did this message come from
  uint32_t messageLength; // Length of the string
  char *string; // Pointer to string
} msg_StringMessage_t;

// Message to use to send commands
typedef struct {
  msgType_t messageType; // Type of message content
  msgSource_t messageSource; // Where did this message come from
  msgCommand_t command; // Pointer to string
} msg_CommandMessage_t;

// == Exported Variables ==
extern osThreadId bossTaskHandle;
extern osThreadId USARTInTaskHandle;
extern osThreadId USARTOutTaskHandle;
extern commState_t wifiCommState;

// USART In Task String Queue
extern osPoolId msgPoolUSARTIn;
extern osMessageQId msgQUSARTIn;

// USART Out Task String Queue
extern osPoolId msgPoolUSARTOut;
extern osMessageQId msgQUSARTOut;

// Boss Task Command Queue
extern osPoolId msgPoolBoss;
extern osMessageQId msgQBoss;


// == Function Prototypes ==
void StartBossTask(void const * argument);
void StartUSARTInTask(void const * argument);
void StartUSARTOutTask(void const * argument);
msg_StringMessage_t* msgStringStructAlloc(osPoolId mPool, uint32_t msgStringLength, char *msgString);

#endif /*USERTASKS_TASK_H*/