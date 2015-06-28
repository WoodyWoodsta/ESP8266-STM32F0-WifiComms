#ifndef SRL_UARTUSBSERIAL_LIB_H
#define SRL_UARTUSBSERIAL_LIB_H

// == Includes ==
#include "stdint.h"
#include "stm32f0xx.h"

// == Defines ==
#define STM32F051

// == Declarations ==
void srl_UARTUSBSerialInit(void);
void srl_sendData(const char* format, ...);

#endif /* SRL_UARTUSBSERIAL_LIB_H */
