#include "position.h"
#include "printlog.h"
#include "qmlrtspclient.h"

extern long int myposition;

Position::Position()
{
}

Position::~Position()
{
    Destroy();
    WaitExit();
}

int Position::Start(long clientinfo)
{
    if(Create("PostionThread",clientinfo) < 0){
        LogError( "create thread  RtpClientThread failed\n" );
        return -1;
    }
    return 0;
}

void Position::thread_proc(long user_info)
{
    QmlRtspClient *qmlClient = (QmlRtspClient*)user_info;
    while(1){
        if(myposition - qmlClient->m_munite_position>= 1){
            qmlClient->m_munite_position = myposition;
            qmlClient->m_position++;
//            cout <<"position_thread: " << qmlClient->position() << endl;
            emit qmlClient->positionChanged();
        }
    }
}
