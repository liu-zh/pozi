/*
 * RegistServer.cpp
 *
 *  Created on: 2014Äê8ÔÂ30ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/RegistServer.h"

namespace server {

RegistServer::RegistServer(boost::asio::io_service& io_service,const int& port)
:io_service(io_service),acceptor_(io_service,tcp::endpoint(tcp::v4(), port)) {
	// TODO Auto-generated constructor stub
	this->port = port;

	_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FILE"));
}


void RegistServer::handle_accept(socket_ptr sock,boost::shared_ptr<MultiVector> shared,const boost::system::error_code& error){

	if(!error){
		cout<<"(----------)"<<endl;
      cout<<"receive the regist request from "<<sock->remote_endpoint().address()<<endl;
			 LOG4CPLUS_INFO(_logger,"receive regist request from "<<sock->remote_endpoint().address());
      sock->async_read_some(
    		 boost::asio::buffer(buf,60),
    		 boost::bind(&RegistServer::handle_read,this,sock,shared,boost::asio::placeholders::bytes_transferred,boost::asio::placeholders::error));
     start_accept(shared);
		}else
			outerror(error);
	}
	void RegistServer::handle_read(socket_ptr sock,boost::shared_ptr<MultiVector> shared,size_t st,const boost::system::error_code& error){
           if(!error){
             LOG4CPLUS_INFO(_logger,"accept the regist messsge"<<buf);
             std::string mes(buf,st);
             Counter cnt(mes,320);
             shared->push(cnt);
             LOG4CPLUS_INFO(_logger,"The size of the pool: "<<shared->size());
             boost::asio::async_write(*sock,
            		 boost::asio::buffer("304",3),
            		 boost::bind(&RegistServer::handle_write,this,sock,boost::asio::placeholders::error));



           }else
        	   outerror(error);
	}
	void RegistServer::handle_write(socket_ptr sock,const boost::system::error_code& error){
		if(!error){
         LOG4CPLUS_INFO(_logger,"regist resource receiption:"<<sock->remote_endpoint().address());
          sock->close();
		}else
			outerror(error);
	}
	void  RegistServer::handle_close(socket_ptr sock,const boost::system::error_code& error){
         if(!error){
        	 sock->close();
         }else
        	 outerror(error);
	}
	/*
	void RegistServer::handle_comm(){
		while(true){
			if(_vec.size() > 0){

		      Counter cn = _vec.next();

			}
			}
	}
	*/
	void RegistServer::outerror(const boost::system::error_code& error){
		cerr<<error.message()<<endl;
	}
	void RegistServer::start_accept(boost::shared_ptr<MultiVector> shared){
	//	boost::asio::io_service io_service;
	//	tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port));

		socket_ptr _socket(new tcp::socket(io_service));
		try{
		acceptor_.async_accept(*_socket,
		             boost::bind(&RegistServer::handle_accept,this,_socket,shared,boost::asio::placeholders::error));
		}catch(exception& ex){
			cout<<"error occur: "<<ex.what()<<endl;
		}
	}
RegistServer::~RegistServer(){
	// TODO Auto-generated destructor stub
}

} /* namespace server */
