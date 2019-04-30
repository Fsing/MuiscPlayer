#ifndef MYRTPSESSION_H
#define MYRTPSESSION_H

//jrtplib接收数据、并播放音频流

#include "thread.h"
#include "encodesrc.h"
#include <time.h>
#include <iostream>

//jrtplib
#include "rtpsession.h"
#include "rtpudpv4transmitter.h"

#include <jthread/jthread.h>

using jrtplib::RTPSession;
using jrtplib::SocketType;

class CRtpSession: public CThread
{
public:
    CRtpSession();
    ~CRtpSession();

public:
    //开启RTPSession Thread、解码线程
    int Start(const char *url);
    //线程执行函数
    virtual void thread_proc( long user_info );

    int close();            //关闭RTP接收数据会话
    int Pause();            //暂停数据
    void clear();           //清理数据缓存

    //get
     int get_port(const char *data,int len,const char *s_mark,const char *e_mark);
     int get_ip(const char *data,int len,const char *s_mark,const char *e_mark);

     //setting
     void setClientPort(uint16_t port){m_client_port =port;}
private:
     friend class CEncodeSrc;

public:
    CEncodeSrc m_encodeSrc;         //encodeSrc的thread_pro函数中，没有调用m_fun。跟随RtpSession的销毁而销毁
//    time_t m_startTime;                 //close会话开始的时间.单位为秒
//    time_t m_currentTime;
private:
    uint16_t m_client_port;                //客户读端口
    uint16_t m_server_port;                //服务器端口
    bool m_is_close;                    //是否关闭流媒体连接
    bool m_is_playing;
    char m_ip[128];                     //服务器地址

//    double duration;                    //播放时长
//    double position;                    //播放位置
};

//class MyRTPSession : public RTPSession
//{
//protected:
//    void onValidatedRTPPacket(RTPSourceData *srcdat, RTPPacket *rtppack, bool isonprobation, bool *ispackethandled);
//};
//class MyPollThread : public jthread::JThread
//{
//public:
//    MyPollThread(const SocketType &socket,const RTPSession session)
//        :m_socket(socket),m_session(session)
//    {

//    }

//private:
//    SocketType m_socket;
//    RTPSession m_session;
//};




























#endif // RTPSESSION_H
