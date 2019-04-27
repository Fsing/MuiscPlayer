import QtQuick 2.0

Item {
    ListModel {
        id:recommendSongListsModel
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
        }
    }

    Rectangle{
        //x:30
        y:30
        width: parent.width
        height: (parent.width/5 + 50)*2
        GridView {
            id:gridView
            anchors.fill: parent
            cellWidth: parent.width/5
            cellHeight: parent.height/2

            model: recommendSongListsModel
            delegate: Column {
                Rectangle{
                    id:rectangle
                    border.color: "pink"
                    border.width: 2
                    width: gridView.cellWidth - 15
                    height: gridView.cellWidth -15
                    Image { source: icon; anchors.fill: rectangle; fillMode: Image.Stretch }
                }
                Text {
                    text: name;
                    elide: Text.ElideRight
                    anchors.horizontalCenter: parent.horizontalCenter
                }

            }
        }
    }
}
