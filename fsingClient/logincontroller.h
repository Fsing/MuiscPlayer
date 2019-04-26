#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "fan.h"
#include "fsingcontroller.h"

class LoginController : public FSingController
{   
    Q_OBJECT
public:
    LoginController();
    ~LoginController() override;

    QString getFanUserName();
    QString getFanIcon();
    QList<QString> getCreateSongNameLists();

    //判断服务端返回的消息的类型,并调用相应的处理函数,纯虚函数，各个用况的controller继承实现，动态绑定
    virtual void dealMessage(std::string type,Json::Value resultRoot) override;

    bool getLogining();
    //void setLogining(bool logining);

    QString getResult();
    //void setResult(const QString &result);

signals:
    void loginingChanged();

private:
    //消息处理结果
    QString m_result;

    bool m_logining = false;
    //用户信息
    Fan m_fan;
};

#endif // LOGINCONTROLLER_H
