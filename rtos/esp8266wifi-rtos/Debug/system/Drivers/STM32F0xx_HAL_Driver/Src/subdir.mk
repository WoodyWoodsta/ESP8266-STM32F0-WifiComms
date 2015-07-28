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
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F051x8 -DSTM32F051C6 -I../include/ -I../system/Drivers/CMSIS/Device/ST/STM32F0xx/Include/ -I../system/Drivers/STM32F0xx_HAL_Driver/Inc/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/include/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0/ -I../system/Drivers/CMSIS/Include/ -I../system -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


