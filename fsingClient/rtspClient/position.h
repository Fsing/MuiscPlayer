#ifndef POSITON_H
#define POSITON_H

#include "thread.h"

class Position : public CThread
{
public:
    Position();
    ~Position();

public:
    int Start(long clientinfo);

    virtual void thread_proc( long user_info );

private:
//    long int m_munite_position;
};

#endif // POSITON_H
