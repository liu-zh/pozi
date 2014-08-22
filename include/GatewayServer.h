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
#include <vector>
using boost::asio::ip::tcp;
using namespace std;
namespace server {
typedef boost::shared_ptr<tcp::socket> socket_ptr;
class response{
private:
	tcp::acceptor acceptor_;
	boost::asio::io_service& io_service;
	char buf[128];
    vector<string> filelist;
	void handle_accept(socket_ptr sock,const boost::system::error_code& error){
		if(!error){
     cout<<"receive the connection from "<<sock->remote_endpoint().address()<<endl;
     boost::asio::async_read(*sock,
    		 boost::asio::buffer(buf,3),
    		 boost::bind(&response::handle_read,this,sock,boost::asio::placeholders::error));
     start_accept();
		}else
			outerror(error);
	}
	void handle_read(socket_ptr sock,const boost::system::error_code& error){
           if(!error){
             cout<<buf<<endl;
             boost::asio::async_write(*sock,
            		 boost::asio::buffer("127.0.0.1:10100",15),
            		 boost::bind(&response::handle_write,this,sock,boost::asio::placeholders::error));
           }else
        	   outerror(error);
	}
	void handle_write(socket_ptr sock,const boost::system::error_code& error){
		if(!error){
         cout<<"write successfully!"<<endl;
          sock->close();
		}else
			outerror(error);
	}
	void handle_close(socket_ptr sock,const boost::system::error_code& error){
         if(!error){
        	 sock->close();
         }else
        	 outerror(error);
	}
	void outerror(const boost::system::error_code& error){
		cerr<<error.message()<<endl;
	}
	void start_accept(){
		socket_ptr _socket(new tcp::socket(io_service));
		acceptor_.async_accept(*_socket,
		             boost::bind(&response::handle_accept,this,_socket,boost::asio::placeholders::error));
	}

public:
	response(boost::asio::io_service& io_service)
    :acceptor_(io_service,tcp::endpoint(tcp::v4(), 6700)),io_service(io_service)
    {

		start_accept();

	}
	 ~response()
	 {

	 }
};
class GatewayServer {
private:
	response _response;
public:
	GatewayServer(boost::asio::io_service& io_service);
	virtual ~GatewayServer();
};

} /* namespace server */

#endif /* GATEWAYSERVER_H_ */
