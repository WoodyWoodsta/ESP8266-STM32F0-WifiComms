/**
  * ============================================================================
  * File Name          : USARTInTask_task.c
  * Description        : USARTInTask Body
  * ============================================================================
  */

  // == Includes ==
#include "userTasks_task.h"

// == Function Declarations ==

// == Function Definitions ==
/**
* @brief USARTInTask
* @param argument
*/
void StartUSARTInTask(void const * argument) {

  // Strings to send
  const char commStateManualTxString[] = "MANUAL Mode Started\r\n";
  const char commStateAutoTxString[] = "AUTO Mode Started\r\n";

  // Strings to compare with
  const char led0ToggleRxString[] = "Toggle LED0";
  const char commStateManualRxString[] = "MANUAL";
  const char commStateAutoRxString[] = "AUTO";
  const char testATRxString[] = "Test AT";

  /* Infinite loop */
  for (;;) {
    osDelay(1);

  }
}
