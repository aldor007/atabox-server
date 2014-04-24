################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/utils/DanielsonLanczosTest.cpp \
../test/utils/FastFourierTransformTest.cpp 

OBJS += \
./test/utils/DanielsonLanczosTest.o \
./test/utils/FastFourierTransformTest.o 

CPP_DEPS += \
./test/utils/DanielsonLanczosTest.d \
./test/utils/FastFourierTransformTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/utils/%.o: ../test/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


