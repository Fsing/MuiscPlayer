import QtQuick 2.0

Rectangle {
    border.width: 1
    signal clicked

    property alias source: icon.source

    Image {
        id: icon
        anchors.fill: parent
    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            clicked()
//        }
//    }
}
