#include "commentControler.h"
//#include <boost/lexical_cast.hpp>
#include "json/json.h"
#include "string.h"
#include "mysql/mysql.h"

CommentController::CommentController()
{

}

string CommentController::getComment(string songId,string left = "1", string right = "10"){
    auto redisControl = RedisControl::getInstance();
    string command;
    command += "zrevrange ";
    command += "point_";
    command += songId;
    command += " ";
    command += to_string(stoi(left)-1);
    command += " ";
    command += right;
    command += " withscores";

    try {
        vector<string> vec;
        try {
            vec = redisControl->excuteCommand(command);
        }catch (const char * e) {
            try {
                MYSQL mysql;
                mysql_init(&mysql);
                if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,nullptr,0)){
                    throw "getComment conect MYSQL failed!";
                }
                char sql[512];
                memset(sql,0,sizeof(char)*512);
                std::sprintf(sql,"select * from Comment WHERE songId = '%s' order by points desc limit %d,%d",songId.data(),stoi(left)-1,stoi(right));
                size_t length =strlen(sql);
                int res = mysql_real_query(&mysql,sql,length);
                if(res != 0){
                    cout << sql << endl;
                    throw "excute error";
                }else{
                    MYSQL_RES *result;
                    MYSQL_ROW row;
                    result = mysql_store_result(&mysql);
                    if(result){
                          while((row = mysql_fetch_row(result))){
                        string command3;
                        command3 += "zadd point_";
                        command3 += row[1];
                        command3 += " ";
                        command3 += row[4];
                        command3 += " ";
                        command3 += row[2];

                        redisControl->excuteCommand(command3);

                        string command4 ;
                        command4 += "set ";
                        command4 += row[1];
                        command4 += "_";
                        command4 += row[2];
                        command4 += " ";
                        command4 += replace_all(string(row[3])," ","&nbsp");
                        redisControl->excuteCommand(command4);
                          }
                    }
                }
            } catch (...) {
                throw ;
            }
        }

        vec = redisControl->excuteCommand(command);
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
string CommentController::commentLike(string songId, string accountId, string method){
    auto redisControl = RedisControl::getInstance();
    Json::Value root;
    root["type"] = "COMMENTLIKE";
    try {
        string sql;
        if("like"==method){
            sql += "update Comment set points = points + 1  where songid = '";
            sql += songId;
            sql += "' and accountId = '";
            sql += accountId;
            sql += "'";
            redisControl->pushQueue(sql);
        }else if("unlike"==method){
            sql += "update Comment set points = points - 1  where songid = '";
            sql += songId;
            sql += "' and accountId = '";
            sql += accountId;
            sql += "'";
            redisControl->pushQueue(sql);
        }else
            throw "method error";



        string command;
        command += "zincrby ";
        command += "point_";
        command += songId;
        command += " ";
        if("like" == method){
            command += "1";
        }else if("unlike" == method){
            command += "-1";
        }else {
            throw "like method is not right ";
        }
        command += " ";
        command += accountId;
        vector<string> vec = redisControl->excuteCommand(command);
        root["status"] = "800";
        return root.toStyledString();
    } catch (const char * e) {
        cout << "commendLike receive exception " << e << endl;
        root["message"] = e;
    } catch (int & e){
        cout << "commendLike receive exception " << e << endl;
        root["message"] = e;
    } catch (...){
        cout << "commendLike receive exception " <<  endl;
        root["message"] = "unknon error";
    }
    root["status"] = "500";
    return root.toStyledString();
}
string CommentController::addComment(string songId,string accountId,string comment){
    auto redisControl = RedisControl::getInstance();
    Json::Value root;
    root["type"] = "ADDCOMMENT";
    try {
        MYSQL mysql;
        mysql_init(&mysql);
        if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,nullptr,0)){
            throw "addComment conect MYSQL failed!";
        }

        char sql1[1024];
        string num;
        std::sprintf(sql1,"select 1 from Comment where songId = %s and accountId = %s",
                     songId.data(),accountId.data());
        auto length1 = strlen(sql1);
        if(mysql_real_query(&mysql,sql1,length1)){
            throw  "inset into comment fail";
        }else {
            MYSQL_RES *result;
            MYSQL_ROW row;
            result = mysql_store_result(&mysql);
            if(result){
                  while((row = mysql_fetch_row(result))){
                    num = row[0];
                  }
            }
        }
        if(""!=num)
            throw "there is already has a comment";

        string Ssql = "insert into Comment(songId,accountId,comment,points)";
        Ssql += " values('";
        Ssql += songId;
        Ssql += "','";
        Ssql += accountId;
        Ssql += "','";
        Ssql += comment;
        Ssql += "',0)";
        redisControl->pushQueue(Ssql);

        string command;
        command += "zscore ";
        command += "point_";
        command += songId;
        command += " ";
        command += accountId;
        vector<string> vec = redisControl->excuteCommand(command);
        if("null"==vec[0]){
            string command1;
            command1 += "zadd ";
            command1 += "point_";
            command1 += songId;
            command1 += " 1 ";
            command1 += accountId;
            redisControl->excuteCommand(command1);

            string command2;
            command2 += "set ";
            command2 += songId;
            command2 += "_";
            command2 += accountId;
            command2 += " ";
            command2 += replace_all(comment," ","&nbsp");
            cout << command2 <<endl;
            redisControl->excuteCommand(command2);

            root["status"] = "800";
            return root.toStyledString();
        }else {
            throw "there is already have a comment";
        }

    } catch (const char * e) {
        cout << "addComment receive exception " << e << endl;
        root["message"] = e;
    } catch (int & e){
        cout << "addComment receive exception " << e << endl;
        root["message"] = e;
    } catch (...){
        cout << "addComment receive exception " <<  endl;
        root["message"] = "unknon error";
    }
    root["status"] = "500";
    return root.toStyledString();
}
vector<string> CommentController::getAccount(string accountId){
    auto redisControl = RedisControl::getInstance();
    vector<string> retVec;
    string command;
    command += "hgetall ";
    command += "account_";
    command += accountId;
    try {
        vector<string> vec = redisControl->excuteCommand(command);

        for(unsigned long i = 0;i < vec.size();i+=2){
            retVec.push_back(replace_all(vec[i+1],"&nbsp"," "));
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

void CommentController::setAccount(string accountId){
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
