#ifndef COMMENT_H
#define COMMENT_H
#include <string>
#include <vector>
#include "rediscontrol.h"
#include "mysql/mysql.h"

using namespace std;
string replace_all(string str,const   string&   old_value, const   string&   new_value);
class Comment
{

public:
    Comment();
    string getComment(string songId, string left = "0", string right = "10");
    vector<string> getAccount(string accountId);
    void setAccount(string accountId);

private:
        MYSQL m_database;
};

#endif // COMMENT_H
