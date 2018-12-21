import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

Item {
    anchors.fill: parent
    property var searchModel: []

    TableView {
        id: searchview
        visible: true
        anchors.fill: parent
        model: searchModel

        TableViewColumn {
            title: "id"
            role: "sid"
        }

        TableViewColumn {
            title: "操作"
            role: "salbum"
        }

        TableViewColumn {
            title: "标题"
            role: "sname"
        }

        TableViewColumn {
            title: "歌手"
            role: "ssinger"
        }

        TableViewColumn {
            title: "专辑"
            role: "salbum"
        }
        TableViewColumn {
            title: "playQuantity"
            role: "splayQuantity"
        }
        onDoubleClicked: {
            client.songInformation(searchModel.get(searchview.currentRow).sid)
            if (!client.currentPlayListSong(searchModel.get(
                                                searchview.currentRow).sid)) {
                mediaPlayer.playlist.addItem(searchModel.get(
                                                 searchview.currentRow).ssource)
                songChanged(searchModel.get(searchview.currentRow).ssource)
                clickedListSong(searchModel.get(searchview.currentRow).ssource)
                mediaPlayer.play()
            } else {
                songChanged(searchModel.get(searchview.currentRow).ssource)
                clickedListSong(searchModel.get(searchview.currentRow).ssource)
                mediaPlayer.play()
            }
        }
    }
}
