# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required (VERSION 3.0)
project(atabox_server)
set(atabox_server_VERSION_MAJOR 0)
set(atabox_server_VERSION_MINOR 5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# external libs
add_subdirectory(external)

find_package(Boost REQUIRED COMPONENTS random chrono system thread locale regex filesystem program_options)

set(SOURCE_FILES
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
    src/main.cpp
)
include_directories(${PROJECT_SRC_DIR}/src)
add_executable(atabox_server ${SOURCE_FILES})