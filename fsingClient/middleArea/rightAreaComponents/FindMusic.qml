import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.11
import "../../element/FindMusic"
import "../../element"

Rectangle {
    id:findMusic_
    color: "#fafafa"
    property int index: 0
    property var recSongListNames: client.getRecommendSongListNames()
    property var recSongListIcons: client.getRecommendSongListIcons()

    ListModel{
        id: menuModel
        ListElement{
            menuName:"个性歌单"
        }
        ListElement{
            menuName:"歌单"
        }
        ListElement{
            menuName:"排行榜"
        }
        ListElement{
            menuName:"歌手"
        }
        ListElement{
            menuName:"最新音乐"
        }
    }
    ScrollView{
        id:findMusicView
        anchors.fill: parent
        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        Column{
            x:30
            spacing: 20
            id:column
            width:findMusicView - 45
            //height: parent.implicitHeight
            //height: recTopView.height + stackLayout.height
            //height: bar.height+1+recommendedSongListsPreview.height
            Rectangle{
                id:recTopView
                width: findMusicView.width - 45
                height: 31
                color: "transparent"
                MyTabBar{
                    id: bar
                    x:(findMusicView.width - 400)/2
                    y:0
                    width: findMusicView.width-300
                    buttonWidth: 60
                    currentIndex: 0

                    height: 30
                    spacing: 20
                    textNormalColor:"#606060"
                    textClickColor: topArea.color
                    textHoverColor: topArea.color
                    hoverColor: findMusic_.color
                    clickColor: findMusic_.color
                    normalColor: findMusic_.color
                    lineColor: topArea.color

                    myModel: ["个性推荐", "歌单", "排行榜","歌手","最新音乐"]
                }
                Rectangle{
                    width: findMusicView.width - 60
                    height: 1
                    color: "#e1e1e2"
                    anchors.bottom: bar.bottom
                }
            }
//            StackLayout{
//                id:stackLayout
//                width: recTopView.width
//                height: if (currentIndex === 0){
//                            return recommendedSongListsPreview.height
//                        } else if (currentIndex === 1){
//                            console.log(songList.height)
//                            return songList.height
//                        }
//                currentIndex: bar.currentIndex
//                RecommendedSongListsPreview{
//                    id:recommendedSongListsPreview
//                }
//                Rectangle{
//                    id:songList

//                    //width: findMusicView.width-60
//                    width: parent.width
//                    height: 600
//                    color: "pink"
//                }

//                onHeightChanged: {
//                    console.log("stackLayout height changed!   "+ height)
//                }

//            }


                RecommendedSongListsPreview{
                    //property int number: 0
                    id:recommendedSongListsPreview
                    width: recTopView.width
                    visible: bar.currentIndex === 0 ? true : false

                }
                Rectangle{
                    id:songList
                    //property int number: 0

                    //width: findMusicView.width-60
                    width: recTopView.width
                    height: 600
                    color: "pink"
                    visible: bar.currentIndex === 1 ? true : false
                }

        }
    }

    onRecSongListNamesChanged: {
        recSongListsModel()
    }

    //TODO
    function recSongListsModel(){
        if (recSongListNames.length !== 0){
            var i = 0
            for (; i < recSongListNames.length; i++){
//                recommendedSongListsPreview.recModel.append({"icon": "file:///root/gridView/zhenhy.jpg","name":recSongListNames[i]})
                recommendedSongListsPreview.recModel.setProperty(i, "name", recSongListNames[i])
                //client.fileTransfer(recSongListIcons[i])
                var path = "file://" + applicationDirPath + "/" + recSongListIcons[i]
                recommendedSongListsPreview.recModel.setProperty(i, "icon", path)
            }
        }
    }


    //        RecommendedSongListsPreview{
    //            id:recommendedSongListsPreview
    //            //y:50
    //            width: findMusicView.width - 60
    //        }


}
