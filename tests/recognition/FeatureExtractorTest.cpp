//
// Created by aldor on 04.07.16.
//

#include <cnpy.h>
#include <thread>
#include <ctpl_stl.h>


#include "recognition/FeatureExtractor.h"
#include "utils/functions.h"
#include "wave/WaveFile.h"
// #include "SamplesAnalyzer.h"
#include "wave/Samples.h"
#undef U //XXX: potrzebne zeby sie kompilowala z casablanca
#include <boost/filesystem.hpp>
#include <aquila/transform/Dft.h>
#include <dataproviders/RocksdbProvider.h>

#ifndef GTEST_H_
#define GTEST_H_
#include "gtest/gtest.h"
#endif

namespace fs = boost::filesystem;

class FeatureExtractorTest: public ::testing::Test {

};

const unsigned int POOL_SIZE = 13;
TEST_F(FeatureExtractorTest, extract_DFT) {


    ctpl::thread_pool pool{POOL_SIZE};
    std::mutex mylock;
    RocksdbProvider<std::string, std::vector<std::vector<double>>> db("/tmp/dft");
    std::map<std::string, std::vector<std::vector<double>>> filesMap;

    std::vector<std::string> dzienDobryFiles{"./tests/wave/waveFiles/marcin/dzienDobry", "./tests/wave/waveFiles/tomek2/dzienDobry", "./tests/wave/waveFiles/tata/dzienDobry",
        "./tests/wave/waveFiles/mama/dzienDobry", "./tests/wave/waveFiles/babcia/dzienDobry"
    };
    std::vector<std::string> proszeFiles{"./tests/wave/waveFiles/marcin/prosze", "./tests/wave/waveFiles/tomek2/prosze", "./tests/wave/waveFiles/tata/prosze",
        "./tests/wave/waveFiles/mama/prosze", "./tests/wave/waveFiles/babcia/prosze"
    };

    std::string filePrefix[] = {"prosze", "prosze"};
    size_t p = 0;
    std::vector<std::vector<std::string>> filesList{proszeFiles};
    std::vector<std::vector<double>> baseLabels = {
            {1, 0, 0, 0, 0}, // marcin
            {0, 0, 1, 0, 0}, // tomek
            {0, 1, 0, 0 , 0}, // tata
            {0, 0, 0, 1 , 0}, // mama
            {0, 0, 0, 0 , 1}  // babcia
    };

    for (std::vector<std::string> filesDir: filesList) {
        std::vector<std::vector<double>> trainData;
        std::vector<std::vector<double>> labels;
        for (int x = 0; x < filesDir.size(); ++x) {
            fs::path marcinSamples(filesDir[x]);
            fs::recursive_directory_iterator end;

            for (fs::recursive_directory_iterator i(marcinSamples); i != end; ++i) {
                const fs::path cp = (*i);
                std::string filePath = cp.string();
                if (!boost::ends_with(filePath, ".wav")) {
                    std::cout << "Error not wav file " << filePath;
                    continue;
                }

                std::vector<std::vector<double>> trainTmp;
                std::vector<double> tmpLabel;
                if (db.get(filePath, trainTmp)) {
                    if (trainTmp.size() > 0) {
                        std::cout << "Data for " << filePath << " " << trainTmp.size() << " " << trainTmp.begin()->size() <<
                        '\n';
                        trainData.insert(trainData.end(), trainTmp.begin(), trainTmp.end());
                        for (int t = 0, len = trainTmp.size(); t < len; ++t) {
                            labels.push_back(baseLabels[x]);
                        }
                        continue;
                    }
                }

                pool.push([&trainData, &labels, &mylock, &baseLabels, x, filePath, &filesMap, &db] (int tid) {
                    Samples samples;
                    std::cout << "Now " << filePath << " tid =  "<< tid << '\n';

                    try {
                        samples = (Samples::createSample(WaveFile(filePath.c_str())));
                    } catch (std::exception e) {
                        std::cout << "Error reading file " << filePath << " " << e.what();
                        return;
                    }

                    uint16_t samplesInFrame = static_cast<uint16_t>(std::ceil(
                            samples.getNumberOfSamples() / 100));
                    Aquila::FramesCollection frames(samples, samplesInFrame);
                    std::vector<std::vector<double>> dbData;
                    if (frames.count() == 0) {
                        std::cerr<< "Error no frames!";
                        return;
                    }

                   for (auto it = frames.begin(); it != frames.end(); ++it) {
                       const double * frame = it->toArray();
                       size_t len = it->length();
                      Aquila::Dft dft(len);
                      Aquila::SpectrumType dftTrans = dft.fft(frame);
                      std::vector<double> trans;
                      trans.reserve(dftTrans.size());

                    std::transform(std::begin(dftTrans), std::end(dftTrans), std::back_inserter(trans),
                                     [](std::complex<double> x) {
                                         double abs = std::abs(x);

                                         if (abs != abs) {
                                             return 0.0;
                                         } else {
                                             return abs;
                                         }
                                     });

                       // mean, std, variane,

                       std::tuple<double, double, double> stats = calculateStatictic(trans);
                       /* if (std::get<0>(stats) > 5e10) { */
                       /*     LOG(warning) << "Skip data for filename " << filePath; */
                       /*     continue; */
                       /* } */

                      mylock.lock();
    //                   // std::cout << " trans dft size "<< trans.size() << " dft sie" << dftTrans.size() << " ";
                      trainData.push_back(trans);
                       dbData.push_back(trans);
                      labels.push_back(baseLabels[x]);
                      filesMap[filePath].push_back(trans);
                      /* std::cout << "Trans " << trans.size() << '\n'; */
                      mylock.unlock();
                   }
                    if (dbData.size() > 0)
                        db.put(filePath, dbData);
                    std::cout << "End of " << filePath <<" tid = " << tid << '\n';
                 });

            }
        }

        pool.interrupt();
        std::cout << "End of processing train data" << trainData.size() << "labels " << labels.size() << '\n';
        if (trainData.size() == 0) {
            std::cerr <<"No data";
            return;
        }
        size_t max = normalizeArray<std::vector<std::vector<double>>, std::vector<double>>(trainData, 0, labels);
        // normalizeArray<std::vector<std::vector<double>>, std::vector<double>>(labels, max);
        std::vector<int> indexes;
        indexes.reserve(trainData.size());
        for (int i = 0; i < trainData.size(); ++i)
            indexes.push_back(i);
        std::random_shuffle(indexes.begin(), indexes.end());
        reorder(indexes.begin(), indexes.end(), trainData.begin());
        reorder(indexes.begin(), indexes.end(), labels.begin());
        std::cout << "End of normalize train data" << trainData.size() << max<< '\n';


        std::string trainName = std::string("train-dft-") + filePrefix[p] + std::string(".npy");
        std::string labelsName = std::string("labels-dft-") + filePrefix[p++] + std::string(".npy");
        save_2d_npy(trainName.c_str(), trainData);
        save_2d_npy(labelsName.c_str(), labels);
    }
}

TEST_F(FeatureExtractorTest, extract_MFCC) {
    FeatureExtractor cos;
    cos.init();

    ctpl::thread_pool pool{POOL_SIZE};
    std::vector<std::vector<double>> trainData;
    std::vector<std::vector<double>> labels;
    std::mutex mylock;
    RocksdbProvider<std::string, std::vector<double>> db("/tmp/mfcc");
    std::map<std::string, std::vector<std::vector<double>>> filesMap;

    std::vector<std::string> dzienDobryFiles{"./tests/wave/waveFiles/marcin/dzienDobry", "./tests/wave/waveFiles/tomek2/dzienDobry", "./tests/wave/waveFiles/tata/dzienDobry",
        "./tests/wave/waveFiles/mama/dzienDobry", "./tests/wave/waveFiles/babcia/dzienDobry"
    };
    std::vector<std::string> proszeFiles{"./tests/wave/waveFiles/marcin/prosze", "./tests/wave/waveFiles/tomek2/prosze", "./tests/wave/waveFiles/tata/prosze",
        "./tests/wave/waveFiles/mama/prosze", "./tests/wave/waveFiles/babcia/prosze"
    };

    std::string filePrefix[] = {"dd", "prosze"};
    size_t p = 0;
    std::vector<std::vector<std::string>> filesList{dzienDobryFiles, proszeFiles};
    std::vector<std::vector<double>> baseLabels = {
            {1, 0, 0, 0, 0}, // marcin
            {0, 0, 1, 0, 0}, // tomek
            {0, 1, 0, 0 , 0}, // tata
            {0, 0, 0, 1 , 0}, // mama
            {0, 0, 0, 0 , 1}  // babcia
    };


    for (std::vector<std::string> filesDir: filesList) {

        for (int x = 0; x < filesDir.size(); ++x) {
            fs::path marcinSamples(filesDir[x]);
            fs::recursive_directory_iterator end;

            for (fs::recursive_directory_iterator i(marcinSamples); i != end; ++i) {
                const fs::path cp = (*i);
                std::string filePath = cp.string();
                if (!boost::ends_with(filePath, ".wav")) {
                    std::cout << "Error not wav file " << filePath;
                    continue;
                }

                std::vector<double> trainTmp;
                if (db.get(filePath, trainTmp)) {
                    if (trainTmp.size() > 0) {
                        std::cout << "Data for " << filePath << " " << trainTmp.size() << '\n';
                        trainData.push_back(trainTmp);
                        labels.push_back(baseLabels[x]);
                        continue;
                    }
                }

                pool.push([&trainData, &labels, &mylock, &baseLabels, x, filePath, &filesMap, &db, &cos] (int tid) {
                    Samples samples;
                    std::cout << "Now " << filePath << "tid "<< tid << '\n';

                    try {
                        samples = (Samples::createSample(WaveFile(filePath.c_str())));
                    } catch (std::exception e) {
                        std::cout << "Error reading file " << filePath << " " << e.what();
                        return;
                    }

                    auto trans = cos.getSummaryVector(samples);

                    mylock.lock();
                    trainData.push_back(trans);
                    labels.push_back(baseLabels[x]);
                    filesMap[filePath].push_back(trans);
                    db.put(filePath, trans);
                    mylock.unlock();
                    std::cout << "End of " << filePath << '\n';
                 });

            }
        }

        pool.interrupt();
        std::cout << "End of processing train data" << trainData.size() << "labels " << labels.size() << '\n';
        if (trainData.size() == 0) {
            std::cerr <<"No data";
            return;
        }
        size_t max = normalizeArray<std::vector<std::vector<double>>, std::vector<double>>(trainData, 0, labels);
        // normalizeArray<std::vector<std::vector<double>>, std::vector<double>>(labels, max);
        std::vector<int> indexes;
        indexes.reserve(trainData.size());
        for (int i = 0; i < trainData.size(); ++i)
            indexes.push_back(i);
        std::random_shuffle(indexes.begin(), indexes.end());
        reorder(indexes.begin(), indexes.end(), trainData.begin());
        reorder(indexes.begin(), indexes.end(), labels.begin());
        std::cout << "End of normalize train data" << trainData.size() << max<< '\n';

        std::string trainName = std::string("train-mfcc-all-sound") + filePrefix[p] + std::string(".npy");
        std::string labelsName = std::string("labels-mfcc-all-sound") + filePrefix[p++] + std::string(".npy");
        save_2d_npy(trainName.c_str(), trainData);
        save_2d_npy(labelsName.c_str(), labels);
    }
}

TEST_F(FeatureExtractorTest, DISABLED_extract) {
    FeatureExtractor cos;
    cos.init();

    std::vector<std::vector<double>> trainData;
    std::vector<std::vector<double>> vData;
    std::vector<std::vector<double>> labels;
    std::vector<std::vector<double>> vLabels;
    std::mutex mylock;
    std::vector<std::thread> workers;
    const unsigned int POOL_SIZE = 3;

    ctpl::thread_pool pool{POOL_SIZE};

    fs::path marcinSamples("./tests/wave/waveFiles/marcin/");
    fs::recursive_directory_iterator end;

    for (fs::recursive_directory_iterator i(marcinSamples); i != end; ++i) {
        const fs::path cp = (*i);
        std::string filePath = cp.string();
        pool.push(([&trainData, &labels, &mylock, filePath, &cos](int tid) {
            auto d = cos.getSummaryVector(Samples::createSample(WaveFile(filePath.c_str())));
            mylock.lock();
            for (int f = 0; f < 3; f++) {
                trainData.push_back(d);
                labels.push_back({1, 0, 0});

            }
            mylock.unlock();

        }));
    }


    fs::path tomekSamples("./tests/wave/waveFiles/tomek/");

    for (fs::recursive_directory_iterator i(tomekSamples); i != end; ++i) {
        const fs::path cp = (*i);
        std::string filePath = cp.string();
        pool.push(([&trainData, &labels, &mylock, filePath, &cos](int tid) {
            auto d = cos.getSummaryVector(Samples::createSample(WaveFile(filePath.c_str())));
            mylock.lock();
            for (int f = 0; f < 3; f++) {
                trainData.push_back(d);
                labels.push_back({0, 0, 1});
            }
            mylock.unlock();
        }));
    }

    std::cout << "Thread Poll " << pool.n_idle();
    /*while (pool.n_idle() != POOL_SIZE) {
        //std::cout << " Poll " << pool.n_idle();
    };
    */
    pool.interrupt();

    std::cout << "train data size " << trainData.size();

    size_t i =0, j = 0;
    size_t counter = 0;
   for (auto &a: trainData) {
        i++;
        j = 0;
        counter =0 ;
        for (auto &b: a) {
            j++;
            if (b != b) {
                b = 1.0;
                // std::cout << "NAM !!!\n";
            }
            if (b < 1e-5) {
                counter++;
                // std::cout << "i = " << i << " j = " << j << ' ' << b << '\n';
            }
        }
        std::cout << "i = " << i << " counter = " << counter << '\n';
    }

    for (auto &a: trainData) {
        for (auto &b: a) {
            if (b != b) {
                b = 1.0;
                std::cout << "NAM !!!";
            }
        }
    }


    for (auto &a: vData) {
        for (auto &b: a) {
            if (b != b) {
                b = 1.0;
                std::cout << "NAM !!!";
            }
        }
    }
    size_t max = normalizeArray<std::vector<std::vector<double>>, std::vector<double>>(trainData, 0, labels);

    save_2d_npy("train2.npy", trainData);
    save_2d_npy("labels2.npy", labels);

    /*Samples mama{WaveFile("./tests/wave/waveFiles/dziendobryMama.wav")};
    Samples babcia{WaveFile("./tests/wave/waveFiles/dziendobryBabcia.wav")};

    std::vector<double> mamaRealVector = cos.getSummaryVector(mama);

    save_1d_npy("mama.npy", mamaRealVector);

    auto babciaRV = cos.getSummaryVector(babcia);
    save_1d_npy("babcia.npy", babciaRV);

    auto proszeTomek = cos.getSummaryVector(Samples::createSample(WaveFile("./tests/wave/waveFiles/proszeTomek.wav")));
    save_1d_npy("tomek-prosze.npy", proszeTomek);

    auto proszeMama = cos.getSummaryVector(Samples::createSample(WaveFile("./tests/wave/waveFiles/proszeMama.wav")));
    save_1d_npy("mama-prosze.npy", proszeTomek);

    auto proszeBabcia = cos.getSummaryVector(Samples::createSample(WaveFile("./tests/wave/waveFiles/proszeBabcia.wav")));
    save_1d_npy("babcia-prosze.npy", proszeBabcia);*/
}
