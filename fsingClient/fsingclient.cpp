#include "fsingclient.h"
#include "listenmusiccontroller.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

using std::endl;
using std::cout;
using namespace boost::asio;
using boost::system::error_code;
using boost::asio::ip::address;
using boost::asio::io_service;

io_service service;
ip::tcp::endpoint ep(address::from_string("127.0.0.1"),2001);
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

void FSingClient::receiveMessage(std::string &&string)
{

}

QList<QObject *> FSingClient::getLocalSongInfo(QList<QString> dirList)
{
    ListenMusicController listenMusicController;
    return listenMusicController.getLocalSongInfo(dirList);
}

