#ifndef FSINGCONTROLLER_H
#define FSINGCONTROLLER_H
//#include "head.h"
#include "json/json.h"
#include <string>

//typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class FSingController
{
public:
    FSingController();
    virtual ~FSingController();

    //判断服务端返回的消息的类型（处理传过来的处理结果，不需要sock）,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) = 0;
};

#endif // FSINGCONTROLLER_H
