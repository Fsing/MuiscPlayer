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

    property int numbers:_locaMusicModel.count
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
                //visible: songInfoView.visible === true ? false : true
                visible: !isLocalListVisable
            }

            Rectangle{
                id:songInfoView
                //visible: _locaMusicModel.count == 0 ? false : true
                visible: isLocalListVisable
                width: scroll.width
                //height: scroll.height - top.height
                height: isLocalListVisable? localListSongsHeight : (scroll.height - top.height)
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
                                for (; i < _locaMusicModel.count; i++){
                                    currentListRectangle.playListModel.append({"id":0,"title":_locaMusicModel.get(i).title,"artist":_locaMusicModel.get(i).artist, "time":_locaMusicModel.get(i).time})
                                    currentPlaylist.addItem(_locaMusicModel.get(i).path)
                                }
                                console.log("currentListRectangle.playListModel." + currentListRectangle.playListModel.count)
                                console.log("currentPlaylist:  " + currentPlaylist.itemCount)
                                currentPlaylist.currentIndex = 1
                                currentListRectangle.songNumber = currentListRectangle.playListModel.count
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
            _locaMusicModel.clear()
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

                _locaMusicModel.append({"number": num, "title":songInfoList[i].title, "artist": songInfoList[i].artist, "album":songInfoList[i].album, "time": songInfoList[i].time, "size":songInfoList[i].size+'MB', "path": songInfoList[i].path})
            }
            //numbers = songInfo.model.count
            songInfoView.height = songInfoList.length * 28 +30+100
            column.height = top.height + songInfoView.height
//            console.log("column.width " +   column.width)
//            console.log("column.height " +   column.height)
//            console.log("scroll.width " +   scroll.width)
//            console.log("scroll.height " +   scroll.height)
//            console.log("songInfo.height " +   songInfo.height)
            songInfoView.update()
            //initView.visible = false
            //songInfoView.visible = true
            localListSongsHeight = songInfoList.length * 28 +30+100
            if (_locaMusicModel.count === 0){
                isLocalListVisable = false
            } else {
                isLocalListVisable = true
            }
        }
    }
}
