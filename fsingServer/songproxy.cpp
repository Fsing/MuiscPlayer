#include "songproxy.h"
#include "songbroker.h"
#include "json/json.h"

std::string SongProxy::songInformation(std::string songId){
    auto songBroker = SongBroker::getInstance();
    auto res =songBroker->findSong(songId);

    Json::Value root;
    root["type"] = "SONGINFO";
    if(res == NULL){
        root["hasData"] = "no";
        return root.toStyledString();
    }else{
        root["id"] = res->getId();
        root["name"] = res->getName();
        root["source"] = res->getSource();
        root["singer"] = res->getSinger();
        root["album"] = res->getAlbum();
        root["playQuantity"] = res->getPlayQuantity();
        root["downloadQuantity"] = res->getDownloadQuantity();
        root["shareQuantity"] = res->getShareQuantity();
        return root.toStyledString();
    }
}

std::string SongProxy::fetchSong(std::string songID)
{
    auto songBroker = SongBroker::getInstance();
    auto res = songBroker->findSong(songID);

    Json::Value root;
    root["type"] = "FETCHSONG";
    if(res == nullptr){
        root["hasData"] = "no";
        return root.toStyledString();
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
        return root.toStyledString();
    }

}
