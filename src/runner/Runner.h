/*
 * Runner.h
 *
 *  Created on: 5 maj 2014
 *      Author: aldor
 */

#ifndef RUNNER_H_
#define RUNNER_H_
#include <boost/process.hpp>
//#include <boost/asio.hpp>
/*
#if defined(BOOST_WINDOWS_API)
#   include <Windows.h>

#elif defined(BOOST_POSIX_API)
#   include <sys/wait.h>
#   include <errno.h>
#endif*/
#include <boost/system/error_code.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/algorithm/string.hpp>

#include <vector>
#include <string>
#include <functional>

#include <cpprest/json.h>

namespace bp = boost::process;
namespace bpi = boost::process::initializers;
namespace bi = boost::iostreams;
namespace  wj = web::json;

class Runner {
//private:
  //  boost::asio::io_service &m_io_service;
public:
//	Runner(boost::asio::io_service&);
	Runner();
	virtual ~Runner();
	static wj::value run(std::string command, std::string args=""/*,
			std::function<void(const boost::system::error_code&,int)> lambda*/);
};

#endif /* RUNNER_H_ */
