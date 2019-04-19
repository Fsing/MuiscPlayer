#include "PrintLog.h"
#include "RtspClient.h"


#define URL "rtsp://192.168.43.32:8554/testStream.mp3"

//int init_environment()
//{
//    return 0;
//}

static void data_cb_fun( const char* data, int len )
{
    if( data == nullptr )
        LogInfo( "rtsp client close\n" );
    else{
        LogInfo( "data len:%d\n", len );
    }
}

int main( void )
{
//    init_environment();
    CRtspClient rtsp_client;
    rtsp_client.Start( URL, data_cb_fun, 0 );       //向服务器请求，发送一系列命令，建立会话
    Sleep(3000);
    rtsp_client.Pause();
    Sleep(3000);
    rtsp_client.Play();
    Sleep(3000);
    rtsp_client.Close();
    getchar();
    return 0;
}
