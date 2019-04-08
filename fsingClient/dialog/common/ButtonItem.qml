import QtQuick 2.0

Rectangle {
    id: buttonItem
    width: 280
    height: 30

    property var usource
    property var utext
    property bool endImageVisible: true

    signal buttonClick

    Image {
        id: image
        width: 20
        height: 20
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        source: usource
    }
    Text {
        id: ntext
        anchors.left: image.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        color: "#333333"
        opacity: 0.55
        font.pixelSize: 15
        text: utext
    }

    Image {
        width: 12
        height: 8
        visible: endImageVisible
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.5
        source: "qrc:/images/common/right_arrow.png"
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            buttonItem.color = "#f3f2f2"
        }
        onExited: {
            buttonItem.color = "white"
        }
        onClicked: {
            buttonClick()
        }
    }
}
