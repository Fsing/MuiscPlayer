import QtQuick 2.0

Rectangle {
    border.width: 1
    border.color: "#e0e0e0"
    signal clicked

    property alias source: icon.source

    Image {
        id: icon
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            clicked()
//        }
//    }
}
