import QtQuick 2.0

Rectangle {
    id: imageButton
    //    border.color: "#CCCCCC"
    //    border.width: 0.5
    width: 100
    height: 100
    color: "white"
    opacity: 0.8

    property alias source: image.source
    property alias text: t.text

    Image {
        id: image
        width: parent.width
        height: parent.height - t.height
    }
    Text {
        id: t
        text: "QQ"
        anchors.top: image.bottom
        anchors.left: image.left
        anchors.leftMargin: image.width * 0.4
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            imageButton.opacity = 1
        }
        onExited: {
            imageButton.opacity = 0.8
        }
    }
}
