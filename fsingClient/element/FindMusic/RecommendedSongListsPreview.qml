import QtQuick 2.0
import "../../middleArea/RightAreaJS.js" as Js
import "../../songList"

Item {
    id:recSongLists
    width: recTopView.width -60
    //height: (recTopView.width/5 + 50) *2
    height:recSongListsLabel.height + gridViewRec.height
    property alias recModel:recommendSongListsModel

    signal showMoreOnlineSongList()

    ListModel {
        id:recommendSongListsModel
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:0
        }
    }


    Item{
        id:recSongListsLabel
        width: recSongLists.width
        height: 40
        Text {
            text: "推荐歌单"
            color: "#3b3b3b"
            font.pixelSize: 18
        }
        Text {
            id: moreText
            text: "更多"
            color: "#696969"
            anchors.right: recSongListsLabel.right
            anchors.rightMargin: 20
            anchors.bottom: recSongListsLabel.bottom
            anchors.bottomMargin: 15

            opacity: moreTextMouse.containsMouse ? 1.0 : 0.8
            MouseArea{
                id:moreTextMouse
                anchors.fill: moreText
                hoverEnabled: true
                cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                onClicked: {
                    tabBar.currentIndex = 1
                }
            }
        }
        Rectangle{
            width: recSongLists.width-15
            height: 1
            anchors.top: recSongListsLabel.bottom
            anchors.topMargin: -10
            color:"#e1e1e2"
        }
    }

    Rectangle{
        id:gridViewRec
        anchors.top: recSongListsLabel.bottom
        color: "transparent"
        width: recSongLists.width
        height: (recSongLists.width/5 + 50)*2
        GridView {
            id:gridView
            anchors.fill: parent
            cellWidth: recTopView.width/5
            cellHeight:recTopView.width/5 + 50

            model: recommendSongListsModel
            delegate:Column {
                Rectangle{
                    id:rectangle
                    border.color: "pink"
                    border.width: 2
                    width: gridView.cellWidth - 15
                    height: gridView.cellWidth -15
                    Image { id:recImae; source: icon; anchors.fill: rectangle; fillMode: Image.Stretch }
                    MouseArea{
                        id:recMouse
                        anchors.fill: rectangle
                        hoverEnabled: true
                        cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                        onClicked: {
                            var songListId = recSongListIds[index]
                            client.songList(songListId)
                            rightArea.songListInfo = client.getSongListBasicInfo(songListId)

                            rightArea.songsListTable = client.getSongListSongs(songListId)
                            appendSong(rightArea.songsListTable)
                            Js.popView(11)
                        }
                    }

                    Rectangle {
                        id:playQuantityRectangle
                        anchors.top:recImae.top
                        anchors.right: recImae.right
                        width:  recImae.height * 0.15
                        height:recImae.width * 0.4
                        anchors.rightMargin: 18
                        anchors.topMargin: -18
                        color: parent.color
                        rotation:90
                        //visible:!recMouse.containsMouse && backImage.status === Image.Ready
                        visible: recMouse.containsMouse ? false : true
                        gradient: Gradient {
                            GradientStop{
                                position: 0.0;
                                color: Qt.rgba(0,0,0,0.7);

                            }
                            GradientStop{
                                position: 1.0;
                                color: Qt.rgba(0,0,0,0);
                            }
                        }
                    }
                    Text {
                        anchors.top:rectangle.top
                        anchors.topMargin: 0
                        anchors.right: rectangle.right
                        anchors.rightMargin: 5
                        //anchors.topMargin: 15
                        id: clickQuantityText
                        text: clickQuantity
                        color: "white"
                        visible: recMouse.containsMouse ? false : true
                    }
                }
                Text {
                    id:recText
                    text: name;
                    width:  gridView.cellWidth - 15
                    elide: Text.ElideRight
                    wrapMode: Text.WordWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: recTextMouse.containsMouse ? "#222222" : "#505050"
                    MouseArea{
                        id:recTextMouse
                        anchors.fill: recText
                        hoverEnabled: true
                        cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                    }
                }
            }
        }
    }
    function appendSong(lists){
        if(lists.length !== 0){
            rightArea.model_.clear()
            var count = lists.length/9
            var j = 1;
            var k = '0'
            var m = ''
            for (var i = 0; i < count; i++){
                //设置歌曲的序号
                var num
                if (i < 9){
                    num = k+j
                    j++
                }else{
                    num = m+j
                    j++

                }

                rightArea.model_.append({"number": num,
                                            "operator":"",
                                            "title":lists[i * 9 + 1],
                                            "artist":lists[i * 9 + 2],
                                            "album":lists[i * 9 + 3],
                                            "time":lists[i * 9 + 5]})

            }
        }
    }

}
