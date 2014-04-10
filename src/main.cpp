/*
 * main.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */
#include <string>
#include "dataproviders/RocksdbProvider.h"
#include <map>
#include <iostream>
#include <random>
#include <iostream>
#include <thread>

static const int num_threads = 3;


void call_from_thread(int tid) {
    std::cout << "Thread in C++11 style" << tid << std::endl;
}

int main() {
    std::thread t[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(call_from_thread, i);
    }

    std::cout << "This funtions is used do determine if c++11 compilation is correct.\n";

    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }

    RocksdbProvider<std::string, std::string> db("test.db");
    std::string tmp = db.get("test");
    auto mapa = db.getAllKV();
    for(std::map<std::string, std::string>::iterator it = mapa.begin(); it != mapa.end(); it++)
        std::cout<<"key "<<it->first<< " value "<<mapa[it->first]<<'\n';
    std::cout<<tmp<<std::endl;
    return 0;
}



