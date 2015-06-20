// == Includes ==
#include "srl_UARTUSBSerial_lib.h"
#include <string.h>
#include <stdio.h>
#include "stdarg.h"
#include "assert.h"
#include "stdlib.h"
#include <unistd.h>

// == Defines ==
#define BUFFER_SIZE 64

// == Static Function Prototypes ==
static uint32_t processInput(uint8_t *rx_buffer);

void srl_UARTUSBSerialInit(void) {
  // Disable buffering to prevent having to send a newline to flush
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // Clock to USART1
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  // Clock to GPIOA
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  // PA9 and PA10 to AF
  GPIOA->MODER |= GPIO_MODER_MODER9_1;
  GPIOA->MODER |= GPIO_MODER_MODER10_1;
  // Remap to correct AF
  GPIOA->AFR[1] |= (1 << (1*4)); // Remap pin 9 to AF1
  GPIOA->AFR[1] |= (1 << (2*4)); // Remap pin 10 to AF1

  // BRR = fclk / baud = fclk / 115200
  SystemCoreClockUpdate();
  USART1->BRR = SystemCoreClock/115200;
  USART1->CR1 |= USART_CR1_RE; // Receive enable
  USART1->CR1 |= USART_CR1_RXNEIE; // Receive not empty interrupt enable
  USART1->CR1 |= USART_CR1_TE; // Transmit enable
  USART1->CR1 |= USART_CR1_UE; // USART enable

  NVIC_EnableIRQ(USART1_IRQn); // Enable interrupt on USART
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
    printf("ERROR 3: buffer overrun\r\n");
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

  _writeUSART2(buf, n); // Write the string to USART2

  // Cleanup
  free(buf);
}

