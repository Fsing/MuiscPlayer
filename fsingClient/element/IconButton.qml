import QtQuick 2.0

Rectangle {
    id:playAll
    width: 100
    height: 25
    radius: 5
    border.width: 1
    border.color: "#e0e0e0"
    smooth: true
    color: playMouseArea.containsMouse ?"#f5f5f7" : "white"

    property string iconSource
    property double iconScale : 1
    property string buttonText
    signal clicked()

    Rectangle{
        id:playImage
        x:10
        width: playAll.height
        height: playAll.height
        color: "#00000000"
        Image {
            anchors.fill: playImage
            anchors.verticalCenter: parent.verticalCenter
            source: iconSource
            smooth: true
            scale: iconScale
        }
    }
    Text{
        anchors.left: playImage.right
        anchors.leftMargin: 2
        text:buttonText
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea{
        id:playMouseArea
        anchors.fill: playAll
        hoverEnabled: true
        onClicked: {
            clicked()
        }
    }
}
