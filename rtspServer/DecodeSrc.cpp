#include "DecodeSrc.h"
#include "PrintLog.h"
#include <algorithm>
#include <iostream>

//ffmpeg
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

using std::min;

CDecodeSrc::CDecodeSrc()
{
    memset(m_fileName,0,sizeof (m_fileName));
}

CDecodeSrc::~CDecodeSrc()
{
    Destroy();
    WaitExit();
}

int CDecodeSrc::Start(char *fileName)
{
    if(fileName == nullptr)
        return -1;
    strncpy(m_fileName,fileName,strlen(fileName));
    if(Create("Decode Source Thread",0) < 0){
        LogError( "Decode source thread failed\n" );
        return -1;
    }
    return 0;
}

void CDecodeSrc::thread_proc(long user_info)
{
    AVFormatContext	*pFormatCtx;
    AVCodecContext	*pCodecCtx;
    AVCodec			*pCodec;
    AVPacket		packet;
    int				i, audioStream;

    FILE *pFile=nullptr;
    //    string fileurl = "../rtspServer/music" + fileName;
    //char *url = fileurl.c_str();
    char *url= m_fileName;

    av_register_all();
    avformat_network_init();
    pFormatCtx = avformat_alloc_context();
    //Open
    if(avformat_open_input(&pFormatCtx,url,nullptr,nullptr)!=0){
        printf("Couldn't open input stream.\n");
        return;
    }
    av_dump_format(pFormatCtx, 0, url, false);
    audioStream=-1;
    for(i=0; i < pFormatCtx->nb_streams; i++)
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
            audioStream=i;
            break;
        }

    if(audioStream==-1){
        printf("Didn't find a audio stream.\n");
        return;
    }
    // Get a pointer to the codec context for the audio stream
    pCodecCtx=pFormatCtx->streams[audioStream]->codec;

    // Find the decoder for the audio stream
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==nullptr){
        printf("Codec not found.\n");
        return;
    }

    // 打开解码器
    if(avcodec_open2(pCodecCtx, pCodec,nullptr)<0){
        printf("Could not open codec.\n");
        return;
    }


    //解码--------------------------------------------------------------------------
    while(av_read_frame(pFormatCtx,&packet) >= 0){
        if(packet.stream_index == audioStream){
            PacketNode node;
            node.buf = new uint8_t[BUFF_MAX_SIZE*3];//每次读1024字节,不超过1400就行
            node.length = 0;
            memcpy(node.buf+node.length,packet.data,packet.size);
            node.length += packet.size;
            node.pts = packet.pts;


            av_free_packet(&packet);

//            while(node.length < 1024){
//                if(av_read_frame(pFormatCtx,&packet) >= 0){
//                    if(packet.stream_index == audioStream){
//                        memcpy(node.buf+node.length,packet.data,packet.size);
//                        node.length += packet.size;
//                        node.pts = packet.pts;
//                    }
//                }
//                av_free_packet(&packet);
//            }
//            std::cout << "Decode packet ,Sceq: " << packet.pts << endl;
            m_mutex.Enter();
            m_packetList.push_back(node);
            m_mutex.Leave();
        }
    }

//    FILE *file_m = fopen64(m_fileName,"rb");
//    while(IsDestroyed() == false){
//        PacketNode node;
//        node.buf = new uint8_t[BUFF_MAX_SIZE*3];//每次读1024字节,不超过1400就行
//        node.length = 0;
//        if(fread(node.buf,BUFF_MAX_SIZE,1,file_m)){
//            node.length += BUFF_MAX_SIZE;
//        }
//        m_mutex.Enter();
//        m_packetList.push_back(node);
//        m_mutex.Leave();
//    }
}

int CDecodeSrc::getNextPacket(uint8_t *buf, int buf_size, int64_t &spts)
{
    int nsize = 0;              //记录buf中，已经读取的数据长度
    m_mutex.Enter();
    if(!m_packetList.empty()){
        auto it = m_packetList.begin();
        for(;it != m_packetList.end();)
        {
            if(nsize < buf_size)
            {
                int readSize = min(buf_size - nsize,(*it).length);
                if(readSize < (*it).length){
                    memcpy(buf+nsize,(*it).buf,readSize);
                    nsize += readSize;
                    //将后面未复制的数据，复制到前面
                    memmove((*it).buf,(*it).buf+readSize,(*it).length-readSize);
                    (*it).length -= readSize;
                    spts = (*it).pts;
                    break;
                }else
                {
                    memcpy(buf+nsize,(*it).buf,(*it).length);
                    nsize += (*it).length;
                    spts = (*it).pts;
                }
            }
            delete[] (*it).buf;         //释放内存
            m_packetList.erase(it++);
        }
    }else{
        nsize = -1;         //表示没有数据可读
    }
    m_mutex.Leave();

    return nsize;
}
