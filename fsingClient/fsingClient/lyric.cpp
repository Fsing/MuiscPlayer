#include "lyric.h"
#include <QFile>
#include <QMap>
#include <QtDebug>
#include <QTextCodec>

Lyric::Lyric(QObject *parent):QObject (parent)
{

}

Lyric::Lyric(const int time, const QString text,QObject *parent)
    : QObject(parent),m_time{time}, m_text{text}
{

}

//解析歌词文件
QList<QObject *> Lyric::resolveLyric(const QString &filePath)
{
    QMap<int, QString> lyricMap;
    QList<QObject *> lyrics;
    //获取歌词路径
    if(filePath.isEmpty())
        throw QString("The path to the song file is empty");
    QString tmpPath = filePath;
    QString lyricFilePath = tmpPath.remove(filePath.right(3)) + "lrc";

    //打开歌词文件
    QFile lyricFile(lyricFilePath);
    if(!lyricFile.open(QIODevice::ReadOnly)) {
        QObject *text = new Lyric(0, "未找到歌词文件！");
        lyrics.append(text);
        return lyrics;
    }

    //设置字符串编码
    QTextCodec *codec = QTextCodec::codecForName("GBK");

    //获取歌词全部信息
    QString allText = QString(codec->toUnicode(lyricFile.readAll()));

    //关闭歌词文件
    lyricFile.close();

    //将歌词按行分解为歌词列表
    QStringList lines = allText.split("\n");

    //使用正则表达式将时间标签和歌词内容分离
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach(QString line,lines){
        //先在当前行的歌词的备份中将时间内容清除，这样就获得了歌词文本
        QString temp = line;
        temp.replace(rx, "");
        //然后依次获取当前行中所有时间标签，并分别与歌词文本存入QMap中
        int pos = rx.indexIn(line, 0);
        while(pos != -1) {
            QString cap = rx.cap(0);

            //将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            qDebug() << regexp.cap(0);
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);

            qDebug() << regexp.cap(0);

            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(? =\\]");
            qDebug() << regexp.cap(0);
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            int totalTime = minute * 60000 + second * 1000 + millisecond * 10;

            //插入到Map中去
            QString text = temp;
            lyricMap.insert(totalTime,text);
            pos += rx.matchedLength();
            pos = rx.indexIn(line, pos);
        }
    }

    QMap<int, QString>::const_iterator it = lyricMap.constBegin();
    while (it != lyricMap.constEnd()) {
         QObject *text = new Lyric(it.key(), it.value());
         lyrics.append(text);
         ++it;
    }
    return lyrics;
}

int Lyric::time() const
{
    return m_time;
}

void Lyric::setTime(int time)
{
    m_time = time;
}

QString Lyric::text() const
{
    return m_text;
}

void Lyric::setText(const QString &text)
{
    m_text = text;
}
