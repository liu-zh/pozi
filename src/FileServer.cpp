/*
 * FileServer.cpp
 *
 *  Created on: 2014年8月16日
 *      Author: liuzhenhua
 */

#include "../include/FileServer.h"

namespace server {

FileServer::FileServer(boost::asio::io_service& io_service ) :
	_filereceive(io_service ){
	// TODO Auto-generated constructor stub

}

FileServer::~FileServer() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
