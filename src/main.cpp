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
#include <fstream>
#include <thread>

#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>

#include "cpprest/containerstream.h"
#include "cpprest/rawptrstream.h"

#include "dataproviders/BaseDataProvider.h"
#include "dataproviders/RocksdbProvider.h"
#include "api/AtaboxApi.h"
using namespace web;
using namespace web::http;
using namespace web::http::client;

static const int num_threads = 3;
//TODO move somewhere

enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};
BaseDataProvider<std::string, std::string> * mainDB;
void handle_add(web::http::http_request request) {

	json::value response;
    auto path = request.relative_uri().path();

    response["path"] = json::value::string(path);

    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() != 3) {
    	BOOST_LOG_TRIVIAL(error)<<"Bad request";
    	response["error"] = json::value::string("Bad request. Read doc for info");
    	response["status"] = json::value::string("error");
    	request.reply(status_codes::BadRequest, response);
    	return;
    }
    std::string commandName = paths[1];
    std::string commandString = paths[2];
    BOOST_LOG_TRIVIAL(debug)<<"Add command name "<<commandName<<" command string: "<<commandString;
    concurrency::streams::istream body = request.body();
    Concurrency::streams::container_buffer<std::vector<uint8_t>> inStringBuffer;
    utility::size64_t content_lenght = request.headers().content_length();
    BOOST_LOG_TRIVIAL(debug)<<"Content lenght of request "<<content_lenght;
    body.read(inStringBuffer, content_lenght).then([inStringBuffer](size_t bytesRead) {
    	std::vector<uint8_t> &waveData = inStringBuffer.collection();
    	BOOST_LOG_TRIVIAL(debug)<<"file "<<bytesRead;
    WaveFile wave(&waveData);
  //  WavePreprocesor processWave;
    //processWave.run(&wave);
    WaveFileAnalizator analyze;
    WaveProperries waveProperties = analyze.getAllProperties();
    waveProperties.name = name;
    mainDB->put(waveProperties.toString(), commandString);


    }).wait();

    /* not Working
     utility::size64_t content_lenght = request.headers().content_length();
    BOOST_LOG_TRIVIAL(debug)<<"Content lenght of request "<<content_lenght;
    uint8_t *rawData = new uint8_t[content_lenght];
    Concurrency::streams::rawptr_buffer<uint8_t> rawBuffer(rawData, content_lenght, std::ios::in);

    body.read(rawBuffer, content_lenght).then([rawBuffer](size_t bytesRead) {
    	//std::vector<uint8_t> &wave = inStringBuffer.collection();
    	//BOOST_LOG_TRIVIAL(debug)<<"file "<<rawData[0];
    }).wait();
*/
	request.reply(status_codes::OK, response);

}

void handle_execute(web::http::http_request request) {
	json::value response;
    auto path = request.relative_uri().path();

    response["path"] = json::value::string(path);

	   request
	      .extract_json()

	      .then([&response,&request](pplx::task<json::value> task) {
	         try
	         {
	           auto jvalue = task.get();
	           if(!jvalue.is_null()) {
	           //auto &jsonObject = jvalue.as_object();
	         //  std::string name = jsonObject["name"].is_string()?jsonObject["name"].serialize():"test";
	        //   std::string command = jsonObject["command"].serialize();
	         // BOOST_LOG_TRIVIAL(debug)<<" "<<jsonObject["waveFile"];
	           }
	         }
	         catch (http_exception const & e)
	         {
	            std::cout << "errror "<<e.what() << std::endl;
	            BOOST_LOG_TRIVIAL(error) << "An error severity message";
	            response["error"] = json::value::string(	e.what());

	         //   	request.reply(status_codes::OK, response );

	         }
	            BOOST_LOG_TRIVIAL(error) << "End of then";
	      }).wait();

	request.reply(status_codes::OK, response);


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

    mainDB  = new RocksdbProvider<std::string, std::string>("atabox.db"); //FIXME: database name read from config file
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



