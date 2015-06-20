#ifndef WFI_UARTESP8266WIFI_LIB_H
#define WFI_UARTESP8266WIFI_LIB_H

// == Includes ==
#include "stdint.h"
#include "stm32f0xx.h"

// == Defines ==
#define STM32F051

// == Declarations ==
// initialises the USART and enable the incomming char interupt
void wfi_ESP8266UARTInit(void);

#endif /* WFI_UARTESP8266WIFI_LIB_H */
