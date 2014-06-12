################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/samples/CasaLens/casalens.cpp \
../external/casablanca/Release/samples/CasaLens/datafetcher.cpp \
../external/casablanca/Release/samples/CasaLens/stdafx.cpp 

OBJS += \
./external/casablanca/Release/samples/CasaLens/casalens.o \
./external/casablanca/Release/samples/CasaLens/datafetcher.o \
./external/casablanca/Release/samples/CasaLens/stdafx.o 

CPP_DEPS += \
./external/casablanca/Release/samples/CasaLens/casalens.d \
./external/casablanca/Release/samples/CasaLens/datafetcher.d \
./external/casablanca/Release/samples/CasaLens/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/samples/CasaLens/%.o: ../external/casablanca/Release/samples/CasaLens/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


