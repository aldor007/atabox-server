################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../external/rocksdb_source/util/arena_impl.o \
../external/rocksdb_source/util/auto_roll_logger.o \
../external/rocksdb_source/util/blob_store.o \
../external/rocksdb_source/util/bloom.o \
../external/rocksdb_source/util/build_version.o \
../external/rocksdb_source/util/cache.o \
../external/rocksdb_source/util/coding.o \
../external/rocksdb_source/util/comparator.o \
../external/rocksdb_source/util/crc32c.o \
../external/rocksdb_source/util/env.o \
../external/rocksdb_source/util/env_hdfs.o \
../external/rocksdb_source/util/env_posix.o \
../external/rocksdb_source/util/filter_policy.o \
../external/rocksdb_source/util/hash.o \
../external/rocksdb_source/util/hash_skiplist_rep.o \
../external/rocksdb_source/util/histogram.o \
../external/rocksdb_source/util/ldb_cmd.o \
../external/rocksdb_source/util/ldb_tool.o \
../external/rocksdb_source/util/logging.o \
../external/rocksdb_source/util/murmurhash.o \
../external/rocksdb_source/util/options.o \
../external/rocksdb_source/util/perf_context.o \
../external/rocksdb_source/util/skiplistrep.o \
../external/rocksdb_source/util/slice.o \
../external/rocksdb_source/util/statistics.o \
../external/rocksdb_source/util/status.o \
../external/rocksdb_source/util/string_util.o \
../external/rocksdb_source/util/vectorrep.o 

CC_SRCS += \
../external/rocksdb_source/util/arena_impl.cc \
../external/rocksdb_source/util/arena_test.cc \
../external/rocksdb_source/util/auto_roll_logger.cc \
../external/rocksdb_source/util/auto_roll_logger_test.cc \
../external/rocksdb_source/util/autovector_test.cc \
../external/rocksdb_source/util/blob_store.cc \
../external/rocksdb_source/util/blob_store_test.cc \
../external/rocksdb_source/util/bloom.cc \
../external/rocksdb_source/util/bloom_test.cc \
../external/rocksdb_source/util/build_version.cc \
../external/rocksdb_source/util/cache.cc \
../external/rocksdb_source/util/cache_test.cc \
../external/rocksdb_source/util/coding.cc \
../external/rocksdb_source/util/coding_test.cc \
../external/rocksdb_source/util/comparator.cc \
../external/rocksdb_source/util/crc32c.cc \
../external/rocksdb_source/util/crc32c_test.cc \
../external/rocksdb_source/util/env.cc \
../external/rocksdb_source/util/env_hdfs.cc \
../external/rocksdb_source/util/env_posix.cc \
../external/rocksdb_source/util/env_test.cc \
../external/rocksdb_source/util/filelock_test.cc \
../external/rocksdb_source/util/filter_policy.cc \
../external/rocksdb_source/util/hash.cc \
../external/rocksdb_source/util/hash_skiplist_rep.cc \
../external/rocksdb_source/util/histogram.cc \
../external/rocksdb_source/util/histogram_test.cc \
../external/rocksdb_source/util/ldb_cmd.cc \
../external/rocksdb_source/util/ldb_tool.cc \
../external/rocksdb_source/util/logging.cc \
../external/rocksdb_source/util/manual_compaction_test.cc \
../external/rocksdb_source/util/murmurhash.cc \
../external/rocksdb_source/util/options.cc \
../external/rocksdb_source/util/perf_context.cc \
../external/rocksdb_source/util/signal_test.cc \
../external/rocksdb_source/util/skiplistrep.cc \
../external/rocksdb_source/util/slice.cc \
../external/rocksdb_source/util/statistics.cc \
../external/rocksdb_source/util/status.cc \
../external/rocksdb_source/util/string_util.cc \
../external/rocksdb_source/util/testharness.cc \
../external/rocksdb_source/util/testutil.cc \
../external/rocksdb_source/util/vectorrep.cc 

OBJS += \
./external/rocksdb_source/util/arena_impl.o \
./external/rocksdb_source/util/arena_test.o \
./external/rocksdb_source/util/auto_roll_logger.o \
./external/rocksdb_source/util/auto_roll_logger_test.o \
./external/rocksdb_source/util/autovector_test.o \
./external/rocksdb_source/util/blob_store.o \
./external/rocksdb_source/util/blob_store_test.o \
./external/rocksdb_source/util/bloom.o \
./external/rocksdb_source/util/bloom_test.o \
./external/rocksdb_source/util/build_version.o \
./external/rocksdb_source/util/cache.o \
./external/rocksdb_source/util/cache_test.o \
./external/rocksdb_source/util/coding.o \
./external/rocksdb_source/util/coding_test.o \
./external/rocksdb_source/util/comparator.o \
./external/rocksdb_source/util/crc32c.o \
./external/rocksdb_source/util/crc32c_test.o \
./external/rocksdb_source/util/env.o \
./external/rocksdb_source/util/env_hdfs.o \
./external/rocksdb_source/util/env_posix.o \
./external/rocksdb_source/util/env_test.o \
./external/rocksdb_source/util/filelock_test.o \
./external/rocksdb_source/util/filter_policy.o \
./external/rocksdb_source/util/hash.o \
./external/rocksdb_source/util/hash_skiplist_rep.o \
./external/rocksdb_source/util/histogram.o \
./external/rocksdb_source/util/histogram_test.o \
./external/rocksdb_source/util/ldb_cmd.o \
./external/rocksdb_source/util/ldb_tool.o \
./external/rocksdb_source/util/logging.o \
./external/rocksdb_source/util/manual_compaction_test.o \
./external/rocksdb_source/util/murmurhash.o \
./external/rocksdb_source/util/options.o \
./external/rocksdb_source/util/perf_context.o \
./external/rocksdb_source/util/signal_test.o \
./external/rocksdb_source/util/skiplistrep.o \
./external/rocksdb_source/util/slice.o \
./external/rocksdb_source/util/statistics.o \
./external/rocksdb_source/util/status.o \
./external/rocksdb_source/util/string_util.o \
./external/rocksdb_source/util/testharness.o \
./external/rocksdb_source/util/testutil.o \
./external/rocksdb_source/util/vectorrep.o 

CC_DEPS += \
./external/rocksdb_source/util/arena_impl.d \
./external/rocksdb_source/util/arena_test.d \
./external/rocksdb_source/util/auto_roll_logger.d \
./external/rocksdb_source/util/auto_roll_logger_test.d \
./external/rocksdb_source/util/autovector_test.d \
./external/rocksdb_source/util/blob_store.d \
./external/rocksdb_source/util/blob_store_test.d \
./external/rocksdb_source/util/bloom.d \
./external/rocksdb_source/util/bloom_test.d \
./external/rocksdb_source/util/build_version.d \
./external/rocksdb_source/util/cache.d \
./external/rocksdb_source/util/cache_test.d \
./external/rocksdb_source/util/coding.d \
./external/rocksdb_source/util/coding_test.d \
./external/rocksdb_source/util/comparator.d \
./external/rocksdb_source/util/crc32c.d \
./external/rocksdb_source/util/crc32c_test.d \
./external/rocksdb_source/util/env.d \
./external/rocksdb_source/util/env_hdfs.d \
./external/rocksdb_source/util/env_posix.d \
./external/rocksdb_source/util/env_test.d \
./external/rocksdb_source/util/filelock_test.d \
./external/rocksdb_source/util/filter_policy.d \
./external/rocksdb_source/util/hash.d \
./external/rocksdb_source/util/hash_skiplist_rep.d \
./external/rocksdb_source/util/histogram.d \
./external/rocksdb_source/util/histogram_test.d \
./external/rocksdb_source/util/ldb_cmd.d \
./external/rocksdb_source/util/ldb_tool.d \
./external/rocksdb_source/util/logging.d \
./external/rocksdb_source/util/manual_compaction_test.d \
./external/rocksdb_source/util/murmurhash.d \
./external/rocksdb_source/util/options.d \
./external/rocksdb_source/util/perf_context.d \
./external/rocksdb_source/util/signal_test.d \
./external/rocksdb_source/util/skiplistrep.d \
./external/rocksdb_source/util/slice.d \
./external/rocksdb_source/util/statistics.d \
./external/rocksdb_source/util/status.d \
./external/rocksdb_source/util/string_util.d \
./external/rocksdb_source/util/testharness.d \
./external/rocksdb_source/util/testutil.d \
./external/rocksdb_source/util/vectorrep.d 


# Each subdirectory must supply rules for building sources it contributes
external/rocksdb_source/util/%.o: ../external/rocksdb_source/util/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


