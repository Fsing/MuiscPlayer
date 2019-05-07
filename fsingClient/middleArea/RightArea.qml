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

    property var songsListTable         //歌曲列表对象
    property var songListInfo
    property var model_: songsModel_
    property alias stackView: stackView
    property int localListSongsHeight: _locaMusicModel.count * 28 + 130
    property var songInfoList: []
    property bool isLocalListVisable: false
    //property alias searchComponent: searchComponent

    //    property alias lyricCurrent: lyric.current
    //    property alias lyricIndex: lyric.index

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

    Component{
        id:lyricComponent
        Lyric{
            id:lyric
            songSource:applicationDirPath +"/" + leftArea.lyricSource
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

    Component {
        id: searchComponent
        Search {
            id: search

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

    Connections{
        target: topArea.topSearch_
        onSearchKey:{
            console.log("onSearch")
            Js.popView(-2)

            var lists = client.searchResult()
            var count = lists.length/9
            var j = 1;
            var k = '0'
            var m = ''
            for (var i = 0; i < count; i++){
                var num
                if (i < 9){
                    num = k+j
                    j++
                }else{
                    num = m+j
                    j++

                }
                searchModel.append({"number": num,
                                       "operator":"",
                                       "title":lists[i * 9 + 1],
                                       "artist":lists[i * 9 + 2],
                                       "album":lists[i * 9 + 4],
                                       "time":lists[i * 9 + 3]})
            }

        }
    }
    Connections{
        target: topArea
        onBack:{
            if (topArea.backStackView.length > 1){
                topArea.backStackView.pop()
//                if(topArea.backStackView.length > 0){
                    var tmpIndex = topArea.backStackView.length - 1
                    var tmp = topArea.backStackView[tmpIndex]
                    console.log("tmp:                           "+ tmp)
                    Js.popView(topArea.backStackView[tmpIndex])
                if (topArea.backStackView.length === 1)
                    topArea.backAndForwardButton.leftButtonOpacity = 0.5
//                }
            }else {
                topArea.backAndForwardButton.leftButtonOpacity = 0.5
            }
        }
    }

    //歌单 songListComponent的model
    ListModel{
        id:songsModel_
    }
    //本地音乐界面的歌曲列表model
    ListModel{
        id:_locaMusicModel
    }
    //本地音乐界面文件目录的model
    ListModel{
        id:_localMusicDir
    }
    //搜索界面的model
    ListModel{
        id:searchModel
    }
    //在线歌单界面的model
    ListModel{
        id:onlineListModel
    }
}
