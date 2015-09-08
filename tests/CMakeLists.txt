cmake_minimum_required (VERSION 3.0)
project(atabox_tests)
set(ATABOX_TEST_SOURCE
    api/AtaboxApiTest.cpp
    api/casablancaMocks.cpp
    api/casablancaMocks.h
    dataproviders/RocksdbProviderTest.cpp
    recognition/PropertiesComparatorTest.cpp
    runner/RunnerTest.cpp
    tuningRunners/VimWaveRunner.cpp
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
    RunAllTests.cpp
)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS} ${ATABOX_INC})

add_executable(atabox_tests ${ATABOX_TEST_SOURCE})
target_link_libraries(atabox_tests ${ATABOX_LIBS} atabox gtest gmock)
