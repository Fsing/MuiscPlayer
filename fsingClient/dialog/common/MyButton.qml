import QtQuick 2.0

Rectangle {
    id: button
    border.color: "#CCCCCC"
    border.width: 1
    color: buttonColor
    radius: 6
    opacity: 0.7

    property string textColor: "#333333"
    property string buttonColor: "white"
    property alias text: t.text
    property alias radius: button.radius
    signal buttonClicked

    Text {
        id: t
        color: textColor
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            buttonClicked()
        }
        onEntered: {
            button.opacity = 1
        }
        onExited: {
            button.opacity = 0.7
        }
    }
}
