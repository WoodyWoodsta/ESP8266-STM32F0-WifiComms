
// == Includes ==
#include "userTasks_task.h"

// == Function Definitions ==
void StartUSARTOutTask(void const * argument) {

  /* Infinite loop */
  for (;;) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
    osDelay(350);
  }
}
