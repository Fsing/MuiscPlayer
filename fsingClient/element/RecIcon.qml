import QtQuick 2.0

Rectangle {
    width: 200
    height: 200
    border.width: 1
    border.color: "#e0e0e0"
    signal clicked
    property alias iconSource: icon.source

    Image {
        id: icon
        anchors.fill: parent
        //source: songlist.songListImage_
        //fillMode属性用来定义当图片大小设置小于item大小时的填充方式
        fillMode: Image.PreserveAspectCrop//图片会被统一缩放，如果有必要则会剪切
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            clicked()
        }
    }
}
