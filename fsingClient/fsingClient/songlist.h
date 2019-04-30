#ifndef SONGLIST_H
#define SONGLIST_H

#include <memory>
#include "song.h"
#include <map>

class SongList
{
public:
    SongList();
    SongList(int id,std::string name,std::string author, std::string createTime,std::string label,
             std::string info,std::string icon,int collectionQuantity,
             int clickQuantity,int shareQuantity)
        :m_id{id},m_name{name},m_author{author},m_createTime{createTime},m_label{label},
          m_info{info},m_icon{icon},m_collectionQuantity{collectionQuantity},
          m_clickQuantity{clickQuantity},m_shareQuantity{shareQuantity}{}
//    SongList():m_id{0},m_name{""},m_author{""},m_createTime{""},m_label{""},m_info{""},m_icon{""},m_collectionQuantity{0},m_clickQuantity{0},m_shareQuantity{0}{}

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
    //set
    void setSongs(std::map<int,std::shared_ptr<Song>> songs){
        _songs = songs;
    }
    std::map<int,std::shared_ptr<Song>> getSongs(){
        return _songs;
    }

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
//    std::map<std::string,std::shared_ptr<Fan>> _collectionUsers;        //收藏歌单的所有用户
    //歌单中的歌
    std::map<int,std::shared_ptr<Song>> _songs;
};
#endif // SONGLIST_H
