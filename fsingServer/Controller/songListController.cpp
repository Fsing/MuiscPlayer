#include "songlistController.h"
#include "Entity/songlistbroker.h"
#include "Entity/songbroker.h"
#include "listenMusicController.h"
#include "json/json.h"
#include "loginController.h"
#include "Entity/fanbroker.h"

#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

std::string SongListController::songListInformation(std::string songListId){
    auto songListBroker = SongListBroker::getInstance();
    Json::Value root;
    Json::Value arryObj;
    root["type"] = "SONGLIST";
    try {
    auto res =songListBroker->findSongList(songListId);
    if(res == nullptr){
        throw "nodata";
    }else{
        root["hasData"] = "yes";
        root["id"] = res->getId();
        root["name"] = res->getName();
        root["author"] = res->getAuthor();
        root["createTime"] = res->getCreateTime();
        root["label"] = res->getLabel();
        root["info"] = res->getInfo();
        root["icon"] =res->getIcon();
        root["collectionQuantity"] = res->getCollectionQuantity();
        root["clickQuantity"] = res->getClickQuantity();
        root["shareQuantity"] = res->getShareQuantity();

        auto map = res->getSongs();
        for(auto iter = map.begin(); iter != map.end(); iter++) {
             Json::Value item;
             item["id"] = iter->second->getId();
             item["name"] = iter->second->getName();
             item["source"] = iter->second->getSource();
             item["singer"] = iter->second->getSinger();
             item["album"] = iter->second->getAlbum();
             item["time"] = iter->second->getTime();
             item["playQuantity"] = iter->second->getPlayQuantity();
             item["downloadQuantity"] = iter->second->getDownloadQuantity();
             item["shareQuantity"] = iter->second->getShareQuantity();
             arryObj.append(item);
         }
        root["array"] = arryObj;
    }
    root["status"] = "800";
    return root.toStyledString();
} catch (const char * e) {
    cout << "songListInformation receive exception " << e << endl;
    root["hasData"] = "no";
    root["message"] = e;
} catch (int & e){
    cout << "songListInformation receive exception " << e << endl;
    root["message"] = e;
} catch (...){
    cout << "songListInformation receive exception " <<  endl;
    root["message"] = "unknon error";
}
root["status"] = "500";
return root.toStyledString();
}
std::string SongListController::addSongList(std::string username, std::string songListName, std::string time)
{
    Json::Value root;
    root["type"] = "CREATESONGLIST";
    root["username"] = username;
    root["songListName"] = songListName;   //歌单名
    root["createTime"] = time;

    if(username.size()){
        //记录创建歌单成功返回SUCCESS,反之返回FAILD
        MYSQL mysql;
        mysql_init(&mysql);
        if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
            cout << "addCreateSongList conect MYSQL failed!" << endl;
            root["recordSuccess"] = "FAILD";
            root.toStyledString();
            return root.toStyledString();
        }
        //验证是否已经有重复的歌单名，有则不可创建
        char sql[512];
        MYSQL_RES *result;
        MYSQL_ROW row;
        std::sprintf(sql,"select * from SongList where name='%s' and author='%s'",songListName.data(),username.data());
        if(!mysql_real_query(&mysql,sql,strlen(sql))){
            result = mysql_store_result(&mysql);
            if(result){
                while((row = mysql_fetch_row(result))){
                    root["recordSuccess"] = "NAME_INVAILD";
                    root.toStyledString();
                    return root.toStyledString();
                }
            }
        }else{
            cout <<"addSongList: select * from SongList faild!" << endl;
            root["recordSuccess"] = "FAILD";
            root.toStyledString();
            return root.toStyledString();
        }

        //歌单名可用，插入一行歌单信息
        MYSQL mysql1;
        mysql_init(&mysql1);
        if(!mysql_real_connect(&mysql1,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
            cout << "addCreateSongList conect MYSQL failed!" << endl;
            root["recordSuccess"] = "FAILD";
            root.toStyledString();
            return root.toStyledString();
        }
        auto uname = username.data();
        auto lname = songListName.data();
        auto ctime = time.data();
        //std::shared_ptr<LoginController> loginController;
        //auto maxid = loginController->getMaxid("SongList");
        std::sprintf(sql,"insert into SongList(name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) values('%s','%s','%s','0','0','songListIcon.png',0,0,0)",lname,uname,ctime);
        auto length = strlen(sql);
        if(!mysql_real_query(&mysql1,sql,length)){
            //如果缓存中有该用户，则从缓存中删除，下一次查找更新
            auto fanBroker = FanBroker::getInstance();
            if(fanBroker->findUserInCache(username)){
                auto songlistBroker = SongListBroker::getInstance();
                auto songlist = songlistBroker->findSongListBySongListNameAndUserName(songListName,username);
                fanBroker->updateCacheForCreatedSongList(username,songlist);
            }
            cout <<"addSongList:insert into SongList: " << songListName << " success!" << endl;

            char sql3[512];
            MYSQL_RES *result3;
            MYSQL_ROW row3;
            MYSQL mysql3;
            mysql_init(&mysql3);
            if(!mysql_real_connect(&mysql3,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
                cout << "addCreateSongList conect MYSQL failed!" << endl;
                root["recordSuccess"] = "FAILD";
                root.toStyledString();
                return root.toStyledString();
            }
            std::sprintf(sql3,"select id from SongList where name='%s' and author='%s'",songListName.data(),username.data());
            if(!mysql_real_query(&mysql3,sql3,strlen(sql3))){
                result3 = mysql_store_result(&mysql3);
                cout << result3 << sql3 <<endl;
                if(result3){
                    while((row3 = mysql_fetch_row(result3))){
                        root["songListID"] = row3[0];
                    }
                }
            }

            root["recordSuccess"] = "SUCCESS";
            return root.toStyledString();
        }else {
            cout <<"record create song list " << lname << " false" << endl;
            root["recordSuccess"] = "FAILD";
            root.toStyledString();
            return root.toStyledString();
        }
    }else{
        cout <<"addSongList:insert into SongList: " << songListName << " faild!" << endl;
        root["recordSuccess"] = "FAILD";
        root.toStyledString();
        return root.toStyledString();
    }
}

std::string SongListController::addSongToSongList(std::string songlistID, std::string songID)
{
    Json::Value root;
    root["type"] = "ADDSONGTOSONGLIST";
    root["songListID"] = songlistID;
    root["songID"] = songID;   //歌单名

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "addSongToSongList conect MYSQL failed!" << endl;
        root["collectSongSuccess"] = "FAILD";
        root.toStyledString();
        return root.toStyledString();
    }

    //验证歌单中是否已经存在此歌曲
    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from SongListRelation where songlistID='%s' and songID='%s'",songlistID.data(),songID.data());
    if(!mysql_real_query(&mysql,sql,strlen(sql))){
        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                root["collectSongSuccess"] = "SONG_EXISRENCE";
                root.toStyledString();
                return root.toStyledString();
            }
        }
    }else{
        cout <<"addSongToSongList: select * from SongListRelation faild!" << endl;
        root["collectSongSuccess"] = "FAILD";
        root.toStyledString();
        return root.toStyledString();
    }

    //插入收藏歌曲信息
    char sql1[512];
    auto songlistId = songlistID.data();
    auto songId = songID.data();
    std::sprintf(sql1,"insert into SongListRelation(songlistID, songID) values('%s','%s')",songlistId,songId);
    auto length = strlen(sql1);
    if(!mysql_real_query(&mysql,sql1,length)){
        cout <<"addSongToSongList:insert into SongListRelation success!" << endl;
        root["cellectSongToSuccess"] = "SUCCESS";
        auto songlistBroker = SongListBroker::getInstance();
        auto songBroker = SongBroker::getInstance();
        songlistBroker->updateCacheForSong(songlistID,songID,songBroker->findSong(songID));
        root.toStyledString();
        return root.toStyledString();
    }else {
        cout <<"record insert song to songlist false" << endl;
        root["collectSongSuccess"] = "FAILD";
        root.toStyledString();
        return root.toStyledString();
    }
}

std::string SongListController::collectSongList(std::string userId, std::string songListId){
    Json::Value root;
    root["type"] = "COLLECTSONGLIST";
    root["userID"] = userId;
    root["songListID"] = songListId;   //歌单名

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "collectSongList conect MYSQL failed!" << endl;
        root["status"] = "800";
        root["msg"] = "connect mysql fail";
        return root.toStyledString();
    }

    //验证歌单中是否已经存在此歌曲
    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select 1 from CollectionRelation where collectedUser=(select"
                     " name from Account where id = '%s') and songlistID='%s'",userId.data(),songListId.data());
    if(!mysql_real_query(&mysql,sql,strlen(sql))){
        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                if(""!=string(row[0])){
                root["status"] = "400";
                root["msg"] = "the songlist is already collect";
                return root.toStyledString();
                }
            }
        }
    }else{
        cout <<"addSongToSongList: select * from SongListRelation faild!" << endl;
        root["status"] = "400";
        root["msg"] = "CollectRelation query failed";
        return root.toStyledString();
    }

    //插入收藏歌曲信息
    char sql1[512];
    std::sprintf(sql1,"insert into CollectionRelation(collectedUser, songlistID) values(("
                      "select name from Account where id ='%s'),'%s')",userId.data(),songListId.data());
    cout << sql << endl ;
    auto length = strlen(sql1);
    if(!mysql_real_query(&mysql,sql1,length)){
        cout <<"CollectRelation:insert into CollectRelation success!" << endl;
        root["status"] = "800";
        return root.toStyledString();
    }else {
        cout <<"record insert song to songlist false" << endl;
        root["status"] = "400";
        root["msg"] = "CollectRelation insert failed";
        root.toStyledString();
        return root.toStyledString();
    }

}
