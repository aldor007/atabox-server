cmake_minimum_required (VERSION 3.0)

# include(../CMake/FindOpenMP.cmake)
# aquila
set(Aquila_BUILD_EXAMPLES OFF)
set(Aquila_BUILD_TESTS OFF)
add_subdirectory(aquila)

# casablanca
set(BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS ON)
set(BUILD_SAMPLES OFF)
add_subdirectory(casablanca/Release)

#shark
set(BUILD_EXAMPLES OFF)
set(ENABLE_ACCELERATE OFF)
set(ENABLE_ATLAS OFF)

# FindOpenMP()
# if(OPENMP_FOUND)
#    set(ENABLE_OPENMP OFF)
# endif()
set(ENABLE_OPENMP ON)
set(SHARK_USE_OPENMP OFF)
set(BUILD_TESTING OFF)
#include(shark/UseShark.cmake)
add_subdirectory(shark)

add_subdirectory(cnpy)
