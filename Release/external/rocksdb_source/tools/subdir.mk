################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../external/rocksdb_source/tools/blob_store_bench.cc \
../external/rocksdb_source/tools/db_repl_stress.cc \
../external/rocksdb_source/tools/db_stress.cc \
../external/rocksdb_source/tools/ldb.cc \
../external/rocksdb_source/tools/reduce_levels_test.cc \
../external/rocksdb_source/tools/sst_dump.cc 

OBJS += \
./external/rocksdb_source/tools/blob_store_bench.o \
./external/rocksdb_source/tools/db_repl_stress.o \
./external/rocksdb_source/tools/db_stress.o \
./external/rocksdb_source/tools/ldb.o \
./external/rocksdb_source/tools/reduce_levels_test.o \
./external/rocksdb_source/tools/sst_dump.o 

CC_DEPS += \
./external/rocksdb_source/tools/blob_store_bench.d \
./external/rocksdb_source/tools/db_repl_stress.d \
./external/rocksdb_source/tools/db_stress.d \
./external/rocksdb_source/tools/ldb.d \
./external/rocksdb_source/tools/reduce_levels_test.d \
./external/rocksdb_source/tools/sst_dump.d 


# Each subdirectory must supply rules for building sources it contributes
external/rocksdb_source/tools/%.o: ../external/rocksdb_source/tools/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


