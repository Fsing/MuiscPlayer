#ifndef ATTENUSERCONTROLLER_H
#define ATTENUSERCONTROLLER_H

//#include "head.h"
#include "fsingcontroller.h"

class AttenUserController : public FSingController
{
public:
    AttenUserController();
    ~AttenUserController() override;

    //判断服务端返回的消息的类型,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) override;
};

#endif // ATTENUSERCONTROLLER_H
