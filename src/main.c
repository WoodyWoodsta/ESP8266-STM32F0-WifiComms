#include "stm32f0xx.h"
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "wfi_uartESP8266Wifi_lib.h"
#include "srl_UARTUSBSerial_lib.h"

int main(int argc, char* argv[]) {

  wfi_ESP8266UARTInit();
  srl_UARTUSBSerialInit();
  int i = 0;

  srl_sendData("\rStartup complete!\r\n");

  while (1) {
    __WFI();
  }

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
