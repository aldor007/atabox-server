################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/wave/analysis/AmplitudePropertyTest.cpp \
../test/wave/analysis/AverageValuePropertyTest.cpp \
../test/wave/analysis/LengthPropertyTest.cpp \
../test/wave/analysis/PercentageAbovePropertyTest.cpp \
../test/wave/analysis/SamplesAnalizatorTest.cpp \
../test/wave/analysis/WhereIsAmplitudePropertyTest.cpp \
../test/wave/analysis/ZeroCrossingsPropertyTest.cpp 

OBJS += \
./test/wave/analysis/AmplitudePropertyTest.o \
./test/wave/analysis/AverageValuePropertyTest.o \
./test/wave/analysis/LengthPropertyTest.o \
./test/wave/analysis/PercentageAbovePropertyTest.o \
./test/wave/analysis/SamplesAnalizatorTest.o \
./test/wave/analysis/WhereIsAmplitudePropertyTest.o \
./test/wave/analysis/ZeroCrossingsPropertyTest.o 

CPP_DEPS += \
./test/wave/analysis/AmplitudePropertyTest.d \
./test/wave/analysis/AverageValuePropertyTest.d \
./test/wave/analysis/LengthPropertyTest.d \
./test/wave/analysis/PercentageAbovePropertyTest.d \
./test/wave/analysis/SamplesAnalizatorTest.d \
./test/wave/analysis/WhereIsAmplitudePropertyTest.d \
./test/wave/analysis/ZeroCrossingsPropertyTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/wave/analysis/%.o: ../test/wave/analysis/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -I../external/kiss_fft -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


