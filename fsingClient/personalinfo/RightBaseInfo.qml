import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "../dialog/common"
import "./element"

Item {

    property alias attentions: attention.number     //关注用户数量
    property alias fans: fan.number                 //粉丝数量
    property alias personalInfo: info.contentText   //用户简介
    property alias address: address.contentText     //用户地址
    property alias userName: username.text          //用户名

    signal editInformationClicked
    signal attentionsClicked
    signal fansClicked

    ColumnLayout{
        id:first
        width: parent.width
        height: parent.height * 0.2
        spacing: 20
        Row{
            id:name
            spacing: parent.width * 0.4
            Text{
                id:username
//                text:"那一份情，那么重"
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            MyButton{
                width:100
                height: 20
                text:"编辑个人信息"
                onButtonClicked:editInformationClicked()
            }
        }
        Row{
            id:fans
            spacing: 20
            NumberText{
                number:"0"
                text:"动态"
            }
            NumberText{
                id:attention
                number:"0"
                text:"关注"
                onNumberTextClicked: attentionsClicked()
            }
            NumberText{
                id:fan
                number:"0"
                text:"粉丝"
                onNumberTextClicked: fansClicked()
            }
        }
    }
    ColumnLayout{
        anchors.top: first.bottom
        anchors.topMargin: 70
        width: parent.width
        height: parent.height * 0.2
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


















