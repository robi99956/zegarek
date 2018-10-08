################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
X:/ARM_STM32/zegarek_justyny_V2/Src/system_stm32f0xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f0xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f0xx.o: X:/ARM_STM32/zegarek_justyny_V2/Src/system_stm32f0xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


