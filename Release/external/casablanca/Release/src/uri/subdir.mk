################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/src/uri/uri.cpp \
../external/casablanca/Release/src/uri/uri_builder.cpp \
../external/casablanca/Release/src/uri/uri_parser.cpp 

OBJS += \
./external/casablanca/Release/src/uri/uri.o \
./external/casablanca/Release/src/uri/uri_builder.o \
./external/casablanca/Release/src/uri/uri_parser.o 

CPP_DEPS += \
./external/casablanca/Release/src/uri/uri.d \
./external/casablanca/Release/src/uri/uri_builder.d \
./external/casablanca/Release/src/uri/uri_parser.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/src/uri/%.o: ../external/casablanca/Release/src/uri/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


