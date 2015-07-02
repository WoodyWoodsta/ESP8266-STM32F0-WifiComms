#ifndef USERTASKS_TASK_H
#define USERTASKS_TASK_H

// == Includes ==
#include "cmsis_os.h"
#include "hal_lib.h"

// == Exported Variables ==
extern osThreadId defaultTaskHandle;
extern osThreadId USARTInTaskHandle;
extern osThreadId USARTOutTaskHandle;

// == Function Prototypes ==
void StartDefaultTask(void const * argument);
void StartUSARTInTask(void const * argument);
void StartUSARTOutTask(void const * argument);

#endif /*USERTASKS_TASK_H*/