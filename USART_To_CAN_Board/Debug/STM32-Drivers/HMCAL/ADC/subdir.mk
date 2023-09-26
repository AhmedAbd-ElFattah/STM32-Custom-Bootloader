################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32-Drivers/HMCAL/ADC/ADC.c 

OBJS += \
./STM32-Drivers/HMCAL/ADC/ADC.o 

C_DEPS += \
./STM32-Drivers/HMCAL/ADC/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
STM32-Drivers/HMCAL/ADC/%.o STM32-Drivers/HMCAL/ADC/%.su STM32-Drivers/HMCAL/ADC/%.cyclo: ../STM32-Drivers/HMCAL/ADC/%.c STM32-Drivers/HMCAL/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/ahmed/Desktop/Github/STM32-Custom-Bootloader/USART_To_CAN_Board/STM32_Drivers_Configurations" -I"/home/ahmed/Desktop/Github/STM32-Custom-Bootloader/USART_To_CAN_Board/STM32-Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32-2d-Drivers-2f-HMCAL-2f-ADC

clean-STM32-2d-Drivers-2f-HMCAL-2f-ADC:
	-$(RM) ./STM32-Drivers/HMCAL/ADC/ADC.cyclo ./STM32-Drivers/HMCAL/ADC/ADC.d ./STM32-Drivers/HMCAL/ADC/ADC.o ./STM32-Drivers/HMCAL/ADC/ADC.su

.PHONY: clean-STM32-2d-Drivers-2f-HMCAL-2f-ADC

