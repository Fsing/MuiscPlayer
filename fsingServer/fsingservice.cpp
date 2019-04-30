#include "fsingservice.h"
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <exception>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Include/macro.h"
#include "json/json.h"

using namespace boost::asio;
using std::cout;            using std::endl;
using std::string;          using std::vector;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;


io_service service;   //创建调度器
ip::tcp::endpoint ep(ip::tcp::v4(),2001);  //监听端口
ip::tcp::acceptor acc(service,ep); //创建连接器

//void parameterAnalysis(char data[],vector<string> &parameter);
//接受客户端传来的请求事务,并将结果返回给客户端
//void serviceHandle(socket_ptr sock);

Server::Server()
{
    cout << "server is running" <<endl;
}


void Server::display(){
    while (true) {
        sleep(5);
        system("clear");
        cout << "there are " <<m_hostList.size() << " hosts connected" << endl;
        for (auto &l:m_hostList){
            cout << l <<endl;
        }
    }
}
void Server::waitingForConnect()
{
    //如果套接字连接一个已经在使用中的本地地址，则进行重用地址，因为每一个连接都由本地地址和远端地址的组合唯一确定，所以只要远端地址不同，两个套接口与一个地址捆绑并无大碍
    //设置套接口实现不要因为一个地址已被一个套接口使用就不让它与另一个套接口捆绑，在bind()调用前先设置SO_REUSEADDR选项
    //    ip::tcp::socket sock_;
    bool value = true;
    setsockopt(1,SOL_SOCKET,SO_REUSEADDR,(void *)&value,sizeof(value));
    while(true){
        socket_ptr sock(new ip::tcp::socket(service));
        acc.accept(*sock); //接收新的连接
        boost::thread(boost::bind(&Server::serviceHandle,this,sock)); //开辟线程去处理该连接上的事务
        //前两步可以等价于
        //        acc.async_accept(*sock,boost::bind(client_session,sock));
    }
}


//异步传送消息,写回客户端
void sendMessage(string result2,socket_ptr sock)
{
    std::cout << result2 << std::endl;
    boost::system::error_code ec;
    if(result2 != "fileTransfer"){
        char data2[1024*10];
        memset(data2,0,sizeof(data2));

        char headLength[10];
        memset(headLength,0,sizeof(headLength));
        sprintf(headLength, "%lu", result2.size());
        result2.copy(data2,result2.size(),0);

        sock->write_some(buffer(headLength), ec);  //send the length of message to client
        if(ec)
        {
            std::cout << boost::system::system_error(ec).what() << std::endl;
            throw ec;
        }
        sock->write_some(buffer(data2), ec);  //send message to client
        if(ec)
        {
            std::cout << boost::system::system_error(ec).what() << std::endl;
            throw ec;
        }
    }
}


void Server::dealMessage(string sig,vector<string> str,socket_ptr sock)
{
    string res;
    cout << "dealMessage:" << sig << endl;

    try {
        if(sig == "SONGINFO"){
            res = _listenMusicController->songInformation(str[1]);
        }else if(sig == "REGISTER"){
            res = _loginController->myRegister(str[1],str[2]);
        }else if(sig == "LOGIN"){
            cout << "enter dealMessage" << endl;
            res = _loginController->myLogin(str[1],str[2]);
        }else if(sig == "SEARCH"){
            res = _searchController->search(str[1]);
        }else if(sig == "FILETRANSFER"){
            fileSender(str[1],sock);
            res = "fileTransfer";
        }else if(sig == "CREATESONGLIST"){
            res = _songListController->addSongList(str[1],str[2],str[3]);
        }else if(sig == "ADDSONGTOSONGLIST"){
            res = _songListController->addSongToSongList(str[1], str[2]);
        }else if(sig == "GETSONGSFROMSONGLIST"){
            res = _songListController->songListInformation(str[1]);
        }else if(sig == "SONGLIST"){
            res = _songListController->songListInformation(str[1]) ;
        }else if(sig == "INTERFACE"){
            res = database.interface(str[1]);
        }else if(sig == "FETCHSONG"){
            res = _listenMusicController->fetchSong(str[1]);
        }else if(sig == "SONGALBUM"){
            res = _listenMusicController->songAlbumInformation(str[1]);
        }else if(sig == "COMMENT"){
            res = _commentController->getComment(str[1],str[2],str[3]);
        }else if(sig == "COMMENTLIKE"){
            res = _commentController->commentLike(str[1],str[2],str[3]);
        }else if(sig == "ADDCOMMENT"){
            res = _commentController->addComment(str[1],str[2],str[3]);
        }else
            res = "wrongParameter";

        sendMessage(res,sock);
    }catch (std::exception &e){
        cout << "dealMessage "<< e.what() << endl;
        sendMessage("server error",sock);
    }
}

//接受客户端传来的请求事务,并将结果返回给客户端
void Server::serviceHandle(socket_ptr sock)
{
    boost::system::error_code ec;
    auto ep1 = sock->remote_endpoint(ec); //获得客户端的连接端口
    try {
        if(ec)
            std::cout << boost::system::system_error(ec).what() << std::endl;
        pushHostList(ep1.address().to_string());
        while(true)
        {
            char data1[512];
            memset(data1,0,sizeof(char)*512);
            //同步接收消息，异步处理
            sock->read_some(buffer(data1), ec);
            if(ec)
            {
                throw boost::system::system_error(ec);
            }
            cout << "receive from client : " << data1<<endl;

            try {
                if(strlen(data1) != 0){
                    vector<string> result1;
                    parameterAnalysis(data1,result1);//deal json parameter into vector

                    if(result1[0]== "FILETRANSFER")
                        dealMessage(result1[0],result1,sock);
                    else
                        boost::thread(boost::bind(&Server::dealMessage,this,result1[0],result1,sock));
                }
            }catch (const char* msg){
                cout << "serviceHandle LOOP" << msg << endl;
            }
        }
    }catch(std::exception){
        popHostList(ep1.address().to_string());
        cout << "Host disconnected: "<<ep1.address().to_string()<< endl;
    }
}
void Server::parameterAnalysis(char data[], vector<string> &parameter){
    Json::Value  value;
    Json::Reader reader;

    try {
        if (!reader.parse(data, value))
        {
            throw "no post data!";
        }else{
            string type = value["type"].asString();
            if(type == "SONGINFO"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songInfo"].asString());
            }else if(type == "REGISTER"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["userName"].asString());
                parameter.push_back(value["userPassword"].asString());
            }else if(type == "LOGIN"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["userName"].asString());
                parameter.push_back(value["userPassword"].asString());
            }else if(type == "SEARCH"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songKey"].asString());
            }else if(type == "FILETRANSFER"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["fileName"].asString());
            }else if(type == "CREATESONGLIST"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["username"].asString());
                parameter.push_back(value["songListName"].asString());
                parameter.push_back(value["createTime"].asString());
            }else if(type == "ADDSONGTOSONGLIST"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songListID"].asString());
                parameter.push_back(value["songID"].asString());
            }else if(type == "SONGLIST"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songListId"].asString());
            }else if(type == "SONGALBUM"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songId"].asString());
            }else if(type == "GETSONGSFROMSONGLIST"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songListID"].asString());
            }else if(type == "INTERFACE"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["interfaceName"].asString());
            }else if(type == "FETCHSONG"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songID"].asString());
            }else if(type == "COMMENT"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songId"].asString());
                parameter.push_back(value["left"].asString());
                parameter.push_back(value["right"].asString());
            }else if(type == "COMMENTLIKE"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songId"].asString());
                parameter.push_back(value["accountId"].asString());
                parameter.push_back(value["method"].asString());
            }else if(type == "ADDCOMMENT"){
                parameter.push_back(value["type"].asString());
                parameter.push_back(value["songId"].asString());
                parameter.push_back(value["accountId"].asString());
                parameter.push_back(value["comment"].asString());
            }
            else parameter.push_back("wrongParameter");
        }
    }catch (std::exception &e){
        cout << "parameterAnalysis " <<e.what() << endl;
        throw e;
    }
}

void Server::pushHostList(string ip){
    m_hostList.push_back(ip);
}

void Server::popHostList(string ip){
    m_hostList.erase( std::remove( m_hostList.begin(), m_hostList.end(), ip ), m_hostList.end());
}













/* ---------------------------------------- */
void Server::fileSender(string fileName,socket_ptr sock){
    //typedef boost::asio::ip::tcp TCP;

    auto filename = fileName.data();
    FILE *fp = fopen(filename, "rb");
    if (fp == nullptr) {
        cout << "cannot open file\n" <<endl;
        File_info file_info;
        char buffer[16];
        memcpy(buffer, &file_info, sizeof(file_info));
        sock->send(boost::asio::buffer(buffer, sizeof(buffer)), 0);
        return;
    }

    //使用智能指针，防止程序出现异常时，fclose未被调用。
    boost::shared_ptr<FILE> file_ptr(fp, fclose);

    clock_t cost_time = clock();

    const size_t k_buffer_size = 32 * 1024;
    char buffer[k_buffer_size];
    File_info file_info;

    size_t filename_size  = strlen(filename) + 1;
    size_t file_info_size = sizeof(file_info);
    size_t total_size = file_info_size + filename_size;
    if (total_size > k_buffer_size) {
        std::cerr << "File name is too long";
        return;
    }
    file_info.filename_size = filename_size;

    fseek(fp, 0, SEEK_END);
    file_info.filesize = static_cast<unsigned long long>(ftell(fp)) ;
    rewind(fp);

    memcpy(buffer, &file_info, file_info_size);
    memcpy(buffer + file_info_size, filename, filename_size);


    std::cout << "Sending file : " << filename << "\n";
    size_t len = total_size;
    unsigned long long total_bytes_read = 0;
    while (true) {
        sock->send(boost::asio::buffer(buffer, len), 0);
        if (feof(fp)) break;
        len = fread(buffer, 1, k_buffer_size, fp);
        total_bytes_read += len;
    }

    cost_time = clock() - cost_time;
    if (cost_time == 0) cost_time = 1;

    double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / cost_time;
    std::cout << "cost time: " << cost_time / static_cast<double>(CLOCKS_PER_SEC)  << " s "
              << "  transferred_bytes: " << total_bytes_read << " bytes\n"
              << "speed: " <<  speed << " MB/s\n\n";

    return;
}
