################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Buzzer.c \
../Core/Src/DAC.c \
../Core/Src/EEPROM.c \
../Core/Src/IR.c \
../Core/Src/LED.c \
../Core/Src/LIS3DH.c \
../Core/Src/LMT86.c \
../Core/Src/LTR_329ALS.c \
../Core/Src/POTENTIOMETER.c \
../Core/Src/UART.c \
../Core/Src/main.c \
../Core/Src/shtc3RH.c \
../Core/Src/shtc3temperature.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c 

OBJS += \
./Core/Src/Buzzer.o \
./Core/Src/DAC.o \
./Core/Src/EEPROM.o \
./Core/Src/IR.o \
./Core/Src/LED.o \
./Core/Src/LIS3DH.o \
./Core/Src/LMT86.o \
./Core/Src/LTR_329ALS.o \
./Core/Src/POTENTIOMETER.o \
./Core/Src/UART.o \
./Core/Src/main.o \
./Core/Src/shtc3RH.o \
./Core/Src/shtc3temperature.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o 

C_DEPS += \
./Core/Src/Buzzer.d \
./Core/Src/DAC.d \
./Core/Src/EEPROM.d \
./Core/Src/IR.d \
./Core/Src/LED.d \
./Core/Src/LIS3DH.d \
./Core/Src/LMT86.d \
./Core/Src/LTR_329ALS.d \
./Core/Src/POTENTIOMETER.d \
./Core/Src/UART.d \
./Core/Src/main.d \
./Core/Src/shtc3RH.d \
./Core/Src/shtc3temperature.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I"C:/Users/puneeth/Desktop/Documents for Hackaton team/Full Project - Copy (5)/Drivers/Atwinc/inc" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Buzzer.d ./Core/Src/Buzzer.o ./Core/Src/Buzzer.su ./Core/Src/DAC.d ./Core/Src/DAC.o ./Core/Src/DAC.su ./Core/Src/EEPROM.d ./Core/Src/EEPROM.o ./Core/Src/EEPROM.su ./Core/Src/IR.d ./Core/Src/IR.o ./Core/Src/IR.su ./Core/Src/LED.d ./Core/Src/LED.o ./Core/Src/LED.su ./Core/Src/LIS3DH.d ./Core/Src/LIS3DH.o ./Core/Src/LIS3DH.su ./Core/Src/LMT86.d ./Core/Src/LMT86.o ./Core/Src/LMT86.su ./Core/Src/LTR_329ALS.d ./Core/Src/LTR_329ALS.o ./Core/Src/LTR_329ALS.su ./Core/Src/POTENTIOMETER.d ./Core/Src/POTENTIOMETER.o ./Core/Src/POTENTIOMETER.su ./Core/Src/UART.d ./Core/Src/UART.o ./Core/Src/UART.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/shtc3RH.d ./Core/Src/shtc3RH.o ./Core/Src/shtc3RH.su ./Core/Src/shtc3temperature.d ./Core/Src/shtc3temperature.o ./Core/Src/shtc3temperature.su ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su

.PHONY: clean-Core-2f-Src

