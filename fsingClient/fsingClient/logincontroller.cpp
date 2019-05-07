#include "logincontroller.h"
#include <iostream>
#include <QDebug>

LoginController::LoginController()
{

}

LoginController::~LoginController()
{

}

QString LoginController::getFanUserName()
{
    return m_fan.userName();
}

QString LoginController::getFanIcon()
{
    return m_fan.icon();
}

QString LoginController::getFanId()
{
    return m_fan.userId();
}

QString LoginController::getFanLabel()
{
    return m_fan.label();
}

QString LoginController::getFanAddress()
{
    return m_fan.address();
}

void LoginController::createSongList(Json::Value resultRoot)
{
    std::string ret = resultRoot["recordSuccess"].asString();
    std::cout << "record create song list " << ret<< std::endl;
    if(ret == "SUCCESS"){
        QList<QString> list;
        list.append(QString::fromStdString(resultRoot["songListID"].asString()));
        list.append(QString::fromStdString(resultRoot["songListName"].asString()));
        list.append(QString::fromStdString(resultRoot["username"].asString()));
        list.append(QString::fromStdString(resultRoot["createTime"].asString()));
        list.append("");
        list.append("");
        list.append("");
        list.append("");
        list.append("");
        list.append("");

        m_fan.addCreatedSongList(QString::fromStdString(resultRoot["songListName"].asString()),list);
        //m_CreatedSongListCount++;
        //_songlistIDs.append(QString::fromStdString(resultRoot["songListID"].asString()));
        QString id = QString::fromStdString(resultRoot["songListID"].asString());
        std::cout << "songlistID:" << id.toStdString()  << std::endl;
        //_songlistNames.append(songlistName);
        //emit createdSongListCountChanged();
    }
}

//QList<QString> LoginController::getUserCreateSongList()
//{

//}

QList<QString> LoginController::getCreateSongNameLists()
{
    std::cout << "********************************************1" << std::endl;
    auto createSongLists = m_fan.createdSongLists();
    auto listNames = createSongLists.keys();
    auto values = createSongLists.values();
    QList<QString> createSongNames;
    std::cout << "********************************************2:" << listNames.count() << std::endl;
    for (int i = 0; i < listNames.count(); i++){
        createSongNames.append(listNames[i]);
        createSongNames.append(values[i][0]);
        std::cout << "********************************************" << std::endl;
        qDebug() <<values[i][0];
        qDebug() << createSongNames[i];
    }
    qDebug() << createSongNames.count();

    return createSongNames;
}

void LoginController::userLogout()
{
    m_fan.clear();
}

void LoginController::registerUser(Json::Value resultRoot)
{
    string ret = resultRoot["registerSuccess"].asString();
    m_result = QString::fromStdString(ret);
    std::cout << "register " << ret<<std::endl;
}

void LoginController::dealMessage(std::string type, Json::Value resultRoot)
{
    if (type == "LOGIN"){
        std::string ret = resultRoot["loginSuccess"].asString();
        m_result = QString::fromStdString(ret);
        std::cout << "login " << ret<< std::endl;
        if (ret == "SUCCESS"){
            m_fan.clear();
            //设置用户基本信息
            m_fan.setId(QString::fromStdString(resultRoot["id"].asString()));
            m_fan.setUserName(QString::fromStdString(resultRoot["userName"].asString()));
            m_fan.setPassword(QString::fromStdString(resultRoot["userPassword"].asString()));
            m_fan.setLabel(QString::fromStdString(resultRoot["userLabel"].asString()));
            m_fan.setSex(QString::fromStdString(resultRoot["userSex"].asString()));
            m_fan.setBirthday(QString::fromStdString(resultRoot["userBirthday"].asString()));
            m_fan.setAddress(QString::fromStdString(resultRoot["userAddress"].asString()));
            m_fan.setIcon(QString::fromStdString(resultRoot["userIcon"].asString()));

            //设置用户是否登录
            m_logining = true;
            std::cout << "loginController Result: " << m_logining << std::endl;

            //创建歌单信息
            const Json::Value arrayObj = resultRoot["array"];
            for (unsigned int i = 0; i < arrayObj.size(); i++){
                Json::Value value;
                value = arrayObj[i];

                //存储原创歌单名字
                QList<QString> ret;
                ret.append(QString::fromStdString(value["id"].asString()));
                ret.append(QString::fromStdString(value["name"].asString()));
                ret.append(QString::fromStdString(value["author"].asString()));
                ret.append(QString::fromStdString(value["createTime"].asString()));
                ret.append(QString::fromStdString(value["label"].asString()));
                ret.append(QString::fromStdString(value["info"].asString()));
                ret.append(QString::fromStdString(value["icon"].asString()));
                ret.append(QString::fromStdString(value["collectionQuantity"].asString()));
                ret.append(QString::fromStdString(value["clickQuantity"].asString()));
                ret.append(QString::fromStdString(value["shareQuantity"].asString()));

                m_fan.addCreatedSongList(QString::fromStdString(value["name"].asString()),ret);

                //收藏歌单信息
                const Json::Value arrayObj1 = resultRoot["collectedArray"];
                for (unsigned int i = 0; i < arrayObj1.size(); i++)
                {
                    Json::Value value;
                    value = arrayObj1[i];

                    QList<QString> ret;
                    ret.append(QString::fromStdString(value["id"].asString()));
                    ret.append(QString::fromStdString(value["name"].asString()));
                    ret.append(QString::fromStdString(value["author"].asString()));
                    ret.append(QString::fromStdString(value["createTime"].asString()));
                    ret.append(QString::fromStdString(value["label"].asString()));
                    ret.append(QString::fromStdString(value["info"].asString()));
                    ret.append(QString::fromStdString(value["icon"].asString()));
                    ret.append(QString::fromStdString(value["collectionQuantity"].asString()));
                    ret.append(QString::fromStdString(value["clickQuantity"].asString()));
                    ret.append(QString::fromStdString(value["shareQuantity"].asString()));

                    m_fan.addCollectedSongLists(QString::fromStdString(value["name"].asString()),ret);
                }
            }

            //关注用户信息
            const Json::Value arrayObj2 = resultRoot["attentedUsers"];
            for (unsigned int i = 0; i < arrayObj2.size(); i++)
            {
                Json::Value value;
                value = arrayObj2[i];

                QList<QString> ret;
                ret.append(QString::fromStdString(value["name"].asString()));
                ret.append(QString::fromStdString(value["password"].asString()));
                ret.append(QString::fromStdString(value["label"].asString()));
                ret.append(QString::fromStdString(value["sex"].asString()));
                ret.append(QString::fromStdString(value["birthday"].asString()));
                ret.append(QString::fromStdString(value["address"].asString()));
                ret.append(QString::fromStdString(value["icon"].asString()));

                m_fan.addAttentedUsers(QString::fromStdString(value["name"].asString()),ret);

            }

            //粉丝信息
            const Json::Value arrayObj3 = resultRoot["fanUsers"];
            for (unsigned int i = 0; i < arrayObj3.size(); i++)
            {
                Json::Value value;
                value = arrayObj3[i];

                QList<QString> ret;
                ret.append(QString::fromStdString(value["name"].asString()));
                ret.append(QString::fromStdString(value["password"].asString()));
                ret.append(QString::fromStdString(value["label"].asString()));
                ret.append(QString::fromStdString(value["sex"].asString()));
                ret.append(QString::fromStdString(value["birthday"].asString()));
                ret.append(QString::fromStdString(value["address"].asString()));
                ret.append(QString::fromStdString(value["icon"].asString()));

                m_fan.addFanUsers(QString::fromStdString(value["name"].asString()),ret);

            }
        }
    } else if(type == "REGISTER") {
        registerUser(resultRoot);
    } else if (type == "CREATESONGLIST"){
        createSongList(resultRoot);
    }
}

bool LoginController::getLogining()
{
    return m_logining;
}

QString LoginController::getResult()
{
    return m_result;
}

void LoginController::setResult(const QString &result)
{
    m_result = result;
}

void LoginController::setLogining(bool logining)
{
    m_logining = logining;
}



