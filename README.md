# simple_webrtc_server_demo
在原有另外一个大神开发的基础上实现了最简单的webrtc网关，可以实现群组通话。原先地址:https://www.jianshu.com/p/61e3c9e13456


原有demo只能实现将一个服务端视频或语音文件，通过浏览器webrtc播放。这里增加了上行流，和流转发。


基础原理就是，将一个端收到的rtp包，取出编码数据，然后重新封包转发给其它用户。每个用户都有一个队列用户存放待发送的包。

之前的demo在windows下编译，我这边改为了在linux下编译。




#安装方法是:



##基础组件安装
 
```
yum install git gtk-doc  libffi-devel zlib-devel pcre-devel openssl-devel lrzsz boost-devel nginx 
yum group install "Development Tools"
mkdir webrtcvoice
cd webrtcvoice
```
##库安装
glib安装
注意这里要至少安装2.56版本，不能使用yum安装glib。
```
cd /root/webrtcvoice
wget http://ftp.acc.umu.se/pub/GNOME/sources/glib/2.56/glib-2.56.1.tar.xz
tar -xvf glib-2.56.1.tar.xz 
cd glib-2.56.1
./configure --prefix=/usr/local/app/glib_2_56 --enable-libmount=no
make && make install
export PKG_CONFIG_PATH=/usr/local/app/glib_2_56/lib/pkgconfig
export PATH=/usr/local/app/glib_2_56/bin:$PATH
```
libnice 用于进行ice候选项生成和连接的建立
github地址：https://github.com/libnice/libnice

```
cd /root/webrtcvoice
git clone https://github.com/libnice/libnice
cd libnice
 sh autogen.sh
./configure --prefix=/usr/local/app/libnice
make && make install
```
libsrtp安装
注意这里需要1.x版本 我是在github上下载的1.6.0 然后rz上去的
```
cd /root/webrtcvoice
unzip libsrtp-1.6.0.zip 
cd libsrtp-1.6.0
./configure --prefix=/usr/local/app/libsrtp
make && make install
```
websocketpp 安装
注意 websocketpp 本身其实不用安装，直接从github上下载下来代码就可以了。
```
cd /root/webrtcvoice
git clone https://github.com/zaphoyd/websocketpp
```

openssl 安装
注意 在yum中已经安装了openssl，这里之所以还要编译安装是因为 代码需要更新版本的openssl
```
cd /root/webrtcvoice
wget https://www.openssl.org/source/openssl-1.1.1d.tar.gz
tar zxvf openssl-1.1.1d.tar.gz 
cd openssl-1.1.1d
./config --prefix=/usr/local/app/openssl
make && make install
```

## 运行库添加
将运行库加入到 /etc/ld.so.conf 如下图所示。 然后运行 /sbin/ldconfig -v
/usr/local/app/openssl/lib/
/usr/local/app/libnice/lib/

![图片描述](/tfl/captures/2019-10/tapd_20374522_base64_1571282284_67.png)

## 编译运行
运行sh create.sh进行编译。create.sh 是我写的编译脚本。
通过./webrtcgateway 开始运行。下图表示运行成功。


![图片描述](/tfl/captures/2019-10/tapd_20374522_base64_1571282164_72.png)


## nginx环境
nginx是为了代理websocket，因为webrtc的websocket必须使用https也就是wss，所以必须配置证书。

配置如下:
```


#user  nobody;
worker_processes  1;

#error_log  /root/logs/error.log;
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

#pid        logs/nginx.pid;


events {
    worker_connections  1024;
}


http {
    include       mime.types;
    default_type  application/octet-stream;

    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #access_log  logs/access.log  main;

    sendfile        on;
    #tcp_nopush     on;

    #keepalive_timeout  0;
    keepalive_timeout  65;

    #gzip  on;
	

	 server {
        listen       443 ssl;
        server_name  ericrtc.com;
        #charset koi8-r;
        location / {
			proxy_pass http://127.0.0.1:9002;
        	# WebScoket Support
        	proxy_http_version 1.1;
        	proxy_set_header Upgrade $http_upgrade;
        	proxy_set_header Connection "upgrade";

        	proxy_set_header Origin xxx;
        	proxy_set_header X-Real-IP $remote_addr;
        	proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        	proxy_set_header Host $http_host;
        	proxy_set_header X-NginX-Proxy true;
        }
		ssl_certificate  /root/ssl/ssl.crt;
		ssl_certificate_key /root/ssl/ssl.key;
		






    }
	

	 server {
        listen       443 ssl;
        server_name  webrtc.mygrsun.com;
        #charset koi8-r;
        location / {
			proxy_pass http://127.0.0.1:9002;
        	# WebScoket Support
        	proxy_http_version 1.1;
        	proxy_set_header Upgrade $http_upgrade;
        	proxy_set_header Connection "upgrade";

        	proxy_set_header Origin xxx;
        	proxy_set_header X-Real-IP $remote_addr;
        	proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        	proxy_set_header Host $http_host;
        	proxy_set_header X-NginX-Proxy true;
        }
		ssl_certificate  /root/webrtc_mygrsun_com_ssl/1_webrtc.mygrsun.com_bundle.crt;
		ssl_certificate_key /root/webrtc_mygrsun_com_ssl/2_webrtc.mygrsun.com.key;
		

    }
	
	 server {
        listen       9054 ssl;
        server_name  ericrtc.com;
        #charset koi8-r;
        location / {
            root   html;
            index  index.html index.htm;
        }
		ssl_certificate  /root/ssl/ssl.crt;
		ssl_certificate_key /root/ssl/ssl.key;
		

    }

    server {
        listen       81;
        server_name  localhost;

        #charset koi8-r;

        #access_log  logs/host.access.log  main;

        location / {
            root   html;
            index  index.html index.htm;
        }

        #error_page  404              /404.html;

        # redirect server error pages to the static page /50x.html
        #
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }

      
    }

    server {
        listen       81;
        server_name  webrtc.mygrsun.com;

        #charset koi8-r;

        #access_log  logs/host.access.log  main;

        location / {
            root   html;
            index  index.html index.htm;
        }

        #error_page  404              /404.html;

        # redirect server error pages to the static page /50x.html
        #
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }

      
    }




}




```

## 其它
###libnice 打开调试 方法
文档在:https://nice.freedesktop.org/libnice/libnice-Debug-messages.html
设置环境变量:
export G_MESSAGES_DEBUG=all
export NICE_DEBUG=all
代码中调用nice_debug_enable(true)
注意:不需要重新编译libnice 就可以打开调试

### 关于腾讯云部署
腾讯云开通公网地址后，ifconfig中看不到公网地址，这是腾讯云特有的一种机制。需要开通eip直通文档如下：https://cloud.tencent.com/document/product/213/12540
如果没有使用弹性网卡，需要先转成弹性网卡https://cloud.tencent.com/document/product/213/16586
因为腾讯云的eip直通处于体验阶段，所以需要提交腾讯云工单，之后才可以开通。（没开通前 页面中没有开通按钮）



