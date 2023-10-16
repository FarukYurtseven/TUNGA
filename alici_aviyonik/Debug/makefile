################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
alici_aviyonik.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
alici_aviyonik.list \

OBJCOPY_BIN += \
alici_aviyonik.bin \


# All Target
all: alici_aviyonik.elf secondary-outputs

# Tool invocations
alici_aviyonik.elf: $(OBJS) $(USER_OBJS) C:\Users\Faruk\Desktop\roketsan\alici_aviyonik\STM32G431KBTX_FLASH.ld
	arm-none-eabi-gcc -o "alici_aviyonik.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Faruk\Desktop\roketsan\alici_aviyonik\STM32G431KBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="alici_aviyonik.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

alici_aviyonik.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "alici_aviyonik.list"
	@echo 'Finished building: $@'
	@echo ' '

alici_aviyonik.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "alici_aviyonik.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
