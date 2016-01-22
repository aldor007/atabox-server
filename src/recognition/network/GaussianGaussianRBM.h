//
// Created by aldor on 22.01.16.
//

#ifndef ATABOX_SERVER_GAUSSIANGAUSSIANRBM_H_H
#define ATABOX_SERVER_GAUSSIANGAUSSIANRBM_H_H

#include <shark/Unsupervised/RBM/RBM.h>
#include <shark/Unsupervised/RBM/Energy.h>

#include <shark/Unsupervised/RBM/Neuronlayers/GaussianLayer.h>
#include <shark/Unsupervised/RBM/Sampling/GibbsOperator.h>
#include <shark/Unsupervised/RBM/Sampling/TemperedMarkovChain.h>
#include <shark/Unsupervised/RBM/Sampling/MarkovChain.h>

#include <shark/Unsupervised/RBM/GradientApproximations/ContrastiveDivergence.h>
#include <shark/Unsupervised/RBM/GradientApproximations/MultiChainApproximator.h>
#include <shark/Unsupervised/RBM/GradientApproximations/SingleChainApproximator.h>
#include <shark/Rng/GlobalRng.h>
namespace shark{

typedef RBM<GaussianLayer,GaussianLayer, Rng::rng_type> GaussianGaussianRBM;
typedef GibbsOperator<GaussianGaussianRBM> GaussianGaussianGibbsOperator;
typedef MarkovChain<GaussianGaussianGibbsOperator> GaussianGaussianGibbsChain;
typedef TemperedMarkovChain<GaussianGaussianGibbsOperator> GaussianGaussianPTChain;

typedef MultiChainApproximator<GaussianGaussianGibbsChain> GaussianGaussianPCD;
typedef ContrastiveDivergence<GaussianGaussianGibbsOperator> GaussianGaussianCD;
typedef SingleChainApproximator<GaussianGaussianPTChain> GaussianGaussianParallelTempering;
}


#endif //ATABOX_SERVER_GAUSSIANGAUSSIANRBM_H_H
