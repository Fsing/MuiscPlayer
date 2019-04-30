#ifndef SONGINFO_H
#define SONGINFO_H
#include <QObject>

class SongInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString artist READ artist)
    Q_PROPERTY(QString album READ album)
    Q_PROPERTY(QString time READ time)
    Q_PROPERTY(QString size READ size)
    Q_PROPERTY(QString path READ path)

public:
    SongInfo(QString title, QString artist, QString album, QString time,QString size,QString path);

    QString title() const;

    QString artist() const;

    QString album() const;

    QString time() const;

    QString size() const;

    void setTitle(const QString &title);

    void setArtist(const QString &artist);

    void setAlbum(const QString &album);

    void setTime(const QString &time);

    void setSize(const QString &size);

    QString path() const;

private:
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_time;
    QString m_size;
    QString m_path;

};

#endif // SONGINFO_H
