#include "fsingclient.h"
#include "head.h"

using std::endl;
using std::cout;
using namespace boost::asio;
using boost::system::error_code;
using boost::asio::ip::address;
using boost::asio::io_service;

io_service service;
ip::tcp::endpoint ep(address::from_string("203.6.224.219"),2001);
//客户端异步连接，有多个套接字，每次发送信息、接受信息都重新分配一个套接字，并且分配一个线程独立进行
ip::tcp::socket sock(service);


FSingClient::FSingClient()
{
    connect_server();
}

void FSingClient::connect_server()
{
    boost::system::error_code e;
    sock.async_connect(ep,[](const error_code &e){
        if(e){
            cout << e.message() << endl;
            return;
        }
    });

    service.run();
}
