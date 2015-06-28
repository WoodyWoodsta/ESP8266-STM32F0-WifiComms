#include "stm32f0xx.h"
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "wfi_uartESP8266Wifi_lib.h"
#include "srl_UARTUSBSerial_lib.h"

#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

int main(int argc, char* argv[]) {

  wfi_ESP8266UARTInit();
  srl_UARTUSBSerialInit();

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIOBInitStruct;
  GPIO_StructInit(&GPIOBInitStruct);
  GPIOBInitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIOBInitStruct.GPIO_OType = GPIO_OType_PP;
  GPIOBInitStruct.GPIO_Pin = GPIO_Pin_0 |
                              GPIO_Pin_1 |
                              GPIO_Pin_2 |
                              GPIO_Pin_3 |
                              GPIO_Pin_4 |
                              GPIO_Pin_5 |
                              GPIO_Pin_6 |
                              GPIO_Pin_7;
  GPIO_Init(GPIOB, &GPIOBInitStruct);

  int i = 0;

  srl_sendData("\rStartup complete!\r\n");

  while (1) {
    // If there is data in the global buffer, push it out and clear the buffer
    if(wfi_buffer) {
      srl_sendData("Wifi: %s\r\n", wfi_buffer);
      if(strcmp(wfi_buffer, "+IPD,0,7:LEDs ON") == 0) {
        GPIO_SetBits(GPIOB, GPIO_Pin_0 |
                            GPIO_Pin_1 |
                            GPIO_Pin_2 |
                            GPIO_Pin_3 |
                            GPIO_Pin_4 |
                            GPIO_Pin_5 |
                            GPIO_Pin_6 |
                            GPIO_Pin_7);
      } else if (strcmp(wfi_buffer, "+IPD,0,8:LEDs OFF") == 0) {
        GPIO_ResetBits(GPIOB, GPIO_Pin_0 |
                            GPIO_Pin_1 |
                            GPIO_Pin_2 |
                            GPIO_Pin_3 |
                            GPIO_Pin_4 |
                            GPIO_Pin_5 |
                            GPIO_Pin_6 |
                            GPIO_Pin_7);

      }
      free(wfi_buffer);
      wfi_buffer = NULL;
    }
  }

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
