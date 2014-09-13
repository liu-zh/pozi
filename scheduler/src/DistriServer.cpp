/*
 * DistriServer.cpp
 *
 *  Created on: 2014Äê8ÔÂ30ÈÕ
 *      Author: liuzhenhua
 */

#include "../include/DistriServer.h"

namespace server {

void DistriServer::handle_accept(socket_ptr sock,boost::shared_ptr<MultiVector> shared,const boost::system::error_code& error){
	if(!error){
		/*
 cout<<"receive the distribute request from "<<sock->remote_endpoint().address()<<endl;

 strcpy(sbuffer.name,"609");
 sbuffer.port = 609;
 cout<<"send message to MQ:"<<mq.sendMQ(&sbuffer)<<endl;
 memset(&sbuffer,'\0',sizeof(st_Request));
 cout<<"receive message from MQ:"<<mq.receiveMQ(&sbuffer)<<endl;
 cout<<"message:"<<sbuffer.name<<sbuffer.port<<endl;
 */
 boost::asio::async_read(*sock,
		 boost::asio::buffer(buf,3),
		 boost::bind(&DistriServer::handle_read,this,sock,shared,boost::asio::placeholders::bytes_transferred,boost::asio::placeholders::error));
 start_accept(shared);
	}else
		outerror(error);
}
void DistriServer::start_accept(boost::shared_ptr<MultiVector> shared){
		socket_ptr _socket(new tcp::socket(io_service));
		acceptor_.async_accept(*_socket,
		             boost::bind(&DistriServer::handle_accept,this,_socket,shared,boost::asio::placeholders::error));
	}
void DistriServer::handle_read(socket_ptr sock,boost::shared_ptr<MultiVector> shared,size_t st,const boost::system::error_code& error){
           if(!error){
             LOG4CPLUS_INFO(_logger, "distribute server receipt "<<buf);
             std::string mes(buf,st);
             if(!mes.compare("305")){
            //	 cout<<"vec list size"<<_vec.size()<<endl;
            	Counter  waiting  =   shared->next();
            	LOG4CPLUS_INFO(_logger,"arrnge the server: "<<waiting.getIP());
               boost::asio::async_write(*sock,
            		 boost::asio::buffer(waiting.getIP(),strlen(waiting.getIP().c_str())),
            		 boost::bind(&DistriServer::handle_write,this,sock,  shared,boost::asio::placeholders::error));
             }else if(!mes.compare(0,3,"306")){
                  std::string releaseIP = mes.substr(4);
                //  _vec.set(releaseIP);
                  boost::asio::async_write(*sock,
                 	            		 boost::asio::buffer("307",3),
                 	            		 boost::bind(&DistriServer::handle_write,this,sock,shared,boost::asio::placeholders::error));
             }
             }else
        	   outerror(error);
	}
void DistriServer::handle_write(socket_ptr sock,boost::shared_ptr<MultiVector> shared,const boost::system::error_code& error){
		if(!error){
         LOG4CPLUS_INFO(_logger,"distribute successfully!");
          //sock->close();
		}else
			outerror(error);
	}
void DistriServer::outerror(const boost::system::error_code& error){
		cerr<<error.message()<<endl;
	}

DistriServer::DistriServer(boost::asio::io_service& io_service,const int& port )
:acceptor_(io_service,tcp::endpoint(tcp::v4(), port)),io_service(io_service),counter(0)
{
	 _logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("FILE"));

}
 DistriServer::~DistriServer()
 {

 }
}
