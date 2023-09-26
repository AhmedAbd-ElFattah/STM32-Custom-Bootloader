################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/DAC.c 

OBJS += \
./STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/DAC.o 

C_DEPS += \
./STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/DAC.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/%.o STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/%.su STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/%.cyclo: ../STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/%.c STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/Image-Flasher/STM32-USART-Bootloader/STM32-Custom-Bootloader/STM32F407VG-Discovery-Board-Drivers" -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/Image-Flasher/STM32-USART-Bootloader/STM32-Custom-Bootloader/STM32-Custom-Bootloader/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-HMCAL-2f-DAC

clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-HMCAL-2f-DAC:
	-$(RM) ./STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/DAC.cyclo ./STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/DAC.d ./STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/DAC.o ./STM32F407VG-Discovery-Board-Drivers/HMCAL/DAC/DAC.su

.PHONY: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-HMCAL-2f-DAC

