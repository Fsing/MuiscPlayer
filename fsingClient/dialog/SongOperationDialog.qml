import QtQuick 2.0
import "./common"

CommonDialog {
    id: songOperationDialog

    width: 200
    height: 300
    z: 10

    property var songIndex: -1

    contentItem: SongOperationItem {
        id: operation
        onCollectSongClick: {
            collectSong.x = operation.width
            collectSong.y = pos * 30
            console.log(collectSong.x, collectSong.y)
            collectSong.open()

            var i = 0
            while (client.createdSongLists()[i]) {
                collectSong.collectSongModel.append({
                                                        songlistName: client.createdSongLists(
                                                                          )[i],
                                                        iconSource: "../../images/common/user.png",
                                                        imageVisible: false
                                                    })
                i++
            }
        }
    }

    CollectSongDialog {
        id: collectSong
    }

    function clickSongIndex(pos) {
        console.log("clickSongIndex(pos): " + pos)
        songIndex = pos
    }
}
