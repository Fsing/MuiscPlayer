#include "fsingcontroller.h"

std::map<int,std::shared_ptr<SongList>> FSingController::m_songListsMap;
std::map<int,std::shared_ptr<Song>> FSingController::m_songsMap;

FSingController::FSingController()
{

}

FSingController::~FSingController()
{

}
