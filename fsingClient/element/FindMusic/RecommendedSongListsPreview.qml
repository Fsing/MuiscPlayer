import QtQuick 2.0

Item {
    id:recSongLists
    width: recTopView.width -60
    //height: (recTopView.width/5 + 50) *2
    height:recSongListsLabel.height + gridViewRec.height
    property alias recModel:recommendSongListsModel
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


    Item{
        id:recSongListsLabel
        width: recSongLists.width
        height: 40
        Text {
            text: "推荐歌单"
            color: "#3b3b3b"
            font.pixelSize: 18
        }
        Rectangle{
            width: recSongLists.width-15
            height: 1
            anchors.top: recSongListsLabel.bottom
            anchors.topMargin: -10
            color:"#e1e1e2"
        }
    }

    Rectangle{
        id:gridViewRec
        anchors.top: recSongListsLabel.bottom
        color: "transparent"
        width: recSongLists.width
        height: (recSongLists.width/5 + 50)*2
        GridView {
            id:gridView
            anchors.fill: parent
            cellWidth: recTopView.width/5
            cellHeight:recTopView.width/5 + 50

            model: recommendSongListsModel
            delegate:Column {
                    Rectangle{
                        id:rectangle
                        border.color: "pink"
                        border.width: 2
                        width: gridView.cellWidth - 15
                        height: gridView.cellWidth -15
                        Image { source: icon; anchors.fill: rectangle; fillMode: Image.Stretch }
                        MouseArea{
                            anchors.fill: rectangle
                            hoverEnabled: true
                            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                        }
                    }
                    Text {
                        id:recText
                        text: name;
                        width:  gridView.cellWidth - 15
                        elide: Text.ElideRight
                        wrapMode: Text.WordWrap
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: recTextMouse.containsMouse ? "#222222" : "#505050"
                        MouseArea{
                            id:recTextMouse
                            anchors.fill: recText
                            hoverEnabled: true
                            cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                        }
                    }
                }
        }
    }
}
