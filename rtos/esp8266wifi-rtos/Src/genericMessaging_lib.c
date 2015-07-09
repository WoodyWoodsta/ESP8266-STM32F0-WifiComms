/**
* ============================================================================
* File Name          : genericMessaging_lib.c
* Description        : Generic messaging system source file which introduces
*                      the ability to send generic messages linking in
*                      customisable data structures (allowing any data to be
*                      sent to any task with one type of message Q)
* ============================================================================
*/

// == Includes ==
#include "genericMessaging_lib.h"

// == Function Definitions ==
/**
* @brief Send a generic message which packages any data structure
* @param msgQ: Message Q to send the message to
* @param type: Type of data that is linked in
* @param source: Where the message is being sent from
* @param mRsp: Memory responsibility - whether or not the library should be responsible for allocating and deallocating the memory for the data
* @param *data: Pointer to the struct holding the message data
* @param timeout: How long the operating system must wait until the message is successfully placed in message Q msgQ
*/
void sendMessage(osMessageQId msgQ, msgType_t type, msgSource_t source, uint8_t mRsp, void *data, uint32_t timeout) {
  uint32_t dataLength; // Length of the data to be linked in
  msg_genericMessage_t *message;
  void *dataContent;

  // Allocate a block of memory in the global memory pool for the generic message
  message = osPoolAlloc(genericMPool);

  // Identify the size of the data that will be linked in based on the data struct used
  switch (type) {
  case MSG_TYPE_STRING:
    dataLength = sizeof(data_string_t);
    break;

  case MSG_TYPE_COMMAND:
    dataLength = sizeof(data_command_t);
    break;

  case MSG_TYPE_COORDS:
    dataLength = sizeof(data_coords_t);
    break;
  }

  // If the library is held responsible for managing memory for data, do the thing!
  if (mRsp) {
    // Allocated memory for the data
    dataContent = pvPortMalloc(dataLength);

    // Copy the data into the allocated memory block
    memcpy(dataContent, data, dataLength);

    // Pass the pointer to the generic message
    message->data = dataContent;
    message->mRsp = MRSP_HANDLE;

  } else {
    // Just pass the generic message the pointer, the library will not handle the memory
    message->data = data;
    message->mRsp = MRSP_NO_HANDLE;
  }

  // Polpulate the generic message
  message->data = dataContent;
  message->messageType = type;
  message->messageSource = source;
  message->dataLength = dataLength;

  // Send the message!
  osMessagePut(msgQ, (uint32_t) message, timeout);
}

/**
* @brief Wait for a generic message in the queue and copy out the generic message upon arrival
* @param msgQ: Message Q to send the message to
* @param *messagePtr: Pointer to a generic message struct
* @param timeout: How long the operating system must wait until the message is successfully placed in message Q msgQ
*/
void fetchMessage(osMessageQId msgQ, msg_genericMessage_t *messagePtr, uint32_t timeout) {
  osEvent messageEvent;
  msg_genericMessage_t *messageRxPtr;

  // Wait for a message in the message Q, msgQ
  messageEvent = osMessageGet(msgQ, timeout);

  // If the recieved data is a message
  if (messageEvent.status == osEventMessage) {
    // Grab the pointer to the generic message and copy it into the externally declared message struct
    messageRxPtr = messageEvent.value.p;
    memcpy(messagePtr, messageRxPtr, sizeof(msg_genericMessage_t));

    // Then free the message from the global memory pool
    osPoolFree(genericMPool, messageRxPtr);

  } else {
    // If there was no message received after the timeout value, set the type to NULL to indicate this
    messagePtr->messageType = MSG_TYPE_NO_MESSAGE;

  }
}

/**
* @brief Copy out the data that was in the generic message
* @param *messagePtr: Pointer to a generic message struct
* @param *dataStruct: Pointer to a struct where the data will be copied into. Pass NULL is user is handling the memory
*/
void *decodeMessage(msg_genericMessage_t *messagePtr, void *dataStruct) {
  // If the library is handling the data memory
  if (messagePtr->mRsp == MRSP_HANDLE) {
    void *dataPtr = messagePtr->data;

    // Copy the data into the locally declared struct by pointer dataStruct
    memcpy(dataStruct, dataPtr, messagePtr->dataLength);

    // Free the previously allocated memory
    vPortFree(dataPtr);
    return NULL;

  } else {
    // Else, user is handling the memory, therefore just return the pointer to that data
    return messagePtr->data;

  }
}
