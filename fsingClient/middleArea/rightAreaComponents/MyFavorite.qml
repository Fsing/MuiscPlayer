import QtQuick 2.0

Rectangle {
    property int index: 9
    color:"lightblue"
    Text {
        anchors.centerIn: parent
        text: qsTr("我喜欢的")
    }
}
