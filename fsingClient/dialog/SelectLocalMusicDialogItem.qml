import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4
import "common"

Rectangle {
    id: dialog
    border.color: "Silver"

    anchors.fill: parent

    signal quitClicked()
    signal okButtonClicked()
    signal checkChanged()

    Item {
        id: topitem
        width: parent.width
        height: 50
        focus: true
        anchors {
            top: parent.top
            left: parent.left
        }
        Text {
            id: name
            text: "选择本地音乐文件夹"
            font.bold: true
            color: "#6f6f6f"
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 20
            }
            font.pixelSize: 15
        }

        Rectangle{
            width: topitem.width
            height: 1
            anchors.top: name.bottom
            anchors.topMargin: 12
            color: "silver"
        }

        Rectangle {
            id: re1
            color: "white"
            border.width: 0
            width: 15
            height: 15
            anchors {
                right: parent.right
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            Image {
                id: exitButton
                width: 15
                height: 15
                source: "../images/common/close.png"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: re1
                focus: true
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    quitClicked()
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
                var delta = Qt.point(mouse.x - clickpos.x, mouse.y - clickpos.y)
                selectLocalMusicDialog.x = (selectLocalMusicDialog.x + delta.x)
                selectLocalMusicDialog.y = (selectLocalMusicDialog.y + delta.y)
            }
        }
    }
    Item {
        id: centeritem
        width: parent.width
        height: parent.height - 100

        anchors {
            top: topitem.bottom
        }

        Text{
            id:text_
            text:"将自动扫描您勾选的目录，文件增删实时同步。"
            color: "#888888"
            font.pixelSize: 13
            anchors.top:centeritem.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ListView{
            id:pathView
            width: centeritem.width
            height: centeritem.height
            model: _localMusicDir
            anchors.top: text_.bottom
            anchors.topMargin: 5
            delegate: Rectangle{
                id:viewItem
                width: centeritem.width-2
                height: 25
                color: "transparent"

                //property alias checkState: checkBox.checked

                CheckBox{
                    id:checkBox
                    x:10
                    checked: isChecked
                    text: path

                    onCheckedChanged: {
                        //checkChanged()
                        _localMusicDir.setProperty(index, "isChecked", checked)
                    }
                }

                Rectangle {
                    id: recImg
                    color: "white"
                    border.width: 0
                    width: 15
                    height: 15

                    anchors {
                        right: viewItem.right
                        rightMargin: 10
                        verticalCenter: viewItem.verticalCenter
                    }
                    Image {
                        id: deleteButton
                        width: 15
                        height: 15
                        source: "qrc:/images/common/dialogColse.png"
                        scale: 0.7
                        anchors.fill: recImg
                        visible: recImgMouse.containsMouse ? true : false
                    }
                    MouseArea {
                        id:recImgMouse
                        anchors.fill: recImg
                        hoverEnabled: true
                        focus: true
                        acceptedButtons: Qt.LeftButton
                        onClicked: {
                            _localMusicDir.remove(pathView.currentIndex)
                        }
                    }
                }
            }
        }

    }

    Item {
        id: bottomitem
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom

        Rectangle{
            width: topitem.width
            height: 1
            anchors.top: bottomitem.top
            anchors.topMargin: 0
            color: "silver"
        }

        Row {
            id:bottomRow
            spacing: 20
            anchors.verticalCenter: parent.verticalCenter
            height: 30

            anchors.left: parent.left
            anchors.leftMargin: 50
            MyButton {
                id: okButton
                width: 80
                height: 30
                text: "确认"
                color: "#3333CC"
                textColor: "white"
                onButtonClicked: {
                    getSelectPath()
                    quitClicked()
                    okButtonClicked()
                    console.log("okButtonClicked")
                }
            }
            MyButton {
                id: addButton
                width: 80
                height: 30
                text: "添加文件夹"
                onButtonClicked: {
                    fileDialog.open()
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        selectFolder:true

        onAccepted: {
            var str = new String(fileDialog.fileUrl)
            var res = str.slice(7)
            console.log("type: " + res)
            //pathText.text = str

            console.log("You chose: " + fileDialog.fileUrl)
            //console.log("res" + res)
            _localMusicDir.append({"isChecked": true, "path": res})
        }
    }

    function getSelectPath(){
        var count = _localMusicDir.count
        var i = 0;
        var list = []
        for (; i <  count; i++){
            if (_localMusicDir.get(i).isChecked === true){
                list.push(_localMusicDir.get(i).path)
            }
        }
        console.log(list.length)
        console.log(list[0])
        pathList = list
        var j =  0
        for (; j < pathList.length; j++)
            console.log(pathList[j]+"0000")
    }
}
