################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/init.c \
../src/serial.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

CPP_SRCS += \
../src/ad_convert.cpp \
../src/hardware.cpp \
../src/main.cpp \
../src/user.cpp 

OBJS += \
./src/ad_convert.o \
./src/hardware.o \
./src/init.o \
./src/main.o \
./src/serial.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/user.o 

C_DEPS += \
./src/init.d \
./src/serial.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 

CPP_DEPS += \
./src/ad_convert.d \
./src/hardware.d \
./src/main.d \
./src/user.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo %cd%
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib" -I"C:/Users/Koizumi/workspace/halfmouse/inc" -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib/CMSIS/core" -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib/CMSIS/device" -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F405RGTx -DSTM32F4 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib" -I"C:/Users/Koizumi/workspace/halfmouse/inc" -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib/CMSIS/core" -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib/CMSIS/device" -I"C:/Users/Koizumi/workspace/stm32f405rg_stdperiph_lib/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


