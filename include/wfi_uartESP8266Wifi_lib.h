#ifndef WFI_UARTESP8266WIFI_LIB_H
#define WFI_UARTESP8266WIFI_LIB_H

// == Includes ==
#include "stdint.h"
#include "stm32f0xx.h"
#include "srl_UARTUSBSerial_lib.h"

// == Defines ==
#define STM32F051

// == Declarations ==
void wfi_ESP8266UARTInit(void);
void wfi_sendData(const char* format, ...);

#endif /* WFI_UARTESP8266WIFI_LIB_H */
