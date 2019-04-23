#include "songinfo.h"

SongInfo::SongInfo(QString title, QString artist, QString album, QString time, QString size)
    : m_title{title}, m_artist{artist}, m_album{album}, m_time{time}, m_size{size}
{

}

QString SongInfo::title() const
{
    return m_title;
}

QString SongInfo::artist() const
{
    return m_artist;
}

QString SongInfo::album() const
{
    return m_album;
}

QString SongInfo::time() const
{
    return m_time;
}

QString SongInfo::size() const
{
    return m_size;
}

void SongInfo::setTitle(const QString &title)
{
    m_title = title;
}

void SongInfo::setArtist(const QString &artist)
{
    m_artist = artist;
}

void SongInfo::setAlbum(const QString &album)
{
    m_album = album;
}

void SongInfo::setTime(const QString &time)
{
    m_time = time;
}

void SongInfo::setSize(const QString &size)
{
    m_size = size;
}
