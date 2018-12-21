import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import "../dialog"

Rectangle {
    id: rec_parent
    width: 200
    height: parent.height //topArea.height - bottomArea.height
    color: "#F5F5F7"

    property int modelindex: -1
    property bool showAllCreateClicked: false
    property int creatIndex: 9
    property int maxIndex: listModel.count
    property var listmodel: listModel
    property alias createSongListDialog: createSongListDialog
    signal leftAreaClicked(int n)

    //-----
    Connections {
        target: mainWindow
    }

    Rectangle {
        id: lyric
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width
        height: 50
        color: "#E8E8E8"
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
                lyricClicked()
                leftAreaClicked(-1)
            }
        }
        Image {
            id: songImage
            width: 50
            height: 50
            anchors.left: parent.left
            source: "../images/leftArea/btnlove2.png"
        }
        Text {
            id: songName
            anchors.left: songImage.right
            anchors.leftMargin: 10
            width: 50
            color: "#FF3030"
        }
    }

    ScrollView {
        id: leftItem
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: lyric.top
        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        ListView {
            id: listView
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.left: parent.left
            spacing: 10
            width: rec_parent.width - 10
            height: rec_parent.height
            model: listModel
            delegate: delegates
        }
    }

    Component {
        id: delegates
        LeftItem {
            id: leftItemDelegates
            width: parent.width - 10
            height: classfify.visible ? 50 : 25
            onItemClicked: {
                listView.currentIndex = index
                console.log("listView.currentIndex = " + listView.currentIndex)
                leftAreaClicked(index)
                if (listView.currentIndex > 9) {
                    var i = index - 10

                    var j = client.createdSongListIDs()[i]
                    console.log(j + "]]]]]]]]]]")
                    client.songList(j)
                    rightArea.songListInfo = client.getSongListInformation(j)
                    console.log("songlistInfo: " + rightArea.songListInfo[1])
                    rightArea.appendSongs(j)
                }
            }
            onCreateClicked: createSongListDialog.open()
        }
    }
    ListModel {
        id: listModel
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/sound.png"
            tx: "发现音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "推荐"
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnradio2.png"
            tx: "私人FM"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnmv.png"
            tx: "MV"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnfriends.png"
            tx: "朋友"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/localMusic.png"
            tx: "本地音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "我的音乐"
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btndownload.png"
            tx: "下载管理"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/sound.png"
            tx: "我的音乐云盘"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/sound.png"
            tx: "我的歌手"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnmv.png"
            tx: "我的MV"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnfavorite.png"
            tx: "我喜欢的音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "创建的歌单"
            showAllCreateVisible: true
            delegate_listVisible: false
        }
    }

    onShowAllCreateClickedChanged: {
        if (rec_parent.showAllCreateClicked) {
            var i = maxIndex - 1
            for (i; i >= creatIndex; i--) {
                listModel.setProperty(i, "delegate_listVisible", true)
            }
        } else {
            var j = maxIndex - 1
            for (j; j >= creatIndex; j--) {
                listModel.setProperty(j, "delegate_listVisible", false)
            }
        }
    }
    CreateSongListDialog {
        id: createSongListDialog
        onInputAccepted: {
            listModel.append({
                                 recColor: "#F5F5F7",
                                 imagesource: "../images/leftArea/list.png",
                                 tx: createSongListDialog.inputText,
                                 opaci: 0.55,
                                 classifyText: "",
                                 delegate_listVisible: true
                             })
        }
    }
}
