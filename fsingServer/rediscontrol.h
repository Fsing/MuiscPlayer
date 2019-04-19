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

class RedisControl
{
public:
    static shared_ptr<RedisControl> getInstance();
    RedisControl();
    void connect();
    vector<string> excuteCommand(string command);
private:
    static std::shared_ptr<RedisControl> _instance;
    redisContext *c;
};

#endif // REDISCONTROL_H
