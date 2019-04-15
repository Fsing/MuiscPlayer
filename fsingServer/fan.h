#ifndef FAN_H
#define FAN_H
#include "user.h"
#include "songlist.h"
#include <string>
#include <map>
#include <memory>
#include <string>
#include <vector>

//class SongList;

using std::string;      using std::vector;
using std::map;

class Fan:public User
{
public:
    Fan();
    Fan(string name,string password,string label,string sex,string birthday,string address,string icon);

    //getting
    std::map<std::string, std::shared_ptr<SongList>> getCollectedSongList();
    std::map<std::string, std::shared_ptr<SongList> > getCreatedSongList();
    std::map<string ,std::shared_ptr<Fan>> getAttenedFans();
    std::map<string ,std::shared_ptr<Fan>> getFanusers();
    string getUserName();
    string getUserPw();
//    int getUserId();
    string getlabel(){return m_label;}
    string getSex(){return m_sex;}
    string getBirthday(){return m_birthday;}
    string getAddress(){return m_address;}
    string getIcon(){return m_icon;}

    //setting
    void setAttentedUsers(std::map<string ,std::shared_ptr<Fan>> attentedUsers);
    void setFanUsers(std::map<string,std::shared_ptr<Fan>> fanUsers);
    void setCollectedSongLists(std::map<string,std::shared_ptr<SongList>> collectedSongList);
    void setCreatedSongLists(std::map<std::string, std::shared_ptr<SongList> > createdSongList);

    //adding
    void addCreatedSongList(string songlistID,std::shared_ptr<SongList> songlist);

private:
//    int m_userID;               //用户id
    std::string m_name;         //用户名
    std::string m_password;     //用户密码
    std::string m_label;        //用户标签
    std::string m_sex;          //性别
    std::string m_birthday;     //生日
    std::string m_address;      //地址
    std::string m_icon;         //头像，保存路径
    bool m_vaild;               //状态变量，用来标志歌曲是否违法，是否可用
    std::map<string,std::shared_ptr<SongList>> _collectedSongList;    //已收藏歌单
    std::map<string,std::shared_ptr<SongList>> _createdSongList;      //创建歌单
    std::map<string ,std::shared_ptr<Fan>> _attentedUsers;               //关注的用户
    std::map<string,std::shared_ptr<Fan>> _fanUsers;                   //粉丝
};
#endif // FAN_H
