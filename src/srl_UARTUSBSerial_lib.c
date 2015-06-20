// == Includes ==
#include "srl_UARTUSBSerial_lib.h"

#include <string.h>
#include <stdio.h>
#include "stdarg.h"
#include "assert.h"
#include "stdlib.h"
#include <unistd.h>

#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_gpio.h"

// == Defines ==
#define BUFFER_SIZE 64

// == Static Function Prototypes ==
static uint32_t processInput(uint8_t *rx_buffer);

void srl_UARTUSBSerialInit(void) {
  // Disable buffering to prevent having to send a newline to flush
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // Clocks to USART1 and GPIOA
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  // PA9 and PA10 to AF1
  GPIO_InitTypeDef GPIOAUSART1InitStruct;
  GPIO_StructInit(&GPIOAUSART1InitStruct);
  GPIOAUSART1InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIOAUSART1InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIOAUSART1InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIOAUSART1InitStruct);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

  // BRR = fclk / baud = fclk / 115200
  SystemCoreClockUpdate();
  USART_InitTypeDef USART1InitStruct;
  USART_StructInit(&USART1InitStruct);
  USART1InitStruct.USART_BaudRate = 115200; // Set the baud
  USART1InitStruct.USART_WordLength = USART_WordLength_8b;
  USART1InitStruct.USART_StopBits = USART_StopBits_1;
  USART1InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // Transmit and receive enable
  USART_Init(USART1, &USART1InitStruct);

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // Enable "receive not empty" interrupt config
  USART_Cmd(USART1, ENABLE);

  NVIC_EnableIRQ(USART1_IRQn); // Enable interrupt on USART1
}

void USART1_IRQHandler(void) {
  static uint8_t rx_buffer[BUFFER_SIZE];
  static uint32_t buffer_pointer = 0;

  // Acknowledge the interrupt by reading the received data
  uint8_t received_char = USART1->RDR;
  write(0, &received_char, 1);
  if (received_char == '\r') { // "Enter"
    write(0, "\n", 1);
    rx_buffer[buffer_pointer] = 0; // Finalize the string by terminating it with a 0
    buffer_pointer = 0; // Ready to buffer fresh string
    processInput(rx_buffer);
    write(0, "> ", 2);  // Ready for next command
  } else if (received_char == '\b') { // Backspace
    if (buffer_pointer > 0) {
      rx_buffer[--buffer_pointer] = 0; // clear the previous char
      write(0, " \b", 3); // Overwrite with space and then move back
    }
  }
  else { // New char arrived. Add it to the buffer
    rx_buffer[buffer_pointer++] = received_char;
  }
  // Check for impending overrun
  if (buffer_pointer >= BUFFER_SIZE) {
    srl_sendData("ERROR 3: buffer overrun\r\n");
    buffer_pointer = 0;
    write(0, "> ", 2);  // Ready for next command
  }
}

static uint32_t processInput(uint8_t *rx_buffer) {
  uint8_t instruction[BUFFER_SIZE];
  uint32_t opcode = 1;
  if (sscanf(rx_buffer, "%s", instruction) != 1) { // Redundant, but here if we want to make input strings more complex
    srl_sendData("ERROR 1: invalid command syntax: \"%s\"\r\n", rx_buffer);
    return -1;
  }

  if (strcmp("PING", instruction) == 0) { // Bounce back "PONG" for testing
    for (uint32_t i = 0; i < opcode; i++) {
      srl_sendData("PONG!\r\n");
    }
  } else {
    srl_sendData("ERROR 2: no such command: \"%s\"\r\n", rx_buffer); // Gobbledygook
  }
  return 0;
}

void srl_sendData(const char* format, ...) {
  // Make use of the format list (variable arguments) to formulate the formatted string
  va_list va;
  va_start(va, format);
  int n = 0;
  n = vsnprintf(0, 0, format, va);
  va_end(va);
  va_start(va, format);
  char* buf = (char*)malloc(n+1); // Prep memory
  vsnprintf(buf, n+1, format, va); // Formulate
  va_end(va);

  _writeUSART1(buf, n); // Write the string to USART1

  // Cleanup
  free(buf);
}

