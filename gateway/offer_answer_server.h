#ifndef _WXH_OFFER_ANSWER_SERVER_H_
#define _WXH_OFFER_ANSWER_SERVER_H_


#include <websocketpp/config/asio_no_tls.hpp>

#include <websocketpp/server.hpp>
#include <rtp_rtcp.h>
#include <rtc_client.h>

#include <iostream>
#include <set>

/*#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>*/
#include <websocketpp/common/thread.hpp>

typedef websocketpp::server<websocketpp::config::asio> websocket_server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class ClientNiceAgent;
typedef std::shared_ptr<ClientNiceAgent> nice_agent_ptr;



class OfferAnswerServer 
{
public:
    OfferAnswerServer(boost::asio::io_service* ptr_io_service, uint16_t port);
    void on_open(connection_hdl hdl) ;
    void on_close(connection_hdl hdl) ;
    void on_message(connection_hdl hdl, websocket_server::message_ptr msg);    
    RtcClient& get_data_from_hdl(connection_hdl hdl);
    bool dispatchData(connection_hdl fromHdl,RtpQuePacketObj *rtpQuePacketObj);

private:    
     typedef std::map<connection_hdl,RtcClient,std::owner_less<connection_hdl>> con_list;
    websocket_server m_server;
    con_list m_connections;
};

#endif