################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../external/rocksdb_source/utilities/backupable/backupable_db.o 

CC_SRCS += \
../external/rocksdb_source/utilities/backupable/backupable_db.cc \
../external/rocksdb_source/utilities/backupable/backupable_db_test.cc 

OBJS += \
./external/rocksdb_source/utilities/backupable/backupable_db.o \
./external/rocksdb_source/utilities/backupable/backupable_db_test.o 

CC_DEPS += \
./external/rocksdb_source/utilities/backupable/backupable_db.d \
./external/rocksdb_source/utilities/backupable/backupable_db_test.d 


# Each subdirectory must supply rules for building sources it contributes
external/rocksdb_source/utilities/backupable/%.o: ../external/rocksdb_source/utilities/backupable/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


