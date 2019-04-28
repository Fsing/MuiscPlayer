import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../element"
import "../dialog"

Rectangle {
    id: songlist
    anchors.fill: parent

    property int index:10
    property string songListId
    property string userName
    property string userImage
    property string songListName
    property string songListCreateTime
    property string label
    property string briefInfo
    //property var songListModel: listmodel

    ListModel{
        id:listmodel

        ListElement{
                    number: "01"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "02"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "03"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "04"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "05"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "06"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "07"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "08"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "09"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "09"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "09"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "09"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }
                ListElement{
                    number: "09"
                    operator:""
                    title:"慢慢喜欢你"
                    artist:"莫文蔚"
                    album:"我们在中场等你"
                    time:"03:41"
                }

    }

    ScrollView {
        id: scroll
        anchors.fill: parent

        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        Column{
            //spacing: 0
            SongListTop {
                id: songListTop
                width: songlist.width
                height: 250

                username: userName
                userImg: userImage
                listName: songListName
                createTime:songListCreateTime
                labels: label
                briefInfos:briefInfo
            }

            SongListBottom {
                id: songListBottom
                width: songlist.width
                //height: songlist.height - songListTop.height
               //y:songListTop.y+songListTop.height
            }
        }
    }
}
