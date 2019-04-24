#ifndef FANBROKER_H
#define FANBROKER_H
#include "ralationbroker.h"
#include "fan.h"
#include <memory>
#include <map>

class FanBroker : public RalationBroker
{
public:
    static std::shared_ptr<FanBroker> getInstance();   //静态成员函数，只能通过类名调用
    std::shared_ptr<Fan> findUser(std::string username);            //在缓存中查询
    std::shared_ptr<Fan> retrievalUser(std::string username);       //在数据库中检索,检索用户的所有信息，包括歌单、关注、粉丝
    std::map<string,std::shared_ptr<Fan>> findAttentedFanByRelation(string username);       //通过表FanRelation查找关联的用户---关注用户
    std::map<string,std::shared_ptr<Fan>> findFansByRelation(string username);              //通过表FanRelation查找关联的用户---粉丝
    std::shared_ptr<Fan> findUserByUserName(string username);                               //再Account中查找单个用户的信息,并返回Fan对象
//    std::map<std::string, std::shared_ptr<Fan> > findUserBySongListName(string songlistId);   //通过歌单id，在CollectionRelation表中查找收藏歌单的用户
    std::shared_ptr<Fan> findUserInCache(std::string username);            //在缓存中查找是否存在数据
    void updateCacheForCreatedSongList(std::string username, std::shared_ptr<SongList> songlist);       //更新缓存

private:
    FanBroker();        //保护构造函数，不能通过new创建对象
//    ~FanBroker();
    static std::shared_ptr<FanBroker> _instance;
    std::map<std::string, std::shared_ptr<Fan>> _fans;       //用户名为键
};
#endif // FANBROKER_H
