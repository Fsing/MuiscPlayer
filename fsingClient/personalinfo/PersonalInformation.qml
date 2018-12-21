import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "../middleArea/RightAreaComponents"

Rectangle{
    id:personalInformation
    width: parent.width
    height: parent.height
    //    width: 700
    //    height: 500

    property int createdSongListNumber
    property string collectedSongListNumber
    property alias attentions: userBaseInfo.attentions
    property alias fans: userBaseInfo.fans
    property alias address: userBaseInfo.address
    property alias personalInfo: userBaseInfo.personalInfo
    property alias userName: userBaseInfo.userName
    property alias userIcon: userBaseInfo.userIcon

    property alias songlistModel: personalCreatedSongLists.songlistModel
    property alias songlistModel1:personalCollectedSongLists.songlistModel

    onCreatedSongListNumberChanged: console.log(createdSongListNumber)
    onCollectedSongListNumberChanged: console.log(collectedSongListNumber)

    ScrollView {
        id: leftItem
        anchors.fill: parent
        clip: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        Column{
            anchors{
                top:parent.top
                topMargin: 20
                left: parent.left
                leftMargin: 20
            }
            spacing: 20
            UserBaseInfo{
                id:userBaseInfo
                width: personalInformation.width - 40
                height: personalInformation.height * 0.4

                //                //点击查看粉丝
                //                onFansUserClicked:
                //                {
                //                }
                //                //点击查看关注用户
                onAttentionUserClicked: {
                    //用户信息界面插入关注用户信息
                    middleArea.attentedUserModel.clear()
                    var i = 0
                    while(client.attentedUsers()[i]){
                        middleArea.attentedUserModel.append({
                                                                usernametext:client.attentedUsers()[i],
                                                                loginButtonSource:"file:///" + applicationDirPath + "/" + client.attentedUsers()[++i],
                                                            })
                        i++;
                    }
                    middleArea.allAttentions.visible = true
                }
                onFansUserClicked: {
                    //用户信息界面插入粉丝用户信息
                    middleArea.attentedUserModel.clear()
                    var i=0
                    while(client.fanUsers()[i]){
                        middleArea.attentedUserModel.append({
                                                                usernametext:client.fanUsers()[i],
                                                                loginButtonSource:"file:///" + applicationDirPath + "/" + client.fanUsers()[++i],
                                                            })
                        i++;
                    }
                    middleArea.allAttentions.visible = true
                }

            }

            //分割线
            Rectangle{
                id:fengexian1
                width: personalInformation.width + 10
                height: 30
                border.width: 1
                border.color: "#dcdcdc"
                Text {
                    text: qsTr("创建的歌单( " + createdSongListNumber+" )")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                }
            }
            PersonalCreatedSongLists{
                id:personalCreatedSongLists
                width: personalInformation.width
                height:200
            }
            //            Grid{
            //                columns: 4
            //                width: personalInformation.width
            //                height:200
            //                spacing: 10
            //                Repeater{
            //                    delegate: SongListRectangle{
            //                        playQuantity: String(50)
            //                        source: "file:///" + applicationDirPath + "/" + client.userIcon()
            //                        songlistId: "interfaceParamter[0]"
            //                        songlistName: "interfaceParamter[1]"
            //                    }
            //                }
            //            }
            //分割线
            Rectangle{
                id:fengexian2
                width: personalInformation.width + 10
                height: 30
                border.width: 1
                border.color: "#dcdcdc"
                Text {
                    text: qsTr("收藏的歌单( " + collectedSongListNumber+" )")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                }
            }
            PersonalCollectedSongLists{
                id:personalCollectedSongLists
                width: personalInformation.width
                height:600
            }
        }
    }

}
