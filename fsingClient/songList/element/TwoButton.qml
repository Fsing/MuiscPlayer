import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2

Item {
    anchors.verticalCenter: parent.verticalCenter
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
            onClicked: {
                console.log("like")
                buttonClick()
            }
        }

        background: Image {
            id: firstButtonImage
            anchors.fill: parent
            opacity: 1
            source: "qrc:/images/leftArea/btnfavorite.png"
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
            onClicked: {
                console.log("download")
                buttonClick()
            }
        }

        background: Image {
            id: secondButtonImage
            anchors.fill: parent
            opacity: 1
            source: "qrc:/images/leftArea/btndownload.png"
        }
    }
}
