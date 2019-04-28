import QtQuick 2.0
import "../../songList"

Rectangle {
    property int index: 9
    //anchors.fill: parent
    color:"lightblue"

    ListModel{
        id:dlsfljsdf
        ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
               ListElement{
                   number: "01"
                   operator:""
                   title:"慢慢喜欢你"
                   artist:"莫文蔚"
                   album:"我们在中场等你"
                   time:"03:41"
               }
    }

    SongList{
        width: parent.width
        height: parent.height
        songListName: "我喜欢的音乐"
        songListCreateTime: "2017-03-12"
        userName: "eva"


        onSongListNameChanged: {
            console.log("dlsdlfjlsdfjldsfjlds")
            songListModel.append({"number": "01",
                                     "operator":"",
                                     "title":"慢慢喜欢你",
                                     "artist":"莫文蔚",
                                     "album":"我们在中场等你",
                                     "time":"03:41"})
        }
    }
}
