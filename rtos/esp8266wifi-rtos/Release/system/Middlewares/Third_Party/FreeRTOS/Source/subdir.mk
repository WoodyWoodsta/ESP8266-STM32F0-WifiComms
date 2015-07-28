################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
../system/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
../system/Middlewares/Third_Party/FreeRTOS/Source/list.c \
../system/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
../system/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
../system/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

OBJS += \
./system/Middlewares/Third_Party/FreeRTOS/Source/croutine.o \
./system/Middlewares/Third_Party/FreeRTOS/Source/event_groups.o \
./system/Middlewares/Third_Party/FreeRTOS/Source/list.o \
./system/Middlewares/Third_Party/FreeRTOS/Source/queue.o \
./system/Middlewares/Third_Party/FreeRTOS/Source/tasks.o \
./system/Middlewares/Third_Party/FreeRTOS/Source/timers.o 

C_DEPS += \
./system/Middlewares/Third_Party/FreeRTOS/Source/croutine.d \
./system/Middlewares/Third_Party/FreeRTOS/Source/event_groups.d \
./system/Middlewares/Third_Party/FreeRTOS/Source/list.d \
./system/Middlewares/Third_Party/FreeRTOS/Source/queue.d \
./system/Middlewares/Third_Party/FreeRTOS/Source/tasks.d \
./system/Middlewares/Third_Party/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
system/Middlewares/Third_Party/FreeRTOS/Source/%.o: ../system/Middlewares/Third_Party/FreeRTOS/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F051x8 -DSTM32F051C6 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-stdperiph" -I/eps8266wifi-rtos/system/Drivers/CMSIS/Include -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\Drivers\CMSIS\Device\ST\STM32F0xx\Include" -I/eps8266wifi-rtos/system/Drivers/STM32F0xx_HAL_Driver/Inc -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/include -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\diag" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


