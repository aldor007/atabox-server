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
    std::cout << "Wątek w stylu C++11 " << tid << std::endl;
}

int main() {
    std::thread t[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(call_from_thread, i);
    }

    std::cout << "To jest tylko test czy kompilacja w standardzie c++11 przebiega poprawnie\n";

    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }

    return 0;
}



