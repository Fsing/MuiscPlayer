#include "localmusic.h"
#include <QDir>
#include <QDebug>
#include <taglib/fileref.h>
#include <taglib/tag.h>
extern "C"
{
#include <libavformat/avformat.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}

using namespace std;

LocalMusic::LocalMusic()
{
//    QDir dir("/root/tmp");
//    dir.setFilter(QDir::Files | QDir::NoSymLinks);

//    QStringList nameFilters;
//    nameFilters << "*.mp3";
//    dir.setNameFilters(nameFilters);
//    QStringList files = dir.entryList();
//    m_songList.clear();
//    for (int i = 0; i < files.size(); ++i){
//        QString path = "/root/tmp/" + files.at(i);

//        addSongInfo(resolveSongInfo(path));
//    }

//    qDebug() << m_songList.size();
    //return files;
}

void LocalMusic::setDirList(QList<QString> dirList)
{
    try{
    if (dirList.count() != 0)
        for (int i = 0; i < dirList.count(); i++){
            m_dirList.push_back(dirList[i]);
        }
        dealDirList();
    } catch(...){

    }
}

void LocalMusic::dealDirList()
{
    if (m_dirList.count() != 0){
        m_songList.clear();
        for(int i = 0; i < m_dirList.count(); i++){
            //qDebug() << m_dirList[i] +"m_dirList[i]#############";
            QDir dir(m_dirList[i]);
            dir.setFilter(QDir::Files | QDir::NoSymLinks);

            QStringList nameFilters;
            nameFilters << "*.mp3";
            dir.setNameFilters(nameFilters);
            QStringList files = dir.entryList();
            //qDebug() << files.size() +"#############";
            for (int j = 0; j < files.size(); ++j){
                QString path = m_dirList[i] + "/" + files.at(j);
                //qDebug() << path + " -================";

                addSongInfo(resolveSongInfo(path));
            }
        }
    }

    qDebug() << m_songList.size();
}

QString LocalMusic::formatTime(int ms)
{
    int ss = 1000000;
    int mi = ss * 60;

    long minute = ms / mi;
    long second = (ms - minute * mi) / ss;

    QString min_tmp = QString("%1").arg(minute, 2, 10, QChar('0'));
    QString sec_tmp = QString("%1").arg(second, 2, 10, QChar('0'));
    QString res = min_tmp + ":" +sec_tmp;
    return res;
}

QObject *LocalMusic::resolveSongInfo(const QString filePath)
{
    TagLib::FileRef f(filePath.toLocal8Bit());
    QString title = QString::fromLocal8Bit(f.tag()->title().toCString(true));
    QString artist= QString::fromLocal8Bit(f.tag()->artist().toCString(true));
    QString album= QString::fromLocal8Bit(f.tag()->album().toCString(true));
    QString time;

    av_register_all();
    avformat_network_init();
    AVFormatContext	*pFormatCtx;

    pFormatCtx = avformat_alloc_context();

    if (avformat_open_input(&pFormatCtx, filePath.toLocal8Bit().data(), NULL, NULL) != 0){
        qDebug() << "Couldn't open input stream.";
    } else {
        if(avformat_find_stream_info(pFormatCtx,NULL)>=0){
            auto duration = pFormatCtx->duration;
            time = formatTime(duration);
           //qDebug() << time ;
        }
    }

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    double size_tmp = (file.size()/1024.0)/1024;
    QString size = QString::number(size_tmp, 'f', 1);
    //QString path = "file://" + filePath;
    QString path = filePath;

    QObject *info = new SongInfo(title, artist, album, time, size,path);
    return info;
}

QList<QObject *> LocalMusic::songList() const
{
    return m_songList;
}

void LocalMusic::addSongInfo(QObject *songInfo)
{

    m_songList.append(songInfo);
}

