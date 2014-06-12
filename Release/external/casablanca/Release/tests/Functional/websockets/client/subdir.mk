################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/websockets/client/client_construction.cpp \
../external/casablanca/Release/tests/Functional/websockets/client/close_tests.cpp \
../external/casablanca/Release/tests/Functional/websockets/client/error_tests.cpp \
../external/casablanca/Release/tests/Functional/websockets/client/receive_msg_tests.cpp \
../external/casablanca/Release/tests/Functional/websockets/client/send_msg_tests.cpp \
../external/casablanca/Release/tests/Functional/websockets/client/stdafx.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/websockets/client/client_construction.o \
./external/casablanca/Release/tests/Functional/websockets/client/close_tests.o \
./external/casablanca/Release/tests/Functional/websockets/client/error_tests.o \
./external/casablanca/Release/tests/Functional/websockets/client/receive_msg_tests.o \
./external/casablanca/Release/tests/Functional/websockets/client/send_msg_tests.o \
./external/casablanca/Release/tests/Functional/websockets/client/stdafx.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/websockets/client/client_construction.d \
./external/casablanca/Release/tests/Functional/websockets/client/close_tests.d \
./external/casablanca/Release/tests/Functional/websockets/client/error_tests.d \
./external/casablanca/Release/tests/Functional/websockets/client/receive_msg_tests.d \
./external/casablanca/Release/tests/Functional/websockets/client/send_msg_tests.d \
./external/casablanca/Release/tests/Functional/websockets/client/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/websockets/client/%.o: ../external/casablanca/Release/tests/Functional/websockets/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


