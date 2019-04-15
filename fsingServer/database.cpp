#include "database.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <macro.h>
#include "json/json.h"

using std::string;           using std::cout;
using std::endl;

//INVALID 无效
//VALID 有效，存在

DatabaseController::DatabaseController()
{
}

std::string DatabaseController::songInformation(std::string songSource)
{

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return FAILD;
    }

    char sql[100];
    auto source = songSource.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from songinfo WHERE source= '%s'",source);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;

        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                //                m_userNameFlag = true;
                if(string(row[1]) == source){

                    std::string songName = row[0];
                    Json::Value root;
                    root["type"] = "SONGINFO";
                    root["songName"] = songName;
                    root.toStyledString();
                    std::string out = root.toStyledString();
                    return out.data();
                }
            }
        }
    }
    return "null infomation";
}
std::string DatabaseController::search(std::string songKey)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return "FAILD";
    }

    char sql[512];
    memset(sql,0,sizeof(char)*512);
    auto key = songKey.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from Song WHERE name like '%%%s%%' or singer like '%%%s%%'",key,key);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Song failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            Json::Value root;
            Json::Value arrayObj;
            root["type"] = "SEARCH";

            while((row = mysql_fetch_row(result))){
                //                m_userNameFlag = true;
                Json::Value item;

                item["id"] = row[0];
                item["type"] = "SONGINFO";
                item["name"] = row[1];
                item["source"] = row[2];
                item["singer"] = row[3];
                item["album"] = row[4];
                item["playQuantity"] = row[5];
                item["shareQuantity"] = row[6];
                item["downloadQuantity"] = row[7];
                arrayObj.append(item);
            }
            root["array"] = arrayObj;

            root.toStyledString();
            std::string out = root.toStyledString();
            return out.data();
        }
    }
    return "null infomation";
}
std::string DatabaseController::songAlbumInformation(std::string songId){
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "songAlbumInformation conect MYSQL failed!" << endl;
        return "FAILD";
    }

    char sql[512];
    memset(sql,0,sizeof(char)*512);
    auto key = songId.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from SongAlbumRelation WHERE songID like '%s'",key);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"songAlbumInformation select * from SongAlbumRelation failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_RES *resultAlbum;
        MYSQL_ROW row;
        MYSQL_ROW rowAlbum;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            row = mysql_fetch_row(result);
            Json::Value root;
            root["type"] = "SONGALBUM";
            string songAlbumId = row[1];


            memset(sql,0,sizeof(char)*512);
            std::sprintf(sql,"select * from SongAlbum WHERE songAlbumID like '%s'",songAlbumId.data());
            length =strlen(sql);
            res = mysql_real_query(&mysql,sql,length);
            if(res != 0){
                cout <<"SongAlbum select * from SongAlbumRelation failed" << endl;
            }else{
                resultAlbum = mysql_store_result(&mysql);
                if(resultAlbum){
                   rowAlbum = mysql_fetch_row(resultAlbum);
                           root["songAlbumName"] = rowAlbum[1];
                           root["songAlbumSource"] = rowAlbum[2];

                           std::string out = root.toStyledString();
                           return out;
                }
        }
    }
    }
    return "no album";

}

std::string DatabaseController::interface(std::string interfaceName){

    cout<<interfaceName<<endl;
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return "FAILD";
    }
    char sql[512];
    memset(sql,0,sizeof(char)*512);
    std::sprintf(sql,"select * from SongList");
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"songlist has no data" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            Json::Value root;
            Json::Value arrayObj;
            Json::Value advertArrayObj;
            root["type"] = "INTERFACE";

            int i = 0;
           while((row = mysql_fetch_row(result)) && (i < 8)){

                Json::Value item;
                item["type"] = "SONGLIST";
                item["id"] =row[0];
                item["name"] = row[1];
                item["author"] = row[2];
                item["createTime"] = row[3];
                item["label"] = row[4];
                item["info"] = row[5];
                item["icon"] = row[6];
                item["collectionQuantity"] = row[7];
                item["clickQuantity"] = row[8];
                item["shareQuantity"] = row[9];
                arrayObj.append(item);
                //only transfer 6 songlist
                ++i;
            }

                 Json::Value item1;
                 Json::Value item2;
                 Json::Value item3;
                 Json::Value item4;
                 Json::Value item5;
                 Json::Value item6;
                 item1["source"] = "ad1.jpg";
                 item2["source"] = "ad2.jpg";
                 item3["source"] = "ad3.jpg";
                 item4["source"] = "ad4.jpg";
                 item5["source"] = "ad5.jpg";
                 item6["source"] = "ad6.jpg";
                 advertArrayObj.append(item1);
                 advertArrayObj.append(item2);
                 advertArrayObj.append(item3);
                 advertArrayObj.append(item4);
                 advertArrayObj.append(item5);
                 advertArrayObj.append(item6);


            root["array"] = arrayObj;
            root["advertArray"] = advertArrayObj;
            std::string out = root.toStyledString();
            return out.data();
        }
    }
    return "null infomation";

}

std::string DatabaseController::songList(std::string songListName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return "FAILD";
    }
    char sql[512];
    memset(sql,0,sizeof(char)*512);
    auto key = songListName.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from %s",key);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            Json::Value root;
            Json::Value arrayObj;
            root["type"] = "SONGLIST";
            int resultRow = 0;

            while((row = mysql_fetch_row(result))){
                //                m_userNameFlag = true;
                Json::Value item;

                item["songName"] = row[1];
                item["type"] = "SONGINFO";
                item["source"] = row[2];
                item["id"] = row[0];
                arrayObj.append(item);
                ++resultRow;
            }
            root["array"] = arrayObj;
            root["row"] = resultRow;

            root.toStyledString();
            std::string out = root.toStyledString();
            return out.data();
        }
    }
    return "null infomation";
}

