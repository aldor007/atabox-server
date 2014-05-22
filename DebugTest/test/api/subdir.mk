################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/api/AtaboxApiTest.cpp \
../test/api/casablancaMocks.cpp 

OBJS += \
./test/api/AtaboxApiTest.o \
./test/api/casablancaMocks.o 

CPP_DEPS += \
./test/api/AtaboxApiTest.d \
./test/api/casablancaMocks.d 


# Each subdirectory must supply rules for building sources it contributes
test/api/%.o: ../test/api/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


