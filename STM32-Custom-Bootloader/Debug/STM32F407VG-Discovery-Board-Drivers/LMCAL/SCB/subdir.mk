################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/SCB.c 

OBJS += \
./STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/SCB.o 

C_DEPS += \
./STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/SCB.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/%.o STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/%.su STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/%.cyclo: ../STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/%.c STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/Image-Flasher/STM32-USART-Bootloader/STM32-Custom-Bootloader/STM32F407VG-Discovery-Board-Drivers" -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/Image-Flasher/STM32-USART-Bootloader/STM32-Custom-Bootloader/STM32-Custom-Bootloader/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LMCAL-2f-SCB

clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LMCAL-2f-SCB:
	-$(RM) ./STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/SCB.cyclo ./STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/SCB.d ./STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/SCB.o ./STM32F407VG-Discovery-Board-Drivers/LMCAL/SCB/SCB.su

.PHONY: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LMCAL-2f-SCB

