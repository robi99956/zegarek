################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/USB_Device_Library/subdir.mk
-include Middlewares/FatFs/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/WiFi/subdir.mk
-include Application/User/WAV_player/subdir.mk
-include Application/User/Scheduler/subdir.mk
-include Application/User/RTC/subdir.mk
-include Application/User/Led/subdir.mk
-include Application/User/Flash_mem/subdir.mk
-include Application/User/subdir.mk
-include Application/SW4STM32/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: zegarek_justyny_V2.elf

# Tool invocations
zegarek_justyny_V2.elf: $(OBJS) $(USER_OBJS) ../STM32F072CBTx_FLASH.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -specs=nosys.specs -specs=nano.specs -T"../STM32F072CBTx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "zegarek_justyny_V2.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating hex and Printing size information:'
	arm-none-eabi-objcopy -O ihex "zegarek_justyny_V2.elf" "zegarek_justyny_V2.hex"
	arm-none-eabi-size "zegarek_justyny_V2.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
