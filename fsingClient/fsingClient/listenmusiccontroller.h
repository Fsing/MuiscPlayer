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
    //获取推荐歌单图片集合
    QList<QString> getRecSongListIcons();
    //获取推荐歌单的Id集合
    QList<QString> getRecSongListIds();
    //获取推荐歌单基本信息集合
    QList<QString> getRecSongListBasicInfo(QString recSongListId);
    //获取歌单实体
    bool findSongList(QString songListId);
    //获取歌单信息
    //void getSongListInfo(QString songListId);

    //获取歌单歌曲集合
    QList<QString> getSongListSongs(QString songListId);

    //获取歌单评论信息
    void getSongListComment(Json::Value resultRoot);
    QList<QString> getCommnets();

    //获取歌词信息
    QList<QObject *> getLyric(QString filePath);
    //获取本地歌曲信息
    QList<QObject *> getLocalSongInfo(QList<QString> dirList); 


    //广告的source
    QList<QString> m_adverts;
    //推荐歌单
    //std::vector<SongList> m_songList; //歌单的基本信息
    //QMap<QString, SongList> m_songList;
    std::map<int,std::shared_ptr<SongList>> m_songList;

    QList<QString> m_songInformation;
    //评论信息
    QList<QString> m_comments;

    //歌单歌曲缓存
    std::map<int,std::shared_ptr<SongList>> m_songListsMap;
    std::map<int,std::shared_ptr<Song>> m_songsMap;
};

#endif // LISTENMUSICCONTROLLER_H
