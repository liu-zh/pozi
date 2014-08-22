/*
 * FileClient.cpp
 *
 *  Created on: 2014Äê8ÔÂ16ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/FileClient.h"

namespace client {

FileClient::FileClient(boost::asio::io_service &_io_service,tcp::endpoint &end_point,vector<string> &filelist):
		_filesend(_io_service,end_point, filelist){
	// TODO Auto-generated constructor stub

}

FileClient::~FileClient() {
	// TODO Auto-generated destructor stub
}

} /* namespace server */
