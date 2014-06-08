################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/wave/preprocessing/NormalizingFilterTest.cpp \
../test/wave/preprocessing/PreprocessorTest.cpp \
../test/wave/preprocessing/SilenceCuttingFilterTest.cpp 

OBJS += \
./test/wave/preprocessing/NormalizingFilterTest.o \
./test/wave/preprocessing/PreprocessorTest.o \
./test/wave/preprocessing/SilenceCuttingFilterTest.o 

CPP_DEPS += \
./test/wave/preprocessing/NormalizingFilterTest.d \
./test/wave/preprocessing/PreprocessorTest.d \
./test/wave/preprocessing/SilenceCuttingFilterTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/wave/preprocessing/%.o: ../test/wave/preprocessing/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -I../external/kiss_fft -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


