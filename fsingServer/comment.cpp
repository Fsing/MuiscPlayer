#include "comment.h"
//#include <boost/lexical_cast.hpp>
#include "json/json.h"
#include "string.h"

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
            vector<string> accountMeta;
            try {
                accountMeta = getAccount(vec[i]);
            } catch (const char * e) {
                cout << "getComment receive exception " << e
                     << " add accountMeta " << vec[i]
                        << " to redis"
                        << endl;
                setAccount(vec[i]);
                accountMeta = getAccount(vec[i]);
            } catch (int & e){
                cout << "getComment receive exception " << e << endl;
                throw e;
            }


            Json::Value item;
            item["accountId"] = vec[i].c_str();
            item["accountName"] = accountMeta[0];
            item["points"] = vec[i+1].c_str();
            item["comment"] = setVec[0].c_str();
            arryObj.append(item);
        }
        root["array"] = arryObj;
        return root.toStyledString();
    } catch (const char * e) {
        cout << "getComment receive exception " << e << endl;
        throw e;
    } catch (int & e){
        cout << "getComment receive exception " << e << endl;
        throw e;
    }
}


vector<string> Comment::getAccount(string accountId){
    auto redisControl = RedisControl::getInstance();
    vector<string> retVec;
    string command;
    command += "hgetall ";
    command += "account_";
    command += accountId;
    try {
        vector<string> vec = redisControl->excuteCommand(command);

        for(unsigned long i = 0;i < vec.size();i+=2){
            retVec.push_back(vec[i+1]);
        }
        return retVec;
    } catch (const char * e) {
        cout << "getAccount receive exception " << e << endl;
        throw e;
    } catch (int & e){
        cout << "getAccount receive exception " << e << endl;
        throw e;
    }
}

void Comment::setAccount(string accountId){
    auto redisControl = RedisControl::getInstance();
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,nullptr,0)){
        std::cout << "findUser conect MYSQL failed!" << std::endl;
        throw "connect mysql fail";
    }

    char sql[512];
    auto source = accountId.data();

    std::sprintf(sql,"select * from Account WHERE id = '%s'",source);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);


    if(res != 0){
        throw sql;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        result = mysql_store_result(&mysql);
        if(result){
            string command;
            while((row = mysql_fetch_row(result))){
                command += "hmset ";
                command += "account_";
                command += accountId;
                command += " ";
                command += "name";
                command += " ";
                command += replace_all(string(row[1])," ","&nbsp");
                command += " ";
                command += "label";
                command += " ";
                command += replace_all(string(row[3])," ","&nbsp");
                command += " ";
                command += "sex";
                command += " ";
                command += replace_all(string(row[4])," ","&nbsp");
                command += " ";
                command += "birthday";
                command += " ";
                command += replace_all(string(row[5])," ","&nbsp");
                command += " ";
                command += "address";
                command += " ";
                command += replace_all(string(row[6])," ","&nbsp");
                command += " ";
                command += "icon";
                command += " ";
                command += replace_all(string(row[7])," ","&nbsp");
                command += " ";
            }
            redisControl->excuteCommand(command);
        }
    }
}
string   replace_all(string   str,const   string&   old_value, const   string&   new_value)
{
    while(true)   {
        string::size_type   pos(0);
        if(   (pos=str.find(old_value))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}
