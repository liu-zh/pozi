/*
 * RegisterApp.cpp
 *
 *  Created on: 2014Äê8ÔÂ30ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/RegisterApp.h"

namespace server {

RegisterApp::RegisterApp() {
	// TODO Auto-generated constructor stub

	      _logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FILE"));
}
void RegisterApp::startRegist(boost::shared_ptr<MultiVector> shared){

int port = 6700;
boost::asio::io_service io_service;
 RegistServer server(io_service,port);
 server.start_accept(shared);
 LOG4CPLUS_INFO(_logger,"register server start......");
 io_service.run();
}

RegisterApp::~RegisterApp() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
