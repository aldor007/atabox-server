################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestAssertHandler.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCheckMacros.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestChecks.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCompositeTestReporter.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCurrentTest.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestDeferredTestReporter.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestMemoryOutStream.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTest.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestList.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestMacros.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestResults.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestRunner.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestSuite.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestUnitTestPP.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestXmlTestReporter.cpp \
../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/stdafx.cpp 

OBJS += \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestAssertHandler.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCheckMacros.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestChecks.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCompositeTestReporter.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCurrentTest.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestDeferredTestReporter.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestMemoryOutStream.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTest.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestList.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestMacros.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestResults.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestRunner.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestSuite.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestUnitTestPP.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestXmlTestReporter.o \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/stdafx.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestAssertHandler.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCheckMacros.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestChecks.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCompositeTestReporter.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestCurrentTest.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestDeferredTestReporter.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestMemoryOutStream.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTest.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestList.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestMacros.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestResults.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestRunner.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestTestSuite.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestUnitTestPP.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/TestXmlTestReporter.d \
./external/casablanca/Release/tests/Common/UnitTestpp/src/tests/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Common/UnitTestpp/src/tests/%.o: ../external/casablanca/Release/tests/Common/UnitTestpp/src/tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


