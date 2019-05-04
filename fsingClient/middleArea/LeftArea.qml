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
    property string leftItemColor: rec_parent.color

    property string lyricSource
    property string currentSongId
    property string currentSongName:""
    property string currentSinger
    property string currentAlbum
    property var comments
    property string albumImage: "qrc:/images/common/ayi.9.png"

    signal leftAreaClicked(int n)
    signal showComment()

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
        visible:currentSongName === "" ? false :true
        //visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("Commetnt!!!!")
                //client.comment(leftArea.currentSongId,1,10)
                console.log("lyric")
                client.fileTransfer(lyricSource)
                leftAreaClicked(-1)

                //comments = client.getComments()
                showComment()
            }
        }
        Image {
            id: songImage
            width: 50
            height: 50
            anchors.left: parent.left
            fillMode: Image.PreserveAspectCrop
            //source: "../images/leftArea/btnlove2.png"
            source: albumImage
            //source: "file:///root/new10/MuiscPlayer/build-fsingClient-Desktop_Qt_5_11_1_GCC-Debug/不靠谱的日常.jpg"
        }
        Text {
            id: songName
            anchors.left: songImage.right
            anchors.leftMargin: 10
            anchors.top: songImage.top
            anchors.topMargin: 10
            width: 50
            color: "#333333"
            text:currentSongName
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
                leftAreaClicked(index)
            }

            onCreateClicked: {
                createSongListDialog.open()
            }
        }
    }
    ListModel {
        id: listModel
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/sound.png"
            tx: "发现音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "推荐"
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/btnradio2.png"
            tx: "私人FM"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/btnmv.png"
            tx: "MV"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/btnfriends.png"
            tx: "朋友"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/localMusic.png"
            tx: "本地音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "我的音乐"
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/btndownload.png"
            tx: "下载管理"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/sound.png"
            tx: "我的音乐云盘"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/sound.png"
            tx: "我的歌手"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/btnmv.png"
            tx: "我的MV"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "transparent"
            imagesource: "../images/leftArea/btnlove2.png"
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
        x: mainWindow.width / 2 - 150
        y: 100
        onInputAccepted: {

        }
    }
}
