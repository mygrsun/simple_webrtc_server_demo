CC = g++
CFLAGS = -std=c++0x
#这里是定义了一些变量
libnicestr=-I /usr/local/app/glib_2_56/include/ -I /usr/local/app/libnice/include/nice -I /usr/local/app/glib_2_56/lib/glib-2.0/include/ -I /usr/local/app/glib_2_56/include/glib-2.0/ -L /usr/local/app/glib_2_56/lib/ -L /usr/local/app/libnice/lib/  -lnice -lgio-2.0 -lgobject-2.0 -lgthread-2.0 -pthread -lglib-2.0
websocketppstr=-pthread  -I /usr/local/boost/include -I /root/websocketpp -L /usr/local/boost/lib -lboost_system -lboost_date_time -lboost_regex -lboost_random -lboost_chrono
booststr=-I /usr/include/boost/thread/ -lboost_thread
srtp=-I /usr/local/app/libsrtp/include/ -L /usr/local/app/libsrtp/lib/ -lsrtp
openssllib=-I /usr/local/app/openssl/include/ -L /usr/local/app/openssl/lib -lssl -lcrypto
CINCLUDE_CLIB_CLD=$(booststr) $(libnicestr) $(websocketppstr) $(srtp) $(openssllib)
OBJECTS=offer_answer_server.o rtp_rtcp.o dtls_srtp.o client_nice_agent.o webrtcgateway.o voice_udp_server.o voice_tcp_server.o rtc_client.o
webrtcgateway:$(OBJECTS)
	$(CC) $(CFLAGS) -o webrtcgateway $(OBJECTS) -I ./ $(CINCLUDE_CLIB_CLD)
#
offer_answer_server.o:offer_answer_server.cpp
	$(CC) $(CFLAGS) -o offer_answer_server.o -c offer_answer_server.cpp  -I ./ $(CINCLUDE_CLIB_CLD)
rtp_rtcp.o:rtp_rtcp.cpp
	$(CC) $(CFLAGS) -o rtp_rtcp.o -c rtp_rtcp.cpp  -I ./ $(CINCLUDE_CLIB_CLD)
dtls_srtp.o:dtls_srtp.cpp	
	$(CC) $(CFLAGS) -o dtls_srtp.o -c dtls_srtp.cpp  -I ./ $(CINCLUDE_CLIB_CLD)
client_nice_agent.o:client_nice_agent.cpp
	$(CC) $(CFLAGS) -o client_nice_agent.o -c client_nice_agent.cpp  -I ./ $(CINCLUDE_CLIB_CLD)
webrtcgateway.o:webrtcgateway.cpp
	$(CC) $(CFLAGS) -o webrtcgateway.o -c webrtcgateway.cpp  -I ./ $(CINCLUDE_CLIB_CLD)
voice_udp_server.o:voice_udp_server.cpp
	$(CC) $(CFLAGS) -o voice_udp_server.o -c voice_udp_server.cpp  -I ./ $(CINCLUDE_CLIB_CLD)
voice_tcp_server.o:voice_tcp_server.cpp
	$(CC) $(CFLAGS) -o voice_tcp_server.o -c voice_tcp_server.cpp  -I ./ $(CINCLUDE_CLIB_CLD)
rtc_client.o:rtc_client.cpp
	$(CC) $(CFLAGS) -o rtc_client.o -c rtc_client.cpp  -I ./ $(CINCLUDE_CLIB_CLD)

	
 #  .PHONY 表示clean是一个伪目标
 .PHONY:clean
 #clean rm前面的横杠 表示错误忽略
clean:
	-rm webrtcgateway $(OBJECTS)

