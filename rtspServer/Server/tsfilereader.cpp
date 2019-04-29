#include "tsfilereader.h"
#include "printlog.h"
#include <memory.h>

CTsFileReader::CTsFileReader()
{
    m_file = nullptr;
    m_file_size = 0;
    m_cur_pcr = -1;
    m_first_pcr = -1;
    m_last_pcr = -1;
}

CTsFileReader::~CTsFileReader()
{
    if( m_file != nullptr )
        fclose( m_file ), m_file = nullptr;
}

//打开文件
int CTsFileReader::Init( const char* filename )
{
    //m_file文件指针,清空，重新打开文件
    if( m_file != nullptr )
        fclose( m_file ), m_file = nullptr;
    //和fopen()相同，但是linux特有的，fopen64（）函数为了加载大型文件所做的扩展。
    m_file = fopen64(filename, "rb" );
    if( m_file == nullptr ){
        LogError( "open file failed, filename:%s\n", filename );
        return -1;
    }
    if( init_file() < 0 )
        return -1;
    LogInfo( "file size:%lld, first pcr:%lld, last pcr:%lld\n", m_file_size, m_first_pcr, m_last_pcr );
    return 0;
}

int CTsFileReader::GetFileRange()
{
    return int((m_last_pcr - m_first_pcr)/90000);
}

bool CTsFileReader::SeekByTime( uint64_t sec )
{
    int64_t diff_sec = (int64_t)( m_first_pcr + sec*1000 - m_cur_pcr );
    if( diff_sec < 2000 && diff_sec > -2000 )
        return true;
    int64_t offset = m_file_size/((m_last_pcr-m_first_pcr)/90000)*sec/TS_PKT_LEN*TS_PKT_LEN;
    if( offset > (int64_t)m_file_size )
        offset = m_file_size;
    if( fseeko64( m_file, offset, SEEK_SET ) != 0 ){
        LogError( "seek to end failed\n" );
        return false;
    }
    return true;
}

int CTsFileReader::GetTsPkt( char* buf, int len, uint64_t& pcr )
{
    int ret = fread( buf, sizeof(char), len, m_file );
    if( ret < TS_PKT_LEN ){
        LogError( "read ts pkts failed\n" );
        return -1;
    }

    uint64_t cur_pcr = -1;
    for( int i = 0; i < ret/TS_PKT_LEN; i++ )
        GetPcr( (const uint8_t*)buf+i*TS_PKT_LEN, cur_pcr );
    if( cur_pcr != (uint64_t)-1 )
        m_cur_pcr = cur_pcr;
    pcr = m_cur_pcr;
    return ret;
}

int CTsFileReader::GetPcr(const uint8_t *data, uint64_t &pcr)
{
    TsHeader* t_h = (TsHeader*)data;
    if( t_h->sync != 0x47 || t_h->field_control < 2
        || t_h->field_len < 1 || t_h->pcr == 0 )
        return -1;
    PcrT* pcr_info = (PcrT*)(data+sizeof(TsHeader));
    pcr = ntohl(pcr_info->pcr_base);
    pcr = pcr << 1 | pcr_info->pcr_basebit;
    pcr = pcr * 300 + pcr_info->pcr_ext;
    pcr /= 300;
    //LogInfo( "pcr:%llu\n", pcr );
    return 0;
}

bool CTsFileReader::IsUnitStart(const uint8_t *data)
{
    TsHeader* t_h = (TsHeader*)data;
    return t_h->sync == 0x47 && t_h->unit_start == 1 ? true : false;
}

int CTsFileReader::init_file()
{
    m_file_size = 0;
    m_cur_pcr = -1;
    m_first_pcr = -1;
    m_last_pcr = -1;
    /*
     * 函数设置文件指针stream的位置。如果执行成功，stream将指向以fromwhere（偏移起始位置：文件头0(SEEK_SET)，当前位置1(SEEK_CUR)，文件尾2(SEEK_END)）为基准，
     * 偏移offset（指针偏移量）个字节 的位置。如果执行失败(比如offset超过文件自身大小)，则不改变stream指向的位置。
     */
    //即m_file指向文件尾
    if( fseeko64( m_file, 0, SEEK_END ) != 0 ){
        LogError( "seek to end failed\n" );
        return -1;
    }

    //返回m_file的当前位置,一个ts长度为188
    //因为m_file指向文件的末尾，所以，返回的结果就是文件的大小
    m_file_size = ftello64( m_file );
    if( m_file_size < TS_PKT_LEN ){
        LogError( "file is to small, size:%ld\n", m_file_size );
        return -1;
    }
    //m_file指向文件头
    if( fseeko64( m_file, 0, SEEK_SET ) != 0 ){
        LogError( "seek to begin failed\n" );
        return -1;
    }
    int64_t offset = -1;    //偏移量
    while(1){
        if( offset >= 0 ){
            if( fseeko64( m_file, offset, SEEK_SET ) == -1 ){
                LogError( "seek file to %lld failed\n", offset );
                return -1;
            }
        }
        uint8_t buf[TS_PKT_LEN];
        //从文件中读取一个ts packet:里面包含流媒体数据包
        if( fread( buf, sizeof(uint8_t), TS_PKT_LEN, m_file ) != TS_PKT_LEN ){
            LogError( "read one ts pkt failed\n" );
            return -1;
        }
        uint64_t pcr = 0;
        //获得pcr
        if( GetPcr( buf, pcr ) < 0 ){
            if( offset != -1 )
                offset -= TS_PKT_LEN;
            continue;
        }
        //当前、第一个pcr
        if( m_first_pcr == (uint64_t)-1 ){
            m_cur_pcr = m_first_pcr = pcr;
            offset = (m_file_size/TS_PKT_LEN-1)*TS_PKT_LEN;
        }else{
            m_last_pcr = pcr;
            break;
        }
    }
//    if( m_last_pcr <= m_first_pcr ){
//        LogError( "get file range failed\n" );
//        return -1;
//    }
//    if( fseeko64( m_file, 0, SEEK_SET ) != 0 ){
//        LogError( "seek to end failed\n" );
//        return -1;
//    }
    return 0;
}
