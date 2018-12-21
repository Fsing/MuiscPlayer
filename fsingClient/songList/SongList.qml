import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "./element"
import "../dialog"

Rectangle {
    id: songlist
    property int index: 9
    property string songListId
    //用于显示歌曲的model
    property var model: []
    //歌单名
    property var listname
    //歌单图片
    property var listImg
    //用户图片
    property var userImg
    //创建者
    property var username
    //创建时间
    property var createTime
    //标签
    property var label
    //歌单简介
    property var briefInfo

    ScrollView {
        id: scroll
        anchors.fill: parent

        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        //        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        ColumnLayout {
            y: 20
            spacing: 40
            SongListTop {
                id: songListTop
                width: songlist.width
                height: (songlist.height - 60) / 2
            }

            SongListBottom {
                id: songListBottom
                width: songlist.width
                height: 1500
            }
        }
    }

    SongOperationDialog {
        id: songOperationDialog
    }

    function collecSong() {
        console.log("songListInfo[0];  " + songListId)
        return songListId
    }
}
