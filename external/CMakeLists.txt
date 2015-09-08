cmake_minimum_required (VERSION 3.0)
# aquila
set(Aquila_BUILD_EXAMPLES OFF)
set(Aquila_BUILD_TESTS OFF)
add_subdirectory(aquila)

# casablanca
set(BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS ON)
set(BUILD_SAMPLES OFF)
add_subdirectory(casablanca/Release)

#rocksdb

