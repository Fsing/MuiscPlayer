#ifndef LOCALCLIENTPAY_H
#define LOCALCLIENTPAY_H

#include <QObject>
#include "./rtspClient/mutex.h"

//ffmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <SDL2/SDL.h>
};

class LocalPlayThread
{
public:
//    typedef void (*NotifyFun)( string songName,long user_info );
public:
    LocalPlayThread();

    ~LocalPlayThread();         //结束线程

    //解码并播放本地音乐
     int play(QString songName);
     void pause();

    //创建解码播放线程
    int create();

    // setting

private:
    bool m_is_destroyed;
    CMutex m_mutex;
    bool m_is_playing;
    pthread_t m_handle;
    string m_fileName;
    SDL_AudioSpec  wanted_spec;

    AVFormatContext     *pFormatCtx;
    AVCodecContext      *pCodecCtx;
    AVCodec             *pCodec;
    AVPacket            *packet;
    uint8_t             *out_buffer;
    AVFrame             *pFrame;

    //线程相关
//    NotifyFun m_fun;
//    long m_userinfo;

    //解码播放
    int decode(string fileName);
    static void *thread_fun(void *arg);
    //ffmpeg内部填充数据缓冲区callback
    static void call_back(void *udata,Uint8 *stream,int len);
};

#endif // LOCALCLIENTPAY_H
