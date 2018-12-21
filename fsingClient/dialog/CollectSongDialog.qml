import QtQuick 2.0
import "../dialog/common"

CommonDialog {
    id: collectSongDialog
    z: 10
    property alias collectSongModel: collectsongItem.collectSongModel

    width: 200
    height: collectsongItem.height + 20
    contentItem: CollectSongItem {
        id: collectsongItem
        onCreateSongList: {
            leftArea.createSongListDialog.open()
            collectSongDialog.close()
            songOperationDialog.close()
        }
        onCollectSongToSongList: {
            var tmp = songlist.collecSong()
            console.log("rightArea.collecSong(tmp):   " + tmp)
            var list = client.getSongListSongs(tmp)
            var songId = list[songOperationDialog.songIndex * 8]
            var collectSongListId = client.createdSongListIDs(
                        )[collectsongItem.viewCurrentIndex - 2]

            console.log("songId:   " + songId)
            console.log("cellectSongListId:   " + collectSongListId)
            client.addSongToSongList(collectSongListId, songId)
            collectSongDialog.close()
            songOperationDialog.close()
        }
    }
}
