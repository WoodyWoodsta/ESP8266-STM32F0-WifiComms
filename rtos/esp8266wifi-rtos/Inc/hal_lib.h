#ifndef HAL_LIB_H
#define HAL_LIB_H

#pragma once

// == Includes ==
#include "stm32f0xx_hal.h"

// == Prototypes ==
void SystemClock_Config(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_DMA_Init(void);
void MX_GPIO_Init(void);

#endif /* HAL_LIB_H */