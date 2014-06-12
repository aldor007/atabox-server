################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/rocksdb_source/tools/shell/DBClientProxy.cpp \
../external/rocksdb_source/tools/shell/LeveldbShell.cpp \
../external/rocksdb_source/tools/shell/ShellContext.cpp \
../external/rocksdb_source/tools/shell/ShellState.cpp 

OBJS += \
./external/rocksdb_source/tools/shell/DBClientProxy.o \
./external/rocksdb_source/tools/shell/LeveldbShell.o \
./external/rocksdb_source/tools/shell/ShellContext.o \
./external/rocksdb_source/tools/shell/ShellState.o 

CPP_DEPS += \
./external/rocksdb_source/tools/shell/DBClientProxy.d \
./external/rocksdb_source/tools/shell/LeveldbShell.d \
./external/rocksdb_source/tools/shell/ShellContext.d \
./external/rocksdb_source/tools/shell/ShellState.d 


# Each subdirectory must supply rules for building sources it contributes
external/rocksdb_source/tools/shell/%.o: ../external/rocksdb_source/tools/shell/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


