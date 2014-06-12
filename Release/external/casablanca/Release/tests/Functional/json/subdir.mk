################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/json/construction_tests.cpp \
../external/casablanca/Release/tests/Functional/json/fuzz_tests.cpp \
../external/casablanca/Release/tests/Functional/json/iterator_tests.cpp \
../external/casablanca/Release/tests/Functional/json/json_numbers_tests.cpp \
../external/casablanca/Release/tests/Functional/json/negative_parsing_tests.cpp \
../external/casablanca/Release/tests/Functional/json/parsing_tests.cpp \
../external/casablanca/Release/tests/Functional/json/stdafx.cpp \
../external/casablanca/Release/tests/Functional/json/to_as_and_operators_tests.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/json/construction_tests.o \
./external/casablanca/Release/tests/Functional/json/fuzz_tests.o \
./external/casablanca/Release/tests/Functional/json/iterator_tests.o \
./external/casablanca/Release/tests/Functional/json/json_numbers_tests.o \
./external/casablanca/Release/tests/Functional/json/negative_parsing_tests.o \
./external/casablanca/Release/tests/Functional/json/parsing_tests.o \
./external/casablanca/Release/tests/Functional/json/stdafx.o \
./external/casablanca/Release/tests/Functional/json/to_as_and_operators_tests.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/json/construction_tests.d \
./external/casablanca/Release/tests/Functional/json/fuzz_tests.d \
./external/casablanca/Release/tests/Functional/json/iterator_tests.d \
./external/casablanca/Release/tests/Functional/json/json_numbers_tests.d \
./external/casablanca/Release/tests/Functional/json/negative_parsing_tests.d \
./external/casablanca/Release/tests/Functional/json/parsing_tests.d \
./external/casablanca/Release/tests/Functional/json/stdafx.d \
./external/casablanca/Release/tests/Functional/json/to_as_and_operators_tests.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/json/%.o: ../external/casablanca/Release/tests/Functional/json/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


