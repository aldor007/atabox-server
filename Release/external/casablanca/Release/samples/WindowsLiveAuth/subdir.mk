################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/samples/WindowsLiveAuth/App.xaml.cpp \
../external/casablanca/Release/samples/WindowsLiveAuth/MainPage.xaml.cpp \
../external/casablanca/Release/samples/WindowsLiveAuth/pch.cpp 

OBJS += \
./external/casablanca/Release/samples/WindowsLiveAuth/App.xaml.o \
./external/casablanca/Release/samples/WindowsLiveAuth/MainPage.xaml.o \
./external/casablanca/Release/samples/WindowsLiveAuth/pch.o 

CPP_DEPS += \
./external/casablanca/Release/samples/WindowsLiveAuth/App.xaml.d \
./external/casablanca/Release/samples/WindowsLiveAuth/MainPage.xaml.d \
./external/casablanca/Release/samples/WindowsLiveAuth/pch.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/samples/WindowsLiveAuth/%.o: ../external/casablanca/Release/samples/WindowsLiveAuth/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


