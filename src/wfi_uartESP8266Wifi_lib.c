// == Includes ==
#include "wfi_uartESP8266Wifi_lib.h"
#include "lcd_stm32f0.h"
#include <string.h>
#include <stdio.h>
#include "stdarg.h"
#include "assert.h"
#include "stdlib.h"
#include <unistd.h>
#include "diag/Trace.h" // For TRACE output support

// == Defines ==
#define BUFFER_SIZE 512

// == Static Function Prototypes ==
static uint32_t processInput(uint8_t *rx_buffer);

void wfi_ESP8266UARTInit(void) {
  // Disable buffering to prevent having to send a newline to flush
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // Clocks to USART2 and GPIOA
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  USART_DeInit(USART2); // For reset

  // PA2 and PA3 to AF1
  GPIO_InitTypeDef GPIOAUSART2InitStruct;
  GPIO_StructInit(&GPIOAUSART2InitStruct);
  GPIOAUSART2InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIOAUSART2InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_15;
  GPIOAUSART2InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIOAUSART2InitStruct);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_1);

  // BRR = fclk / baud = fclk / 115200
  SystemCoreClockUpdate();
  USART_InitTypeDef USART2InitStruct;
  USART_StructInit(&USART2InitStruct);
  USART2InitStruct.USART_BaudRate = 9600; // Set the baud
  USART2InitStruct.USART_WordLength = USART_WordLength_8b;
  USART2InitStruct.USART_StopBits = USART_StopBits_1;
  USART2InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // Transmit and receive enable
  USART_Init(USART2, &USART2InitStruct);

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // Enable "receive not empty" interrupt config
  USART_Cmd(USART2, ENABLE);

  NVIC_EnableIRQ(USART2_IRQn); // Enable interrupt on USART2
}

void USART2_IRQHandler(void) {
  static uint8_t rx_buffer[BUFFER_SIZE];
  static uint32_t buffer_pointer = 0;
  uint8_t dirtyByte = FALSE;

  // Check for and clear other interrupts
  ITStatus USART2OREFlag = USART_GetFlagStatus(USART2, USART_FLAG_ORE);
  ITStatus USART2FEFlag = USART_GetFlagStatus(USART2, USART_FLAG_FE);
  ITStatus USART2OREStatus = USART_GetITStatus(USART2, USART_IT_ORE);
  ITStatus USART2FEStatus = USART_GetITStatus(USART2, USART_IT_FE);
  uint32_t itReg = USART2->ISR;

  if ((USART2FEStatus == SET) || (USART2FEFlag == SET)) {
    USART_ClearFlag(USART2, USART_FLAG_FE);
    USART_ClearITPendingBit(USART2, USART_IT_FE);
    dirtyByte = TRUE;
  }

  if ((USART2OREStatus == SET) || (USART2OREFlag == SET)) {
    USART_ClearFlag(USART2, USART_FLAG_ORE);
    USART_ClearITPendingBit(USART2, USART_IT_ORE);
    dirtyByte = TRUE;
  }

  // Acknowledge the interrupt by reading the received data
  uint8_t received_char = USART2->RDR;
  if (!dirtyByte) { // Chuck away any junk (noise, it must be)
    srl_sendData("%c", received_char);
  }

//  if (received_char == '\r') { // "Enter"
//    rx_buffer[buffer_pointer] = 0; // Finalize the string by terminating it with a 0
//    buffer_pointer = 0; // Ready to buffer fresh string
//    processInput(rx_buffer);
//  } else { // New char arrived. Add it to the buffer
//    rx_buffer[buffer_pointer++] = (uint8_t)received_char;
//  }
//  // Check for impending overrun
//  if (buffer_pointer >= BUFFER_SIZE) {
//    srl_sendData("ERROR 3: buffer overrun\r\n");
//    buffer_pointer = 0;
//  }

//  static uint8_t rx_buffer[BUFFER_SIZE];
//  static uint32_t buffer_pointer = 0;
//
//  rx_buffer[buffer_pointer++] = received_char;
//
//  if (received_char == '\n') { // "Line feed"
//    rx_buffer[buffer_pointer] = 0; // Finalize the string by terminating it with a 0
//    if (!wfi_Buffer) { // If there is nothing in the buffer
//      wfi_Buffer = malloc(buffer_pointer+1); // Prep the memory
//      memcpy(wfi_Buffer, rx_buffer, buffer_pointer+1); // Copy across the buffer
//      *(wfi_Buffer + buffer_pointer + 1) = (char) 0; // Append null character to signify end of buffer
//      buffer_pointer = 0; // Ready to buffer fresh string
//    }
//  }
//
//  // Check for impending overrun
//  if (buffer_pointer >= BUFFER_SIZE) {
//    srl_sendData("ERROR 3: buffer overrun\r\n");
//    buffer_pointer = 0;
//    exit(1); // Kill the app if this occurs
//  }
}

static uint32_t processInput(uint8_t *rx_buffer) {
  uint8_t instruction[BUFFER_SIZE];

  srl_sendData("Wifi: %s\r\n", rx_buffer);

  return 0;
}

void wfi_sendData(const char* format, ...) {
  // Make use of the format list (variable arguments) to formulate the formatted string
  va_list va;
  va_start(va, format);
  int n = 0;
  n = vsnprintf(0, 0, format, va);
  va_end(va);
  va_start(va, format);
  char* buf = (char*) malloc(n + 1); // Prep memory
  vsnprintf(buf, n + 1, format, va); // Formulate
  va_end(va);

  _writeUSART2(buf, n); // Write the string to USART2

  // Cleanup
  free(buf);
}

