#ifndef FSINGCLINET_H
#define FSINGCLINET_H

#include <QObject>

class FSingClient:public QObject
{
    Q_OBJECT
public:
    FSingClient();
    ~FSingClient(){}

    Q_INVOKABLE void connect_server();

    //直接将通过参数传入的封装好的json字符串传送给服务器。参数string由用况controller里的各个函数封装
    void sendStreamMediaRequest(std::string string);
    //直接将通过参数传入的封装好的json字符串传送给服务器。参数string由用况controller里的各个函数封装
    void sendServerMessage(std::string string);


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
    void receiveMessage(std::string &&string);
    bool checkLogin();      //检测是否已经登录

    Q_INVOKABLE QList<QObject *> getLocalSongInfo(QList<QString> dirList);
};

#endif // FSINGCLINET_H
