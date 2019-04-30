#ifndef REDISCONTROL_H
#define REDISCONTROL_H

#include <iostream>
#include <string>
#include "hiredis/hiredis.h"
#include <vector>
#include <memory>

#define REDISHOSTIP "127.0.0.1"
#define REDISHOSTPORT 6379

using namespace std;
string replace_all(string str,const   string&   old_value, const   string&   new_value);
class RedisControl
{
public:
    static shared_ptr<RedisControl> getInstance();
    RedisControl();
    void connect();
    vector<string> excuteCommand(string command);

    void pushQueue(string sql1);
    void popQueue();
private:
    static std::shared_ptr<RedisControl> _instance;
    redisContext *c;
};

#endif // REDISCONTROL_H
