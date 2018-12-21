//import QtQuick 2.0
import QtQuick 2.7
import QtQuick.Controls 2.1
import "common"

Rectangle {
    id: dialog
    border.color: "white"
    //        color: "red" //"#F5F5F7"
//    border.width: 0.5

    anchors.fill: parent

    signal quitClicked
    signal okButtonClicked

    //    property bool inputValid: false
    Item {
        id: topitem
        width: parent.width
        height: parent.height * 0.2
        focus: true
        anchors {
            top: parent.top
            left: parent.left
        }

        Rectangle {
            anchors.fill: parent
            border.color: "Silver"
            color: "white"
            border.width: 0.5
            Text {
                id: name
                text: "新建歌单"
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 20
                }
                color: "#333333"
                font.pixelSize: 15
            }
            Rectangle {
                id: re1
                color: "white"
                border.width: 0
                width: 17
                height: 17
                anchors {
                    right: parent.right
                    rightMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                Image {
                    id: exitButton
                    width: 17
                    height: 17
                    source: "../images/leftArea/close.png"
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: re1
                    focus: true
                    acceptedButtons: Qt.LeftButton
                    onClicked: {
                        quitClicked()
                        titlerec.text = ""
                    }
                }
            }
        }

        MouseArea {
            anchors {
                left: parent.left
                bottom: parent.bottom
                top: parent.top
                right: parent.right
                rightMargin: 20
            }

            hoverEnabled: false
            acceptedButtons: Qt.LeftButton
            property point clickpos: "0,0"
            onPressed: {
                clickpos = Qt.point(mouse.x, mouse.y)
            }
            onPressAndHold: {
                dialog.opacity = 0.6
            }

            onReleased: {
                dialog.opacity = 1
            }

            onPositionChanged: {

                //                NumberAnimation{

                //                }
                var delta = Qt.point(mouse.x - clickpos.x, mouse.y - clickpos.y)
                createSongListDialog.x = (createSongListDialog.x + delta.x)
                createSongListDialog.y = (createSongListDialog.y + delta.y)
            }
        }
    }
    Item {
        id: centeritem
        width: parent.width
        height: parent.height * 0.6

        anchors {
            top: topitem.bottom
        }
        Rectangle {
            anchors.fill: parent
            border.color: "silver"

            border.width: 0.5
            Text {
                id: titlename
                text: "标题:"
                font.pixelSize: 15
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 30
            }
            MyTextInput{
                id:titlerec
                width: 150
                height: titlename.height * 1.5
                maxTextLength:30
                anchors{
                    left: titlename.right
                    leftMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                remindText: titlerec.text == "" ? "输入歌单名" :""
                text:remindText == "" ? titlerec.text :""
                onTextAccepted: {
                    if (titlerec.text != "" && titlerec.text != " ") {
                        createSongListDialog.inputText = titlerec.text
                        okButtonClicked()
                        titlerec.text = ""
                    }
                }
            }
        }
    }
    Item {
        id: bottomitem
        width: parent.width
        height: parent.height * 0.2

        anchors {
            top: centeritem.bottom
            bottom: parent.bottom
        }
        Rectangle {
            anchors.fill: parent

            border.color: "silver"
            border.width: 0.5
            Row {
                spacing: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 50
                MyButton {
                    id: okButton
                    width: 80
                    height: 30
                    text: "确定"
                    color: "#3333CC"
                    textColor: "white"
                    onButtonClicked: {
                        if (titlerec.text != "" && titlerec.text != " ") {
                            createSongListDialog.inputText = titlerec.text
                            okButtonClicked()
                            titlerec.text = ""
                        }
                    }
                }
                MyButton {
                    id: cancelButton
                    width: 80
                    height: 30
                    text: "取消"
                    onButtonClicked: {
                        quitClicked()
                        titlerec.text = ""
                    }
                }
            }
        }
    }
}
