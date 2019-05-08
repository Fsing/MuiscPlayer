#include "myrtpsession.h"
#include "mutex.h"
#include "printlog.h"
#include <string>
#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>

////jrtplib
//#include "rtpsession.h"
//#include "rtpsessionparams.h"
//#include "rtpudpv4transmitter.h"
//#include "rtppacket.h"
//#include "rtpipv4address.h"
//#include "rtptimeutilities.h"

#define SEND_BUFFE_SIZE 1045        //每次读1045字节,一个NAL,不超过1400就行

using namespace jrtplib;

using std::string;                  using std::cout;
using std::endl;


CRtpSession::CRtpSession()
{
    m_fun =nullptr;
    m_user_info = 0;
    m_is_Play = false;
    m_is_new_connect = false;
    setDestroyed(true);
}

CRtpSession::~CRtpSession()
{
    Destroy();
    //    WaitExit();
}

//fun:RTSPSession的notify_fun函数
int CRtpSession::Start(int fd, NotifyFun fun, long user_info)
{
    //上锁
    setDestroyed(true);
    m_fun = fun;
    m_user_info = user_info;
    m_fd = fd;
    //    get_ip(clientUrl,sizeof(clientUrl),"/",":");
    //创建RTPSession线程
    if(Create("RTPSessionThread",0) < 0){
        LogError("create thread RtpSession failed\n");
        return -1;
    }
    return 0;
}

int CRtpSession::init(char *clienturl)
{
    int ret = 0;
    //    strncpy(m_fileName,filename,strlen(filename));
    //    get_ip(clienturl,strlen(clienturl),"/",":");
//    get_port(clienturl+strlen("rtsp://"),strlen(clienturl)-strlen("rtsp://"),":","/");
    get_fileName(clienturl+strlen("rtsp://"),strlen(clienturl)-strlen("rtsp://"),"/");
    if(m_decodeSrc.Start(m_fileName) < 0)
        ret = -1;
    return ret;
}


//线程执行函数：主要用于判断是否开始play,若开始，则从数据缓存区中读取数据并发送
void CRtpSession::thread_proc(long user_info)
{
    //从队列链表中读取数据，并发送到客户端
    //    if(m_is_Play){

    RTPSession session;

    RTPSessionParams sessionparams;
    sessionparams.SetOwnTimestampUnit(1.0 / 90000.0);
    sessionparams.SetAcceptOwnPackets(true);

    RTPUDPv4TransmissionParams transparams;
    transparams.SetPortbase(m_server_port); //这个端口必须未被占用

    int status = session.Create(sessionparams, &transparams);
    if (status < 0)
    {
        cout << "rtpsession create failed" << endl;
        setDestroyed(true);
    }
    //    while(1){
    //        if(m_is_new_connect == false){}

    RTPIPv4Address addr(ntohl(inet_addr(m_client_ip)), m_client_port);
    cout << m_client_ip << " " << m_client_port << endl;
    status = session.AddDestination(addr);

    if (status < 0)
    {
        cout << "rtpsession add address failed" << endl;
        setDestroyed(true);
    }

    session.SetDefaultPayloadType(96);          //rtp头的payload类型
    session.SetDefaultMark(false);              //rtp头MarkerBut的默认值
    session.SetDefaultTimestampIncrement(90000.0 / 25.0);   //时间戳增量3600

    //        session.SetDefaultMark(true);
    //        RTPTime delay(10);
    {

    auto readBytesPerSec = 2 * 1024 * 1024/8;
    RTPTime delay(BUFF_MAX_SIZE * 1.0/readBytesPerSec);

    //读数据
    uint8_t buffer[1024];
    int bufLength;
    int64_t pts;
    int sleep_ms = 5;
    //    int has_send_length = 0;                //已经发送的数据长度

    //每25秒发送一段数据
    time_t startTime = time(nullptr);
    time_t currentTime;


    std::ofstream write;
    write.open("../rtspServer/pts",ios::app);
    //    std::ofstream writeMedioStream;
    //    writeMedioStream.open("")

}
    while(1){
        while(IsDestroyed() == false){
            if(m_is_Play == true){
                if((bufLength = m_decodeSrc.getNextPacket(buffer,SEND_BUFFE_SIZE,pts)) > 0 ){
                    session.SendPacket(buffer,bufLength);
//                    cout <<"Send paccket  " << bufLength << "bytes" << endl;
                    //
                    {has_send_length += bufLength;
                    write << pts << endl;
                    bufLength = 0;
                    }
                }
            }
            currentTime = time(nullptr);
            if((currentTime - startTime) >= 0.7){
                RTPTime::Wait(RTPTime(1,0));
                startTime = time(nullptr);
            }
            Sleep( 2000 * BUFF_MAX_SIZE/readBytesPerSec );
        }
    }

    write.close();
    session.DeleteDestination(addr);
    session.Destroy();
    //    }
    //
    //    m_decodeSrc.Destroy();
    //    m_decodeSrc.clear();

    //会话结束，销毁服务器对象中的fd对应的那个会话
    //    if(m_fun != nullptr)
    //        m_fun(m_fd,DATA_SRC_CLOSE,m_user_info);
}

int CRtpSession::Pause()
{
    CGuard lock(m_mutex);
    cout <<"pause playing,songName: " << m_fileName << endl;
    m_is_Play = false;
    return 0;
}

int CRtpSession::Play(string fileName,int len)
{
    //    string name(m_fileName.data());
//    char name[64];
//    strncpy(name,fileName.c_str(),len);
//    name[len]='\0';

    //    if(strcmp(m_fileName,name) != 0){
    CGuard lock(m_mutex);
    if(IsDestroyed() == false){
        setDestroyed(true);
    }
    if(m_decodeSrc.IsDestroyed() == false)
        m_decodeSrc.setDestroyed(true);
    m_decodeSrc.clear();            //清理数据缓存
    //更新歌曲信息
    strncpy(m_fileName,fileName.c_str(),len);
    m_fileName[len] = '\0';
    m_decodeSrc.setFileName(m_fileName);

    m_is_Play = true;
    setDestroyed(false);
    m_decodeSrc.setDestroyed(false);

    //    }else if(strcmp(m_fileName,name) != 0){
    //        m_mutex.Enter();
    //        m_is_Play = true;
    //        m_mutex.Leave();
    //    }
    return 0;
}

int CRtpSession::close()
{
    Destroy();
    m_decodeSrc.Destroy();
    //    Destroy();
    //    m_decodeSrc.clear();
    //    WaitExit();
    //    m_decodeSrc.close();
}


int CRtpSession::get_ip(const char *data, int len, const char *s_mark, const char *e_mark)
{
    //找到s_mark的位置
    const char* satrt = strstr( data, s_mark );
    if( satrt != nullptr ){
        //找到e_mark的位置
        const char* end = strstr( satrt, e_mark );
        if( end != nullptr )
            strncpy(m_server_ip , satrt+2, end-satrt-2 );
        return 0;
    }
    return -1;
}

int CRtpSession::get_port(const char *data, int len, const char *s_mark, const char *e_mark)
{
    //找到s_mark的位置
    char port[128];
    const char* satrt = strstr( data, s_mark );
    if( satrt != nullptr ){
        //找到e_mark的位置
        const char* end = strstr( satrt, e_mark);
        if( end != nullptr )
            strncpy( port, satrt+1, 4);
        m_server_port = atoi(port);
        return 0;
    }
    return -1;
}

int CRtpSession::get_fileName(const char *data, int len, const char *s_mark)
{
    //找到s_mark的位置
    const char* satrt = strstr( data, s_mark );
    if( satrt != nullptr ){
        //找到e_mark的位置
        //        const char* end = strstr( satrt, e_mark);
        //        if( end != nullptr )
        memcpy(m_fileName,satrt+1,strlen(satrt)-1);
        return 0;
    }
    return -1;
}

//char *CRtpSession::getFileName()
//{
//    return m_fileName;
//}

//int CRtpSession::decodeThread(char *fileName)
//{
//    if(fileName == nullptr)
//        return -1;
//    m_fileName = fileName;
//    if(Create("Decode Source Thread",0,decode_data) < 0){
//        LogError( "Decode source thread failed\n" );
//        return -1;
//    }
//    return 0;
//}

//void CRtpSession::decode_data(CThread *thread,long user_info)
//{
//    AVFormatContext	*pFormatCtx;
//    AVCodecContext	*pCodecCtx;
//    AVCodec			*pCodec;
//    AVPacket		packet;
//    int				i, audioStream;

//    FILE *pFile=nullptr;
//    //    string fileurl = "../rtspServer/music" + fileName;
//    //char *url = fileurl.c_str();
//    char *url= m_fileName;

//    av_register_all();
//    avformat_network_init();
//    //Open
//    if(avformat_open_input(&pFormatCtx,url,nullptr,nullptr)!=0){
//        printf("Couldn't open input stream.\n");
//        return;
//    }
//    av_dump_format(pFormatCtx, 0, url, false);
//    audioStream=-1;
//    for(i=0; i < pFormatCtx->nb_streams; i++)
//        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
//            audioStream=i;
//            break;
//        }

//    if(audioStream==-1){
//        printf("Didn't find a audio stream.\n");
//        return;
//    }
//    // Get a pointer to the codec context for the audio stream
//    pCodecCtx=pFormatCtx->streams[audioStream]->codec;

//    // Find the decoder for the audio stream
//    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
//    if(pCodec==nullptr){
//        printf("Codec not found.\n");
//        return;
//    }

//    // 打开解码器
//    if(avcodec_open2(pCodecCtx, pCodec,nullptr)<0){
//        printf("Could not open codec.\n");
//        return;
//    }
//    //解码--------------------------------------------------------------------------
//    while(av_read_frame(pFormatCtx,&packet) >= 0){
//        if(packet.stream_index == audioStream){
//            PacketNode node;
//            node.buf = new uint8_t[1024];
//            node.length = 0;
//            memcpy(node.buf+node.length,packet.data,packet.size);
//            node.length += packet.size;
//            //
//            while(node.length < 1024){
//                if(av_read_frame(pFormatCtx,&packet) >= 0){
//                    if(packet.stream_index == audioStream){
//                        memcpy(node.buf+node.length,packet.data,packet.size);
//                        node.length += packet.size;
//                    }
//                }
//            }
//            m_mutex.Enter();
//            m_packetList.push_back(node);
//            m_mutex.Leave();
//        }
//    }
//}



