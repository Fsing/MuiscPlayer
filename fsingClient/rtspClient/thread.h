#ifndef __INCLUDE_THREAD_H__
#define __INCLUDE_THREAD_H__

#include "def.h"
#include <pthread.h>
#include "mutex.h"

//线程类，只要是用来创建线程
//-------------------------线程类，用户可继承CThread实现thread_proc并在thread_proc中处理事件-------------------
//-------------------------也可不继承CThread，通过设置ThreadFun以处理事件。-----------------------------------
class CThread
{
public:
    //初始化各个成员变量
    CThread();
    virtual ~CThread();
public:
    //线程函数定义
    //参数：thread：线程对象执指针，user_info：用户信息
    typedef void (*ThreadFun)( CThread* thread, long user_info );
    //创建:标准库：pthread_create()
    //参数：thread_name：线程名，user_info：用户信息，
    //		fun：线程函数,nullptr则在新线程中调用thread_proc，否则调用fun
    //返回值：0成功，-1失败
    //创建线程thread_fun---->然后在thread_fun中再根据m_fun在启动新的线程
    int Create( const char* thread_name, long user_info, ThreadFun fun = nullptr );
    //销毁,m_is_destroyed = true;
    void Destroy();
    //等待退出线程，需先调用Destroy.   m_is_exited = true、pthread_cancel( m_handle );
    void WaitExit();
    //是否已经销毁，在新线程处理函数中需判断是否已经销毁，若销毁则需返回
    //返回值：true：已销毁，false：未销毁
    //return m_is_destroyed;
    bool IsDestroyed();
    //新线程是否正在运行
    //返回值：true：正在运行，false：未运行
    bool IsRuning();
    //获取当前线程ID
    //返回值：当前线程ID
    static int GetCurThreadId();
    void setDestroyed(bool l){
        m_mutex.Enter();
        m_is_destroyed = l;
        m_mutex.Leave();
    }
private:
    //新线程执行处理函数，由用户继承实现
    //参数：user_info：用户信息
    virtual void thread_proc( long user_info ){ return; }
private:
    //线程处理函数，根据传入的arg，动态绑定到不同的子类thread_proc（）函数，并执行
    static void* thread_fun( void *arg );
//#endif
private:
    CMutex m_mutex;
    bool m_is_destroyed;            //线程是否被销毁
    bool m_is_runing;               //线程是否在运行

    pthread_t m_handle;             //线程标识符
    bool m_is_exited;               //线程是否退出,false:已经退出，true未退出
    ThreadFun m_fun;                //线程函数指针
    long m_user_info;               //用户信息
    char m_thread_name[128];        //线程名字
};

#endif
