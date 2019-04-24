import QtQuick 2.0
import QtQuick.Layouts 1.11

Item {
    id: selectCatelogRec
    width: parent.width
    height: parent.height

    ColumnLayout{
        y: scroll.height/4
        width: scroll.width
        height: scroll.height/3
        spacing: 0
        Text{
            id:label_
            text: "请添加本地音乐"
            //y:parent.height/2 -100
            font.pixelSize: 15
            //anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Qt.AlignCenter

        }

        Rectangle{
            color: blueSelectMouse.containsMouse? "#1167a8" : "#0c73c2"
            width: 250
            height: 60
            // y:parent.height/2
            radius: 5
            //anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Qt.AlignCenter
            Text{
                text: "选择本地音乐文件夹"
                anchors.centerIn: parent
                font.pixelSize: 17
                color: "white"
            }

            MouseArea{
                id: blueSelectMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: (pressed||blueSelectMouse.containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                onClicked: selectLocalMusicDialog.open()
            }
        }
    }
}
