import QtQuick 2.0

Item {
    id:personSongListsView
    //width: 800
    //height: 400
    width: parent.width
    property var partName
    property var songListNumber:personSongListsModel.count
    property var songsnum
    property var personSongListsModel

    Column{
        anchors.fill: parent
        Item{
            width: parent.width
            height: 50
            Column{
                anchors.fill: parent
                spacing: 5
                Rectangle{
                    width: parent.width
                    height: 1
                    color: "#e0e0e0"
                }
                Text {
                    id: name
                    x:30
                    text: partName +"（"+  songListNumber  +"）"
                    color: "#4f4f4f"
                }
                Rectangle{
                    width: parent.width
                    height: 1
                    color: "#e0e0e0"
                }
            }
        }

        GridView {
            x:30
            id:gridView
            width: personSongListsView.width
            height: ((personSongListsView.width-30)/5 + 50) * Math.ceil(personSongListsModel.count/5)
            cellWidth: (personSongListsView.width-30)/5
            cellHeight:(personSongListsView.width-30)/5 + 50

       //     model: onlineSongListModel
            model:personSongListsModel
            delegate:Column {
                Rectangle{
                    id:rectangle
                    border.color: "pink"
                    border.width: 2
                    width: gridView.cellWidth - 15
                    height: gridView.cellWidth -15
                    Image { id:recImae; source: icon; anchors.fill: rectangle; fillMode: Image.Stretch }
                    MouseArea{
                        id:recMouse
                        anchors.fill: rectangle
                        hoverEnabled: true
                        cursorShape:(pressed||containsMouse)? Qt.PointingHandCursor: Qt.ArrowCursor
                        onClicked: {
//                            var songListId = recSongListIds[index]
//                            client.songList(songListId)
//                            rightArea.songListInfo = client.getSongListBasicInfo(songListId)

//                            rightArea.songsListTable = client.getSongListSongs(songListId)
//                            appendSong(rightArea.songsListTable)
//                            Js.popView(11)
                        }
                    }

                    Rectangle {
                        id:playQuantityRectangle
                        anchors.top:recImae.top
                        anchors.right: recImae.right
                        width:  recImae.height * 0.15
                        height:recImae.width * 0.4
                        anchors.rightMargin: 18
                        anchors.topMargin: -18
                        color: parent.color
                        rotation:90
                        //visible:!recMouse.containsMouse && backImage.status === Image.Ready
                        visible: recMouse.containsMouse ? false : true
                        gradient: Gradient {
                            GradientStop{
                                position: 0.0;
                                color: Qt.rgba(0,0,0,0.7);

                            }
                            GradientStop{
                                position: 1.0;
                                color: Qt.rgba(0,0,0,0);
                            }
                        }
                    }
                    Text {
                        anchors.top:rectangle.top
                        anchors.topMargin: 0
                        anchors.right: rectangle.right
                        anchors.rightMargin: 5
                        //anchors.topMargin: 15
                        id: clickQuantityText
                        text: clickQuantity
                        color: "white"
                        visible: recMouse.containsMouse ? false : true
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
                Text {
                    id: songsNumber_
                    text: 0 + "首"
                    color:"#6b6b6b"
                }
            }
        }
    }

}
