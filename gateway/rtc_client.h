#ifndef _WXH_RTC_CLIENT_H_
#define _WXH_RTC_CLIENT_H_
#include <iostream>
#include<memory>
// #include "common.h"
class ClientNiceAgent;

class RtcClient
{
    public:
        RtcClient();
        std::shared_ptr<ClientNiceAgent> get_agent();
        void set_agent(std::shared_ptr<ClientNiceAgent> agent);
        void set_msgid(uint32_t msgid);
        uint32_t get_msgid();
    private:
        std::shared_ptr<ClientNiceAgent> agent;
        std::string m_client_id;
        uint32_t msgid;
   
};

#endif