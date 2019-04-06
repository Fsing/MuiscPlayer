import QtQuick 2.0

Rectangle {
    property int index: 0
    color:"red"
    Text {
        anchors.centerIn: parent
        text: qsTr("发现音乐")
    }
}
