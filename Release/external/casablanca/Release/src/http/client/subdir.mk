################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/src/http/client/http_linux.cpp \
../external/casablanca/Release/src/http/client/http_msg_client.cpp \
../external/casablanca/Release/src/http/client/http_win7.cpp \
../external/casablanca/Release/src/http/client/http_win8.cpp 

OBJS += \
./external/casablanca/Release/src/http/client/http_linux.o \
./external/casablanca/Release/src/http/client/http_msg_client.o \
./external/casablanca/Release/src/http/client/http_win7.o \
./external/casablanca/Release/src/http/client/http_win8.o 

CPP_DEPS += \
./external/casablanca/Release/src/http/client/http_linux.d \
./external/casablanca/Release/src/http/client/http_msg_client.d \
./external/casablanca/Release/src/http/client/http_win7.d \
./external/casablanca/Release/src/http/client/http_win8.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/src/http/client/%.o: ../external/casablanca/Release/src/http/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


