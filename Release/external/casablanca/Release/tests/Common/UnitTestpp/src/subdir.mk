################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Common/UnitTestpp/src/AssertException.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/CompositeTestReporter.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/CurrentTest.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/DeferredTestReporter.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/DeferredTestResult.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/GlobalSettings.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/MemoryOutStream.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/ReportAssert.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/Test.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/TestDetails.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/TestList.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/TestReporter.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/TestReporterStdout.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/TestResults.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/TestRunner.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/XmlTestReporter.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/stdafx.cpp 

OBJS += \
./external/casablanca/Release/tests/Common/UnitTestpp/src/AssertException.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/CompositeTestReporter.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/CurrentTest.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/DeferredTestReporter.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/DeferredTestResult.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/GlobalSettings.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/MemoryOutStream.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/ReportAssert.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/Test.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestDetails.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestList.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestReporter.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestReporterStdout.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestResults.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestRunner.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/XmlTestReporter.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/stdafx.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Common/UnitTestpp/src/AssertException.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/CompositeTestReporter.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/CurrentTest.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/DeferredTestReporter.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/DeferredTestResult.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/GlobalSettings.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/MemoryOutStream.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/ReportAssert.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/Test.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestDetails.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestList.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestReporter.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestReporterStdout.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestResults.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/TestRunner.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/XmlTestReporter.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Common/UnitTestpp/src/%.o: ../external/casablanca/Release/tests/Common/UnitTestpp/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


