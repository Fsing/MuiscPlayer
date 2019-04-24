#ifndef SONGLIST_H
#define SONGLIST_H

#include <string>
#include <memory>
#include <map>
//#include "fan.h"
#include "song.h"
#include <vector>
#include <string>

class Fan;

class SongList
{
public:
    SongList(int id,std::string name,std::string author, std::string createTime,std::string label,
             std::string info,std::string icon,int collectionQuantity,
             int clickQuantity,int shareQuantity)
        :m_id{id},m_name{name},m_author{author},m_createTime{createTime},m_label{label},
          m_info{info},m_icon{icon},m_collectionQuantity{collectionQuantity},
          m_clickQuantity{clickQuantity},m_shareQuantity{shareQuantity}{}
    //insert
    void insertSong(std::string songlistID, std::shared_ptr<Song> ret);

    //getting
    int getId(){return m_id;}
    std::string getName(){return m_name;}
    std::string getAuthor(){return m_author;}
    std::string getCreateTime(){return m_createTime;}
    std::string getLabel(){return m_label;}
    std::string getInfo(){return m_info;}
    std::string getIcon(){return m_icon;}

    int getCollectionQuantity(){return m_collectionQuantity;}
    int getClickQuantity(){return m_clickQuantity;}
    int getShareQuantity(){return m_shareQuantity;}

    std::map<std::string,std::shared_ptr<Song>> getSongs(){
        return _songs;
    }

    //setting
    void setSongs(std::map<std::string,std::shared_ptr<Song>> songs);
    void setCollectionUsers(std::map<std::string,std::shared_ptr<Fan>> collectionUsers){_collectionUsers = collectionUsers;}

    void addSong(std::string songID, std::shared_ptr<Song> song);
private:
    int m_id;                       //歌单ID，歌单的关键字，标识符
    std::string m_name;             //歌单名
    std::string m_author;           //歌单创建者
    std::string m_createTime;       //创建时间

    //double m_size;                  //大小
    std::string m_label;            //标签
    std::string m_info;             //简介
    std::string m_icon;             //歌单头像路径
    //std::string m_comment;          //评论
    int m_collectionQuantity;       //收藏量
    int m_clickQuantity;            //点击量
    int m_shareQuantity;            //分享量
    std::map<std::string,std::shared_ptr<Fan>> _collectionUsers;        //收藏歌单的所有用户
    std::map<std::string,std::shared_ptr<Song>> _songs;                 //歌单中的歌
};
#endif // SONGLIST_H
