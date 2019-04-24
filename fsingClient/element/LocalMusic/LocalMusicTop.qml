import QtQuick 2.0
import QtQuick.Layouts 1.11

Item {
    id: topRect
    width: parent.width
    height: 60
    Column{
        RowLayout{
            id:row
            x: 30

            Rectangle{
                id:labelRect
                width: 100
                height: topRect.height
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
                            selectLocalMusicDialog.open()
                        }
                    }
                }
            }
        }
        Rectangle{
            id:line
            width: scroll.width
            height: 1
            color: "#e1e1e2"
        }
    }
}
