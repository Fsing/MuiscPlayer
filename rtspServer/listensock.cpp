#include "listensock.h"
#include "printlog.h"
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

CListenSock::CListenSock()
{
}

CListenSock::~CListenSock()
{
    Destroy();
    WaitExit();
}

int CListenSock::Listen( const char* ip, int port )
{
    if( open( SOCK_STREAM ) < 0 )
        return -1;
    if( set_addr_reuse() < 0 || bind( ip, port ) < 0 ){
        Close();
        return -1;
    }
    if( ::listen( m_fd, 128 ) == -1 ){
        Close();
        LogError( "listen error!\n" );
        return -1;
    }
    if( Create( "Listen Thread", 0 ) < 0 ){
        Close();
        LogError( "create listen thread failed\n" );
        return -1;
    }
    return 0;
}

void CListenSock::thread_proc( long user_info )
{
    while( IsDestroyed() == false ){
        fd_set read_fd_set;
        fd_set except_fd_set;
        FD_ZERO( &read_fd_set );	//WRITE_EVENT
        FD_ZERO( &except_fd_set );	//EXCEPT_EVENT
        FD_SET( m_fd, &read_fd_set );
        FD_SET( m_fd, &except_fd_set );
        struct timeval tmv_timeout={ 0L, 1000L };//单位毫秒，默认1秒超时

        int ret = select( m_fd+1, &read_fd_set, nullptr, &except_fd_set, &tmv_timeout );
        if( ret > 0 ){
            if( FD_ISSET( m_fd, &read_fd_set ) != 0 ){
                struct sockaddr_in remote_addr;

                socklen_t sock_size = sizeof( sockaddr_in );

                int new_fd = ::accept( m_fd, (sockaddr *)&remote_addr, &sock_size );
                if( new_fd < 0 )
                    LogError( "acceptt failed, err info:%d %s\n", ERROR_NO, ERROR_STR );
//                m_client_ip = inet_ntoa(remote_addr.sin_addr);
                strcpy(m_client_ip,inet_ntoa(remote_addr.sin_addr));
                m_client_port = ntohs(remote_addr.sin_port);
                accept_sock( new_fd );
            }
            if( FD_ISSET( m_fd, &except_fd_set ) != 0 ){
                accept_sock( -1 );
                break;
            }
        }
    }
}
