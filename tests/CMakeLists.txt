cmake_minimum_required (VERSION 3.0)
set(ATABOX_TEST_SOURCE
    api/AtaboxApiTest.cpp
    api/casablancaMocks.cpp
    api/casablancaMocks.h
    dataproviders/RocksdbProviderTest.cpp
    recognition/PropertiesComparatorTest.cpp
    utils/execution_policyTest.cpp
    utils/jsonextendTest.cpp
    wave/analysis/AmplitudePropertyTest.cpp
    wave/analysis/AverageValuePropertyTest.cpp
    wave/analysis/FirstSampleValueTestingProperty.h
    wave/analysis/LengthPropertyTest.cpp
    wave/analysis/MfccPropertyTest.cpp
    wave/analysis/PercentageAbovePropertyTest.cpp
    wave/analysis/SamplesAnalizatorTest.cpp
    wave/analysis/SpectrumPropertyTest.cpp
    wave/analysis/WhereIsAmplitudePropertyTest.cpp
    wave/analysis/ZeroCrossingsPropertyTest.cpp
    wave/processing/postprocessing/FastFourierTransformFilterTest.cpp
    wave/processing/postprocessing/HannWindowFilterTest.cpp
    wave/processing/preprocessing/ConstantAddingTestFilter.h
    wave/processing/preprocessing/NormalizingFilterTest.cpp
    wave/processing/preprocessing/SilenceCuttingFilterTest.cpp
    wave/processing/ProcessorTest.cpp
    wave/PreprocessorTest.cpp
    wave/ProcessAndAnalyzeTest.cpp
    wave/SamplesMock.h
    wave/SamplesTest.cpp
    wave/WaveFileMock.cpp
    wave/WaveFileMock.h
    wave/WaveFileTest.cpp
    wave/WaveUtilsTest.cpp
        recognition/network/RBMTest.cpp)

set(ATABOX_TEST_SOURCE ${ATABOX_TEST_SOURCE}
    RunAllTests.cpp)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS} ${ATABOX_INC})
option(ATABOX_TESTS_COVERAGE "Build tests with coverage" ON)
if(ATABOX_TESTS_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wshadow -fprofile-arcs -ftest-coverage")
    include(../CMake/CodeCoverage.cmake)
    setup_target_for_coverage_cobertura(coverage atabox_test coverage_report)
endif()

    add_executable(atabox_tests ${ATABOX_TEST_SOURCE})
set_target_properties(atabox_tests PROPERTIES COMPILE_FLAGS
    "-c -fmessage-length=0 -fprofile-arcs -ftest-coverage")
target_link_libraries(atabox_tests  atabox ${ATABOX_LIBS} gtest gmock gcov)
