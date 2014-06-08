/*
 * Runner.cpp
 *
 *  Created on: 5 maj 2014
 *      Author: aldor
 */

#include "runner/Runner.h"
#include "utils/atabox_log.h"
//Runner::Runner(boost::asio::io_service &l_io_service) : m_io_service(l_io_service) {
//}

Runner::Runner() {

}
Runner::~Runner() {
}
wj::value Runner::run(std::string command, std::string args/*,
			std::function<void(const boost::system::error_code&,int)> lambda*/) {
    wj::value result;
    LOG(debug)<<"Running command "<<command<<" "<<args;

	boost::system::error_code ec;
    std::string commandPath = bp::search_path(command);
    std::string logFileName;
    if (commandPath.empty()) {
        commandPath = command;
        std::vector<std::string> tmpPath;
        boost::split(tmpPath, commandPath, boost::is_any_of("/"));
        logFileName = tmpPath.back();
    }
    else {

        logFileName = command;
    }
    std::string commandLine = command;
    if (!args.empty())
    	commandLine += std::string(" ") +  args;
    {
    bi::file_descriptor_sink sink_stdout(logFileName + std::string("_stdout.log"));
    bi::file_descriptor_sink sink_stderr(logFileName + std::string("_stderr.log"));
    #if defined(BOOST_POSIX_API)
     //   boost::asio::signal_set set(m_io_service, SIGCHLD);
     //   set.async_wait(lambda);
        /*[&status, &result](const boost::system::error_code&, int test)
            {
        		::wait(&status);
        		result["cmd_status"] = wj::value::string("RUN");
        		result["cmd_code"] = wj::value::number(status);
        		std::cout<<"test "<<test;
            }
        );*/
	#endif
    try
      {
          bp::child c = bp::execute(
                bpi::run_exe(commandPath)
                ,bpi::set_cmd_line(commandLine)
                , bpi::bind_stdout(sink_stdout)
                , bpi::bind_stderr(sink_stderr)
                 ,bpi::inherit_env()
                ,bpi::throw_on_error()
    	#if defined(BOOST_POSIX_API)
               // , bpi::notify_io_service(m_io_service)
    	#endif

		#if defined(BOOST_WINDOWS_API)
           // DWORD exit_code;
           // boost::asio::windows::object_handle handle(m_io_service, c.process_handle());
            //handle.async_wait(
            //    [&handle, &exit_code](const boost::system::error_code&)
             //       { ::GetExitCodeProcess(handle.native(), &exit_code); }
            //);
    	#endif
            );
          int32_t exit_code = bp::wait_for_exit(c);
          if (exit_code)
        	  exit_code /= 256;

        		result["cmd_status"] = wj::value::string("RUN");
        		result["cmd_code"] = wj::value::number(exit_code);


        } catch(boost::system::system_error &e)
        {
        	result["cmd_status"] = wj::value::string("ERROR");
        	result["cmd_code"] = wj::value::number(e.code().value());
        	result["cmd_error_msg"] = wj::value::string(e.what());

        }
    }
    return result;

}



