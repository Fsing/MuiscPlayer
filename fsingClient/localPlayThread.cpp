#include "localPlayThread.h"
#include "localPlayThread.h"
#include <string>
#include <iostream>
#include <pthread.h>

using namespace std;

#define MAX_AUDIO_FRAME_SIZE 192000
static  Uint8  *audio_chunk;            //chunk:数据块，音频帧缓冲区
static  Uint32  audio_len;              //缓冲区大小
static  Uint8  *audio_pos;              //等于audio_chunk

LocalPlayThread::LocalPlayThread()
{
    m_mutex.Enter();
    m_is_playing = false;
    m_is_destroyed = true;
    m_mutex.Leave();
}

LocalPlayThread::~LocalPlayThread()
{
//    void *ret;
//    pthread_exit(ret);

    SDL_CloseAudio();//Close SDL
    SDL_Quit();

    av_free(out_buffer);
    avcodec_close(pCodecCtx);
    av_packet_free(&packet);
    av_frame_free(&pFrame);
    avformat_close_input(&pFormatCtx);

    m_is_destroyed = true;
    pthread_cancel(m_handle);
    cout <<"leave localPlay Thread: " << m_fileName << endl;
}

int LocalPlayThread::play(QString songName)
{
    //    m_fun = fun;
    //    m_userinfo = userinfo;

    //先判断当前是否有正在播放的歌曲
    //若有，则停止播放，退出decode函数
    //    m_mutex.Enter();
    //    if(m_is_destroyed == false){
    //        m_is_destroyed = true;          //停止播放
    ////        pthread_cancel(m_handle);
    //    }
    //    m_mutex.Leave();

    m_fileName = songName.toStdString();
    m_mutex.Enter();
    m_is_destroyed = false;
    m_is_playing = true;
    m_mutex.Leave();

    //创建线程，重新播放新歌曲
//    if(create() < 0){
//        cout << "LocalClientPlay Thread failed" << endl;
//        return -1;
//    }
//    return 0;
    if(pthread_create(&m_handle,nullptr,thread_fun,this) != 0){
        cout<< "create LocalClientThread failed " << endl;
        return -1;
    }
    return 0;
}

void LocalPlayThread::pause()
{
    m_mutex.Enter();
    m_is_playing = false;
    m_mutex.Leave();
}

int LocalPlayThread::create()
{
    if(pthread_create(&m_handle,nullptr,thread_fun,this) != 0){
        cout<< "create LocalClientThread failed " << endl;
        return -1;
    }
    return 0;
}


//stream:音频流 、 len:音频流的大小
//callback函数单独开启一个线程，不断的将音频发送的音频设备进行播放.
void  LocalPlayThread::call_back(void *udata,Uint8 *stream,int len){
    //SDL 2.0
    SDL_memset(stream, 0, len);
    if(audio_len==0)
        return;

    len=(len>audio_len?audio_len:len);
    //取小的，混合尽可能多的数据


//    cout << "Start to Play " << endl;
    //对音频数据进行混音,感觉这边混音的用处就是为了填充缓存
    SDL_MixAudio(stream,audio_pos,len,SDL_MIX_MAXVOLUME);
    audio_pos += len;       //更新播放位置
    audio_len -= len;       //更新数据长度
}

void *LocalPlayThread::thread_fun(void *arg)
{
    pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, nullptr ); // 设置其他线程可以cancel掉此线程
    pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, nullptr );   //设置立即取消
    LocalPlayThread *localPlay = (LocalPlayThread *)arg;
    cout << "Enter thread: LocalClientPlay" << endl;

    localPlay->decode(localPlay->m_fileName);

    return 0;
}

int LocalPlayThread::decode(string fileName)
{
    //检测是否已经开始播放
    if(m_is_destroyed == false){
//        AVFormatContext     *pFormatCtx;
        int                 i, audioStream;
//        AVCodecContext      *pCodecCtx;
//        AVCodec             *pCodec;
//        AVPacket            *packet;
//        uint8_t             *out_buffer;
//        AVFrame             *pFrame;
//        SDL_AudioSpec       wanted_spec;
        int ret;
        uint32_t len = 0;
        int got_picture;
        int64_t in_channel_layout;
        struct SwrContext *au_convert_ctx;


        //解码前准备工作：----------------------------------------------------------------------------------
        FILE *pFile = nullptr;
        auto url = fileName.c_str();
        av_register_all();
        avformat_network_init();
        pFormatCtx = avformat_alloc_context();          //这一步可以不要，avformat_open_input()可以给他分配并填充

        //打开媒体文件
        if(avformat_open_input(&pFormatCtx,url,nullptr,nullptr)!=0){
            printf("Couldn't open input stream.\n");
            return -1;
        }

        // 探测媒体流
        if(avformat_find_stream_info(pFormatCtx,nullptr)<0){
            printf("Couldn't find stream information.\n");
            return -1;
        }

        // 输出媒体信息
        av_dump_format(pFormatCtx, 0, url, false);

        // 查找出第一个音频流
        audioStream=-1;
        for(i=0; i < pFormatCtx->nb_streams; i++)
            if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO){
                audioStream=i;
                break;
            }

        if(audioStream==-1){
            printf("Didn't find a audio stream.\n");
            return -1;
        }

        pCodecCtx=pFormatCtx->streams[audioStream]->codec;

        pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
        if(pCodec == nullptr){
            printf("Codec not found.\n");
            return -1;
        }

        if(avcodec_open2(pCodecCtx, pCodec,nullptr)<0){
            printf("Could not open codec.\n");
            return -1;
        }


        //解码--------------------------------------------------------------------------
        packet=(AVPacket *)av_malloc(sizeof(AVPacket));
        av_init_packet(packet);

        //Out Audio Param，输出音频参数
        uint64_t out_channel_layout=AV_CH_LAYOUT_STEREO;
        int out_nb_samples=pCodecCtx->frame_size;                       //缓冲区大小,nb_samples: AAC-1024 MP3-1152
        AVSampleFormat out_sample_fmt=AV_SAMPLE_FMT_S16;                //采样精度
        int out_sample_rate= pCodecCtx->sample_rate;//44100;            //采样率,pCodecCtx->sample_rate;有些文件的采样率不是44100的话，播放会有问题
        int out_channels=av_get_channel_layout_nb_channels(out_channel_layout);//通道数

        int out_buffer_size=av_samples_get_buffer_size(nullptr,out_channels ,out_nb_samples,out_sample_fmt, 1);//Out Buffer Size，//计算出保存一系列的样本需要的缓存大小

        out_buffer=(uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE*2);
        pFrame=av_frame_alloc();

        //SDL------------------
        //Init
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
            printf( "Could not initialize SDL - %s\n", SDL_GetError());
            return -1;
        }

        //SDL_AudioSpec
        wanted_spec.freq = out_sample_rate;
        wanted_spec.format = AUDIO_S16SYS;
        wanted_spec.channels = out_channels;
        wanted_spec.silence = 0;
        wanted_spec.samples = out_nb_samples;
        wanted_spec.callback = call_back;
        wanted_spec.userdata = pCodecCtx;

        if (SDL_OpenAudio(&wanted_spec, nullptr)<0){               //开启线程，callback（）
            printf("can't open audio.  %s\n",SDL_GetError());
            return -1;
        }

        //有些编解码器的上下文信息可能有遗失
        in_channel_layout=av_get_default_channel_layout(pCodecCtx->channels);
        //Swr

        au_convert_ctx = swr_alloc();
        au_convert_ctx=swr_alloc_set_opts(au_convert_ctx,out_channel_layout, out_sample_fmt, out_sample_rate,
                                          in_channel_layout,pCodecCtx->sample_fmt , pCodecCtx->sample_rate,0, nullptr);
        swr_init(au_convert_ctx);               //当设置好相关的参数后，使用此函数来初始化SwrContext结构体

        //Play
        SDL_PauseAudio(0);

        cout <<"start" << endl;
        while(m_is_destroyed == false){
            //若m_is_playing=false,则表示停止播放
            if(m_is_playing == true){
                if(av_read_frame(pFormatCtx, packet)>=0){
                    if(packet->stream_index==audioStream){
                        ret = avcodec_decode_audio4( pCodecCtx, pFrame,&got_picture, packet);

                        //                        ret = avcodec_send_packet(pCodecCtx,packet);
                        //                        if(ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF){
                        //                            printf("Error in decoding audio frame.\n");
                        //                            return -1;
                        //                        }
                        //                        ret = avcodec_receive_frame(pCodecCtx,pFrame);
                        //                        if (ret < 0 && ret != AVERROR_EOF){
                        //                            printf("Error in decoding audio frame.\n");
                        //                            return -1;
                        //                        }


                        if ( ret < 0 ) {
                            printf("Error in decoding audio frame.\n");
                            return -1;
                        }
                        if ( got_picture > 0 ){
                            //此函数便是将输入的音频按照定义的参数进行转换，并输出
                            swr_convert(au_convert_ctx,&out_buffer, MAX_AUDIO_FRAME_SIZE,(const uint8_t **)pFrame->data , pFrame->nb_samples);

                            while(audio_len>0)//等待知道完成
                                SDL_Delay(1);

                            //Set audio buffer (PCM data)
                            audio_chunk = (Uint8 *) out_buffer;
                            //Audio buffer length
                            audio_len = out_buffer_size;
                            audio_pos = audio_chunk;
                        }

                    }
                    av_free_packet(packet);
                }
            }
        }

        swr_free(&au_convert_ctx);

        SDL_CloseAudio();//Close SDL
        SDL_Quit();

        av_free(out_buffer);
        avcodec_close(pCodecCtx);
        av_packet_free(&packet);
        av_frame_free(&pFrame);
        avformat_close_input(&pFormatCtx);
    }
}


