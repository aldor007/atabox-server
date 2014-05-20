// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/process.hpp>
#include <boost/asio.hpp>
#if defined(BOOST_WINDOWS_API)
#   include <Windows.h>
#elif defined(BOOST_POSIX_API)
#   include <sys/wait.h>
#   include <errno.h>
#endif
#include <string>
#include <stdio.h>
#include <boost/system/error_code.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/system/system_error.hpp>
#include <vector>

using namespace boost::process;
using namespace boost::process::initializers;
using namespace boost::iostreams;

class Runner {
    public:
        boost::asio::io_service m_io_service;
    public:
        void start_ioservice() {
            m_io_service.run();
        }
        int run(std::string path, std::string cmd) {
        //[async

    boost::system::error_code ec;
    std::vector<std::string> tmpPath;
    boost::split(tmpPath, path, boost::is_any_of("/"));
    std::string filename = tmpPath.back() + std::string("_stdOut.log");
            file_descriptor_sink sink(filename);
        #if defined(BOOST_POSIX_API)
            int status;
            boost::asio::signal_set set(m_io_service, SIGCHLD);
            set.async_wait(
                [&status](const boost::system::error_code&, int) { ::wait(&status); }
            );
    #endif
        try 
        {
            child c = execute(
                run_exe(path.c_str())
                ,set_cmd_line(cmd)
                , bind_stdout(sink)
                 ,inherit_env()
                ,throw_on_error()
    #if defined(BOOST_POSIX_API)
                , notify_io_service(m_io_service)
    #endif  
            );
        } catch(boost::system::system_error &e) 
        {}
            //throw ex on error
    #if defined(BOOST_WINDOWS_API)
            DWORD exit_code;
            boost::asio::windows::object_handle handle(m_io_service, c.process_handle());
            handle.async_wait(
                [&handle, &exit_code](const boost::system::error_code&)
                    { ::GetExitCodeProcess(handle.native(), &exit_code); }
            );
    #endif
        
        }

};

// Runner::m_io_service;//= boost::asio:io_service();

int main()
{
    Runner runnerA;

    runnerA.run(search_path("terminator"), "terminator -x gvim");
    runnerA.run("/bin/ls", "ls -l");
    runnerA.run("ls", "ls -lh");
    runnerA.run("test", "ls -lh");
    // runnerA.start_ioservice();
    getchar();
}
