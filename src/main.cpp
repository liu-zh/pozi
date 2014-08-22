/*
 * main.cpp
 *
 *  Created on: 2014Äê8ÔÂ9ÈÕ
 *      Author: liuzhenhua
 */
#include "../include/GatewayClient.h"
#include "../include/FileClient.h"
using boost::asio::ip::tcp;
using namespace std;
int main(){
	vector<string> filelist;
	filelist.push_back("E:/newinter.rar");
	filelist.push_back("E:/20140724.rar");
	boost::asio::io_service io_service;
	tcp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 6700);
	//client::GatewayClient cli(io_service,end_point);
	client::FileClient cli(io_service,end_point,filelist);
	io_service.run();
	return 0;
}



