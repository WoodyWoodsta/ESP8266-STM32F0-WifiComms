
// == Includes ==
#include "userTasks_task.h"

// == Function Definitions ==
void StartUSARTInTask(void const * argument) {

  /* Infinite loop */
  for (;;) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
    osDelay(150);
  }
}
