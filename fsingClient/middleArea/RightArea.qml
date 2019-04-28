import QtQuick 2.5
import QtQuick.Controls 2.1
import "rightAreaComponents"
import "../songList"
import "RightAreaJS.js" as Js

Rectangle {
    anchors.left: leftArea.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom

   // property alias downloadModel2:downloadModel1

//    ListModel{
//        id:downloadModel1
//    }

    property var songListInfo
    property var model_: songsModel_
    property alias stackView: stackView
    //property alias searchComponent: searchComponent

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem:findMusicComponent

        popEnter: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 0
                to: 1
                duration: 1000
            }
        }

        popExit: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 1
                to: 0
                duration: 1000
            }
        }
        pushEnter: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 0
                to: 1
                duration: 1000
            }
        }

        pushExit: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 1
                to: 0
                duration: 1000
            }
        }
    }

    Connections {
        target: leftArea
        onLeftAreaClicked: {
            console.log("Js.popView(n)" + n)
            Js.popView(n)
            console.log("deepth" + stackView.depth)
        }
    }

    Component {
        id: findMusicComponent
        FindMusic {
            id: findMusic
        }
    }
    Component {
        id: fmComponent
        FM {
            id: fm
        }
    }
    Component {
        id: mvComponent
        Mv {
            id: mv
        }
    }
    Component {
        id: friendComponent
        Friends {
            id: friend
        }
    }
    Component {
        id: localMusicComponent

        LocalMusic {

            id: localMusic
        }
    }
    Component {
        id: downloadComponent
//        property alias dowload: download
        Download {
            id: download
            //downloadModels:downloadModel1
        }
    }
    Component {
        id: myMusicCloudDiskComponent
        MyMusicCloudDisk {
            id: myMusicCloudDisk
        }
    }
    Component {
        id: mySingerComponent
        MySinger {
            id: mySinger
        }
    }
    Component {
        id: myMvComponent
        MyMv {
            id: mymv
        }
    }

    Component {
        id: favoriteComponent
        MyFavorite {
            id: favorite
        }
    }

    Component{
        id:songListComponent
        SongList{
            id:mySongList
            songListId_: songListInfo[0]
            userName_:songListInfo[2]
            //userImage_:songListInfo[2]
            songListName_:songListInfo[1]
            songListImage_: "file://"+ applicationDirPath + "/" + songListInfo[6]
            songListCreateTime_:songListInfo[3]
            label_:songListInfo[4]
            briefInfo_:songListInfo[5]

            songListModel: model_
        }
    }

    ListModel{
        id:songsModel_
    }
}
