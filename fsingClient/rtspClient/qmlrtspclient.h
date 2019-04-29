#ifndef QMLRTSPCLIENT_H
#define QMLRTSPCLIENT_H

#include <QObject>
#include "rtspclient.h"
#include <string>

using std::string;

class QmlRtspClient : public QObject
{
    Q_OBJECT
public:
    QmlRtspClient();
    Q_INVOKABLE int start(QString songName);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void play(QString songName);

    //从配置文件中读取url信息
    int readUrl(char *url, char *port, string songName);
    //提取字符串字段
    int get_str( const char* data, const char* s_mark, bool with_s_make, const char* e_mark, bool with_e_make, char* dest );

private:
    static void data_cb_fun( const char* data, int len );

private:
    CRtspClient m_rtspClient;
    char m_client_port[32];
    string m_fileName;
};

#endif // QMLRTSPCLIENT_H
