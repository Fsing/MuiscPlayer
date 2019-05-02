import QtQuick 2.0


Item {
    id:commentItem
    Rectangle{

        width: commentItem.width
        height:2
        color: "#f0f0f0"
    }

    Row{
        width: parent.width
        height: parent.height
        y:10
        CircleIcon{
            id:userIcon
            width: 40
            height: 40
            userImage: image
        }

        Rectangle{
            id:commentRight
            width: commentItem.width - userIcon.width
            height: 50
            color: "#00000000"
            Column{
                x:10
                Row{
                    width: commentRight.width
                    height: 50
                    Text {
                        id:name__
                        //text: qsTr("Eva:  ")
                        //text: userName
                        text:name
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
                        id:comment__
                        width: commentRight.width - 10 - userIcon.width - name.width
                        height: 50
                        color: "#343434"
                        text:comment
                        //elide: Text.ElideRight
                        wrapMode: Text.WordWrap
                    }
                }

            }
        }
    }
}
