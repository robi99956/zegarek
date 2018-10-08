################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_bot.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_data.c \
X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_scsi.c 

OBJS += \
./Middlewares/USB_Device_Library/usbd_core.o \
./Middlewares/USB_Device_Library/usbd_ctlreq.o \
./Middlewares/USB_Device_Library/usbd_ioreq.o \
./Middlewares/USB_Device_Library/usbd_msc.o \
./Middlewares/USB_Device_Library/usbd_msc_bot.o \
./Middlewares/USB_Device_Library/usbd_msc_data.o \
./Middlewares/USB_Device_Library/usbd_msc_scsi.o 

C_DEPS += \
./Middlewares/USB_Device_Library/usbd_core.d \
./Middlewares/USB_Device_Library/usbd_ctlreq.d \
./Middlewares/USB_Device_Library/usbd_ioreq.d \
./Middlewares/USB_Device_Library/usbd_msc.d \
./Middlewares/USB_Device_Library/usbd_msc_bot.d \
./Middlewares/USB_Device_Library/usbd_msc_data.d \
./Middlewares/USB_Device_Library/usbd_msc_scsi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/USB_Device_Library/usbd_core.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_ctlreq.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_ioreq.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_msc.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_msc_bot.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_bot.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_msc_data.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_data.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/USB_Device_Library/usbd_msc_scsi.o: X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_scsi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F072xB -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Drivers/CMSIS/Include" -I"X:/ARM_STM32/zegarek_justyny_V2/Inc" -I"X:/ARM_STM32/zegarek_justyny_V2/Middlewares/Third_Party/FatFs/src"  -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


