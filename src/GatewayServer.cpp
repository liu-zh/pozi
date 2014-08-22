/*
 * GatewayServer.cpp
 *
 *  Created on: 2014年8月9日
 *      Author: liuzhenhua
 */

#include "../include/GatewayServer.h"

namespace server {

GatewayServer::GatewayServer(boost::asio::io_service& io_service)
:_response(io_service){
	// TODO Auto-generated constructor stub

}

GatewayServer::~GatewayServer() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
