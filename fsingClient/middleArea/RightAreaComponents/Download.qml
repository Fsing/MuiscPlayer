import QtQuick 2.0
import "../../songList/element"
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    property int index: 5

    property var downloadModels:[]

    TableView{
        id:downloadView
        anchors.fill: parent
        model: downloadModels
        TableViewColumn{
            title: "id"
            role: "songid"
        }
        TableViewColumn{
            title: "标题"
            role: "title"
        }
        TableViewColumn{
            title: "歌手"
            role: "singer"
        }
        TableViewColumn{
            title: "专辑"
            role: "Ablum"
        }
        TableViewColumn{
            title: "playQuantity"
            role: "playQuantity"
        }
    }
    ListModel{
        id:downloadlistModel
        ListElement{
            songid:"1"
            title:"最美"
            singer:"羽泉"
            Ablum:"最美"
            playQuantity:"100"
        }
    }

//    ScrollView{
//        id: downloadView
//        anchors.fill: parent
//        clip: true
//        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
//        style: ScrollViewStyle {
//            id: ss
//            transientScrollBars: true
//        }
////        ListView{
////            anchors.top: parent.top
////            anchors.bottom: parent.bottom
////            anchors.bottomMargin: 15
////            anchors.left: parent.left
////            spacing: 10
////            model:songlistModel
////            delegate: songlist
////        }
////        ListModel
////        {
////            id:songlistModel
////            ListElement{
////                idtext:"1"
////                name:"最美"
////                singer:"周杰伦"
////                album:"haha"
////                playQuantity:"1"
////            }
////        }

//        ListSongs{
//            id:songlist
//            Row {
//                anchors.top:songlist.bottom
//                anchors.topMargin: 30
//                anchors.left: parent.left
////                anchors.verticalCenter: parent.verticalCenter
//                spacing: 8

//                Text {
//                    text: idtexttt
//                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
//                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
//                }

//                TwoButton {
//                    id: button_2
//                    z: 3
//                    anchors.top: parent.top
//                    anchors.topMargin: -3
//                    onButtonClick: {
//                        wrapper.ListView.view.currentIndex = index
//                    }
//                }
//                Text {
//                    text: name
//                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
//                    elide: Text.ElideRight
//                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
//                }
//                Text {
//                    text: singer
//                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
//                    elide: Text.ElideRight
//                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
//                }
//                Text {
//                    text: album
//                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
//                    elide: Text.ElideRight
//                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
//                }

//                Text {
//                    text: playQuantity
//                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
//                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
//                }
//            }
//        }
//    }
}
