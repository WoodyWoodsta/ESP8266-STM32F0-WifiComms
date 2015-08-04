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
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_STD_PERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F051x8 -I../include/ -I../system/Drivers/CMSIS/Device/ST/STM32F0xx/Include/ -I../system/Drivers/STM32F0xx_HAL_Driver/Inc/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/include/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0/ -I../system/Drivers/CMSIS/Include/ -I../system -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


