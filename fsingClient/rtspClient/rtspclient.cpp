#include "./rtspClient/rtspclient.h"
#include "printlog.h"
#include <string.h>
#include "ntime.h"
#include <iostream>
#include <sstream>

using std::cout;            using std::endl;

CRtspClient::CRtspClient()
{
    m_fun = nullptr;
    m_user_info = 0;
    memset( m_recv_buf, 0, sizeof(m_recv_buf) );
    m_recv_len = 0;
    m_cseq = 0;
    m_rtp_ch = 0;
    memset( m_session, 0, sizeof(m_session) );
    memset( m_base_url, 0, sizeof(m_base_url) );
    m_method = RTSP_METHOD_MAX;
    memset( &m_media_info, 0, sizeof(m_media_info) );
    m_media_num = 0;
    m_media_index = 0;
    m_range = -1;
}

CRtspClient::~CRtspClient()
{
    Destroy();
    WaitExit();
}

//int CRtspClient::Start(QString url,QString baseport)
//{
//    m_fun = data_cb_fun;
//    memset( m_base_url, 0, sizeof(m_base_url) );

//    //url复制
//    auto baseUrl = url.toStdString();
//    strncpy( m_base_url, baseUrl.c_str(), strlen(baseUrl.c_str()) );

//    std::string port(baseport.toStdString());
//    stringstream ss(port);
//    ss >> m_client_port;
//    m_rtpSession.setClientPort(m_client_port);

//    //    m_rtpSession.Start(url);
//    if( open_sock( baseUrl.c_str() ) < 0 )
//        return -1;
//    if( Create( "RtspClientThread", 0 ) < 0 ){
//        LogError( "create thread  RtspClientThread failed\n" );
//        return -1;
//    }
//    return 0;
//}
int CRtspClient::Start(const char* url, DataCBFun fun, long user_info , char *baseport)
{
    m_fun = fun;
    m_user_info = user_info;
    memset( m_base_url, 0, sizeof(m_base_url) );
    strncpy( m_base_url, url, sizeof(m_base_url) );

    std::string port(baseport);
    stringstream ss(port);
    ss >> m_client_port;
    m_rtpSession.setClientPort(m_client_port);

    //    m_rtpSession.Start(url);
    if( open_sock( url ) < 0 )
        return -1;
    if( Create( "RtspClientThread", 0 ) < 0 ){
        LogError( "create thread  RtspClientThread failed\n" );
        return -1;
    }
    return 0;
}

int CRtspClient::GetRange()
{
    return m_range;
}

int CRtspClient::Play(string songName)
{
    //        m_rtpSession.Start(m_base_url);
    //开启rtp会话，接收数据，并开启解码线程，播放
    //开启接收数据

    //如果正在接收数据，停止接收
    if(m_rtpSession.IsDestroyed() == false){
        m_rtpSession.setDestroyed(true);
    }
    //停止解码
    if(m_rtpSession.m_encodeSrc.IsDestroyed() == false)
        m_rtpSession.m_encodeSrc.setDestroyed(true);

    m_rtpSession.m_encodeSrc.play();

    m_rtpSession.clear();
    m_rtpSession.setDestroyed(false);       //开始接收
    m_rtpSession.m_encodeSrc.setDestroyed(false);   //开始解码播放

    return send_play_cmd( songName);
}

void CRtspClient::continuePlay()
{
    m_rtpSession.m_encodeSrc.play();
}

int CRtspClient::Pause()
{
    m_rtpSession.Pause();
    return send_simple_cmd( RTSP_PAUSE );
    return 0;
}

void CRtspClient::Close()
{
    send_simple_cmd( RTSP_TEARDOWN );
}

void CRtspClient::clear()
{
    m_rtpSession.clear();
}

void CRtspClient::thread_proc( long user_info )
{
    int ret = 0;
    while( IsDestroyed() == false ){
        CGuard lock( m_mutex );
        fd_set read_fd_set;
        fd_set except_fd_set;
        FD_ZERO( &read_fd_set );	//WRITE_EVENT
        FD_ZERO( &except_fd_set );	//EXCEPT_EVENT
        FD_SET( m_sock.GetFd(), &read_fd_set );
        FD_SET( m_sock.GetFd(), &except_fd_set );

        struct timeval tmv_timeout={ 0L, 1000L };//???????1???
        if( select( m_sock.GetFd()+1, &read_fd_set, nullptr, &except_fd_set, &tmv_timeout ) > 0  ){
            if( FD_ISSET( m_sock.GetFd(), &read_fd_set ) != 0 ){
                if( recv_data() < 0 ){
                    ret = -1;
                    break;
                }
            }
            if( FD_ISSET( m_sock.GetFd(), &except_fd_set ) != 0 ){
                LogError( "session net exception\n" );
                ret = -1;
                break;
            }
        }
    }
    if( ret < 0 && m_fun != nullptr )
        m_fun( nullptr, 0 );//close client
}

int CRtspClient::open_sock( const char* url )
{
    char ip[128] = "";
    int port = 554;
    const char* start = strstr( url, "rtsp://" );
    if( start == nullptr ){
        LogError( "url format error, url:%s\n", url );
        return -1;
    }
    //end:端口前面的“：”
    const char* end = strstr( url+strlen("rtsp://"), ":" );
    //提取端口
    if( end != nullptr )
        port = atoi( end+1 );               //端口
    else{
        end = strstr( url+strlen("rtsp://"), "/" );         //end:端口后面的“/”
        if( end == nullptr ){
            LogError( "url format error, url:%s\n", url );
            return -1;
        }
    }
    //提取ip地址:192.168.43.31
    strncpy( ip, url+strlen("rtsp://"), end-start-strlen("rtsp://") );
    m_method = RTSP_METHOD_MAX;
    m_sock.Close();

    if( m_sock.Connect( ip, port ) < 0 ){
        LogError( "open sock failed, ip:%s, port:%d\n", ip, port );
        return -1;
    }
    //    m_method = RTSP_OPTIONS;
    //    if( send_simple_cmd( RTSP_OPTIONS ) < 0 ){
    //        LogError( "send describe request failed\n" );
    //        return -1;
    //    }
    m_method = RTSP_CLIENT_PORT;
    if( send_simple_cmd( RTSP_CLIENT_PORT ) < 0 ){
        LogError( "send RTSP_CLIENT_PORT request failed\n" );
        return -1;
    }
    return 0;
}

int CRtspClient::recv_data()
{
    int recv_len = sizeof(m_recv_buf)-1-m_recv_len;
    if( recv_len <= 0 ){
        LogError( "recv buf len <=0\n" );
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

int CRtspClient::handle_data()
{
    char *recv_buf = m_recv_buf;
    m_recv_buf[m_recv_len] = '\0';
    int ret = -1;
    while( m_recv_len > 0 ){
        ret = 0;
        //当有音频数据传入时
        if( '$' == *recv_buf ){
            auto i = strstr(m_recv_buf,"200 OK");
            if(i != nullptr){
                m_recv_len -= strlen(m_recv_buf);
                recv_buf += strlen(m_recv_buf);
                m_method = RTSP_OPTIONS;
                send_simple_cmd( RTSP_OPTIONS );

                ret = 0;
                break;
            }
            //数据长度不够大
            //            if( m_recv_len <= sizeof(struct RtpTcpHdr) )
            //                break;
            //            struct RtpTcpHdr* r_t_hd = (struct RtpTcpHdr *)recv_buf;
            //            uint32_t r_t_len = ntohs(r_t_hd->len);
            //            if( m_recv_len < r_t_len + 4 )
            //                break;
            //            if( r_t_hd->channel == m_rtp_ch && m_fun != nullptr )
            //                m_fun( recv_buf+4, r_t_len ); // handle rtp---m_fun()处理接收到的具体数据
            //            //handle rtcp
            //            m_recv_len -= r_t_len + 4;
            //            recv_buf += r_t_len + 4;

        }else{
            int parser_ret = parse_data( recv_buf, m_recv_len );
            if( parser_ret < 0 )
                break;
            PRINT_RECV_CMD( recv_buf, parser_ret );
            if( handle_cmd( recv_buf, parser_ret ) < 0 )
                return -1;
            m_recv_len -= parser_ret;
            recv_buf += parser_ret;
        }
    }
    if( m_recv_len > 0 )
        memmove( m_recv_buf , recv_buf, m_recv_len );
    return ret;
}

int CRtspClient::parse_data( const char* data, int len )
{
    const char *start = data;
    const char *end_mark = "\r\n\r\n";
    const char *end = nullptr;
    if( nullptr == (end = strstr(start, end_mark)) )
        return -1;
    int header_len = end - start + strlen(end_mark);
    int content_len = 0;
    const char* conten_len_mark = "Content-Length: ";
    const char* content_len_pos = strstr(data, conten_len_mark);
    if( content_len_pos != nullptr && strstr(content_len_pos, "\r\n") != nullptr )
        content_len = atoi( content_len_pos+strlen(conten_len_mark) );
    if( len < (header_len + content_len) )
        return -1;
    return (header_len + content_len);
}

int CRtspClient::handle_cmd( const char* data, int len )
{
    int code = parse_rsp_code( data, len );     //返回处理码
    if( code != 200 ){
        LogError( "response code id not 200 ok, code:%d\n", code );
        return -1;
    }
    int ret = 0;
    switch( m_method ){
    case RTSP_OPTIONS:
        //        cout << data << endl;
        ret = send_describe_cmd();
        m_method = RTSP_DESCRIBE;
        //        Sleep(3000);
        break;
    case RTSP_DESCRIBE:
        parser_describe( data, len );
        ret = send_setup_cmd();
        m_method = RTSP_SETUP;
        break;
//    case RTSP_SETUP:
//        parser_setup( data, len );
//        if( m_media_index < m_media_num )
//            ret = send_setup_cmd();
//        else{
//            ret = send_play_cmd( 0, -1 );
//            m_method = RTSP_METHOD_MAX;
//        }
//        break;
    default:
        break;
    }
    return ret;
}

int CRtspClient::get_str( const char* data, const char* s_mark, bool with_s_make, const char* e_mark, bool with_e_make, char* dest )
{
    const char* satrt = strstr( data, s_mark );
    if( satrt != nullptr ){
        const char* end = strstr( satrt, e_mark );
        if( end != nullptr ){
            int s_pos = with_s_make ? 0 : strlen(s_mark);
            int e_pos = with_e_make ? strlen(e_mark) : 0;
            strncpy( dest, satrt+s_pos, (end-e_pos) - (satrt+s_pos) );
        }
        return 0;
    }
    return -1;
}

int CRtspClient::parse_rsp_code( const char* data, int len )
{
    const char* rtsp_pos = strstr( data, "RTSP/" );
    if( rtsp_pos != data ){
        LogError( "response format error\n" );
        return -1;
    }
    const char* pos = strstr( rtsp_pos+strlen("RTSP/"), " " );
    if( pos == nullptr ){
        LogError( "response format error\n" );
        return -1;
    }
    int code = atoi( pos+1 );
    if( code < 100 || code > 999 ){
        LogError( "response format error\n" );
        return -1;
    }
    return code;
}

int CRtspClient::send_simple_cmd( RtspMethodT method )
{
    char cmd[512] = "";
    if(method == RTSP_CLIENT_PORT)
        snprintf( cmd, sizeof(cmd), "$%d",m_client_port);
    else
        snprintf( cmd, sizeof(cmd), "%s %s RTSP/1.0\r\nCSeq: %d\r\n%s\r\n", g_method[method].method_str, m_base_url, m_cseq++, m_session );
    //    cout << cmd << endl;
    return send_cmd( cmd, strlen(cmd) );
}

int CRtspClient::send_describe_cmd()
{
    char cmd[512] = "";
    snprintf( cmd, sizeof(cmd), "DESCRIBE %s RTSP/1.0\r\nCSeq: %d\r\n%sAccept: application/sdp\r\n\r\n", m_base_url, m_cseq++, m_session );
    return send_cmd( cmd, strlen(cmd) );
}

int CRtspClient::send_setup_cmd()
{
    m_rtpSession.Start(m_base_url);
    char cmd[512] = "";
    snprintf( cmd, sizeof(cmd), "SETUP %s%s%s RTSP/1.0\r\nCSeq: %d\r\n%sTransport: RTP/AVP/TCP;unicast;interleaved=%d-%d\r\n\r\n",
              m_base_url, m_base_url[strlen(m_base_url)-1]=='/'?"":"/", m_media_info[m_media_index++].track_id, m_cseq++, m_session, m_rtp_ch, m_rtp_ch+1 );
    return send_cmd( cmd, strlen(cmd) );
}

int CRtspClient::send_play_cmd(string songname)
{
//    char range[64] = "";
//    if( s_sec != -1 ){
//        if( e_sec != -1 )
//            snprintf( range, sizeof(range), "Range: npt=%d.00-%d.00\r\n", s_sec, e_sec );
//        else
//            snprintf( range, sizeof(range), "Range: npt=%d.00-\r\n", s_sec );
//    }
    char cmd[512] = "";
    snprintf( cmd, sizeof(cmd), "PLAY %s RTSP/1.0\r\nCSeq: %d\r\n%s\r\n\r\n", m_base_url, m_cseq++, songname.c_str() );

//    //开启rtp会话，接收数据，并开启解码线程，播放
//    //开启接收数据

//    //如果正在接收数据，停止接收
//    if(m_rtpSession.IsDestroyed() == false){
//        m_rtpSession.setDestroyed(true);
//    }
//    //停止解码
//    if(m_rtpSession.m_encodeSrc.IsDestroyed() == false)
//        m_rtpSession.m_encodeSrc.setDestroyed(true);
//    m_rtpSession.clear();
//    m_rtpSession.setDestroyed(false);       //开始接收
//    m_rtpSession.m_encodeSrc.setDestroyed(false);   //开始解码播放

    return send_cmd( cmd, strlen(cmd) );
}

int  CRtspClient::parser_describe( const char* data, int len )
{
    //    cout << "DESCRIBE: " <<data << endl;
    //提取出url
    get_str( data, "Content-Base: ", false, "\r\n", false, m_base_url );
    const char* ptr = data;
    for( int i = 0; i < MAX_MEDIA_NUM; i++ ){
        const char* media_pos = strstr( ptr, "m=" );
        if( media_pos != nullptr ){
            ptr = media_pos+2;
            m_media_num++;
            m_media_info[i].index = i;
            get_str( media_pos, "a=control:", false, "\r\n", false, m_media_info[i].track_id );
        }else
            break;
    }
    const char* range = strstr( data, "a=range:npt=0--" );
    //提取音频的大小信息字段
    if( range != nullptr )
        m_range = atoi( range+strlen("a=range:npt=0--") );
    else
        m_range = 0;
    return 0;
}

int  CRtspClient::parser_setup( const char* data, int len )
{
    //    cout << "SETUP: " <<data << endl;
    get_str( data, "Session:", true , "\r\n", true, m_session );
    const char* pos = strstr( m_session, ";" );
    if( pos != nullptr ){
        char session[128] = "";
        strncpy( session, m_session, pos-m_session );
        memset( m_session, 0, sizeof(m_session) );
        snprintf( m_session, sizeof(m_session), "%s\r\n", session );
    }
    return 0;
}

int CRtspClient::send_cmd( const char* data, int len )
{
    PRINT_CMD( data );
//    cout << data << endl;
    return m_sock.Send( data, len );
}

//void CRtspClient::data_cb_fun(const char *data, int len)
//{
//    if( data == nullptr )
//        LogInfo( "rtsp client close\n" );
//    else{
//        LogInfo( "data len:%d\n", len );
//    }
//}

//int CRtspClient::get_port(const char *data, int len, const char *s_mark, const char *e_mark)
//{
//    //找到s_mark的位置
//    char port[128];
//    const char* satrt = strstr( data, s_mark );
//    if( satrt != nullptr ){
//        //找到e_mark的位置
//        const char* end = strstr( satrt, e_mark);
//        if( end != nullptr )
//            strncpy( port, satrt+1, 4);
//        m_port = atoi(port);
//        return 0;
//    }
//    return -1;
//}
