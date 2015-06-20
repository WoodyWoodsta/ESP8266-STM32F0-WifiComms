
#include "stm32f0xx.h"
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

int main(int argc, char* argv[]) {

  wfi_ESP8266UARTInit();
  lcd_init();

  int i = 0;
  int j = 0;
  int8_t testInt = 125;
  int8_t testInt2 = 3;
  while (1) {
    wfi_sendData("Hello World - %i\r\n", j);
    for(i = 0; i < 10000000; i++);
    j++;
  }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
