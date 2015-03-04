#ifndef APIMOCK_H_
#define APIMOCK_H_

#include "cpprest/http_listener.h"
#undef U

#include "gmock/gmock.h"

class http_listenerMock: public web::http::experimental::listener::http_listener {
public:
	http_listenerMock();

};

#endif /* WAVEFILEMOCK_H_ */
