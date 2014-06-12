################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../external/rocksdb_source/db/builder.o \
../external/rocksdb_source/db/c.o \
../external/rocksdb_source/db/compaction.o \
../external/rocksdb_source/db/compaction_picker.o \
../external/rocksdb_source/db/db_filesnapshot.o \
../external/rocksdb_source/db/db_impl.o \
../external/rocksdb_source/db/db_impl_readonly.o \
../external/rocksdb_source/db/db_iter.o \
../external/rocksdb_source/db/db_stats_logger.o \
../external/rocksdb_source/db/dbformat.o \
../external/rocksdb_source/db/filename.o \
../external/rocksdb_source/db/log_reader.o \
../external/rocksdb_source/db/log_writer.o \
../external/rocksdb_source/db/memtable.o \
../external/rocksdb_source/db/memtablelist.o \
../external/rocksdb_source/db/merge_helper.o \
../external/rocksdb_source/db/merge_operator.o \
../external/rocksdb_source/db/repair.o \
../external/rocksdb_source/db/table_cache.o \
../external/rocksdb_source/db/table_properties_collector.o \
../external/rocksdb_source/db/tailing_iter.o \
../external/rocksdb_source/db/transaction_log_impl.o \
../external/rocksdb_source/db/version_edit.o \
../external/rocksdb_source/db/version_set.o \
../external/rocksdb_source/db/write_batch.o 

C_SRCS += \
../external/rocksdb_source/db/c_test.c 

CC_SRCS += \
../external/rocksdb_source/db/builder.cc \
../external/rocksdb_source/db/c.cc \
../external/rocksdb_source/db/compaction.cc \
../external/rocksdb_source/db/compaction_picker.cc \
../external/rocksdb_source/db/corruption_test.cc \
../external/rocksdb_source/db/db_bench.cc \
../external/rocksdb_source/db/db_filesnapshot.cc \
../external/rocksdb_source/db/db_impl.cc \
../external/rocksdb_source/db/db_impl_readonly.cc \
../external/rocksdb_source/db/db_iter.cc \
../external/rocksdb_source/db/db_stats_logger.cc \
../external/rocksdb_source/db/db_test.cc \
../external/rocksdb_source/db/dbformat.cc \
../external/rocksdb_source/db/dbformat_test.cc \
../external/rocksdb_source/db/deletefile_test.cc \
../external/rocksdb_source/db/filename.cc \
../external/rocksdb_source/db/filename_test.cc \
../external/rocksdb_source/db/log_reader.cc \
../external/rocksdb_source/db/log_test.cc \
../external/rocksdb_source/db/log_writer.cc \
../external/rocksdb_source/db/memtable.cc \
../external/rocksdb_source/db/memtablelist.cc \
../external/rocksdb_source/db/merge_helper.cc \
../external/rocksdb_source/db/merge_operator.cc \
../external/rocksdb_source/db/merge_test.cc \
../external/rocksdb_source/db/perf_context_test.cc \
../external/rocksdb_source/db/prefix_test.cc \
../external/rocksdb_source/db/repair.cc \
../external/rocksdb_source/db/simple_table_db_test.cc \
../external/rocksdb_source/db/skiplist_test.cc \
../external/rocksdb_source/db/table_cache.cc \
../external/rocksdb_source/db/table_properties_collector.cc \
../external/rocksdb_source/db/table_properties_collector_test.cc \
../external/rocksdb_source/db/tailing_iter.cc \
../external/rocksdb_source/db/transaction_log_impl.cc \
../external/rocksdb_source/db/version_edit.cc \
../external/rocksdb_source/db/version_edit_test.cc \
../external/rocksdb_source/db/version_set.cc \
../external/rocksdb_source/db/version_set_test.cc \
../external/rocksdb_source/db/write_batch.cc \
../external/rocksdb_source/db/write_batch_test.cc 

OBJS += \
./external/rocksdb_source/db/builder.o \
./external/rocksdb_source/db/c.o \
./external/rocksdb_source/db/c_test.o \
./external/rocksdb_source/db/compaction.o \
./external/rocksdb_source/db/compaction_picker.o \
./external/rocksdb_source/db/corruption_test.o \
./external/rocksdb_source/db/db_bench.o \
./external/rocksdb_source/db/db_filesnapshot.o \
./external/rocksdb_source/db/db_impl.o \
./external/rocksdb_source/db/db_impl_readonly.o \
./external/rocksdb_source/db/db_iter.o \
./external/rocksdb_source/db/db_stats_logger.o \
./external/rocksdb_source/db/db_test.o \
./external/rocksdb_source/db/dbformat.o \
./external/rocksdb_source/db/dbformat_test.o \
./external/rocksdb_source/db/deletefile_test.o \
./external/rocksdb_source/db/filename.o \
./external/rocksdb_source/db/filename_test.o \
./external/rocksdb_source/db/log_reader.o \
./external/rocksdb_source/db/log_test.o \
./external/rocksdb_source/db/log_writer.o \
./external/rocksdb_source/db/memtable.o \
./external/rocksdb_source/db/memtablelist.o \
./external/rocksdb_source/db/merge_helper.o \
./external/rocksdb_source/db/merge_operator.o \
./external/rocksdb_source/db/merge_test.o \
./external/rocksdb_source/db/perf_context_test.o \
./external/rocksdb_source/db/prefix_test.o \
./external/rocksdb_source/db/repair.o \
./external/rocksdb_source/db/simple_table_db_test.o \
./external/rocksdb_source/db/skiplist_test.o \
./external/rocksdb_source/db/table_cache.o \
./external/rocksdb_source/db/table_properties_collector.o \
./external/rocksdb_source/db/table_properties_collector_test.o \
./external/rocksdb_source/db/tailing_iter.o \
./external/rocksdb_source/db/transaction_log_impl.o \
./external/rocksdb_source/db/version_edit.o \
./external/rocksdb_source/db/version_edit_test.o \
./external/rocksdb_source/db/version_set.o \
./external/rocksdb_source/db/version_set_test.o \
./external/rocksdb_source/db/write_batch.o \
./external/rocksdb_source/db/write_batch_test.o 

C_DEPS += \
./external/rocksdb_source/db/c_test.d 

CC_DEPS += \
./external/rocksdb_source/db/builder.d \
./external/rocksdb_source/db/c.d \
./external/rocksdb_source/db/compaction.d \
./external/rocksdb_source/db/compaction_picker.d \
./external/rocksdb_source/db/corruption_test.d \
./external/rocksdb_source/db/db_bench.d \
./external/rocksdb_source/db/db_filesnapshot.d \
./external/rocksdb_source/db/db_impl.d \
./external/rocksdb_source/db/db_impl_readonly.d \
./external/rocksdb_source/db/db_iter.d \
./external/rocksdb_source/db/db_stats_logger.d \
./external/rocksdb_source/db/db_test.d \
./external/rocksdb_source/db/dbformat.d \
./external/rocksdb_source/db/dbformat_test.d \
./external/rocksdb_source/db/deletefile_test.d \
./external/rocksdb_source/db/filename.d \
./external/rocksdb_source/db/filename_test.d \
./external/rocksdb_source/db/log_reader.d \
./external/rocksdb_source/db/log_test.d \
./external/rocksdb_source/db/log_writer.d \
./external/rocksdb_source/db/memtable.d \
./external/rocksdb_source/db/memtablelist.d \
./external/rocksdb_source/db/merge_helper.d \
./external/rocksdb_source/db/merge_operator.d \
./external/rocksdb_source/db/merge_test.d \
./external/rocksdb_source/db/perf_context_test.d \
./external/rocksdb_source/db/prefix_test.d \
./external/rocksdb_source/db/repair.d \
./external/rocksdb_source/db/simple_table_db_test.d \
./external/rocksdb_source/db/skiplist_test.d \
./external/rocksdb_source/db/table_cache.d \
./external/rocksdb_source/db/table_properties_collector.d \
./external/rocksdb_source/db/table_properties_collector_test.d \
./external/rocksdb_source/db/tailing_iter.d \
./external/rocksdb_source/db/transaction_log_impl.d \
./external/rocksdb_source/db/version_edit.d \
./external/rocksdb_source/db/version_edit_test.d \
./external/rocksdb_source/db/version_set.d \
./external/rocksdb_source/db/version_set_test.d \
./external/rocksdb_source/db/write_batch.d \
./external/rocksdb_source/db/write_batch_test.d 


# Each subdirectory must supply rules for building sources it contributes
external/rocksdb_source/db/%.o: ../external/rocksdb_source/db/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../src -I../external/rocksdb_source/include -I../external/kiss_fft -I../external/boost -I../external/casablanca/Release/include -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

external/rocksdb_source/db/%.o: ../external/rocksdb_source/db/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/aldor/workspace/studia/aipsc/atabox-server/src" -I"/home/aldor/workspace/studia/aipsc/atabox-server/external" -I"/home/aldor/workspace/studia/aipsc/atabox-server/external/rocksdb_source/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


