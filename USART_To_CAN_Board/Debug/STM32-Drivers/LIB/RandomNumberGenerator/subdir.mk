################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32-Drivers/LIB/RandomNumberGenerator/RNG.c 

OBJS += \
./STM32-Drivers/LIB/RandomNumberGenerator/RNG.o 

C_DEPS += \
./STM32-Drivers/LIB/RandomNumberGenerator/RNG.d 


# Each subdirectory must supply rules for building sources it contributes
STM32-Drivers/LIB/RandomNumberGenerator/%.o STM32-Drivers/LIB/RandomNumberGenerator/%.su STM32-Drivers/LIB/RandomNumberGenerator/%.cyclo: ../STM32-Drivers/LIB/RandomNumberGenerator/%.c STM32-Drivers/LIB/RandomNumberGenerator/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/ahmed/Desktop/Github/STM32-Custom-Bootloader/USART_To_CAN_Board/STM32_Drivers_Configurations" -I"/home/ahmed/Desktop/Github/STM32-Custom-Bootloader/USART_To_CAN_Board/STM32-Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32-2d-Drivers-2f-LIB-2f-RandomNumberGenerator

clean-STM32-2d-Drivers-2f-LIB-2f-RandomNumberGenerator:
	-$(RM) ./STM32-Drivers/LIB/RandomNumberGenerator/RNG.cyclo ./STM32-Drivers/LIB/RandomNumberGenerator/RNG.d ./STM32-Drivers/LIB/RandomNumberGenerator/RNG.o ./STM32-Drivers/LIB/RandomNumberGenerator/RNG.su

.PHONY: clean-STM32-2d-Drivers-2f-LIB-2f-RandomNumberGenerator
