#include "offer_answer_server.h"
#include "client_nice_agent.h"


OfferAnswerServer::OfferAnswerServer(boost::asio::io_service* ptr_io_service, uint16_t port) 
{
    // Initialize Asio Transport
    m_server.init_asio(ptr_io_service);

    // Register handler callbacks
    m_server.set_open_handler(bind(&OfferAnswerServer::on_open,this,::_1));
    m_server.set_close_handler(bind(&OfferAnswerServer::on_close,this,::_1));
    m_server.set_message_handler(bind(&OfferAnswerServer::on_message,this,::_1,::_2));
    m_server.listen(port);
    m_server.start_accept();
}
//websocket 连接回调
void OfferAnswerServer::on_open(connection_hdl hdl) 
{    
    websocket_server::connection_ptr conn = m_server.get_con_from_hdl(hdl);
    std::cout << conn->get_uri()->str()  << " : " << conn->get_uri()->get_resource() << " - "<< conn->get_remote_endpoint() << std::endl;

    nice_agent_ptr agent = std::make_shared<ClientNiceAgent>(&m_server, hdl, true,this);            
    int nstreamid = agent->add_stream("audio", 1);
    agent->start_gather(nstreamid);
    RtcClient rtc_client;
    rtc_client.set_agent(agent);
    rtc_client.set_msgid(0);
    m_connections[hdl] = rtc_client;
}

void OfferAnswerServer::on_close(connection_hdl hdl) 
{        
    std::cout << "on_close" << std::endl;
    m_connections.erase(hdl);        
}

void OfferAnswerServer::on_message(connection_hdl hdl, websocket_server::message_ptr msg) 
{        
    std::cout << "on_message" << std::endl;            
    //m_server.send(hdl, "this great\r\n", websocketpp::frame::opcode::text);
    std::cout << msg->get_payload();
    RtcClient& rtc_client = get_data_from_hdl(hdl);
    if (0 == rtc_client.get_msgid())
    {
        rtc_client.get_agent()->set_remote_sdp(msg->get_payload().c_str());
    }
    else if (1 == rtc_client.get_msgid())
    {
        rtc_client.get_agent()->set_remote_candidate(msg->get_payload().c_str());
    }
    rtc_client.set_msgid(rtc_client.get_msgid()+1);
}
bool OfferAnswerServer::dispatchData(connection_hdl fromHdl,RtpQuePacketObj *rtpQuePacketObj){//这里要想把发最后销毁数据 还没做


    con_list::iterator iter;
    auto fromHdlIter = m_connections.find(fromHdl);
    int i=0;
    for(iter=this->m_connections.begin(); iter!=this->m_connections.end();iter++){
        connection_hdl hdl = iter->first;
        RtcClient rtc_client = iter->second;
        if(fromHdlIter==iter){//不发送给自己
            continue;
        }
        printf("dispatch:%d",i);
        rtc_client.get_agent()->pushDataToAgent(rtpQuePacketObj);
        i++;

    }

}
RtcClient& OfferAnswerServer::get_data_from_hdl(connection_hdl hdl) 
{    
    auto it = m_connections.find(hdl);

    if (it == m_connections.end()) {
        // this connection is not in the list. This really shouldn't happen
        // and probably means something else is wrong.
        throw std::invalid_argument("No data available for session");
    }

    return it->second;
}



