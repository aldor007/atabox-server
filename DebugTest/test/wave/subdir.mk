################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/wave/NormalizedSampleListMock.cpp \
../test/wave/NormalizedSamplesListTest.cpp \
../test/wave/WaveFileAnalizatorTest.cpp \
../test/wave/WaveFileMock.cpp \
../test/wave/WaveFileTest.cpp \
../test/wave/WavePreprocessorTest.cpp \
../test/wave/WavePropertiesTest.cpp \
../test/wave/WaveUtilsTest.cpp 

OBJS += \
./test/wave/NormalizedSampleListMock.o \
./test/wave/NormalizedSamplesListTest.o \
./test/wave/WaveFileAnalizatorTest.o \
./test/wave/WaveFileMock.o \
./test/wave/WaveFileTest.o \
./test/wave/WavePreprocessorTest.o \
./test/wave/WavePropertiesTest.o \
./test/wave/WaveUtilsTest.o 

CPP_DEPS += \
./test/wave/NormalizedSampleListMock.d \
./test/wave/NormalizedSamplesListTest.d \
./test/wave/WaveFileAnalizatorTest.d \
./test/wave/WaveFileMock.d \
./test/wave/WaveFileTest.d \
./test/wave/WavePreprocessorTest.d \
./test/wave/WavePropertiesTest.d \
./test/wave/WaveUtilsTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/wave/%.o: ../test/wave/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


