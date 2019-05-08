import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    width: 200
    height: parent.height
    anchors.left: parent.left
    color: parent.color

    property string buttonColor: ""
    property double noHoverOpacity: 1.0
    property double hoverOpacity:0.8

    //    property bool isPlaying: false                      //是否正在播放
    property string playingSongName                     //正在播放的歌曲名字

    Button {
        id: prebutton
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter
        width: 32
        height: 32

        MouseArea{
            id: preButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
//                var previousIndex = mediaPlayer.playlist.previousIndex()
//                if (previousIndex === -1) {
//                    mediaPlayer.playlist.currentIndex = mediaPlayer.playlist.itemCount - 1
//                } else {
//                    mediaPlayer.playlist.previous()
//                }
//                mediaPlayer.play()
                var i = currentListRectangle.listView.currentIndex-1
                if(i < 0){
                    i = currentListRectangle.playListModel.count;
                }
                currentListRectangle.listView.currentIndex = i;

                //专辑图、歌词
                middleArea.leftArea.lyricSource =  middleArea.rightArea.songsListTable[i*9+1] + ".lrc"
//                var p = currentListRectangle.listView.currentIndex
                var albumImg = middleArea.rightArea.model_.get(i).album +".jpg"
                client.fileTransfer(albumImg)
                middleArea.leftArea.albumImage = "file://" + applicationDirPath +"/" + albumImg
                middleArea.leftArea.currentSongId = middleArea.rightArea.songsListTable[i*9]
                middleArea.leftArea.currentSongName = currentListRectangle.playListModel.get(i).title
                middleArea.leftArea.currentSinger = middleArea.rightArea.model_.get(i).artist
                middleArea.leftArea.currentAlbum = middleArea.rightArea.model_.get(i).album

                rtspClient.play(currentListRectangle.playListModel.get(i).id + ".mp3")
                console.log("urrentListRectangle.playListModel.get(currentPlaylist.currentIndex).id" + currentListRectangle.playListModel.get(i).id)
            }
        }
        background:Rectangle{
            id:preButtonRectangle
            anchors.fill: parent
            color: buttonColor
            radius: 30
            Image {
                id:preButtonImage
                anchors.centerIn:parent
                opacity: preButtonMouseArea.containsMouse ? hoverOpacity : noHoverOpacity
                source: "qrc:/images/bottomArea/previous.png"
            }
        }
    }
    Button {
        id: pausebutton
        anchors.left: prebutton.right
        anchors.leftMargin: 20
        anchors.verticalCenter: prebutton.verticalCenter
        width: 40
        height: 40

        MouseArea{
            id: pauseButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                //                                console.log("mediaPlayer.playbackState:   " + mediaPlayer.playbackState)
                //                                if(mediaPlayer.playbackState === 1)
                //                                            mediaPlayer.pause()
                //                                else
                //                                    mediaPlayer.play()
                //在线音乐
                console.log("onlineMedia.playbackState:   " + rtspClient.playState +":  " + playingSongName)
                if(rtspClient.playState === 0){
                    rtspClient.play(playingSongName)
                }else if(rtspClient.playState === 1)
                    rtspClient.pause()
            }
        }
        background:Rectangle{
            id:pauseButtonRectangle
            anchors.fill: parent
            color: buttonColor
            radius: 30
            Image {
                width: 44
                height: 44
                id:pauseButtonImage
                anchors.centerIn:parent
                opacity: pauseButtonMouseArea.containsMouse ? hoverOpacity : noHoverOpacity
//                source: mediaPlayer.playbackState === 1 ?
//                            "qrc:/images/bottomArea/pause.png"
//                          : "qrc:/images/bottomArea/play.png"
                source: rtspClient.playState === 1 ?
                            "qrc:/images/bottomArea/pause.png"
                          : "qrc:/images/bottomArea/play.png"
            }
        }
    }
    Button {
        id: nextbutton
        anchors.left: pausebutton.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 32
        height: 32

        MouseArea{
            id: nextButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                //                var nextIndex = mediaPlayer.playlist.nextIndex()
                //                if (nextIndex === -1) {
                //                    mediaPlayer.playlist.currentIndex = 0
                //                } else {
                //                    mediaPlayer.playlist.next()
                //                }
                //                mediaPlayer.play()
                //            }

                var i = currentListRectangle.listView.currentIndex+1
                if(currentListRectangle.playListModel.count === i){
                    i = 0;
                }
                currentListRectangle.listView.currentIndex = i;

                //专辑图、歌词
//                var p = currentListRectangle.listView.currentIndex
//                console.debug("current index" + i)
//                console.debug("count" + currentListRectangle.playListModel.count)
                middleArea.leftArea.lyricSource =  middleArea.rightArea.songsListTable[i*9+1] + ".lrc"
                var albumImg = middleArea.rightArea.model_.get(i).album +".jpg"
                client.fileTransfer(albumImg)
                middleArea.leftArea.albumImage = "file://" + applicationDirPath +"/" + albumImg
                middleArea.leftArea.currentSongId = middleArea.rightArea.songsListTable[i*9]
                middleArea.leftArea.currentSongName = currentListRectangle.playListModel.get(i).title
                middleArea.leftArea.currentSinger = middleArea.rightArea.model_.get(i).artist
                middleArea.leftArea.currentAlbum = middleArea.rightArea.model_.get(i).album

                rtspClient.play(currentListRectangle.playListModel.get(i).id + ".mp3")
                console.log("urrentListRectangle.playListModel.get(currentPlaylist.currentIndex).id" + currentListRectangle.playListModel.get(i).id)

//                var nextIndex = mediaPlayer.playlist.nextIndex()
//                if (nextIndex === -1) {
//                    mediaPlayer.playlist.currentIndex = 0
//                } else {
//                    mediaPlayer.playlist.next()
//                }
//                mediaPlayer.play()
            }
        }
        background:Rectangle{
            id:nextButtonRectangle
            anchors.fill: parent
            color: buttonColor
            radius: 30
            Image {
                id:nextButtonImage
                anchors.centerIn:parent
                opacity: nextButtonMouseArea.containsMouse ? hoverOpacity : noHoverOpacity
                source: "qrc:/images/bottomArea/next.png"
            }
        }
    }


}
