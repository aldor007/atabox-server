/*
 * main.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */

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

    return 0;
}



