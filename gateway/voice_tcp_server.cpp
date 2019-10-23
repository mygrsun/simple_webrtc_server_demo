#include "voice_tcp_server.h"
using namespace boost::asio;
VoiceTcpServer::VoiceTcpServer():m_acceptor(m_io,ip::tcp::endpoint(ip::tcp::v4(), 6688)){
    this->accept();
    boost::thread tcp_thread(boost::bind(&VoiceTcpServer::run, this));

} 
void VoiceTcpServer::accept()
{
    sock_ptr sock(new ip::tcp::socket(m_io));
    m_acceptor.async_accept(*sock, boost::bind(&VoiceTcpServer::accept_handler, this, boost::asio::placeholders::error, sock));
}

void VoiceTcpServer::accept_handler(const boost::system::error_code& ec, sock_ptr sock)
{
    if (ec)
    {
        return;
    }
    cout << "Client:";
    cout << sock->remote_endpoint().address() << endl;

    // sock.async_read_some(boost::asio::buffer(1024),boost::bind(&VoiceTcpServer::ContinueRead, shared_from_this(),

	// 						boost::asio::placeholders::error,

	// 						boost::asio::placeholders::bytes_transferred));

    memset(m_szRecvBuffer, 0x00, 1024);
    sock->async_read_some(boost::asio::buffer(m_szRecvBuffer), boost::bind(&VoiceTcpServer::read_handler, this, boost::asio::placeholders::error,sock));
    // 发送完毕后继续监听，否则io_service将认为没有事件处理而结束运行
    this->accept();
}
void VoiceTcpServer::write_handler(const boost::system::error_code &ec)
{
    cout << "send msg complete" << endl;

}
void VoiceTcpServer::read_handler(const boost::system::error_code &ec, sock_ptr sock)
{
    cout << "read msg complete:"<< this->m_szRecvBuffer<< endl;
    sock->async_write_some(buffer("received your msg\n"), boost::bind(&VoiceTcpServer::write_handler, this, boost::asio::placeholders::error));
    sock->async_read_some(boost::asio::buffer(m_szRecvBuffer), boost::bind(&VoiceTcpServer::read_handler, this, boost::asio::placeholders::error,sock));

}
void VoiceTcpServer::run()
{
    m_io.run();
}

// void VoiceTcpServer::init(){

//     io_service my_io_service;
// 	ip::udp::endpoint local_endpoint(ip::address_v4::from_string("127.0.0.1"), 230);//create  a local endpoint
// 	ip::udp::endpoint romote_endpoint; //this enpoint is used to store the endponit from remote-computer
// 	ip::udp::socket socket(my_io_service, local_endpoint);//create socket and bind the endpoint
// 	char buffer[40000];
// 	int nAdd = 0;
// 	while (1)
// 	{
//         printf("wait receive\n");
// 		memset(buffer, 0, 40000);//to initialize variables
// 		nAdd++;
// 		socket.receive_from(boost::asio::buffer(buffer, 40000), romote_endpoint);//receive data from  remote-computer
// 		printf("recv %d datapacket:%s\n",nAdd, buffer);
// 	}

// }
