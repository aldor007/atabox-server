cmake_minimum_required(VERSION 2.8.11)
project(atabox_server CXX)

set(atabox_server_VERSION_MAJOR 1)
set(atabox_server_VERSION_MINOR 0)
set(atabox_server_VERSION_PATCH 0)
set(atabox_server_VERSION_SUFFIX "-dev")
set(atabox_server_VERSION "${atabox_server_VERSION_MAJOR}.${atabox_server_VERSION_MINOR}.${atabox_server_VERSION_PATCH}${atabox_server_VERSION_SUFFIX}")



################################################################################
#
# Dependencies
#
################################################################################

# libraries bundled with atabox_server
add_subdirectory(external)
set(atabox_server_LIBRARIES_TO_LINK_WITH )

# additional CMake modules
set(CMAKE_MODULE_PATH "${atabox_server_SOURCE_DIR}/cmake")


################################################################################
#
# atabox_server sources
#
################################################################################

# library headers
set(atabox_server_HEADERS

)

# library sources
set(atabox_server_SOURCES
)


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
    setup_target_for_coverage(coverage atabox_server_test htmlcov)
endif()


################################################################################
#
# Building and linking
#
################################################################################

# main atabox_server library
add_library(atabox_server ${atabox_server_HEADERS} ${atabox_server_SOURCES})

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/external/aquila/aquila/"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/casablanca/Release/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/rocksdb_source/include/"
)


# linking with extra libs
target_link_libraries(atabox_server ${atabox_server_LIBRARIES_TO_LINK_WITH})


#tests
if(atabox_server_BUILD_TESTS)
    enable_testing()
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
install(TARGETS atabox_server
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

