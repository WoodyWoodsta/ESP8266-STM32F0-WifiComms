/**
  * ============================================================================
  * File Name          : genericMessaging_lib.h
  * Description        : Generic messaging system header file
  * Author             : Sean Wood
  * ============================================================================
  */

#ifndef GENERICMESSAGING_LIB_H
#define GENERICMESSAGING_LIB_H

// == Includes ==
#include "cmsis_os.h"
#include "hal_lib.h"
#include "string.h"

// == Definitions ==
#define MRSP_NO_HANDLE 0 // Do not let the library handle the data memory
#define MRSP_HANDLE 1 // Let the library handle the data memory

#define GLOBAL_MESSAGE_MPOOL_SIZE       20 // Maximum number of messages that can exist in memory
#define STRING_BUFFER_MPOOL_SIZE        10 // Maximum number of string buffer pointer messages that can exist in memory
#define RBUF_BUFFER_ENTRIES             20 // Number of entries in the ring buffer
#define RBUF_ENTRY_PTR_SIZE             sizeof(ringBuf_entry_t *)
#define RBUF_BUFFER_SIZE                RBUF_BUFFER_ENTRIES * RBUF_ENTRY_PTR_SIZE // Size of the memory for the ring buffer
#define RBUF_ENTRY_HEADER_SIZE          sizeof(msgSource_t) + sizeof(uint16_t) // Size of a ring buffer entry header

// == Type Definitions ==
// Types of messages
typedef enum {
  MSG_TYPE_NO_MESSAGE,
  MSG_TYPE_STRING,
  MSG_TYPE_COORDS,
  MSG_TYPE_COMMAND
} msgType_t;

// Sources of messages
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
  MSG_COMMAND_LED0_TOGGLE
} msgCommand_t;

// Generic message struct to package any associated data
typedef struct {
  msgType_t messageType; // Type of message data
  msgSource_t messageSource; // Where did this message come from
  uint8_t mRsp; // Data memory responsibility
  uint32_t dataLength; // Length of the data
  void *data; // Pointer to data TODO Rename this to dataPtr
} msg_genericMessage_t;

// String pointer message struct to be used for sending to the USART In Task
typedef struct {
  msgSource_t messageSource; // Where did this message come from
  uint16_t stringLength; // Length of the string
  uint8_t *stringPtr; // Pointer to string
} msg_stringMessage_t;

// == Message Data Structures ==
// NOTE: All message types named: data_<type of data>_t

// String data struct
typedef struct {
  msgType_t messageType;
  uint16_t stringLength;
  char *stringPtr;
} data_string_t;

// Co-ordinate data struct
typedef struct {
  msgType_t messageType;
  uint16_t x;
  uint16_t y;
  uint16_t z;
} data_coords_t;

// Command data struct
typedef struct {
  msgType_t messageType;
  msgCommand_t command;
} data_command_t;

// == Ring Buffer Typedefs ==
// Signals to send to the USARTInBufferTask from the interrupt
typedef enum {
  RBUF_SIG_READ,
  RBUF_SIG_UNREAD
} ringBuf_signal_t;

typedef enum {
  RBUF_STATUS_OK,
  RBUF_STATUS_FULL,
  RBUF_STATUS_EMPTY,
  RBUF_STATUS_ERROR
} ringBuf_status_t;

// Definition of an entry into the 
typedef struct {
  msgSource_t stringSource;
  uint16_t stringLength;
  uint8_t string[];
} ringBuf_entry_t;

// Definition of the global ring buffer info struct
typedef struct {
  ringBuf_entry_t **startPtr;
  ringBuf_entry_t **outPtr;
  ringBuf_entry_t **inPtr;
  uint8_t usedEntries;
} ringBuf_h;

// == Declarations ==
osPoolId genericMPool;
osPoolId strBufMPool;

// == Exported Variables ==
extern ringBuf_h ringBufHandle;

// == Function Prototypes ==
void sendMessage(osMessageQId msgQ, msgType_t type, msgSource_t source, uint8_t mRsp, void *data, uint32_t timeout);
void sendCommand(osMessageQId msgQ, msgSource_t source, msgCommand_t command, uint32_t timeout);
void fetchMessage(osMessageQId msgQ, msg_genericMessage_t *messagePtr, uint32_t timeout);
void *decodeMessage(msg_genericMessage_t *messagePtr, void *dataStruct);
msgCommand_t decodeCommand(msg_genericMessage_t *messagePtr);

ringBuf_entry_t *ringBuf_allocEntry(uint16_t stringLength);
void ringBuf_freeEntry(ringBuf_entry_t *ringBufEntryPtr);
ringBuf_status_t ringBuf_enqueue(ringBuf_entry_t *ringBufEntryPtr);
ringBuf_status_t ringBuf_dequeue(ringBuf_entry_t *ringBufEntryPtr);


#endif /*GENERICMESSAGING_LIB_H*/
