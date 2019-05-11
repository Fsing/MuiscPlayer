#include "Server/rtspsvr.h"
#include "printlog.h"
#include <pthread.h>
//#include <signal.h>
#include <exception>
#include <iostream>

int main( void )
{
    CRtspSvr rtsp_svr;
    try{
        rtsp_svr.Start( 8554 );
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    //打开服务器，并进行监听。
    //服务器有个监听socket,当有客户端连接时，建立新的会话线程，保存新连接的socket，放到m_session_map
    //然后监听socket继续进行监听



    getchar();
    return 0;
}
