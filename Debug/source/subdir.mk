################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/DemoInfo1.c \
../source/L2.Adc.c \
../source/L2.Bme280.c \
../source/L2.Clock.c \
../source/L2.Ctimer.c \
../source/L2.Dac.c \
../source/L2.Debug.Console.c \
../source/L2.Flash.c \
../source/L2.Gpio.c \
../source/L2.Pwm.c \
../source/L2.Spi.c \
../source/L2.SysTick.c \
../source/L2.Usart.c \
../source/L3.BH1750.c \
../source/L3.Bme280.spi.c \
../source/L3.json.parse.c \
../source/L4.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/DemoInfo1.o \
./source/L2.Adc.o \
./source/L2.Bme280.o \
./source/L2.Clock.o \
./source/L2.Ctimer.o \
./source/L2.Dac.o \
./source/L2.Debug.Console.o \
./source/L2.Flash.o \
./source/L2.Gpio.o \
./source/L2.Pwm.o \
./source/L2.Spi.o \
./source/L2.SysTick.o \
./source/L2.Usart.o \
./source/L3.BH1750.o \
./source/L3.Bme280.spi.o \
./source/L3.json.parse.o \
./source/L4.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/DemoInfo1.d \
./source/L2.Adc.d \
./source/L2.Bme280.d \
./source/L2.Clock.d \
./source/L2.Ctimer.d \
./source/L2.Dac.d \
./source/L2.Debug.Console.d \
./source/L2.Flash.d \
./source/L2.Gpio.d \
./source/L2.Pwm.d \
./source/L2.Spi.d \
./source/L2.SysTick.d \
./source/L2.Usart.d \
./source/L3.BH1750.d \
./source/L3.Bme280.spi.d \
./source/L3.json.parse.d \
./source/L4.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\board" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\source" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\drivers" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\device" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\CMSIS" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\component\uart" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\utilities" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\board\boards" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


