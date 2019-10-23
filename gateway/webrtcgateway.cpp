
#include <stdio.h>
#include "offer_answer_server.h"
#include "client_nice_agent.h"
#include "voice_udp_server.h"
#include "voice_tcp_server.h"



//int _tmain(int argc, _TCHAR* argv[])
void nice_thread_handle();
int main(int argc, char* argv[])
{      
    boost::thread nice_thread(nice_thread_handle);

    VoiceTcpServer voiceTcpServer;
    VoiceUdpServer voiceUdpServer;

    nice_thread.join();
}

void nice_thread_handle(){
    ClientNiceAgent::init();

    boost::asio::io_service service;
    OfferAnswerServer server_instance(&service, 9002);
    boost::system::error_code ec;
    service.run(ec);

    ClientNiceAgent::release();
}