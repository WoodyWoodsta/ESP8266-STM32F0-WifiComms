
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

int main(int argc, char* argv[]) {

  wfi_ESP8266UARTInit();
  lcd_init();

  int i = 0;
  while (1) {
    printf("Hello World\r\n");
    for (i = 0; i < 100000000; i++);
  }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
