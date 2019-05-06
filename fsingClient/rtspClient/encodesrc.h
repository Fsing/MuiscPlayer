#ifndef ENCODESRC_H
#define ENCODESRC_H

//存储数据，并编码播放


#include "thread.h"
#include <list>
#include "mutex.h"

//extern "C"
//{
//#include <libavcodec/avcodec.h>
//}

struct PacketNode{
    uint8_t *buf;           //buf要先用new分配内存再使用
    int length;    //<=1024
};


class CEncodeSrc : public CThread
{
public:
    CEncodeSrc();
    ~CEncodeSrc();
    friend int fill_iobuffer(void *opaque,uint8_t *buf,int bufsize);
//    friend int getNextPacket(uint8_t *buf,int buf_size);

public:
    //开启编码播放线程
    int Start();

    //清理缓存
    void clear();

    //解码，读取数据
    virtual void thread_proc(long user_info);

    //get
    int getNextPacket(uint8_t *buf,int buf_size);
    int readBuf(uint8_t *data, int len);
    //put
    int put_packetNode(PacketNode p);
    //停止播放
    void pause();
    void play();
    bool isPlay(){return m_is_play;}

private:

    std::list<PacketNode> m_packetList;         //数据缓冲队列
    CMutex m_mutex;
    bool m_is_play;                             //是否正在播放

    double m_duration;                    //播放时长
    double m_position;                    //播放位置
};

#endif // ENCODESRC_H
