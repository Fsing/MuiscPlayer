#ifndef DATABASE_H
#define DATABASE_H

#include <string>

class DatabaseController
{
public:
    //初始化，如果没有，创建服务器在线歌曲的所有表
    DatabaseController();

    std::string songInformation(std::string songSource);
    std::string search(std::string songKey);
    std::string songList(std::string songListName);
    std::string interface(std::string interfaceName);
    std::string songAlbumInformation(std::string songId);
private:
    std::string m_userName;
    std::string m_userPassword;

};
#endif // DATABASE_H
