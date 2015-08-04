################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/diag/Trace.c \
../system/diag/trace_impl.c 

OBJS += \
./system/diag/Trace.o \
./system/diag/trace_impl.o 

C_DEPS += \
./system/diag/Trace.d \
./system/diag/trace_impl.d 


# Each subdirectory must supply rules for building sources it contributes
system/diag/%.o: ../system/diag/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_STD_PERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F051x8 -I../include/ -I../system/Drivers/CMSIS/Device/ST/STM32F0xx/Include/ -I../system/Drivers/STM32F0xx_HAL_Driver/Inc/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/include/ -I../system/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0/ -I../system/Drivers/CMSIS/Include/ -I../system -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


