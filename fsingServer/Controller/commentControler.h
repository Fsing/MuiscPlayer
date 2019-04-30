#ifndef COMMENT_H
#define COMMENT_H
#include <string>
#include <vector>
#include "DB/rediscontrol.h"
#include "mysql/mysql.h"

using namespace std;
class CommentController
{

public:
    CommentController();
    string getComment(string songId, string left, string right);
    string commentLike(string songId, string accountId, string method);
    string addComment(string songId,string accountId,string comment);
    vector<string> getAccount(string accountId);
    void setAccount(string accountId);

private:
        MYSQL m_database;        
};

#endif // COMMENT_H
