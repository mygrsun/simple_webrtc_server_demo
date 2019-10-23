#ifndef _WXH_VOICE_TCP_SERVER_H_
#define _WXH_VOICE_TCP_SERVER_H_
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
using namespace boost::asio;
using namespace std;
typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;

class VoiceTcpServer
{
public:
    VoiceTcpServer();
    // void init();
    void run();
    void accept();
    void accept_handler(const boost::system::error_code& ec, sock_ptr sock);
    void write_handler(const boost::system::error_code &ec);
    void read_handler(const boost::system::error_code &ec,sock_ptr sock);

private:
    io_service m_io;
    ip::tcp::acceptor m_acceptor;
    char m_szRecvBuffer[1024];
};

#endif