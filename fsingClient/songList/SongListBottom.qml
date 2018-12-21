import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import "./element"

Rectangle {
    id: rectangle

    Column {
        RowLayout {
            id: rec
            x: 50
            spacing: 10
            Button {
                id: songListButton
                text: "歌曲列表"
                onClicked: {
                    listsongs.tvisible = true
                }
            }
            Button {
                text: "评论"
                onClicked: {
                    listsongs.tvisible = false
                }
            }
            Button {
                text: "收藏者"
                onClicked: {
                    listsongs.tvisible = false
                }
            }
        }
        Rectangle {
            id: horline
            //模拟线段
            width: rectangle.width //长
            height: 2 //高
            visible: true
            color: "#C62F2F" //颜色
        }
        Rectangle {
            id: list
            width: rectangle.width
            height: rectangle.height - rec.height
            ListSongs {
                id: listsongs
                anchors.fill: list
                tvisible: true
                songListModel: songlist.model
            }
        }
    }
}
