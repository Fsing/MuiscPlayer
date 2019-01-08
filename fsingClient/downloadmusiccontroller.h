#ifndef DOWNLOADMUSICCONTROLLER_H
#define DOWNLOADMUSICCONTROLLER_H

//#include "head.h"
#include "fsingcontroller.h"

class DownloadMusicController : public FSingController
{
public:
    DownloadMusicController();
    ~DownloadMusicController() override;

    //判断服务端返回的消息的类型,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) override;
};

#endif // DOWNLOADMUSICCONTROLLER_H
