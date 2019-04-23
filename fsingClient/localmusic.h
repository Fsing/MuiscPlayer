#ifndef LOCIALMUSIC_H
#define LOCIALMUSIC_H

#include <QObject>
#include "songinfo.h"

class LocalMusic : public QObject
{
    Q_OBJECT
public:
    LocalMusic();

    QString formatTime(int ms);
    QObject *resolveSongInfo(const QString filePath);

    Q_INVOKABLE QList<QObject *> songList() const;
    void addSongInfo(QObject *songInfo);

private:
    QList<QObject *> m_songList;

};

#endif // LOCIALMUSIC_H
