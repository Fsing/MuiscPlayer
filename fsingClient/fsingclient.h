#ifndef FSINGCLINET_H
#define FSINGCLINET_H

#include <QObject>

class FSingClient:public QObject
{
    Q_OBJECT
public:
    FSingClient();
    ~FSingClient(){}

    Q_INVOKABLE void connect_server();
};

#endif // FSINGCLINET_H
