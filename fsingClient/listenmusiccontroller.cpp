#include "listenmusiccontroller.h"
#include "localmusic.h"

ListenMusicController::ListenMusicController()
{

}

ListenMusicController::~ListenMusicController()
{

}

void ListenMusicController::dealMessage(std::string type, Json::Value resultRoot)
{

}

QList<QObject *> ListenMusicController::getLocalSongInfo(QList<QString> dirList)
{
    LocalMusic localMusic;
    localMusic.setDirList(dirList);
    return localMusic.songList();
}
