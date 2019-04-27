import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import "../element"

Rectangle {
    id:songListBottom
    height: bar.height + line.height + layout.height

    MyTabBar{
        id: bar
        x: 50
        width: parent.width
        height: 30
        spacing: 10

        myModel: ["歌曲列表", "评论", "收藏者"]
    }

    Rectangle{
        id:line
        anchors.top: bar.bottom
        width: songListBottom.width
        height: 2
        color: "#C62F2F"
    }

    StackLayout{
        id:layout
        anchors.top: line.bottom

        width: songListBottom.width
        height: if (currentIndex ===0 ) {
                    songListInit.visible ? (songlist.height - songListTop.height - bar.height - line.height): listSongs.height
                }else{
                    songlist.height - songListTop.height - bar.height - line.height
                }

        currentIndex: bar.currentIndex
        Rectangle{
            color: "green"
            width: layout.width
            height: listSongs.height
            Text{
                id:songListInit
                visible:listSongs.model.count === 0 ? true : false
                text: "赶快去收藏你喜欢的音乐"
                anchors.centerIn: parent
            }
            ListSongs{
                id:listSongs
                //anchors.fill:parent
                visible: model.count ===0 ? false: true
            }
        }

        Rectangle{
            color: "plum"
            Text{
                text: "评论"
                anchors.centerIn: parent
            }
        }

        Rectangle{
            color: "teal"
            Text{
                text: "暂无收藏者"
                anchors.centerIn: parent
            }
        }
    }

}
