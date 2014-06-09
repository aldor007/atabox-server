################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/wave/processing/postprocessing/FastFourierTransformFilterTest.cpp \
../test/wave/processing/postprocessing/HannWindowFilterTest.cpp 

OBJS += \
./test/wave/processing/postprocessing/FastFourierTransformFilterTest.o \
./test/wave/processing/postprocessing/HannWindowFilterTest.o 

CPP_DEPS += \
./test/wave/processing/postprocessing/FastFourierTransformFilterTest.d \
./test/wave/processing/postprocessing/HannWindowFilterTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/wave/processing/postprocessing/%.o: ../test/wave/processing/postprocessing/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -I../external/kiss_fft -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


