#include "mutex.h"

CMutex::CMutex()
{
    pthread_mutex_init( &m_mutex, nullptr );
}

CMutex::~CMutex()
{
	pthread_mutex_destroy( &m_mutex );
}

void CMutex::Enter()
{ 
	pthread_mutex_lock( &m_mutex );
}

void CMutex::Leave()
{ 
	pthread_mutex_unlock( &m_mutex );
}
