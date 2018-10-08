################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/WiFi/server.c \
../Application/User/WiFi/wifi.c \
../Application/User/WiFi/wifi_uart.c 

OBJS += \
./Application/User/WiFi/server.o \
./Application/User/WiFi/wifi.o \
./Application/User/WiFi/wifi_uart.o 

C_DEPS += \
./Application/User/WiFi/server.d \
./Application/User/WiFi/wifi.d \
./Application/User/WiFi/wifi_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/WiFi/%.o: ../Application/User/WiFi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


