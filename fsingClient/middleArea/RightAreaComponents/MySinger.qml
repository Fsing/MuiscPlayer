import QtQuick 2.0

Rectangle {
    property int index: 7
    color: "#117722"
    Text {
        width: 100
        height: 20
        anchors.centerIn: parent
        text: qsTr("我的歌手")
    }
}
