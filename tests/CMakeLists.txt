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
        recognition/network/RBMTest.cpp
        recognition/network/DBNTest.cpp
        wave/processing/SpectogramTest.cpp wave/analysis/LpccPropertyTest.cpp recognition/FeatureExtractorTest.cpp)

set(ATABOX_TEST_SOURCE ${ATABOX_TEST_SOURCE}
        RunAllTests.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(ATABOX_INC ${ATABOX_INC} ../libs/gmock-1.7.0/include ../libs/gtest-1.7.0/include)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ../libs/gtest-1.7.0/lib/ ../libs/gmock-1.7.0/lib)

endif()

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS} ${ATABOX_INC})
set(ATABOX_TESTS_COVERAGE OFF)
option(ATABOX_TESTS_COVERAGE "Build tests with coverage" OFF)

add_executable(atabox_tests ${ATABOX_TEST_SOURCE})

if(ATABOX_TESTS_COVERAGE)
    set_target_properties(atabox_tests PROPERTIES COMPILE_FLAGS
            "-c -fmessage-length=0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0  -fprofile-arcs -ftest-coverage")
    include(../CMake/CodeCoverage.cmake)
    setup_target_for_coverage_cobertura(coverage tests/build/atabox_tests coverage_report)
endif()

target_link_libraries(atabox_tests  atabox ${ATABOX_LIBS} gtest gmock )
