#include "ntime.h"
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>

uint64_t CNTime::GetCurMs()
{
    return GetCurUs()/1000;
}

uint64_t CNTime::GetCurUs()
{
    struct timeval cur_time;
    gettimeofday( &cur_time, nullptr );
    return cur_time.tv_sec*1000000+cur_time.tv_usec;
}

