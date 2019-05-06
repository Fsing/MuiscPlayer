#include "qmlrtspclient.h"
#include <fstream>
#include <iostream>

using std::ifstream;

long int myposition;

QmlRtspClient::QmlRtspClient()
{
    start("0.mp3");
    m_position = 0;
    m_munite_position = myposition = 0;
    m_playState = 0;
}

int QmlRtspClient::start(QString SongName)
{
    char url[128];
    char port[8];
    readUrl(url,port,SongName.toStdString());
    std::cout <<url <<endl;
    strncpy(m_client_port,port,strlen(port));
    //开启rtsp线程

    m_rtspClient.Start(url,data_cb_fun,0,m_client_port);
    _position.Start((long)this);
//    pthread_t handle;
//    pthread_create(&handle,nullptr,position_thread,this);
}

void QmlRtspClient::pause()
{
    m_playState = 0;
    emit playStateChanged();

    m_rtspClient.Pause();
    cout <<"QmlRtspClient->Pause: PlayState:  " << m_playState << endl;
}

void QmlRtspClient::play(QString songName)
{
    if(m_fileName == songName.toStdString()){
        cout <<"continue play,songName: " << songName.toStdString() << endl;
        m_rtspClient.continuePlay();
//        m_rtspClient.send_play_cmd(songName.toStdString());
    }else{
        cout<< "QmlRtspClient::play" << endl;
        m_position = myposition = 0;        //播放进度条设置为0
        m_playState = 1;                    //播放状态
        emit playStateChanged();

        m_fileName = songName.toStdString();
        string songname = songName.toStdString();
        m_rtspClient.Play(songName.toStdString());
    }
}

int QmlRtspClient::readUrl(char *url,char *port,string songName)
{
    memset(url,0,sizeof(url));
    memset(port,0,sizeof(port));

    ifstream fp;
    fp.open("config");

    char buf[128];
    memset(buf,0,sizeof(buf));

    //fp指向文件末尾
    fp.seekg(0,std::ios::end);
    int length = fp.tellg();        //文件长度
    fp.seekg(0,std::ios::beg);      //回到文件开头
    fp.read(buf,length);

    cout << buf << songName << endl;
    auto i = strstr(buf,"\n");
    strncpy(port,i+1,4);
    strncpy(url,buf,i-buf);

    url[strlen(url)] = '\0';
    std::cout << url << endl;
    strncpy(url+strlen(url)-4,songName.c_str(),songName.size());
    url[i-buf + songName.size()] = '\0';
    fp.close();
}

int QmlRtspClient::get_str(const char *data, const char *s_mark, bool with_s_make, const char *e_mark, bool with_e_make, char *dest)
{
    const char* satrt = strstr( data, s_mark );
    if( satrt != nullptr ){
        const char* end = strstr( satrt, e_mark );
        if( end != nullptr ){
            int s_pos = with_s_make ? 0 : strlen(s_mark);
            int e_pos = with_e_make ? strlen(e_mark) : 0;
            strncpy( dest, satrt+s_pos, (end-e_pos) - (satrt+s_pos) );
        }
        return 0;
    }
    return -1;
}

long QmlRtspClient::position()
{
    return m_position * 1000;
}

int QmlRtspClient::playState()
{
    return m_playState;
}

void QmlRtspClient::setPlayState(int l)
{
    m_playState = l;
    emit playStateChanged();
}

double QmlRtspClient::calculationDuration(QString duration)
{
    auto list = duration.split(":");
    int m = list[0].toInt() * 60;
    int s = list[1].toInt();
    //    cout <<"duration : " << m+s << endl;
    return (m+s) * 1000;
}

void QmlRtspClient::data_cb_fun(const char *data, int len)
{
    if( data == nullptr )
        LogInfo( "rtsp client close\n" );
    else{
        LogInfo( "data len:%d\n", len );
    }

}

//void *QmlRtspClient::position_thread(void *arg)
//{
//    QmlRtspClient *qmlClient = (QmlRtspClient*)arg;
//    while(1){
//        if(myposition - qmlClient->m_munite_position >= 1){
//            qmlClient->m_munite_position = myposition;

//            qmlClient->m_position++;
//            cout <<"position_thread: " << qmlClient->m_munite_position << endl;
//            emit qmlClient->positionChanged();
//        }
//    }
//}
