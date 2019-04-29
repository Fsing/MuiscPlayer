#ifndef __INCLUDE_TS_FILE_READER_H__
#define __INCLUDE_TS_FILE_READER_H__

#include "def.h"
#include <stdio.h>
#include "tsheader.h"

//TS文件读取类，完成TS文件数据的读取
class CTsFileReader
{
public:
    //成员变量初始化
	CTsFileReader();
	~CTsFileReader();
public:
    //打开文件，获取信息-调用init_file（）
	int Init( const char* filename );
	int GetFileRange();
	bool SeekByTime( uint64_t sec );
	int GetTsPkt( char* buf, int len, uint64_t& pcr );
    int GetPcr(const uint8_t *data,uint64_t &pcr);
    bool IsUnitStart( const uint8_t* data );
private:
    //读取文件，获取各种成员变量信息并赋值
	int init_file();
private:
	FILE* m_file;
	char m_data_buf[TS_PKT_LEN];
    uint64_t m_file_size;                   //文件大小
    uint64_t m_cur_pcr;                     //当前进度
    uint64_t m_first_pcr;                   //第一位置
    uint64_t m_last_pcr;                    //最后的位置
};


#endif
