import QtQuick 2.0
import "../../songList"

Rectangle {
    property int index: 9
    //anchors.fill: parent
    color:"lightblue"

    SongList{
        width: parent.width
        height: parent.height
        songListName: "我喜欢的音乐"
        songListCreateTime: "2017-03-12"
        userName: "eva"
    }
}
