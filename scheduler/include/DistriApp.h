/*
 * GatewayServer.h
 *
 *  Created on: 2014年8月9日
 *      Author: liuzhenhua
 */

#ifndef GATEWAYSERVER_H_
#define GATEWAYSERVER_H_
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <vector>
#include "Counter.h"
#include "log.h"
#include "DistriServer.h"
#include "MultiVector.h"
using boost::asio::ip::tcp;
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
namespace server {
typedef boost::shared_ptr<tcp::socket> socket_ptr;

/*****************************
 * 负责文件服务器的
 * 注册请求
 */

/************************************
 * 负责分发客户端的服务资源请求
 */

class DistriApp {
private:

	int port;
	int distributePort;
	Logger _logger;
public:
	DistriApp(const int& distributePort);

	void startDistribute(boost::shared_ptr<MultiVector> shared);
	virtual ~DistriApp();
};

} /* namespace server */

#endif
