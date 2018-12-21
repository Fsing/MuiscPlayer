import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    width: playImg.width + 1 + textImg.width
    height: playImg.height

    signal allClick
    signal addClick

    Button {
        id: playImg
        icon.source: "qrc:/images/bottomArea/play.png"
        text: "播放全部"
        onClicked: allClick()
    }
    Rectangle {
        id: line
        //模拟线段
        width: 1 //长
        height: playImg.height //高
        anchors.left: playImg.right
        anchors.bottom: playImg.bottom
        visible: true
        color: "#7c7171" //颜色
    }

    Button {
        id: textImg
        width: 30
        anchors.left: playImg.right
        anchors.leftMargin: 1
        icon.source: "qrc:/images/leftArea/creatSongList.png"
        onClicked: addClick()
    }
}
