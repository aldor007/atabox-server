################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/wave/WaveFileAnalizatorTest.cpp \
../test/wave/WaveFileMock.cpp \
../test/wave/WaveFileTest.cpp 

OBJS += \
./test/wave/WaveFileAnalizatorTest.o \
./test/wave/WaveFileMock.o \
./test/wave/WaveFileTest.o 

CPP_DEPS += \
./test/wave/WaveFileAnalizatorTest.d \
./test/wave/WaveFileMock.d \
./test/wave/WaveFileTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/wave/%.o: ../test/wave/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__GXX_EXPERIMENTAL_CXX0X__ -I"/home/mj/CppWorkspace/Atabox_server/src" -I"/home/mj/CppWorkspace/Atabox_server/external" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


