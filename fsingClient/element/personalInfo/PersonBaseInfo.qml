import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "../../element/personalInfo"

Item {
    id:personBaseInfoView
    width: parent.width
    //width: 800
    height: 280
//    property alias attentions: attention.number
//    property alias fans: fan.number
    property alias icon: userIcon.source
    property alias name: userName.text
    property alias personalInfo: info.contentText
    property alias address: address.contentText

//    signal attentionClicked
//    signal cancelAttentionClicked

    Row{
        x:30
        y:20
        spacing: 30
        UserIcon{
            id:userIcon
            width: 200
            height: 200
        }

        ColumnLayout{
            id:first
            x:50
            //spacing: 20
//            Row{
//                id:name
                //spacing: parent.width * 0.4
                Text{
                    id:userName
                    text:""
                    font.pixelSize: 20
                    color: "#333333"
                    //anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle{
                    width: personBaseInfoView.width - userIcon.width -50
                    height: 1
                    color: "#e0e0e0"
                }

                Row{
                    id:fans
                    spacing: 20
                    NumberText{
                        number:"0"
                        text:"动态"
                    }
                    Rectangle{
                        width: 1
                        height: fans.height
                        color: "#e0e0e0"
                    }

                    NumberText{
                        id:attention
                        number:"0"
                        text:"关注"
                    }
                    Rectangle{
                        width: 1
                        height: fans.height
                        color: "#e0e0e0"
                    }
                    NumberText{
                        id:fan
                        number:"0"
                        text:"粉丝"
                    }
                }
//            }
            ColumnLayout{
                anchors.top: first.bottom
                //anchors.topMargin: 30
//                width: parent.width
//                height: parent.height * 0.2
                spacing: 10
                TextText{
                    id:info
                    titleText: "个人介绍："
                    contentText: "暂无介绍"
                }
                TextText{
                    id:address
                    titleText: "所在地区"
                    contentText: "暂无信息"

                }
            }
        }
    }
}


















