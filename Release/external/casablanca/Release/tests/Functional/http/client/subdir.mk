################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../external/casablanca/Release/tests/Functional/http/client/authentication_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/building_request_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/client_construction.cpp \
../external/casablanca/Release/tests/Functional/http/client/connections_and_errors.cpp \
../external/casablanca/Release/tests/Functional/http/client/header_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/http_client_fuzz_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/http_client_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/http_methods_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/multiple_requests.cpp \
../external/casablanca/Release/tests/Functional/http/client/outside_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/pipeline_stage_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/progress_handler_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/proxy_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/request_helper_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/request_stream_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/request_uri_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/response_extract_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/response_stream_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/status_code_reason_phrase_tests.cpp \
../external/casablanca/Release/tests/Functional/http/client/stdafx.cpp \
../external/casablanca/Release/tests/Functional/http/client/to_string_tests.cpp 

OBJS += \
./external/casablanca/Release/tests/Functional/http/client/authentication_tests.o \
./external/casablanca/Release/tests/Functional/http/client/building_request_tests.o \
./external/casablanca/Release/tests/Functional/http/client/client_construction.o \
./external/casablanca/Release/tests/Functional/http/client/connections_and_errors.o \
./external/casablanca/Release/tests/Functional/http/client/header_tests.o \
./external/casablanca/Release/tests/Functional/http/client/http_client_fuzz_tests.o \
./external/casablanca/Release/tests/Functional/http/client/http_client_tests.o \
./external/casablanca/Release/tests/Functional/http/client/http_methods_tests.o \
./external/casablanca/Release/tests/Functional/http/client/multiple_requests.o \
./external/casablanca/Release/tests/Functional/http/client/outside_tests.o \
./external/casablanca/Release/tests/Functional/http/client/pipeline_stage_tests.o \
./external/casablanca/Release/tests/Functional/http/client/progress_handler_tests.o \
./external/casablanca/Release/tests/Functional/http/client/proxy_tests.o \
./external/casablanca/Release/tests/Functional/http/client/request_helper_tests.o \
./external/casablanca/Release/tests/Functional/http/client/request_stream_tests.o \
./external/casablanca/Release/tests/Functional/http/client/request_uri_tests.o \
./external/casablanca/Release/tests/Functional/http/client/response_extract_tests.o \
./external/casablanca/Release/tests/Functional/http/client/response_stream_tests.o \
./external/casablanca/Release/tests/Functional/http/client/status_code_reason_phrase_tests.o \
./external/casablanca/Release/tests/Functional/http/client/stdafx.o \
./external/casablanca/Release/tests/Functional/http/client/to_string_tests.o 

CPP_DEPS += \
./external/casablanca/Release/tests/Functional/http/client/authentication_tests.d \
./external/casablanca/Release/tests/Functional/http/client/building_request_tests.d \
./external/casablanca/Release/tests/Functional/http/client/client_construction.d \
./external/casablanca/Release/tests/Functional/http/client/connections_and_errors.d \
./external/casablanca/Release/tests/Functional/http/client/header_tests.d \
./external/casablanca/Release/tests/Functional/http/client/http_client_fuzz_tests.d \
./external/casablanca/Release/tests/Functional/http/client/http_client_tests.d \
./external/casablanca/Release/tests/Functional/http/client/http_methods_tests.d \
./external/casablanca/Release/tests/Functional/http/client/multiple_requests.d \
./external/casablanca/Release/tests/Functional/http/client/outside_tests.d \
./external/casablanca/Release/tests/Functional/http/client/pipeline_stage_tests.d \
./external/casablanca/Release/tests/Functional/http/client/progress_handler_tests.d \
./external/casablanca/Release/tests/Functional/http/client/proxy_tests.d \
./external/casablanca/Release/tests/Functional/http/client/request_helper_tests.d \
./external/casablanca/Release/tests/Functional/http/client/request_stream_tests.d \
./external/casablanca/Release/tests/Functional/http/client/request_uri_tests.d \
./external/casablanca/Release/tests/Functional/http/client/response_extract_tests.d \
./external/casablanca/Release/tests/Functional/http/client/response_stream_tests.d \
./external/casablanca/Release/tests/Functional/http/client/status_code_reason_phrase_tests.d \
./external/casablanca/Release/tests/Functional/http/client/stdafx.d \
./external/casablanca/Release/tests/Functional/http/client/to_string_tests.d 


# Each subdirectory must supply rules for building sources it contributes
external/casablanca/Release/tests/Functional/http/client/%.o: ../external/casablanca/Release/tests/Functional/http/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


