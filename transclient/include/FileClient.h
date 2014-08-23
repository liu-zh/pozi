/*
 * FileClient.h
 *
 *  Created on: 2014Äê8ÔÂ16ÈÕ
 *      Author: liuzhenhua
 */

#ifndef FILECLIENT_H_
#define FILECLIENT_H_
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <boost/filesystem.hpp>
#include "../include/util.h"
#include <vector>
using boost::asio::ip::tcp;
using namespace std;
namespace client {
class Filesend{

private:
	boost::asio::io_service& _io_service;
	tcp::socket _socket;
	char buf[128];
	char sendbuf[10240];
	vector<string> filelist;
	vector<string>::iterator iterator;
	boost::system::error_code error_a;

public:
	Filesend(boost::asio::io_service &_io_service,tcp::endpoint &end_point,vector<string> &flist):

		_io_service(_io_service),_socket(_io_service),filelist(flist){
		iterator = filelist.begin();
		_socket.async_connect(end_point,
		    		 boost::bind(&Filesend::handle_sendname,this,
		    		 boost::asio::placeholders::error));

	}


	void handle_sendname(const boost::system::error_code& error){

		if(!error){
            if((iterator == filelist.end())){
            	_socket.async_write_some(boost::asio::buffer("706",3),
             		   boost::bind(&Filesend::handle_close,this,boost::asio::placeholders::error));
            	return;
            }
			cout<<"filename receive:"<<buf<<endl;

		boost::filesystem::path full_path(*iterator);
				unsigned long long fsize = boost::filesystem::file_size(full_path);
				string sendname = full_path.filename()+"@"+longlongtostr(fsize);
				_socket.async_write_some(boost::asio::buffer(sendname,strlen(sendname.data())),
    		   boost::bind(&Filesend::handle_sendfile,this,boost::asio::placeholders::error));
		}else
			outerror(error);
	}
	void handle_sendfile(const boost::system::error_code& error){
		if(!error){
		ifstream ifs(iterator->c_str(),std::ios::binary);
		 if(!ifs.is_open()){
	     cout<<"could not open the file: "<<*iterator<<endl;
         return;
		 }
        unsigned long long readsize = 0;
		for(;;){
         ifs.read(sendbuf,10240);
         if(ifs.eof()) break;
         _socket.write_some(boost::asio::buffer(sendbuf,ifs.gcount()),error_a);
         readsize += ifs.gcount();

		}
		  boost::asio::write(_socket,boost::asio::buffer(sendbuf,ifs.gcount()));
		  readsize += ifs.gcount();
          ifs.close();
        boost::asio::async_read(_socket,
               		 boost::asio::buffer(buf,3),
               		 boost::bind(&Filesend::handle_sendname,this,boost::asio::placeholders::error));
        iterator++;
		}else
			outerror(error);
	}
	void handle_close(const boost::system::error_code& error){
       if(!error){
    	   _socket.close();
    	   cout<<"close successfully!"<<endl;
       }else
    	   outerror(error);
	}

	void outerror(const boost::system::error_code& error){
		cerr<<error.message()<<endl;
	}
	~Filesend(){
		//_socket.close();
		cout<<"destructor of request"<<endl;
	}

};
class FileClient {
private:
	Filesend _filesend;
public:
	FileClient(boost::asio::io_service &_io_service,tcp::endpoint &end_point,vector<string> &filelist);
	virtual ~FileClient();
};

} /* namespace server */

#endif /* FILECLIENT_H_ */
