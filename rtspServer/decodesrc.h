#ifndef DECODESRC_H
#define DECODESRC_H

#include "thread.h"
#include "mutex.h"
#include <list>
//#include <memory>

//解码
#define BUFF_MAX_SIZE 1024

class CDecodeSrc:public CThread
{
public:
    CDecodeSrc();
    ~CDecodeSrc();
public:
    //开启解码线程
    int Start(char *fileName);

//    int close();
    //setting
    void setFileName(char *fileName);

    //put
    virtual void thread_proc(long user_info);
    //get
    int getNextPacket(uint8_t *buf,int buf_size,int64_t &spts);
    //清空m_packetList
    void clear();
private:
    struct PacketNode{
//        std::shared_ptr<uint8_t> buf;
        uint8_t *buf;           //buf要先用new分配内存再使用
        int length;    //<=1024
        int64_t pts;
    };
    std::list<PacketNode> m_packetList;         //数据缓冲队列
    CMutex m_mutex;                             //m_packetList数据队列缓冲区访问锁
    char m_fileName[128];                       //文件名
};
#endif // DECODESRC_H
