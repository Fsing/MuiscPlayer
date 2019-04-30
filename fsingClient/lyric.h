#ifndef LYRIC_H
#define LYRIC_H

#include <QObject>

class Lyric:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY timeChanged)
public:
    Lyric(QObject *parent = 0);
    Lyric(const int time, const QString text, QObject *parent = 0);
    Q_INVOKABLE QList<QObject *> resolveLyric(const QString &filePath);//解析歌词文件

    int time() const;
    void setTime(int time);

    QString text() const;
    void setText(const QString &text);

signals:
    void textChanged();
    void timeChanged();

private:
    int m_time;
    QString m_text;
};

#endif // LYRIC_H
