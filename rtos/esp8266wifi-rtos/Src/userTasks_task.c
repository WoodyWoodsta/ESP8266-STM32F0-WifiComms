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
commState_t wifiCommState = COMM_STATE_AUTO;

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
/**
  * @brief Allocate and populate a string message as well as a seperate memory block for the string
  * @param mPool: Memory pool in which the string message has been allocated
  * @param msgStringLength: Length of memory to be allocated for the string
  * @param *msgString: Pointer to the string
  * @return Pointer to the string message struct
  */
msg_StringMessage_t* msgStringStructAlloc(osPoolId mPool, uint32_t msgStringLength, char *msgString) {
  msg_StringMessage_t* msgStringStructPtr; // Create the struct pointer needed for the message

  msgStringStructPtr = osPoolAlloc(mPool);

  msgStringStructPtr->messageType = MSG_TYPE_STRING; // Label the message as a string type message
  msgStringStructPtr->messageLength = msgStringLength; // Assign the length of the allocated memory space
  msgStringStructPtr->string = pvPortMalloc(msgStringLength); // Actually allocate the memory space

  memcpy(msgStringStructPtr->string, msgString, msgStringLength); // Copy into the new space, the string contents

  return msgStringStructPtr;
}

/**
  * @brief Free the string message from memory
  * @param mPool: Memory pool in which the string message has been allocated
  * @param *msgStringStructPtr: Pointer to the string message struct
  */
void msgStringStructFree(osPoolId mPool, msg_StringMessage_t *msgStringStructPtr) {
  vPortFree(msgStringStructPtr->string); // Free the memory

  osPoolFree(mPool, msgStringStructPtr); // Free the message from the memory pool

  // TODO Add some sort of safety here, gee...
}

/**
  * @brief Create, populate and send a command type message
  * @param mPool: Memory pool to allocate the message to
  * @param messageQ: Message queue to send the message to
  * @param *msgCommandTxPtr: pointer to the message struct
  * @param source: Who sent the message
  * @param command: The command
  */
void msgCommandSend(osPoolId mPool, osMessageQId messageQ, msg_CommandMessage_t *msgCommandTxPtr, msgSource_t source, msgCommand_t command) {
  // Allocate memory for the message in the memory pool
  msgCommandTxPtr = osPoolAlloc(mPool);

  // Fill the message
  msgCommandTxPtr->messageType = MSG_TYPE_COMMAND;
  msgCommandTxPtr->messageSource = source;
  msgCommandTxPtr->command = command;

  // Send the message
  osMessagePut(messageQ, (uint32_t) msgCommandTxPtr, osWaitForever);
}

