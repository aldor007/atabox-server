/*
 * main.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */
#include <string>
#include <map>
#include <iostream>
#include <random>
#include <iostream>
#include <thread>

#include "dataproviders/RocksdbProvider.h"
#include "api/AtaboxApi.h"
using namespace web::http;

static const int num_threads = 3;
//TODO move somewhere

void handle_add(web::http::http_request request) {


       request.reply(status_codes::Forbidden, U("Not implemented yet"));

}

void handle_execute(web::http::http_request request) {

  request.reply(status_codes::Forbidden, U("Not implemented yet"));

}

void handle_list(web::http::http_request request) {
  request.reply(status_codes::Forbidden, U("Not implemented yet"));

}


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

   AtaboxApi mainApi("127.0.0.1", "8111");
    mainApi.addMethod("add", handle_add);
    mainApi.addMethod("execute", handle_execute);
    mainApi.addMethod("list", handle_list);
    mainApi.open().wait();
    std::string line;
       std::getline(std::cin, line);
     mainApi.close().wait();



    return 0;
}



