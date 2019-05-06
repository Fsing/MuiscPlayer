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
    property var recSongListIds: client.getRecommendSongListIds()
    property var recSongListClickQuantity: client.getRecommendSongListClickQuantity()

    //数据格式：[id,listName,userName,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity,]
    //property var recSongListsInfo: client.getRecSongListBasicInfo()

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

            Advert{
                id: advert
                modle: advertListmodle
                width: recTopView.width
                //Layout.fillWidth: true
                visible: bar.currentIndex === 0 ? true : false
            }

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

    ListModel {
        id: advertListmodle
    }

    Timer {
        interval: 100
        running: true
        onTriggered: advertAppend()
    }


    function advertAppend() {
        var list = client.getAdvertImages();
        //console.log(interfaceParamter)
        for (var i = 0; i < list.length; ++i) {
            advertListmodle.append({
                                       advertImg: "file:///" + applicationDirPath
                                                  + "/" + list[i]
                                   })
        }
    }

    //TODO
    function recSongListsModel(){
//        if (recSongListNames.length !== 0){
        if (recSongListNames.length !== 0){
            var i = 0
            for (; i < recSongListNames.length; i++){
                recommendedSongListsPreview.recModel.setProperty(i, "name", recSongListNames[i])
                var path = "file://" + applicationDirPath + "/" + recSongListIcons[i]
                recommendedSongListsPreview.recModel.setProperty(i, "icon", path)
                recommendedSongListsPreview.recModel.setProperty(i, "clickQuantity", recSongListClickQuantity[i])

            }
        }
    }



    //        RecommendedSongListsPreview{
    //            id:recommendedSongListsPreview
    //            //y:50
    //            width: findMusicView.width - 60
    //        }


}
