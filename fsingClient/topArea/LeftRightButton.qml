import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle {
    id: topLeftRight
    width: 50
    height: 20
    color: parent.color
    x:190
    anchors.verticalCenter: parent.verticalCenter
    radius: 3
    border.color: "#a82828"

    property int buttonWidth: 15
    property int buttonHeight: 15

    property double noHoverOpacity: 1.0
    property double hoverOpacity:0.5

    Button {
        anchors.left: parent.left
        anchors.leftMargin: 5
        width: buttonWidth
        height: buttonHeight
        anchors.verticalCenter: parent.verticalCenter
        MouseArea{
            id: leftButtonMouseArea;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: {

            }
        }

        background: Image {
            id:leftButtonImage
            anchors.fill: parent
            opacity: leftButtonMouseArea.containsMouse ? noHoverOpacity : hoverOpacity
            source: "qrc:/images/topArea/left.png"
        }


    }
    Rectangle {
        width: 1
        height: parent.height
        anchors.centerIn: parent
        color: parent.border.color
    }

    Button {
        anchors.right: parent.right
        anchors.rightMargin: 5
        width: buttonWidth
        height: buttonHeight
        anchors.verticalCenter: parent.verticalCenter

        MouseArea{
            id: rightButtonMouseArea;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked:{}

        }
        background: Image {
            mirror: true
            anchors.fill: parent
            opacity: rightButtonMouseArea.containsMouse ? noHoverOpacity : hoverOpacity
            source: "qrc:/images/topArea/left.png"
        }
    }

}
