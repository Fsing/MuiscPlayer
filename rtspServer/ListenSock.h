#ifndef __INCLUDE_LISTEN_SOCK_H__
#define __INCLUDE_LISTEN_SOCK_H__

#include "Def.h"
#include "Sock.h"
#include "TcpSock.h"
#include "Thread.h"

//监听套接字类
class CListenSock : public CSock, public CThread
{
public:
	CListenSock();
	~CListenSock();
public:
    //创建套接字。并绑定ip和port.监听：Thread::listen()
	int Listen( const char* ip, int port );
private:
    //接收fd,创建会话对象
	virtual void accept_sock( int fd ){ return; }

    //accept():获得新的连接的socket fd
	virtual void thread_proc( long user_info );
};

#endif
