################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/streams/fstreambuf_tests.cpp \
../external/casablanca/Release/tests/Functional/streams/fuzz_tests.cpp \
../external/casablanca/Release/tests/Functional/streams/istream_tests.cpp \
../external/casablanca/Release/tests/Functional/streams/memstream_tests.cpp \
../external/casablanca/Release/tests/Functional/streams/ostream_tests.cpp \
../external/casablanca/Release/tests/Functional/streams/stdafx.cpp \
../external/casablanca/Release/tests/Functional/streams/stdstream_tests.cpp \
../external/casablanca/Release/tests/Functional/streams/winrt_interop_tests.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/streams/fstreambuf_tests.o \
./external/casablanca/Release/tests/Functional/streams/fuzz_tests.o \
./external/casablanca/Release/tests/Functional/streams/istream_tests.o \
./external/casablanca/Release/tests/Functional/streams/memstream_tests.o \
./external/casablanca/Release/tests/Functional/streams/ostream_tests.o \
./external/casablanca/Release/tests/Functional/streams/stdafx.o \
./external/casablanca/Release/tests/Functional/streams/stdstream_tests.o \
./external/casablanca/Release/tests/Functional/streams/winrt_interop_tests.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/streams/fstreambuf_tests.d \
./external/casablanca/Release/tests/Functional/streams/fuzz_tests.d \
./external/casablanca/Release/tests/Functional/streams/istream_tests.d \
./external/casablanca/Release/tests/Functional/streams/memstream_tests.d \
./external/casablanca/Release/tests/Functional/streams/ostream_tests.d \
./external/casablanca/Release/tests/Functional/streams/stdafx.d \
./external/casablanca/Release/tests/Functional/streams/stdstream_tests.d \
./external/casablanca/Release/tests/Functional/streams/winrt_interop_tests.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/streams/%.o: ../external/casablanca/Release/tests/Functional/streams/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


