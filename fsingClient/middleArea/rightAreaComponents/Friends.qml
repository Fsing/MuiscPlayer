import QtQuick 2.0

Rectangle {
    property int index: 3
    color:"green"
    Text {
        anchors.centerIn: parent
        text: qsTr("朋友")
    }
}
