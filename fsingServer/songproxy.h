#ifndef SONGPROXY_H
#define SONGPROXY_H
#include <string>

class SongProxy
{
public:
    std::string songInformation(std::string songId);
    std::string fetchSong(std::string songID);
};
#endif // SONGPROXY_H
