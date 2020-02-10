################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Applications.c \
../HwPWM.c \
../SPI.c \
../SwICU.c \
../UART.c \
../dcMotor.c \
../gpio.c \
../led.c \
../pushButton.c \
../sevenSeg.c \
../softwareDelay.c \
../timers.c 

OBJS += \
./Applications.o \
./HwPWM.o \
./SPI.o \
./SwICU.o \
./UART.o \
./dcMotor.o \
./gpio.o \
./led.o \
./pushButton.o \
./sevenSeg.o \
./softwareDelay.o \
./timers.o 

C_DEPS += \
./Applications.d \
./HwPWM.d \
./SPI.d \
./SwICU.d \
./UART.d \
./dcMotor.d \
./gpio.d \
./led.d \
./pushButton.d \
./sevenSeg.d \
./softwareDelay.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


