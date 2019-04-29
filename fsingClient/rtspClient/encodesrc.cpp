#include "encodesrc.h"
#include "printlog.h"
#include <fstream>
#include <iostream>

//ffmpeg
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <SDL2/SDL.h>
};

//jrtplib
#include "rtpsession.h"
#include "rtpsessionparams.h"
#include "rtpudpv4transmitter.h"

#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000

static  Uint8  *audio_chunk;            //chunk:数据块，音频帧缓冲区
static  Uint32  audio_len;              //缓冲区大小
static  Uint8  *audio_pos;              //等于audio_chunk

CEncodeSrc::CEncodeSrc()
{
    setDestroyed(true);
    m_is_play = false;
}

CEncodeSrc::~CEncodeSrc()
{
    Destroy();
    WaitExit();
}

int CEncodeSrc::Start()
{
    if( Create( "DecodeSrcThread", 0 ) < 0 ){
        LogError( "decode source thread  DecodeSrcThread failed\n" );
        return -1;
    }
    return 0;
}

void CEncodeSrc::clear()
{
    m_mutex.Enter();
    std::cout << "clear data buffer" << std::endl;
    if(!m_packetList.empty()){
        auto it = m_packetList.begin();
        for(;it != m_packetList.end();){
            delete[] (*it).buf;
            m_packetList.erase(it++);
        }
    }
    m_mutex.Leave();
}


int fill_iobuffer(void *opaque, uint8_t *buf, int bufsize)
{
    int size = 0;
    if(!opaque) return -1;
    auto decodeSrc = (CEncodeSrc *)opaque;
    //    FILE *fp = fopen64("testStream.mp3","rb");
    //    fseeko(fp,0,SEEK_SET);
    //    fseeko(fp,0,SEEK_END);
    //    int len = ftell(fp);
    //    if(len > bufsize){
    //        fseek(fp,bufsize,SEEK_SET);
    //        size = fread(buf,bufsize,1,fp);
    //    }

    //    fclose(fp);
    size = decodeSrc->readBuf(buf,bufsize);
    if(size < 0) size = 0;
    return size;
}

//stream:音频流 、 len:音频流的大小
//callback函数单独开启一个线程，不断的将音频发送的音频设备进行播放.
void  fill_audio(void *udata,Uint8 *stream,int len){
    //SDL 2.0
    SDL_memset(stream, 0, len);
    if(audio_len==0)
        return;

    len=(len>audio_len?audio_len:len);
    //取小的，混合尽可能多的数据 /*  Mix  as  much  data  as  possible  */

    //对音频数据进行混音,感觉这边混音的用处就是为了填充缓存.没有这个没有声音
    SDL_MixAudio(stream,audio_pos,len,SDL_MIX_MAXVOLUME);
    audio_pos += len;       //更新播放位置
    audio_len -= len;       //更新数据长度
}

int CEncodeSrc::readBuf(uint8_t *data, int len)
{
    int data_to_read = len;
    auto pReadPtr = data;

    while (IsDestroyed() == false)
    {
        int nRead = getNextPacket((uint8_t*)pReadPtr, data_to_read);
        if (nRead < 0)
        {
            continue;               //等待数据
        }
        pReadPtr += nRead;
        data_to_read -= nRead;
        if (data_to_read > 0)
        {
            continue;
        }
        break;                        //知道读取到len指定数据长度，返回
    }

    return (data_to_read > 0) ? -1 : len;

}

//void CEncodeSrc::audio_callback(void *userdata, uint8_t *stream, int len)
//{
//    AVCodecContext *aCodecCtx = (AVCodecContext *)userdata;
//}

void CEncodeSrc::thread_proc(long user_info)
{
    while(1){
        if(IsDestroyed() == false){
            clear();
            AVFormatContext *pFormatCtx = nullptr;
            int             i, audioStream;                 //用于查找音频流位置
            AVPacket        packet;                         //存放解码得到的avPacket数据

            AVCodecContext  *aCodecCtxOrig = nullptr;
            AVCodecContext  *aCodecCtx = nullptr;
            AVCodec         *aCodec = nullptr;

            SDL_Event       event;
            SDL_AudioSpec   wanted_spec, spec;

            AVInputFormat *piFmt = nullptr;             //输入容器，其中包含了输入文件的音视频流信息,程序从输入容器中读出音视频包进行解码处理--AVFormatContext成员

            // Register all formats and codecs
            av_register_all();

            if(SDL_Init(SDL_INIT_AUDIO)) {
                fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
                exit(1);
            }

            pFormatCtx = nullptr;
            pFormatCtx = avformat_alloc_context();          //因为是从服务端接收文件数据，所以这里不能用打开音频文件的方法，直接获得一个AVFormatContext变量。只能从Client
            unsigned char * iobuffer = (unsigned char *)av_malloc(32768);       //输入输出缓存。因为AVIOContext的缓存大小（默认32768）。用于设置AVIOContext中的buffer成员（缓存）

            //AVIOContext是FFMPEG管理输入输出数据缓冲的结构体，I/O上下文,通过对该变量赋值可以改变输入源或输出目的
            AVIOContext * avio = avio_alloc_context(iobuffer, 32768, 0, this, fill_iobuffer, nullptr, nullptr);
            //输入输出缓存、缓存大小、缓存不可写、指针用于回调时使用、读包函数指针、写包函数指针、seek文件函数指针
            pFormatCtx->pb = avio;

            if(!avio) {
                printf("avio_alloc_context error!!!\n");
                setDestroyed(true);
            }

            //探测流格式,探测网络数据
            if(av_probe_input_buffer(avio, &piFmt, "", nullptr, 0, 0) < 0) {
                printf("av_probe_input_buffer error!\n");
                setDestroyed(true);
            } else {
                printf("probe success\n");
                printf("format: %s[%s]\n", piFmt->name, piFmt->long_name);
            }

            //打开
            int err = avformat_open_input(&pFormatCtx, "nothing", nullptr, nullptr);
            if(err) {
                printf("avformat_open_input error: %d\n", err);
                setDestroyed(true);
            }
            // 查找流信息
            if(avformat_find_stream_info(pFormatCtx, nullptr)<0)
                setDestroyed(true); // Couldn't find stream information

            // Dump information about file onto standard error
            // av_dump_format(pFormatCtx, 0, argv[1], 0);
            av_dump_format(pFormatCtx, 0, "", 0);

            //  查找音频流位置
            audioStream=-1;
            for(i=0; i<pFormatCtx->nb_streams; i++) {
                if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO &&
                        audioStream < 0) {
                    audioStream=i;
                }
            }
            // if(videoStream==-1)
            //   return -1; // Didn't find a video stream
            if(audioStream==-1)
                setDestroyed(true);

            aCodecCtxOrig=pFormatCtx->streams[audioStream]->codec;
            aCodec = avcodec_find_decoder(aCodecCtxOrig->codec_id);
            if(!aCodec) {
                fprintf(stderr, "Unsupported codec!\n");
                setDestroyed(true);
            }

            // Copy context
            aCodecCtx = avcodec_alloc_context3(aCodec);
            if(avcodec_copy_context(aCodecCtx, aCodecCtxOrig) != 0) {
                fprintf(stderr, "Couldn't copy codec context");
                setDestroyed(true); // Error copying codec context
            }

            //打开解码器
            avcodec_open2(aCodecCtx, aCodec, nullptr);


            //Out Audio Param，输出音频参数
            uint64_t out_channel_layout=AV_CH_LAYOUT_STEREO;
            //nb_samples: AAC-1024 MP3-1152
            int out_nb_samples = aCodecCtx->frame_size;                       //缓冲区大小
            AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;                //采样精度
            int out_sample_rate = aCodecCtx->sample_rate;//44100;            //采样率,pCodecCtx->sample_rate;有些文件的采样率不是44100的话，播放会有问题
            int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);//通道数

            //Out Buffer Size，//计算出保存一系列的样本需要的缓存大小
            int out_buffer_size = av_samples_get_buffer_size(nullptr,out_channels ,out_nb_samples,out_sample_fmt, 1);
            uint8_t			*out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE*2);

            //    printf("channel_layout=%lld\n", out_channel_layout);
            //    printf("nb_channels=%d\n", out_nb_samples);
            //    printf("freq=%d\n", out_sample_rate);

            //    if (!out_channel_layout || out_nb_channels != av_get_channel_layout_nb_channels(channel_layout)) {
            //        channel_layout = av_get_default_channel_layout(nb_channels);

            //        channel_layout &= ~AV_CH_LAYOUT_STEREO_DOWNMIX;
            //        printf("correction\n");
            //    }

            // Set audio settings from codec info
            wanted_spec.freq = out_sample_rate;
            wanted_spec.format = AUDIO_S16SYS;
            wanted_spec.channels = out_channels;
            wanted_spec.silence = 0;
            wanted_spec.samples = out_nb_samples;
            wanted_spec.callback = fill_audio;
            wanted_spec.userdata = aCodecCtx;

            if(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
                fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
                setDestroyed(true);
            }
            printf("freq: %d\tchannels: %d\n", spec.freq, spec.channels);

            AVFrame         *aFrame;
            aFrame = av_frame_alloc();
            //分配并设置avFrame变量
            //    aFrame.format = AV_SAMPLE_FMT_S16;
            //    aFrame.sample_rate = spec.freq;
            //    aFrame.channel_layout = av_get_default_channel_layout(spec.channels);
            //    aFrame.channels = spec.channels;

            int64_t in_channel_layout = av_get_default_channel_layout(aCodecCtx->channels);
            SwrContext *au_convert_ctx = swr_alloc_set_opts(au_convert_ctx,out_channel_layout,out_sample_fmt,out_sample_rate,
                                                            in_channel_layout,aCodecCtx->sample_fmt,aCodecCtx->sample_rate,0,nullptr);
            swr_init(au_convert_ctx);

            //play
            SDL_PauseAudio(0);                      //开启新线程，调用回调函数  //让音频设备开始播放,参数为0的时候即可开始播放音频数据。设置为1的时候，将会播放静音的值。

            std::ofstream write;
            write.open("../rtspClient/pts",ios::app);

            int ret;
            int got_picture = 0;
            while(IsDestroyed() == false){
                if(m_is_play == true){
                    if(av_read_frame(pFormatCtx, &packet)>=0) {
                        if(packet.stream_index==audioStream){
                            //解码播放
                            ret = avcodec_decode_audio4( aCodecCtx, aFrame,&got_picture, &packet);
                            //                    ret = avcodec_send_packet(aCodecCtx,&packet);
                            //                    if(ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF){
                            //                        printf("Error in decoding audio frame.\n");
                            //                        setDestroyed(true);
                            //                    }
                            //                    ret = avcodec_receive_frame(aCodecCtx,&aFrame);
                            //                    if (ret < 0 && ret != AVERROR_EOF){
                            //                        printf("Error in decoding audio frame.\n");
                            //                        setDestroyed(true);
                            //                    }

                            int dst_nb_samples = av_rescale_rnd(swr_get_delay(au_convert_ctx,aFrame->sample_rate) + aFrame->nb_samples,aFrame->sample_rate,aFrame->format,AVRounding(1));
                            if(got_picture > 0){
                                //此函数便是将输入的音频按照定义的参数进行转换，并输出
                                swr_convert(au_convert_ctx,&out_buffer, dst_nb_samples,(const uint8_t **)aFrame->data , aFrame->nb_samples);
                                //                        fwrite(out_buffer, 1, out_buffer_size, pFile);
//                                printf("pts:%lld\t packet size:%d\n",packet.pts,packet.size);
                                write << packet.pts << endl;

                                while(audio_len>0)//Wait until finish
                                    SDL_Delay(1);

                                audio_chunk = (Uint8 *) out_buffer;
                                audio_len = out_buffer_size;
                                audio_pos = audio_chunk;
                            }
                        }
                        av_free_packet(&packet);
                    }
                }
            }

            // Close the codecs
            avcodec_close(aCodecCtxOrig);
            avcodec_close(aCodecCtx);
            av_frame_free(&aFrame);
            // Close the video file
            avformat_close_input(&pFormatCtx);
            pFormatCtx = nullptr;
            av_free(out_buffer);
        }
    }
}

int CEncodeSrc::getNextPacket(uint8_t *buf, int buf_size)
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
                    break;
                }else
                {
                    memcpy(buf+nsize,(*it).buf,(*it).length);
                    nsize += (*it).length;
                    delete[] (*it).buf;         //释放内存
                    m_packetList.erase(it++);
                }
            }
            //            delete[] (*it).buf;         //释放内存
            //            m_packetList.erase(it++);
        }
    }else{
        nsize = -1;         //表示没有数据可读
    }
    m_mutex.Leave();

    return nsize;
}


int CEncodeSrc::put_packetNode(PacketNode p)
{
    //    PacketNode tmp;
    //    tmp.length = p.length;
    //    tmp.buf = p.b
    CGuard lock(m_mutex);
    m_packetList.push_back(p);
    return 0;
}

void CEncodeSrc::pause()
{
    m_is_play = false;
}

void CEncodeSrc::play()
{
    m_is_play = true;
}

//int CEncodeSrc::audio_decode_frame(AVCodecContext *aCodecContext, uint8_t *audio_buf, int buf_size)
//{

//    //    cout << " enter audio_decode_frame " << endl;

//    static AVPacket aPacket;                         //存放从队列中取出的一个packet
//    static uint8_t *audio_pkt_data = nullptr;
//    static int audio_pkt_size = 0;                   //aPacket里面的data数据大小
//    static AVFrame  frame;         //用来存放解码后的帧数据

//    int len1;                   //用于判断是否解码成功
//    int data_size = 0;

//    SwrContext *aSwrContext = nullptr;

//    //依次从队列中取出packet,并解码
//    while(true){
//        while(audio_pkt_size > 0){              //是否取出了一个packet
//            int got_frame = 0;
//            //            packet_queue_get(aPacketQueue,aPacket,0);                                       //取数据
//            len1 = avcodec_decode_audio4(aCodecContext,&frame,&got_frame,&aPacket);                       //成功返回被解码的AVPacket消耗的字节数
//            //解码,如果在解码期间发生错误，则返回否定错误代码，否则返回从输入AVPacket消耗的字节数。
//            if(len1 < 0){               //解码出错，跳出
//                audio_pkt_size = 0;
//                break;
//            }

//            audio_pkt_data += len1;             //???
//            audio_pkt_size -= len1;             //audio_pkt_size=0
//            data_size = 0;
//            if(got_frame){
//                //获取采样的大小,即frame变量中data的大小
//                data_size = av_samples_get_buffer_size(nullptr,aCodecContext->channels,frame.nb_samples,aCodecContext->sample_fmt,1);
//                assert(data_size <= buf_size);
//                memcpy(audio_buf,frame.data[0],data_size);      //将解码的数据复制到静态缓冲区
//            }

//            //设置frame变量的参数
//            if(frame.channels > 0 && frame.channel_layout == 0){
//                frame.channel_layout = av_get_default_channel_layout(frame.channels);
//            }else if(frame.channels == 0 && frame.channel_layout > 0){
//                frame.channels = av_get_channel_layout_nb_channels(frame.channel_layout);
//            }

//            if(aSwrContext){
//                swr_free(&aSwrContext);
//                aSwrContext = nullptr;
//            }

//            //设置需要转换成的参数，aFrame.channel_layout为想要的参数
//            aSwrContext = swr_alloc_set_opts(nullptr,aFrame.channel_layout,(AVSampleFormat)aFrame.format,aFrame.sample_rate,
//                                             frame.channel_layout, (AVSampleFormat)frame.format,frame.sample_rate,0,nullptr);
//            //            swr_init(aSwrContext);          //当设置好相关的参数后，使用此函数来初始化SwrContext结构体

//            if(!aSwrContext || swr_init(aSwrContext) < 0){              //当设置好相关的参数后，使用此函数来初始化SwrContext结构体,初始化失败
//                cout << "swr_init() failed" << endl;
//                break;
//            }

//            //在进行转换前，还需要计算出转换后的sample的个数dst_nb_samples。然后调用swr_convert就完成了输入的音频到输出音频格式的转换
//            //函数swr_get_delay得到输入sample和输出sample之间的延迟，并且其返回值的根据传入的第二个参数不同而不同。如果是输入的采样率，
//            //则返回值是输入sample个数；如果输入的是输出采样率，则返回值是输出sample个数。
//            int dst_nb_samples = av_rescale_rnd(swr_get_delay(aSwrContext,frame.sample_rate) + frame.nb_samples,
//                                                aFrame.sample_rate,aFrame.format,AVRounding(1));
//            //得到解码后的数据后，输入的音频格式可能和SDL打开的音频设备所支持的格式不一致，所以在将数据放入到callback的静态缓冲区前，需要做一个数据格式的转换。
//            //-----------------------------------------播放-----------------------------------------------------------
//            int len2 = swr_convert(aSwrContext, &audio_buf, dst_nb_samples,
//                                   (const uint8_t**)frame.data, frame.nb_samples);
//            if (len2 < 0)
//            {
//                cout << "swr_convert failed\n";
//                break;
//            }


//            //av_get_bytes_per_sample:获取每个采样值所占有的字节.返回转换的数据的字节数：通道数*sample个数*每个simple的字节数
//            return aFrame.channels * len2 * av_get_bytes_per_sample((AVSampleFormat)aFrame.format);                 //返回采样的大小

//            if (data_size <= 0)
//                continue; // No data yet,get more frames

//            //            return data_size; // we have data,return it and come back for more later
//        }

//        if (aPacket.data){                       //apacket中没有数据
//            av_free_packet(&aPacket);
//        }

//        //            if (quit)
//        //                return -1;

//        if (packet_queue_get(&aPacketQueue, &aPacket, true) < 0)                //从队列中取出
//            return -1;

//        audio_pkt_data = aPacket.data;              //压缩编码的数据，uint8_t*类型
//        audio_pkt_size = aPacket.size;              //packet中data的大小
//    }

//}

//void CEncodeSrc::audio_callback(void *userdata, uint8_t *stream, int len){

//    //    cout <<"Enter aucio_callback " << endl;

//    AVCodecContext *aCodecContext = (AVCodecContext *)userdata;
//    int len1;
//    int audioSize;
//    //静态的数据缓冲区，callback函数每次向音频设备传送数据时，首先检测静态缓存区中是否有数据，有则直接复制到stream，
//    //否则调用audio_decode_frame函数，从Packet 队列中取出Packet，将解码后的数据填充到静态缓冲区，然后再传送到音频设备。
//    static uint8_t audio_buff[(MAX_AUDIO_FRAME_SIZE * 3)/2];            //解码后的帧的缓冲区
//    static unsigned int audio_buf_size = 0;                 //帧数据缓冲区audio_buff的数据元素个数
//    static unsigned int audio_buf_index = 0;                //当前处理的帧数据的位置

//    SDL_memset(stream,0,len);           //格式化空间

//    //静态的数据缓冲区，callback函数每次向音频设备传送数据时，首先检测静态缓存区中是否有数据，有则直接复制到stream，
//    //否则调用audio_decode_frame函数，从Packet 队列中取出Packet，将解码后的数据填充到静态缓冲区，然后再传送到音频设备。
//    while(len > 0){                 //缓冲区可用
//        if(audio_buf_index >= audio_buf_size){
//            //静态缓冲区中没有数据，调用函数解码,并放入静态缓冲区
//            //audio_decode_frame:解audio_buf_size码数据并进行格式转换
//            audioSize = audio_decode_frame(aCodecContext,audio_buff,sizeof(audio_buff));
//            if(audioSize < 0){
//                audio_buf_size = 1024;
//                memset(audio_buff,0,audio_buf_size);
//            }else{
//                audio_buf_size = audioSize;
//            }
//            audio_buf_index = 0;
//        }
//        len1 = audio_buf_size - audio_buf_index;                //剩下多少没有复制到stream缓冲区
//        if(len1 > len){                                         //是否超出stream缓冲区大小
//            len1 = len;
//        }
//        memcpy(stream,(uint8_t*)(audio_buff + audio_buf_index),len1);                 //覆盖型复制
//        len -= len1;                    //缓冲区还剩多少可以复制
//        stream += len1;                 //下一次复制就从上一次复制的后面接着复制，实现不覆盖
//        audio_buf_index += len1;        //
//    }
//}























