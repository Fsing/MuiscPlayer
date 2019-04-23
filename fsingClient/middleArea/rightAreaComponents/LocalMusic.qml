import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import "../../element"
import "../../dialog"

Rectangle {
    property int index: 4
    color:"#fafafa"
    anchors.fill: parent

    property int numbers

    Rectangle{
        id: topRect
        width: parent.width
        height: 60
        color: "transparent"

        RowLayout{
            x: 30

            Rectangle{
                id:labelRect
                width: 100
                height: topRect.height
//                border.width: 2
//                border.color: "plum"
                color: "transparent"
                Text{
                    id:label
                    text: "本地音乐"
                    font.pixelSize: 20
                    anchors.horizontalCenter: labelRect.horizontalCenter
                    anchors.bottom: labelRect.bottom
                    anchors.bottomMargin: 10
                }
            }
            Rectangle{
                id:musicCountRect
                width: 60
                height: parent.height
                Text {
                    id: musicCount
                    color: "#7e7e7e"
                    text: numbers + "首音乐, "
                }
            }

            Rectangle{
                id:catelogRec
                width: 60
                height: parent.height
                color: "transparent"
                Text{
                    id:catelogText
                    text: "选择目录"
                    color: "#4996d0"
                    MouseArea{
                        id:catelogMouse
                        anchors.fill:catelogText
                        hoverEnabled: true
                        cursorShape:(pressed||catelogMouse.containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                        onClicked: {
                            console.log("catelog")
                        }
                    }
                }
            }
        }
    }

    Rectangle{
        id:line
        width: parent.width
        height: 1
        color: "#e1e1e2"
        anchors.top: topRect.bottom
    }

    Rectangle{
        width: parent.width
        height: topRect.height
        visible: false
//        border.width: 2
//        border.color: "plum"
        anchors.top: topRect.bottom
        anchors.topMargin: line.height

        PlayAllButton{
            x: 30
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Rectangle{
        id: selectCatelogRec
        width: parent.width
        height: parent.height - topRect.height - line.height
        anchors.top:line.bottom
        color: "transparent"

        Text{
            id:label_
            text: "请添加本地音乐"
            y:parent.height/2 -100
            font.pixelSize: 15
            anchors.horizontalCenter: selectCatelogRec.horizontalCenter
        }

        Rectangle{
            color: blueSelectMouse.containsMouse? "#1167a8" : "#0c73c2"
            width: 250
            height: 60
            anchors.top: label_.bottom
            radius: 5
            anchors.topMargin: 50
            anchors.horizontalCenter: selectCatelogRec.horizontalCenter

            Text{
                text: "选择本地音乐文件夹"
                anchors.centerIn: parent
                font.pixelSize: 17
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
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

    SelectLocalMusicDialog {
        id: selectLocalMusicDialog
        x: mainWindow.width / 2 - 150
        y: 100
        onInputAccepted: {

        }
    }
}
