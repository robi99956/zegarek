################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/diskio.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/ff.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/option/syscall.c 

OBJS += \
./Middlewares/FatFs/diskio.o \
./Middlewares/FatFs/ff.o \
./Middlewares/FatFs/ff_gen_drv.o \
./Middlewares/FatFs/syscall.o 

C_DEPS += \
./Middlewares/FatFs/diskio.d \
./Middlewares/FatFs/ff.d \
./Middlewares/FatFs/ff_gen_drv.d \
./Middlewares/FatFs/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/diskio.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/diskio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FatFs/ff.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/ff.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FatFs/ff_gen_drv.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FatFs/syscall.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src/option/syscall.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


