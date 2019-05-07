import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    width: 30
    height: 30

    property var userImage
    Image {
        id: img
        source: userImage
        sourceSize: Qt.size(parent.width, parent.height)
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        smooth: true
        visible: false //是图片变成圆形
        enabled: true
    }

    //轮廓
    Rectangle {
        id: mask
        smooth: true
        visible: false
        anchors.fill: parent
        radius: height / 2
    }

    OpacityMask {
        anchors.fill: img
        source: img
        maskSource: mask
        enabled: true
    }
}
