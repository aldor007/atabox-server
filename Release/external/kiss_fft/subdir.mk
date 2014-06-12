################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../external/kiss_fft/kiss_fft.c 

OBJS += \
./external/kiss_fft/kiss_fft.o 

C_DEPS += \
./external/kiss_fft/kiss_fft.d 


# Each subdirectory must supply rules for building sources it contributes
external/kiss_fft/%.o: ../external/kiss_fft/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/aldor/workspace/studia/aipsc/atabox-server/src" -I"/home/aldor/workspace/studia/aipsc/atabox-server/external" -I"/home/aldor/workspace/studia/aipsc/atabox-server/external/rocksdb_source/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


