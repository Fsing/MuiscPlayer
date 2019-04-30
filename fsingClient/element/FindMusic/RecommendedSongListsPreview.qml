import QtQuick 2.0
import "../../middleArea/RightAreaJS.js" as Js
import "../../songList"

Item {
    id:recSongLists
    width: recTopView.width -60
    //height: (recTopView.width/5 + 50) *2
    height:recSongListsLabel.height + gridViewRec.height
    property alias recModel:recommendSongListsModel
    ListModel {
        id:recommendSongListsModel
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
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
                    Image { source: icon; anchors.fill: rectangle; fillMode: Image.Stretch }
                    MouseArea{
                        anchors.fill: rectangle
                        hoverEnabled: true
                        cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                        onClicked: {
                            var songListId = recSongListIds[index]
                            client.songList(songListId)
                            rightArea.songListInfo = client.getRecSongListBasicInfo(songListId)

                            rightArea.songsListTable = client.getSongListSongs(songListId)
                            appendSong(rightArea.songsListTable)
                            Js.popView(11)
                        }
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
        rightArea.model_.clear()
        var count = lists.length/9
        for (var i = 0; i < count; i++){
            var j = 1;
            var k = '0'
            var m = ''

                rightArea.model_.append({"number": i,
                                        "operator":"",
                                        "title":lists[i * 9 + 1],
                                        "artist":lists[i * 9 + 2],
                                        "album":lists[i * 9 + 3],
                                        "time":lists[i * 9 + 5]})


        }
    }

}
