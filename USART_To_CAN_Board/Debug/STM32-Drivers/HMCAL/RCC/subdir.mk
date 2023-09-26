################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32-Drivers/HMCAL/RCC/RCC.c 

OBJS += \
./STM32-Drivers/HMCAL/RCC/RCC.o 

C_DEPS += \
./STM32-Drivers/HMCAL/RCC/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
STM32-Drivers/HMCAL/RCC/%.o STM32-Drivers/HMCAL/RCC/%.su STM32-Drivers/HMCAL/RCC/%.cyclo: ../STM32-Drivers/HMCAL/RCC/%.c STM32-Drivers/HMCAL/RCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/ahmed/Desktop/Github/STM32-Custom-Bootloader/USART_To_CAN_Board/STM32_Drivers_Configurations" -I"/home/ahmed/Desktop/Github/STM32-Custom-Bootloader/USART_To_CAN_Board/STM32-Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32-2d-Drivers-2f-HMCAL-2f-RCC

clean-STM32-2d-Drivers-2f-HMCAL-2f-RCC:
	-$(RM) ./STM32-Drivers/HMCAL/RCC/RCC.cyclo ./STM32-Drivers/HMCAL/RCC/RCC.d ./STM32-Drivers/HMCAL/RCC/RCC.o ./STM32-Drivers/HMCAL/RCC/RCC.su

.PHONY: clean-STM32-2d-Drivers-2f-HMCAL-2f-RCC

