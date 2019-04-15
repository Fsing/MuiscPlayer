#include "fan.h"

Fan::Fan()
{

}

Fan::Fan(std::string name, std::string password, std::string label, std::string sex, std::string birthday, std::string address, std::string icon)
    :m_name{name},m_password{password},m_label{label},m_sex{sex},m_birthday{birthday},m_address{address},m_icon{icon}
{

}

std::map<string,std::shared_ptr<SongList>> Fan::getCollectedSongList()
{
    return _collectedSongList;
}

std::map<std::string, std::shared_ptr<SongList>> Fan::getCreatedSongList()
{
    return _createdSongList;
}

std::map<std::string, std::shared_ptr<Fan> > Fan::getAttenedFans()
{
    return _attentedUsers;
}

std::map<std::string, std::shared_ptr<Fan> > Fan::getFanusers()
{
    return _fanUsers;
}

std::string Fan::getUserName()
{
    return m_name;

}

std::string Fan::getUserPw()
{
    return m_password;
}

void Fan::setAttentedUsers(std::map<std::string, std::shared_ptr<Fan>> attentedUsers)
{
    _attentedUsers = attentedUsers;
}

void Fan::setFanUsers(std::map<std::string, std::shared_ptr<Fan>> fanUsers)
{
    _fanUsers = fanUsers;
}

void Fan::setCollectedSongLists(std::map<std::string, std::shared_ptr<SongList>> collectedSongList)
{
    _collectedSongList = collectedSongList;
}

void Fan::setCreatedSongLists(std::map<std::string, std::shared_ptr<SongList>> createdSongList)
{
    _createdSongList = createdSongList;
}

void Fan::addCreatedSongList(std::string songlistID, std::shared_ptr<SongList> songlist)
{
    _createdSongList.insert(std::make_pair(songlistID,songlist));
}

