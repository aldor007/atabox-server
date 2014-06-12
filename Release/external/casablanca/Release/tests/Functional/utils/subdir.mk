################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/utils/base64.cpp \
../external/casablanca/Release/tests/Functional/utils/datetime.cpp \
../external/casablanca/Release/tests/Functional/utils/macro_test.cpp \
../external/casablanca/Release/tests/Functional/utils/stdafx.cpp \
../external/casablanca/Release/tests/Functional/utils/strings.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/utils/base64.o \
./external/casablanca/Release/tests/Functional/utils/datetime.o \
./external/casablanca/Release/tests/Functional/utils/macro_test.o \
./external/casablanca/Release/tests/Functional/utils/stdafx.o \
./external/casablanca/Release/tests/Functional/utils/strings.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/utils/base64.d \
./external/casablanca/Release/tests/Functional/utils/datetime.d \
./external/casablanca/Release/tests/Functional/utils/macro_test.d \
./external/casablanca/Release/tests/Functional/utils/stdafx.d \
./external/casablanca/Release/tests/Functional/utils/strings.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/utils/%.o: ../external/casablanca/Release/tests/Functional/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


