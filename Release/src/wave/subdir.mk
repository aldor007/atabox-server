################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/wave/WaveFile.cpp \
../src/wave/WaveFileAnalizator.cpp \
../src/wave/WavePreprocessor.cpp \
../src/wave/WaveProperties.cpp 

OBJS += \
./src/wave/WaveFile.o \
./src/wave/WaveFileAnalizator.o \
./src/wave/WavePreprocessor.o \
./src/wave/WaveProperties.o 

CPP_DEPS += \
./src/wave/WaveFile.d \
./src/wave/WaveFileAnalizator.d \
./src/wave/WavePreprocessor.d \
./src/wave/WaveProperties.d 


# Each subdirectory must supply rules for building sources it contributes
src/wave/%.o: ../src/wave/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/mj/CppWorkspace/Atabox_server/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


