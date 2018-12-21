import QtQuick 2.0

Rectangle {
    width: 250
    height: 250
    border.width: 1
    signal clicked

    Image {
        id: icon
        anchors.fill: parent
        source: songlist.listImg
        fillMode: Image.PreserveAspectCrop
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            clicked()
        }
    }
}
