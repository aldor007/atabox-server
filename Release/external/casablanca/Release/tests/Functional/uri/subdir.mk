################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/uri/accessor_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/combining_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/constructor_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/conversions_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/diagnostic_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/encoding_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/operator_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/splitting_tests.cpp \
../external/casablanca/Release/tests/Functional/uri/stdafx.cpp \
../external/casablanca/Release/tests/Functional/uri/uri_builder_tests.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/uri/accessor_tests.o \
./external/casablanca/Release/tests/Functional/uri/combining_tests.o \
./external/casablanca/Release/tests/Functional/uri/constructor_tests.o \
./external/casablanca/Release/tests/Functional/uri/conversions_tests.o \
./external/casablanca/Release/tests/Functional/uri/diagnostic_tests.o \
./external/casablanca/Release/tests/Functional/uri/encoding_tests.o \
./external/casablanca/Release/tests/Functional/uri/operator_tests.o \
./external/casablanca/Release/tests/Functional/uri/splitting_tests.o \
./external/casablanca/Release/tests/Functional/uri/stdafx.o \
./external/casablanca/Release/tests/Functional/uri/uri_builder_tests.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/uri/accessor_tests.d \
./external/casablanca/Release/tests/Functional/uri/combining_tests.d \
./external/casablanca/Release/tests/Functional/uri/constructor_tests.d \
./external/casablanca/Release/tests/Functional/uri/conversions_tests.d \
./external/casablanca/Release/tests/Functional/uri/diagnostic_tests.d \
./external/casablanca/Release/tests/Functional/uri/encoding_tests.d \
./external/casablanca/Release/tests/Functional/uri/operator_tests.d \
./external/casablanca/Release/tests/Functional/uri/splitting_tests.d \
./external/casablanca/Release/tests/Functional/uri/stdafx.d \
./external/casablanca/Release/tests/Functional/uri/uri_builder_tests.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/uri/%.o: ../external/casablanca/Release/tests/Functional/uri/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


