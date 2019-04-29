#ifndef LOCALMUSICPLAY_H
#define LOCALMUSICPLAY_H

#include <QObject>
#include <map>
#include <string>

#include "localPlayThread.h"
#include "./rtspClient/mutex.h"

using std::string;

class LocalPlayThreadContain
{
public:
//    LocalMusicPlay();

    //解码并播放本地音乐
    Q_INVOKABLE void play(QString songName);
//    Q_INVOKABLE void pause();

    //释放new对象
//    static void notify_fun( string songName, long user_info );
public:
    std::map<string,LocalPlayThread*> m_localPlay;
    CMutex m_mutex;
};

#endif // LOCALMUSICPLAY_H
