################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/src/http/listener/http_linux_server.cpp \
../external/casablanca/Release/src/http/listener/http_listener.cpp \
../external/casablanca/Release/src/http/listener/http_msg_listen.cpp \
../external/casablanca/Release/src/http/listener/http_server_api.cpp \
../external/casablanca/Release/src/http/listener/http_windows_server.cpp 

OBJS += \
./external/casablanca/Release/src/http/listener/http_linux_server.o \
./external/casablanca/Release/src/http/listener/http_listener.o \
./external/casablanca/Release/src/http/listener/http_msg_listen.o \
./external/casablanca/Release/src/http/listener/http_server_api.o \
./external/casablanca/Release/src/http/listener/http_windows_server.o 

CPP_DEPS += \
./external/casablanca/Release/src/http/listener/http_linux_server.d \
./external/casablanca/Release/src/http/listener/http_listener.d \
./external/casablanca/Release/src/http/listener/http_msg_listen.d \
./external/casablanca/Release/src/http/listener/http_server_api.d \
./external/casablanca/Release/src/http/listener/http_windows_server.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/src/http/listener/%.o: ../external/casablanca/Release/src/http/listener/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


