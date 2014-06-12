################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Common/TestRunner/test_module_loader.cpp \
../external/casablanca/Release/tests/Common/TestRunner/test_runner.cpp 

OBJS += \
./external/casablanca/Release/tests/Common/TestRunner/test_module_loader.o \
./external/casablanca/Release/tests/Common/TestRunner/test_runner.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Common/TestRunner/test_module_loader.d \
./external/casablanca/Release/tests/Common/TestRunner/test_runner.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Common/TestRunner/%.o: ../external/casablanca/Release/tests/Common/TestRunner/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


