import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    width: 270
    height: parent.height
    anchors.left: bottomLeftButton.right
    anchors.right: bottomRightButton.left
    color: parent.color

    property string slidercolor: ""

    Text {
        id: totalTime
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: ""
    }
    Text {
        id: currentTime
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text: ""
    }
    Slider {
        id: positionSlider
        anchors.left: currentTime.right
        anchors.right: totalTime.left
        anchors.verticalCenter: parent.verticalCenter
        from: 0.0
        to: 1.0
        value: 0

        handle: Rectangle {
            id: handleRectangle
            visible: true
            x: positionSlider.value * (positionSlider.width - positionSlider.leftPadding
                                       - positionSlider.rightPadding)
            y: positionSlider.topPadding + positionSlider.availableHeight / 2 - height / 2
            implicitWidth: 14
            implicitHeight: 14
            radius: 13
            border.width: 1
            border.color: "#E1E1E2"
            Rectangle {
                width: 4
                height: 4
                color: slidercolor
                radius: 13
                anchors.centerIn: parent
            }
        }
        Rectangle {
            anchors.left: positionSlider.left
            anchors.leftMargin: positionSlider.leftPadding
            anchors.right: handleRectangle.left
            anchors.rightMargin: positionSlider.rightPadding

            y: positionSlider.topPadding + positionSlider.availableHeight / 2 - height / 2
            radius: 13
            height: 4
            color: slidercolor
        }
        MouseArea{
            anchors.fill: parent;
            acceptedButtons: Qt.LeftButton;
            onReleased: {

            }
            onWheel: wheel.accepted = true;

        }
    }
}