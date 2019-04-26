#include "fsingclient.h"
#include "fsingcontroller.h"
#include "logincontroller.h"
#include "listenmusiccontroller.h"
#include <iostream>
#include <boost/thread.hpp>
#include "json/json.h"
#include <QDebug>

using std::endl;
using std::cout;
using namespace boost::asio;
using boost::system::error_code;
using boost::asio::ip::address;
using boost::asio::io_service;

io_service service;
ip::tcp::endpoint ep(address::from_string("127.0.0.1"),2001);
//客户端异步连接，有多个套接字，每次发送信息、接受信息都重新分配一个套接字，并且分配一个线程独立进行
ip::tcp::socket sock(service);
ip::tcp::socket sock_fileTransfer(service);

FSingClient::FSingClient()
{
    connect_server();
    try{
    _loginController = std::make_shared<LoginController>();
    }catch(...){
        std::cout << "_loginController error!" <<std::endl;
    }
}

void FSingClient::connect_server()
{
    boost::system::error_code e;
    sock.async_connect(ep,[](const error_code &e){
        if(e){
            cout << e.message() << endl;
            return;
        }
    });

    service.run();
}

void FSingClient::fileTransfer(QString fileName)
{
    auto filename = fileName.toStdString().data();
    FILE *fp = fopen(filename, "rb");
    if (fp != NULL) {
        std::cout << "find previous file" <<fileName.toStdString()<<std::endl;
        return;
    }

    Json::Value root;
    root["type"] = "FILETRANSFER";
    root["fileName"] = fileName.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();
    auto s = out.data();

    boost::system::error_code ec;
    sock_fileTransfer.write_some(buffer(s,strlen(s)),ec);
    std::cout<<"send message to server: " <<out<<std::endl;
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }

    fileReceiver();
    std::cout << "complete" << std::endl;
}

void FSingClient::fileReceiver()
{
    sock_fileTransfer.receive(buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)));
    if(file_info_.filename_size == 0){
        std::cout<<"file is not exist"<<std::endl;
        return;
    }
    boost::system::error_code error;
    handle_header(error);
}

void FSingClient::handle_write(const boost::system::error_code &error, size_t bytes_transferred)
{

}

void FSingClient::receive_file_content(std::string fileName)
{
    boost::system::error_code error;
    size_t bytes_transferred = 0;
    total_bytes_writen_ = 0;

    while(total_bytes_writen_ != file_info_.filesize){
        bytes_transferred = sock_fileTransfer.receive(buffer(buffer_, k_buffer_size));
        //bytes_transferred = strlen(buffer_);
        if (error) {
            if (error != error::eof)
                return;
            File_info::Size_type filesize = file_info_.filesize;
            if (total_bytes_writen_ != filesize)
                std::cerr <<  "Filesize not matched! " << total_bytes_writen_
                           << "/" << filesize << "\n";
            return;
        }
        total_bytes_writen_ += fwrite(buffer_, 1, bytes_transferred, fp_);
    }

    fclose(fp_);
    std::cout << "transfer successful " << fileName<<std::endl;
}

void FSingClient::handle_file(const boost::system::error_code &error)
{
    if (error) {
        std::cout << boost::system::system_error(error).what() << std::endl;
    };
    const char *basename = buffer_ + file_info_.filename_size - 1;
    while (basename >= buffer_ && (*basename != '\\' && *basename != '/')) --basename;
    ++basename;

    fp_ = fopen(basename, "wb");
    if (fp_ == NULL) {
        std::cerr << "Failed to open file to write\n";
        return;
    }
    string fileName = basename;
    receive_file_content(fileName);
}

void FSingClient::handle_header(const boost::system::error_code &error)
{
    if (error) {
        std::cout << boost::system::system_error(error).what() << std::endl;
    };
    size_t filename_size = file_info_.filename_size;
    if (filename_size > k_buffer_size) {
        std::cerr << "Path name is too long!\n";
        return;
    }
    //得用async_read, 不能用async_read_some，防止路径名超长时，一次接收不完
    read(sock_fileTransfer, buffer(buffer_, file_info_.filename_size));
    handle_file(error);
}

QList<QObject *> FSingClient::getLocalSongInfo(QList<QString> dirList)
{
    //ListenMusicController listenMusicController;
    if (_listenMusicController == nullptr)
        throw "空指针";
    return _listenMusicController->getLocalSongInfo(dirList);
}

bool FSingClient::checkLogin()
{
    if (_loginController == nullptr)
        throw "空指针";
    return _loginController->getLogining();
}

QString FSingClient::getUserName()
{
    if (_loginController == nullptr)
        throw "空指针";
    return _loginController->getFanUserName();
}

QString FSingClient::getUserIcon()
{
    QString icon;
    try{
    icon = _loginController->getFanIcon();
    //socket_fileTransfer请求传送用户头像
    cout << "请求头像： " << icon.toStdString() << endl;
    if(icon.toStdString() != "")
        fileTransfer(icon);
    }catch(...){
        throw ("用户头像传输失败！");
    }

    return icon;
}

QList<QString> FSingClient::createSongNameLists()
{
    return _loginController->getCreateSongNameLists();
}

void FSingClient::login(QString userName, QString userPassword)
{
    try{
    Json::Value root;
    root["type"] = "LOGIN";
    root["userName"] = userName.toStdString();
    root["userPassword"] = userPassword.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();
    boost::system::error_code ec;
    sendServerMessage(ec,out);

    receiveMessage(ec,std::move(out));
    } catch(...){
        std::cout << "login error" << std::endl;
    }
}

void FSingClient::sendServerMessage(boost::system::error_code ec,std::string string)
{
    auto s = string.data();

    //传输到服务器
    sock.write_some(buffer(s, strlen(s)), ec);
    if (ec){
        std::cout << "sendServerMessage Error!" << std::endl;
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }
}

void FSingClient::receiveMessage(boost::system::error_code ec, std::string &&string)
{
    //接受服务器返回的用户信息：基本信息、用户粉丝、关注、收藏歌单、创建歌单
    char dataSize[10];
    memset(dataSize,0,sizeof(char)*10);//reset 0 to data[]
    while(strlen(dataSize) == 0)
        sock.read_some(buffer(dataSize,sizeof(char)*10),ec);
    //cout << dataSize <<endl;

    char data[2048];
    memset(data,0,sizeof(char)*2048);//reset 0 to data[]

    std::string receiveData;
    while(receiveData.length() < atoi(dataSize)){
        sock.read_some(buffer(data),ec);
        receiveData.append(data,0,sizeof(data));
        memset(data,0,sizeof(char)*2048);
    }

    if(ec)
    {
        std::cout << "receiveMessage Error!" << std::endl;
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }

    Json::Reader reader;
    Json::Value resultRoot;
    if (!reader.parse(receiveData.data(), resultRoot)){
        std::cout << "json received faild" << std::endl;
        return;
    } else {
        std::string type = resultRoot["type"].asString();
        if (type == "LOGIN"){
            std::shared_ptr<FSingController> fsingController = _loginController;
            //boost::thread(boost::bind(&FSingController::dealMessage,&fsingController,type, resultRoot));
            fsingController->dealMessage(type, resultRoot);


            //_loginController->dealMessage(type, resultRoot);
        }
    }
}

QString FSingClient::getLoginConcrollerResult()
{
    m_loginConcrollerResult = _loginController->getResult();
    return m_loginConcrollerResult;
}

