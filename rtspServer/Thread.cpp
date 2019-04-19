#include "Thread.h"
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif	//_WIN32
#include "PrintLog.h"

CThread::CThread()
{
    m_is_destroyed = false;
    m_is_runing = false;
#ifndef _WIN32
    m_handle = -1;
#else
    m_handle = nullptr;
#endif
    m_is_exited = true;
    m_fun = nullptr;
    m_user_info = 0;
    memset( m_thread_name, 0, sizeof(m_thread_name) );
}

CThread::~CThread()
{
}

//创建线程
//fun：线程函数,NULL则在新线程中调用thread_proc，否则调用fun
int CThread::Create( const char* thread_name, long user_info, ThreadFun fun )
{
    strncpy( m_thread_name, thread_name, sizeof(m_thread_name)-1 );
    m_user_info = user_info;
    m_fun = fun;

    //创建
    if(pthread_create( &m_handle, nullptr, thread_fun, this ) != 0 ){
        LogError( "create thread failed\n" );
        return -1;
    }
    return 0;
}

void CThread::Destroy()
{
    m_is_destroyed = true;
}

void CThread::WaitExit()
{
    int i = 400;
    while( i-- > 0 ){
        if( m_is_exited == true )
            break;
        Sleep(5);
    }
    if( m_is_exited == false ){
        LogInfo( "terminate thread %s\n", m_thread_name );
        pthread_cancel( m_handle );
    }
}

bool CThread::IsDestroyed()
{
    return m_is_destroyed;
}

bool CThread::IsRuning()
{
    return m_is_runing;
}

int CThread::GetCurThreadId()
{
    return pthread_self();
}

void* CThread::thread_fun( void* arg )
{
    pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, nullptr ); // 设置其他线程可以cancel掉此线程
    pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, nullptr );   //设置立即取消
    CThread* thread = (CThread*)arg;
    LogInfo( "enter thread %s, id:%d\n", thread->m_thread_name, GetCurThreadId() );
    thread->m_is_runing = true;
    thread->m_is_exited = false;
    //-----------线程执行----------------------------
    if( thread->m_fun == nullptr )
        thread->thread_proc( thread->m_user_info );
    else
        thread->m_fun( thread, thread->m_user_info );
    //-----------线程执行----------------------------
    //表示线程已经退出
    LogInfo( "leave thread %s, id:%d\n", thread->m_thread_name, GetCurThreadId() );
    thread->m_is_runing = false;
    thread->m_is_exited = true;
#ifndef _WIN32
    pthread_detach( pthread_self() );
#endif
    return 0;
}
