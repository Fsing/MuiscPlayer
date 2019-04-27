import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.11
import "../../element/FindMusic"
import "../../element"

Rectangle {
    id:findMusic_
    property int index: 0
    color: "#fafafa"
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
            id:column
            width:findMusicView - 60
            height: bar.height+1+stackLayout.height
            MyTabBar{
                id: bar
                y:0
                x: (findMusicView.width - 400)/2-30
                width: findMusicView.width-300
                buttonWidth: 60

                height: 30
                spacing: 20
                textNormalColor:"#606060"
                textClickColor: topArea.color
                textHoverColor: topArea.color
                hoverColor: findMusic_.color
                clickColor: findMusic_.color
                normalColor: findMusic_.color
                lineColor: topArea.color

                myModel: ["个性推荐", "歌单", "主播电台","排行榜","歌手","最新音乐"]
            }
            Rectangle{
                width: findMusicView.width - 60
                height: 1
                color: "#e1e1e2"
            }
            StackLayout{
                id:stackLayout
                width: column.width
                //height: initialItem.height
                //height: recommendedSongListsPreview.height
                currentIndex: bar.currentIndex
                RecommendedSongListsPreview{
                    id:recommendedSongListsPreview
                    y:20
                    width: findMusicView.width
                }
                Rectangle{
                    id:songList
                    width: findMusicView.width-60
                    height: 700
                    color: "pink"
                }
                onCurrentIndexChanged: {
                    if (currentIndex === 0)
                        height = recommendedSongListsPreview.height
                    else if (currentIndex === 1){
                        height = songList.height
                    }
                }

            }

        }
    }



//            RecommendedSongListsPreview{
//                id:recommendedSongListsPreview
//                y:20
//                width: findMusicView.width - 60
//            }

}
