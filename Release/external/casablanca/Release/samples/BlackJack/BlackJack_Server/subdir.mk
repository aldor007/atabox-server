################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/samples/BlackJack/BlackJack_Server/BlackJack_Server.cpp \
../external/casablanca/Release/samples/BlackJack/BlackJack_Server/Dealer.cpp \
../external/casablanca/Release/samples/BlackJack/BlackJack_Server/Table.cpp \
../external/casablanca/Release/samples/BlackJack/BlackJack_Server/stdafx.cpp 

OBJS += \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/BlackJack_Server.o \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/Dealer.o \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/Table.o \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/stdafx.o 

CPP_DEPS += \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/BlackJack_Server.d \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/Dealer.d \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/Table.d \
./external/casablanca/Release/samples/BlackJack/BlackJack_Server/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/samples/BlackJack/BlackJack_Server/%.o: ../external/casablanca/Release/samples/BlackJack/BlackJack_Server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


