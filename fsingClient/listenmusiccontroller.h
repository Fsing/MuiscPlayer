#ifndef LISTENMUSICCONTROLLER_H
#define LISTENMUSICCONTROLLER_H

//#include "head.h"
#include "fsingcontroller.h"
//#include "json/json.h"
//#include <string>
#include "localmusic.h"
#include "songlist.h"
#include "song.h"

class ListenMusicController : public FSingController
{
    Q_OBJECT
public:
    ListenMusicController();
    ~ListenMusicController() override;

    //判断服务端返回的消息的类型,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) override;

    //获取推荐歌单名字集合
    QList<QString> getRecSongListNames();
    //获取推荐歌单图片
    QList<QString> getRecSongListIcons();

    //获取本地歌曲信息
    QList<QObject *> getLocalSongInfo(QList<QString> dirList);

    //广告的source
    QList<QString> m_adverts;
    //推荐歌单
    std::vector<SongList> m_songList;
    QList<QString> m_songInformation;

    //歌单歌曲缓存
    std::map<int,std::shared_ptr<SongList>> m_songListsMap;
    std::map<int,std::shared_ptr<Song>> m_songsMap;
};

#endif // LISTENMUSICCONTROLLER_H
