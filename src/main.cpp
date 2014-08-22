/*
 * main.cpp
 *
 *  Created on: 2014/08/09
 *      Author: liuzhenhua
 */

#include "../include/Gateway.h"
#include "../include/GatewayServer.h"
#include "../include/FileServer.h"
int main(){

	boost::asio::io_service io_service;
			//server::Gateway server(io_service);
	//server::GatewayServer server(io_service);
	       server::FileServer server(io_service);
			io_service.run();
	return 0;
}


