################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/wave/Samples.cpp \
../src/wave/WaveFile.cpp \
../src/wave/WaveUtils.cpp 

OBJS += \
./src/wave/Samples.o \
./src/wave/WaveFile.o \
./src/wave/WaveUtils.o 

CPP_DEPS += \
./src/wave/Samples.d \
./src/wave/WaveFile.d \
./src/wave/WaveUtils.d 


# Each subdirectory must supply rules for building sources it contributes
src/wave/%.o: ../src/wave/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -O0 -g3 -c -fmessage-length=0 -std=c++11  -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


