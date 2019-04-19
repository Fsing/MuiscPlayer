#ifndef __INCLUDE_MUTEX_H__
#define __INCLUDE_MUTEX_H__

#include "Def.h"
#include <pthread.h>

//线程互斥锁类
class CMutex
{
public:
    //标准库：pthread_mutex_init()初始化m_mutex
    CMutex();
    //pthread_mutex_destroy():销毁m_mutex
    ~CMutex();
public:
    //进锁:pthread_mutex_lock()
    void Enter();
    //出锁:pthread_mutex_unlock()
    void Leave();
private:
    pthread_mutex_t m_mutex;
};

/////////////
//构造时进锁，析构时出锁
class CGuard
{
public:
    CGuard( CMutex& mutex ):m_mutex(mutex){ m_mutex.Enter(); }
    ~CGuard(){ m_mutex.Leave(); }
private:
    CMutex& m_mutex;
};

#endif
