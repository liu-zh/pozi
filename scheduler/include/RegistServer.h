/*
 * RegistServer.h
 *
 *  Created on: 2014Äê8ÔÂ30ÈÕ
 *      Author: liuzhenhua
 */

#ifndef REGISTSERVER_H_
#define REGISTSERVER_H_
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <vector>
#include "../include/Counter.h"
#include "../include/log.h"
#include "MultiVector.h"

using boost::asio::ip::tcp;
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
namespace server {
typedef boost::shared_ptr<tcp::socket> socket_ptr;
class RegistServer {
private:
	tcp::acceptor acceptor_;
	boost::asio::io_service& io_service;
	char buf[128];

    Logger _logger;
    int port;

public:
	RegistServer(boost::asio::io_service& io_service,const int& port);
	void handle_accept(socket_ptr sock,boost::shared_ptr<MultiVector> shared,const boost::system::error_code& error);
	void handle_read(socket_ptr sock,boost::shared_ptr<MultiVector> shared,size_t st,const boost::system::error_code& error);
	void handle_write(socket_ptr sock,const boost::system::error_code& error);
	void start_accept(boost::shared_ptr<MultiVector> shared);

	void outerror(const boost::system::error_code& error);
	void  handle_close(socket_ptr sock,const boost::system::error_code& error);
	virtual ~RegistServer();
};

} /* namespace server */

#endif /* REGISTSERVER_H_ */
