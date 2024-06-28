################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/miniusart_adapter.c 

OBJS += \
./component/uart/miniusart_adapter.o 

C_DEPS += \
./component/uart/miniusart_adapter.d 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\board" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\source" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\drivers" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\device" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\CMSIS" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\component\uart" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\utilities" -I"C:\Users\Dario\Documents\MCUXpressoIDE_11.1.1_3241\workspace\DemoInfo1\board\boards" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


