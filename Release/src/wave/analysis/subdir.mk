################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/wave/analysis/PropertyWithRange.cpp \
../src/wave/analysis/SamplesAnalizator.cpp 

OBJS += \
./src/wave/analysis/PropertyWithRange.o \
./src/wave/analysis/SamplesAnalizator.o 

CPP_DEPS += \
./src/wave/analysis/PropertyWithRange.d \
./src/wave/analysis/SamplesAnalizator.d 


# Each subdirectory must supply rules for building sources it contributes
src/wave/analysis/%.o: ../src/wave/analysis/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -c -fmessage-length=0 -std=c++11 -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


