cmake_minimum_required(VERSION 2.8.11)
project(atabox-server CXX)

set(atabox-server_VERSION_MAJOR 1)
set(atabox-server_VERSION_MINOR 0)
set(atabox-server_VERSION_PATCH 0)
set(atabox-server_VERSION_SUFFIX "-dev")
set(atabox-server_VERSION "${atabox-server_VERSION_MAJOR}.${atabox-server_VERSION_MINOR}.${atabox-server_VERSION_PATCH}${atabox-server_VERSION_SUFFIX}")


################################################################################
#
# Build options
#
################################################################################

option(atabox-server_BUILD_EXAMPLES "Build example programs?" ON)
option(atabox-server_BUILD_TESTS "Build test programs?" ON)

################################################################################
#
# Dependencies
#
################################################################################

# libraries bundled with atabox-server
add_subdirectory(external)
set(atabox-server_LIBRARIES_TO_LINK_WITH )

# additional CMake modules
set(CMAKE_MODULE_PATH "${atabox-server_SOURCE_DIR}/cmake")

# SFML - if available
#set(SFML_STATIC true)
find_package(SFML COMPONENTS System Audio)
if(SFML_FOUND)
    message("SFML was found, wrappers and examples using SFML will be built.")
    include_directories(${SFML_INCLUDE_DIR})
    list(APPEND atabox-server_LIBRARIES_TO_LINK_WITH ${SFML_LIBRARY})
else()
    message(WARNING "SFML was not found, wrappers and examples using SFML will not be built.")
endif()


################################################################################
#
# atabox-server sources
#
################################################################################

# library headers
set(atabox-server_HEADERS
    aquila/aquila.h
    aquila/global.h
    aquila/functions.h
    aquila/Exceptions.h
    aquila/source.h
    aquila/tools.h
    aquila/transform.h
    aquila/filter.h
    aquila/ml.h
    aquila/filter/MelFilter.h
    aquila/filter/MelFilterBank.h
    aquila/ml/DtwPoint.h
    aquila/ml/Dtw.h
    aquila/source/SignalSource.h
    aquila/source/Frame.h
    aquila/source/FramesCollection.h
    aquila/source/PlainTextFile.h
    aquila/source/RawPcmFile.h
    aquila/source/WaveFile.h
    aquila/source/WaveFileHandler.h
    aquila/source/generator/Generator.h
    aquila/source/generator/SineGenerator.h
    aquila/source/generator/SquareGenerator.h
    aquila/source/generator/TriangleGenerator.h
    aquila/source/generator/PinkNoiseGenerator.h
    aquila/source/generator/WhiteNoiseGenerator.h
    aquila/source/window/BarlettWindow.h
    aquila/source/window/BlackmanWindow.h
    aquila/source/window/FlattopWindow.h
    aquila/source/window/GaussianWindow.h
    aquila/source/window/HammingWindow.h
    aquila/source/window/HannWindow.h
    aquila/source/window/RectangularWindow.h
    aquila/transform/Fft.h
    aquila/transform/Dft.h
    aquila/transform/atabox-serverFft.h
    aquila/transform/OouraFft.h
    aquila/transform/FftFactory.h
    aquila/transform/Dct.h
    aquila/transform/Mfcc.h
    aquila/transform/Spectrogram.h
    aquila/tools/TextPlot.h
)

# library sources
set(atabox-server_SOURCES
    aquila/filter/MelFilter.cpp
    aquila/filter/MelFilterBank.cpp
    aquila/ml/Dtw.cpp
    aquila/source/SignalSource.cpp
    aquila/source/Frame.cpp
    aquila/source/FramesCollection.cpp
    aquila/source/PlainTextFile.cpp
    aquila/source/WaveFile.cpp
    aquila/source/WaveFileHandler.cpp
    aquila/source/generator/Generator.cpp
    aquila/source/generator/SineGenerator.cpp
    aquila/source/generator/SquareGenerator.cpp
    aquila/source/generator/TriangleGenerator.cpp
    aquila/source/generator/PinkNoiseGenerator.cpp
    aquila/source/generator/WhiteNoiseGenerator.cpp
    aquila/source/window/BarlettWindow.cpp
    aquila/source/window/BlackmanWindow.cpp
    aquila/source/window/FlattopWindow.cpp
    aquila/source/window/GaussianWindow.cpp
    aquila/source/window/HammingWindow.cpp
    aquila/source/window/HannWindow.cpp
    aquila/transform/Dft.cpp
    aquila/transform/atabox-serverFft.cpp
    aquila/transform/OouraFft.cpp
    aquila/transform/FftFactory.cpp
    aquila/transform/Dct.cpp
    aquila/transform/Mfcc.cpp
    aquila/transform/Spectrogram.cpp
    aquila/tools/TextPlot.cpp
)

# SFML wrappers
if(SFML_FOUND)
    list(APPEND atabox-server_HEADERS
        aquila/synth.h
        aquila/wrappers/SoundBufferAdapter.h
        aquila/synth/Synthesizer.h
        aquila/synth/KarplusStrongSynthesizer.h
        aquila/synth/SineSynthesizer.h
    )
    list(APPEND atabox-server_SOURCES
        aquila/wrappers/SoundBufferAdapter.cpp
        aquila/synth/Synthesizer.cpp
        aquila/synth/KarplusStrongSynthesizer.cpp
        aquila/synth/SineSynthesizer.cpp
    )
endif()


################################################################################
#
# Compiler-specific workarounds
#
################################################################################

if(MSVC)
    # disable "strncpy is deprecated" warning and enable math constants
    add_definitions("/D_CRT_NONSTDC_NO_DEPRECATE /D_USE_MATH_DEFINES")
endif()


if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    if(APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wcast-qual -Wcast-align -Wno-unused-parameter -Wmissing-include-dirs -Wpointer-arith -Wredundant-decls -Wshadow -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    setup_target_for_coverage(coverage aquila_test htmlcov)
endif()


################################################################################
#
# Building and linking
#
################################################################################

# main atabox-server library
add_library(atabox-server ${atabox-server_HEADERS} ${atabox-server_SOURCES})

# linking with extra libs
target_link_libraries(atabox-server ${atabox-server_LIBRARIES_TO_LINK_WITH})

# examples
if(atabox-server_BUILD_EXAMPLES)
    add_custom_target(examples)
    add_subdirectory(examples)
endif()

#tests
if(atabox-server_BUILD_TESTS)
    enable_testing()
    set(UNITTESTPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/unittestpp/")
    add_subdirectory(tests)
endif()

################################################################################
#
# Documentation
#
################################################################################

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        IMMEDIATE @ONLY
    )
    add_custom_target(docs
        "${DOXYGEN_EXECUTABLE}"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    )
else()
    message(WARNING "Doxygen not found, documentation will not be built")
endif()


################################################################################
#
# Installing
#
################################################################################

# install the binaries and include files
install(TARGETS atabox-server
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY aquila/ DESTINATION include/aquila FILES_MATCHING PATTERN "*.h")
install(FILES CHANGELOG LICENSE README.md DESTINATION share/aquila)


################################################################################
#
# Uninstalling
#
################################################################################

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
)
