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

// == Exported Variables ==
extern osThreadId bossTaskHandle;
extern osThreadId USARTInTaskHandle;
extern osThreadId USARTOutTaskHandle;

// USART In Task String Queue
extern osPoolId msgPoolUSARTIn;
extern osMessageQId msgQUSARTIn;

// USART Out Task String Queue
extern osPoolId msgPoolUSARTOut;
extern osMessageQId msgQUSARTOut;

// Boss Task Command Queue
extern osPoolId msgPoolBoss;
extern osMessageQId msgQBoss;

// == Type Declarations ==
// Types of messages
typedef enum {
  MSG_TYPE_STRING_IN,
  MSG_TYPE_STRING_OUT,
  MSG_TYPE_COMMAND
} msgType_t;

// Destination of messages
typedef enum {
  MSG_DEST_USART_IN,
  MSG_DEST_USART_OUT,
  MSG_DEST_BOSS
} msgDestination_t;

// Commands usable in messages
typedef enum {
  MSG_COMMAND_LED0_TOGGLE,
  MSG_COMMAND_LED1_TOGGLE,
  MSG_COMMAND_LED2_TOGGLE
} msgCommand_t;

// Message to use to send strings
typedef struct {
  msgType_t messageType; // Type of message content
  msgDestination_t messageDestination; // Where must this message go
  uint32_t messageLength; // Length of the string
  char *string; // Pointer to string
} msg_StringMessage_t;

// Message to use to send commands
typedef struct {
  msgType_t messageType; // Type of message content
  msgDestination_t messageDestination; // Where must this message go
  msgCommand_t command; // Pointer to string
} msg_CommandMessage_t;

// == Function Prototypes ==
void StartBossTask(void const * argument);
void StartUSARTInTask(void const * argument);
void StartUSARTOutTask(void const * argument);
msg_StringMessage_t* msgStringStructAlloc(osPoolId mPool, uint32_t msgStringLength, char *msgString);
void msgStringStructFree(osPoolId mPool, msg_StringMessage_t *msgStringStructPtr);

#endif /*USERTASKS_TASK_H*/