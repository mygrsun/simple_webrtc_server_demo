#include "voice_udp_server.h"
using namespace boost::asio;

VoiceUdpServer::VoiceUdpServer(){
     boost::thread udp_thread(boost::bind(&VoiceUdpServer::init, this));
 
}
void VoiceUdpServer::init(){

    io_service my_io_service;
	ip::udp::endpoint local_endpoint(ip::address_v4::from_string("127.0.0.1"), 2300);//create  a local endpoint
	ip::udp::endpoint romote_endpoint; //this enpoint is used to store the endponit from remote-computer
	ip::udp::socket socket(my_io_service, local_endpoint);//create socket and bind the endpoint
	char buffer[40000];
	int nAdd = 0;
	while (1)
	{   
        printf("wait receive\n");
		memset(buffer, 0, 40000);//to initialize variables
		nAdd++;
		socket.receive_from(boost::asio::buffer(buffer, 40000), romote_endpoint);//receive data from  remote-computer
		printf("recv %d datapacket:%s\n",nAdd, buffer);
	}

}
