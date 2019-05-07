import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2

Item {
    //anchors.verticalCenter: parent.verticalCenter
    //anchors.centerIn: parent
    property bool isLike:false
    property string firstSource: firstButtonImage.source
    property string secondSource: secondButtonImage.source
    signal buttonClick
    Button {
        id: firstButton
        anchors.top: parent.top
        MouseArea {
            id: firstButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
            onClicked: {
                console.log("like")
                buttonClick()
                if (isLike){
                    isLike = false
                }else{
                    isLike = true
                }
            }
        }

        background: Image {
            id: firstButtonImage
            //anchors.fill: parent
            //anchors.centerIn: parent
            anchors.bottom: firstButton.bottom
            anchors.bottomMargin: -4
            fillMode: Image.PreserveAspectCrop
            //scale: 0.9
            opacity: firstButtonMouseArea.containsMouse? 1.0: 0.7
            source: isLike ? "qrc:/images/common/btn_islove (2).png":"qrc:/images/common/btn_love (2).png"
        }
    }

    Button {
        id: secondButton
        anchors.left: firstButton.right
        anchors.leftMargin: 2
        anchors.top: firstButton.top

        MouseArea {
            id: secondButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
            onClicked: {
                console.log("download")
                buttonClick()
            }
        }

        background: Image {
            id: secondButtonImage
            anchors.fill: parent
            scale: 0.9
            opacity: secondButtonMouseArea.containsMouse ? 1.0: 0.7
            source: "qrc:/images/leftArea/btndownload.png"
        }
    }
}
