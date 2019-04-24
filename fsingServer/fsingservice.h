#ifndef FSINGSERVICE_H
#define FSINGSERVICE_H

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include "fanbroker.h"
#include <songlistbroker.h>
#include <songbroker.h>
#include "database.h"
#include "Controller/commentControler.h"
#include "Controller/listenMusicController.h"
#include "Controller/loginController.h"
#include "Controller/searchController.h"
#include "Controller/songlistController.h"

using std::vector;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

struct File_info {
    typedef unsigned long long Size_type;
    Size_type filesize;
    size_t filename_size;
    File_info() : filesize(0), filename_size(0) {}
};

class Server{
//    friend std::string dealMessage(char data[],socket_ptr sock,std::shared_ptr<Server> server);

public:
    Server();
    //接收客户端的连接
    void display();
    void waitingForConnect();
    //判断客户端发来的消息的类型,并调用相应的处理函数
    void dealMessage(string sig, vector<string> str, socket_ptr sock);
    //接收客户端信息
//    boost::system::error_code &getMessage(socket_ptr sock,boost::system::error_code &ec);
    //分配客户端接收信息
    void serviceHandle(socket_ptr sock);
    void fileSender(std::string fileName, socket_ptr sock);
    void parameterAnalysis(char data[],vector<string> &parameter);
    //处理客户端请求的操作
//    void dealOperation();
    //处理客户端请求的数据
//    void dealData();
    void pushHostList(std::string ip);
    void popHostList(std::string ip);
private:
    std::shared_ptr<LoginController> _loginController;
    std::shared_ptr<ListenMusicController> _listenMusicController;
    std::shared_ptr<SongListController> _songListController;
    std::shared_ptr<SearchController> _searchController;
    std::shared_ptr<CommentController> _commentController;
    DatabaseController database;
    vector<string> m_hostList;
};
//std::string dealMessage(char data[], socket_ptr sock, std::shared_ptr<Server> server);
#endif // FSINGSERVICE_H
