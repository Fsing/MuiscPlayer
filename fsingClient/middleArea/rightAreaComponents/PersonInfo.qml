import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../../element/personalInfo"

Item {
    id:personInfo
//    width: 900
//    height: 800
    anchors.fill: parent
    ScrollView{
        id:findMusicView
        anchors.fill: parent
        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        Column{
            PersonBaseInfo{
                width:personInfo.width
                name:client.getUserName()
                icon:"file://"+ applicationDirPath + "/" +client.getUserIcon()
                personalInfo:client.getUserLabel()
                address:client.getUserAddress()
            }
            PersonSongLists{
                width:personInfo.width
                partName: "歌单"
                personSongListsModel: textModel1
                height: ((personInfo.width-30)/5 + 50) * Math.ceil(textModel1.count/5)+50
            }
            PersonSongLists{
                width:personInfo.width
                partName: "收藏"
                personSongListsModel: textModel2
                height: ((personInfo.width-30)/5 + 50) * Math.ceil(textModel2.count/5)+50
            }
        }
    }

    ListModel{
        id:textModel1
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:10
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:11
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:12
        }
    }

    ListModel{
        id:textModel2
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:10
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:11
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:12
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:11
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:12
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:11
        }
        ListElement {
            icon: "file:///root/gridView/zhenhy.jpg"
            name: "未知"
            clickQuantity:12
        }
    }

}
