################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/Keypad.c 

OBJS += \
./STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/Keypad.o 

C_DEPS += \
./STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/Keypad.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/%.o STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/%.su STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/%.cyclo: ../STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/%.c STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/Image-Flasher/STM32-USART-Bootloader/STM32-Custom-Bootloader/STM32F407VG-Discovery-Board-Drivers" -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/Image-Flasher/STM32-USART-Bootloader/STM32-Custom-Bootloader/STM32-Custom-Bootloader/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-HAL-2f-Keypad

clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-HAL-2f-Keypad:
	-$(RM) ./STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/Keypad.cyclo ./STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/Keypad.d ./STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/Keypad.o ./STM32F407VG-Discovery-Board-Drivers/HAL/Keypad/Keypad.su

.PHONY: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-HAL-2f-Keypad

