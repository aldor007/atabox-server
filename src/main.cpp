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
#include <boost/program_options.hpp>
#include <boost/asio/io_service.hpp>

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
#include <runner/Runner.h>
#include <utils/execution_policy.h>
using namespace web;
using namespace web::http;
using namespace web::http::client;



const std::string DEFAULT_POLICY = "nonstrict";
enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};
BaseDataProvider<WaveProperties, std::string> * g_mainDB;
boost::asio::io_service g_io_service;
Runner g_runner(g_io_service);
typedef std::string(*policy_fun)(std::map<WaveProperties,std::string>&, WaveProperties&);
std::map<std::string, policy_fun>  g_policies;

void handle_add(web::http::http_request request) {

	json::value response;
    std::map<std::string, std::string> querymap = uri::split_query(request.relative_uri().query());
    if (querymap.find("name") == querymap.end() || querymap.find("command") == querymap.end()) {
    	BOOST_LOG_TRIVIAL(error)<<"Bad request";
    	response["error_msg"] = json::value::string("Bad request. Read doc for info. Missing name or command field in request.");
    	response["status"] = json::value::string("ERROR");
    	request.reply(status_codes::BadRequest, response);
    	return;

    }
    std::string commandName = uri::decode(querymap["name"]);
    std::string commandString = uri::decode(querymap["command"]);
    BOOST_LOG_TRIVIAL(debug)<<"Add command name "<<commandName<<" command string: "<<commandString;
    concurrency::streams::istream body = request.body();
    uint64_t content_lenght = request.headers().content_length();
    BOOST_LOG_TRIVIAL(debug)<<"Content lenght of request "<<content_lenght;
    if (content_lenght == 0) {
    	BOOST_LOG_TRIVIAL(error)<<"Bad request! Empty body";
    	response["error_msg"] = json::value::string("Bad request.Empty body!");
    	response["status"] = json::value::string("ERROR");
    	request.reply(status_codes::BadRequest, response);
    	return;

    }
    uint8_t * waveData = new uint8_t[content_lenght];
    Concurrency::streams::rawptr_buffer<uint8_t> buffer(waveData, content_lenght);
    body.read(buffer, content_lenght).get();
    WaveFile wave(waveData);
    delete waveData;
    NormalizedSamplesList waveSamples(wave);
    WavePreprocessor::deleteSielienceFromBeginningAndEnd(waveSamples);
    WaveFileAnalizator analizator;
    WaveProperties waveProperties = analizator.getAllProperties(waveSamples);
    waveProperties.name = commandName;

    try {
    	g_mainDB->put(waveProperties.toString(), commandString);
    } catch (std::exception const & ex) {
    	BOOST_LOG_TRIVIAL(error)<<"Error "<<ex.what();
    	response["status"] = json::value::string("ERROR");
    	response["error_msg"] = json::value::string(ex.what());
    	request.reply(status_codes::InternalError, response);
    	return;
    }
    response["status"] = json::value::string("OK");
    response["command"] = json::value::string(commandString);
    request.reply(status_codes::OK, response);

}

void handle_execute(web::http::http_request request) {

	json::value response;
    concurrency::streams::istream body = request.body();
    uint64_t content_lenght = request.headers().content_length();
    BOOST_LOG_TRIVIAL(debug)<<"Content lenght of request "<<content_lenght;
    if (content_lenght == 0) {
    	BOOST_LOG_TRIVIAL(error)<<"Bad request! Empty body";
    	response["error_msg"] = json::value::string("Bad request.Empty body!");
    	response["status"] = json::value::string("ERROR");
    	request.reply(status_codes::BadRequest, response);
    	return;

    }
    uint8_t * waveData = new uint8_t[content_lenght];
    Concurrency::streams::rawptr_buffer<uint8_t> buffer(waveData, content_lenght);
    body.read(buffer, content_lenght).get();
    WaveFile wave(waveData);
    delete waveData;
    NormalizedSamplesList waveSamples(wave);
    WavePreprocessor::deleteSielienceFromBeginningAndEnd(waveSamples);
    WaveFileAnalizator analizator;
    WaveProperties waveProperties = analizator.getAllProperties(waveSamples);

	std::map<WaveProperties, std::string> list;
	list = g_mainDB->getAllKV();
	auto tmpFun = g_policies[DEFAULT_POLICY];

	std::string command = tmpFun(list, waveProperties);
	if (!command.empty()) {

			web::json::value cmdResult = g_runner.run(command, " ");
			response["status"] = json::value::string("OK");
			response["command"] = json::value::string(command);
			response["command_ret"] = cmdResult;
			request.reply(status_codes::OK, response);
			return;
	}

	response["status"] = json::value::string("NOT_FOUND");

    request.reply(status_codes::OK, response);

}

void handle_list(web::http::http_request request) {
	std::map<WaveProperties, std::string> list;
	json::value result;
	try {

		list = g_mainDB->getAllKV();
    } catch (std::exception const & ex) {
    	BOOST_LOG_TRIVIAL(error)<<"DB Error "<<ex.what();
    	result["status"] = json::value::string("ERROR");
    	result["error_msg"] = json::value::string(ex.what());
    	request.reply(status_codes::InternalError, result);
    	return;
    }
	uint32_t counter = 0;
    json::value tmp;
    result[0] = tmp;
	for (map_it iterator = list.begin(); iterator != list.end(); iterator++) {
		tmp["waveProperties"] = iterator->first.toJSON();
		tmp["command"] = json::value::string(iterator->second);
		result[counter++] =  tmp;
	}


  request.reply(status_codes::OK, result);

}

void handle_test(web::http::http_request request) {
	json::value result;
	result["status"] = json::value::string("OK");
	request.reply(status_codes::OK, result);
}

int main(int argc, char** argv) {
//TODO: http://www.radmangames.com/programming/how-to-use-boost-program_options
	 /** Define and parse the program options
	     */
	    namespace po = boost::program_options;
	    po::options_description desc("Options");
	    desc.add_options()
	      ("help", "Print help messages")
	      ("add", "additional options")
	      ("like", "this");

	    po::variables_map vm;
	    try
	    {
	      po::store(po::parse_command_line(argc, argv, desc),
	                vm); // can throw

	      /** --help option
	       */
	      if ( vm.count("help")  )
	      {
	        std::cout << "Basic Command Line Parameter App" << std::endl
	                  << desc << std::endl;
	        return 0;
	      }

	      po::notify(vm); // throws on error, so do after help in case
	                      // there are any problems
	    }
	    catch(po::error& e)
	    {
	      std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
	      std::cerr << desc << std::endl;
	      return 2;
	    }

	    // application code here //






    BOOST_LOG_TRIVIAL(debug)<<"Server listening localhost:8111. Db name atabox.db";
    g_mainDB  = new RocksdbProvider<WaveProperties, std::string>("/tmp/atabox.db"); //FIXME: database name read from config file
    g_policies["strict"] = execution_policy_strict;
    g_policies["nonstrict"] = execution_policy_nonstrict;
    AtaboxApi mainApi("127.0.0.1", "8111");
    mainApi.addMethod("add", handle_add);
    mainApi.addMethod("execute", handle_execute);
    mainApi.addMethod("list", handle_list);
    mainApi.addMethod("test", handle_test);
    //g_io_service.run();
    mainApi.open().wait();
    //std::string line;
    //std::getline(std::cin, line);
    while(1) {}
    mainApi.close().wait();
    BOOST_LOG_TRIVIAL(debug)<<"End of work. Bye ;)";



    return 0;
}



