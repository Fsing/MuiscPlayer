#ifndef SONGLISTPROXY_H
#define SONGLISTPROXY_H
#include <string>

class SongListProxy
{
public:
    std::string songListInformation(std::string songListId);
    std::string addSongList(std::string username, std::string songListName, std::string time);
    std::string addSongToSongList(std::string songlistID, std::string songID);
};
#endif // SONGLISTPROXY_H
