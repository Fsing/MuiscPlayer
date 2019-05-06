#include "searchcontroller.h"
#include <iostream>
SearchController::SearchController()
{

}

SearchController::~SearchController()
{

}

void SearchController::dealMessage(std::string type, Json::Value resultRoot)
{
    if (type == "SEARCH"){
        search(resultRoot);
    }

}

void SearchController::search(Json::Value resultRoot)
{
    m_searchResult.clear();
    std::cout << "SearchController                m_songsMap.size:           "<<m_songsMap.size() << std::endl;
    const Json::Value arrayObj = resultRoot["array"];
    for (unsigned int i = 0; i < arrayObj.size(); i++)
    {
        //add to song cache pool
        if(arrayObj[i]["type"] == "SONGINFO"){
            std::shared_ptr<Song> retSong = std::make_shared<Song>(
                        Song(std::stoi(arrayObj[i]["id"].asString()),
                        arrayObj[i]["name"].asString(),
                    arrayObj[i]["singer"].asString(),
                    arrayObj[i]["time"].asString(),
                    arrayObj[i]["album"].asString(),
                    arrayObj[i]["source"].asString(),
                    std::stoi(arrayObj[i]["playQuantity"].asString()),
                    std::stoi(arrayObj[i]["shareQuantity"].asString()),
                    std::stoi(arrayObj[i]["downloadQuantity"].asString())));
            m_songsMap.insert(std::make_pair(std::stoi(arrayObj[i]["id"].asString()),retSong));
            //add to Qlist
            m_searchResult.append(QString::fromStdString(arrayObj[i]["id"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["name"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["singer"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["time"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["album"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["source"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["playQuantity"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["downloadQuantity"].asString()));
            m_searchResult.append(QString::fromStdString(arrayObj[i]["shareQuantity"].asString()));
        }
       std::cout << "SearchController1                m_songsMap.size:           "<<m_songsMap.size() << std::endl;
    }
}

QList<QString> SearchController::getSearchResult()
{
    return m_searchResult;
}
