/*
 * GatewayClient.cpp
 *
 *  Created on: 2014Äê8ÔÂ9ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/GatewayClient.h"

namespace client {

GatewayClient::GatewayClient(boost::asio::io_service &_io_service,tcp::endpoint &end_point):
	_request(_io_service,end_point){
	// TODO Auto-generated constructor stub

}

GatewayClient::~GatewayClient() {
	// TODO Auto-generated destructor stub
}

} /* namespace client */
