#ifndef __INCLUDE_RTSP_CLIENT_H__
#define __INCLUDE_RTSP_CLIENT_H__

#include "Def.h"
#include "Thread.h"
#include "TcpSock.h"
#include "Mutex.h"
#include "MyRtpSession.h"

#include <time.h>
#include <string>

//RTSP客户端，创建并管理RTSP会话
class CRtspClient : CThread
{
public:
    //初始化成员变量
	CRtspClient();
    //销毁会话线程
	~CRtspClient();
public:
	typedef void (*DataCBFun)( const char* data, int len );
    //记录URl:m_base_url,连接服务器，发送OPTIONS命令
    //创建RTSP客户端线程
    int Start( const char* url, DataCBFun fun, long user_info,char *baseport );
	int GetRange();
    //send_play_cmd()
	int Play( int s_sec = -1, int e_sec = -1 );
    //send_simple_cmd()
	int Pause();
    //关闭会话， send_simple_cmd( RTSP_TEARDOWN ).服务端关闭对客户端的连接
	void Close();
private:
    //线程执行函数，循环检测是否有数据传入，并调用recev_data()处理
	virtual void thread_proc( long user_info );
    //从URL中提取ip、port,连接服务器.并将m_method设置为RTSP_OPTIONS.发送OPTIONS命令：send_simple_cmd()
	int open_sock( const char* url );
    //接收数据
	int recv_data();
    //处理数据
	int handle_data();
    //返回数据长度
	int parse_data( const char* data, int len );
    //处理命令，发送并处理建立前期的一系列命令
	int handle_cmd( const char* data, int len );
private:
    DataCBFun m_fun;                            //函数指针.用于处理接收到的消息中的具体的payload数据
    long m_user_info;                           //用户信息
    CTcpSock m_sock;                            //当前客户端的套接字
	enum{
        MAX_RECV_BUF_LEN = 1024*4,              //接收缓存大小
	};
    char m_recv_buf[MAX_RECV_BUF_LEN];          //接收缓存
    uint32_t m_recv_len;                        //缓存中数据的长度。下次接收，将放在已有数据的后面。buffer+len
    CMutex m_mutex;                             //访问数据的线程锁

    CRtpSession m_rtpSession;                   //RTP会话，接收数据

    uint16_t m_client_port;                     //客户端端口
private:
    //提取字符串字段
	int get_str( const char* data, const char* s_mark, bool with_s_make, const char* e_mark, bool with_e_make, char* dest );
    //提取服务器返回的处理结果标识（int)：200成功、、、、、
	int parse_rsp_code( const char* data, int len );
    //发送OPTIOINS命令
	int send_simple_cmd( RtspMethodT method ); 
    //发送DESCRIBE命令
	int send_describe_cmd();
    //发送SETUP命令
	int send_setup_cmd();
	int send_play_cmd( int s_sec, int e_sec );

    //处理命令返回的结果
    //获取url给m_base_url，提取音频大小给m_rang
	int parser_describe( const char* data, int len );
	int parser_setup( const char* data, int len );

    //发送调用命令的函数
	int send_cmd( const char* data, int len );

private:
    int m_cseq;                             //序列号
	int m_rtp_ch; 
    char m_session[128];                    //会话ID
    char m_base_url[256];                   //服务器URL
    RtspMethodT m_method;                   //rtsp请求命令的类型
	enum{
        MAX_MEDIA_NUM = 2,                  //最大媒体数：RTP、RTCP
	};
	struct MediaInfo{
		int index;
		char track_id[128];
	};
	MediaInfo m_media_info[MAX_MEDIA_NUM];
	int m_media_num;
	int m_media_index;
	int m_range;
};

#endif
