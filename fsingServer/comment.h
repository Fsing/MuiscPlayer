#ifndef COMMENT_H
#define COMMENT_H
#include <string>
#include "rediscontrol.h"


using namespace std;
class Comment
{

public:
    Comment();
    string getComment(string songId, string left = "0", string right = "10");
};

#endif // COMMENT_H
