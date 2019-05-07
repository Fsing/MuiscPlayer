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
    //border.color: "#a82828"
    //border.color: "white"

    property int buttonWidth: 15
    property int buttonHeight: 15
    property double leftButtonOpacity : 0.5
    property double rightButtonOpacity : 0.5
    property double noHoverOpacity: 0.5
    property double hoverOpacity:1.0
    Rectangle{
        width: parent.width
        height: 1
        color: "black"
        opacity: 0.2
        anchors.top:parent.top
        radius: 3
    }
    Rectangle{
        width: parent.width
        height: 1
        color: "black"
        opacity: 0.2
        anchors.bottom: parent.bottom
        radius: 3
    }
    Rectangle{
        width: 1
        height: parent.height
        color: "black"
        opacity: 0.2
        anchors.left: parent.left
        radius: 3
    }
    Rectangle{
        width: 1
        height: parent.height
        color: "black"
        opacity: 0.2
        anchors.right: parent.right
        radius: 3
    }

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
            cursorShape:((leftButtonImage.opacity === 1.0) && (pressed||containsMouse))? Qt.PointingHandCursor: Qt.ArrowCursor
            onClicked: {
                back()
            }
        }

        background: Image {
            id:leftButtonImage
            anchors.fill: parent
            //opacity: leftButtonMouseArea.containsMouse ? noHoverOpacity : hoverOpacity
            //opacity: backStackView.length === 0 ? noHoverOpacity :  hoverOpacity
            opacity: leftButtonOpacity
            source: "qrc:/images/topArea/left.png"
        }


    }
    Rectangle {
        width: 1
        height: parent.height
        anchors.centerIn: parent
        color: "black"
        opacity: 0.2
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
            onClicked:{
                forward()
            }

        }
        background: Image {
            id:rightButtonImage
            mirror: true
            anchors.fill: parent
            //opacity: rightButtonMouseArea.containsMouse ? hoverOpacity : noHoverOpacity
            //opacity: forwardStackView.length === 0 ? noHoverOpacity : hoverOpacity
            opacity: rightButtonOpacity
            source: "qrc:/images/topArea/left.png"
        }
    }

}
