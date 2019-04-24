#include "listenMusicController.h"
#include "Entity/songbroker.h"
#include <json/json.h>
#include <string>
#include <cstring>
#include <iostream>

std::string ListenMusicController::songInformation(std::string songId){
    auto songBroker = SongBroker::getInstance();
    Json::Value root;
    root["type"] = "SONGINFO";
    try {
        auto res =songBroker->findSong(songId);
        if(res == nullptr){
            throw "nodata";
        }else{
            root["hasData"] = "yes";
            root["id"] = res->getId();
            root["name"] = res->getName();
            root["source"] = res->getSource();
            root["singer"] = res->getSinger();
            root["album"] = res->getAlbum();
            root["playQuantity"] = res->getPlayQuantity();
            root["downloadQuantity"] = res->getDownloadQuantity();
            root["shareQuantity"] = res->getShareQuantity();
        }
        return root.toStyledString();
    } catch (const char * e) {
        cout << "songInformation receive exception " << e << endl;
        root["hasData"] = "no";
        root["message"] = e;
    } catch (int & e){
        cout << "songInformation receive exception " << e << endl;
        root["message"] = e;
    } catch (...){
        cout << "songInformation receive exception " <<  endl;
        root["message"] = "unknon error";
    }
    root["status"] = "500";
    return root.toStyledString();
}

std::string ListenMusicController::fetchSong(std::string songID)
{
    auto songBroker = SongBroker::getInstance();
    Json::Value root;
    root["type"] = "FETCHSONG";
    try {
        auto res = songBroker->findSong(songID);


        if(res == nullptr){
            root["hasData"] = "no";
            throw "nodata";
        }else{
            root["hasData"] = "yes";
            root["id"] = res->getId();
            root["name"] = res->getName();
            root["source"] = res->getSource();
            root["singer"] = res->getSinger();
            root["album"] = res->getAlbum();
            root["playQuantity"] = res->getPlayQuantity();
            root["downloadQuantity"] = res->getDownloadQuantity();
            root["shareQuantity"] = res->getShareQuantity();
        }
        return root.toStyledString();
    } catch (const char * e) {
        cout << "fetchSong receive exception " << e << endl;
        root["hasData"] = "no";
        root["message"] = e;
    } catch (int & e){
        cout << "fetchSong receive exception " << e << endl;
        root["message"] = e;
    } catch (...){
        cout << "fetchSong receive exception " <<  endl;
        root["message"] = "unknon error";
    }
    root["status"] = "500";
    return root.toStyledString();
}
string ListenMusicController::songAlbumInformation(string songId){
    MYSQL mysql;
    mysql_init(&mysql);
    Json::Value root;
    root["type"] = "SONGALBUM";
    try {
        if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,nullptr,0)){
            throw "songAlbumInformation conect MYSQL failed!" ;
        }

        char sql[512];
        memset(sql,0,sizeof(char)*512);
        auto key = songId.data();
        //    auto pw = password.data();
        std::sprintf(sql,"select * from SongAlbumRelation WHERE songID like '%s'",key);
        size_t length =strlen(sql);
        int res = mysql_real_query(&mysql,sql,length);
        if(res != 0){
            throw "songAlbumInformation select * from SongAlbumRelation failed" ;
        }else{
            MYSQL_RES *result;
            MYSQL_RES *resultAlbum;
            MYSQL_ROW row;
            MYSQL_ROW rowAlbum;
            //    MYSQL_FIELD *fields;

            result = mysql_store_result(&mysql);
            if(result){
                row = mysql_fetch_row(result);
                string songAlbumId = row[1];


                memset(sql,0,sizeof(char)*512);
                std::sprintf(sql,"select * from SongAlbum WHERE songAlbumID like '%s'",songAlbumId.data());
                length =strlen(sql);
                res = mysql_real_query(&mysql,sql,length);
                if(res != 0){
                    throw "SongAlbum select * from SongAlbumRelation failed" ;
                }else{
                    resultAlbum = mysql_store_result(&mysql);
                    if(resultAlbum){
                        rowAlbum = mysql_fetch_row(resultAlbum);
                        root["songAlbumName"] = rowAlbum[1];
                        root["songAlbumSource"] = rowAlbum[2];
                    }
                }
            }
        }
        root["status"] = "800";
        return root.toStyledString();
    } catch (const char * e) {
        cout << "songAlbumInformation receive exception " << e << endl;
        root["message"] = e;
    } catch (int & e){
        cout << "songAlbumInformation receive exception " << e << endl;
        root["message"] = e;
    } catch (...){
        cout << "songAlbumInformation receive exception " <<  endl;
        root["message"] = "unknon error";
    }
    root["status"] = "500";
    return root.toStyledString();
}
