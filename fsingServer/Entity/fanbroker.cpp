#include "fanbroker.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <sstream>
#include "songlist.h"
#include "songlistbroker.h"


using std::cout;            using std::endl;
using std::string;          using std::vector;


std::shared_ptr<FanBroker> FanBroker::_instance = std::make_shared<FanBroker>(FanBroker());
std::shared_ptr<FanBroker> FanBroker::getInstance()
{
    return _instance;
}

std::shared_ptr<Fan> FanBroker::findUserInCache(std::string username)
{
    if(_fans.find(username) != _fans.end()){
        return _fans[username];
    }else{
        return nullptr;
    }
}

void FanBroker::updateCacheForCreatedSongList(std::string username, std::shared_ptr<SongList> songlist)
{
    std::stringstream ss;
    ss << songlist->getId();
    string id;
    ss >> id;
    _fans[username]->addCreatedSongList(id,songlist);
}

std::shared_ptr<Fan> FanBroker::findUser(std::string username)
{
    cout << "enter findUser" << endl;
    if(_fans.find(username) != _fans.end()){
        return _fans[username];
    }else{
        return retrievalUser(username);
    }
}

std::shared_ptr<Fan> FanBroker::retrievalUser(std::string username)
{
    cout << "enter retrievalUser" << endl;

    //查找用户基本信息
    auto ret = findUserByUserName(username);
    if(ret != nullptr){
        //查找用户created歌单信息
        auto songlistBroker = SongListBroker::getInstance();
        auto createdSongLists = songlistBroker->findSongListsByUserName(username);

        //查找用户collected歌单信息
        auto collectedSongLists = songlistBroker->findSongListsByCollectionRelation(username);

        //查找关注的用户
        auto attentedfans = findAttentedFanByRelation(username);

        //查找粉丝
        auto fans = findFansByRelation(username);

        //实例化新的用户对象
        ret->setCreatedSongLists(createdSongLists);
        ret->setCollectedSongLists(collectedSongLists);
        ret->setAttentedUsers(attentedfans);
        ret->setFanUsers(fans);

        //往缓存中添加用户
        _fans.insert(std::make_pair(username,ret));
        return ret;
    }
    return nullptr;
}

//通过表FanRelation查找关联的用户---关注用户
std::map<std::string, std::shared_ptr<Fan> > FanBroker::findAttentedFanByRelation(std::string username)
{
    std::map<string,std::shared_ptr<Fan>> attentedFans;
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findSongListsByCollectionRelation: conect MYSQL failed!" << endl;
        return attentedFans;
    }

    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from FanRelation where fanName='%s'",username.data());
    size_t length = strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"findAttentedFanByRelation:select * from FanRelation faild " << endl;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                attentedFans.insert(std::make_pair(row[0],findUserByUserName(row[0])));
            }
        }
    }
    return attentedFans;
}

//通过表FanRelation查找关联的用户---粉丝
std::map<string,std::shared_ptr<Fan>> FanBroker::findFansByRelation(string username)
{
    std::map<string,std::shared_ptr<Fan>> fans;
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findSongListsByCollectionRelation: conect MYSQL failed!" << endl;
        return fans;
    }

    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from FanRelation where userName='%s'",username.data());
    size_t length = strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"findAttentedFanByRelation:select * from FanRelation faild " << endl;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                fans.insert(std::make_pair(row[1],findUserByUserName(row[1])));
            }
        }
    }
    return fans;
}

//再Account中查找单个用户的信息,并返回Fan对象
std::shared_ptr<Fan> FanBroker::findUserByUserName(string username)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findSongListsByCollectionRelation: conect MYSQL failed!" << endl;
        return nullptr;
    }

    string name;
    string password;
    string label;
    string sex;
    string birthday;
    string address;
    string icon;
    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from Account where name='%s'",username.data());
    size_t length = strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"findUserByUserName:select * from Account faild " << endl;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                name = row[1];
                password = row[2];
                label = row[3];
                sex = row[4];
                birthday = row[5];
                address = row[6];
                icon = row[7];
                return std::make_shared<Fan>(Fan(name,password,label,sex,birthday,address,icon));
            }
        }
    }
    return nullptr;
}


//std::map<string,std::shared_ptr<Fan>> FanBroker::findUserBySongListName(std::string songlistId)
//{
//    std::map<string,std::shared_ptr<Fan>> users;
//    MYSQL mysql;
//    mysql_init(&mysql);
//    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
//        cout << "findSongListsByCollectionRelation: conect MYSQL failed!" << endl;
//        return users;
//    }

//    char sql[512];
//    MYSQL_RES *result;
//    MYSQL_ROW row;
//    std::sprintf(sql,"select * from CollectionRelation where songlistID='%s'",songlistId.data());
//    size_t length = strlen(sql);
//    int res = mysql_real_query(&mysql,sql,length);
//    if(res != 0){
//        cout <<"findUserBySongListName:select * from CollectionRelation faild " << endl;
//    }else{
//        result = mysql_store_result(&mysql);
//        if(result){
//            while((row = mysql_fetch_row(result))){
//                users.insert(std::make_pair(row[0],findUser(row[0])));
//            }
//        }
//    }
//    return users;
//}
FanBroker::FanBroker()
{

}
