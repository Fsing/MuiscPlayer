import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../../element/LocalMusic"
import "../../element"
import "../../dialog"

Rectangle {
    anchors.fill: parent
    property int index: 4
    color:"#fafafa"
    //anchors.fill: parent

    property int numbers
    property var songInfoList: []

    ScrollView{
        id: scroll
        width: parent.width
        height: parent.height
        clip: true

        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        ColumnLayout{
            id:column
            width: parent.width

            LocalMusicTop{
                id:top
                width: parent.width
            }

            LocalMusicInit{
                id:initView
                width: parent.width
                height: parent.height
            }

            Rectangle{
                id:songInfoView
                visible: false
                width: scroll.width
                height: scroll.height - top.height
                color: "transparent"

                onHeightChanged: {
                    console.log("*************songInfoView Height:   " + songInfoView.height)
                }

                Column{
                    //anchors.fill: songInfoView
                    Rectangle{
                        width: parent.width
                        height: top.height
                        color: "transparent"
                        PlayAllButton{
                            x: 30
                            anchors.verticalCenter: parent.verticalCenter
                            //添加本地音乐到播放列表
                            onPlayAllClick: {
                                currentListRectangle.playListModel.clear()
                                var i = 0
                                for (; i < songInfo.model.count; i++){
                                    currentListRectangle.playListModel.append({"title":songInfo.model.get(i).title,"artist":songInfo.model.get(i).artist, "time":songInfo.model.get(i).time})
                                    currentPlaylist.addItem(songInfo.model.get(i).path)
                                }
                                console.log("currentListRectangle.playListModel." + currentListRectangle.playListModel.count)
                                console.log("currentPlaylist:  " + currentPlaylist.itemCount)
                                currentPlaylist.currentIndex = 1
                                console.log("currentPlaylist:  " + currentPlaylist.currentItemSource)
                                currentListRectangle.listView.height = currentListRectangle.playListModel.count * 30
                                currentListRectangle.noSongsView.visible = false
                                currentListRectangle.listView.visible = true
                            }
                        }
                    }

                    LocalSongList{
                        id: songInfo
                        width: scroll.width
                        //height: 690
                    }
                }
            }
        }
    }

    SelectLocalMusicDialog {
        id: selectLocalMusicDialog
        x: mainWindow.width / 2 -selectLocalMusicDialog.width
        y: 100
        onOkClicked: {
            console.log("selectlocal")
            songInfoList = client.getLocalSongInfo(selectLocalMusicDialog.pathList)
            songInfo.model.clear()
            //songInfoView.visible = false

            console.log("songInfoList: " + songInfoList.length)
            var j = 1;
            var k = '0'
            var m = ''
            for (var i in songInfoList){
                var num
                if (i < 9){
                    num = k+j
                    j++
                }else{
                    num = m+j
                    j++

                }

                songInfo.model.append({"number": num, "title":songInfoList[i].title, "artist": songInfoList[i].artist, "album":songInfoList[i].album, "time": songInfoList[i].time, "size":songInfoList[i].size+'MB', "path": songInfoList[i].path})
            }
            songInfoView.height = songInfoList.length * 28 +30+100
            column.height = top.height + songInfoView.height
            console.log("column.width " +   column.width)
            console.log("column.height " +   column.height)
            console.log("scroll.width " +   scroll.width)
            console.log("scroll.height " +   scroll.height)
            console.log("songInfo.height " +   songInfo.height)
            songInfoView.update()
            initView.visible = false
            songInfoView.visible = true
        }
    }
}
