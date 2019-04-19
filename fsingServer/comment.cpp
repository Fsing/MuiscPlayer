#include "comment.h"
//#include <boost/lexical_cast.hpp>
#include "json/json.h"


Comment::Comment()
{

}

string Comment::getComment(string songId,string left,string right ){
    auto redisControl = RedisControl::getInstance();
    string command;
    command += "zrevrange ";
    command += "point_";
    command += songId;
    command += " ";
    command += left;
    command += " ";
    command += right;
    command += " withscores";

    try {
        vector<string> vec = redisControl->excuteCommand(command);

        Json::Value root;
        Json::Value arryObj;
        root["type"] = "COMMENT";
        root["songId"] = songId.c_str();
        for(unsigned long i = 0;i < vec.size();i+=2){
            string vecCommand;
            vecCommand += "get ";
            vecCommand += songId;
            vecCommand += "_";
            vecCommand += vec[i];
            vector<string> setVec = redisControl->excuteCommand(vecCommand);


            Json::Value item;
            item["accountId"] = vec[i].c_str();
            item["points"] = vec[i+1].c_str();
            item["comment"] = setVec[0].c_str();
            arryObj.append(item);
        }
            root["array"] = arryObj;
            return root.toStyledString();
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
