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
#include "wave/WaveFileAnalizator.h"
#include "wave/WaveProperties.h"
#include "wave/WaveFile.h"
#include "wave/WavePreprocessor.h"
#include "recognition/PropertiesComparator.h"

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
BaseDataProvider<WaveProperties, std::string> * mainDB;
void handle_add(web::http::http_request request) {

	json::value response;
    auto path = request.relative_uri().path();

    response["path"] = json::value::string(path);

    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() != 3) {
    	BOOST_LOG_TRIVIAL(error)<<"Bad request";
    	response["error_msg"] = json::value::string("Bad request. Read doc for info");
    	response["status"] = json::value::string("error");
    	request.reply(status_codes::BadRequest, response);
    	return;
    }
    std::string commandName = paths[1];
    std::string commandString = paths[2];
    BOOST_LOG_TRIVIAL(debug)<<"Add command name "<<commandName<<" command string: "<<commandString;
    concurrency::streams::istream body = request.body();
    uint64_t content_lenght = request.headers().content_length();
    BOOST_LOG_TRIVIAL(debug)<<"Content lenght of request "<<content_lenght;
    uint8_t * waveData = new uint8_t[content_lenght];
    Concurrency::streams::rawptr_buffer<uint8_t> buffer(waveData, content_lenght);
    body.read(buffer, content_lenght).get();
    WaveFile wave(waveData);
    delete waveData;
    //WavePreprocesor processWave;
            //processWave.process(&wave);
    NormalizedSamplesList waveSamples(wave);
    WaveFileAnalizator analizator;
    WaveProperties waveProperties = analizator.getAllProperties(waveSamples);
    waveProperties.name = commandName;

    try {
    	mainDB->put(waveProperties.toString(), commandString);
    } catch (std::exception const & ex) {
    	BOOST_LOG_TRIVIAL(error)<<"Error "<<ex.what();
    }
    request.reply(status_codes::OK, response);

}

void handle_execute(web::http::http_request request) {

    concurrency::streams::istream body = request.body();
    uint64_t content_lenght = request.headers().content_length();
    BOOST_LOG_TRIVIAL(debug)<<"Content lenght of request "<<content_lenght;
    uint8_t * waveData = new uint8_t[content_lenght];
    Concurrency::streams::rawptr_buffer<uint8_t> buffer(waveData, content_lenght);
    body.read(buffer, content_lenght).get();
    WaveFile wave(waveData);
    delete waveData;
    NormalizedSamplesList waveSamples(wave);
    WaveFileAnalizator analizator;
    WaveProperties waveProperties = analizator.getAllProperties(waveSamples);

	std::map<WaveProperties, std::string> list;
	list = mainDB->getAllKV();
	typedef std::map<WaveProperties, std::string>::iterator map_it;
	PropertiesComparator comparator;
	json::value response;

	for (map_it iterator = list.begin(); iterator != list.end(); iterator++) {
		double distance =  comparator.getDistance(iterator->first, waveProperties);
		if (distance == 0) {
			BOOST_LOG_TRIVIAL(debug)<<"Run command "<<iterator->second;
			//TODO: runner here
			response["status"] = json::value::string("OK");
			response["command_ret"] = json::value::number(0);
			request.reply(status_codes::OK, response);
			return;
		}
	}
	response["status"] = json::value::string("NOT_FOUND");

    request.reply(status_codes::OK, response);

}

void handle_list(web::http::http_request request) {
	std::map<WaveProperties, std::string> list;
	list = mainDB->getAllKV();
	json::value result;
	typedef std::map<WaveProperties, std::string>::iterator map_it;
	uint32_t counter = 0;
	for (map_it iterator = list.begin(); iterator != list.end(); iterator++) {
		json::value tmp;
		tmp["waveProperties"] = iterator->first.toJSON();
		tmp["command"] = json::value::string(iterator->second);
		result[counter++] =  tmp;
	}


  request.reply(status_codes::OK, result);

}



int main() {

    BOOST_LOG_TRIVIAL(debug)<<"Server listening localhost:8111. Db name atabox.db";
    mainDB  = new RocksdbProvider<WaveProperties, std::string>("atabox.db"); //FIXME: database name read from config file
    AtaboxApi mainApi("127.0.0.1", "8111");
    mainApi.addMethod("add", handle_add);
    mainApi.addMethod("execute", handle_execute);
    mainApi.addMethod("list", handle_list);
    mainApi.open().wait();
    std::string line;
    std::getline(std::cin, line);
    mainApi.close().wait();
    BOOST_LOG_TRIVIAL(debug)<<"End of work. Bye ;)";



    return 0;
}



