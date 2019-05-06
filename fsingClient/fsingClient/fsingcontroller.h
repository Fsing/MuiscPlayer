#ifndef FSINGCONTROLLER_H
#define FSINGCONTROLLER_H
#include "songlist.h"
#include "song.h"
#include "json/json.h"
#include <string>
#include <QObject>

//typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class FSingController : public QObject
{
    Q_OBJECT
public:
    FSingController();
    virtual ~FSingController();

    //判断服务端返回的消息的类型（处理传过来的处理结果，不需要sock）,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) = 0;

    //歌单歌曲缓存
    static std::map<int,std::shared_ptr<SongList>> m_songListsMap;
    static std::map<int,std::shared_ptr<Song>> m_songsMap;
};

#endif // FSINGCONTROLLER_H
