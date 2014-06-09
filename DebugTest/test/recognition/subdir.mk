################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/recognition/ProcessAndAnalyzeTest.cpp \
../test/recognition/PropertiesComparatorTest.cpp 

OBJS += \
./test/recognition/ProcessAndAnalyzeTest.o \
./test/recognition/PropertiesComparatorTest.o 

CPP_DEPS += \
./test/recognition/ProcessAndAnalyzeTest.d \
./test/recognition/PropertiesComparatorTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/recognition/%.o: ../test/recognition/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -I../external/kiss_fft -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


