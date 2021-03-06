#include "listenmusiccontroller.h"
#include "localmusic.h"
#include "lyric.h"
#include <QDebug>
#include <iostream>

ListenMusicController::ListenMusicController()
{

}

ListenMusicController::~ListenMusicController()
{

}

void ListenMusicController::dealMessage(std::string type, Json::Value resultRoot)
{
    try{
        if(type == "INTERFACE"){
            std::string interfaceName = resultRoot["interfaceName"].asString();
            if (interfaceName == "FINDMUSIC"){
                std::cout << "deal FINDMUSIC" << std::endl;
                getOnlineSongList(resultRoot);
            }else{
                getRecSongList(resultRoot);
            }
        } else if (type == "SONGINFO"){
            songInfo(resultRoot);
        }else if (type == "SONGLIST"){
            songListInfo(resultRoot);
        }else if(type == "COMMENT"){
            getSongListComment(resultRoot);
        }else if(type == "ADDCOMMENT"){

        }else if (type == "COMMENTLIKE"){

        }
    }catch(...){
        std::cout<< "listenMusicController dealMessage error!" << std::endl;
    }
}

void ListenMusicController::getRecSongList(Json::Value resultRoot)
{
    const Json::Value arrayObj = resultRoot["array"];
    for (unsigned int i = 0; i < arrayObj.size(); i++){
        std::shared_ptr<SongList> songList = std::make_shared<SongList>(std::stoi(arrayObj[i]["id"].asString()),arrayObj[i]["name"].asString()
                , arrayObj[i]["author"].asString()
                ,arrayObj[i]["createTime"].asString(),arrayObj[i]["label"].asString()
                ,arrayObj[i]["info"].asString(),arrayObj[i]["icon"].asString()
                ,std::stoi(arrayObj[i]["collectionQuantity"].asString()),std::stoi(arrayObj[i]["clickQuantity"].asString())
                ,std::stoi(arrayObj[i]["shareQuantity"].asString()));
        //m_songList.push_back(songList);
        m_songList.insert(std::make_pair(std::stoi(arrayObj[i]["id"].asString()),songList));

    }
    std::cout << m_songList.size() << std::endl;

    //std::cout << m_songList.size() << std::endl;
    const Json::Value advertArrayObj = resultRoot["advertArray"];
    for (unsigned int i = 0; i < advertArrayObj.size(); i++)
    {
        m_adverts.append(QString::fromStdString( advertArrayObj[i]["source"].asString()));
    }
}

void ListenMusicController::getOnlineSongList(Json::Value resultRoot)
{
    m_onlineSongList.clear();
    const Json::Value arrayObj = resultRoot["array"];
    for (unsigned int i = 0; i < arrayObj.size(); i++){
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["id"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["name"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["author"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["createTime"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["label"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["info"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["icon"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["collectionQuantity"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["clickQuantity"].asString()));
        m_onlineSongList.append(QString::fromStdString(arrayObj[i]["shareQuantity"].asString()));
    }
    std::cout <<"m_onlineSongList.size() :  " << m_onlineSongList.size() << std::endl;
}

QList<QString> ListenMusicController::getOnlineSongListsInfo()
{
    return m_onlineSongList;
}

QList<QString > ListenMusicController::getSongListBasicInfo(QString recSongListId)
{
    QList<QString> res;
    if (m_songList.size() != 0){
        //auto songList = m_songList[recSongListId.toInt()];
        auto songList = m_songList.find(recSongListId.toInt())->second;
        QString id = QString::number(songList->getId(),10);
        QString name = QString::fromStdString(songList->getName());
        QString author = QString::fromStdString(songList->getAuthor());
        QString createTime = QString::fromStdString(songList->getCreateTime());
        QString label = QString::fromStdString(songList->getLabel());
        QString info = QString::fromStdString(songList->getInfo());
        QString icon = QString::fromStdString(songList->getIcon());
        QString collectionQuantity = QString::number(songList->getCollectionQuantity(),10);
        QString clickQuantity = QString::number(songList->getClickQuantity(),10);
        QString shareQuantity = QString::number(songList->getShareQuantity(),10);

        res.append(id);
        res.append(name);
        res.append(author);
        res.append(createTime);
        res.append(label);
        res.append(info);
        res.append(icon);
        res.append(collectionQuantity);
        res.append(clickQuantity);
        res.append(shareQuantity);
    }
    return res;
}

bool ListenMusicController::findSongList(QString songListId)
{
    if (m_songListsMap.find(songListId.toInt()) != m_songListsMap.end()){
        return true;
    }
    return false;
}

void ListenMusicController::songInfo(Json::Value resultRoot)
{
    //add to song cache pool
    std::shared_ptr<Song> retSong = std::make_shared<Song>(
                Song(resultRoot["id"].asInt(),
                resultRoot["name"].asString(),
            resultRoot["singer"].asString(),
            resultRoot["album"].asString(),
            resultRoot["source"].asString(),
            resultRoot["time"].asString(),
            resultRoot["playQuantity"].asInt(),
            resultRoot["shareQuantity"].asInt(),
            resultRoot["downloadQuantity"].asInt()));
    m_songsMap.insert(std::make_pair(resultRoot["id"].asInt(),retSong));
}

void ListenMusicController::songListInfo(Json::Value resultRoot)
{
    const Json::Value arrayObj = resultRoot["array"];
    std::shared_ptr<SongList> ret = std::make_shared<SongList>(SongList(resultRoot["id"].asInt(),
                                                               resultRoot["name"].asString(),
            resultRoot["author"].asString(),
            resultRoot["createTime"].asString(),
            resultRoot["label"].asString(),
            resultRoot["info"].asString(),
            resultRoot["icon"].asString(),
            resultRoot["collectionQuantity"].asInt(),
            resultRoot["clickQuantity"].asInt(),
            resultRoot["shareQuantity"].asInt()));
    std::map<int,std::shared_ptr<Song>> songs;
    for (unsigned int i = 0; i < arrayObj.size(); i++)
    {
        std::shared_ptr<Song> retSong = std::make_shared<Song>(
                    Song(arrayObj[i]["id"].asInt(),
                    arrayObj[i]["name"].asString(),
                arrayObj[i]["singer"].asString(),
                arrayObj[i]["album"].asString(),
                arrayObj[i]["source"].asString(),
                arrayObj[i]["time"].asString(),
                arrayObj[i]["playQuantity"].asInt(),
                arrayObj[i]["shareQuantity"].asInt(),
                arrayObj[i]["downloadQuantity"].asInt()));
        songs.insert(std::make_pair(arrayObj[i]["id"].asInt(),retSong));
        //add to song cache pool
        m_songsMap.insert(std::make_pair(arrayObj[i]["id"].asInt(),retSong));
    }
    ret->setSongs(songs);
    m_songListsMap.insert(std::make_pair(resultRoot["id"].asInt(),ret)) ;
}

QList<QString> ListenMusicController::getSongListSongs(QString songListId)
{
    if(songListId != ""){
        std::cout << "songListId: " << songListId.toInt() << std::endl;
        std::shared_ptr<SongList> songlist = m_songListsMap[songListId.toInt()];
        QList<QString> ret;
        ret.clear();

        auto songs = songlist->getSongs();
        for(auto &l : songs){
            auto song = l.second;
            ret.append(QString::number(song->getId()));
            ret.append(QString::fromStdString(song->getName()));
            ret.append(QString::fromStdString(song->getSinger()));
            ret.append(QString::fromStdString(song->getAlbum()));
            ret.append(QString::fromStdString(song->getSource()));
            ret.append(QString::fromStdString(song->getTime()));
            ret.append(QString::number(song->getPlayQuantity()));
            ret.append(QString::number(song->getDownloadQuantity()));
            ret.append(QString::number(song->getShareQuantity()));
        }
        return ret;
    }
}

void ListenMusicController::getSongListComment(Json::Value resultRoot)
{
    m_comments.clear();
    const Json::Value arrayObj = resultRoot["array"];
    for (unsigned int i = 0; i < arrayObj.size(); i++)
    {
        m_comments.append(QString::fromStdString( arrayObj[i]["accountId"].asString()));
        m_comments.append(QString::fromStdString( arrayObj[i]["accountName"].asString()));
        m_comments.append(QString::fromStdString( arrayObj[i]["comment"].asString()));
        m_comments.append(QString::fromStdString(arrayObj[i]["icon"].asString()));
        m_comments.append(QString::fromStdString(arrayObj[i]["points"].asString()));
    }
    std::cout << "m_comments.count():        " << m_comments.count() << std::endl;
}

QList<QString> ListenMusicController::getCommnets()
{
    return m_comments;
}

QList<QObject *> ListenMusicController::getLyric(QString filePath)
{
    Lyric lyric;
    return lyric.resolveLyric(filePath);
}

//void ListenMusicController::getSongListInfo(QString songListId)
//{
//    if (m_songListsMap.find(songListId.toInt()) != m_songListsMap.end()){

//    }
//}

QList<QString> ListenMusicController::getRecSongListNames()
{
    QList<QString> names;
    if (m_songList.size() != 0){
        for (auto it = m_songList.begin(); it != m_songList.end(); it++){
            auto songList = it->second;
            QString name = QString::fromStdString(songList->getName());
            names.append(name);
        }
    }
    return names;
}

QList<QString> ListenMusicController::getRecSongListIcons()
{
    QList<QString> icons;
    if (m_songList.size() != 0){
        for (auto it = m_songList.begin(); it != m_songList.end(); it++){
            auto songList = it->second;
            QString icon = QString::fromStdString(songList->getIcon());
            icons.append(icon);
        }
    }
    return icons;
}

QList<int> ListenMusicController::getRecSongListClickQuantity()
{
    QList<int> clickQuantitys;
    if (m_songList.size() != 0){
        for (auto it = m_songList.begin(); it != m_songList.end(); it++){
            auto songList = it->second;
            int clickQuantity = songList->getClickQuantity();
            clickQuantitys.append(clickQuantity);
        }
    }
    return clickQuantitys;
}

QList<QString> ListenMusicController::getAdvertsImages()
{
    qDebug() << "enter getAdvertsImages";
    qDebug() << m_adverts.size();
    QList<QString> res;
    res.clear();
    if (m_adverts.size() != 0){
        for (int i = 0; i < m_adverts.size(); i++){
            qDebug() << m_adverts[i];
            res.append(m_adverts[i]);
        }
    }
    return res;
}

QList<QString> ListenMusicController::getRecSongListIds()
{
    QList<QString> ids;
    if (m_songList.size() != 0){
        for (auto it = m_songList.begin(); it != m_songList.end(); it++){
            auto songList = it->second;
            QString icon = QString::number(songList->getId(),10);
            ids.append(icon);
        }
    }
    return ids;
}

QList<QObject *> ListenMusicController::getLocalSongInfo(QList<QString> dirList)
{
    LocalMusic localMusic;
    localMusic.setDirList(dirList);
    return localMusic.songList();
}
