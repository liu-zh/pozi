/*
 * GatewayClient.h
 *
 *  Created on: 2014��8��9��
 *      Author: liuzhenhua
 */

#ifndef GATEWAYCLIENT_H_
#define GATEWAYCLIENT_H_
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace std;
namespace client {
class request{
private:
	boost::asio::io_service& _io_service;

	tcp::socket _socket;
	char buf[128];
public:
	request(boost::asio::io_service &_io_service,tcp::endpoint &end_point):
	_io_service(_io_service),_socket(_io_service){
		_socket.async_connect(end_point,
		    		 boost::bind(&request::handle_connect,this,
		    		 boost::asio::placeholders::error));
	}

	void handle_connect(const boost::system::error_code& error){
     if(!error){
    	 cout<<"connect successfully!"<<endl;
    	 string address = _socket.local_endpoint().address().to_string();
    	 string registmsg =address +":10100";
         boost::asio::async_write(_socket,
        		 boost::asio::buffer(/*"701"*/registmsg,strlen(registmsg.c_str())),
        		 boost::bind(&request::handle_write,this,boost::asio::placeholders::error));
     }
	}
	void handle_write(const boost::system::error_code& error){
       if(!error){
    	   cout<<"write successfully!"<<endl;

            boost::asio::async_read (_socket,
        		   boost::asio::buffer(buf,3),
        		   boost::bind(&request::handle_read,this,boost::asio::placeholders::error));

       }else{
    	   outerror(error);
       }
	}
	void handle_read(const boost::system::error_code& error){
        if(!error){
           cout<<"receive the receiption:"<<buf<<endl;
           string mes(buf,3);
           if(!mes.compare("304")){
        	   cout<<"regist successfully";
        	   _socket.close();
           }

          // _socket.close();
        }else{
        	cout<<buf<<endl;
        	cout<<"***********handle_read***********"<<endl;
        	outerror(error);
        }
	}
	void outerror(const boost::system::error_code& error){
		cerr<<error.message()<<endl;
	}
	~request(){
		_socket.close();
		cout<<"destructor of request"<<endl;
	}
};
class GatewayClient {
private:
string ip;
int port;
public:
	GatewayClient(const string& ip,const int& port);
	bool regist();
	virtual ~GatewayClient();
};

} /* namespace client */

#endif /* GATEWAYCLIENT_H_ */
