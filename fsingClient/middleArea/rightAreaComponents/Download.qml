import QtQuick 2.0

Rectangle {
    property int index: 5
    color:"blue"
    Text {
        anchors.centerIn: parent
        text: qsTr("下载管理")
    }
}
