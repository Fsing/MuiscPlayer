import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../middleArea/RightAreaJS.js" as Js

Item {
    id:onlineSongListView
    property var onlineSongListModel
    //anchors.fill: parent

    //    ScrollView{
    //        id:onlineSongListView
    //        anchors.fill: parent
    //        //anchors.horizontalCenter: parent.horizontalCenter
    //        clip: true
    //        style: ScrollViewStyle {
    //            id: ss
    //            transientScrollBars: true
    //        }

    GridView {
        id:gridView
        x:25
        anchors.fill: parent
        cellWidth: (onlineSongListView.width)/5
        cellHeight:(onlineSongListView.width)/5 + 50

        model: onlineSongListModel
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
                        var songListId = onlineSongListInfo[index*10]
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
    //    }
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
