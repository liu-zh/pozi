/*
 * ScheServer.cpp
 *
 *  Created on: 2014Äê8ÔÂ23ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/DistriApp.h"

namespace server {

DistriApp::DistriApp(  const int& distributePort)
 {


      this->distributePort = distributePort;

      _logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FILE"));
}

 void    DistriApp::startDistribute(boost::shared_ptr<MultiVector> shared){
 	boost::asio::io_service io_service;
 	 DistriServer distri(io_service, distributePort );
 	 distri.start_accept(shared);
 	LOG4CPLUS_INFO(_logger,"distribute server start......");
 	io_service.run();
 }

 DistriApp::~DistriApp() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
