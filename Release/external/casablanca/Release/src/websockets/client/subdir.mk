################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/src/websockets/client/ws_msg.cpp \
../external/casablanca/Release/src/websockets/client/ws_winrt.cpp 

OBJS += \
./external/casablanca/Release/src/websockets/client/ws_msg.o \
./external/casablanca/Release/src/websockets/client/ws_winrt.o 

CPP_DEPS += \
./external/casablanca/Release/src/websockets/client/ws_msg.d \
./external/casablanca/Release/src/websockets/client/ws_winrt.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/src/websockets/client/%.o: ../external/casablanca/Release/src/websockets/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


