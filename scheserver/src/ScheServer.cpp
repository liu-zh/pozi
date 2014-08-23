/*
 * ScheServer.cpp
 *
 *  Created on: 2014Äê8ÔÂ23ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/ScheServer.h"

namespace server {

ScheServer::ScheServer( const int& port,const int& distributePort)
 {
      this->port = port;
      this->distributePort = distributePort;
}
 void    ScheServer::startRegist(){
	boost::asio::io_service io_service;
	response _response(io_service, port,vec);
	io_service.run();
}
 void    ScheServer::startDistribute(){
 	boost::asio::io_service io_service;
 	distribute _distribute(io_service, distributePort,vec);
 	io_service.run();
 }
 void ScheServer::execute(){

    boost::thread r(boost::bind(&ScheServer::startRegist,this));
    boost::thread d(boost::bind(&ScheServer::startDistribute,this));
    r.join();
    d.join();
 }
ScheServer::~ScheServer() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
