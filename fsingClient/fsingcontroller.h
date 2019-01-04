#ifndef FSINGCONTROLLER_H
#define FSINGCONTROLLER_H
#include "head.h"

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class FSingController
{
public:
    FSingController();

    //判断服务端返回的消息的类型,并调用相应的处理函数
    std::string dealMessage(std::string sig, std::vector<std::string> str, socket_ptr sock);
};

#endif // FSINGCONTROLLER_H
