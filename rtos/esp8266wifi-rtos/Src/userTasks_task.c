/**
  * ============================================================================
  * File Name          : userTasks_task.c
  * Description        : Common source between all tasks, specific to tasks
  *                      Also includes source common to memory pools and
  *                      messaging cues
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Exported Variables ==
osThreadId bossTaskHandle;
osThreadId USARTInTaskHandle;
osThreadId USARTOutTaskHandle;

// USART In Task String Queue
osPoolId msgPoolUSARTIn;
osMessageQId msgQUSARTIn;

// USART Out Task String Queue
osPoolId msgPoolUSARTOut;
osMessageQId msgQUSARTOut;

// Boss Task Command Queue
osPoolId msgPoolBoss;
osMessageQId msgQBoss;

// == Function Definitions ==
msg_StringMessage_t* msgStringStructAlloc(osPoolId mPool, uint32_t msgStringLength, char *msgString) {
  msg_StringMessage_t* msgStringStructPtr; // Create the struct pointer needed for the message

  msgStringStructPtr = osPoolAlloc(mPool);

  msgStringStructPtr->messageType = MSG_TYPE_STRING_IN; // Label the message as a string type message TODO Sort this out
  msgStringStructPtr->messageLength = msgStringLength; // Assign the length of the allocated memory space
  msgStringStructPtr->string = pvPortMalloc(msgStringLength); // Actually allocate the memory space

  strncpy(msgStringStructPtr->string, msgString, msgStringLength); // Copy into the new space, the string contents

  return msgStringStructPtr;
}

void msgStringStructFree(osPoolId mPool, msg_StringMessage_t *msgStringStructPtr) {
  vPortFree(msgStringStructPtr->string); // Free the memory

  osPoolFree(mPool, msgStringStructPtr); // Free the message from the memory pool

  // TODO Add some sort of safety here, gee...
}

