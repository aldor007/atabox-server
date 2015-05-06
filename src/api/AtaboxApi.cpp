/*
 * AtaboxApi.cpp
 *
 *  Created on: 21 kwi 2014
 *      Author: aldor
 */

#include "AtaboxApi.h"
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
#include <sys/stat.h>


AtaboxApi::AtaboxApi(std::string host, std::string port) {
    m_url = U("http://");
    m_url.append(host);
    m_url.append(":");
    m_url.append(port);
    //m_url.append(m_apiMainPath);
}
void AtaboxApi::addMethod(std::string name, handle_request_fun fun) {
    m_router[name] = fun;
}

AtaboxApi::AtaboxApi(utility::string_t url) {
    m_url = U("http://");
    m_url.append(url);
    //m_url.append(m_apiMainPath);
}

void  AtaboxApi::listenerSetSupports() {
    //m_listener.configuration().set_timeout()
    http_listener_config conf;
    utility::seconds timeoutAtabox(30);
    m_listener = http_listener(m_url, conf);
    m_listener.support(methods::GET, std::bind(&AtaboxApi::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&AtaboxApi::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&AtaboxApi::handle_put, this, std::placeholders::_1));

}
AtaboxApi::~AtaboxApi() {
    m_listener.close();
}

std::map<utility::string_t, handle_request_fun> AtaboxApi::getMethods() const{
    return m_router;
}
void AtaboxApi::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}

pplx::task<void> AtaboxApi::open()
{
  //  return m_listener.open().then(std::bind(&handle_error, std::placeholders::_1));
    listenerSetSupports();
   return m_listener.open().then([]()
        {
            //...
           LOG(debug)<<"Open listener";
        });
}

pplx::task<void> AtaboxApi::close()
{
    LOG(debug)<<"IN close";
    return m_listener.close().then([](){

       LOG(debug)<<"Close listener";
    });
}
bool AtaboxApi::staticFilesHandler(http_request& request) {
     auto path = request.relative_uri().path();
        auto content_data = m_htmlcontentmap.find(path);
        if (content_data == m_htmlcontentmap.end())
        {
            return false;
        }

        auto file_name = std::get<0>(content_data->second);
        auto content_type = std::get<1>(content_data->second);
        struct stat buffer;

        if (stat (file_name.c_str(), &buffer) != 0) {

            LOG(error) <<"File not found "<<file_name;
            request.reply(status_codes::NotFound, U("File " + file_name + " not found ")).wait();
            return true;
        }

         concurrency::streams::istream is  = concurrency::streams::fstream::open_istream(file_name, std::ios::in).get();

          if(!is.is_open())
            request.reply(status_codes::InternalError).wait();
          else
            request.reply(status_codes::OK, is, content_type).then([=](){
            LOG(debug)<<"Send file "<<file_name;
          });
        return true;

}
void AtaboxApi::commonHandler(http_request& request) {

    try
    {
        auto path = request.relative_uri().path();


        LOG(info)<<"Path "<<path;
        std::string req_method = path;
        std::string req_headers = "";
        for (auto it = request.headers().begin(); it != request.headers().end(); it++)
              req_headers += it->first  + ": " +it->second + ", ";
        LOG(info) <<"Request headers "<<req_headers;

        if (req_method[req_method.size() - 1] == '/') {
            req_method.pop_back();
        }

        auto handle_fun = m_router.find(req_method);
        if (handle_fun == m_router.end())      {
            LOG(error) <<"Method "<<path<<" not found ";
            request.reply(status_codes::NotFound, U("Method " + path + " not found ")).wait();
            return;
        }
        (handle_fun->second)(request);
    } catch(std::exception &e) {
        LOG(fatal)<<"Exception! "<<e.what();
        request.reply(status_codes::InternalError).wait();
        return;
    }
}
// Handler to process HTTP::GET requests.
// Replies to the request with data.
void AtaboxApi::handle_get(http_request request) {

    if(!staticFilesHandler(request)) {
        commonHandler(request);
    }
}

// Respond to HTTP::POST messages
// Post data will contain the postal code or location string.
// Aggregate location data from different services and reply to the POST request.
void AtaboxApi::handle_post(http_request request)
{
    try {
        commonHandler(request);
    } catch(std::exception &e) {
        LOG(fatal)<<"Exception! "<<e.what()  ;
        request.reply(status_codes::InternalError).wait();
    }

}

void AtaboxApi::handle_put(http_request request) {
    commonHandler(request);
}

void AtaboxApi::enableStaticFiles() {
    m_htmlcontentmap[U("/")] = std::make_tuple(U("index.html"), U("text/html"));
    m_htmlcontentmap[U("/js/main.js")] = std::make_tuple(U("js/main.js"), U("application/javascript"));
    m_htmlcontentmap[U("/js/jquery-2.1.1.min.js")] = std::make_tuple(U("js/jquery-2.1.1.min.js"), U("application/javascript"));
    m_htmlcontentmap[U("/js/audiodisplay.js")] = std::make_tuple(U("js/audiodisplay.js"), U("application/javascript"));
    m_htmlcontentmap[U("/js/recorderjs/recorder.js")] = std::make_tuple(U("js/recorderjs/recorder.js"), U("application/javascript"));
    m_htmlcontentmap[U("/js/recorderjs/recorderWorker.js")] = std::make_tuple(U("js/recorderjs/recorderWorker.js"), U("application/javascript"));
    m_htmlcontentmap[U("/css/default.css")] = std::make_tuple(U("css/default.css"), U("text/css"));
    m_htmlcontentmap[U("/img/logo.png")] = std::make_tuple(U("img/logo.png"), U("application/octet-stream"));
    m_htmlcontentmap[U("/img/mic128.png")] = std::make_tuple(U("img/mic128.png"), U("image/png"));
    m_htmlcontentmap[U("/img/load.gif")] = std::make_tuple(U("img/load.gif"), U("image/gifl"));

}
