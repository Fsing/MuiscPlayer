#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

//#include "head.h"
#include "fsingcontroller.h"

class SearchController : public FSingController
{
public:
    SearchController();
    ~SearchController() override;

    //判断服务端返回的消息的类型,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) override;
};

#endif // SEARCHCONTROLLER_H
