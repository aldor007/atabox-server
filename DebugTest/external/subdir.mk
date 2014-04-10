################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../external/gmock-gtest-all.cc 

OBJS += \
./external/gmock-gtest-all.o 

CC_DEPS += \
./external/gmock-gtest-all.d 


# Each subdirectory must supply rules for building sources it contributes
external/%.o: ../external/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-4.8 -std=c++1y -I"/home/aldor/workspace/repos/studia/aipsc/atabox-server/external/rocksdb_source/include" -I"/home/aldor/workspace/repos/studia/aipsc/atabox-server/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


