################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/src/json/json.cpp \
../external/casablanca/Release/src/json/json_parsing.cpp \
../external/casablanca/Release/src/json/json_serialization.cpp 

OBJS += \
./external/casablanca/Release/src/json/json.o \
./external/casablanca/Release/src/json/json_parsing.o \
./external/casablanca/Release/src/json/json_serialization.o 

CPP_DEPS += \
./external/casablanca/Release/src/json/json.d \
./external/casablanca/Release/src/json/json_parsing.d \
./external/casablanca/Release/src/json/json_serialization.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/src/json/%.o: ../external/casablanca/Release/src/json/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


