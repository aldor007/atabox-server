################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../external/rocksdb_source/utilities/merge_operators/put.o \
../external/rocksdb_source/utilities/merge_operators/uint64add.o 

CC_SRCS += \
../external/rocksdb_source/utilities/merge_operators/put.cc \
../external/rocksdb_source/utilities/merge_operators/uint64add.cc 

OBJS += \
./external/rocksdb_source/utilities/merge_operators/put.o \
./external/rocksdb_source/utilities/merge_operators/uint64add.o 

CC_DEPS += \
./external/rocksdb_source/utilities/merge_operators/put.d \
./external/rocksdb_source/utilities/merge_operators/uint64add.d 


# Each subdirectory must supply rules for building sources it contributes
external/rocksdb_source/utilities/merge_operators/%.o: ../external/rocksdb_source/utilities/merge_operators/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


