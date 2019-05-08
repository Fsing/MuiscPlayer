#include "thread.h"
#include <string.h>
#include <unistd.h>
#include "printlog.h"
#include <exception>
#include <iostream>

using std::cout;        using std::end;

CThread::CThread()
{
    m_is_destroyed = false;
    m_is_runing = false;
    m_handle = -1;

    m_is_exited = true;
    m_fun = nullptr;
    m_user_info = 0;
    is_destroy_has_changed = false;
    memset( m_thread_name, 0, sizeof(m_thread_name) );
}

CThread::~CThread()
{
}

//创建线程
//fun：线程函数,nullptr则在新线程中调用thread_proc，否则调用fun
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
        if( m_is_exited == true ){
            LogInfo( "terminate thread %s\n", m_thread_name );
            break;
        }
        Sleep(5);
    }
    if( m_is_exited == false ){
        LogInfo( "terminate thread %s\n", m_thread_name );
        auto i = pthread_cancel( m_handle );
//        pthread_exit(nullptr);
        /*主线程 关闭子线程时pthread_cancel()不能让子线程立即退出
         * ，线程继续执行直到有线程取消点，但pthread_cancel()却自动返回，
         * 让主线程继续执行，但主线程不得不释放内存，
         * 这样子线程就有可能访问到释放的内存中，导致段错误。
         * 这种问题可以通过 设置标志位和pthread_join()来解决，但是有可能时间过长（比如子线程中有个sleep（））。
         * 解决方案是，主线程初始化的时候就释放内存，而子线程结束时不释放内存。
         * 也就是说把本次内存释放工作，交给下次系统初始化去做，这样子线程爱什么时候退出就什么时候退出吧！perfict！
         */
        void *ret = nullptr;
        pthread_join(m_handle,&ret);
        cout << (char*)ret << endl;
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
    pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, nullptr ); // 设置其他线程可以cancel掉此线程,第二个参数不为nullptr,则保存原来的Cancel状态，以便恢复
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
//    if(thread->m_thread_name == "RtspSessionThread"){
//        thread->delete_rtspSession(thread->m_ffd);
//    }
//    pthread_detach( pthread_self() );
//    pthread_cancel(pthread_self());
//    void *ret;
//    pthread_join(pthread_self(),&ret);
//    pthread_exit(nullptr);
    return ((void*)0);
}
