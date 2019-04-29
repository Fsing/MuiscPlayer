#include "myrtpsession.h"
#include "printlog.h"
//#include <iostream>
#include <fstream>

//jrtplib
#include "rtpsession.h"
#include "rtpsessionparams.h"
#include "rtpudpv4transmitter.h"
#include "rtppacket.h"
#include "rtpipv4address.h"
#include "rtptimeutilities.h"

#include <jthread/jthread.h>

using namespace jrtplib;
using namespace jthread;
using std::cout;                using std::cin;
using std::endl;


void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

CRtpSession::CRtpSession()
{
    //    m_startTime = m_currentTime = time(nullptr);
    m_is_close = false;
    setDestroyed(true);
}


CRtpSession::~CRtpSession()
{
    Destroy();
    WaitExit();
}

int CRtpSession::Start(const char *url)
{
    get_ip(url,strlen(url),"/",":");
    get_port(url+strlen("rtsp://"),strlen(url)-strlen("rtsp://"),":","/");
    if( Create( "RtpClientThread", 0 ) < 0 ){
        LogError( "create thread  RtpClientThread failed\n" );
        return -1;
    }
    if( m_encodeSrc.Start() < 0 ){
        LogError( "create thread  DecodeSrcThread failed\n" );
        return -1;
    }
    return 0;
}

void CRtpSession::thread_proc(long user_info)
{
    cout << "enter thread_pro" << endl;
    RTPSession session;

    RTPSessionParams sessionparams;
    sessionparams.SetOwnTimestampUnit(1.0 / 90000.0);
    sessionparams.SetAcceptOwnPackets(true);
    sessionparams.SetUsePollThread(true);               //开启自动处理RTCP包的线程

    RTPUDPv4TransmissionParams transparams;
    transparams.SetPortbase(m_client_port); //接收端口

    int oldBufSize = transparams.GetRTPReceiveBuffer();
    transparams.SetRTPReceiveBuffer(oldBufSize * 10);
    int status = session.Create(sessionparams, &transparams);

    checkerror(status);

    int newBufSize = transparams.GetRTPReceiveBuffer();         //新RTP接收缓存
    int oldBufSizec = transparams.GetRTCPReceiveBuffer();
    transparams.SetRTCPReceiveBuffer(oldBufSizec *10);
    int newBufSizec = transparams.GetRTCPReceiveBuffer();       //新RTCP接收缓存

    //    RTPIPv4Address addr(ntohl(inet_addr(m_ip)), m_client_port);
    //    status = session.AddDestination(addr);
    //    checkerror(status);


    time_t startTime;
    time_t currentTime;
    startTime = currentTime = time(nullptr);

    std::ofstream write;
    write.open("../rtspClient/Sceq",ios::app);

    while(1){
        while(IsDestroyed() == false){
            if(m_is_close == true){
                if(startTime == currentTime){
                    startTime = time(nullptr);
                }else{
                    currentTime = time(nullptr);
                    if(currentTime - startTime >= 60)
                        setDestroyed(true);
                }
            }

            // 丢包 ，数据的处理速度满足不了接收方的接收速度，导致udp缓存满之后，被刷新而丢包
            int error_status = session.Poll();
            checkerror(error_status);
            session.BeginDataAccess();
            if (session.GotoFirstSourceWithData())
            {
                //            cout <<"__________________________________________" << endl;
                do
                {
                    RTPPacket *pack;

                    while ((pack = session.GetNextPacket()) != nullptr)
                    {
//                        cout <<"get Pack" << endl;
                        //                    fwrite(pack->SetExtendedSequenceNumber(),1,sizeof(pack->SetExtendedSequenceNumber()),pFile)
                        //                    int nPayType = pack->GetPayloadType();
                        int nLen = pack->GetPayloadLength();
                        unsigned char *pPayData = pack->GetPayloadData();
                        //                    int nPackLen = pack->GetPacketLength();
                        //                    unsigned char *pPackData = pack->GetPacketData();
                        //                    int csrc_cont = pack->GetCSRCCount();
                        //                    int ssrc = pack->GetSSRC();
                        //                    int nTimestamp = pack->GetTimestamp();
                        //将包序号写入文件:
                        int nSeqNum = pack->GetSequenceNumber();
                        write << nSeqNum << endl;
                        //                    cout <<"Receive packet,Sceq: " << nSeqNum <<" ,size: " << nLen << endl;

                        PacketNode temNode;
                        temNode.length = nLen;
                        temNode.buf = new uint8_t[nLen];
                        memcpy(temNode.buf, pPayData, nLen);
                        m_encodeSrc.put_packetNode(temNode);            //数据存放入缓存区

                        session.DeletePacket(pack);
                    }
                    RTPTime::Wait(RTPTime(1,0));
                } while (session.GotoNextSourceWithData());
            }
            session.EndDataAccess();

            RTPTime::Wait(RTPTime(1,0));
        }
    }
    session.BYEDestroy(RTPTime(10,0),0,0);
    session.Destroy();
}


int CRtpSession::close()
{
    //    m_startTime = time(nullptr);
    m_is_close = true;
}

int CRtpSession::Pause()
{
    m_encodeSrc.pause();
//    m_is_playing = false;
}

void CRtpSession::clear()
{
    m_encodeSrc.clear();
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

int CRtpSession::get_ip(const char *data, int len, const char *s_mark, const char *e_mark)
{
    //找到s_mark的位置
    const char* satrt = strstr( data, s_mark );
    if( satrt != nullptr ){
        //找到e_mark的位置
        const char* end = strstr( satrt, e_mark );
        if( end != nullptr )
            strncpy( m_ip, satrt+2, end-satrt-2 );
        return 0;
    }
    return -1;
}


//void MyRTPSession::onValidatedRTPPacket(RTPSourceData *srcdat, RTPPacket *rtppack, bool isonprobation, bool *ispackethandled)
//{
//    int nLen = rtppack->GetPayloadLength();
//    unsigned char *pPayData = rtppack->GetPayloadData();
//    //                    int nPackLen = pack->GetPacketLength();
//    //                    unsigned char *pPackData = pack->GetPacketData();
//    //                    int csrc_cont = pack->GetCSRCCount();
//    //                    int ssrc = pack->GetSSRC();
//    //                    int nTimestamp = pack->GetTimestamp();
//    //将包序号写入文件:
//    int nSeqNum = rtppack->GetSequenceNumber();
////    write << nSeqNum << endl;
////                    cout <<"Receive packet,Sceq: " << nSeqNum <<" ,size: " << nLen << endl;

//    PacketNode temNode;
//    temNode.length = nLen;
//    temNode.buf = new uint8_t[nLen];
//    memcpy(temNode.buf, pPayData, nLen);
//    m_encodeSrc.put_packetNode(temNode);            //数据存放入缓存区

//    DeletePacket(rtppack);
//}
