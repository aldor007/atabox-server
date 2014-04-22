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
#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "pplx/pplxlinux.h"
#include "pplx/pplxtasks.h"



typedef void (* handle_request_fun)(web::http::http_request);
//TODO: touple for diffrent method type POST,GEt etc
class AtaboxApi {
public:
	AtaboxApi(std::string host, std::string port);
	//AtaboxApi(utility::string_t url);
	virtual ~AtaboxApi();
	pplx::task<void> open();
	pplx::task<void> close();
	void addMethod(std::string name, handle_request_fun fun);
private:
	static void handle_error(pplx::task<void>&t);
	void  inline listenerSetSupports();
	void inline commonHandler(web::http::http_request);
	void handle_get(web::http::http_request);
	void handle_post(web::http::http_request);
	void handle_put(web::http::http_request);
	std::map<utility::string_t, handle_request_fun> m_router;
	static std::string m_apiMainPath;
	std::string m_host;
	std::string m_port;
	utility::string_t m_url;
	web::http::experimental::listener::http_listener m_listener;
};

#endif /* ATABOXAPI_H_ */
