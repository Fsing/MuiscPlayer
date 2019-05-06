import QtQuick 2.0
import QtQuick.Controls 1.4
import "../element"
Item {
    width: parent.width
//    height: model.count * 28 +30
    height: songListModel.count * 28 +30
    //property alias model:songsModel
    property double length: (width-120)/4

    TableView {
        id:view
        anchors.fill: parent
        enabled: true
        //model: songsModel
        model: songListModel
        //model: localMusic.songList()
        frameVisible:false

        horizontalScrollBarPolicy:Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy:Qt.ScrollBarAlwaysOff

        headerDelegate: Rectangle
        {
            color:"#fafafa"
            implicitWidth:200
            implicitHeight:30
            border.color:"#e1e1e2"
            border.width:1;

            Text
            {
                anchors.leftMargin: 10
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                text: styleData.value
                color: "#757575"
                //font.bold: true
                anchors.fill:parent;

            }
        }

        rowDelegate: Rectangle{
                    id:rowRectangle

                    property color rowColor: styleData.selected?"#e3e3e5":(styleData.alternate ? "#fafafa":"#f5f5f7")
                    color:itemMouse.containsMouse ? "#ecedee" : rowColor
                    height: 28
                    MouseArea{
                        id:itemMouse
                        anchors.fill: rowRectangle
                        enabled: rowRectangle.focus
                        hoverEnabled: true
                        onClicked: {

                        }
                    }
       }

        TableViewColumn {
            id:numberColumn
            role: "number"
            title: " "
            movable: false
            resizable: false
            horizontalAlignment: Text.AlignRight
            width: 50
            visible: true

        }
        TableViewColumn {
            id:operatorColumn
            role: "operator"
            title: "操作"
            movable: false
            resizable: false
            horizontalAlignment: Text.AlignRight
            width: 70
            visible: true
            delegate: Rectangle{
                id:rec
                //anchors.fill: operatorColumn
                color: "#00000000"
                ActionButton{
                    x:15
                    y:3

                    onButtonClick: {
                        console.log(rec.height)
                        console.log(rec.width)
                    }
                }
            }

        }
        TableViewColumn {
            id:titleColumn
            role: "title"
            title: "音乐标题"
            width: length
            elideMode: Text.ElideMiddle

            movable: false
        }

        TableViewColumn {
            id:artistColumn
            role: "artist"
            title: "歌手"
            width: length
            movable: false
        }
        TableViewColumn {
            id:albumColumn
            role: "album"
            title: "专辑"
            width: length
            movable: false
        }
        TableViewColumn {
            id:timeColumn
            role: "time"
            title: "时长"
            width: length
            movable: false
        }

        onClicked: {
            console.log("row clicked")
            console.log("info:    " + songListModel.get(view.currentRow).time)
            console.log("leftArea.lyricSource : " +leftArea.lyricSource )
            console.log("info:    " + songsListTable[row*9])
        }
        onDoubleClicked: {
            rtspClient.play(songsListTable[row*9]+".mp3")
//            mediaPlayer.playbackState  = 1;
//            mediaPlayer.play()
            //界面左下角的歌曲界面
            console.log("applicationDirPath:   "+applicationDirPath)
            leftArea.lyricSource = rightArea.songsListTable[row*9+1] + ".lrc"
            var albumImg = songListModel.get(view.currentRow).album +".jpg"
            client.fileTransfer(albumImg)
            leftArea.albumImage = "file://" + applicationDirPath +"/" + albumImg
            leftArea.currentSongId = songsListTable[row*9]
            leftArea.currentSongName = songListModel.get(view.currentRow).title
            leftArea.currentSinger = songListModel.get(view.currentRow).artist
            leftArea.currentAlbum = songListModel.get(view.currentRow).album
            bottomArea.duration = songListModel.get(view.currentRow).time
        }
    }
}
