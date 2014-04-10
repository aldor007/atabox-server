################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/wave/WaveFileAnalizatorTest.cpp \
../test/wave/WaveFileMock.cpp \
../test/wave/WaveFileTest.cpp \
../test/wave/WavePropertiesTest.cpp \
../test/wave/waveWavePreprocessorTest.cpp 

OBJS += \
./test/wave/WaveFileAnalizatorTest.o \
./test/wave/WaveFileMock.o \
./test/wave/WaveFileTest.o \
./test/wave/WavePropertiesTest.o \
./test/wave/waveWavePreprocessorTest.o 

CPP_DEPS += \
./test/wave/WaveFileAnalizatorTest.d \
./test/wave/WaveFileMock.d \
./test/wave/WaveFileTest.d \
./test/wave/WavePropertiesTest.d \
./test/wave/waveWavePreprocessorTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/wave/%.o: ../test/wave/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-4.8 -std=c++1y -I"/home/aldor/workspace/repos/studia/aipsc/atabox-server/external/rocksdb_source/include" -I"/home/aldor/workspace/repos/studia/aipsc/atabox-server/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


