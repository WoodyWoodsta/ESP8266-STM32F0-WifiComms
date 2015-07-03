
// == Includes ==
#include "userTasks_task.h"

// == Function Definitions ==
void StartDefaultTask(void const * argument) {
  uint8_t *UART1InBuff = pvPortMalloc(128); // Prep the memory
  cHAL_UART_TermReceive_IT(&huart1, UART1InBuff, 128);

  /* Infinite loop */
  for (;;) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    osDelay(50);
  }
}
