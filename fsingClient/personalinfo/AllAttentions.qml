import QtQuick 2.0
import "./element"

Rectangle {
    anchors.fill: parent

    property alias attenedUsersModel: attentionsUserModel

    Grid{
        columns: 3
        spacing: 20
        anchors{
            top:parent.top
            topMargin:20
            left:parent.left
            leftMargin: 10
        }
        Repeater{
            model:attentionsUserModel
            delegate:UserInfoOverView{
            }
        }
    }

    ListModel{
        id:attentionsUserModel
    }
}
