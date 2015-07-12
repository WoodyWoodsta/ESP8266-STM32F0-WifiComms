/**
  * ============================================================================
  * File Name          : main.c
  * Description        : Main program body
  * ============================================================================
  *
  * Modified by Team 13
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  * ============================================================================
  */

// == Includes ==
#include "hal_lib.h"
#include "cmsis_os.h"
#include "userTasks_task.h"

// == Message Pools and Queues ==
// Global generic message and string message pool definitions
osPoolDef(genericMPool, GLOBAL_MESSAGE_MPOOL_SIZE, msg_genericMessage_t);
osPoolDef(strBufMPool, STRING_BUFFER_MPOOL_SIZE, msg_stringMessage_t);

// USART In Task String Queue
osMessageQDef(msgQUSARTIn, 5, msg_stringMessage_t);

// USART Out Task Message Queue
osMessageQDef(msgQUSARTOut, 2, msg_genericMessage_t);

// Boss Task Command Queue
osMessageQDef(msgQBoss, 5, msg_genericMessage_t);


// == Function Definitions ==
int main(void) {

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  osThreadDef(bossTask, StartBossTask, osPriorityNormal, 0, 128);
  bossTaskHandle = osThreadCreate(osThread(bossTask), NULL);

  osThreadDef(USARTInTask, StartUSARTInTask, osPriorityNormal, 0, 128);
  USARTInTaskHandle = osThreadCreate(osThread(USARTInTask), NULL);

  osThreadDef(USARTOutTask, StartUSARTOutTask, osPriorityNormal, 0, 128);
  USARTOutTaskHandle = osThreadCreate(osThread(USARTOutTask), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  // Generic messaging and string message memory pools
  genericMPool = osPoolCreate(osPool(genericMPool));
  strBufMPool = osPoolCreate(osPool(strBufMPool));

  // USART In Task String Queue
  msgQUSARTIn = osMessageCreate(osMessageQ(msgQUSARTIn), NULL);
  
  // USART Out Task Queue
  msgQUSARTOut = osMessageCreate(osMessageQ(msgQUSARTOut), NULL);

  // Boss Task Command Queue
  msgQBoss = osMessageCreate(osMessageQ(msgQBoss), NULL);
  
  /* USER CODE END RTOS_QUEUES */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  while (1) {
  }

}


#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

  /**
    * @}
  */

  /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
