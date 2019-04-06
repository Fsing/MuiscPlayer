import QtQuick 2.0

Rectangle {
    property int index: 4
    color:"pink"
    Text {
        anchors.centerIn: parent
        text: qsTr("本地音乐")
    }
}
