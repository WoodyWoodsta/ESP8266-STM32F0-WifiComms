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

  for (;;) {
    osDelay(1);
  }
}


// TODO: Consider moving this to genericMessaging_lib
void ringBufferInit(void) {
  // Malloc the required amount of memory for the ring buffer
  ringBufHandle.startPtr = pvPortMalloc(RBUF_BUFFER_SIZE);
  ringBufHandle.inPtr = ringBufHandle.startPtr;
  ringBufHandle.outPtr = ringBufHandle.startPtr;

  // Reset the used entries (buffer is empty)
  ringBufHandle.usedEntries = 0;

}
