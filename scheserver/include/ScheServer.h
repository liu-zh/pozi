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
#include "../include/Counter.h"
using boost::asio::ip::tcp;
using namespace std;
namespace server {
typedef boost::shared_ptr<tcp::socket> socket_ptr;
/**************************
 * 共享资源队列
 */
class multivector{
private:
	pthread_mutex_t pmt;
	vector<Counter> vec;
	 int number  ;
public:
	multivector():number(0){
     pthread_mutex_init(&pmt,NULL);
     cout<<"初始化共享资源队列的锁"<<endl;
	}
	void push(Counter t){
        pthread_mutex_lock(&pmt);
        bool isHave = false;
        int i = 0;
        for(;i < vec.size();i++){
        	if(vec[i] == t){
        		isHave = true;
        		break;
        	}
        }
        if(!isHave)
		  vec.push_back(t);
        pthread_mutex_unlock(&pmt);
	}
	Counter& next(){
		Counter cnt;
		pthread_mutex_lock(&pmt);
		cnt = vec[number++%vec.size()];
		pthread_mutex_unlock(&pmt);
		return cnt;
	}
	/*
	 bool  increase(Counter t){
		  bool isFind = false;
		 pthread_mutex_lock(&pmt);
		   int i = 0;
		   for(;i < vec.size();i++){
           if(vec[i] == t){
        	   vec[i].inc();
        	   isFind = true;
        	   break;
           }
		   }
		 pthread_mutex_unlock(&pmt);
        return isFind;
	}
	 bool decrease(Counter t){
		 bool isFind = false;
				 pthread_mutex_lock(&pmt);
				   int i = 0;
				   for(;i < vec.size();i++){
		           if(vec[i] == t){
		        	   vec[i].inc();
		        	   isFind = true;
		        	   break;
		           }
				   }
				 pthread_mutex_unlock(&pmt);
		        return isFind;
	 }
      */
	 int size(){
		 return vec.size();
	 }
	 bool set(string ip){
			 bool isFind = false;
					 pthread_mutex_lock(&pmt);
					   int i = 0;
					   for(;i < vec.size();i++){
			           if(!vec[i].getIP().compare(ip)){
			        	   vec[i].inc();
			        	   isFind = true;
			        	   break;
			           }
					   }
					 pthread_mutex_unlock(&pmt);
			        return isFind;
		 }
	 Counter& get(int i){
		 Counter cnt;
		 pthread_mutex_lock(&pmt);
		     vec[i].dec();
		     cnt = vec[i];
		  pthread_mutex_unlock(&pmt);
		  return cnt;
	 }
	~multivector(){
        pthread_mutex_destroy(&pmt);
        cout<<"销毁锁......"<<endl;
	}
};
/*****************************
 * 负责文件服务器的
 * 注册请求
 */
class response{
private:
	tcp::acceptor acceptor_;
	boost::asio::io_service& io_service;
	char buf[128];
    multivector _vec;
	void handle_accept(socket_ptr sock,const boost::system::error_code& error){
		if(!error){
     cout<<"receive the regist request from "<<sock->remote_endpoint().address()<<endl;

     boost::asio::async_read(*sock,
    		 boost::asio::buffer(buf,60),
    		 boost::bind(&response::handle_read,this,sock,boost::asio::placeholders::bytes_transferred,boost::asio::placeholders::error));
     start_accept();
		}else
			outerror(error);
	}
	void handle_read(socket_ptr sock,size_t st,const boost::system::error_code& error){
           if(!error){
             cout<<"accept the messsge"<<buf<<endl;
             string mes(buf,st);
             Counter cnt(mes,320);
             _vec.push(cnt);

             boost::asio::async_write(*sock,
            		 boost::asio::buffer("304",3),
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
	response(boost::asio::io_service& io_service,const int& port,multivector& vec)
    :acceptor_(io_service,tcp::endpoint(tcp::v4(), port)),io_service(io_service),_vec(vec)
    {
		start_accept();
	}
	 ~response()
	 {

	 }
};
/************************************
 * 负责分发客户端的服务资源请求
 */
class distribute{
private:
	tcp::acceptor acceptor_;
	boost::asio::io_service& io_service;
	char buf[128];
    multivector _vec;
    int counter;
	void handle_accept(socket_ptr sock,const boost::system::error_code& error){
		if(!error){
     cout<<"receive the distribute request from "<<sock->remote_endpoint().address()<<endl;

     boost::asio::async_read(*sock,
    		 boost::asio::buffer(buf,3),
    		 boost::bind(&distribute::handle_read,this,sock,boost::asio::placeholders::bytes_transferred,boost::asio::placeholders::error));
     start_accept();
		}else
			outerror(error);
	}
	void start_accept(){
			socket_ptr _socket(new tcp::socket(io_service));
			acceptor_.async_accept(*_socket,
			             boost::bind(&distribute::handle_accept,this,_socket,boost::asio::placeholders::error));
		}
	void handle_read(socket_ptr sock,size_t st,const boost::system::error_code& error){
	           if(!error){
	             cout<<"accept the messsge"<<buf<<endl;
	             string mes(buf,st);
	             if(!mes.compare("305")){
	            	Counter& waiting =  _vec.next();
                   boost::asio::async_write(*sock,
	            		 boost::asio::buffer(waiting.getIP(),strlen(waiting.getIP().c_str())),
	            		 boost::bind(&distribute::handle_write,this,sock,boost::asio::placeholders::error));
	             }else if(!mes.compare(0,3,"306")){
                      string releaseIP = mes.substr(4);
                      _vec.set(releaseIP);
                      boost::asio::async_write(*sock,
                     	            		 boost::asio::buffer("307",3),
                     	            		 boost::bind(&distribute::handle_write,this,sock,boost::asio::placeholders::error));
	             }
	             }else
	        	   outerror(error);
		}
	void handle_write(socket_ptr sock,const boost::system::error_code& error){
			if(!error){
	         cout<<"distribute successfully!"<<endl;
	          sock->close();
			}else
				outerror(error);
		}
	void outerror(const boost::system::error_code& error){
			cerr<<error.message()<<endl;
		}
public:
	distribute(boost::asio::io_service& io_service,const int& port,multivector& vec)
    :acceptor_(io_service,tcp::endpoint(tcp::v4(), port)),io_service(io_service),_vec(vec),counter(0)
    {
		start_accept();
	}
	 ~distribute()
	 {

	 }
};
class ScheServer {
private:
   // MultiVector<string> vec;
	multivector vec;
	int port;
	int distributePort;
public:
	ScheServer(const int& port,const int& distributePort);
	void startRegist();
	void startDistribute();
	void  execute();
	virtual ~ScheServer();
};

} /* namespace server */

#endif
