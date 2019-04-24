#ifndef SONGPROXY_H
#define SONGPROXY_H
#include <string>

using namespace  std;
class ListenMusicController
{
public:
    string songInformation(string songId);
    string fetchSong(string songID);
    string songAlbumInformation(string songId);

};
#endif // SONGPROXY_H
