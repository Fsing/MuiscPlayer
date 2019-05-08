#ifndef QMLRTSPCLIENT_H
#define QMLRTSPCLIENT_H

#include <QObject>
#include "rtspclient.h"
#include "position.h"
#include "mutex.h"
#include <string>

using std::string;

class QmlRtspClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(long position READ position NOTIFY positionChanged)
    Q_PROPERTY(int playState READ playState WRITE setPlayState NOTIFY playStateChanged)

public:
    QmlRtspClient();
    Q_INVOKABLE int start(QString songName);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void play(QString songName);
    Q_INVOKABLE void speed(QString position);

    //从配置文件中读取url信息
    int readUrl(char *url, char *port, string songName);
    //提取字符串字段
    int get_str( const char* data, const char* s_mark, bool with_s_make, const char* e_mark, bool with_e_make, char* dest );

    Q_INVOKABLE long position();
    Q_INVOKABLE int playState();
    Q_INVOKABLE void setPlayState(int l);

    Q_INVOKABLE double calculationDuration(QString duration);
private:
    static void data_cb_fun( const char* data, int len );
//    static void *position_thread(void *arg);
signals:
    void positionChanged();
    void playStateChanged();

    friend class Position;
private:
    CRtspClient m_rtspClient;
    Position _position;

    char m_client_port[32];
    string m_fileName;

    long int m_munite_position;
    long int m_position;
//    CMutex m_mutex;

    bool m_playState;
};

#endif // QMLRTSPCLIENT_H
