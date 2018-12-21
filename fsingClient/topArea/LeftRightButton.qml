import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle {
    id: rectangle1
    width: 50
    height: 20
    color: parent.color
    x:192
    anchors.verticalCenter: parent.verticalCenter
    radius: 3
    border.color: "#a82828"

    Button {
        anchors.left: parent.left
        anchors.leftMargin: 5
        width: 15
        height: 15
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
            opacity: leftButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/left.png"
        }


    }
    Rectangle {
        width: 1
        height: parent.height
        anchors.centerIn: parent
        color: "#a82828"
    }

    Button {
        anchors.right: parent.right
        anchors.rightMargin: 5
        width: 15
        height: 15
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
            opacity: rightButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/left.png"
        }
    }

}
