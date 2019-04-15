#ifndef SONG_H
#define SONG_H

#include <string>

class Song
{
public:
    Song(int id,std::string name,std::string source,std::string singer,std::string album
         ,int playQuantity,int downloadQuantity,int shareQuantity):
        m_id(id),m_name(name),m_singer(singer),m_album(album),m_source(source),
        m_playQuantity(playQuantity),m_downloadQuantity(downloadQuantity),m_shareQuantity(shareQuantity){}
    //get functhion
    int getId(){return m_id;}
    std::string getName(){return m_name;}
    std::string getSinger(){return m_singer;}
    std::string getAlbum(){return m_album;}
    std::string getSource(){return m_source;}

    int getPlayQuantity(){return m_playQuantity;}
    int getDownloadQuantity(){return m_downloadQuantity;}
    int getShareQuantity(){return m_shareQuantity;}


private:
    int m_id;
    std::string m_name;         //歌曲名
    std::string m_singer;       //歌手
    std::string m_album;        //专辑
    std::string m_source;
    //int m_duration;             //毫秒
    //double m_size;              //文件大小
    // std::string m_comment;      //评论
    int m_playQuantity;         //歌曲播放量
    int m_downloadQuantity;     //下载量
    int m_shareQuantity;        //分享量




};
#endif // SONG_H
