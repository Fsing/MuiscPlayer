#ifndef FSINGCLINET_H
#define FSINGCLINET_H

#include <QObject>
#include <memory>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class AttenUserController;
class CollectController;
class DownloadMusicController;
class ListenMusicController;
class LoginController;
class SearchController;

struct File_info {
    typedef unsigned long long Size_type;
    Size_type filesize;
    size_t filename_size;
    File_info() : filesize(0), filename_size(0) {}
};

class FSingClient:public QObject
{
    Q_OBJECT
public:
    FSingClient();
    ~FSingClient(){}

public:
    //获取本地音乐信息
    Q_INVOKABLE QList<QObject *> getLocalSongInfo(QList<QString> dirList);
    //检测是否已经登录
    Q_INVOKABLE bool checkLogin();
    //获取用户名字信息
    Q_INVOKABLE QString getUserName();
    Q_INVOKABLE QString getUserIcon();

    //获取用户创建歌单的名字集合 huang
    Q_INVOKABLE QList<QString> createSongNameLists();
    //获取推荐歌单名字集合
    Q_INVOKABLE QList<QString> getRecommendSongListNames();
    //获取推荐歌单图片集合
    Q_INVOKABLE QList<QString> getRecommendSongListIcons();
    //获取推荐歌单Id集合
    Q_INVOKABLE QList<QString> getRecommendSongListIds();

    //获取推荐歌单基本信息
    Q_INVOKABLE QList<QString> getRecSongListBasicInfo(QString recSongListId);
    //获取歌单歌曲列表
    Q_INVOKABLE QList<QString> getSongListSongs(QString songListId);

    //获取歌词
    Q_INVOKABLE QList<QObject*> getLyric(QString filePath);

    //获取歌单信息
    //Q_INVOKABLE QList<QString> getSongListInfo(QString songListId);

    //缓存区
    Q_INVOKABLE void songList(QString songListId);

    //获取歌单信息 huang
    Q_INVOKABLE QString getSongInformation(QString songId);


public:

    Q_INVOKABLE void connect_server();
    //请求文件
    Q_INVOKABLE void fileTransfer(QString fileName);
    //filetransfer
    //接收文件
    void fileReceiver();
    //传文件调用函数
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void receive_file_content(std::string fileName);
    void handle_file(const boost::system::error_code& error);
    void handle_header(const boost::system::error_code& error);

    //登录账户,服务器数据库查找用户信息
    Q_INVOKABLE void login(QString userName, QString userPassword);
    //退出账户
    Q_INVOKABLE void logout();

    //获取推荐歌单Lists huang
    void getRecommendSongLists();

    //获取歌单评论信息
    void getSongListComment();

    //获取歌曲评论信息
    void getSongComment();

    //获取歌单信息


    //直接将通过参数传入的封装好的json字符串传送给服务器。参数string由用况controller里的各个函数封装
    void sendStreamMediaRequest(std::string string);
    //直接将通过参数传入的封装好的json字符串传送给服务器。参数string由用况controller里的各个函数封装
    void sendServerMessage(boost::system::error_code ec,std::string string);


    //接收消息，并将收到的字符串转换为json对象存储，作为参数传送给各个用况controller的dealMessage()函数处理
    /*例登录请求login()--LoginController：
     * void login(){
     *      //封装需要传送的字符串strr
     *      //传送消息：sendServerMessage(strr)
     *      std::string receiveString;
     *      //接收消息:receiveMessage(receiveString);
     *      Json::Reader reader;
     *      Json::Value resultRoot;
     *      reader.parse(receiveString.data(),resultRoot);
     *      //处理消息，调用相应LoginController的dealMessage()处理消息
     *      dealMessage(resultRoot["type"].asString(),resultRoot);//将查询到的相应的用户信息存储起来
     */
    //void receiveMessage(boost::system::error_code ec,std::string &&string);
    void receiveMessage(boost::system::error_code ec);

     Q_INVOKABLE QString getLoginControllerResult();
     Q_INVOKABLE void setLoginingStatus(bool res);

signals:
    void loginConcrollerResultChanged();

private:
    std::shared_ptr<LoginController> _loginController;
    std::shared_ptr<ListenMusicController> _listenMusicController;
    std::shared_ptr<DownloadMusicController> _downloadMusicController;
    //结果信息
    QString m_loginConcrollerResult;

    //for file transfer
    clock_t clock_;
    FILE *fp_;
    File_info file_info_;
    File_info::Size_type total_bytes_writen_;
    static const unsigned k_buffer_size = 1024 * 32;
    char buffer_[k_buffer_size];
};


#endif // FSINGCLINET_H
