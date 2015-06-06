/*
Copyright (c) 2013, jackdeng@gmail.com
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Algorithm is based on matlab code from http://www.cs.toronto.edu/~hinton/MatlabForSciencePaper.html
/*
Training a deep autoencoder or a classifier 
on MNIST digits
Code provided by Ruslan Salakhutdinov and Geoff Hinton 
Permission is granted for anyone to copy, use, modify, or distribute this program and accompanying programs and documents for any purpose, provided this copyright notice is retained and prominently displayed, along with a note saying that the original programs are available from our web page. The programs and documents are distributed without any warranty, express or implied. As the programs were written for research purposes only, they have not been tested to the degree that would be advisable in any important application. All use of these programs is entirely at the user's own risk.
*/

// Conjugate Gradient implementation is based on matlab code at http://learning.eng.cam.ac.uk/carl/code/minimize/minimize.m
// % Copyright (C) 2001 - 2006 by Carl Edward Rasmussen (2006-09-08).


#ifndef RBM_H
#define RBM_H

#include <iostream>
#include <random>


#include "utils/LightVector.h"
#include "Batch.h"

struct RBM
{
    enum class Type 
    {
        SIGMOID,
        LINEAR,
        EXP
    };

    Type type_ = Type::SIGMOID;
    Vector bias_visible_, bias_hidden_, bias_visible_inc_, bias_hidden_inc_;
    Vector weight_, weight_inc_;

    struct Conf {
        float momentum_ = 0.5, weight_cost_ = 0.0002, learning_rate_ = 0.1;
    };

    static float sigmoid(float x) {
        return (1.0 / (1.0 + exp(-x))); 
    }

    static const Vector& bernoulli(const Vector& input, Vector& output) { 
        static std::default_random_engine eng(::time(NULL));
        static std::uniform_real_distribution<float> rng(0.0, 1.0);

        for (size_t i=0; i<input.size(); ++i) {
            output[i] = (rng(eng) < input[i])? 1.0 : 0.0; 
        } 
        return output;
    }

    static const Vector& add_noise(const Vector& input, Vector& output) { 
        static std::default_random_engine eng(::time(NULL));
        static std::normal_distribution<float> rng(0.0, 1.0);

        for (size_t i=0; i<input.size(); ++i) {
            output[i] = input[i] + rng(eng); 
        }
        return output;
    }

    RBM() {

    }

    RBM(size_t visible, size_t hidden)
    : bias_visible_(visible), bias_hidden_(hidden), weight_(visible * hidden)
    , bias_visible_inc_(visible), bias_hidden_inc_(hidden), weight_inc_(visible * hidden)
    {
        static std::default_random_engine eng(::time(NULL));
        static std::normal_distribution<float> rng(0.0, 1.0);
        for (auto& x: weight_) 
            x = rng(eng) * .1;
    }

    size_t num_hidden() const { 
        return bias_hidden_.size(); 
    }

    size_t num_visible() const {
        return bias_visible_.size(); 
    }
    size_t num_weight() const { return weight_.size(); }

    int mirror(const RBM& rbm)
    {
        size_t n_visible = bias_visible_.size(), n_hidden = bias_hidden_.size();
        if (n_hidden != rbm.num_visible() || n_visible != rbm.num_hidden()) { 
            std::cout << "not mirrorable" << std::endl;
            return -1;
        }

        bias_visible_ = rbm.bias_hidden_;
        bias_hidden_ = rbm.bias_visible_;
        for (size_t i = 0; i < n_visible; ++i) {
           for (size_t j = 0; j < n_hidden; ++j) {
            weight_[j * n_visible + i] = rbm.weight_[i * n_hidden + j];
          }
        }
        return 0;  
    }

    const Vector& activate_hidden(const Vector& visible, Vector& hidden) const {
        return RBM::activate_hidden(visible, hidden, bias_hidden_, weight_, type_);
    }

    template <class Vector1, class Vector2, class Vector3>
    static const Vector2& activate_hidden(const Vector1& visible, Vector2& hidden, const Vector3& bias_hidden, const Vector3& weight, Type type)
    {
        size_t n_visible = visible.size(), n_hidden = hidden.size();

        std::fill(hidden.begin(), hidden.end(), 0);
        for (size_t i = 0; i < n_hidden; ++i) {
            float *xd = const_cast<float *>(weight.data() + i * n_visible);
            float s = v::dot(visible, v::LightVector(xd, xd + n_visible));
            s += bias_hidden[i];

            if (type == Type::SIGMOID)
                s = sigmoid(s);
            else if (type == Type::EXP)
                s = exp(s);

            hidden[i] = s;
        }

        return hidden;
    }

    const Vector& activate_visible(const Vector& hidden, Vector& visible) const
    {
        size_t n_visible = bias_visible_.size(), n_hidden = bias_hidden_.size();

        std::fill(visible.begin(), visible.end(), 0);
        for (size_t i = 0; i < n_visible; ++i) {
            float s = 0;
            for (size_t j = 0; j < n_hidden; ++j)
                s += hidden[j] * weight_[j * n_visible+ i];
            
            s += bias_visible_[i];

            s = sigmoid(s);
            visible[i] = s;
        }

        return visible;
    }

    float train(Batch inputs, const Conf& conf) {
        size_t n_visible = bias_visible_.size(), n_hidden = bias_hidden_.size();
        float momentum = conf.momentum_, learning_rate = conf.learning_rate_, weight_cost = conf.weight_cost_;

        // temporary results
        Vector v1(n_visible), h1(n_hidden), v2(n_visible), h2(n_hidden), hs(n_hidden);

        //delta
        Vector gw(n_visible * n_hidden), gv(n_visible), gh(n_hidden);
        for (auto const& input: inputs) {
            v1 = input;
            this->activate_hidden(v1, h1);
            this->activate_visible((type_ == Type::LINEAR? add_noise(h1, hs): bernoulli(h1, hs)), v2);
            this->activate_hidden(v2, h2);

            for (size_t i = 0; i < n_visible; ++i) {
                for (size_t j = 0; j < n_hidden; ++j) gw[j * n_visible + i] += h1[j] * v1[i] - h2[j] * v2[i];
            }

          v::saxpy2(gh, 1.0, h1, -1.0, h2);
          v::saxpy2(gv, 1.0, v1, -1.0, v2);
        }

        //update
        size_t n_samples = inputs.size();
        //    gw /= float(n_samples);
        //    gw -= weight_ * weight_cost;
        v::saxpy(1.0/n_samples, gw, -weight_cost, weight_);
        //    weight_inc_ = weight_inc_ * momentum + gw * learning_rate;
        v::saxpy(momentum, weight_inc_, learning_rate, gw);

        //    weight_ += weight_inc_;
        v::saxpy(weight_, 1.0, weight_inc_);

        //    gh /= float(n_samples); 
        //    bias_hidden_inc_ = bias_hidden_inc_ * momentum + gh * learning_rate;
        v::saxpy(momentum, bias_hidden_inc_, learning_rate / n_samples, gh);
        //    bias_hidden_ += bias_hidden_inc_;
        v::saxpy(bias_hidden_, 1.0, bias_hidden_inc_);

        //    gv /= float(n_samples); 
        //    bias_visible_inc_ = bias_visible_inc_ * momentum + gv * learning_rate;
        v::saxpy(momentum, bias_visible_inc_, learning_rate / n_samples, gv);
        //    bias_visible_ += bias_visible_inc_;
        v::saxpy(bias_visible_, 1.0, bias_visible_inc_);

        //    float error = sqrt(gv.dot(gv) / n_visible);
        v::scale(gv, 1.0/n_samples);
        float error = sqrt(v::dot(gv, gv) / n_visible);

        return error;
    }

    virtual float free_energy() const
    {
        size_t n_visible = bias_visible_.size(), n_hidden = bias_hidden_.size();
        float s = 0;
        for (size_t i = 0; i < n_visible; ++i) {
            for (size_t j = 0; j < n_hidden; ++j) 
                s += weight_[j * n_visible+ i] * bias_hidden_[j] * bias_visible_[i];
        }
        return -s;
    }

    template <typename T> static void _write(std::ostream& os, const T& v) { 
        os.write(reinterpret_cast<const char *>(&v), sizeof(v)); 
    }

    void store(std::ostream& os) const
    {
        int type = (int)type_;
        size_t n_visible = bias_visible_.size();
        size_t n_hidden = bias_hidden_.size();

        _write(os, type);
        _write(os, n_visible);
        _write(os, n_hidden);

        for (float v: bias_visible_)
            _write(os, v);
        for (float v: bias_hidden_) 
            _write(os, v);
        for (float v: weight_) 
            _write(os, v);
    }

    template <typename T> static void _read(std::istream& is, T& v) { is.read(reinterpret_cast<char *>(&v), sizeof(v)); }
    void load(std::istream& is) {
        int type = 0;
        size_t n_visible = 0, n_hidden = 0;
        _read(is, type);
        _read(is, n_visible);
        _read(is, n_hidden);

        type_ = (Type)type;
        bias_visible_.resize(n_visible);
        bias_hidden_.resize(n_hidden);
        weight_.resize(n_visible * n_hidden);

        for (float& v: bias_visible_) 
            _read(is, v);
        for (float& v: bias_hidden_) 
            _read(is, v);
        for (float& v: weight_) 
            _read(is, v);
    }
};

#endif