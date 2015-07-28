################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c \
../system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.c 

OBJS += \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.o \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.o 

C_DEPS += \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.d \
./system/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart_ex.d 


# Each subdirectory must supply rules for building sources it contributes
system/Drivers/STM32F0xx_HAL_Driver/Src/%.o: ../system/Drivers/STM32F0xx_HAL_Driver/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F051x8 -DSTM32F051C6 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-stdperiph" -I/eps8266wifi-rtos/system/Drivers/CMSIS/Include -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\Drivers\CMSIS\Device\ST\STM32F0xx\Include" -I/eps8266wifi-rtos/system/Drivers/STM32F0xx_HAL_Driver/Inc -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/include -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\diag" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


