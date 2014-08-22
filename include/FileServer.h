/*
 * FileServer.h
 *
 *  Created on: 2014年8月16日
 *      Author: liuzhenhua
 */

#ifndef FILESERVER_H_
#define FILESERVER_H_
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <fstream>
using boost::asio::ip::tcp;
using namespace std;
namespace server {
typedef boost::shared_ptr<tcp::socket> socket_ptr;

class Filereceive{

private:
	tcp::acceptor acceptor_;
	boost::asio::io_service& io_service;
	char buf[128];
	char readbuf[10240];
	string currentfile;
	boost::system::error_code error_a;

	void handle_filetrans(socket_ptr sock,const boost::system::error_code& error){
        if(!error){
        	cout<<"receive the connection from "<<sock->remote_endpoint().address()<<endl;

        	sock->async_read_some(
        		boost::asio::buffer(buf,128),
        		boost::bind(&Filereceive::handle_readdata,this,sock,boost::asio::placeholders::bytes_transferred,boost::asio::placeholders::error));
        start_accept();
        }else
        	outerror(error);
	}
	void handle_readdata(socket_ptr sock, size_t rsize,const boost::system::error_code& error){
		if(!error){

        string fname(buf,rsize);
         cout<<"receive the filename string: "<<fname<<endl;
         if(!fname.compare("706")){
        	 cout<<"client connection close!"<<endl;
        	 sock->close();
        	 return;
         }
        string filename = fname.substr(0,fname.find_last_of("@"));
        string strfilesize = fname.substr(fname.find_last_of("@")+1);
        unsigned long long filesize = atoll(strfilesize.c_str());
       // cout<<"receive filename "<<filename<<" filesize:"<<filesize<<"bytes"<<endl;
        ofstream  ofs(filename.c_str(),std::ios::binary);
        unsigned long long readsize = 0;
        size_t st;

        for(;;){
        	 st = sock->read_some( boost::asio::buffer(readbuf,10240),error_a);

         if(error_a == boost::asio::error::eof){
        	 cout<<"finish read"<<endl;
        	 break;
         }
         if(st <= 0) break;
         readsize += st;
         ofs.write(readbuf,st);
         if(readsize == filesize) break;
        }

        ofs.flush();
        ofs.close();
        cout<<filename<<" transfer complete!"<<endl;
		}else
			outerror(error);

         sock->async_write_some(
            		 boost::asio::buffer("705",3),
            		 boost::bind(&Filereceive::handle_filetrans,this,sock,boost::asio::placeholders::error));


	}



	void outerror(const boost::system::error_code& error){
		cerr<<error.message()<<endl;
	}
	void start_accept(){
		socket_ptr _socket(new tcp::socket(io_service));
		acceptor_.async_accept(*_socket,
		             boost::bind(&Filereceive::handle_filetrans,this,_socket,boost::asio::placeholders::error));
	}

public:
	Filereceive(boost::asio::io_service& io_service)
    :acceptor_(io_service,tcp::endpoint(tcp::v4(), 6700)),io_service(io_service)
    {

		start_accept();

	}
	 ~Filereceive()
	 {

	 }

};
class FileServer {
private:
	Filereceive _filereceive;
public:
	FileServer(boost::asio::io_service& io_service);
	virtual ~FileServer();
};

} /* namespace server */

#endif /* FILESERVER_H_ */
