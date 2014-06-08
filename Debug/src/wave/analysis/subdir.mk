################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/wave/analysis/SamplesAnalizator.cpp \
../src/wave/analysis/WaveProperties.cpp 

OBJS += \
./src/wave/analysis/SamplesAnalizator.o \
./src/wave/analysis/WaveProperties.o 

CPP_DEPS += \
./src/wave/analysis/SamplesAnalizator.d \
./src/wave/analysis/WaveProperties.d 


# Each subdirectory must supply rules for building sources it contributes
src/wave/analysis/%.o: ../src/wave/analysis/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -I../external/kiss_fft -O0 -g3 -c -fmessage-length=0 -std=c++11  -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


