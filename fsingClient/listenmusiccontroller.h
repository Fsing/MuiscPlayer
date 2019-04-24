#ifndef LISTENMUSICCONTROLLER_H
#define LISTENMUSICCONTROLLER_H

//#include "head.h"
#include "fsingcontroller.h"
//#include "json/json.h"
//#include <string>
#include "localmusic.h"

class ListenMusicController : public FSingController
{
    Q_OBJECT
public:
    ListenMusicController();
    ~ListenMusicController() override;

    //判断服务端返回的消息的类型,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) override;

    QList<QObject *> getLocalSongInfo(QList<QString> dirList);
};

#endif // LISTENMUSICCONTROLLER_H
