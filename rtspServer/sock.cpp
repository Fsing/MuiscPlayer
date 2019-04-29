#include "sock.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "printlog.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>

CSock::CSock()
{
    m_fd = INVALID_SOCK_FD;
}

CSock::~CSock()
{
    Close();
}

int CSock::GetFd() const
{
    return m_fd;
}

//绑定socket fd
//参数：fd：socket fd
//返回值：0成功，-1失败
//给m_fd赋值
int CSock::AttachFd( int fd )
{	
    if( m_fd != INVALID_SOCK_FD )
        return -1;
    else
        m_fd = fd;
    if( m_fd > 0 ){
        //设置是否阻塞
        if( set_block_opt( false ) < 0 ){
            m_fd = INVALID_SOCK_FD;
            return -1;
        }
    }
    return 0;
}

int CSock::DetachFd()
{
    int tmp = m_fd;
    m_fd = INVALID_SOCK_FD;
    return tmp;
}

int CSock::open( int sock_type )
{
    Close();
    //创建套接字
    m_fd = ::socket( AF_INET, sock_type, 0 );
    if( m_fd == -1 ){
        LogError( "create socket failed, err info:%d %s\n", ERROR_NO, ERROR_STR );
        return -1;
    }
    //设置不阻塞
    if( set_block_opt( false ) < 0 ){
        Close();
        return -1;
    }
    return m_fd;
}

void CSock::Close()
{
    if( m_fd != INVALID_SOCK_FD ){
        ::close( m_fd );
        m_fd = INVALID_SOCK_FD;
    }
}

int CSock::bind( const char* ip, int port )
{
    struct sockaddr_in local_addr;
    if( get_addr( ip, port, local_addr ) < 0 )
        return -1;
    if( ::bind( m_fd, (struct sockaddr *)&local_addr, sizeof(local_addr) ) == -1 ){
        LogError( "bind failed, err info:%d %s\n", ERROR_NO, ERROR_STR );
        return -1;
    }
    return 0;
}

//从字符串中提取IP，并将ip、port等赋值给 sockaddr_in addr中的对应成员变量
int CSock::get_addr( const char* ip, int port, sockaddr_in& addr )
{
    int ip_n = 0;
    if( ip == nullptr || ip[0] == '\0' )
        ip_n = 0;
    else if( inet_addr(ip) == INADDR_NONE ){
        struct hostent* hent = nullptr;
        if( (hent = gethostbyname( ip )) == nullptr ){
            LogError( "get host by name failed, name:%s\n", ip );
            return -1;
        }
        memcpy( &ip_n, *(hent->h_addr_list), sizeof(ip_n) );
    }else
        ip_n = inet_addr(ip);
    addr.sin_family = AF_INET;      //协议族
    addr.sin_addr.s_addr = ip_n;
    addr.sin_port = htons( port );
    return 0;
}

int CSock::set_addr_reuse()
{
    int opt = 1;
    //设置closesocket（）后，还可以重用该socket(m_fd)
    if( ::setsockopt( m_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt) ) < 0 ){
        LogError( "set reuseaddr failed, err info:%d %s\n", ERROR_NO, ERROR_STR );
        return -1;
    }
    return 0;
}

int CSock::set_block_opt( bool is_block )
{
    if( m_fd == INVALID_SOCK_FD )
        return 0;
    //获取文件描述符标志
    int flags = ::fcntl( m_fd, F_GETFL );
    if( flags < 0 ) {
        LogError( "set socket block failed! %s\n", ERROR_STR );
        return -1;
    }
    if( is_block )
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;
    //设置套接字文件描述符状态
    int retval = ::fcntl( m_fd, F_SETFL, flags );
    if( retval < 0 ){
        LogError( "set socket block failed! %s\n", ERROR_STR );
        return -1;
    }
    return 0;
}
