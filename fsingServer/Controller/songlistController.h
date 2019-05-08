#ifndef SONGLISTPROXY_H
#define SONGLISTPROXY_H
#include <string>

class SongListController
{
public:
    std::string songListInformation(std::string songListId);
    std::string addSongList(std::string username, std::string songListName, std::string time);
    std::string addSongToSongList(std::string songlistID, std::string songID);
    std::string collectSongList(std::string userId, std::string songListId);
};
#endif // SONGLISTPROXY_H
