import QtQuick 2.0
import QtQuick.Controls 1.4
    import QtQuick.Layouts 1.11
import "../element"

Rectangle {
    id:commentEnd
    color: "#fafafa"
    property alias commentView: commentView__

    signal addCommnet(var str)
    signal addPoint()
    signal deletePoint()

    ColumnLayout{
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
                    onClicked: {
                        addCommnet(editTextArea.text)
                        editTextArea.text = ""
                    }
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
            id:commentView__
            width: parent.width
            //height: commentModel_.count * 120
            //height: 300
            //anchors.top: _label_.bottom
            model: commentModel_
            delegate: delegates
        }
    }
    Component {
        id: delegates
        CommentItem {
            id: leftItemDelegates
            width: commentView.width
            height: 50
        }
    }

    onHeightChanged: {
       // console.log("height:  " + height)
        //console.log("commentView__.height:  " + commentView__.height)
        commentView__.height = height+50
        //console.log("commentView__.height:  " + commentView__.height)
    }
}
