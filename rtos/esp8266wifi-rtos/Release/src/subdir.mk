################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/USARTInTask_task.c \
../src/USARTOutTask_task.c \
../src/bossTask_task.c \
../src/freertos.c \
../src/genericMessaging_lib.c \
../src/hal_lib.c \
../src/main.c \
../src/stm32f0xx_hal_msp.c \
../src/stm32f0xx_it.c \
../src/strings_res.c \
../src/userTasks_task.c 

OBJS += \
./src/USARTInTask_task.o \
./src/USARTOutTask_task.o \
./src/bossTask_task.o \
./src/freertos.o \
./src/genericMessaging_lib.o \
./src/hal_lib.o \
./src/main.o \
./src/stm32f0xx_hal_msp.o \
./src/stm32f0xx_it.o \
./src/strings_res.o \
./src/userTasks_task.o 

C_DEPS += \
./src/USARTInTask_task.d \
./src/USARTOutTask_task.d \
./src/bossTask_task.d \
./src/freertos.d \
./src/genericMessaging_lib.d \
./src/hal_lib.d \
./src/main.d \
./src/stm32f0xx_hal_msp.d \
./src/stm32f0xx_it.d \
./src/strings_res.d \
./src/userTasks_task.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F051x8 -DSTM32F051C6 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-stdperiph" -I/eps8266wifi-rtos/system/Drivers/CMSIS/Include -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\Drivers\CMSIS\Device\ST\STM32F0xx\Include" -I/eps8266wifi-rtos/system/Drivers/STM32F0xx_HAL_Driver/Inc -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/include -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\diag" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


