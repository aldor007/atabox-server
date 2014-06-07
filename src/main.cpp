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
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <cstring>
#include <sys/time.h>
#include <sys/resource.h>
#include <memory>

#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/program_options.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/log/attributes/named_scope.hpp>

// Supporting headers
#include <boost/log/support/exception.hpp>

#include <pplx/threadpool.h>


#include "cpprest/containerstream.h"
#include "cpprest/rawptrstream.h"

#include "utils/atabox_log.h"
#include "dataproviders/BaseDataProvider.h"
#include "dataproviders/RocksdbProvider.h"
#include "api/AtaboxApi.h"
#include "wave/analysis/SamplesAnalizator.h"
#include "wave/analysis/WaveProperties.h"
#include "wave/WaveFile.h"
#include "wave/preprocessing/WavePreprocessor.h"
#include "recognition/PropertiesComparator.h"
#include "runner/Runner.h"
#include "utils/execution_policy.h"
using namespace web;
using namespace web::http;
using namespace web::http::client;



const std::string DEFAULT_POLICY = "nonstrict";
BaseDataProvider<WaveProperties, std::string> * g_mainDB;
auto &g_io_service = crossplat::threadpool::shared_instance().service();
Runner g_runner();
typedef std::string(*policy_fun)(std::map<WaveProperties,std::string>&, WaveProperties&);
std::map<std::string, policy_fun>  g_policies;

extern atabox_log::logger g_log;

void handle_add(web::http::http_request request) {

	json::value response;
    std::map<std::string, std::string> querymap = uri::split_query(request.relative_uri().query());
    if (querymap.find("name") == querymap.end() || querymap.find("command") == querymap.end()) {
    	LOG(error)<<"Bad request";
    	response["error_msg"] = json::value::string("Bad request. Read doc for info. Missing name or command field in request.");
    	response["status"] = json::value::string("ERROR");
    	request.reply(status_codes::BadRequest, response).get();
    	return;

    }
    std::string commandName = uri::decode(querymap["name"]);
    std::string commandString = uri::decode(querymap["command"]);
    LOG(debug)<<"Add command name "<<commandName<<" command string: "<<commandString;
    concurrency::streams::istream body = request.body();
    uint64_t content_lenght = request.headers().content_length();
    LOG(debug)<<"Content lenght of request "<<content_lenght;
    if (content_lenght == 0) {
    	LOG(error)<<"Bad request! Empty body";
    	response["error_msg"] = json::value::string("Bad request.Empty body!");
    	response["status"] = json::value::string("ERROR");
    	request.reply(status_codes::BadRequest, response).get();
    	return;

    }
    try {
    	uint8_t * waveData = new uint8_t[content_lenght];
    	Concurrency::streams::rawptr_buffer<uint8_t> buffer(waveData, content_lenght);
    	//body.read_to_end(buffer).get();
    	body.read(buffer, content_lenght).get();
    	WaveFile wave(waveData);
    	delete waveData;
    	Samples waveSamples(wave);
    	WavePreprocessor::deleteSielienceFromBeginningAndEnd(waveSamples);
    	SamplesAnalizator analizator;
    	WaveProperties waveProperties = analizator.getAllProperties(waveSamples);
    	waveProperties.name = commandName;

    	try {
    		g_mainDB->put(waveProperties.toString(), commandString);
    	} catch (std::exception const & ex) {
    		LOG(error)<<"Error "<<ex.what();
    		response["status"] = json::value::string("ERROR");
    		response["error_msg"] = json::value::string(ex.what());
    		request.reply(status_codes::InternalError, response).get();
    		return;
    	}
    	response["status"] = json::value::string("OK");
    	response["command"] = json::value::string(commandString);
    	request.reply(status_codes::OK, response).get();
    } catch (std::exception &e) {

  		LOG(error)<<"Error "<<e.what();
   		response["status"] = json::value::string("ERROR");
   		response["command"] = json::value::string(e.what());
   		request.reply(status_codes::BadRequest, response).get();
   	}

}

void handle_execute(web::http::http_request request) {

	json::value response;
    concurrency::streams::istream body = request.body();
    uint64_t content_lenght = request.headers().content_length();
    LOG(debug)<<"Content lenght of request "<<content_lenght;
    if (content_lenght == 0) {
    	LOG(error)<<"Bad request! Empty body";
    	response["error_msg"] = json::value::string("Bad request.Empty body!");
    	response["status"] = json::value::string("ERROR");
    	request.reply(status_codes::BadRequest, response).get();
    	return;

    }
    uint8_t * waveData = new uint8_t[content_lenght];
    Concurrency::streams::rawptr_buffer<uint8_t> buffer(waveData, content_lenght);
    body.read(buffer, content_lenght).get();
    WaveFile wave(waveData);
    delete waveData;
    Samples waveSamples(wave);
    WavePreprocessor::deleteSielienceFromBeginningAndEnd(waveSamples);
    SamplesAnalizator analizator;
    WaveProperties waveProperties = analizator.getAllProperties(waveSamples);

	std::map<WaveProperties, std::string> list;
	list = g_mainDB->getAllKV();
	auto tmpFun = g_policies[DEFAULT_POLICY];

	std::string command = tmpFun(list, waveProperties);
	if (!command.empty()) {

			web::json::value cmdResult = Runner::run(command, " ");
			response["status"] = json::value::string("OK");
			response["command"] = json::value::string(command);
			response["command_ret"] = cmdResult;
			request.reply(status_codes::OK, response).get();
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
    	LOG(error)<<"DB Error "<<ex.what();
    	result["status"] = json::value::string("ERROR");
    	result["error_msg"] = json::value::string(ex.what());
    	request.reply(status_codes::InternalError, result).get();
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
	request.reply(status_codes::OK, result).get();
}

inline void daemonize(const std::string &dir = "/",
               const std::string &stdinfile = "/dev/null",
               const std::string &stdoutfile = "/dev/null",
               const std::string &stderrfile = "/dev/null")
{
  rlimit rl;
      umask(0);
  if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
  {
    //can't get file limit
    throw std::runtime_error(strerror(errno));
  }

  pid_t pid;
  g_io_service.notify_fork(boost::asio::io_service::fork_prepare);

  if ((pid = fork()) < 0)
  {
    //Cannot fork!
    throw std::runtime_error(strerror(errno));
  } else if (pid != 0) { //parent

    g_io_service.notify_fork(boost::asio::io_service::fork_parent);
     //g_io_service.stop();
    exit(0);

  }
  if (setsid() < 0)
  {
	  LOG(fatal)<<"Set sid error";
      exit(EXIT_FAILURE);
  }


      umask(0);
  if (!dir.empty() && chdir(dir.c_str()) < 0)
  {
    // Oops we couldn't chdir to the new directory
    throw std::runtime_error(strerror(errno));
  }

  if (rl.rlim_max == RLIM_INFINITY)
  {
    rl.rlim_max = 1024;
  }

  umask(0);
 /* if (pid_t pid = fork())
      {
        if (pid > 0)
        {
        	g_io_service.notify_fork(boost::asio::io_service::fork_parent);
          exit(0);
        }
        else
        {
    throw std::runtime_error(strerror(errno));
        }
      }*/
  // Close all open file descriptors
  for (uint32_t i = 0; i < sysconf(_SC_OPEN_MAX); i++)
  {
    close(i);
  }


  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  int fd0 = open(stdinfile.c_str(), O_RDONLY);
  int fd1 = open(stdoutfile.c_str(),
      O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
  int fd2 = open(stderrfile.c_str(),
      O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);

  if (fd0 != STDIN_FILENO || fd1 != STDOUT_FILENO || fd2 != STDERR_FILENO)
  {
    //Unexpected file descriptors
    throw std::runtime_error("new standard file descriptors were not opened as expected");
  }
}


int main(int argc, char** argv) {
    try
    {
    	std::string listen = "127.0.0.1:8111";
    	namespace po = boost::program_options;
    	po::options_description desc("Options");
        bool color = false;
        bool atabox_daemon = false;
        std::string databasename = "/tmp/atabox.db";
        std::string configFile;
        desc.add_options()
          ("help,h", "Print help messages")
          ("listen,l", po::value<std::string>(&listen), " host:port listen ")
          ("config", po::value<std::string>(&configFile), "config file ")
          ("color,c",  "turn on color")
          ("database,f", po::value<std::string>(&databasename), "database name and location")
          ("daemon,d",  "Deamoznie")
          ;
        po::variables_map vm;
        try
        {
          po::store(po::parse_command_line(argc, argv, desc),
                    vm); // can throw

          // --help option
           //
          if ( vm.count("help")  )
          {
            std::cout << "atabox server options" << std::endl
                      << desc << std::endl;
            return 0;
          }
          color = vm.count("color");
          atabox_daemon = vm.count("daemon");
          po::notify(vm); // throws on error, so do after help in case
                          // there are any problems
        }
        catch(po::error& e)
        {
          std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
          std::cerr << desc << std::endl;
          return 2;
        }
        BOOST_LOG_FUNCTION();
        atabox_log::init_logging(color, atabox_daemon);
        LOG(debug) <<"Hello, world!";
        AtaboxApi mainApi(listen);
        mainApi.addMethod("/api/add", handle_add);
        mainApi.addMethod("/api/execute", handle_execute);
        mainApi.addMethod("/api/list", handle_list);
        mainApi.addMethod("/api/test", handle_test);
        LOG(info)<<"Server listening "<<listen<<" Db name "<<databasename;
        g_mainDB  = new RocksdbProvider<WaveProperties, std::string>(databasename);
        g_policies["strict"] = execution_policy_strict;
        g_policies["nonstrict"] = execution_policy_nonstrict;
        try {
           mainApi.open().wait();
        } catch(std::exception &e) {

            LOG(fatal)<<"ERROR "<<e.what();
            exit(2);
        }
      if (atabox_daemon)
      {
        //FIXME: deamon NOT workigin
        mainApi.close().wait();
        boost::asio::signal_set  signals(g_io_service, SIGINT, SIGTERM);
        signals.async_wait(boost::bind(&boost::asio::io_service::stop, &g_io_service));
        g_io_service.notify_fork(boost::asio::io_service::fork_prepare);
        g_io_service.stop();
        LOG(debug)<<"Io "<<crossplat::threadpool::shared_instance().service().stopped();
        daemon(1, 1);

       //crossplat::threadpool::shared_instance().service().reset();
         LOG(debug)<<"Io "<<crossplat::threadpool::shared_instance().service().stopped();
        //daemonize();
        //g_io_service.notify_fork(boost::asio::io_service::fork_child);
        //g_io_service.run();
        mainApi.open().get();

      }
      LOG(info)<<"After listener open.";
      std::string line;
      std::getline(std::cin, line);

      mainApi.close().get();
       LOG(info)<<"End of work. Bye ;)";

    } catch(boost::system::system_error& e) {
        LOG(fatal)<<e.code();
        LOG(fatal)<<"Info: "  << boost::diagnostic_information(e) ;
        exit(1);
       }
    catch (std::exception &e) {
        LOG(fatal)<<e.what();
        LOG(fatal)<<"Info: "  << boost::diagnostic_information(e) ;
        exit(1);

    }

    return 0;
}



