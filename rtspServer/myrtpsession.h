#ifndef MYRTPSESSION_H
#define MYRTPSESSION_H

#include "thread.h"
#include "mutex.h"
#include "def.h"
#include "decodesrc.h"
#include <string>

using std::string;

//jirblib连接客户端，发送数据
//解码音频

class CRtpSession: public CThread
{
public:
    CRtpSession();
    ~CRtpSession();

public:
    //这个函数指针是用来释放CRtpSession对象的,user_info是fun需要的参数
    int Start(int fd, NotifyFun fun, long user_info);
    //开启解码线程
    int init(char *clienturl);
    //CRTPSession线程执行函数：从队列中读取数据，并发送
    virtual void thread_proc(long user_info);

    int Pause();
    int Play(string fileName, int len);
    //将解码和RTPSession线程destroy()
    int close();

    //setting
    void setClientIP(char *ip){strcpy(m_client_ip,ip);}
    void setClientPort(uint16_t port){m_client_port = port;}

    //data:需要拆分的字符串，len：data长度
    int get_ip(const char* data, int len, const char* s_mark, const char* e_mark);
    int get_port(const char *data,int len,const char *s_mark,const char *e_mark);
    int get_fileName(const char *data, int len, const char *s_mark);
private:
    CMutex m_mutex;                 //m_is_play修改锁
    bool m_is_Play;                 //判断是否pause
    long m_user_info;               //m_fun需要的参数：CRtspSession变量
    NotifyFun m_fun;                //CRtspSession::notify_fun()
    int m_fd;                       //RTSP sock fd
    char m_fileName[128];             //需要解码的文件名
    char m_client_ip[128];                 // 客户端地址：192.168.43.32
    char m_server_ip[128];
    uint16_t m_server_port;                //服务器端口
    uint16_t m_client_port;
    CDecodeSrc m_decodeSrc;         //解码变量

    bool m_is_new_connect;
};

#endif // RTPSESSION_H
