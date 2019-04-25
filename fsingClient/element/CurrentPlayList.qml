import QtQuick 2.11
import QtMultimedia 5.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle {
    id:currentListRectangle
    color:"#F0F0F0"
    //color: "pink"
    //opacity: 0.8
    anchors.right: parent.right
    anchors.bottom: bottomArea.top
    visible: false
    width: 600
    height: 500
    property int songNumber:0

    property alias playListModel: playListModel_
    property alias historyModel:historyModel_
    property alias noSongsView: noSongsView_
    property alias listView: listView_

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            console.log("播放列表")
        }
        onReleased: {}
        onPressed: {}
        onWheel: {}
    }

    /**************************************顶部按钮***************************************/
    Rectangle{
        id:topButton
        width: parent.width
        height: 35
        color: "#f5f5f7"
        property bool isPlayListButtonChecked: true

        Rectangle{
            id:playListButton
            width: 100
            height: 25
            radius: 5
            border.width: 0.5
            border.color: "#e5e5e5"
            x:currentListRectangle.width/2-playListButton.width
            anchors.verticalCenter: parent.verticalCenter
            color: topButton.isPlayListButtonChecked ? "#7c7d85" :(playListButtonMouse.containsMouse ?"#f5f5f7":"white")
            Text{
                text: "播放列表"
                color: topButton.isPlayListButtonChecked ? "white" : (playListButtonMouse.containsMouse ? "#7c7d85": "#929292")
                anchors.centerIn: parent
            }
            MouseArea{
                id:playListButtonMouse
                anchors.fill: playListButton
                hoverEnabled: true
                onClicked: {
                    console.log("play")
                    topButton.isPlayListButtonChecked = true
                }
            }
        }

        Rectangle{
            id:historyButton
            width: 100
            height: 25
            radius: 5
            border.width: 0.5
            border.color: "#e5e5e5"
            anchors.left: playListButton.right
            anchors.top: playListButton.top
            color: topButton.isPlayListButtonChecked ? (historyButtonMouse.containsMouse ?"#f5f5f7":"white") : "#7c7d85"

            Text{
                text: "历史记录"
                anchors.centerIn: parent
                color: topButton.isPlayListButtonChecked ? (historyButtonMouse.containsMouse ? "#7c7d85": "#929292") :"white"
            }
            MouseArea{
                id:historyButtonMouse
                anchors.fill: historyButton
                hoverEnabled: true
                onClicked: {
                    topButton.isPlayListButtonChecked = false
                    console.log("history")
                }
            }
        }

        Rectangle {
            id: re1
            color: "transparent"
            border.width: 0
            width: 15
            height: 15
            anchors.verticalCenter: topButton.verticalCenter
            anchors.right: topButton.right
            anchors.rightMargin: 10
            Image {
                id: exitButton
                width: 15
                height: 15
                scale: 0.6
                source: "../images/common/dialogColse.png"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: re1
                focus: true
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    currentListRectangle.visible = false
                }
            }
        }
    }


    /**************************************播放列表信息***************************************/
    Rectangle{
        id:playListInfo
        width: parent.width-2
        height: 30
        anchors.top: topButton.bottom
        color: "#f9f9f9"

        Text{
            id:playListNumber
            text: "总" + songNumber + "首"
            color: "#838383"
            anchors.verticalCenter: parent.verticalCenter
            x:20
        }

        IconButton{
            id:collectButton
            anchors.top:clearButton.top
            anchors.right: clearButton.left
            anchors.rightMargin: 1
            border.width: 0
            iconScale: 0.9
            color: "transparent"
            buttonText: "收藏全部"
            iconSource: "qrc:/images/common/collect.png"
            opacity: mouseArea.containsMouse ? 1: 0.5
        }
        Rectangle{
            id:line
            width: 1
            height: clearButton.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: clearButton.left
            color: "#cccccc"
        }

        IconButton{
            id:clearButton
            color: "transparent"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            iconScale:0.8
            border.width: 0
            buttonText: "清空"
            iconSource: "qrc:/images/common/delete.png"
            opacity: mouseArea.containsMouse ? 1: 0.5
            onIconButtonClicked: {
                currentPlaylist.clear()
                noSongsView.visible = true
                listView.visible = false
            }
        }
    }

    Rectangle{
        id:noSongsView_
        width: parent.width
        height: parent.height - topButton.height - playListInfo.height
        anchors.top: playListInfo.bottom
        Text{
            text: "你还没有添加任何歌曲！"
            color:"#a2a2a2"
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            y:parent.height/2 - 50

        }
    }

    ListModel{
        id:playListModel_
    }


    ListModel{
        id:historyModel_
    }

    ScrollView{
        width: parent.width
        height: parent.height -topButton.height - playListInfo.height
        anchors.top: playListInfo.bottom
        clip: true

        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        ListView {
            id:listView_
            visible: false

            anchors.fill: parent
            model: playListModel_
            delegate:Rectangle{
                height: 30
                width: parent.width
                color: (index%2 == 0) ? "#fafafa":"#f5f5f7"

                RowLayout{
                    width: parent.width - 20
                    height: parent.height
                    x:20
                    Text {
                        text: title
                        elide: Text.ElideRight
                        Layout.preferredWidth: 380
                    }

                    Text {
                        text: artist
                        elide: Text.ElideRight
                        Layout.preferredWidth: 120
                    }

                    Text {
                        text: time
                        elide: Text.ElideRight
                        Layout.preferredWidth: 100
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked:{

                    }
                }
            }
        }
    }

}
