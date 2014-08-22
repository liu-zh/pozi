/*
 * Gateway.h
 *
 *  Created on: 2014��8��9��
 *      Author: liuzhenhua
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace std;
namespace server {
/**********************
 * enable_shared_from_this
 * 能在自己内部使用自己
 */
class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;
	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new tcp_connection(io_service));
	}

	~tcp_connection()
	{
		//socket_.close();
		std::cout << "tcp_connection destructor" << std::endl;
	}

	tcp::socket& socket()
	{
		return socket_;
	}
    /************************
     * 处理读
     */
	void start()
	{
		cout<<"-------read--"<<socket_.is_open()<<"------"<<endl;
		boost::asio::async_read(socket_,
			boost::asio::buffer(buf,3),
			boost::bind(&tcp_connection::handle_request, this,
			boost::asio::placeholders::error)
			);
		cout<<"-------read over--"<<socket_.is_open()<<"------"<<endl;
	}

	void handle_request(const boost::system::error_code& error)
	{
		cout<<"handle_request"<<endl;
		if (!error )
		{

			cout<<buf<<endl;
			/*
			boost::asio::async_read(socket_,
			boost::asio::buffer(buf),
			boost::bind(&tcp_connection::HandleReadFileChunk, shared_from_this(),	//shared_from_this()����һ��boost::shared_ptr���൱��this
			boost::asio::placeholders::error));
			*/
			cout<<socket_.is_open()<<endl;
			boost::asio::async_write(socket_,
					boost::asio::buffer("127",15),
					boost::bind(&tcp_connection::handle_response,this,
					boost::asio::placeholders::error));
		}
		else
		{
			cout<<"***error**********"<<endl;
			outerror(error);
			socket_.close();
		}
	}
    void handle_response(const boost::system::error_code& error)
    {
       if(!error){
    	   cout<<"write successfully"<<endl;
       }else{
    	   cerr<<"handle response function"<<endl;
    	   outerror(error);
    	   //socket_.close();
       }
    }
/*********************
 * 初始化tcp_connection
 */
private:
	tcp_connection(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}
	void outerror( const boost::system::error_code &error )
	{
		std::cout << error.message() << std::endl;
	}

private:

	//boost::array<char,128> buf;
    char buf[128];
	tcp::socket socket_;

};
class tcp_server
{
	/********************
	 * 1.首先初始化tcp::accepior
	 */
public:
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 6700))
	{
		/***************
		 * 2.启动监听
		 */
		start_accept();
	}

private:
	void start_accept()
	{
		tcp_connection::pointer new_connection =
		tcp_connection::create(acceptor_.io_service());

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			cout<<"accept the connect of "
								<<new_connection->socket().remote_endpoint().address()<<endl;
			new_connection->start();

			start_accept();
		}
	}

	tcp::acceptor acceptor_;
};
class Gateway {
private:
	tcp_server _server;
public:
	Gateway(boost::asio::io_service& io_service);
	virtual ~Gateway();
};

} /* namespace server */

#endif /* GATEWAY_H_ */
