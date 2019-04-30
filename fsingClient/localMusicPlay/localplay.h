#ifndef LOCALPLAY_H
#define LOCALPLAY_H

#include <QObject>
#include "localPlayThreadContain.h"

class LocalPlay : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void play(QString songName);

private:
    LocalPlayThreadContain m_localPlayThreadContain;
};

#endif // LOCALPLAY_H
