#ifndef __INCLUDE_RTSP_SESSION_H__
#define __INCLUDE_RTSP_SESSION_H__

#include "def.h"
#include "thread.h"
#include "tcpsock.h"
#include "mutex.h"
#include <time.h>
#include <string>
#include "datasrc.h"
#include "myrtpsession.h"

//RTSP会话类，处理RTSP请求、响应
class CRtspSession :  public CThread
{
public:
    //初始化成员变量
	CRtspSession();
	~CRtspSession();
public:
    //m_fun赋值、m_user_info赋值、绑定m__sock的m_fd、Cthread::Create(thread_fun):创建线程"RtspSessionThread"
    //start在RtspSvr::accetp_sock()函数中被调用，user_info参数其实就是RtspSession
	int Start( int fd, NotifyFun fun, long user_info );

    //setting
    void setClientIP(char *ip);
    void setClientPort(uint16_t port);
    void setServerPort(uint16_t port);

    //getting
    char *getClientIP(){return m_client_ip;}
    uint16_t getClientPort(){return m_client_port;}

    //调用m_rtpSession.close();，destroy()解码和RTPSession线程
    int close();
private:
    //重载CThread::thread_proc(),线程执行处理函数(线程函数为thread_fun())
    //循环检测指定socket是否有数据传入（select())，recv_data()接收数据
	virtual void thread_proc( long user_info );
    //接收数据，CSock::Recv(),调用handle_data()处理数据
	int recv_data();

    //OPTION
    //处理接收到的数据
    //循环处理，直到将当前缓冲区中的数据被处理完（在数据处理完之前，不会读取新的数据，因为在之前处理之前已经上锁。
	int handle_data();
    //计算接收到的数据的长度
	int parse_data( const char* data, int len );
    //提取请求中的命令，并调用对应的处理函数处理数据
	int handle_cmd( const char* data, int len );

    int parse_Client_port();

private:
    //停止rtsp线程之下的子线程的运行
//    virtual void delete_rtspSession(int fd);
private:
    NotifyFun m_fun;        //函数指针
    long m_user_info;       //m_fun参数：RtspSvr类型
	CTcpSock m_sock;
	enum{
		MAX_RECV_BUF_LEN = 1024*4,
	};
    char m_recv_buf[MAX_RECV_BUF_LEN];          //存放接收的数据
    uint32_t m_recv_len;                        //接收到的数据长度
    CMutex m_mutex;                             //访问数据的线程锁
    CDataSrc m_data_src;                        //文件打开，提取SDP等
    CRtpSession m_rtpSession;                   //数据发送RTP会话

    //客户端地址、ip
    char m_client_ip[128];
    uint16_t m_client_port;
//    uint16_t m_server_port;

//    char *m_fileName[64];

private:
    //判断请求的命令是什么，并返回（describe、option、play、、、）
	RtspMethodT parse_method( const char* data, int len );
    //从接收到的数据中提取出sceq,消息序列号，并赋值给m_sceq
	void parser_common( const char* data, int len );
    //从接收到的数据中提取出rtsp url，并赋值给m_url,如：rtsp://192.168.43.32:5544/test.mp3
	int parser_url( const char* data, int len );
    //在data中找到s_mark开始-e_mark结束之间的字符串，并赋值给dest
	int get_str( const char* data, int len, const char* s_mark, const char* e_mark, char* dest, int dest_len );

    //根据命令，处理数据----------------
    int handle_describe( const char* data, int len );
	int handle_setup( const char* data, int len );
	int handle_play( const char* data, int len );
	int handle_pause();
	int handle_teardowm();
    //只发送一个200 ok响应
	int handle_other_method();
    //----------------------------------------

    //向客户端发送错误码
	int send_simple_cmd( int code ); 
    //向客户端发送对应的处理结果响应，m_sock::Send()
	int send_cmd( const char* data, int len );

private:
    //用于关闭会话：CRtspSvr::notify_fun()
	static void notify_fun( long id, long msg, long user_info );
private:
    char m_cseq[128];           //消息序列
    int m_rtp_ch;
    char m_session[128];        //会话ID
    char m_url[256];            //客户端地址
};

#endif
