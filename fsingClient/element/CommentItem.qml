import QtQuick 2.0


Item {
    id:commentItem

    property string userIcon
    property string userName
    property string comment_
    Rectangle{
        y:5
        width: commentItem.width
        height:2
        color: "#f0f0f0"
    }

    Row{
        y:10
        CircleIcon{
            id:userIcon
            width: 40
            height: 40
            userImage: "file:///root/new7/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/zhenhy.jpg"
        }

        Rectangle{
            id:commentRight
            width: commentItem.width - userIcon.width
            height: 50
            Column{
                x:10
                Row{
                    Text {
                        id:name
                        text: qsTr("Eva:  ")
                        font.pixelSize: 15
                        opacity: nameMouse.containsMouse ? 1.0 :0.8
                        color: "#2984c9"
                        MouseArea{
                            id:nameMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                        }
                    }
                    Text{
                        id:comment
                        width: commentRight.width - 10 - userIcon.width - name.width
                        height: 50
                        color: "#343434"
                        text:"叶凡：“尝尽人间绚烂，难补一生辛酸遗憾”"
                        //elide: Text.ElideRight
                        wrapMode: Text.WordWrap
                    }
                }

            }
        }
    }
}
