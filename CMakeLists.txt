# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required (VERSION 3.0)
project(atabox_server)
set(atabox_server_VERSION_MAJOR 0)
set(atabox_server_VERSION_MINOR 5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")
option(ATABOX_TEST "Build all tests." ON) # Makes boolean 'test' available.


set(ROCKSDB_ROOT external/rocksdb_source)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")


# If no explicit compiler override and clang++ exists, prefer clang.
#find_file(CLANGXX_EXISTS "clang++")
#if(DEFINED ENV{CC})
#    set(CMAKE_C_COMPILER "$ENV{CC}")
#    message("Overriding C compiler from clang to $ENV{CC}")
#elseif(CLANGXX_EXISTS)
#    set(CMAKE_C_COMPILER "clang")
#endif()
#if(DEFINED ENV{CXX})
#    set(CMAKE_CXX_COMPILER "$ENV{CXX}")
#    message("Overriding CXX compiler from clang++ to $ENV{CXX}")
#elseif(CLANGXX_EXISTS)
#    set(CMAKE_CXX_COMPILER "clang++")
#endif()

# external libs
add_subdirectory(external)

add_definitions(-DBOOST_LOG_DYN_LINK=yes)

find_package(Boost REQUIRED COMPONENTS random chrono system thread locale regex filesystem program_options log )
#IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    set(ATABOX_LIBS ${ATABOX_LIBS} boost_log-mt boost_thread-mt)
#endif()
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(ATABOX_LIBS "${Boost_LIBRARIES}")
endif()
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(PUBLIC my_app "-pthread")
endif()
#if(CMAKE_THREAD_LIBS_INIT)
#    set(ATABOX_LIBS "${CMAKE_THREAD_LIBS_INIT}")
#endif()
include(CMake/Findrocksdb.cmake)
if(ROCKSDB_FOUND)
    message("Found rocksdb")
endif()
set(ATABOX_LIBS "${ATABOX_LIBS}" ${ROCKSDB_LIBRARIES} Aquila cpprest)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(ATABOX_LIBS ${ATABOX_LIBS} boost_log-mt boost_thread-mt)
endif()

set(ATABOX_INC
    src/
    external/aquila/aquila
    external/casablanca/Release/src
    external/rocksdb_source/include
)

include_directories(${ATABOX_INC})

set(ATABOX_SOURCES
    src/api/AtaboxApi.cpp
    src/api/AtaboxApi.h
    src/api/BaseApi.h
    src/dataproviders/BaseDataProvider.h
    src/dataproviders/FileDataProvider.cpp
    src/dataproviders/FileDataProvider.h
    src/dataproviders/RocksdbProvider.h
    src/recognition/network/activation_functions.h
    src/recognition/network/Batch.h
    src/recognition/network/DeepBeliefNet.h
    src/recognition/network/LRBM.h
    src/recognition/network/RBM.h
    src/recognition/ProcessAndAnalyze.cpp
    src/recognition/ProcessAndAnalyze.h
    src/recognition/PropertiesComparator.cpp
    src/recognition/PropertiesComparator.h
    src/runner/Runner.cpp
    src/runner/Runner.h
    src/utils/atabox_log.cpp
    src/utils/atabox_log.h
    src/utils/ataboxexception.h
    src/utils/ataboxexception.cpp
    src/utils/execution_policy.h
    src/utils/functions.h
    src/utils/jsonextend.h
    src/utils/LightVector.h
    src/wave/analysis/AmplitudeProperty.h
    src/wave/analysis/AverageValueProperty.h
    src/wave/analysis/LengthProperty.h
    src/wave/analysis/MfccProperty.h
    src/wave/analysis/PercentageAboveProperty.h
    src/wave/analysis/Property.h
    src/wave/analysis/PropertyWithRange.h
    src/wave/analysis/SamplesAnalizator.cpp
    src/wave/analysis/SamplesAnalizator.h
    src/wave/analysis/SpectrumProperty.h
    src/wave/analysis/WhereIsAmplitudeProperty.h
    src/wave/analysis/ZeroCrossingsProperty.h
    src/wave/processing/postprocessing/FastFourierTransformFilter.h
    src/wave/processing/postprocessing/HannWindowFilter.h
    src/wave/processing/preprocessing/NormalizingFilter.h
    src/wave/processing/preprocessing/SilenceCuttingFilter.h
    src/wave/processing/Filter.h
    src/wave/processing/Processor.cpp
    src/wave/processing/Processor.h
    src/wave/Samples.cpp
    src/wave/Samples.h
    src/wave/WaveFile.cpp
    src/wave/WaveFile.h
    src/wave/WaveUtils.cpp
    src/wave/WaveUtils.h
)
# main atabox library
add_library(atabox STATIC ${ATABOX_SOURCES})

set(ATABOX_SERVER_FILES
    ${ATABOX_SOURCES}
    src/main.cpp
)
if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR IOS)
    message("-- Setting clang options")

    set(WARNINGS "-Wall -Wextra -Wcast-qual -Wconversion -Wformat=2 -Winit-self -Winvalid-pch -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wredundant-decls")
    set(OSX_SUPPRESSIONS "-Wno-overloaded-virtual -Wno-sign-conversion -Wno-deprecated -Wno-unknown-pragmas -Wno-reorder -Wno-char-subscripts -Wno-switch -Wno-unused-parameter -Wno-unused-variable -Wno-deprecated -Wno-unused-value -Wno-unknown-warning-option -Wno-return-type-c-linkage -Wno-unused-function -Wno-sign-compare -Wno-shorten-64-to-32 -Wno-reorder")
    set(WARNINGS "${WARNINGS} ${OSX_SUPPRESSIONS}")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wno-return-type-c-linkage -Wno-unneeded-internal-declaration")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-strict-aliasing")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("-- Setting gcc options")

    set(WARNINGS "-Wall -Wextra -Wunused-parameter -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winit-self -Winvalid-pch -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wredundant-decls -Wunreachable-code")
    set(LINUX_SUPPRESSIONS "-Wno-deprecated -Wno-unknown-pragmas -Wno-reorder -Wno-unused-function -Wno-char-subscripts -Wno-switch -Wno-unused-but-set-parameter -Wno-unused-value -Wno-unused-local-typedefs")

    set(WARNINGS "${WARNINGS} ${LINUX_SUPPRESSIONS}")
    set(LD_FLAGS "${LD_FLAGS} -Wl,-z,defs")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-strict-aliasing")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message("-- Setting msvc options")
    set(WARNINGS)
else()
    message("-- Unknown compiler, success is doubtful.")
    message("CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
endif()

#IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    set(ATABOX_LIBS ${ATABOX_LIBS} boost_thread)
#else()
#    set(ATABOX_LIBS ${ATABOX_LIBS} boost_thread)
#endif()
add_executable(atabox_server ${ATABOX_SERVER_FILES})
target_link_libraries(atabox_server ${ATABOX_LIBS})
#if(ATABOX_TEST)
    message("Bulding tests")
    include(CMake/FindGMock.cmake)
    add_subdirectory(tests)
#endif()

