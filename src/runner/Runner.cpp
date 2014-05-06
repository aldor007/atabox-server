/*
 * Runner.cpp
 *
 *  Created on: 5 maj 2014
 *      Author: aldor
 */

#include <runner/Runner.h>
#if defined(__CYGWIN__)
#  define _WIN32_WINNT 0x0501
#  define __USE_W32_SOCKETS
#  undef BOOST_POSIX_API
#  define BOOST_WINDOWS_API
#endif
#include <boost/asio.hpp>
#define BOOST_PROCESS_WINDOWS_USE_NAMED_PIPE
#include <boost/process.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace bp = ::boost::process;
namespace ba = ::boost::asio;

ba::io_service io_service;
boost::array<char, 4096> buffer;

#if defined(BOOST_POSIX_API)
ba::posix::stream_descriptor in(io_service);
#elif defined(BOOST_WINDOWS_API)
ba::windows::stream_handle in(io_service);
#else
#  error "Unsupported platform."
#endif
Runner::Runner() {
	// TODO Auto-generated constructor stub

}

Runner::~Runner() {
	// TODO Auto-generated destructor stub
}
int16_t Runner::run()
{

}




bp::child start_child()
{
    std::string exec = "bjam";

    std::vector<std::string> args;
    args.push_back("--version");

    bp::context ctx;
    ctx.stdout_behavior = bp::capture_stream();

    return bp::launch(exec, args, ctx);
}

void end_read(const boost::system::error_code &ec, std::size_t bytes_transferred);

void begin_read()
{
    in.async_read_some(boost::asio::buffer(buffer),
        boost::bind(&end_read, ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void end_read(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        std::cout << std::string(buffer.data(), bytes_transferred) << std::flush;
        begin_read();
    }
}

int main()
{
    bp::child c = start_child();

    bp::pistream &is = c.get_stdout();
    in.assign(is.handle().release());

    begin_read();

    c.wait();
}
