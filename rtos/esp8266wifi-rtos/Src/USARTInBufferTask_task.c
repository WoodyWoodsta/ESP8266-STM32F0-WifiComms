/**
  * ============================================================================
  * File Name          : USARTInBufferTask_task.c
  * Description        : USARTInBufferTask Body
  * ============================================================================
  */

// == Includes ==
#include "userTasks_task.h"

// == Function Declarations ==
void ringBufferInit(void);

// == Function Definitions ==
/**
* @brief USARTInBufferTask
* @param argument
*/
void StartUSARTInBufferTask(void const * argument) {
  ringBufferInit();
  ringBuf_entry_t *ringBufRxEntryPtr;

  for (;;) {
    // Wait forever for the unread ring buffer entries signal
    osEvent sigRxEvent = osSignalWait(RBUF_SIG_UNREAD, osWaitForever);

    if (sigRxEvent.status == osEventSignal) {
      // Grab the pointer to the new entry
      ringBuf_status_t status = ringBuf_dequeue(&ringBufRxEntryPtr); // TODO: This call does not necessarily protect against stomping

      if (status == RBUF_STATUS_OK) {
        //HAL_StatusTypeDef status = cHAL_USART_sTransmit_DMA(&huart1, ringBufRxEntryPtr->string, ringBufRxEntryPtr->stringLength);
        //if (status != HAL_OK) {
        //  ringBuf_freeEntry(ringBufRxEntryPtr);
        //}

        // Allocate memory for the string message
        msg_stringMessage_t *txMessagePtr = osPoolAlloc(strBufMPool);

        // Fill the string message struct
        txMessagePtr->messageSource = ringBufRxEntryPtr->stringSource;
        txMessagePtr->stringLength = ringBufRxEntryPtr->stringLength;
        txMessagePtr->stringPtr = (uint8_t *) ringBufRxEntryPtr->string;

        // Send the message to USARTInTask
        osStatus status = osMessagePut(msgQUSARTIn, (uint32_t) txMessagePtr, 0);

        // If the message did not send, free the memories
        if (status != osOK) {
          ringBuf_freeEntry(ringBufRxEntryPtr);
          osPoolFree(strBufMPool, txMessagePtr);
        }
      }
    }
  }
}


// TODO: Consider moving this to genericMessaging_lib
void ringBufferInit(void) {
  // Reset the ring buffer handle
  ringBufHandle.inPos = 0;
  ringBufHandle.outPos = 0;
  ringBufHandle.usedEntries = 0;

}
