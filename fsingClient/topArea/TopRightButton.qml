import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

import "../element"

Rectangle {
    id: topright
    width: 300
    height: parent.height
    anchors.right: parent.right
    anchors.rightMargin: 5
    color: parent.color


    property int buttonWidth: 18
    property int buttonHeight: 18

    property int userImageWidth: 25
    property int userImageHeight: 25

    property double noHoverOpacity: 0.7
    property double hoverOpacity:1.0

    property string fanName: "未登录"
    property string loginButtonSource: "qrc:/images/common/ac0.png"

    signal loginButtonClicked()
    signal skinButtonClicked()

    Button {
        id: closebutton
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        width: buttonWidth
        height: buttonHeight
        MouseArea {
            id: closeButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: Qt.quit()
        }

        background: Image {
            id: leftButtonImage
            anchors.fill: parent
            opacity: closeButtonMouseArea.containsMouse ? hoverOpacity :noHoverOpacity
            source: "qrc:/images/topArea/close.png"
        }
    }
    Button {
        id: maxbutton
        anchors.right: closebutton.left
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: buttonWidth
        height: buttonHeight
        MouseArea {
            id: maxButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if (mainWindow.visibility === Window.FullScreen) {
                    mainWindow.width = 1025
                    mainWindow.height = 670
                    mainWindow.setX(xPosition)
                    mainWindow.setY(yPosition)
                    mainWindow.showNormal()
                } else {
                    xPosition = mainWindow.x
                    yPosition = mainWindow.y
                    mainWindow.visibility = Window.FullScreen
                }
            }
        }

        background: Rectangle {
            id: maxButton
            anchors.centerIn: parent
            width: 13
            height: 11
            border.width: 1
            //border.color: maxButtonMouseArea.containsMouse ? "#DCDCDC" : "#E29595"
            border.color: "white"
            opacity: maxButtonMouseArea.containsMouse ? 0.8:0.5
            color: topright.color
            radius: 2
        }
    }
    Button {
        id: minbutton
        anchors.right: maxbutton.left
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: buttonWidth
        height: buttonHeight
        MouseArea {
            id: minButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: mainWindow.visibility = Window.Minimized
        }

        background: Image {
            id: minButtonImage
            anchors.fill: parent
            opacity: minButtonMouseArea.containsMouse ? hoverOpacity :noHoverOpacity
            source: "qrc:/images/topArea/mini.png"
        }
    }
    Rectangle {
        id: rec
        width: 1
        height: buttonHeight
        anchors.right: minbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        color: "black"

        opacity: 0.2
    }
    Button {
        id: settingbutton
        anchors.right: rec.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: buttonWidth
        height: buttonHeight
        MouseArea {
            id: settingbuttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id: settingbuttonImage
            anchors.fill: parent
            opacity: settingbuttonMouseArea.containsMouse ? hoverOpacity : noHoverOpacity
            source: "qrc:/images/topArea/setting1.png"
        }
    }
    Button {
        id: emailbutton
        anchors.right: settingbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: buttonWidth
        height: buttonHeight
        MouseArea {
            id: emailbuttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
               // client.onlineSongLists()
            }
        }

        background: Image {
            id: emailbuttonImage
            anchors.fill: parent
            opacity: emailbuttonMouseArea.containsMouse ? hoverOpacity :noHoverOpacity
            source: "qrc:/images/topArea/message.png"
        }
    }
    Button {
        id: skinbutton
        anchors.right: emailbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: buttonWidth
        height: buttonHeight
        MouseArea {
            id: skinbuttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                skinButtonClicked()
            }
        }

        background: Image {
            id: skinbuttonImage
            anchors.fill: parent
            opacity: skinbuttonMouseArea.containsMouse ? hoverOpacity :noHoverOpacity
            source: "qrc:/images/topArea/skin.png"
        }
    }

    Rectangle {
        id: loginButton
        anchors.right: skinbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.5
        width: 50
        height: buttonHeight
        color: topright.color
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
            onEntered: {
                loginButton.opacity = hoverOpacity
            }
            onExited: {
                loginButton.opacity = noHoverOpacity
            }
            onClicked: {
                loginButtonClicked()
            }
        }
        Text {
            id: name
            anchors.right: userlabel.left
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            width: 40
            height: 16
            color: "#ffffff"
            text: fanName
        }
        Image {
            id: userlabel
            width: 5
            height: 10
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: loginButton.right
            anchors.rightMargin: 2
            rotation: 90
            source: "qrc:/images/common/right_arrow.png"
        }
    }

    Button {
        id: userImageButton
        anchors.right: loginButton.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        width: 25
        height: 25
        opacity: 1.0

        onClicked: {
            console.log("userImageClick")
        }

        background: CircleIcon {
            id: loginbuttonImage
            anchors.fill: parent
            opacity: hoverOpacity
            userImage: loginButtonSource
        }
    }
}
