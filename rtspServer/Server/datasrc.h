#ifndef __INCLUDE_DATA_SRC_H__
#define __INCLUDE_DATA_SRC_H__

#include "def.h"
#include "thread.h"
#include "mutex.h"
#include "tsfilereader.h"
#include "sock.h"

//数据源类，完成RTP打包
class CDataSrc : public CThread
{
public:
	CDataSrc();
	~CDataSrc();
public:
    //sdp赋值,并创建线程：Data Source Thread
	int Init( const char* content, int id, NotifyFun fun, long user_info );
	const char* GetSdp();
	int GetRange();
	int GetMediaNum();
	struct MediaInfo{
		char track_id[32];
		uint16_t seq;
		uint32_t rtp_time;
		uint32_t ssrc;
	};
	int GetMediaInfo( int media_index, MediaInfo& media_info );
	int PerPlay( int s_sec, int e_sec );
	//rtp_ch < 0 RTP OVER UDP; rtp_ch >= 0 RTP OVER RTSP
	int Play( CSock* sock, int rtp_ch );
	int Pause();
private:
	virtual void thread_proc( long user_info );
private:
    char m_sdp[2048];           //SDP
	int m_range;
	int m_media_num;
	enum{
		MAX_MEDIA_NUM = 1,
	};
	MediaInfo m_media_info[MAX_MEDIA_NUM];
	int m_s_sec;
	int m_e_sec;
	CMutex m_mutex;
    CTsFileReader m_reader;             //文件读取
    CSock* m_sock;                      //套接字
	int m_rtp_ch;
	uint64_t m_start_pcr;
	uint64_t m_start_ms;
	uint64_t m_last_pcr;
	NotifyFun m_fun;
	long m_user_info;
};

#endif
