#include "decodesrc.h"
#include "printlog.h"
#include <algorithm>
#include <iostream>
#include <sstream>

//ffmpeg
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

using std::min;         using std::stringstream;

CDecodeSrc::CDecodeSrc()
{
    memset(m_fileName,0,sizeof (m_fileName));
    setDestroyed(true);
}

CDecodeSrc::~CDecodeSrc()
{
    Destroy();
    clear();
    //销毁m_packetlist动态分配的对象
    WaitExit();
}

int CDecodeSrc::Start(char *fileName)
{
    setDestroyed(true);
    if(fileName == nullptr)
        return -1;
    strncpy(m_fileName,fileName,strlen(fileName));
    if(Create("Decode Source Thread",0) < 0){
        LogError( "Decode source thread failed\n" );
        return -1;
    }
    return 0;
}

void CDecodeSrc::setFileName(char *fileName)
{
    cout << "CDecodeSrc::setFileName : " << fileName << endl;
    strncpy(m_fileName,fileName,strlen(fileName));
}

//int CDecodeSrc::close()
//{
//    clear();
//    Destroy();
//    WaitExit();
//    return 0;
//}

void CDecodeSrc::thread_proc(long user_info)
{
    while(1){
        if(IsDestroyed() == false){
            cout <<" Enter CDencodeSrc::thread_pro" << endl;
            AVFormatContext	*pFormatCtx;
            AVCodecContext	*pCodecCtx;
            AVCodec			*pCodec;
            AVPacket		packet;
            int				i, audioStream;

            cout << m_fileName <<endl;
            stringstream ss("./music/");
            char urll[128];
            memset(urll,0,sizeof(urll));

            string path1;
            ss >> path1;
            strncpy(urll,path1.c_str(),path1.size());
            auto it = strstr(m_fileName,"mp3");

            if(strncpy(urll+8,m_fileName,it+3-m_fileName) == nullptr){
                strncpy(urll+8,m_fileName,it+3-m_fileName);
            }
//            string file(m_fileName);
//            file = "./music/" + file;
//            strncpy(urll,file.c_str(),file.size());
//            url[strlen(m_fileName)] = '\0';
//            auto it = strstr(urll,"3");

//            char url[64];
//            memset(url,0,sizeof (url));
//            strncpy(url,urll,it-urll+1);

            cout << urll << endl;
            cout << m_fileName << endl;

            av_register_all();
            avformat_network_init();
            pFormatCtx = avformat_alloc_context();
            //Open
            if(avformat_open_input(&pFormatCtx,urll,nullptr,nullptr)!=0){
                printf("Couldn't open input stream.\n");
                return;
            }
            av_dump_format(pFormatCtx, 0, urll, false);
            audioStream=-1;
            for(i=0; i < pFormatCtx->nb_streams; i++)
                if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
                    audioStream=i;
                    break;
                }

            if(audioStream==-1){
                printf("Didn't find a audio stream.\n");
            }
            // Get a pointer to the codec context for the audio stream
            pCodecCtx=pFormatCtx->streams[audioStream]->codec;

            // Find the decoder for the audio stream
            pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
            if(pCodec==nullptr){
                printf("Codec not found.\n");
            }

            // 打开解码器
            if(avcodec_open2(pCodecCtx, pCodec,nullptr)<0){
                printf("Could not open codec.\n");
            }


            //解码--------------------------------------------------------------------------
            while(IsDestroyed() == false){
                if(av_read_frame(pFormatCtx,&packet) >= 0){
                    if(packet.stream_index == audioStream){
                        PacketNode node;
                        node.buf = new uint8_t[BUFF_MAX_SIZE*2];//每次读1024字节,不超过1400就行
                        //                node.buf = std::make_shared
                        node.length = 0;
                        memcpy(node.buf+node.length,packet.data,packet.size);
                        node.length += packet.size;
                        node.pts = packet.pts;


                        av_free_packet(&packet);

                        m_mutex.Enter();
                        m_packetList.push_back(node);
                        m_mutex.Leave();
                    }
                }
            }
            avformat_close_input(&pFormatCtx);
            cout << "leave CDecodeSrc::thread_pro" << endl;
        }
    }
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

void CDecodeSrc::clear()
{
    m_mutex.Enter();
    if(!m_packetList.empty()){
        auto it = m_packetList.begin();
        for(;it != m_packetList.end();){
            delete[] (*it).buf;
            m_packetList.erase(it++);
        }
    }
    m_mutex.Leave();
}
