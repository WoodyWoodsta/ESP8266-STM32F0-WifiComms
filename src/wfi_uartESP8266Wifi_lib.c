// == Includes ==
#include "wfi_uartESP8266Wifi_lib.h"
#include "lcd_stm32f0.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "diag/Trace.h" // For TRACE output support
//#include "gpio.h"
//#include "timing.h"

// == Defines ==
#define BUFFER_SIZE 64

// == Static Function Prototypes ==
static uint32_t processCommand(uint8_t *rx_buffer);

void wfi_ESP8266UARTInit(void) {
  // disable buffering to prevent having to send a newline to flush
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // clock to USART1
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  // clock to GPIOA
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  // PA9 and PA10 to AF
  GPIOA->MODER |= GPIO_MODER_MODER9_1;
  GPIOA->MODER |= GPIO_MODER_MODER10_1;
  // remap to correct AF
  GPIOA->AFR[1] |= (1 << (1*4)); // remap pin 9 to AF1
  GPIOA->AFR[1] |= (1 << (2*4)); // remap pin 10 to AF1

  // BRR = fclk / baud = fclk / 115200
  SystemCoreClockUpdate();
  USART1->BRR = SystemCoreClock/115200;
  USART1->CR1 |= USART_CR1_RE; // receive enable
  USART1->CR1 |= USART_CR1_RXNEIE; // receive not empty interrupt enable
  USART1->CR1 |= USART_CR1_TE; // transmit enable
  USART1->CR1 |= USART_CR1_UE; // usart enable

  NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void) { // May not need this function
  static uint8_t rx_buffer[BUFFER_SIZE];
  static uint32_t buffer_pointer = 0;

  // ack the interrput by reading the received data
  uint8_t received_char = USART1->RDR;
  write(0, &received_char, 1);
  if (received_char == '\r') { //"Enter"
    write(0, "\n", 1);
    rx_buffer[buffer_pointer] = 0; // finalise the string by terminating it with a 0
    buffer_pointer = 0; // ready to buffer fresh string
    processCommand(rx_buffer);
    write(0, "> ", 2);  // ready for next command
  } else if (received_char == '\b') { //backspac
    if (buffer_pointer > 0) {
      rx_buffer[--buffer_pointer] = 0; // clear the previous char
      write(0, " \b", 3); // overwrite with space and then move back
    }
  }
  else { // new char arrived. Add it to the buffer
    rx_buffer[buffer_pointer++] = received_char;
  }
  // check for impending overrun
  if (buffer_pointer >= BUFFER_SIZE) {
    printf("ERROR 3: buffer overrun\r\n");
    buffer_pointer = 0;
    write(0, "> ", 2);  // ready for next command
  }
}

static uint32_t processCommand(uint8_t *rx_buffer) {
  uint8_t instruction[BUFFER_SIZE];
  uint32_t opcode = 1;
  lcd_two_line_write("Serial Input:",rx_buffer);
//  if (sscanf(rx_buffer, "%s %i %i", instruction, &opcode) != 2) {
  if (sscanf(rx_buffer, "%s", instruction) != 1) {
    printf("ERROR 1: invalid command syntax: \"%s\"\r\n", rx_buffer);
    return -1;
  }
  if (strcmp("PING", instruction) == 0) {
    for (uint32_t i = 0; i < opcode; i++) {
      printf("PONG!\r\n");
    }
  }
  else if (strcmp("GPIO_READ", instruction) == 0) {
    printf("You said GPIO_READ!\r\n");
  }
  else if (strcmp("GPIO_SET", instruction) == 0) {
    printf("You said GPIO_SET!\r\n");
  }
  else if (strcmp("GPIO_CLEAR", instruction) == 0) {
    printf("You said GPIO_CLEAR!\r\n");
  }
  else if (strcmp("GPIO_HIGHZ", instruction) == 0) {
    printf("You said GPIO_HIGHZ!\r\n");
  }
  else if (strcmp("PATTERN_TIMING", instruction) == 0) {
    printf("You said PATTERN_TIMING!\r\n");
  }
  else if (strcmp("NRST", instruction) == 0) {
    printf("You said NSRT!\r\n");
  } else {
    printf("ERROR 2: no such command: \"%s\"\r\n", rx_buffer);
  }
  return 0;
}

