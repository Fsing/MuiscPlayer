import QtQuick 2.0

Rectangle {
    property int index: 7
    color:"yellow"
    Text {
        anchors.centerIn: parent
        text: qsTr("我的歌手")
    }
}
