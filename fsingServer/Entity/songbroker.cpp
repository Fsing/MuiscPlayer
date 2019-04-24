#include "songbroker.h"
#include <string.h>
#include <iostream>
#include "song.h"

std::shared_ptr<SongBroker> SongBroker::_instance = std::make_shared<SongBroker>(SongBroker());
SongBroker::SongBroker()
{
}
std::shared_ptr<Song> SongBroker::findSong(std::string id)
{
    if(_songs.find(id) != _songs.end()){
        std::cout << "find previous data"<< id << std::endl;
        return _songs[id];
    }else{
        return retrievalSong(id);
    }
}

std::shared_ptr<Song> SongBroker::retrievalSong(std::string id)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        std::cout << "findUser conect MYSQL failed!" << std::endl;
        return nullptr;
    }

    char sql[512];
    auto source = id.data();

    std::sprintf(sql,"select * from Song WHERE id = '%s'",source);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    std::shared_ptr<Song> ret;

    if(res != 0){
        std::cout <<"retrievalSong: select * from Song failed" << std::endl;
        return nullptr;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                //往缓存中添加歌曲
                ret = std::make_shared<Song>(Song(atoi(row[0]),row[1],row[2],
                        row[3],row[4],atoi(row[5]),atoi(row[6]),atoi(row[7])));
                _songs.insert(std::make_pair(row[0],ret));
            }
        }
    }
    return ret;
}

std::map<std::string,std::shared_ptr<Song>> SongBroker::findSongsBySongListRelation(std::string songlistID)
{
    std::map<std::string,std::shared_ptr<Song>> ret;
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        std::cout << "findSongsBySongListRelation: conect MYSQL failed!" << std::endl;
        return ret;
    }

    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from SongListRelation WHERE songlistID = '%s'",songlistID.data());
    auto length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        std::cout <<"findSongsBySongListRelation: select * from Song failed" << std::endl;
        return ret;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while((row = mysql_fetch_row(result))){
                MYSQL mysql1;
                mysql_init(&mysql1);
                if(!mysql_real_connect(&mysql1,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
                    std::cout << "findSongsBySongListRelation: conect MYSQL failed!" << std::endl;
                    return ret;
                }
                char sqlSong[512];
                MYSQL_RES *resultSong;
                MYSQL_ROW rowSong;
                std::sprintf(sqlSong,"select * from Song WHERE id = '%s'",row[1]);
                auto lengthSong =strlen(sqlSong);
                int resSong = mysql_real_query(&mysql1,sqlSong,lengthSong);
                if(resSong != 0){
                    std::cout <<"findSongsBySongListRelation: select * from Song failed" << std::endl;
                    return ret;
                }else{
                    resultSong = mysql_store_result(&mysql1);
                    if(resultSong){
                        while((rowSong = mysql_fetch_row(resultSong))){
                            ret.insert(std::make_pair(rowSong[0],
                                       std::make_shared<Song>(Song(atoi(rowSong[0]),rowSong[1],
                                       rowSong[2],rowSong[3],rowSong[4],atoi(rowSong[5]),atoi(rowSong[6]),atoi(rowSong[7])))));
                        }
                    }
                }
            }
        }
    }
    return ret;
}
std::shared_ptr<SongBroker> SongBroker::getInstance()
{
    return _instance;
}
