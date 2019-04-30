import QtQuick 2.0
import QtQuick.Controls 1.4
import "../element"

Rectangle {
    color: "#fafafa"
    Column{
        width: parent.width
        spacing: 20
        Rectangle{
            id:editComment
            width: parent.width
            height: 140
            color: "#f0f0f2"
            TextArea{
                id:editTextArea
                x:15
                y:15
                width: editComment.width - 30
                height: 70
            }

            Rectangle{
                width:40
                height: 28
                radius: 5
                color: editTextMouse.containsMouse ? "#f5f5f7" : "#ffffff"
                border.width: 1
                anchors.right: editTextArea.right
                anchors.top: editTextArea.bottom
                anchors.topMargin: 15
                border.color: "#e1e1e2"
                Text {
                    text: "评论"
                    anchors.centerIn: parent
                }
                MouseArea{
                    id:editTextMouse
                    anchors.fill: parent
                    hoverEnabled: true

                    cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                }
            }
        }
        Text{
            id:_label_
            text: "精彩评论"
            font.pixelSize: 15
            color: "#8b8b8b"
        }

        ListView{
            id:commentView
            width: parent.width
            anchors.top: _label_.bottom
            model: commentModel_
            delegate: CommentItem{
                userIcon: userImage
                userName: name
                comment_: comment
            }
        }
    }
}
