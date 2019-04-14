import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import "../element"

Rectangle {
    id:songListBottom

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
        height: songListBottom.height - bar.height
        currentIndex: bar.currentIndex
        Rectangle{
            color: "green"
            Text{
                text: "赶快去收藏你喜欢的音乐"
                anchors.centerIn: parent
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
