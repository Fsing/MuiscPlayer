#include "rediscontrol.h"
#include "mysql/mysql.h"
#include "string"
#include "string.h"
#include <unistd.h>

shared_ptr<RedisControl> RedisControl::_instance =
        make_shared<RedisControl>(RedisControl());

RedisControl::RedisControl()
{
    try {
        connect();
    } catch (exception &e) {
        cout << e.what() << endl;
    }
}
shared_ptr<RedisControl> RedisControl::getInstance()
{
    return _instance;
}

void RedisControl::connect(){
    c = redisConnect(REDISHOSTIP, REDISHOSTPORT);
    if (c != nullptr && c->err) {
        printf("Error: %s\n", c->errstr);
        throw "redis connect error";
    }
}

vector<string> RedisControl::excuteCommand(string command){
    vector<string> retVec;
    redisReply * reply;
    try {
        reply = static_cast<redisReply*>(redisCommand(c,command.c_str()));
        if (reply->type == REDIS_REPLY_ARRAY) { //array
            if(0 == reply->elements){
                throw "nodata";
            }
            for (unsigned long j = 0; j < reply->elements; j++) {
                retVec.push_back(reply->element[j]->str);
            }
        }else if(reply->type == REDIS_REPLY_STRING){ //get
            retVec.push_back(reply->str);
        }else if(reply->type == REDIS_REPLY_STATUS) { //set
            retVec.push_back(reply->str);
        }else if(reply->type == REDIS_REPLY_NIL) { //set
            retVec.push_back("null");
        }else if(reply->type == REDIS_REPLY_INTEGER) { //zadd
            retVec.push_back("ok");
        }else {
            cout << command <<endl;
            cout << reply->str <<endl;
            throw reply->type;
        }

        freeReplyObject(reply);
        return retVec;
    } catch (const char *e) {
        cout << e << endl;
        freeReplyObject(reply);
        throw e;
    } catch (int &e){
        cout << e << endl;
        freeReplyObject(reply);
        throw e;
    } catch (exception & e){
        cout << e.what() <<endl;
        freeReplyObject(reply);
        throw e;
    }
}
void RedisControl::pushQueue(string sql1){
    RedisControl rediscontrol;
    vector<string> retVec;
    string command;
    command += "lpush ";
    command += "MessageQueue ";
    command += replace_all(sql1," ","&nbsp");
    try {
        vector<string> vec = rediscontrol.excuteCommand(command);
        if ("ok"!=vec[0])
            throw "pushQueue error";
    } catch (const char * e) {
        cout << "pushQueue receive exception " << e << endl;
        throw e;
    } catch (int & e){
        cout << "pushQueue receive exception " << e << endl;
        throw e;
    }
}
void RedisControl::popQueue(){
    RedisControl rediscontrol;
    MYSQL mysql;
    mysql_init(&mysql);
    vector<string> retVec;
    string command;
    command += "rpop ";
    command += "MessageQueue";
    string sql1;

    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,nullptr,0))
    {
        std::cout << "popQueue conect MYSQL failed!" << std::endl;
        throw "popQueue connect mysql fail";
    }

    while (1){
        try {
            vector<string> vec = rediscontrol.excuteCommand(command);
            if ("null"!=vec[0]){
                cout << "sql1" << sql1 <<endl;
                sql1 = replace_all(vec[0],"&nbsp"," ");

            }else {
                throw "nodata";
            }

            char sql[512];
            std::sprintf(sql,"%s",sql1.data());
            size_t length =strlen(sql);
            int res = mysql_real_query(&mysql,sql,length);
            if(res != 0){
                cout << "popQueue excute error sql=" << sql <<endl;
                throw "popQueue  excute error";
            }
        }catch (const char * e){
            //cout << e << endl;
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

