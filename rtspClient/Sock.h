#ifndef __INCLUDE_SOCK_H__
#define __INCLUDE_SOCK_H__

#include "Def.h"
#include <arpa/inet.h>

//套接字基类
class CSock{
public:
    //初始化套接字，fd=-1
    CSock();
    //调用close()
    virtual ~CSock();
public:
    //关闭套接字，对象析构时将自动调用
    void Close();
    //获取套接字fd
    //返回值：-1表示该套接字类不可用
    int GetFd() const;

    //绑定socket fd
    //参数：fd：socket fd
    //返回值：0成功，-1失败
    //给m_fd赋值
    int AttachFd( int fd );

    //解除绑定
    //返回值：之前绑定的fd
    int DetachFd();
    //发送
    //参数：buf：发送内容，len：发送长度
    //返回值: <0失败，>=0发送长度
    virtual int Send( const char* buf, int len ){ return -1; }
    //接收
    //参数：buf：接收缓存，len：接收缓存长度
    //返回值: <0失败，>=0接收长度
    virtual int Recv( char* buf, int len ){ return -1; }
protected:
    //创建套接字，并设置不阻塞
    int open( int sock_type );
     //绑定套接字
    int bind( const char* ip, int port );
    //从初始化sockaddr_in变量类型，从字符串中提取IP，并将ip、port等赋值给 sockaddr_in addr中的对应成员变量
    int get_addr( const char* ip, int port, sockaddr_in& addr );
    //设置。closesocket()后，再可重用该socket
    int set_addr_reuse();
    //设置套接字是否阻塞
    int set_block_opt( bool is_block );
protected:
    //无效的套接字文件标识符
    enum{
        INVALID_SOCK_FD = -1,
    };
    int m_fd;
};

#endif
