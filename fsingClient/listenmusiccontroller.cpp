#include "listenmusiccontroller.h"
#include "localmusic.h"
#include <QDebug>

ListenMusicController::ListenMusicController()
{

}

ListenMusicController::~ListenMusicController()
{

}

void ListenMusicController::dealMessage(std::string type, Json::Value resultRoot)
{
    if(type == "INTERFACE"){
        const Json::Value arrayObj = resultRoot["array"];
        for (unsigned int i = 0; i < arrayObj.size(); i++){
            SongList songList(std::stoi(arrayObj[i]["id"].asString()),arrayObj[i]["name"].asString()
                    , arrayObj[i]["author"].asString()
                    ,arrayObj[i]["createTime"].asString(),arrayObj[i]["label"].asString()
                    ,arrayObj[i]["info"].asString(),arrayObj[i]["icon"].asString()
                    ,std::stoi(arrayObj[i]["collectionQuantity"].asString()),std::stoi(arrayObj[i]["clickQuantity"].asString())
                    ,std::stoi(arrayObj[i]["shareQuantity"].asString()));
            m_songList.push_back(songList);
        }
        const Json::Value advertArrayObj = resultRoot["advertArray"];
        for (unsigned int i = 0; i < advertArrayObj.size(); i++)
        {
            m_adverts.append(QString::fromStdString( advertArrayObj[i]["source"].asString()));
        }
    } else if (type == "SONGINFO"){
        m_songInformation.append(QString::number(resultRoot["id"].asInt()));
        m_songInformation.append(QString::fromStdString(resultRoot["name"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["singer"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["album"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["source"].asString()));
        m_songInformation.append(QString::number(resultRoot["playQuantity"].asInt()));
        m_songInformation.append(QString::number(resultRoot["downloadQuantity"].asInt()));
        m_songInformation.append(QString::number(resultRoot["shareQuantity"].asInt()));

        //add to song cache pool
        std::shared_ptr<Song> retSong = std::make_shared<Song>(
                    Song(resultRoot["id"].asInt(),
                    resultRoot["name"].asString(),
                resultRoot["singer"].asString(),
                resultRoot["album"].asString(),
                resultRoot["source"].asString(),
                resultRoot["playQuantity"].asInt(),
                resultRoot["shareQuantity"].asInt(),
                resultRoot["downloadQuantity"].asInt()));
        m_songsMap.insert(std::make_pair(resultRoot["id"].asInt(),retSong));
    }else if(type == "CREATESONGLIST"){

    }

}

QList<QString> ListenMusicController::getRecSongListNames()
{
    QList<QString> names;
    qDebug() << "QString::fromStdString((*it).getName())";
    if (m_songList.size() != 0)
        for (auto it = m_songList.begin(); it != m_songList.end(); it++){
            qDebug() << QString::fromStdString((*it).getName());
            names.append(QString::fromStdString((*it).getName()));
        }

    qDebug() << "Get RecListNames Complete!";
    return names;
}

QList<QObject *> ListenMusicController::getLocalSongInfo(QList<QString> dirList)
{
    LocalMusic localMusic;
    localMusic.setDirList(dirList);
    return localMusic.songList();
}
