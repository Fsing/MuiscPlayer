#ifndef SONGBROKER_H
#define SONGBROKER_H
#include "ralationbroker.h"
#include "song.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class SongBroker:public RalationBroker
{
public:
    static std::shared_ptr<SongBroker> getInstance();
    std::shared_ptr<Song> findSong(std::string id); //在缓存中查询
    std::shared_ptr<Song> retrievalSong(std::string id);
    std::map<std::string,std::shared_ptr<Song>> findSongsBySongListRelation(std::string songlistID);
private:
   SongBroker();
   static std::shared_ptr<SongBroker> _instance;
   std::map<std::string,std::shared_ptr<Song>> _songs;
};

#endif // SONGBROKER_H
