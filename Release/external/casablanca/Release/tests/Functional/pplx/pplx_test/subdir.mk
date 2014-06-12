################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_op_test.cpp \
../external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_scheduler.cpp \
../external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_task_options.cpp \
../external/casablanca/Release/tests/Functional/pplx/pplx_test/pplxtask_tests.cpp \
../external/casablanca/Release/tests/Functional/pplx/pplx_test/stdafx.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_op_test.o \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_scheduler.o \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_task_options.o \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplxtask_tests.o \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/stdafx.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_op_test.d \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_scheduler.d \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplx_task_options.d \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/pplxtask_tests.d \
./external/casablanca/Release/tests/Functional/pplx/pplx_test/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/pplx/pplx_test/%.o: ../external/casablanca/Release/tests/Functional/pplx/pplx_test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


