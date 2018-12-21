import QtQuick 2.0
import QtQuick.Layouts 1.1
import "../dialog/common"

Rectangle {
    id: operationItem
    width: 200
    height: 30 * collectSongModel.count
    property alias collectSongModel: collectSongModel
    property var viewCurrentIndex: collectedSongListsView.currentIndex

    signal createSongList
    signal collectSongToSongList

    ListModel {
        id: collectSongModel
        ListElement {
            songlistName: "新建歌单"
            iconSource: "../../images/common/user.png"
            imageVisible: false
        }
        ListElement {
            songlistName: "我喜欢"
            iconSource: "../../images/common/user.png"
            imageVisible: false
        }
    }

    Component {
        id: itemDelegate

        ButtonItem {
            width: 180
            utext: songlistName
            usource: iconSource
            endImageVisible: imageVisible
            onButtonClick: {
                collectedSongListsView.currentIndex = index
                if (index === 0) {
                    console.log("collectedSongListsView.currentIndex:   " + index)
                    createSongList()
                } else
                    collectSongToSongList()
            }
        }
    }

    ListView {
        anchors.fill: parent
        id: collectedSongListsView
        model: collectSongModel
        delegate: itemDelegate
    }
}
