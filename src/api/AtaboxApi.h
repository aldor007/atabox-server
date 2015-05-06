/*
 * AtaboxApi.h
 *
 *  Created on: 21 kwi 2014
 *      Author: aldor
 */

#ifndef ATABOXAPI_H_
#define ATABOXAPI_H_
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

#include <boost/log/trivial.hpp>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "pplx/pplxlinux.h"
#include "pplx/pplxtasks.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"
#include "cpprest/producerconsumerstream.h"


#include <utils/atabox_log.h>

typedef void (* handle_request_fun)(web::http::http_request&);
//TODO: touple for diffrent method type POST,GEt etc
class AtaboxApi {
public:
	AtaboxApi(std::string host, std::string port);
	AtaboxApi(utility::string_t url);
	virtual ~AtaboxApi();
	pplx::task<void> open();
	pplx::task<void> close();
	void addMethod(std::string name, handle_request_fun fun);
	std::map<utility::string_t, handle_request_fun> getMethods() const;
	void enableStaticFiles();
protected:
	static void handle_error(pplx::task<void>&t);
	void  inline listenerSetSupports();
	void inline commonHandler(web::http::http_request&);
	bool inline staticFilesHandler(web::http::http_request&);
	void handle_get(web::http::http_request);
	void handle_post(web::http::http_request);
	void handle_put(web::http::http_request);
	std::map<utility::string_t, handle_request_fun> m_router;
	std::string m_host;
	std::string m_port;
	utility::string_t m_url;
	web::http::experimental::listener::http_listener m_listener;
    std::map<utility::string_t, std::tuple<utility::string_t, utility::string_t>> m_htmlcontentmap;
};

#endif /* ATABOXAPI_H_ */
