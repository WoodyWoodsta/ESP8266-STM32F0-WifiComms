/**
  * ============================================================================
  * File Name          : hal_lib.h
  * Description        : Custom Hardware Abstraction header file
  * Authors            : Sean Wood
  *                      Adaptations from CMSIS-RTOS and the STM32Cube HAL
  * ============================================================================
  */

#ifndef HAL_LIB_H
#define HAL_LIB_H

#pragma once

// == Includes ==
#include "stm32f0xx_hal.h"

// == Defines ==
#define USART_DYNAMIC_BUFFER_INCREMENT 16

// == Exported Variables ==
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

// == Function Prototypes ==
void SystemClock_Config(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_DMA_Init(void);
void MX_GPIO_Init(void);
void cHAL_UART_IRQTermHandler(UART_HandleTypeDef *huart);
HAL_StatusTypeDef cUART_TermReceive_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef cHAL_USART_sTransmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t size);

// == Exported Function Prototypes ==
extern HAL_StatusTypeDef cHAL_UART_TermReceive_IT(UART_HandleTypeDef *huart, uint16_t MaxSize);

#endif /* HAL_LIB_H */