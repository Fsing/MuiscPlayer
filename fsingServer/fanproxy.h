#ifndef FANPROXY_H
#define FANPROXY_H

//#include "fanbroker.h"
#include <string>

using std::string;

class FanProxy
{
public:
    //用户登录
    string myLogin(string username,string password);
    //注册用户
    string myRegister(string username,string password);
    //查询是否相应的数据表
    bool hasTable(std::string tableName);
//    创建指定用户的原创歌单表
//    void createCreatedSongList(string songListName);
    //创建用户表Account
    bool createAccountTable();
    //
    void createCollectionRelationTable();
    //添加行到Account表
    bool insertUser(string username, string userpassword, std::string label, std::string sex, std::string birthday, std::string address, std::string icon);
    //获得指定表最大id
    int getMaxid(string tableName);
    //像指定用户的原创歌单表中添加一行信息
//    std::string addCreateSongList(std::string username,std::string songListName, std::string time);
private:
};
#endif // FANPROXY_H
