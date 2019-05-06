#include "fan.h"

Fan::Fan(QString name, QString password, QString label, QString sex, QString birthday, QString address, QString icon):m_name{name},m_password{password},m_label{label},m_sex{sex},m_birthday{birthday},m_address{address},m_icon{icon}
{

}

int Fan::attentionUserCount() const
{
    return _attentedUsers.count();
}

int Fan::fanUserCount() const
{
    return _fanUsers.count();
}

int Fan::createdSongListCount() const
{
    return _createdSongList.count();
}

int Fan::collectedSongListCount() const
{
    return _collectedSongList.count();
}

void Fan::clear()
{
    m_name = "";
    m_password = "";
    m_label = "";
    m_sex = "";
    m_birthday = "";
    m_address = "";
    m_icon = "";
    _collectedSongList.clear();
    _createdSongList.clear();
    _attentedUsers.clear();
    _fanUsers.clear();
}

QString Fan::userId()
{
    return m_id;
}

//getting
QMap<QString,QList<QString>> Fan::createdSongLists()
{
    std::cout << "Fan::createdSongLists(): " << _createdSongList.count() << std::endl;
    return _createdSongList;
}
QMap<QString,QList<QString>> Fan::collectedSongLists()
{
    return _collectedSongList;
}

QMap<QString,QList<QString>> Fan::attentedUsers()
{
    return _attentedUsers;
}

QMap<QString,QList<QString>>Fan::fanUsers()
{
    return _fanUsers;
}

void Fan::setId(const QString &id)
{
    m_id = id;
}

QString Fan::userName(){
    return m_name;
}

QString Fan::password(){
    return m_password;
}

QString Fan::label(){
    return m_label;
}

QString Fan::sex(){
    return m_sex;
}

QString Fan::birthday(){
    return m_birthday;
}

QString Fan::address(){
    return m_address;
}

QString Fan::icon(){
    return m_icon;
}


//setting
void Fan::setUserName(QString username){
    m_name= username;
    emit usernameChanged();
}

void Fan::setPassword(QString password){
    m_password = password;
    emit passwordChanged();
}

void Fan::setLabel(QString label){
    m_label = label;
    emit labelChanged();
}

void Fan::setSex(QString sex){
    m_sex = sex;
    emit sexChanged();
}

void Fan::setBirthday(QString birthday){
    m_birthday = birthday;
    emit birthdayChanged();
}

void Fan::setAddress(QString address){
    m_address = address;
    emit addressChanged();
}

void Fan::setIcon(QString icon){
    m_icon = icon;
    emit iconChanged();
}

void Fan::addCreatedSongList(QString key, QList<QString> s)
{
    _createdSongList.insert(key,s);
    std::cout << _createdSongList.count()<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" <<std::endl;
}

QMap<QString, QList<QString> > Fan::createdSongList() const
{
    return _createdSongList;
}
