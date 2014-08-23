/*
 * GatewayClient.cpp
 *
 *  Created on: 2014��8��9��
 *      Author: liuzhenhua
 */

#include "../include/GatewayClient.h"

namespace client {

GatewayClient::GatewayClient(const string& ip,const int& port)
	{
	// TODO Auto-generated constructor stub
    this->ip = ip;
    this->port = port;
}
bool GatewayClient::regist(){
	    boost::asio::io_service io_service;
		tcp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 6700);
		request _request(io_service,end_point);
		io_service.run();
		return true;
}
GatewayClient::~GatewayClient() {
	// TODO Auto-generated destructor stub
}

} /* namespace client */
