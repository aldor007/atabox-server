################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataproviders/FileDataProvider.cpp \
../src/dataproviders/RocksdbProvider.cpp 

OBJS += \
./src/dataproviders/FileDataProvider.o \
./src/dataproviders/RocksdbProvider.o 

CPP_DEPS += \
./src/dataproviders/FileDataProvider.d \
./src/dataproviders/RocksdbProvider.d 


# Each subdirectory must supply rules for building sources it contributes
src/dataproviders/%.o: ../src/dataproviders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-4.8 -std=c++1y -I"/home/aldor/workspace/atabox-server/external/rocksdb_source/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


