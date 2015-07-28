################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c 

OBJS += \
./system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.o 

C_DEPS += \
./system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.d 


# Each subdirectory must supply rules for building sources it contributes
system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/%.o: ../system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DSTM32F051 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F051x8 -DSTM32F051C6 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-stdperiph" -I/eps8266wifi-rtos/system/Drivers/CMSIS/Include -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\Drivers\CMSIS\Device\ST\STM32F0xx\Include" -I/eps8266wifi-rtos/system/Drivers/STM32F0xx_HAL_Driver/Inc -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/include -I/eps8266wifi-rtos/system/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I"D:\_EmbeddedDev\Projects\ESP8266-STM32F0-WifiComms\rtos\esp8266wifi-rtos\system\diag" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


