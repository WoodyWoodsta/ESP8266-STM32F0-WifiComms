/**
  * ============================================================================
  * File Name          : hal_lib.c
  * Description        : Custom Hardware Abstraction Library adapted from
  *                      STM32Cube HAL
  * ============================================================================
  */

// == Includes ==
#include "hal_lib.h"
#include "userTasks_task.h"

// == Private Variables ==
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_tx;

// == Function Definitions ==

/**
* @brief System clock configuration
*/

void SystemClock_Config(void) {

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

/* USART1 init function */
void MX_USART1_UART_Init(void) {

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&huart1);

}

/**
* @brief USART2 (WIFI) Initialisation Function
*/
void MX_USART2_UART_Init(void) {

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&huart2);

}

/**
* @brief DMA controller clock Initialisation
*/
void MX_DMA_Init(void) {
  /* DMA controller clock enable */
  __DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

}

/**
* @brief GPIO Initialisation
* Configure pins as
* Analog
* Input
* Output
* EVENT_OUT
* EXTI
*/
void MX_GPIO_Init(void) {

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOF_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PA0 PA1 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
  PB4 PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
    | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

// == USART Receive via IT Custom Driver ==

/**
* @brief Receive data, in interrupt mode (non-blocking), up until a terminator
* @param huart: uart handle
* @param pData: pointer to data buffer
* @retval HAL status
*/
HAL_StatusTypeDef cHAL_UART_TermReceive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t MaxSize) {
  if ((huart->State == HAL_UART_STATE_READY) || (huart->State == HAL_UART_STATE_BUSY_TX)) {
    if (pData == NULL) {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(huart);

    huart->pRxBuffPtr = pData;
    huart->RxXferSize = MaxSize; // Maximum created buffer associated with pData pointer
    huart->RxXferCount = 0; // Use this to count how many characters are in current buffer

    /* Computation of UART mask to apply to RDR register */
    __HAL_UART_MASK_COMPUTATION(huart);

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    /* Check if a transmit process is ongoing or not */
    if (huart->State == HAL_UART_STATE_BUSY_TX) {
      huart->State = HAL_UART_STATE_BUSY_TX_RX;
    }
    else {
      huart->State = HAL_UART_STATE_BUSY_RX;
    }

    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_PE);

    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(huart, UART_IT_ERR);

    /* Process Unlocked */
    __HAL_UNLOCK(huart);

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);

    return HAL_OK;
  }
  else {
    return HAL_BUSY;
  }
}

/**
* @brief This function handles UART interrupt request for "Receive via IT" Custom Driver.
* @param huart: uart handle
* @retval None
*/
void cHAL_UART_IRQTermHandler(UART_HandleTypeDef *huart) {
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2 | GPIO_PIN_3);
  /* UART parity error interrupt occurred -------------------------------------*/
  if ((__HAL_UART_GET_IT(huart, UART_IT_PE) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_PE) != RESET)) {
    __HAL_UART_CLEAR_IT(huart, UART_CLEAR_PEF);

    huart->ErrorCode |= HAL_UART_ERROR_PE;
    /* Set the UART state ready to be able to start again the process */
    huart->State = HAL_UART_STATE_READY;
  }

  /* UART frame error interrupt occured --------------------------------------*/
  if ((__HAL_UART_GET_IT(huart, UART_IT_FE) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR) != RESET)) {
    __HAL_UART_CLEAR_IT(huart, UART_CLEAR_FEF);

    huart->ErrorCode |= HAL_UART_ERROR_FE;
    /* Set the UART state ready to be able to start again the process */
    huart->State = HAL_UART_STATE_READY;
  }

  /* UART noise error interrupt occured --------------------------------------*/
  if ((__HAL_UART_GET_IT(huart, UART_IT_NE) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR) != RESET)) {
    __HAL_UART_CLEAR_IT(huart, UART_CLEAR_NEF);

    huart->ErrorCode |= HAL_UART_ERROR_NE;
    /* Set the UART state ready to be able to start again the process */
    huart->State = HAL_UART_STATE_READY;
  }

  /* UART Over-Run interrupt occured -----------------------------------------*/
  if ((__HAL_UART_GET_IT(huart, UART_IT_ORE) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR) != RESET)) {
    __HAL_UART_CLEAR_IT(huart, UART_CLEAR_OREF);

    huart->ErrorCode |= HAL_UART_ERROR_ORE;
    /* Set the UART state ready to be able to start again the process */
    huart->State = HAL_UART_STATE_READY;
  }

  /* Call UART Error Call back function if need be --------------------------*/
  if (huart->ErrorCode != HAL_UART_ERROR_NONE) {
    HAL_UART_ErrorCallback(huart); // TODO Implement this
  }

#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
  /* UART wakeup from Stop mode interrupt occurred -------------------------------------*/
  if ((__HAL_UART_GET_IT(huart, UART_IT_WUF) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_WUF) != RESET)) {
    __HAL_UART_CLEAR_IT(huart, UART_CLEAR_WUF);
    /* Set the UART state ready to be able to start again the process */
    huart->State = HAL_UART_STATE_READY;
    HAL_UART_WakeupCallback(huart);
  }
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */

  /* UART in mode Receiver ---------------------------------------------------*/
  if ((__HAL_UART_GET_IT(huart, UART_IT_RXNE) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE) != RESET)) {
    HAL_StatusTypeDef status = cUART_TermReceive_IT(huart);
    /* Clear RXNE interrupt flag */
    __HAL_UART_SEND_REQ(huart, UART_RXDATA_FLUSH_REQUEST);
  }

  // Don't need these, TODO consider removing
  ///* UART in mode Transmitter ------------------------------------------------*/
  //if ((__HAL_UART_GET_IT(huart, UART_IT_TXE) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_TXE) != RESET)) {
  //  UART_Transmit_IT(huart);
  //}

  ///* UART in mode Transmitter ------------------------------------------------*/
  //if ((__HAL_UART_GET_IT(huart, UART_IT_TC) != RESET) && (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_TC) != RESET)) {
  //  UART_EndTransmit_IT(huart);
  //}
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2 | GPIO_PIN_3);

}

/**
* @brief Receive data, in interrupt mode (non-blocking), up until a terminator (data transfer)
*         Function called under interruption only, once
*         interruptions have been enabled by HAL_UART_Receive_IT()
* @param  huart: UART handle
* @retval HAL status
*/
HAL_StatusTypeDef cUART_TermReceive_IT(UART_HandleTypeDef *huart) {
  uint16_t* tmp;
  uint16_t uhMask = huart->Mask;
  uint16_t RxXferCount = huart->RxXferCount;

  if ((huart->State == HAL_UART_STATE_BUSY_RX) || (huart->State == HAL_UART_STATE_BUSY_TX_RX) || (huart->State == HAL_UART_STATE_READY)) {

    uint8_t inChar = (uint8_t)(huart->Instance->RDR & (uint8_t) uhMask);

    // If we have reached a <cr>, <lf> or NULL, or if we have reached the end of the buffer, send off a completed string
    if ((inChar == 0x0D) || (inChar == 0x0A) || (inChar == 0x00) || (RxXferCount >= huart->RxXferSize)) {

      // If the string is not empty, fire the receive complete callback
      if (RxXferCount != 0) {
        HAL_UART_RxCpltCallback(huart);
      }

      huart->RxXferCount = 0; // Reset string count

      return HAL_OK;
    }

    huart->pRxBuffPtr[RxXferCount] = (uint8_t) inChar;
    huart->RxXferCount = ++RxXferCount; // Update the receive count

    return HAL_OK;
  }
  else {
    return HAL_BUSY;
  }
}

/**
* @brief USART callback on receiving a completed string (terminated)
* @param huart: UART handle
*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  msg_StringMessage_t *inString;
  inString = msgStringStructAlloc(msgPoolUSARTIn, huart->RxXferCount, huart->pRxBuffPtr); // Formulate the message

  // Determine the string source
  if (huart->Instance == USART1_BASE) {
    inString->messageSource = MSG_SRC_USB;
  }
  else if (huart->Instance == USART2_BASE) {
    inString->messageSource = MSG_SRC_WIFI;
  }

  // Send the string, do not wait for timeout since we are in an interrupt
  osMessagePut(msgQUSARTIn, (uint32_t) inString, 0);
}
