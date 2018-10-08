################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
X:/ARM_STM32/zegarek_justyny_V2/Src/fatfs.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/main.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/stm32f0xx_hal_msp.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/stm32f0xx_it.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/usb_device.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/usbd_conf.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/usbd_desc.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/usbd_storage_if.c \
X:/ARM_STM32/zegarek_justyny_V2/Src/user_diskio.c 

OBJS += \
./Application/User/fatfs.o \
./Application/User/main.o \
./Application/User/stm32f0xx_hal_msp.o \
./Application/User/stm32f0xx_it.o \
./Application/User/usb_device.o \
./Application/User/usbd_conf.o \
./Application/User/usbd_desc.o \
./Application/User/usbd_storage_if.o \
./Application/User/user_diskio.o 

C_DEPS += \
./Application/User/fatfs.d \
./Application/User/main.d \
./Application/User/stm32f0xx_hal_msp.d \
./Application/User/stm32f0xx_it.d \
./Application/User/usb_device.d \
./Application/User/usbd_conf.d \
./Application/User/usbd_desc.d \
./Application/User/usbd_storage_if.d \
./Application/User/user_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/fatfs.o: X:/ARM_STM32/zegarek_justyny_V2/Src/fatfs.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: X:/ARM_STM32/zegarek_justyny_V2/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f0xx_hal_msp.o: X:/ARM_STM32/zegarek_justyny_V2/Src/stm32f0xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f0xx_it.o: X:/ARM_STM32/zegarek_justyny_V2/Src/stm32f0xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usb_device.o: X:/ARM_STM32/zegarek_justyny_V2/Src/usb_device.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_conf.o: X:/ARM_STM32/zegarek_justyny_V2/Src/usbd_conf.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_desc.o: X:/ARM_STM32/zegarek_justyny_V2/Src/usbd_desc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_storage_if.o: X:/ARM_STM32/zegarek_justyny_V2/Src/usbd_storage_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/user_diskio.o: X:/ARM_STM32/zegarek_justyny_V2/Src/user_diskio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


