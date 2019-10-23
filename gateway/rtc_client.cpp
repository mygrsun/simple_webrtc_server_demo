#include "rtc_client.h"
RtcClient::RtcClient(){
    
}
std::shared_ptr<ClientNiceAgent> RtcClient::get_agent(){
    return this->agent;
}
void RtcClient::set_agent(std::shared_ptr<ClientNiceAgent> agent){
    this->agent = agent;

}
void RtcClient::set_msgid(uint32_t msgid){
    this->msgid = msgid;

}
uint32_t RtcClient::get_msgid(){
    return this->msgid;

}