#include "Server/RtspSvr.h"
#include "PrintLog.h"

//int un_init_environment()
//{

//    if (WSACleanup() == SOCKET_ERROR)
//        return -1;

//    return 0;
//}


int main( void )
{
    //    init_environment();
    CRtspSvr rtsp_svr;
    rtsp_svr.Start( 8554 );             //打开服务器，并进行监听。
                                        //服务器有个监听socket,当有客户端连接时，建立新的会话线程，保存新连接的socket，放到m_session_map
                                        //然后监听socket继续进行监听
    getchar();
    return 0;
}
