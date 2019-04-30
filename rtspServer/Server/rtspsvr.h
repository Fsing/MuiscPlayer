#ifndef __INCLUDE_RTSP_SVR_H__
#define __INCLUDE_RTSP_SVR_H__

#include "listensock.h"
#include <map>
#include "rtspsession.h"
#include "myrtpsession.h"

//RTSP服务器。创建并管理RTSP会话
class CRtspSvr : public CListenSock
{
public: 
	CRtspSvr();
    //销毁m_ssession_map, 并destroy()、退出线程
	~CRtspSvr();
public:
    //开启服务器，开始监听指定端口，CThread::Listen()
	int Start( int port );
private:
    //创建CRtspSession对象，并调用CRtspSession::Start()[创建RtspSession thread]
    //在m_session_map中添加一个session对象
    //重载函数，处理新连接的socket fd
	virtual void accept_sock( int fd );
public:
    //在m_session_map中查找指定fd对应的session.若存在，则销毁该session对象，并从m_session_map中删除查找到的键值对对象
    //关闭会话
    //定期检测fd是否正常谅解，如果没有，则销毁RTSP对象
	static void notify_fun( long id, long msg, long user_info );
private:
	map<long, CRtspSession*> m_session_map;
//    map<long, CRtpSession *> m_rtpsession_map;
	CMutex m_mutex;
    int i = 0;
};

#endif
