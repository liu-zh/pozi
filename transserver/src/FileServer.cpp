/*
 * FileServer.cpp
 *
 *  Created on: 2014年8月16日
 *      Author: liuzhenhua
 */

#include "../include/FileServer.h"
#include "../include/GatewayClient.h"
namespace server {

FileServer::FileServer(const int& port)
 {
	// TODO Auto-generated constructor stub
   this->port = port;
}

void FileServer::startFileServer(){
	string registip = "127.0.0.1";
	int registPort = 6700;
	client::GatewayClient client(registip,registPort);
	if(client.regist()){
	boost::asio::io_service io_service;
	Filereceive _filereceive(io_service,this->port);
	}
}
FileServer::~FileServer() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
