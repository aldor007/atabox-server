################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/http/listener/building_response_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/connections_and_errors.cpp \
../external/casablanca/Release/tests/Functional/http/listener/header_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/listener_construction_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/reply_helper_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/request_extract_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/request_handler_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/request_relative_uri_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/request_stream_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/requests_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/response_stream_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/status_code_reason_phrase_tests.cpp \
../external/casablanca/Release/tests/Functional/http/listener/stdafx.cpp \
../external/casablanca/Release/tests/Functional/http/listener/to_string_tests.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/http/listener/building_response_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/connections_and_errors.o \
./external/casablanca/Release/tests/Functional/http/listener/header_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/listener_construction_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/reply_helper_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/request_extract_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/request_handler_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/request_relative_uri_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/request_stream_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/requests_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/response_stream_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/status_code_reason_phrase_tests.o \
./external/casablanca/Release/tests/Functional/http/listener/stdafx.o \
./external/casablanca/Release/tests/Functional/http/listener/to_string_tests.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/http/listener/building_response_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/connections_and_errors.d \
./external/casablanca/Release/tests/Functional/http/listener/header_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/listener_construction_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/reply_helper_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/request_extract_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/request_handler_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/request_relative_uri_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/request_stream_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/requests_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/response_stream_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/status_code_reason_phrase_tests.d \
./external/casablanca/Release/tests/Functional/http/listener/stdafx.d \
./external/casablanca/Release/tests/Functional/http/listener/to_string_tests.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/http/listener/%.o: ../external/casablanca/Release/tests/Functional/http/listener/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


