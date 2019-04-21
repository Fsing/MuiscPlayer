#include "rediscontrol.h"


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
        cout << command.c_str() <<endl;
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
    }
}


