import QtQuick 2.0

Rectangle{
    id:personalInformation
    width: parent.width
    height: parent.height
//    width: 700
//    height: 500

    UserBaseInfo{
        id:userBaseInfo
        width: parent.width - 40
        height: parent.height * 0.4
        anchors{
            top:parent.top
            topMargin: 20
            left: parent.left
            leftMargin: 40
        }
    }

    //分割线
    Rectangle{
        width: parent.width + 10
        height: 30
        border.width: 1
        border.color: "#dcdcdc"
        anchors{
            top:userBaseInfo.bottom
            left: parent.left
        }
        Text {
            text: qsTr("创建的歌单")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
    }
}
