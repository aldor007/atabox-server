################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/utils/FastFourierTransformTest.cpp \
../test/utils/execution_policyTest.cpp \
../test/utils/jsonextendTest.cpp 

OBJS += \
./test/utils/FastFourierTransformTest.o \
./test/utils/execution_policyTest.o \
./test/utils/jsonextendTest.o 

CPP_DEPS += \
./test/utils/FastFourierTransformTest.d \
./test/utils/execution_policyTest.d \
./test/utils/jsonextendTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/utils/%.o: ../test/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -I../external/kiss_fft -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


