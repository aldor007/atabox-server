################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../external/rocksdb_source/port/port_posix.o \
../external/rocksdb_source/port/stack_trace.o 

CC_SRCS += \
../external/rocksdb_source/port/port_posix.cc \
../external/rocksdb_source/port/stack_trace.cc 

OBJS += \
./external/rocksdb_source/port/port_posix.o \
./external/rocksdb_source/port/stack_trace.o 

CC_DEPS += \
./external/rocksdb_source/port/port_posix.d \
./external/rocksdb_source/port/stack_trace.d 


# Each subdirectory must supply rules for building sources it contributes
external/rocksdb_source/port/%.o: ../external/rocksdb_source/port/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


