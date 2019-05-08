#include "rtspsession.h"
#include "printlog.h"
#include <string.h>
#include "ntime.h"
#include <iostream>
#include <sstream>
#include <pthread.h>

CRtspSession::CRtspSession()
{
    m_fun = nullptr;
    m_user_info = 0;
    memset( m_recv_buf, 0, sizeof(m_recv_buf) );        //清空初始化
    m_recv_len = 0;
    //////////////////
    memset( m_cseq, 0, sizeof(m_cseq) );
    m_rtp_ch = 0;
    memset( m_session, 0, sizeof(m_session) );
    memset( m_url, 0, sizeof(m_url) );
}

CRtspSession::~CRtspSession()
{
    Destroy();
    WaitExit();
}

int CRtspSession::Start( int fd, NotifyFun fun, long user_info )
{
    //上锁
    CGuard lock( m_mutex );
    m_fun = fun;
    m_user_info = user_info;
    m_sock.AttachFd( fd );
//    m_rtpSession.setClientPort(m_client_port);
    m_rtpSession.setClientIP(m_client_ip);
    if( Create( "RtspSessionThread", 0 ) < 0 ){
        LogError( "create thread  RtspSessionThread failed\n" );
        return -1;
    }
    return 0;
}

void CRtspSession::setClientIP(char *ip){
    strcpy(m_client_ip,ip);
}

void CRtspSession::setClientPort(uint16_t port){
    m_client_port = port;
}

void CRtspSession::setServerPort(uint16_t port)
{
    m_rtpSession.setServerPort(port);
}

//重载CThread::thread_proc(),线程执行处理函数(线程函数为thread_fun())
//循环检测指定socket是否有数据传入（select())，recv_data()接收数据
void CRtspSession::thread_proc( long user_info )
{
    int ret = 0;
    while( IsDestroyed() == false ){
        CGuard lock( m_mutex );         //上锁
        fd_set read_fd_set;         //fd_set文件描述符集，测试指定的fd可读？可写？有异常条件待处理？
        fd_set except_fd_set;
        FD_ZERO( &read_fd_set );	//WRITE_EVENT，将指定的文件描述符集清空，初始化
        FD_ZERO( &except_fd_set );	//EXCEPT_EVENT
        FD_SET( m_sock.GetFd(), &read_fd_set );             //将套接字加入集合，在文件描述符集合中添加一个新的文件名描述符
        FD_SET( m_sock.GetFd(), &except_fd_set );
        //用于描述一段时间长度，如果在这个时间内，需要监视的描述符没有事件发生则函数返回，返回值为0
        struct timeval tmv_timeout={ 0L, 1000L };//单位毫秒，默认1秒超时

        //这里要+1
        if( select( m_sock.GetFd()+1, &read_fd_set, nullptr, &except_fd_set, &tmv_timeout ) > 0  ){    //检查套接字是否可读，是否有数据，
            if( FD_ISSET( m_sock.GetFd(), &read_fd_set ) != 0 ){        //检查套接字是否在集合中，因为select将更新这个集合,把其中不可读的套节字去掉，只保留符合条件的套节字在这个集合里面

                //表示有数据，接收数据
                if( recv_data() < 0 ){
                    ret = -1;
                    break;
                }
            }
            if( FD_ISSET( m_sock.GetFd(), &except_fd_set ) != 0 ){          //是否有异常
                LogError( "session net exception\n" );
                ret = -1;
                break;
            }
        }
    }

    m_rtpSession.Destroy();
//    std::cout <<"RTSPSession close" <<endl;
    //会话结束，销毁服务器对象中的df对应的那个会话.销毁相应对象
//    m_rtpSession.close();       //结束RTPSession线程和解码线程
//    if( m_fun != nullptr )
//        m_fun( m_sock.GetFd(), RTSP_SESSION_CLOSE, m_user_info);
//    pthread_exit((void*)("Exit RtspSessionThread secessful .\n"));             //线程退出，在pthread_join(handle,&ret)里面，会将这段话赋值给ret
}

//void CRtspSession::delete_rtspSession(int fd)
//{
//    //结束rtp和decode线程的执行
//    m_rtpSession.close();
//    notify_fun(fd,RTSP_SESSION_CLOSE,m_user_info);
//}

int CRtspSession::recv_data()
{
    int recv_len = sizeof(m_recv_buf)-1-m_recv_len;     //缓冲区剩余大小
    if( recv_len <= 0 ){
        LogError( "recv buf len <=0 ,buffer full\n" );
        return -1;
    }
    int ret = m_sock.Recv( m_recv_buf+m_recv_len, recv_len );
    if( ret < 0 ){
        LogError( "recv data failed\n" );
        return -1;
    }
    m_recv_len += ret;
    return handle_data();
}

int CRtspSession::handle_data()
{
    char *recv_buf = m_recv_buf;
    m_recv_buf[m_recv_len] = '\0';
    int ret = -1;
    while( m_recv_len > 0 ){
        ret = 0;
        if( '$' == *recv_buf ){
            //第一次传入客户读啊端口：
            ret = parse_Client_port();
            m_recv_len -=strlen(m_recv_buf);
            recv_buf += strlen(m_recv_buf);

            break;
//            if( m_recv_len <= sizeof(struct RtpTcpHdr) )
//                break;
//            struct RtpTcpHdr* r_t_hd = (struct RtpTcpHdr *)recv_buf;
//            uint32_t r_t_len = ntohs(r_t_hd->len);
//            if( m_recv_len < r_t_len + 4 )
//                break;
//            ;//handle rtcp
//            m_recv_len -= r_t_len + 4;
//            recv_buf += r_t_len + 4;
        }else{
            int parser_ret = parse_data( recv_buf, m_recv_len );
            if( parser_ret < 0 )
                break;
            //输出请求信息
            PRINT_RECV_CMD( recv_buf, parser_ret );
            if( handle_cmd( recv_buf, parser_ret ) < 0 )
                return -1;
            m_recv_len -= parser_ret;
            recv_buf += parser_ret;
        }
    }
    if( strlen(m_recv_buf) > 0 )
        memmove( m_recv_buf , recv_buf, strlen(m_recv_buf) );
    return ret;
}

int CRtspSession::parse_Client_port()
{
    char port[5];
    memset(port,0,sizeof(port));
    strncpy(port,m_recv_buf+1,4);
    string s(port);
    stringstream ss(s);
    ss >> m_client_port;
    m_rtpSession.setClientPort(m_client_port);

    //需要发送的返回的消息
    char cmd[128];
    memset(cmd,0,sizeof (cmd));
    snprintf( cmd, sizeof(cmd),
        "$RTSP/1.0 200 OK\r\n"
        );
    return send_cmd(cmd,strlen(cmd));
}


int CRtspSession::parse_data( const char* data, int len )
{
    const char *start = data;
    const char *end_mark = "\r\n\r\n";      //结束标志
    const char *end = nullptr;
    //strstr判断end_mark是否是start的子串，返回在start中首次出现的位置
    if( nullptr == (end = strstr(start, end_mark)) )
        return -1;
    int header_len = end - start + strlen(end_mark);
    int content_len = 0;
    const char* conten_len_mark = "Content-Length ";
    const char* content_len_pos = strstr(end, conten_len_mark);
    if( content_len_pos != nullptr && strstr(content_len_pos, "\r\n") != nullptr )
        content_len = atoi( content_len_pos+strlen(conten_len_mark) );
    if( len < (header_len + content_len) )
        return -1;
    return (header_len + content_len);
}

int CRtspSession::handle_cmd( const char* data, int len )
{
    RtspMethodT method = parse_method( data, len );
    if( method == RTSP_METHOD_MAX ){
        LogError( "unsupported this method\n" );
        return -1;
    }
    parser_common( data, len );
    switch( method ){
    case RTSP_DESCRIBE:
        return handle_describe( data, len );
    case RTSP_SETUP:
        return handle_setup( data, len );
    case RTSP_PLAY:
        return handle_play( data, len );
    case RTSP_PAUSE:
        return handle_pause();
    case RTSP_TEARDOWN:
        return handle_teardowm();
    default:
        return handle_other_method();
    }
    return 0;
}


////////////////////////////////////////////
RtspMethodT CRtspSession::parse_method( const char* data, int len )
{
    RtspMethodT rtsp_method = RTSP_METHOD_MAX;
    if( *data == 'O' && strncmp( data, g_method[RTSP_OPTIONS].method_str, strlen(g_method[RTSP_OPTIONS].method_str) ) == 0 )
        rtsp_method = RTSP_OPTIONS;
    else if( *data == 'D' && strncmp( data, g_method[RTSP_DESCRIBE].method_str, strlen(g_method[RTSP_DESCRIBE].method_str) ) == 0 )
        rtsp_method = RTSP_DESCRIBE;
    else if( *data == 'S' && strncmp( data, g_method[RTSP_SETUP].method_str, strlen(g_method[RTSP_SETUP].method_str) ) == 0 )
        rtsp_method = RTSP_SETUP;
    else if( *data == 'P' && strncmp( data, g_method[RTSP_PLAY].method_str, strlen(g_method[RTSP_PLAY].method_str) ) == 0 )
        rtsp_method = RTSP_PLAY;
    else if( *data == 'P' && strncmp( data, g_method[RTSP_PAUSE].method_str, strlen(g_method[RTSP_PAUSE].method_str) ) == 0 )
        rtsp_method = RTSP_PAUSE;
    else if( *data == 'T' && strncmp( data, g_method[RTSP_TEARDOWN].method_str, strlen(g_method[RTSP_TEARDOWN].method_str) ) == 0 )
        rtsp_method = RTSP_TEARDOWN;
    else if( *data == 'S' && strncmp( data, g_method[RTSP_SET_PARAMETER].method_str, strlen(g_method[RTSP_SET_PARAMETER].method_str) ) == 0 )
        rtsp_method = RTSP_SET_PARAMETER;
    else if( *data == 'G' && strncmp( data, g_method[RTSP_GET_PARAMETER].method_str, strlen(g_method[RTSP_GET_PARAMETER].method_str) ) == 0 )
        rtsp_method = RTSP_GET_PARAMETER;
    return rtsp_method;
}

void CRtspSession::parser_common( const char* data, int len )
{
    memset( m_cseq, 0, sizeof(m_cseq) );
    //找出字符串中的cseq,并赋值给m_cseq
    if( get_str( data, len, "CSeq:", "\r\n", m_cseq, sizeof(m_cseq)-1-strlen("\r\n") ) >= 0 )
        strncpy( m_cseq+strlen(m_cseq), "\r\n", sizeof(m_cseq)-1 );
}

//拆分出地址
int CRtspSession::parser_url( const char* data, int len )
{
    memset( m_url, 0, sizeof(m_url) );
    const char* url_s_mark = "rtsp://";
    if( get_str( data, len, url_s_mark, " RTSP", m_url, sizeof(m_url)-1 ) < 0 ){
        LogError( "get url failed\n" );
        return -1;
    }
    return 0;
}

//找出字符串的某一个指定值
int CRtspSession::get_str( const char* data, int len, const char* s_mark, const char* e_mark, char* dest, int dest_len )
{
    //找到s_mark的位置
    const char* satrt = strstr( data, s_mark );
    if( satrt != nullptr ){
        //找到e_mark的位置
        const char* end = strstr( satrt, e_mark );
        if( end != nullptr )
            strncpy( dest, satrt, end-satrt>dest_len?dest_len:end-satrt );
        return 0;
    }
    return -1;
}

int CRtspSession::handle_describe( const char* data, int len )
{
    if( parser_url( data, len ) < 0 )
        return send_simple_cmd( 400 );
    // strstr( strstr(m_url, "rtsp://")+strlen("rtsp://"), "/" )+1:提取出文件名
    if( m_data_src.Init( strstr( strstr(m_url, "rtsp://")+strlen("rtsp://"), "/" )+1, 0, notify_fun, (long)this ) < 0 )
        return send_simple_cmd( 404 );
    const char* sdp = m_data_src.GetSdp();
    char cmd[4096] = "";
    snprintf( cmd, sizeof(cmd),
        "RTSP/1.0 200 OK\r\n"
        "%s%s"
        "Content-Base: %s/\r\n"
        "Content-Type: application/sdp\r\n"
        "Content-Length: %d\r\n\r\n"
        "%s",
        m_cseq, m_session, m_url, (int)strlen(sdp), sdp );
    return send_cmd( cmd, strlen(cmd));
}

int CRtspSession::handle_setup( const char* data, int len )
{
    if( strstr( data, "RTP/AVP/TCP" ) == nullptr )
        return send_simple_cmd( 461 );
    const char* interleaved = strstr( data, "interleaved=" );
    if( interleaved == nullptr )
        return send_simple_cmd( 400 );
    m_rtp_ch = atoi( interleaved+strlen("interleaved=") );
    if( m_rtp_ch < 0 )
        return send_simple_cmd( 400 );
    //获取当前系统时间微秒，作为当前会话的唯一的会话ID
    snprintf( m_session, sizeof(m_session), "Session: %X\r\n", (uint32_t)CNTime::GetCurUs());
    char cmd[1024] = "";
    snprintf( cmd, sizeof(cmd),
        "RTSP/1.0 200 OK\r\n"
        "%s%s"
        "Transport: RTP/AVP/TCP;unicast;interleaved=%d-%d\r\n\r\n",
        m_cseq, m_session, m_rtp_ch, m_rtp_ch+1 );
    //开启解码线程,准备数据

    if( m_rtpSession.init(m_url) < 0 )
        return send_simple_cmd( 404 );
    //开启音频流传输线程
    if(m_rtpSession.Start(m_sock.GetFd(),notify_fun,(long)this) < 0)
        return send_simple_cmd( 404 );

    return send_cmd( cmd, strlen(cmd) );
}

int CRtspSession::handle_play( const char* data, int len )
{
    //获得歌曲名
    std::stringstream ss(data);
    string pp;
    for(auto i = 0; i < 6;i++){
        ss >> pp;
    }
    char cmd[1024] = "";
    snprintf( cmd, sizeof(cmd),
        "RTSP/1.0 200 OK\r\n"
        "%s%s"
        "RTP-Info: url=%s\r\n",
        m_cseq, m_session, m_url);
    if( send_cmd( cmd, strlen(cmd) ) < 0 )
        return -1;

    //发送数据
    m_rtpSession.Play(pp,pp.size());
    return 0;
}

int CRtspSession::handle_pause()
{
    //停止传送数据
    m_rtpSession.Pause();
    return send_simple_cmd( 200 );
}

int CRtspSession::handle_teardowm()
{
    m_rtpSession.close();               //关闭RTP会话
    send_simple_cmd( 200 );
    return -1;          //返回-1,直接结束RTSPSession 会话线程
}

int CRtspSession::handle_other_method()
{
    return send_simple_cmd( 200 );
}

//发送rtsp/1.0 200k
int CRtspSession::send_simple_cmd( int code )
{
    int i = 0;
    for( ; ; i++ ){
        if( g_rsp_code_str[i].code == code )
            break;
        else if( g_rsp_code_str[i].code == 0 ){
            i = 2; //400 Bad Request
            break;
        }
    }
    char cmd[512] = "";
    snprintf( cmd, sizeof(cmd), "RTSP/1.0 %d %s\r\n%s%s\r\n", g_rsp_code_str[i].code, g_rsp_code_str[i].code_str, m_cseq, m_session );
    return send_cmd( cmd, strlen(cmd) );
}

int CRtspSession::send_cmd( const char* data, int len )
{
    PRINT_CMD( data );      //输出
    return m_sock.Send( data, len );
}

int CRtspSession::close()
{
    m_rtpSession.close();
}

void CRtspSession::notify_fun( long id, long msg, long user_info )
{
    CRtspSession* obj = (CRtspSession*)user_info;
    if( msg == DATA_SRC_CLOSE && obj->m_fun != nullptr )
        obj->m_fun( obj->m_sock.GetFd(), RTSP_SESSION_CLOSE, obj->m_user_info  );
}
