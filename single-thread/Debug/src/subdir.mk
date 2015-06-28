################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_write.c \
../src/lcd_stm32f0.c \
../src/main.c \
../src/srl_UARTUSBSerial_lib.c \
../src/syscalls.c \
../src/wfi_uartESP8266Wifi_lib.c 

OBJS += \
./src/_write.o \
./src/lcd_stm32f0.o \
./src/main.o \
./src/srl_UARTUSBSerial_lib.o \
./src/syscalls.o \
./src/wfi_uartESP8266Wifi_lib.o 

C_DEPS += \
./src/_write.d \
./src/lcd_stm32f0.d \
./src/main.d \
./src/srl_UARTUSBSerial_lib.d \
./src/syscalls.d \
./src/wfi_uartESP8266Wifi_lib.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


