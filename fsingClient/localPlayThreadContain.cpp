#include "localPlayThreadContain.h"
#include <map>
#include <iostream>

using std::cout;            using std::endl;

void LocalPlayThreadContain::play(QString songName)
{
    //先结束现有的播放线程
    if(!m_localPlay.empty()){
        cout <<"clear m_localPlay" << endl;
        auto it = m_localPlay.begin();
        delete it->second;
        it->second = nullptr;
        m_localPlay.erase(it);
    }

    LocalPlayThread *local = new LocalPlayThread;
    if(local->play(songName) == 0){
        m_mutex.Enter();
        m_localPlay[songName.toStdString()] = local;
        m_mutex.Leave();
    }else{
        delete local;
    }
}
